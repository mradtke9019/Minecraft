#pragma once

class Utility 
{
private:


public:

	Utility();
	~Utility();
	void Update(float);
	float& GetDeltaTime();
	float DeltaTime;
	float LastFrame;
};