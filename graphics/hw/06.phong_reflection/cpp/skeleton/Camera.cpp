#include "Camera.h"

// TODO: fill up the following function properly 
void Camera::set_rotation(const glm::quat& _q)
{
	front_dir_ = glm::normalize(_q * glm::vec3(0, 0, -1));
	up_dir_ = glm::normalize(_q * glm::vec3(0, 1, 0));
	right_dir_ = glm::normalize(_q * glm::vec3(1, 0, 0));
}

// TODO: re-write the following function properly 
const glm::quat Camera::get_rotation() const
{
	glm::mat3 rot(
		right_dir_,
		up_dir_,
		-front_dir_
	);

	return glm::quat_cast(rot);
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::quat& _q, const glm::vec3& _t)
{
	position_ = _t;

	front_dir_ = glm::normalize(_q * glm::vec3(0, 0, -1));
	up_dir_ = glm::normalize(_q * glm::vec3(0, 1, 0));
	right_dir_ = glm::normalize(_q * glm::vec3(1, 0, 0));
}

// TODO: fill up the following function properly 
void Camera::get_pose(glm::quat& _q, glm::vec3& _t) const
{
	glm::mat3 rot(
		right_dir_,
		up_dir_,
		-front_dir_
	);

	_q = glm::quat_cast(rot);
	_t = position_;
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_pose() const
{
	glm::mat3 rot(
		right_dir_,
		up_dir_,
		-front_dir_
	);

	glm::mat4 mat = glm::mat4(1.0f);
	mat[0] = glm::vec4(rot[0], 0.0f);
	mat[1] = glm::vec4(rot[1], 0.0f);
	mat[2] = glm::vec4(rot[2], 0.0f);
	mat[3] = glm::vec4(position_, 1.0f);

	return  mat;
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::mat4& _frame)
{
	// +x_cam: right direction of the camera    (it should be a unit vector whose length is 1)
	// right_dir_ = ..... ; // +xbhj7ttwqq
	right_dir_ = glm::normalize(_frame[0]);
	// +y_cam: up direction of the camera       (it should be a unit vector whose length is 1)   
	// up_dir_    = ..... ;    // +y
	up_dir_ = glm::normalize(_frame[1]);
	// -z_cam: front direction of the camera    (it should be a unit vector whose length is 1)
	// front_dir_ = ..... ;    // -z
	front_dir_ = glm::normalize(_frame[2]);
	// pos_cam: position of the camera
	// position_  = ..... ;    // pos
	position_ = glm::vec3(_frame[3]);
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::vec3& _pos, const glm::vec3& _at, const glm::vec3& _up_dir)
{
	// up_dir_    = ..... ;
	// front_dir_ = ..... ;    // -z_cam direction
	// right_dir_ = ..... ;    // +x_cam direction
	// up_dir_    = ..... ;    // +y_cam direction

	front_dir_ = glm::normalize(_at - _pos);
	right_dir_ = glm::normalize(glm::cross(front_dir_, _up_dir));
	up_dir_ = glm::normalize(glm::cross(right_dir_, front_dir_));

	position_ = _pos;
	// position_  = ..... ;      // pos
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_view_matrix() const
{
	return glm::lookAt(
		position_,
		position_ + front_dir_,
		up_dir_
	);
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_projection_matrix() const
{
	// TODO: Considering the followings,
	//       You must return a proper projection matrix
	//       i) camera mode: it can be either kOrtho or kPerspective
	//       ii) zoom-in/-out: if the camera mode is kOrtho, 
	//                         utilize ortho_scale_ for zoom-in/-out
	//                         if the camera mode is kPerspective,
	//                         utilize fovy_ for zoom-in/-out
	//       iii) aspect ratio: utilize aspect_ in the both camera modes
	//       iv) near/far clipping planes: utilize near_, far_

	if (mode_ == kPerspective)
	{
		// fovy는 degree이므로 glm::radians()로 변환 필요
		return glm::perspective(
			glm::radians(fovy_),
			aspect_,
			near_,
			far_
		);
	}
	else // kOrtho
	{
		// ortho_scale_을 기준으로 좌/우/상/하 계산
		float half_w = ortho_scale_ * aspect_ * 0.5f;
		float half_h = ortho_scale_ * 0.5f;

		return glm::ortho(
			-half_w, +half_w,    // left, right
			-half_h, +half_h,    // bottom, top
			near_,
			far_
		);
	}
}

// TODO: fill up the following functions properly 
void Camera::move_forward(float delta)
{
	position_ += front_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_backward(float delta)
{
	position_ -= front_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_left(float delta)
{
	position_ -= right_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_right(float delta)
{
	position_ += right_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_up(float delta)
{
	position_ += up_dir_ * delta;
}

// TODO: fill up the following functions properly 
void Camera::move_down(float delta)
{
	position_ -= up_dir_ * delta;
}
