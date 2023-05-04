#pragma once
#include "Delta.h"
#include <vector>

/// Data structure to hold the entire changes of the whole world generated.
class WorldDelta
{
private:
	std::vector<Delta> deltas;

public:
	WorldDelta();

	// Return a delta for a blocks global coordinate
	Delta* GetDelta(glm::vec3 blockGlobalCoordinate);

	// Return a delta for a chunk coordinate and a blocks local coordinate
	Delta* GetDelta(glm::vec3 chunkCoordinate, glm::vec3 blockCoordinate);

	// Add or modify a delta for a given chunk and block coordinate
	Delta* AddOrModifyDelta(glm::vec3 chunkCoordinate, glm::vec3 blockCoordinate, BlockType type);

	// Add or modify a delta for a blocks global coordinate
	Delta* AddOrModifyDelta(glm::vec3 BlockGlobalCoordinate, BlockType type);
};