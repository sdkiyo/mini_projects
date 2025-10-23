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


/* [in]   pCam_pos	camera position in world
 * [in]   pCam_target	point position in world, where camera should look
 * [in]   pCam_up	vector pointing up for camera
 * [out]  matrix	output view matrix
*/
static inline void lookAt_RH(float matrix[4][4], const vec3 *const pCam_pos, const vec3 *const pCam_target, const vec3 *const pCam_up);


/* [in]   radians_angle (думаю и так понятно)
 * [in]   pAxis		vector indicating the axis of rotation
 * [out]  matrix	output rotate matrix
*/
static inline void rotate(float matrix[4][4], const float radians_angle, const vec3 *const pAxis);


static inline void perspective(float matrix[4][4], const float fov, const float aspect, const float nearZ, const float farZ);


#include "header.inl"
