#include "Mesh.h"

#define GLM_FORCE_RADIANS
#include <glm/ext.hpp>

namespace SoftEngine
{
	Mesh::Mesh(std::string name, int verticesCount)
	{
		this->name = name;
		vertices = std::vector<glm::vec3>(verticesCount);
	}


	Mesh::~Mesh(void)
	{
		
	}

	std::string Mesh::getName() const
	{
		return name;
	}

	glm::vec3 Mesh::getPosition() const
	{
		return position;
	}

	void Mesh::setPosition(glm::vec3 position)
	{
		this->position = position;
	}

	glm::vec3 Mesh::getRotation() const
	{
		return rotation;
	}

	void Mesh::setRotation(glm::vec3 rotation)
	{
		this->rotation = rotation;
	}

	std::ostream& operator<<(std::ostream &stream, const Mesh &mesh)
	{
		stream << mesh.name << ", position=" << glm::to_string(mesh.position);
		stream << ", vertices=";

		for(size_t i = 0; i < mesh.vertices.size(); i ++)
		{
			stream << glm::to_string(mesh.vertices[i]) << ", ";
		}

		return stream;
	}
}
