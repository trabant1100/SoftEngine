#pragma once
#define GLM_FORCE_CXX11

#include <glm\vec3.hpp>

#include <string>
#include <vector>
#include <iostream>

namespace SoftEngine
{
	class Mesh
	{
	public:
		Mesh(std::string name, int verticesCount);
		~Mesh(void);
		std::vector<glm::vec3> vertices;
		std::string getName() const;
		glm::vec3 getPosition() const;
		void setPosition(glm::vec3 position);
		glm::vec3 getRotation() const;
		void setRotation(glm::vec3 rotation);
		friend std::ostream& operator<<(std::ostream& stream, const Mesh& mesh);

	private:
		std::string name;
		glm::vec3 position;
		glm::vec3 rotation;
	};
}
