#include <math.h>
#include <string.h>


typedef struct vec2 {
	float x;
	float y;
} vec2;

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

#define PI 3.141592653589793


static inline float radians(const float x);

static inline void normalize_xyz(float *const x, float *const y, float *const z);

// lookAt_RH
static inline void lookAt(float matrix[4][4], const vec3 *const cam_pos, const vec3 *const cam_target, const vec3 *const cam_up);

static inline void rotate(float matrix[4][4], const float radians_angle, const vec3 *const v);

static inline void perspective(float matrix[4][4], const float fov, const float aspect, const float nearZ, const float farZ);


#include "header.inl"
