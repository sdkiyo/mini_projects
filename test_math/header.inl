
static inline float radians(const float x)
{
	return x * PI / 180;
}


static inline void normalize_xyz(float *const x, float *const y, float *const z)
{
	const float w = (1.0 / sqrtf((*x * *x) + (*y * *y) + (*z * *z)));
	*x *= w;
	*y *= w;
	*z *= w;
}


/* [in]   pCam_pos	camera position in world
 * [in]   pCam_target	point position in world, where camera should look
 * [in]   pCam_up	vector pointing up for camera
 * [out]  matrix	output view matrix
*/
static inline void lookAt_RH(float matrix[4][4], const vec3 *const pCam_pos, const vec3 *const pCam_target, const vec3 *const pCam_up)
{
	matrix[0][2] = -(pCam_target->x - pCam_pos->x);// forward.x
	matrix[1][2] = -(pCam_target->y - pCam_pos->y);// forward.y
	matrix[2][2] = -(pCam_target->z - pCam_pos->z);// forward.z (минус потому что RH)

	// matrix[0][1] is used as a buffer because another value will be written there later
	matrix[0][1] = (1.0 / sqrtf((matrix[0][2] * matrix[0][2]) + (matrix[1][2] * matrix[1][2]) + (matrix[2][2] * matrix[2][2])));
	matrix[0][2] *= matrix[0][1];
	matrix[1][2] *= matrix[0][1];// normalize forward
	matrix[2][2] *= matrix[0][1];

	// right = cross_product(forward, cam_up)
	matrix[0][0] = (-matrix[1][2] * pCam_up->z) - (pCam_up->y * -matrix[2][2]);// right.x
	matrix[1][0] = (-matrix[2][2] * pCam_up->x) - (pCam_up->z * -matrix[0][2]);// right.y
	matrix[2][0] = (-matrix[0][2] * pCam_up->y) - (pCam_up->x * -matrix[1][2]);// right.z

	// matrix[0][1] is used as a buffer because another value will be written there later
	matrix[0][1] = (1.0 / sqrtf((matrix[0][0] * matrix[0][0]) + (matrix[1][0] * matrix[1][0]) + (matrix[2][0] * matrix[2][0])));
	matrix[0][0] *= matrix[0][1];
	matrix[1][0] *= matrix[0][1];// normalize right
	matrix[2][0] *= matrix[0][1];

	// up = cross_product(right, forward)
	matrix[0][1] = (matrix[1][0] * -matrix[2][2]) - (-matrix[1][2] * matrix[2][0]);// up.x = (right.y * forward.z) - (forward.y * right.z)
	matrix[1][1] = (matrix[2][0] * -matrix[0][2]) - (-matrix[2][2] * matrix[0][0]);// up.y = (right.z * forward.x) - (forward.z * right.x)
	matrix[2][1] = (matrix[0][0] * -matrix[1][2]) - (-matrix[0][2] * matrix[1][0]);// up.z = (right.x * forward.y) - (forward.x * right.y)

	matrix[3][0] = -((matrix[0][0] * pCam_pos->x) + (matrix[1][0] * pCam_pos->y) + (matrix[2][0] * pCam_pos->z));// dot_product(right, cam_pos)
	matrix[3][1] = -((matrix[0][1] * pCam_pos->x) + (matrix[1][1] * pCam_pos->y) + (matrix[2][1] * pCam_pos->z));// dot_product(up, cam_pos)
	matrix[3][2] = (-matrix[0][2] * pCam_pos->x) + (-matrix[1][2] * pCam_pos->y) + (-matrix[2][2] * pCam_pos->z);// dot_product(forward, cam_pos)

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
	matrix[3][3] = 1.0f;// idk.
}



/* [in]   radians_angle
 * [in]   pAxis		vector indicating the axis of rotation
 * [out]  matrix	output rotate matrix
*/
static inline void rotate(float matrix[4][4], const float radians_angle, const vec3 *const pAxis)
{
	const float cosine_angle = cosf(radians_angle);
	const float sine_angle = sinf(radians_angle);

	// matrix[0,1,2][3] is used as a buffer because another value will be written there later
	matrix[2][3] = (1.0 / sqrtf((pAxis->x * pAxis->x) + (pAxis->y * pAxis->y) + (pAxis->z * pAxis->z)));
	matrix[0][3] = pAxis->x * matrix[2][3];// axis.x
	matrix[1][3] = pAxis->y * matrix[2][3];// axis.y
	matrix[2][3] = pAxis->z * matrix[2][3];// axis.z

	// matrix[0,1,2][2] is used as a buffer because another value will be written there later
	matrix[0][2] = (1.0f - cosine_angle) * matrix[0][3];// temp.x
	matrix[1][2] = (1.0f - cosine_angle) * matrix[1][3];// temp.y
	matrix[2][2] = (1.0f - cosine_angle) * matrix[2][3];// temp.y

	matrix[0][0] = cosine_angle + matrix[0][2] * matrix[0][3];
	matrix[0][1] = matrix[0][2] * matrix[1][3] + sine_angle * matrix[2][3];
	matrix[0][2] = matrix[0][2] * matrix[2][3] - sine_angle * matrix[1][3];

	matrix[1][0] = matrix[1][2] * matrix[0][3] - sine_angle * matrix[2][3];
	matrix[1][1] = cosine_angle + matrix[1][2] * matrix[1][3];
	matrix[1][2] = matrix[1][2] * matrix[2][3] + sine_angle * matrix[0][3];

	matrix[2][0] = matrix[2][2] * matrix[0][3] + sine_angle * matrix[1][3];
	matrix[2][1] = matrix[2][2] * matrix[1][3] - sine_angle * matrix[0][3];
	matrix[2][2] = cosine_angle + matrix[2][2] * matrix[2][3];

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;

	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;// idk.
}


// я хз как это работает, просто скопировал отсюда https://github.com/recp/cglm/blob/master/include/cglm/clipspace/persp_rh_no.h#L102
static inline void perspective(float matrix[4][4], const float fov, const float aspect, const float nearZ, const float farZ)
{
	const float f = 1.0f / tanf(radians(fov) * 0.5f);
	const float fn = 1.0f / (nearZ - farZ);

	matrix[0][0] = f / aspect;
	matrix[1][1] = -f;
	matrix[2][2] = (nearZ + farZ) * fn;
	matrix[2][3] =-1.0f;
	matrix[3][2] = 2.0f * nearZ * farZ * fn;

	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;

	matrix[1][0] = 0.0;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;

	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;

	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][3] = 0.0;
}
