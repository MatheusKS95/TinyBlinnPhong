/**
 * Matheus' Simple 3D Math
 * Copyright 2023 Matheus Klein Schaefer
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

/**
 * @file 3d_math.h
 * @brief Math functionalities
 * 
 * Simplistic math functionalities, without using SIMD stuff, for OpenGL
 * and other libraries/APIs
 * 
 * @author
 * - Matheus Klein Schaefer
*/

/*
 * There's more than 50 functions, names should be self-explanatory.
 * Documenting every one of them isn't a priority.
*/

#ifndef THREEDMATH
#define THREEDMATH

#include <inttypes.h>

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef float mat4[4][4];
typedef float quat[4];

/*
 * VEC2 BEGIN
*/

void math_vec2_zero(vec2 vec);

void math_vec2_min(vec2 result, vec2 vec_a, vec2 vec_b);

void math_vec2_max(vec2 result, vec2 vec_a, vec2 vec_b);

void math_vec2_copy(vec2 result, vec2 original);

void math_vec2_add(vec2 result, vec2 vec_a, vec2 vec_b);

void math_vec2_sub(vec2 result, vec2 vec_a, vec2 vec_b);

void math_vec2_scale(vec2 result, vec2 vec, float scalar);

float math_vec2_dot(vec2 vec_a, vec2 vec_b);

float math_vec2_cross(vec2 vec_a, vec2 vec_b);

float math_vec2_len(vec2 vec);

void math_vec2_normalize(vec2 result, vec2 vec);

// VEC2 END

/*
 * VEC3 BEGIN
*/

void math_vec3_zero(vec3 vec);

void math_vec3_min(vec3 result, vec3 vec_a, vec3 vec_b);

void math_vec3_max(vec3 result, vec3 vec_a, vec3 vec_b);

void math_vec3_copy(vec3 result, vec3 original);

void math_vec3_negate(vec3 result, vec3 vec);

void math_vec3_add(vec3 result, vec3 vec_a, vec3 vec_b);

void math_vec3_sub(vec3 result, vec3 vec_a, vec3 vec_b);

void math_vec3_div(vec3 result, vec3 vec, float div);

void math_vec3_scale(vec3 result, vec3 vec, float scalar);

float math_vec3_dot(vec3 vec_a, vec3 vec_b);

void math_vec3_cross(vec3 result, vec3 vec_a, vec3 vec_b);

float math_vec3_len(vec3 vec);

void math_vec3_normalize(vec3 vec);

void math_vec3_normalize_to(vec3 result, vec3 vec);

// VEC3 END

/*
 * VEC4 BEGIN
*/

void math_vec4_zero(vec4 vec);

void math_vec4_min(vec4 result, vec4 vec_a, vec4 vec_b);

void math_vec4_max(vec4 result, vec4 vec_a, vec4 vec_b);

void math_vec4_copy(vec4 result, vec4 original);

void math_vec4_add(vec4 result, vec4 vec_a, vec4 vec_b);

void math_vec4_sub(vec4 result, vec4 vec_a, vec4 vec_b);

void math_vec4_div(vec4 result, vec4 vec, float div);

void math_vec4_scale(vec4 result, vec4 vec, float scalar);

float math_vec4_dot(vec4 vec_a, vec4 vec_b);

float math_vec4_len(vec4 vec);

void math_vec4_normalize(vec4 vec);

// VEC4 END

/*
 * MAT4 BEGIN
*/

void math_mat4_zero(mat4 mat);

void math_mat4_identity(mat4 mat);

void math_mat4_add(mat4 result, mat4 mat_a, mat4 mat_b);

void math_mat4_sub(mat4 result, mat4 mat_a, mat4 mat_b);

void math_mat4_scale(mat4 result, mat4 mat, float s);

void math_mat4_row(vec4 result, mat4 mat, uint8_t index);

void math_mat4_col(vec4 result, mat4 mat, uint8_t index);

void math_mat4_scale_xyz(mat4 mat, float scalar); //do the same as math_mat4_scale

void math_mat4_mul(mat4 result, mat4 mat_a, mat4 mat_b);

void math_mat4_copy(mat4 result, mat4 original);

void math_mat4_translate(mat4 mat, vec3 vec);

void math_mat4_rotate_axis(mat4 mat, vec3 axis, float angle);

void math_mat4_rotate_x(mat4 result, mat4 mat, float angle);

void math_mat4_rotate_y(mat4 result, mat4 mat, float angle);

void math_mat4_rotate_z(mat4 result, mat4 mat, float angle);

// MAT4 END

/*
 * QUAT BEGIN
*/

void math_quat_zero(quat qt);

void math_quat_identity(quat qt);

void math_quat_add(quat result, quat qt_a, quat qt_b);

void math_quat_sub(quat result, quat qt_a, quat qt_b);

void math_quat_scale(quat result, quat qt, float scalar);

void math_quat_norm(quat result, quat qt);

//QUAT END

/**
 * CAM BEGIN
*/

void math_lookat(mat4 result, vec3 position, vec3 target, vec3 up);

void math_perspective(mat4 result, float fov, float aspect, float near, float far);

//CAM END

/*
 * OTHER BEGIN
*/

float deg_to_rad(float deg);

float rad_to_deg(float rad);

float math_lerp(float v0, float v1, float t);

//OTHER END

#endif
