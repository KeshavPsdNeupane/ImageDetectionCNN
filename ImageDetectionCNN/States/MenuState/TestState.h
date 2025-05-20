#pragma once
#include"../../ImageRead/ImageReading.h"
#include"../../CNN/CNN.h"
#include"../../FileHandling/File.h"
#include"../../StateObjects.h"
#include"../State.h"
#include<array>

class TestState: public Engine::State {
	bool canTest;
	ImageReading readImg;
	std::shared_ptr<ImageData> currentImage;
	CNN cnn;
	File file;
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	sf::Text gameMenuTitle;
	std::array<sf::Text, 3> texts;
	sf::Sprite sprite;


	sf::Text resultText;
	
	ResultCombo resComb;


	short IsSetectedIndex;
	short IsPressedIndex;
public:
	TestState(std::shared_ptr<StateData> stateData);
	~TestState();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;


private:
	void UiUpdate();
};

