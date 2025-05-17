#pragma once
#include<SFML/Graphics.hpp>
#include"../Utility/Utility.h"

struct ImageData{
	int result;
	sf::Image image;
	sf::Texture texture;
public:	
	ImageData(): result(0),image(), texture(){}
	ImageData(int result , sf::Image img , sf::Texture tex): result(result), image(std::move(img)),texture(std::move(tex)){}
};