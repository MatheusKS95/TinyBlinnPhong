/**
 * Matheus' Tiny Blinn Phong
 * Copyright 2023 Matheus Klein Schaefer
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

/**
 * @file camera.h
 * @brief Camera functions
 * 
 * This file has some basic camera functionalities, including
 * initialization, view matrix and freecam settings.
 * 
 * @author
 * - Matheus Klein Schaefer (email here)
*/

#ifndef CAMERA
#define CAMERA

#include "3d_math.h"

typedef struct ts_camera
{
	//standard camera variables
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 world_up;
	//euler angles
	float yaw;
	float pitch;
	float roll;
	//options
	float zoom;
} ts_camera;

///DEFAULT CAMERA VALUES
//will be removed and replaced by settings-based variables in the 
static const float YAW =			-90.0f;
static const float PITCH =			0.0f;
static const float ROLL =			0.0f;
static const float SPEED =			0.1f;
static const float SENSITIVITY =	0.2f;
static const float ZOOM =			45.0f;

/**
 * Easiest camera setup, you just need the camera structure itself and
 * the starting position - all the rest is using default values.
 * @brief Initialize a camera (position only)
 * @param input (camera*) the camera
 * @param position (vec3) initial position
*/
void camera_initialize(ts_camera *input, vec3 position);

/**
 * Set up a camera with all parameters, allowing more control and
 * ignoring default values.
 * @brief Initialize a camera using all parameters
 * @param input (camera*) the camera
 * @param position (vec3) initial position
 * @param up (vec3) up vector
 * @param yaw (float)
 * @param pitch (float)
 * @param roll (float)
 * @param zoom (float)
*/
void camera_initialize_full
(
	ts_camera *input,
	vec3 position,
	vec3 up,
	float yaw,
	float pitch,
	float roll,
	float zoom
);

/**
 * Exactly like camera_initialize_full, but this is if you hate vec3
 * and want to use individual float values.
 * @brief Initialize a camera without using vec3
 * @param input (camera*) the camera
 * @param pos_x (float) position x
 * @param pos_y (float) position y
 * @param pos_z (float) position z
 * @param up_x (float) up x
 * @param up_y (float) up y
 * @param up_z (float) up z
 * @param yaw (float)
 * @param pitch (float)
 * @param roll (float)
 * @param zoom (float)
*/
void camera_initialize_fulls
(
	ts_camera *input,
	float pos_x,
	float pos_y,
	float pos_z,
	float up_x,
	float up_y,
	float up_z,
	float yaw,
	float pitch,
	float roll,
	float zoom
);

/**
 * This one gets the matrix that you need to get a view from the 3d
 * world.
 * @brief Return view matrix using look-at
 * @param input (camera*) the camera
 * @param view (mat4) view matrix
*/
void camera_get_view_matrix(ts_camera *input, mat4 view);

/**
 * Restrict camera movements based on mouse input. This is meant for
 * first person shooter like cameras or free camera modes.
 * @brief Position the camera using mouse like a freecam or FPS cam
 * @param input (camera*) the camera
 * @param x_offset (float)
 * @param y_offset (float)
 * @param constraint (bool) constraints the pitch vertically
 */
void camera_freecam
(
	ts_camera *input,
	float x_offset,
	float y_offset,
	int constraint //0 == false
);

#endif
