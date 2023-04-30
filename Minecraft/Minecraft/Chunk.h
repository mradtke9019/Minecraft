#pragma once
#include "Block.h"
#include "Noise.h"
#include "Frustum.h"
#include "Volume.h"
#include "Constants.h"
#include "WorldDelta.h"

class Chunk : public ITransformable, public AABB
{
private:
	std::vector<std::vector<std::vector<Block>>> blocks;

public:
	//Returns the closest chunk coordinate to a global coordinate
	static glm::vec3 GlobalToChunkCoordinate(glm::vec3 coord)
	{
		glm::vec3 chunkCoord = coord / (float)Constants::CHUNK_SIZE;
		chunkCoord = glm::floor(chunkCoord);

		return chunkCoord;
	}

	Chunk(glm::vec3 chunkCoordinate,Block block, WorldDelta deltas);

	std::vector<std::vector<std::vector<Block>>>* GetBlockData();

	glm::vec3 GetChunkGlobalCoordinate();

	glm::vec3 GetBlockGlobalCoordinate(glm::vec3 localCoordinate);

	bool ValidBlock(glm::vec3 localCoordinate);

	void Draw();

	//void Draw(Frustum* f);

	bool IsBlockVisible(glm::vec3 localCoordinate);

	/// <summary>
	/// Returns the block at the corresponding local coordinate.
	/// </summary>
	Block* GetBlock(glm::vec3 coordinate);

	std::vector<Block*> GetBlocks();
};

