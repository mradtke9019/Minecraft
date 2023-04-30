#pragma once
#include "WorldDelta.h"

WorldDelta::WorldDelta()
{
	deltas = std::vector<Delta>();
}

Delta* WorldDelta::GetDelta(glm::vec3 chunkCoordinate, glm::vec3 blockCoordinate)
{
	auto d = std::find_if(
		deltas.begin(),
		deltas.end(),
		[&](Delta d) {
			return d.ChunkCoordinate == chunkCoordinate && d.BlockCoordinate == blockCoordinate;
		});
	if (d == deltas.end())
		return nullptr;
	return &(*d);
}

Delta* WorldDelta::GetDelta(glm::vec3 blockGlobalCoordinate)
{
	auto d = std::find_if(
		deltas.begin(),
		deltas.end(),
		[&](Delta d) {
			return d.BlockGlobalCoordinate == blockGlobalCoordinate;
		});
	if (d == deltas.end())
		return nullptr;
	return &(*d);
}


Delta* WorldDelta::AddOrModifyDelta(glm::vec3 chunkCoordinate, glm::vec3 blockCoordinate, BlockType type)
{
	Delta* d = GetDelta(chunkCoordinate, blockCoordinate);

	if (d == nullptr)
	{
		Delta delta = Delta();
		delta.BlockCoordinate = blockCoordinate;
		delta.ChunkCoordinate = chunkCoordinate;
		delta.type = type;
		deltas.push_back(delta);
		d = &delta;
	}
	d->type = type;

	return d;
}

Delta* WorldDelta::AddOrModifyDelta(glm::vec3 blockGlobalCoordinate, BlockType type)
{
	Delta* d = GetDelta(blockGlobalCoordinate);

	if (d == nullptr)
	{
		Delta delta = Delta();
		delta.BlockGlobalCoordinate = blockGlobalCoordinate;
		delta.ChunkCoordinate = glm::vec3(0);
		delta.BlockCoordinate = glm::vec3(0);
		deltas.push_back(delta);
		d = &delta;
	}
	d->type = type;

	return d;
}