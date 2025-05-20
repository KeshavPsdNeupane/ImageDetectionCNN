#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include"../Resources/ResourceManager.h"
#include<memory>

// YES THIS GRAPH IS A MEDIAN GRAPH , IT HAS FIXED SIZE 
// AND REPRESEND VALIES AS MEDIAN OF VALUES OF THE WHOLE DATASET ON ITS FIXED SIZE
// THAT IS WHY THE UNITCOUNT.X MUST BE EVEN
class MedianGraph{
	bool isFirst;
	sf::Vector2u UnitCount;
	sf::VertexArray graph;
	std::vector<float> weight;
	std::vector<float> buffer;
	sf::Vector2f position;
	sf::Vector2f graphSize;
	sf::Vector2f scale;
	sf::Text graphTitle;
public:
	MedianGraph() = default;
	// BY UNITCOUNT , WE MEAN HOW MUCH POINT WE CAN HAVE AS .X AXIS , MAKE SURE .X VAL IS ALWAYS EVEN
	// AND WHAT IS THE UPPER CELING OF DATA SET AS .Y VALUE, WHICH IS USED TO FIND THE SEPERATION BETWEEN IN 
	// PARTICULAR UNIT REPRESENTATION ON BOTH  AXIS, 
	MedianGraph(sf::Vector2u UnitCount, sf::Vector2f position , sf::Vector2f graphSize, const std::string& name);
	~MedianGraph(){}
	void Draw(std::shared_ptr<sf::RenderWindow> window);
public:
	void AddPoint(const float val);
	void DisplayWeight();
	void LoadFont(std::shared_ptr<Engine::ResourceManager> resourceManager);
private:
	inline float Median(float x2, float x1) { return 0.5f * (x2 + x1); }  // for 2 item mean == median
	void UpdateGraph(const std::vector<float> & newVector);
	void ReComputeGraph(std::vector<float>& weight,const std::vector<float>& buffer);
	void UpdateGraph();
};


















////// simple code to make a graph
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple SFML Graph");
//    // Sample data points (y-values)
//    std::vector<float> data = { 100, 150, 200, 180, 220, 300, 280, 320, 270, 250 };
//    // Scale factors to fit graph in window
//    float xSpacing = 70.f;
//    float yScale = 1.f;
//    // Create vertex array for the line strip
//    sf::VertexArray lines(sf::LineStrip, data.size());
//    for (size_t i = 0; i < data.size(); ++i) {
//        float x = 50 + i * xSpacing;          // x position with some margin
//        float y = 550 - data[i] * yScale;     // y inverted to draw upwards, margin at bottom
//        lines[i].position = sf::Vector2f(x, y);
//        lines[i].color = sf::Color::Green;
//    }
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        window.clear(sf::Color::Black);
//        window.draw(lines);
//        window.display();
//    }
//
//    return 0;
//
