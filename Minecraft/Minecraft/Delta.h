#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Block.h"


///Class used to track any differences that occur based on removal of blocks from default terrain
struct Delta
{
	//Type will hold the information about what the target Block should be from the default world block
	BlockType type;
	glm::vec3 ChunkCoordinate;
	glm::vec3 BlockCoordinate;
	glm::vec3 BlockGlobalCoordinate;
};