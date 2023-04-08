#pragma once
#include "Block.h"
class Chunk
{
private:
	std::vector<Block> blocks;

public:
	Chunk(Block block);

	void Draw();
};

