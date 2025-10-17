
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

// lookAt_RH
static inline void lookAt(float matrix[4][4], const vec3 *const cam_pos, const vec3 *const cam_target, const vec3 *const cam_up)
{
	matrix[0][2] = -(cam_target->x - cam_pos->x);// forward x
	matrix[1][2] = -(cam_target->y - cam_pos->y);// forward y
	matrix[2][2] = -(cam_target->z - cam_pos->z);// forward z

	// matrix[0][1] is used as a buffer because another value will be written there later
	matrix[0][1] = (1.0 / sqrtf((matrix[0][2] * matrix[0][2]) + (matrix[1][2] * matrix[1][2]) + (matrix[2][2] * matrix[2][2])));
	matrix[0][2] *= matrix[0][1];// normalize forward vector
	matrix[1][2] *= matrix[0][1];
	matrix[2][2] *= matrix[0][1];

	matrix[0][0] = (-matrix[1][2] * cam_up->z) - (cam_up->y * -matrix[2][2]);// right x
	matrix[1][0] = (-matrix[2][2] * cam_up->x) - (cam_up->z * -matrix[0][2]);// right y
	matrix[2][0] = (-matrix[0][2] * cam_up->y) - (cam_up->x * -matrix[1][2]);// right z

	// matrix[0][1] is used as a buffer because another value will be written there later
	matrix[0][1] = (1.0 / sqrtf((matrix[0][0] * matrix[0][0]) + (matrix[1][0] * matrix[1][0]) + (matrix[2][0] * matrix[2][0])));
	matrix[0][0] *= matrix[0][1];// normalize right vector
	matrix[1][0] *= matrix[0][1];
	matrix[2][0] *= matrix[0][1];

	matrix[0][1] = (matrix[1][0] * -matrix[2][2]) - (-matrix[1][2] * matrix[2][0]);// up x
	matrix[1][1] = (matrix[2][0] * -matrix[0][2]) - (-matrix[2][2] * matrix[0][0]);// up y
	matrix[2][1] = (matrix[0][0] * -matrix[1][2]) - (-matrix[0][2] * matrix[1][0]);// up z

	matrix[3][0] = -((matrix[0][0] * cam_pos->x) + (matrix[1][0] * cam_pos->y) + (matrix[2][0] * cam_pos->z));
	matrix[3][1] = -((matrix[0][1] * cam_pos->x) + (matrix[1][1] * cam_pos->y) + (matrix[2][1] * cam_pos->z));
	matrix[3][2] = (-matrix[0][2] * cam_pos->x) + (-matrix[1][2] * cam_pos->y) + (-matrix[2][2] * cam_pos->z);

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
	matrix[3][3] = 1.0f;
}


static inline void rotate(float matrix[4][4], const float radians_angle, const vec3 *const v)
{
	const float cosine_angle = cosf(radians_angle);
	const float sine_angle = sinf(radians_angle);

	// matrix[0,1,2][3] is used as a buffer because another value will be written there later
	matrix[0][3] = (1.0 / sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
	matrix[1][3] = v->y * matrix[0][3];
	matrix[2][3] = v->z * matrix[0][3];
	matrix[0][3] = v->x * matrix[0][3];

	// matrix[0,1,2][2] is used as a buffer because another value will be written there later
	matrix[0][2] = (1.0f - cosine_angle) * matrix[0][3];
	matrix[1][2] = (1.0f - cosine_angle) * matrix[1][3];
	matrix[2][2] = (1.0f - cosine_angle) * matrix[2][3];

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
	matrix[3][3] = 1.0f;
}


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
