#pragma once
#include<cmath>
#include<string>
namespace GMNumber {
	//  FOR WINDOWS 
	static constexpr float WINDOW_WIDTH = 800.0f;
	static constexpr float WINDOW_HEIGHT = 600.0f;
	static constexpr int MAX_FRAME_RATE = 60; ;
	static constexpr float learnRate = 0.001f;


	static const std::string hiddenLocation("Data/Hidden/");
	static const std::string outputLocation("Data/Output/");
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