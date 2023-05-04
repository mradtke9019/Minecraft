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
	Carpet,
	GrassTop,
	Grass2,
	Grass3,
	Grass4
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
	const int NumVerticesPerFace = 6;
	unsigned int CubeVAO, CubeVBO;
	BlockType BlockTexture;
	std::map<BlockType, Texture*>* TextureMap;

public:
	Block(Shader* s, std::map<BlockType, Texture*>* texMap);

	void SetVisibility(bool v);

	bool IsVisible();

	void Draw();

	BlockType GetBlockType();

	void SetBlockType(BlockType bType);

	void SetTextureTop(BlockType blockTexture);
	void SetTextureBottom(BlockType blockTexture);
	void SetTextureLeft(BlockType blockTexture);
	void SetTextureRight(BlockType blockTexture);
	void SetTextureFront(BlockType blockTexture);
	void SetTextureBack(BlockType blockTexture);

	void DrawGrassTexture();
	void DrawStoneTexture();
	void DrawGoldTexture();
	void DrawCoalTexture();
	void DrawDiamondTexture();
	void DrawCarpetTexture();



};