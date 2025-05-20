#pragma once
#include"../../ImageRead/ImageReading.h"
#include"../../CNN/CNN.h"
#include"../../FileHandling/File.h"
#include"../../StateObjects.h"
#include"../State.h"
#include<array>

class TrainMode : public Engine::State {
	bool isStopped;
	ItandLearn itAndLearn;
	ImageReading readImg;
	CNN cnn;
	File file;
	std::shared_ptr<ImageData> currentImage;


	std::shared_ptr<StateData> stateData;
	sf::Event event;
	sf::Text gameMenuTitle;
	std::array<sf::Text, 3> texts;


	sf::Text iterationText;

	short IsSetectedIndex;
	short IsPressedIndex;
public:
	TrainMode(std::shared_ptr<StateData> stateData);
	~TrainMode();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;


private:
	void UiUpdate();
};

