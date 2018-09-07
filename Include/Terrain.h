#ifndef TERRAIN_H
#define TERRAIN_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <iostream>

using namespace std;

class Terrain {
private:
	float SIZE = 800;
	int VERTEX_COUNT = 128;
	int w;	//width
	int l;	//height
	float ** heights;
	glm::vec3 ** normals;	//stores the normals
	bool computedNormals;	//whether normals is up-to date

public:
	Terrain(int w, int l) {
		this->w = w;
		this->l = l;

		heights = new float*[l];

		for (int i = 0; i < l; i++) {
			heights[i] = new float[w];
		}

		normals = new glm::vec3*[l];
		for (int i = 0; i < l; i++) {
			normals[i] = new glm::vec3[w];
		}

		computedNormals = false;
	}

	int width() {
		return w;
	}

	int length() {
		return l;
	}

	void computeNormals() {

		if (computedNormals) {
			return;
		}

		for (int z = 0;z < l; z++) {	//모든 6개의 삼각형을 border로 갖고 있는 점의 normal 계산
			for (int x = 0; x < w; x++) {
				glm::vec3 sum(0.0f);
				glm::vec3 right(0.0f);
				glm::vec3 left(0.0f);
				glm::vec3 up(0.0f);
				glm::vec3 down(0.0f);
				glm::vec3 diagR(0.0f);
				glm::vec3 diagL(0.0f);
				glm::vec3 face1(0.0f);
				glm::vec3 face2(0.0f);
				glm::vec3 face3(0.0f);
				glm::vec3 face4(0.0f);
				glm::vec3 face5(0.0f);
				glm::vec3 face6(0.0f);
				if (x < w - 1) {
					right = glm::vec3(1.0f, heights[z][x + 1] - heights[z][x], 0.0f);
				}
				if (x > 0) {
					left = glm::vec3(-1.0f, heights[z][x - 1] - heights[z][x], 0.0f);
				}
				if (z > 0) {
					up = glm::vec3(0.0f, heights[z - 1][x] - heights[z][x], -1.0f);
				}
				if (z < l - 1) {
					down = glm::vec3(0.0f, heights[z + 1][x] - heights[z][x], 1.0f);
				}
				if (z > 0 && x < w-1) {
					diagR = glm::vec3(1.0f, heights[z - 1][x + 1] - heights[z][x], -1.0f);
				}
				if (z < l-1 && x > 0) {
					diagL = glm::vec3(-1.0f, heights[z + 1][x - 1] - heights[z][x], 1.0f);
				}

				face1 = cross(left, diagL);
				face2 = cross(diagL, down);
				face3 = cross(down, right);
				face4 = cross(right, diagR);
				face5 = cross(diagR, up);
				face6 = cross(up, left);

				sum = face1 + face2 + face3 + face4 + face5 + face6;
				normals[z][x] = normalize(sum);
			}
		}
	}

	glm::vec3 getNormal(int x, int z) {
		if (!computedNormals) {
			computeNormals();
		}
		return normals[z][x];
	}

	void setHeight(int x, int z, float y)
	{
		heights[z][x] = y;
		computedNormals = false;
	}

	float getHeight(int x, int z) {
		return heights[z][x];
	}

	~Terrain() {
		for (int i = 0; i < l; i++) {
			delete[] heights[i];
		}
		delete[] heights;

		for (int i = 0; i < l; i++) {
			delete[] normals[i];
		}
		delete[] normals;
	}


};

// loads heightmap
// heights of the terrain range from -height/2 to height/2
Terrain * loadTerrain(const char* filename, float height, int gridZNum, int gridXNum) {
	// we need to do sampling. gridZNum, gridXNum is currently 7, 7
	//read the stbi_load function to learn how to read image files in to get their pixels
	int imageWidth, imageHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load(filename, &imageWidth, &imageHeight, &nrChannels, 4);	//4 since the heightmap's a png file.
	if (!data) {
		cout << "Cannot load data" << endl;
		return NULL;
	}
	Terrain* t = new Terrain(gridXNum, gridZNum);
	for (int z = 0; z < gridZNum; z++) {
		for (int x = 0; x < gridXNum; x++) {
			unsigned char color = data[4 * ((z*(imageHeight / gridZNum)) * imageWidth + (x*(imageWidth / gridXNum)))];	//Changed to 4 cause stbi_load's last parameter is 4.
			float h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, z, h);
		}
	}
	stbi_image_free(data);
	t->computeNormals();
	return t;
}

#endif

