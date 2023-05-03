#pragma once
class Player;
#include "Chunk.h"
#include "WorldDelta.h"
#include "Player.h"
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtx/vector_angle.hpp>

class World {
private:
	WorldDelta worldDelta;
	std::vector<Chunk> chunks;

public:
	static glm::vec3 GetClosestBlockWorldPosition(glm::vec3 coord)
	{
		return glm::vec3(glm::round(coord.x), glm::round(coord.y), glm::round(coord.z));
	}

	WorldDelta* GetWorldDelta();

	/// <summary>
	/// Returns the chunks of the world
	/// </summary>
	std::vector<Chunk>* GetChunks();

	/// <summary>
	/// Returns the chunk with the given chunk coordinate
	/// </summary>
	Chunk* GetChunk(glm::vec3 coord);

	/// <summary>
	/// Returns the block with the given global coordinate
	/// </summary>
	Block* GetBlockByGlobalCoordinate(glm::vec3 globalBlockCoordinate);

	/// <summary>
	/// Returns the block with the given chunk coordinate and local block coordinate
	/// </summary>
	Block* GetBlock(glm::vec3 chunkCoord, glm::vec3 blockCoord);

	/// <summary>
	/// Converts a global coordinate to the corresponding chunk coordinate
	/// </summary>
	glm::vec3 GlobalToChunkCoordinate(glm::vec3 globalCoord, bool t = true);

	/// <summary>
	/// Updates the world based on the players current position
	/// </summary>
	void UpdateByPlayerPosition(Player* player, Block* defaultBlock, bool isGlobal);

	void Draw();
};