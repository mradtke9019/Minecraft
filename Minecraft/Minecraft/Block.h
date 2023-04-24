#pragma once
#include "Model.h"
#include "ITransformable.h"

class Block: public ITransformable
{
private:
	Model* model;
	bool visible;
public:
	Block(Model* m);

	void SetVisibility(bool v);
	
	bool IsVisible();

	void Draw();
};

