#include "TestState.h"
#include "MainMenuState.h"

TestState::TestState(std::shared_ptr<StateData> stateData) :
	canTest(false),
	stateData(stateData), event(),
	cnn(1, 784, 100, 10, file),
	IsSetectedIndex(0), IsPressedIndex(-1), texts() {
	this->readImg.LoadTestPictures(GMNumber::PICTURE_DOCKER_PATH);
}

TestState::~TestState() {}

void TestState::Load() {
	const sf::Font& font = this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT);
	sf::Vector2u pos = this->stateData->window->getSize();
	sf::Vector2f half(pos.x * 0.5f, pos.y * 0.5f);
	sf::FloatRect bound;

	this->gameMenuTitle.setFont(font);
	this->gameMenuTitle.setString("TestMode");
	this->gameMenuTitle.setCharacterSize(30);
	bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width * 0.5f, bound.height * 0.5f);
	this->gameMenuTitle.setPosition(half.x, bound.height * 0.5f);
	int fontSize = 18;


	this->resultText.setFont(font);
	this->resultText.setCharacterSize(fontSize);
	this->resultText.setPosition(0.0f, 0.6f * half.y);
	this->resultText.setString("Actual = " + std::to_string(0) +"\n"
		+ "Result = " + std::to_string(this->resComb.result) + " \n"
		+ "Probability:\n" +
		"0 = " + std::to_string(0.0f) + " \n" +
		"1 = " + std::to_string(0.0f) + " \n" +
		"2 = " + std::to_string(0.0f) + " \n" +
		"3 = " + std::to_string(0.0f) + " \n" +
		"4 = " + std::to_string(0.0f) + " \n" +
		"5 = " + std::to_string(0.0f) + " \n" +
		"6 = " + std::to_string(0.0f) + " \n" +
		"7 = " + std::to_string(0.0f) + " \n" +
		"8 = " + std::to_string(0.0f) + " \n" +
		"9 = " + std::to_string(0.0f) + " \n" +
		"Cost = " + std::to_string(this->resComb.cost) + "\n"
	);





	for (unsigned int i = 0; i < texts.size(); ++i) {
		auto& level = this->texts[i];
		level.setFont(font);

		if (i == 0) {
			level.setString("Test Random");
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




	this->sprite.setPosition(half);


}

void TestState::ProcessInput() {
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

void TestState::Update(const float& dt) {
	UiUpdate();
	if (this->canTest) {
		this->canTest = false;
		this->currentImage = this->readImg.GetRandomTestPicture();
		this->sprite.setTexture(this->currentImage->texture, true);
		this->sprite.setScale(sf::Vector2f(3.0f, 3.0f));


	    this->cnn.CnnOperate(true, this->currentImage);
		this->resComb = this->cnn.ReturnResultsWIthProbability();




		auto& prob = this->resComb.probability;
		this->resultText.setString("Actual = " + std::to_string(this->currentImage->label)+ "\n"
			+"Result = " + std::to_string(this->resComb.result) + " \n"
			+ "Probability:\n" + 
			"0 = " + std::to_string(prob[0]) + " \n" +
			"1 = " + std::to_string(prob[1]) + " \n" +
			"2 = " + std::to_string(prob[2]) + " \n" +
			"3 = " + std::to_string(prob[3]) + " \n" +
			"4 = " + std::to_string(prob[4]) + " \n" +
			"5 = " + std::to_string(prob[5]) + " \n" +
			"6 = " + std::to_string(prob[6]) + " \n" +
			"7 = " + std::to_string(prob[7]) + " \n" +
			"8 = " + std::to_string(prob[8]) + " \n" +
			"9 = " + std::to_string(prob[9]) + " \n" +
			"Cost = " + std::to_string(this->resComb.cost) + "\n"
		);

	}


}

void TestState::Draw() {
	this->stateData->window->clear(sf::Color::Black);
	this->stateData->window->draw(this->gameMenuTitle);
	for (auto& text : texts) {
		this->stateData->window->draw(text);
	}
	this->stateData->window->draw(this->resultText);
	this->stateData->window->draw(this->sprite);
	this->stateData->window->display();
}

void TestState::UiUpdate(){
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
			this->canTest = true;
			this->IsPressedIndex = -1;
		}
		else if (this->IsPressedIndex == 1) {
			this->stateData->stateManager->AddState(std::make_unique<MainMenu>(this->stateData), true);
		}
		else if (this->IsPressedIndex == texts.size() - 1) {
			this->stateData->window->close();
		}
	}
}
