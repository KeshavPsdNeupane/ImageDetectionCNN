#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"
#include "../../Utility/Utility.h"
#include"../../Graph/Graph.h"
#include"../../FileHandling/File.h"
#include<array>
#include<random>

class MainMenu : public Engine::State {
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	sf::Text gameMenuTitle;
	std::array<sf::Text, 4> texts;
	File f;
	short IsSetectedIndex;
	short IsPressedIndex;
public:
	MainMenu(std::shared_ptr<StateData> stateData);
	~MainMenu();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;


};
