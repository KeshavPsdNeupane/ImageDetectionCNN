#pragma once
#include<SFML/Graphics.hpp>
#include"States/StateManager.h"
#include"StateObjects.h"

class CnnRunner {
private:
	std::shared_ptr<StateData> stateData;
	sf::Clock clock;
	float DELTA_TIME;
public:
	CnnRunner();
	~CnnRunner();

public:
	void Run();
private:
	void LoadAllAssets();
};

