#pragma once
/// <summary>
/// Utility class to help with book keeping of the game state. 
/// </summary>
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