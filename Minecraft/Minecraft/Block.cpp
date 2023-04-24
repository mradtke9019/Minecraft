#include "Block.h"

Block::Block(Model* m)
	: ITransformable()
{
	model = m;
}

void Block::Draw()
{
	model->Draw(GetTransformPointer());
}