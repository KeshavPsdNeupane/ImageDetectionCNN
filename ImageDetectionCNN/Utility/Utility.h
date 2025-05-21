#pragma once
#include<cmath>
#include<string>


namespace GMNumber {
	//  FOR WINDOWS 
	static constexpr float WINDOW_WIDTH = 800.0f;
	static constexpr float WINDOW_HEIGHT = 600.0f;
	static constexpr int MAX_FRAME_RATE = 0; ;
	static constexpr float LEARN_RATE = 0.0100015f;
	static constexpr int WAITING_TIME_FOR_WRITE = 5000;


	static constexpr int	USE_0_1_LIIMIT = 5000;
	static constexpr int	USE_0_01_LIMIT = 100000;

	static constexpr int RATE_DECAY_OF_LEARN_RATE_ITERATION = 500;
	




	static const std::string& HIDDEN_LAYER_FILES_LOCATION("Data/Hidden/");
	static const std::string& OUTPUT_LAYER_FILES_LOCATION("Data/Output/");
	static const std::string& WEIGHT("weight.txt");
	static const std::string& BIAS("bias.txt");
	static const std::string& LEARN_RATE_LOCATION("Data/externalSetting.txt");





	static const std::string& PICTURE_DOCKER_PATH = "Asset/Pictures";
	static const std::string& TEST_PNG_FOLDER_NAME("Test");
	static const std::string& TRAINING_PNG_FOLDER_NAME("Training");







};




struct UtlFunc {
	template<typename T>
	static T Clamp(T current, const T min, const T max) {
		if (current < min) { current = min; }
		if (current > max) { current = max; }
		return current;
	}

	static float Sigmoid(const float x) {
		return 1.0f / (1.0f + std::exp(x));
	}


	static void handle_error(const std::string& error_message) {
		std::cerr << "Error: " << error_message << std::endl;
		std::abort();
	}
};