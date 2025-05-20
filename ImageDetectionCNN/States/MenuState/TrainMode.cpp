#include "TrainMode.h"
#include "MainMenuState.h"

TrainMode::TrainMode(std::shared_ptr<StateData> stateData) :
	isStopped(false),
	itAndLearn(file.ReadLearnRate(GMNumber::LEARN_RATE_LOCATION)),
	stateData(stateData), event(),
	cnn(1, 784, 100, 10, file),
	IsSetectedIndex(0), IsPressedIndex(-1), texts() {
	this->readImg.LoadTrainingPictures(GMNumber::PICTURE_DOCKER_PATH);
}

TrainMode::~TrainMode() {}

void TrainMode::Load() {
	const sf::Font& font = this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT);
	sf::Vector2u pos = this->stateData->window->getSize();
	sf::Vector2f half(pos.x * 0.5f, pos.y * 0.5f);
	sf::FloatRect bound;

	this->gameMenuTitle.setFont(font);
	this->gameMenuTitle.setString("TrainMode");
	this->gameMenuTitle.setCharacterSize(30);
	bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width * 0.5f, bound.height * 0.5f);
	this->gameMenuTitle.setPosition(half.x, bound.height * 0.5f);
	int fontSize = 18;

	this->iterationText.setFont(font);
	this->iterationText.setCharacterSize(fontSize);
	this->iterationText.setPosition(0.0f, half.y);
	this->iterationText.setString("Iteration = " + std::to_string(this->itAndLearn.iteration));



	for (unsigned int i = 0; i < texts.size(); ++i) {
		auto& level = this->texts[i];
		level.setFont(font);

		if (i == 0) {
			level.setString("Start/Stop");
		}
		else if (i == 1) {
			level.setString("Back");
		}
		else if (i == texts.size() - 1) {
			level.setString("Exit");
		}
		level.setCharacterSize(fontSize);
		bound = level.getLocalBounds();
		level.setOrigin(bound.width * 0.5f, bound.height * 0.5f);
		level.setPosition(bound.width * 0.5f + 2.f, 0.25f * half.y - float(fontSize) + 2 * level.getCharacterSize() * i);
	}
}

void TrainMode::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				this->IsSetectedIndex = UtlFunc::Clamp(this->IsSetectedIndex - 1, 0, (int)(this->texts.size() - 1));
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				this->IsSetectedIndex = UtlFunc::Clamp(this->IsSetectedIndex + 1, 0, (int)(this->texts.size() - 1));
				break;

			case sf::Keyboard::Return:
				this->IsPressedIndex = this->IsSetectedIndex;
				break;

			default:
				break;
			}
		}

	}
}

#include <sstream>
#include <iomanip>

void TrainMode::Update(const float& dt) {
	UiUpdate();
	if (this->isStopped) {
		return;
	}

	this->currentImage = this->readImg.GetRandomTrainingPicture();
	this->cnn.CnnOperate(false, this->currentImage, this->itAndLearn.learnRate);

	auto& iter = ++this->itAndLearn.iteration;
	auto& rate = this->itAndLearn.learnRate;

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(10);
	oss << "Iteration = " << iter << "\nLearnRate = " << rate;
	this->iterationText.setString(oss.str());

	if (iter < GMNumber::USE_0_1_LIIMIT) {
		rate = 0.1f;
	}
	else if (iter == GMNumber::USE_0_1_LIIMIT) {
		rate = 0.01f;
	}
	else if (iter == GMNumber::USE_0_01_LIMIT) {
		rate = 0.001f;
	}

	if (iter >= GMNumber::USE_0_01_LIMIT &&
		iter % GMNumber::RATE_DECAY_OF_LEARN_RATE_ITERATION == 0) {
		rate *= GMNumber::DECAY_RATE;
	}

	if (iter % GMNumber::WAITING_TIME_FOR_WRITE == 0) {
		this->cnn.SaveSignalExternalWieghts();
	}
}





void TrainMode::Draw() {
	this->stateData->window->clear(sf::Color::Black);
	this->stateData->window->draw(this->gameMenuTitle);
	for (auto& text : texts) {
		this->stateData->window->draw(text);
	}
	this->stateData->window->draw(this->iterationText);
	this->stateData->window->display();
}

void TrainMode::UiUpdate() {
	for (unsigned int i = 0; i < texts.size(); ++i) {
		if (i != this->IsSetectedIndex) {
			this->texts[i].setFillColor(sf::Color::White);
		}
		else {
			this->texts[i].setFillColor(sf::Color::Red);
		}
	}

	if (this->IsPressedIndex > -1) {
		if (this->IsPressedIndex == 0) {
			this->isStopped = !this->isStopped;
			this->IsPressedIndex = -1;
		}
		else if (this->IsPressedIndex == 1) {
			file.WriteLearnRate(GMNumber::LEARN_RATE_LOCATION, this->itAndLearn);
			this->cnn.SaveSignalExternalWieghts();
			this->stateData->stateManager->AddState(std::make_unique<MainMenu>(this->stateData), true);
		}
		else if (this->IsPressedIndex == texts.size() - 1) {
			file.WriteLearnRate(GMNumber::LEARN_RATE_LOCATION, this->itAndLearn);
			this->cnn.SaveSignalExternalWieghts();
			this->stateData->window->close();
		}
	}
}
