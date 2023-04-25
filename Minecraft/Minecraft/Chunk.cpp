#include "Chunk.h"

Chunk::Chunk(glm::vec3 chunkCoordinate, Block block)
{
	glm::vec2 chunkCoord = glm::vec2(chunkCoordinate.x, chunkCoordinate.z);
	this->SetPosition(chunkCoordinate);
	blocks = std::vector<std::vector<std::vector<Block>>>();
	//blocks.push_back(std::vector<std::vector<Block>>());
	for (int i = 0; i < 16; i++)
	{
		blocks.push_back(std::vector<std::vector<Block>>());
		for (int k = 0;k < 16; k++)
		{
			blocks[i].push_back(std::vector<Block>());
			glm::vec2 coord = glm::vec2(i, k);
			int height = Noise::GenerateHeight(0, 0, 16, chunkCoord, coord);

			for (int j = 0; j < 16; j++)
			{

				Block newBlock = Block(block);
				glm::vec3 blockWorldPosition = GetBlockGlobalCoordinate(glm::vec3(i,j,k));
				newBlock.SetPosition(blockWorldPosition);


				//int h = glm::floor(height * 16);
				if (j > height)
				{
					newBlock.SetVisibility(false);
				}

				blocks[i][k].push_back(newBlock);
			}
		}
	}

}


glm::vec3 Chunk::GetBlockGlobalCoordinate(glm::vec3 localCoordinate)
{
	glm::vec3 ChunkCoordinate = this->GetPosition();
	glm::vec3 blockWorldPosition = glm::vec3(localCoordinate.x + ChunkCoordinate.x * 16, localCoordinate.y + ChunkCoordinate.y * 16, localCoordinate.z + ChunkCoordinate.z * 16);
	return blockWorldPosition;
}

bool Chunk::IsBlockVisible(glm::vec3 localCoordinate)
{
	// Check each of the 6 faces and see if there are any spots exposed that do not have a block in this chunk.
	bool valid = false;
	int i = localCoordinate.x;
	int j = localCoordinate.y;
	int k = localCoordinate.z;

	if (i < 0 || i >= 16 ||
		j < 0 || j>= 16 || 
		k< 0 || k >= 16)
	{
		return false;
	}

	return blocks[i][j][k].IsVisible();
}

std::vector<Block*> Chunk::GetBlocks()
{
	std::vector<Block*> results = std::vector<Block*>();
	for (int i = 0; i < blocks.size(); i++)
	{
		for (int j = 0; j < blocks[i].size(); j++)
		{
			for (int k = 0; k < blocks[i][j].size(); k++)
			{
				results.push_back(&blocks[i][j][k]);
			}
		}
	}
	return results;
}


bool Chunk::ValidBlock(glm::vec3 localCoordinate)
{
	// Check each of the 6 faces and see if there are any spots exposed that do not have a block in this chunk.
	int i = localCoordinate.x;
	int j = localCoordinate.y;
	int k = localCoordinate.z;

	// Block is not valid if the current one is not visible
	if (!IsBlockVisible(localCoordinate))
	{
		return false;
	}

	// If all neighbors are visible, we cannot see the current block
	if (IsBlockVisible(glm::vec3(i + 1, j, k)) && IsBlockVisible(glm::vec3(i - 1, j, k)) &&
		IsBlockVisible(glm::vec3(i, j + 1, k)) && IsBlockVisible(glm::vec3(i, j - 1, k)) &&
		IsBlockVisible(glm::vec3(i, j, k + 1)) && IsBlockVisible(glm::vec3(i, j, k - 1)))
	{
		return false;
	}

	return true;
}

void Chunk::Draw()
{
	for (int i = 0; i < blocks.size(); i++)
	{
		for (int j = 0; j < blocks[i].size(); j++)
		{
			for (int k = 0; k < blocks[i][j].size(); k++)
			{
				glm::vec3 localCoordinate = glm::vec3(i, j, k);
				if (ValidBlock(localCoordinate))
				{
					blocks[i][j][k].Draw();
				}
			}
		}
	}
}