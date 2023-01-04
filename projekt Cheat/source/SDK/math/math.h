#pragma once
#include "matrix.h"
#include "qangle.h"
#include "vec3.h"
#include <corecrt_math_defines.h>

#define PI_F ( ( float )( M_PI ) ) 
#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)

namespace math {
	void vector_transform( const c_vec3& in1, const matrix_t& in2, c_vec3& out );
	float normalize_yaw( float yaw );
	float angle_diff( float dest_angle, float src_angle );
	[[nodiscard]] qangle_t calc_angle( const c_vec3& src, const c_vec3& dst );
	void vector_angles( const c_vec3& forward, qangle_t& view );
	void vector_angles( const c_vec3& forward, const c_vec3& up, qangle_t& angles );
	void sin_cos( float radians, float* sine, float* cosine );
	void angle_vectors( const qangle_t& angles, c_vec3* forward, c_vec3* right = nullptr, c_vec3* up = nullptr );
	qangle_t angle_normalize( qangle_t& angle );
	bool screen_transform(const c_vec3& in, c_vec3& out, v_matrix WorldToScreenMatrix);
}