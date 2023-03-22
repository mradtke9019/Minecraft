#include "Chunk.h"

Chunk::Chunk(Block block)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				Block newBlock = Block(block);
				newBlock.SetPosition(glm::vec3(i, j, k));
				blocks.push_back(newBlock);
			}
		}
	}
}

void Chunk::Draw()
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].Draw();
	}
}