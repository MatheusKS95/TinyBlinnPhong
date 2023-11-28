/**
 * Matheus' Tiny Blinn Phong
 * Copyright 2023 Matheus Klein Schaefer
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

/**
 * This is a simplified version of
 * https://learnopengl.com/Advanced-Lighting/Advanced-Lighting but using
 * only blinn-phong shaders. I converted it from C++ to C and from GLFW
 * to SDL.
 * The shaders are for non-commercial usage.
 * This is not production-ready, don't even try.
*/

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "gl.h"
#include "3d_math.h"
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int load_texture(char const *path)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);

	int width, height, nrcomp;
	unsigned char *data = stbi_load(path, &width, &height, &nrcomp, 0);
	if (data)
	{
		GLenum format;
		switch(nrcomp)
		{
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
			default: format = GL_RED; break;
		}

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		printf("The following texture failed to load: %s\n", path);
		stbi_image_free(data);
	}

	return texture_id;
}

//non commercial
const char *vertexshadersource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aNormal;\n"
		"layout (location = 2) in vec2 aTexCoords;\n"
		"out VS_OUT\n"
		"{\n"
		"	vec3 FragPos;\n"
		"	vec3 Normal;\n"
		"	vec2 TexCoords;\n"
		"} vs_out;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vs_out.FragPos = aPos;\n"
		"	vs_out.Normal = aNormal;\n"
		"	vs_out.TexCoords = aTexCoords;\n"
		"	gl_Position = projection * view * vec4(aPos, 1.0);\n"
		"}\0";

//non commercial
const char *fragshadersource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in VS_OUT\n"
		"{\n"
		"	vec3 FragPos;\n"
		"	vec3 Normal;\n"
		"	vec2 TexCoords;\n"
		"} fs_in;\n"
		"uniform sampler2D floortexture;\n"
		"uniform vec3 light_pos;\n"
		"uniform vec3 view_pos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec3 color = texture(floortexture, fs_in.TexCoords).rgb;\n"
		"	// ambient\n"
		"	vec3 ambient = 0.05 * color;\n"
		"	// diffuse\n"
		"	vec3 light_dir = normalize(light_pos - fs_in.FragPos);\n"
		"	vec3 normal = normalize(fs_in.Normal);\n"
		"	float diff = max(dot(light_dir, normal), 0.0);\n"
		"	vec3 diffuse = diff * color;\n"
		"	// specular\n"
		"	vec3 view_dir = normalize(view_pos - fs_in.FragPos);\n"
		"	vec3 reflect_dir = reflect(-light_dir, normal);\n"
		"	float spec = 0.0;\n"
		"	vec3 halfway_dir = normalize(light_dir + view_dir);\n"
		"	spec = pow(max(dot(normal, halfway_dir), 0.0), 32.0);\n"
		"	vec3 specular = vec3(0.3) * spec;\n"
		"	FragColor = vec4(ambient + diffuse + specular, 1.0);\n"
		"}\0";

int main()
{
	SDL_Window *window;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ERROR: %s", SDL_GetError());
		return -1;
	}
		
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	window = SDL_CreateWindow("Basic BlinnPhong renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if(window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ERROR: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
	printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ts_camera camera;
	vec3 cam_pos;
	cam_pos[0] = 0.0f;
	cam_pos[1] = 0.0f;
	cam_pos[2] = -3.0f;
	camera_initialize(&camera, cam_pos);
	float last_x = 800 / 2.0f;
	float last_y = 600 / 2.0f;
	int mouse_x = last_x;
	int mouse_y = last_y;
	bool first_mouse = true;

	//timing
	float delta_time = 0.0f;
	float last_frame = 0.0f;

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexshadersource, NULL);
	glCompileShader(vertex_shader);
	int successvertshader;
	char infolog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &successvertshader);
	if(!successvertshader)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infolog);
		SDL_LogInfo(SDL_LOG_CATEGORY_ERROR, "Vertex shader error: %s", infolog);
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Vertex shader compiled fine.");
	}

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragshadersource, NULL);
	glCompileShader(fragment_shader);
	int successfragshader;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &successfragshader);
	if(!successfragshader)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infolog);
		SDL_LogInfo(SDL_LOG_CATEGORY_ERROR, "Fragment shader error: %s", infolog);
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Fragment shader compiled fine.");
	}

	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	//testa erros no shader program
	int successshaderprogram;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &successshaderprogram);
	if(!successshaderprogram)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infolog);
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Shader program link error: %s", infolog);
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Program linking fine.");
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	float planeVertices[] =
	{
		// positions            // normals         // texcoords
		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		 10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};

	// plane VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	unsigned int floor_texture = load_texture("wood floor 2.png");

	glUseProgram(shader_program);
	glUniform1i(glGetUniformLocation(shader_program, "floortexture"), 0);

	vec3 light_pos;
	light_pos[0] = 0.0f;
	light_pos[1] = 0.1f;
	light_pos[2] = 0.0f;

	SDL_Event event;
	bool playing = true;

	while(playing)
	{
		float currentframe = (float)SDL_GetTicks();
		delta_time = currentframe - last_frame;
		last_frame = currentframe;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Exiting because you quit using ESCAPE.");
					playing = false;
					break;
				}
			}
			if(event.type == SDL_MOUSEMOTION)
			{
				if(first_mouse)
				{
					last_x = mouse_x;
					last_y = mouse_y;
					first_mouse = false;
				}

				mouse_x += event.motion.xrel;
				mouse_y += event.motion.yrel;
				float x_offset = mouse_x - last_x;
				float y_offset = last_y - mouse_y;
				last_x = mouse_x;
				last_y = mouse_y;

				camera_freecam(&camera, x_offset, y_offset, 0);
			}
			if(event.type == SDL_QUIT)
			{
				SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Exiting due to other exit input.");
				playing = 0;
				break;
			}
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw objects
		glUseProgram(shader_program);
		mat4 projection;
		math_perspective(projection, deg_to_rad(camera.zoom), 800 / 600, 0.1f, 100.0f);
		mat4 view;
		camera_get_view_matrix(&camera, view);
		glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, &view[0][0]);
		
		//light uniforms
		glUniform3fv(glGetUniformLocation(shader_program, "view_pos"), 1, &camera.position[0]);
		glUniform3fv(glGetUniformLocation(shader_program, "light_pos"), 1, &light_pos[0]);
		
		//floor
		glBindVertexArray(planeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floor_texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		SDL_GL_SwapWindow(window);
		SDL_UpdateWindowSurface(window);
	}

	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &planeVBO);
	glDeleteProgram(shader_program);

	//shutdown
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
