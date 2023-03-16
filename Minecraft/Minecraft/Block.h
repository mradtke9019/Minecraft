#pragma once
#include "Model.h"
#include "ITransformable.h"

class Block: public ITransformable
{
private:
	Model* model;
public:
	Block(Model* m);

	void Draw();
};

