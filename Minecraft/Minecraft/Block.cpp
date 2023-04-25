#include "Block.h"

Block::Block(Model* m)
	: ITransformable()
{
	model = m;
	visible = true;
}

void Block::Draw()
{
	if (!visible)
	{
		return;
	}

	model->Draw(GetTransformPointer());
}

void Block::SetVisibility(bool v)
{
	visible = v;
}

bool Block::IsVisible()
{
	return visible;
}