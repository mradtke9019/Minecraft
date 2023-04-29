#pragma once
#include "Model.h"
#include "ITransformable.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

enum BlockType
{
	None,
	Grass,
	Stone,
	Gold,
	Coal,
	Diamond,
	Carpet
};

class Block : public ITransformable
{
private:
	Model* model;
	bool visible;
	std::vector<Texture*> Textures;
	Shader* shader;
	//Store the cube data here.
	//Layout: Vertex Positions, Texture Coordinates, Normal Vector
	float* cubeData;
	const int NumFaces = 6;
	unsigned int CubeVAO, CubeVBO;


public:
	Block(Shader* s, std::vector<Texture*> tex);

	void SetVisibility(bool v);

	bool IsVisible();

	void Draw();

};