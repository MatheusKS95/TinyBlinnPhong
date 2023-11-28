/**
 * Matheus' Simple 3D Math
 * Copyright 2023 Matheus Klein Schaefer
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

/**
 * @file 3d_math.c
 * @brief 3d_math.h implementation file
 * 
 * @author
 * - Matheus Klein Schaefer
*/

#include <math.h>
#include "3d_math.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

void math_vec2_zero(vec2 vec)
{
	vec[0] = 0.0f;
	vec[1] = 0.0f;
}

void math_vec2_min(vec2 result, vec2 vec_a, vec2 vec_b)
{
	result[0] = fminf(vec_a[0], vec_b[0]);
	result[1] = fminf(vec_a[1], vec_b[1]);
}

void math_vec2_max(vec2 result, vec2 vec_a, vec2 vec_b)
{
	result[0] = fmaxf(vec_a[0], vec_b[0]);
	result[1] = fmaxf(vec_a[1], vec_b[1]);
}

void math_vec2_copy(vec2 result, vec2 original)
{
	result[0] = original[0];
	result[1] = original[1];
}

void math_vec2_add(vec2 result, vec2 vec_a, vec2 vec_b)
{
	result[0] = vec_a[0] + vec_b[0];
	result[1] = vec_a[1] + vec_b[1];
}

void math_vec2_sub(vec2 result, vec2 vec_a, vec2 vec_b)
{
	result[0] = vec_a[0] - vec_b[0];
	result[1] = vec_a[1] - vec_b[1];
}

void math_vec2_scale(vec2 result, vec2 vec, float scalar)
{
	result[0] = vec[0] * scalar;
	result[1] = vec[1] * scalar;
}

float math_vec2_dot(vec2 vec_a, vec2 vec_b)
{
	float dot = vec_a[0] * vec_b[0] + vec_a[1] * vec_b[1];
	return dot;
}

float math_vec2_cross(vec2 vec_a, vec2 vec_b)
{
	float cross = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
	return cross;
}

float math_vec2_len(vec2 vec)
{
	float result = sqrtf(math_vec2_dot(vec, vec));
	return result;
}

void math_vec2_normalize(vec2 result, vec2 vec)
{
	float norm = math_vec2_len(vec);

	if(norm == 0.0f)
	{
		math_vec2_zero(result);
		return;
	}
	math_vec2_scale(result, vec, 1.0f / norm);
}

/*void math_vec2_lerp(vec2 result, vec2 vec_a, vec2 vec_b, float amount)
{
	glm_vec2_lerp(vec_a, vec_b, amount, result);
}*/

void math_vec3_zero(vec3 vec)
{
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
}

void math_vec3_min(vec3 result, vec3 vec_a, vec3 vec_b)
{
	result[0] = fminf(vec_a[0], vec_b[0]);
	result[1] = fminf(vec_a[1], vec_b[1]);
	result[2] = fminf(vec_a[2], vec_b[2]);
}

void math_vec3_max(vec3 result, vec3 vec_a, vec3 vec_b)
{
	result[0] = fmaxf(vec_a[0], vec_b[0]);
	result[1] = fmaxf(vec_a[1], vec_b[1]);
	result[2] = fmaxf(vec_a[2], vec_b[2]);
}

void math_vec3_copy(vec3 result, vec3 original)
{
	result[0] = original[0];
	result[1] = original[1];
	result[2] = original[2];
}

void math_vec3_negate(vec3 result, vec3 vec)
{
	result[0] = -vec[0];
	result[1] = -vec[1];
	result[2] = -vec[2];
}

void math_vec3_add(vec3 result, vec3 vec_a, vec3 vec_b)
{
	result[0] = vec_a[0] + vec_b[0];
	result[1] = vec_a[1] + vec_b[1];
	result[2] = vec_a[2] + vec_b[2];
}

void math_vec3_sub(vec3 result, vec3 vec_a, vec3 vec_b)
{
	result[0] = vec_a[0] - vec_b[0];
	result[1] = vec_a[1] - vec_b[1];
	result[2] = vec_a[2] - vec_b[2];
}

void math_vec3_div(vec3 result, vec3 vec, float div)
{
	result[0] = vec[0] / div;
	result[1] = vec[1] / div;
	result[2] = vec[2] / div;
}

void math_vec3_scale(vec3 result, vec3 vec, float scalar)
{
	result[0] = vec[0] * scalar;
	result[1] = vec[1] * scalar;
	result[2] = vec[2] * scalar;
}

float math_vec3_dot(vec3 vec_a, vec3 vec_b)
{
	float dot = vec_a[0] * vec_b[0] + vec_a[1] * vec_b[1] + vec_a[2] * vec_b[2];
	return dot;
}

