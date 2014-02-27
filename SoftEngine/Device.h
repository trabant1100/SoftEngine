#pragma once

#define GLM_FORCE_CXX11
#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <math.h>
#include <vector>
#include <SDL\SDL.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\mat3x3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

#include "Camera.h"
#include "Mesh.h"

namespace SoftEngine
{
	typedef struct color_t
	{
		float r, g, b, a;
	} COLOR;

	class Device
	{
	public:
		Device(int width, int height, int bpp);
		~Device(void);
		void clear(int r, int g, int b, int a);
		void flush();
		void putPixel(int x, int y, COLOR color);
		glm::vec2 project(glm::vec3 coord, glm::mat4 transMat);
		void drawPoint(glm::vec2 point);
		void render(Camera camera, const std::vector<Mesh> &meshes);
	private:
		int width, height, bpp;
		SDL_Rect screenRect;
		SDL_Surface *screen;
	};
}
