#pragma once
#define GLM_FORCE_CXX11
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\detail\func_geometric.hpp>
#include <cmath>

namespace SoftEngine
{
	class Camera
	{
	public:
		Camera(void);
		~Camera(void);
		glm::vec3 getPosition() const;
		void setPosition(glm::vec3 position);
		glm::vec3 getTarget() const;
		void setTarget(glm::vec3 target);
		static glm::mat4 lookAtLH(const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up);
		static glm::mat4 perspectiveFovLH(float fieldOfViewY, float aspectRatio, float znearPlane, float zfarPlane);
	private:
		glm::vec3 position;
		glm::vec3 target;
	};
}

