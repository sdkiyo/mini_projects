
static inline vec3 cross(const vec3 *const a, const vec3 *const b)
{
	return (vec3) {
		(a->y * b->z) - (b->y * a->z),
		(a->z * b->x) - (b->z * a->x),
		(a->x * b->y) - (b->x * a->y)
	};
}

static inline float dot(const vec3 *const a, const vec3 *const b)
{
	vec3 tmp;
	tmp.x = a->x * b->x;
	tmp.y = a->y * b->y;
	tmp.z = a->z * b->z;
	return tmp.x + tmp.y + tmp.z;
}

static inline vec3 subtraction_vec3(const vec3 *const a, const vec3 *const b)
{
	return (vec3) {
		a->x - b->x,
		a->y - b->y,
		a->z - b->z
	};
}

static inline vec3 normalize_vec3(const vec3 v)
{
	const float w = (1.0 / sqrtf(dot(&v, &v)));
	return (vec3) {
		v.x * w,
		v.y * w,
		v.z * w
	};
}

// lookAt_RH
static inline void lookAt_old(float matrix[4][4], const vec3 *const cam_pos, const vec3 *const cam_target, const vec3 *const cam_up)
{
	const vec3 forward = normalize_vec3(subtraction_vec3(cam_target, cam_pos));
	const vec3 right = normalize_vec3(cross(&forward, cam_up));
	const vec3 up = cross(&right, &forward);

	matrix[0][0] = right.x;
	matrix[0][1] = up.x;
	matrix[0][2] = -forward.x;
	matrix[0][3] = 0.0f;

	matrix[1][0] = right.y;
	matrix[1][1] = up.y;
	matrix[1][2] = -forward.y;
	matrix[1][3] = 0.0f;

	matrix[2][0] = right.z;
	matrix[2][1] = up.z;
	matrix[2][2] = -forward.z;
	matrix[2][3] = 0.0f;

	matrix[3][0] = -dot(&right, cam_pos);
	matrix[3][1] = -dot(&up, cam_pos);
	matrix[3][2] = dot(&forward, cam_pos);
	matrix[3][3] = 1.0f;
}

static inline void rotate_old(float matrix[4][4], const float radians_angle, const vec3 *const v)
{
	const float cosine_angle = cosf(radians_angle);
	const float sine_angle = sinf(radians_angle);

	const vec3 axis = normalize_vec3(*v);
	const vec3 temp = {
		(1.0f - cosine_angle) * axis.x,
		(1.0f - cosine_angle) * axis.y,
		(1.0f - cosine_angle) * axis.z
	};

	matrix[0][0] = cosine_angle + temp.x * axis.x;
	matrix[0][1] = temp.x * axis.y + sine_angle * axis.z;
	matrix[0][2] = temp.x * axis.z - sine_angle * axis.y;
	matrix[0][3] = 0.0f;

	matrix[1][0] = temp.y * axis.x - sine_angle * axis.z;
	matrix[1][1] = cosine_angle + temp.y * axis.y;
	matrix[1][2] = temp.y * axis.z + sine_angle * axis.x;
	matrix[1][3] = 0.0f;

	matrix[2][0] = temp.z * axis.x + sine_angle * axis.y;
	matrix[2][1] = temp.z * axis.y - sine_angle * axis.x;
	matrix[2][2] = cosine_angle + temp.z * axis.z;
	matrix[2][3] = 0.0f;

	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;
}

static inline void perspective_old(float matrix[4][4], const float fov, const float aspect, const float nearZ, const float farZ)
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