void math_vec3_cross(vec3 result, vec3 vec_a, vec3 vec_b)
{
	result[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
	result[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
	result[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
}

float math_vec3_len(vec3 vec)
{
	float result = sqrtf(math_vec3_dot(vec, vec));
	return result;
}

void math_vec3_normalize(vec3 vec)
{
	float norm = math_vec3_len(vec);

	if(norm == 0.0f)
	{
		math_vec3_zero(vec);
		return;
	}
	math_vec3_scale(vec, vec, 1.0f / norm);
}

void math_vec3_normalize_to(vec3 result, vec3 vec)
{
	float norm = math_vec3_len(vec);

	if(norm == 0.0f)
	{
		math_vec3_zero(result);
		return;
	}
	math_vec3_scale(result, vec, 1.0f / norm);
}

/*void math_vec3_lerp(vec3 result, vec3 vec_a, vec3 vec_b, float amount)
{
	glm_vec3_lerp(vec_a, vec_b, amount, result);
}*/


void math_vec4_zero(vec4 vec)
{
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
	vec[3] = 0.0f;
}

void math_vec4_min(vec4 result, vec4 vec_a, vec4 vec_b)
{
	result[0] = fminf(vec_a[0], vec_b[0]);
	result[1] = fminf(vec_a[1], vec_b[1]);
	result[2] = fminf(vec_a[2], vec_b[2]);
	result[3] = fminf(vec_a[3], vec_b[3]);
}

void math_vec4_max(vec4 result, vec4 vec_a, vec4 vec_b)
{
	result[0] = fmaxf(vec_a[0], vec_b[0]);
	result[1] = fmaxf(vec_a[1], vec_b[1]);
	result[2] = fmaxf(vec_a[2], vec_b[2]);
	result[3] = fmaxf(vec_a[3], vec_b[3]);
}

void math_vec4_copy(vec4 result, vec4 original)
{
	result[0] = original[0];
	result[1] = original[1];
	result[2] = original[2];
	result[3] = original[3];
}

void math_vec4_add(vec4 result, vec4 vec_a, vec4 vec_b)
{
	result[0] = vec_a[0] + vec_b[0];
	result[1] = vec_a[1] + vec_b[1];
	result[2] = vec_a[2] + vec_b[2];
	result[3] = vec_a[3] + vec_b[3];
}

void math_vec4_sub(vec4 result, vec4 vec_a, vec4 vec_b)
{
	result[0] = vec_a[0] - vec_b[0];
	result[1] = vec_a[1] - vec_b[1];
	result[2] = vec_a[2] - vec_b[2];
	result[3] = vec_a[3] - vec_b[3];
}

void math_vec4_div(vec4 result, vec4 vec, float div)
{
	result[0] = vec[0] / div;
	result[1] = vec[1] / div;
	result[2] = vec[2] / div;
	result[3] = vec[3] / div;
}

void math_vec4_scale(vec4 result, vec4 vec, float scalar)
{
	result[0] = vec[0] * scalar;
	result[1] = vec[1] * scalar;
	result[2] = vec[2] * scalar;
	result[3] = vec[3] * scalar;
}

float math_vec4_dot(vec4 vec_a, vec4 vec_b)
{
	float dot = vec_a[0] * vec_b[0] + vec_a[1] * vec_b[1] + vec_a[2] * vec_b[2] + vec_a[3] * vec_b[3];
	return dot;
}

float math_vec4_len(vec4 vec)
{
	float result = sqrtf(math_vec4_dot(vec, vec));
	return result;
}

void math_vec4_normalize(vec4 vec)
{
	float norm = math_vec4_len(vec);

	if(norm == 0.0f)
	{
		math_vec4_zero(vec);
		return;
	}
	math_vec4_scale(vec, vec, 1.0f / norm);
}

/*void math_vec4_lerp(vec4 result, vec4 vec_a, vec4 vec_b, float amount)
{
	glm_vec4_lerp(vec_a, vec_b, amount, result);
}*/

void math_mat4_zero(mat4 mat)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			mat[i][j] = 0.0f;
}

void math_mat4_identity(mat4 mat)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			mat[i][j] = i == j ? 1.0f : 0.0f;
}

void math_mat4_add(mat4 result, mat4 mat_a, mat4 mat_b)
{
	for(int i = 0; i < 4; ++i)
	{
		math_vec4_add(result[i], mat_a[i], mat_b[i]);
	}
}

void math_mat4_sub(mat4 result, mat4 mat_a, mat4 mat_b)
{
	for(int i = 0; i < 4; ++i)
	{
		math_vec4_sub(result[i], mat_a[i], mat_b[i]);
	}
}

void math_mat4_scale(mat4 result, mat4 mat, float s)
{
	for(int i = 0; i < 4; i++)
	{
		math_vec4_scale(result[i], mat[i], s);
	}
}

void math_mat4_row(vec4 result, mat4 mat, uint8_t index)
{
	for(uint8_t j = 0; j < 4; ++j)
	{
		result[j] = mat[j][index];
	}
}

void math_mat4_col(vec4 result, mat4 mat, uint8_t index)
{
	for(int j = 0; j < 4; ++j)
	{
		result[j] = mat[index][j];
	}
}

void math_mat4_scale_xyz(mat4 mat, float scalar)
{
	math_mat4_scale(mat, mat, scalar);
}

void math_mat4_mul(mat4 result, mat4 mat_a, mat4 mat_b)
{
	int i, j, k;

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			result[i][j] = 0.0f;
			for(k = 0; k < 4; k++)
			{
				result[i][j] += mat_a[i][k] * mat_b[k][j];
			}
		}
	}
}

