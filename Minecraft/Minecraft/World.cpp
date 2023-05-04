#include "World.h"

std::vector<Chunk>* World::GetChunks()
{
	return &chunks;
}

WorldDelta* World::GetWorldDelta()
{
	return &worldDelta;
}

Chunk* World::GetChunk(glm::vec3 coord)
{
	auto chunk = std::find_if(
		chunks.begin(),
		chunks.end(),
		[&](Chunk c) {
			return c.GetPosition() == coord;
		});
	return &(*chunk);
}

Block* World::GetBlockByGlobalCoordinate(glm::vec3 globalBlockCoordinate)
{
	glm::vec3 chunkCoord = GlobalToChunkCoordinate(globalBlockCoordinate);
	Chunk* chunk = GetChunk(chunkCoord);
	if (chunk == nullptr)
	{
		return nullptr;
	}
	
	glm::vec3 localBlockCoord = glm::vec3(
		(int)globalBlockCoordinate.x % Constants::CHUNK_SIZE,
		(int)globalBlockCoordinate.y % Constants::CHUNK_SIZE,
		(int)globalBlockCoordinate.z % Constants::CHUNK_SIZE
	);

	// If i am at block 54, then locally i would be at block 6 because I am in chunk 3 * 16 = 48, with a remainder of 6
	Block* block = chunk->GetBlock(localBlockCoord);
	return block;
}

Block* World::GetBlock(glm::vec3 chunkCoord, glm::vec3 blockCoord)
{
	Chunk* c = GetChunk(chunkCoord);
	return c->GetBlock(blockCoord);
}

glm::vec3 World::GlobalToChunkCoordinate(glm::vec3 globalCoord, bool round)
{
	glm::vec3 chunkCoord = globalCoord / (float)Constants::CHUNK_SIZE;
	if (round)
	{
		chunkCoord = glm::floor(chunkCoord);
	}

	return chunkCoord;
}

void World::UpdateByPlayerPosition(Player* player, Block* defaultBlock, bool isGlobal)
{
	glm::vec3 playerChunkCoordinate = player->GetCamera()->GetPosition();
	if (isGlobal)
	{
		playerChunkCoordinate = GlobalToChunkCoordinate(playerChunkCoordinate);
	}

	chunks.erase(std::remove_if(chunks.begin(), chunks.end(),
		[&](Chunk& c)
		{
			float distance = glm::distance(playerChunkCoordinate, c.GetPosition());
			if (distance > Constants::RADIUS_GENERATION)
				return true;
			return false;
		}), chunks.end());

	// Add new chunks to load based on the current player position.
	// Do a loop for coordinates around the player to see if we can add any chunks.
	for (int i = -Constants::RADIUS_GENERATION; i < Constants::RADIUS_GENERATION; i++)
	{
		for (int j = -Constants::RADIUS_GENERATION; j < Constants::RADIUS_GENERATION; j++)
		{
			glm::vec3 chunkCoordinate = glm::vec3(playerChunkCoordinate.x, 0, playerChunkCoordinate.z) + glm::vec3(i, 0, j);
			float distance = glm::distance(playerChunkCoordinate, chunkCoordinate);
			if (distance > Constants::RADIUS_GENERATION)
				continue;

			auto chunk = std::find_if(
				chunks.begin(),
				chunks.end(),
				[&](Chunk& c) {
					return c.GetPosition() == chunkCoordinate;
				});

			if (chunk == chunks.end())
			{
				chunks.push_back(Chunk(chunkCoordinate, *defaultBlock, worldDelta));
			}
		}
	}

	// Cull all chunks that are not within the direction the person is facing in the xz plane
	glm::vec3 playerChunkPosition = World::GlobalToChunkCoordinate(player->GetCamera()->GetPosition(), false);
	glm::vec2 camPos = glm::vec2(playerChunkPosition.x, playerChunkPosition.z);
	glm::vec2 camDir = glm::normalize(glm::vec2(player->GetCamera()->GetCameraDirection().x, player->GetCamera()->GetCameraDirection().z));

	for (int i = 0; i < chunks.size(); i++)
	{
		// Consider each corner of the chunk to make sure we dont accidentally cull something that is visible.
		// Assume not visible until one of the corners is visible.
		glm::vec3* corners = chunks[i].GetChunkGlobalCorners();
		bool visible = false;
		for (int i = 0; i < 8; i++)
		{
			glm::vec2 chunkPos = glm::vec2((corners + i)->x, (corners + i)->z);

			glm::vec2 diff = chunkPos - camPos;
			float dot = glm::dot(diff, camDir);
			float angle = glm::angle(diff, camDir);
			if (angle > glm::pi<float>() / 2.0f && angle < glm::pi<float>() * 3.0f / 2.0f)
			{
				//chunks[i].SetVisibility(false);
			}
			else
			{
				visible = true;
				break;
			}
		}

		chunks[i].SetVisibility(visible);
	}
}


void World::Draw()
{
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].Draw();
	}
}