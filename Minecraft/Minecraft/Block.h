#pragma once
#include "Model.h"
#include "ITransformable.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Block: public ITransformable
{
private:
	Model* model;
	bool visible;
	Texture* texture;
	Shader* shader;
	//Store the cube data here.
	//Layout: Vertex Positions, Texture Coordinates, Normal Vector
	float* cubeData;

	unsigned int CubeVAO, CubeVBO;


public:
	Block(Shader* s, Texture* tex);

	void SetVisibility(bool v);
	
	bool IsVisible();

	void Draw();

	void ChangeTexture(Texture* newTexture);
};

