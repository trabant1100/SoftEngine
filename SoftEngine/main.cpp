#include "Device.h"
#include <stdio.h>
#include <iostream>


#include <SDL.h>
#include <emscripten.h>

using namespace SoftEngine;

SDL_Surface *screen = nullptr;
Device *device = nullptr;
Mesh mesh = Mesh("Cube", 8);
Camera camera;
std::vector<Mesh> meshes;

int counter = 0;
int MAX = 2;

void render();
void init();

int main()
{
	//SDL_Init(SDL_INIT_VIDEO);
	//screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	init();
	render();
	emscripten_set_main_loop(render, 0, 0);
	return 0;
}

void init()
{
	device = new Device(160, 100, 32);

	mesh.vertices[0] = glm::vec3(-1.0f, 1.0f, 1.0f);
    mesh.vertices[1] = glm::vec3(1, 1.0f, 1.0f);
    mesh.vertices[2] = glm::vec3(-1.0f, -1.0f, 1.0f);
    mesh.vertices[3] = glm::vec3(-1.0f, -1.0f, -1.0f);
    mesh.vertices[4] = glm::vec3(-1.0f, 1.0f, -1.0f);
    mesh.vertices[5] = glm::vec3(1.0f, 1.0f, -1.0f);
    mesh.vertices[6] = glm::vec3(1.0f, -1.0f, 1.0f);
    mesh.vertices[7] = glm::vec3(1.0f, -1.0f, -1.0f);
	meshes.push_back(mesh);

	camera.setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
}

void render()
{
	/*if(counter >= MAX)
		return;*/
	device->clear(0, 0, 0, 255);
	glm::vec3 rotation = meshes[0].getRotation();
	rotation.x += 0.01f;
	rotation.y += 0.01f;
	meshes[0].setRotation(rotation);
	
	device->render(camera, meshes);

	device->flush();

	counter ++;
}