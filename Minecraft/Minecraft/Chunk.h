#pragma once
#include "Block.h"
#include "Noise.h"

class Chunk : public ITransformable
{
private:
	std::vector<std::vector<std::vector<Block>>> blocks;

public:
	Chunk(glm::vec3 chunkCoordinate,Block block);

	glm::vec3 GetBlockGlobalCoordinate(glm::vec3 localCoordinate);

	bool ValidBlock(glm::vec3 localCoordinate);

	void Draw();

	bool IsBlockVisible(glm::vec3 localCoordinate);

	std::vector<Block*> GetBlocks();
};

