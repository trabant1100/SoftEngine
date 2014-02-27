#include "Device.h"

namespace SoftEngine
{
	Device::Device(int width, int height, int bpp)
		: width(width), height(height), bpp(bpp)
	{
		screenRect.x = screenRect.y = 0;
		screenRect.w = width;
		screenRect.h = height;
		SDL_Init(SDL_INIT_VIDEO);
		this->screen = SDL_SetVideoMode(this->width, this->height, this->bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
	}

	Device::~Device(void)
	{
		SDL_Quit();
		this->screen = nullptr;
	}

	void Device::clear(int r, int g, int b, int a)
	{
		SDL_FillRect(screen, &screenRect, SDL_MapRGBA(screen->format, r, g, b, a));
	}

	void Device::flush()
	{
		SDL_Flip(screen);
	}

	void Device::putPixel(int x, int y, COLOR color)
	{
		/*Uint32 pixel = SDL_MapRGBA(screen->format, color.r * 255, color.g * 255, color.b * 255, color.a * 255);
		Uint8 *addr = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

		*addr = pixel;*/
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = rect.h = 1;
		SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	}

	glm::vec2 Device::project(glm::vec3 coord, glm::mat4 transMat)
	{
		//std::cout << "transMat " << glm::to_string(transMat) << std::endl;
		//std::cout << "project " << glm::to_string(coord) << std::endl;
		glm::vec4 point4 = transMat * glm::vec4(coord.xyz(), 1.0f);
		/*point.x /= point.w;
		point.y /= point.w;
		point.z /= point.w;*/
		//std::cout << "projected4 " << glm::to_string(point4) << std::endl;
		
		point4.x /= point4.w;
		point4.y /= point4.w;
		point4.z /= point4.w;
		point4.w = 1.0f;

		glm::vec3 point(point4);
		
		//std::cout << "projected3 " << glm::to_string(point) << std::endl;

		int x = point.x * width + width / 2.0f;
		int y = -point.y * height + height / 2.0f;

		glm::vec2 res(x, y);

		return res;
	}

	void Device::drawPoint(glm::vec2 point)
	{
		//std::cout << "drawPoint " << glm::to_string(point) << std::endl;
		if(point.x >= 0 && point.y >= 0 && point.x < width && point.y < width)
		{
			COLOR c;
			c.r = 1.0f;
			c.g = 1.0f;
			c.b = 0;
			c.a = 1.0f;
			putPixel(point.x, point.y, c);
		}
	}

	void Device::render(Camera camera, const std::vector<Mesh> &meshes)
	{
		glm::mat4 viewMatrix = Camera::lookAtLH(camera.getPosition(), camera.getTarget(), glm::vec3(0, 1, 0));

		glm::mat4 projectionMatrix = Camera::perspectiveFovLH(0.78f, (float)width / (float)height, 0.01f, 1.0f);

		//std::cout << "projectionMatrix " << glm::to_string(projectionMatrix) << std::endl << "--------" << std::endl;;

		for(auto &mesh : meshes)
		{
			glm::quat rotationQuat(mesh.getRotation());
			glm::mat4 worldMatrix = glm::toMat4(rotationQuat) * glm::translate(glm::mat4(1.0f), mesh.getPosition());
			//glm::mat4 transformMatrix = worldMatrix * viewMatrix * projectionMatrix;
			glm::mat4 transformMatrix = projectionMatrix * viewMatrix * worldMatrix;

						
			/*std::cout << "worldMatrix " << glm::to_string(worldMatrix) << std::endl << "--------" << std::endl;
			std::cout << "viewMatrix " << glm::to_string(viewMatrix) << std::endl << "--------" << std::endl;
			std::cout << "projectionMatrix " << glm::to_string(projectionMatrix) << std::endl << "--------" << std::endl;;
			std::cout << "transformMatrix " << glm::to_string(transformMatrix) << std::endl << "--------" << std::endl;*/

			for(auto &vertex : mesh.vertices)
			{
				glm::vec2 point = project(vertex, transformMatrix);
				drawPoint(point);
			}
		}
	}
}