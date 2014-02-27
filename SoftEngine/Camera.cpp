#include "Camera.h"

namespace SoftEngine
{
	Camera::Camera():
		position(0, 0, 0), target(0, 0, 0)
	{

	}


	Camera::~Camera()
	{
	}

	glm::vec3 Camera::getPosition() const
	{
		return position;
	}

	void Camera::setPosition(glm::vec3 position)
	{
		this->position = position;
	}

	glm::vec3 Camera::getTarget() const
	{
		return target;
	}

	void Camera::setTarget(glm::vec3 target)
	{
		this->target = target;
	}

	glm::mat4 Camera::lookAtLH(const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up)
	{
		glm::vec3 zaxis = glm::normalize(target - eye);
		glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));
		glm::vec3 yaxis = glm::cross(zaxis, xaxis);

		glm::mat4 orientation = glm::mat4(
			xaxis.x, yaxis.x, zaxis.x, 0,
			xaxis.y, yaxis.y, zaxis.y, 0,
			xaxis.z, yaxis.z, zaxis.z, 0,
			0, 0, 0, 1);

		glm::mat4 translation = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-eye.x, -eye.y, -eye.z, 1);
		return orientation * translation;
	}

	glm::mat4 Camera::perspectiveFovLH(float fieldOfViewY, float aspectRatio, float znearPlane, float zfarPlane)
	{
		glm::mat4 mat(0.0f);
		float h = 1.0f / tan(fieldOfViewY / 2);
		float w = h / aspectRatio;

		mat[0][0] = w;
		mat[1][1] = h;
		mat[2][2] = zfarPlane / (zfarPlane - znearPlane);
		mat[2][3] = 1.0f;
		mat[3][2] = -znearPlane * zfarPlane / (zfarPlane - znearPlane);
		return mat;
	}
}