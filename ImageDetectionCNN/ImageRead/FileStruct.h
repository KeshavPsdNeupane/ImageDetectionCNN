#pragma once
#include<SFML/Graphics.hpp>
#include"../Utility/Utility.h"

struct ImageData{
	int label;
	std::vector<float> values;
	sf::Texture texture;
public:	
	ImageData(): label(-1), values(), texture(){}
	ImageData(int label, std::vector<float> values, sf::Texture tex) :
		label(label), values(std::move(values)), texture(std::move(tex)) {
	}
};


