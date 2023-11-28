/**
 * Matheus' Tiny Blinn Phong
 * Copyright 2023 Matheus Klein Schaefer
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

/**
 * @file camera.c
 * @brief camera.h implementation
 * 
 * @author
 * - Matheus Klein Schaefer (email here)
*/

#include <math.h>
#include "camera.h"

static void camera_update(ts_camera *input)
{
	vec3 front;

	front[0] = cos(deg_to_rad(input->yaw)) * cos(deg_to_rad(input->pitch));
	front[1] = sin(deg_to_rad(input->pitch));
	front[2] = sin(deg_to_rad(input->yaw)) * cos(deg_to_rad(input->pitch));
	math_vec3_normalize_to(input->front, front);

	vec3 crossprod;
	math_vec3_cross(crossprod, input->front, input->world_up);
	math_vec3_normalize_to(input->right, crossprod);

	math_vec3_cross(crossprod, input->right, input->front);
	math_vec3_normalize_to(input->up, crossprod);
}

void camera_initialize(ts_camera *input, vec3 position)
{
	math_vec3_copy(input->position, position);
	math_vec3_copy(input->up, (vec3){0.0f, 1.0f, 0.0f});
	math_vec3_copy(input->world_up, input->up);
	input->yaw = YAW;
	input->pitch = PITCH;
	input->roll = ROLL;
	input->zoom = ZOOM;

	camera_update(input);
}

void camera_initialize_full
(
	ts_camera *input,
	vec3 position,
	vec3 up,
	float yaw,
	float pitch,
	float roll,
	float zoom
)
{
	math_vec3_copy(input->position, position);
	math_vec3_copy(input->up, up);
	math_vec3_copy(input->world_up, input->up);
	input->yaw = yaw;
	input->pitch = pitch;
	input->roll = roll;
	input->zoom = zoom;

	camera_update(input);
}

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
)
{
	vec3 position;
	position[0] = pos_x;
	position[1] = pos_y;
	position[2] = pos_z;
	math_vec3_copy(input->position, position);

	vec3 up;
	up[0] = up_x;
	up[1] = up_y;
	up[2] = up_z;
	math_vec3_copy(input->up, up);
	math_vec3_copy(input->world_up, input->up);

	input->yaw = yaw;
	input->pitch = pitch;
	input->roll = roll;
	input->zoom = zoom;

	camera_update(input);
}

void camera_get_view_matrix(ts_camera *input, mat4 view)
{
	vec3 sum;
	math_vec3_add(sum, input->position, input->front);
	math_lookat(view, input->position, sum, input->up);
}

void camera_freecam
(
	ts_camera *input,
	float x_offset,
	float y_offset,
	int constraint
)
{
	x_offset *= SENSITIVITY;
	y_offset *= SENSITIVITY;

	input->yaw += x_offset;
	input->pitch += y_offset;

	if(constraint == 1)
	{
		if(input->pitch > 89.0f)
			input->pitch = 89.0f;
		if(input->pitch < -89.0f)
			input->pitch = -89.0f;
	}

	camera_update(input);
}