void math_mat4_copy(mat4 result, mat4 original)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			result[i][j] = original[i][j];
}

void math_mat4_translate(mat4 mat, vec3 vec)
{
	mat[0][3] += vec[0];
	mat[1][3] += vec[1];
	mat[2][3] += vec[2];
}

void math_mat4_rotate_axis(mat4 mat, vec3 axis, float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	float t = 1.0f - c;

	float x = axis[0];
	float y = axis[1];
	float z = axis[2];

	mat[0][0] = t * x * x + c;
	mat[0][1] = t * x * y - s * z;
	mat[0][2] = t * x * z + s * y;
	mat[0][3] = 0.0f;

	mat[1][0] = t * x * y + s * z;
	mat[1][1] = t * y * y + c;
	mat[1][2] = t * y * z - s * x;
	mat[1][3] = 0.0f;

	mat[2][0] = t * x * z - s * y;
	mat[2][1] = t * y * z + s * x;
	mat[2][2] = t * z * z + c;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
}

void math_mat4_rotate_x(mat4 result, mat4 mat, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	mat4 aux;
	math_mat4_identity(result);
	aux[1][1] = c;
	aux[1][2] = s;
	aux[2][1] = -s;
	aux[2][2] = c;

	math_mat4_mul(result, mat, aux);
}

void math_mat4_rotate_y(mat4 result, mat4 mat, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	mat4 aux;
	math_mat4_identity(result);
	aux[0][0] = c;
	aux[0][2] = -s;
	aux[2][0] = s;
	aux[2][2] = c;

	math_mat4_mul(result, mat, aux);
}

void math_mat4_rotate_z(mat4 result, mat4 mat, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	mat4 aux;
	math_mat4_identity(result);
	aux[0][0] = c;
	aux[0][1] = s;
	aux[1][0] = -s;
	aux[1][1] = c;

	math_mat4_mul(result, mat, aux);
}

void math_quat_zero(quat qt)
{
	qt[0] = qt[1] = qt[2] = qt[3] = 0.0f;
}

void math_quat_identity(quat qt)
{
	qt[0] = qt[1] = qt[2] = 0.0f;
	qt[3] = 1.0f;
}

void math_quat_add(quat result, quat qt_a, quat qt_b)
{
	math_vec4_add(result, qt_a, qt_b);
}

void math_quat_sub(quat result, quat qt_a, quat qt_b)
{
	math_vec4_sub(result, qt_a, qt_b);
}

void math_quat_scale(quat result, quat qt, float scalar)
{
	result[0] = qt[0] * scalar;
	result[1] = qt[1] * scalar;
	result[2] = qt[2] * scalar;
	result[3] = qt[3] * scalar;
}

void math_quat_norm(quat result, quat qt)
{
	float k = 1.0f / math_vec4_len(qt); //quat is literally vec4 here
	math_quat_scale(result, qt, k);
}

void math_lookat(mat4 result, vec3 position, vec3 target, vec3 up)
{
	vec3 f;
	vec3 u;
	vec3 s;

	math_vec3_sub(f, target, position);
	math_vec3_normalize(f);

	math_vec3_cross(s, f, up);
	math_vec3_normalize(s);
	math_vec3_cross(u, s, f);

	result[0][0] = s[0];
	result[0][1] = u[0];
	result[0][2] =-f[0];
	result[1][0] = s[1];
	result[1][1] = u[1];
	result[1][2] =-f[1];
	result[2][0] = s[2];
	result[2][1] = u[2];
	result[2][2] =-f[2];
	result[3][0] = -math_vec3_dot(s, position);
	result[3][1] = -math_vec3_dot(u, position);
	result[3][2] = math_vec3_dot(f, position);
	result[0][3] = result[1][3] = result[2][3] = 0.0f;
	result[3][3] = 1.0f;
}

void math_perspective(mat4 result, float fov, float aspect, float near, float far)
{
	float f;
	float fn;

	math_mat4_zero(result);

	f = 1.0f / tanf(fov * 0.5f);
	fn = 1.0f / (near - far);

	result[0][0] = f / aspect;
	result[1][1] = f;
	result[2][2] = far * fn;
	result[2][3] = -1.0f;
	result[3][2] = near * far * fn;
}

float deg_to_rad(float deg)
{
	return deg * (M_PI / 180.0f);
}

float rad_to_deg(float rad)
{
	return rad * (180.0f / M_PI);
}

float math_lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}
