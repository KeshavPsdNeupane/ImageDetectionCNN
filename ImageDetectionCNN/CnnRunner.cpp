#include "CnnRunner.h"
#include "States/MenuState/MainMenuState.h"
#include"Utility/Utility.h"



CnnRunner::CnnRunner() :
	stateData(std::make_shared<StateData>()),
	DELTA_TIME(0.0f) {
	this->stateData->window->create(sf::VideoMode((int)(GMNumber::WINDOW_WIDTH),
		(int)(GMNumber::WINDOW_HEIGHT)),
		" Physic Engine", sf::Style::Close);
	this->stateData->window->setFramerateLimit(GMNumber::MAX_FRAME_RATE);
	this->stateData->stateManager->AddState(
		std::make_unique<MainMenu>(this->stateData), true);
	LoadAllAssets();
}

CnnRunner::~CnnRunner() {}
void CnnRunner::Run() {
	while (this->stateData->window->isOpen()) {
		this->DELTA_TIME = clock.restart().asSeconds();
		this->stateData->stateManager->ProcessStateChanges();
		auto& currentState = this->stateData->stateManager->GetActiveState();

		currentState->ProcessInput();
		currentState->Update(DELTA_TIME);
		currentState->Draw();
	}
}

void CnnRunner::LoadAllAssets() {
	auto& resource = this->stateData->resourceManager;
	resource->AddFont(ResourceId::MAIN_FONT, "Asset/Fonts/arial.ttf");
}
