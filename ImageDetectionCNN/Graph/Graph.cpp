#include "Graph.h"

MedianGraph::MedianGraph(sf::Vector2u UnitCount, sf::Vector2f position, sf::Vector2f graphSize, const std::string& name):
	isFirst(true),
	UnitCount(UnitCount),
	position(position),
	graphSize(graphSize),
	scale(sf::Vector2f(graphSize.x /float(UnitCount.x), graphSize.y / float(UnitCount.y))),
	graph(sf::LinesStrip, UnitCount.x){
	this->weight.reserve(UnitCount.x);
	this->buffer.reserve(UnitCount.x);
	if ((UnitCount.x & 1)) { // isEvenFunc
		std::cout << "MedianGraph's , UnitCount.x must be even. Current = " << UnitCount.x << "\n";
		std::abort();
	}

	std::cout << "scale: " << scale.x << "," << scale.y << "\n";


	this->graphTitle.setString(name);
	this->graphTitle.setCharacterSize(15);

}

void MedianGraph::Draw(std::shared_ptr<sf::RenderWindow> window){
	window->draw(this->graph);
	window->draw(this->graphTitle);
}


void MedianGraph::AddPoint(const float val){
	this->buffer.push_back(val);
	if (this->buffer.size() >= this->UnitCount.x) {
		UpdateGraph(this->buffer);
		this->buffer.clear();
	}
	
}


void MedianGraph::DisplayWeight(){
	for (unsigned int i = 0; i < this->weight.size(); ++i) {
		std::cout << this->weight[i] << ",";
	}
	std::cout << "Done\n";
}

void MedianGraph::LoadFont(std::shared_ptr<Engine::ResourceManager> resourceManager){
	this->graphTitle.setFont(resourceManager->GetFont(ResourceId::MAIN_FONT));
	const auto& bound = this->graphTitle.getLocalBounds();
	this->graphTitle.setOrigin(sf::Vector2f(bound.width * 0.5f, bound.height * 0.5f));
	this->graphTitle.setPosition(sf::Vector2f(this->position.x + this->graphSize.x * 0.5f, this->position.y + this->graphSize.y));
}

void MedianGraph::UpdateGraph(const std::vector<float>& newVector) {
	if (this->isFirst) {
		this->weight = newVector;
		this->isFirst = false;
	}
	else {
		if (newVector.size() & 1) { // this is easy version of isEven 
			std::cout << "Incoming vectors must be even, UpdateGraph function \n";
			std::abort();
		}
		else {
			ReComputeGraph(this->weight, newVector);
		}
	}	
	UpdateGraph();
}

void MedianGraph::ReComputeGraph(std::vector<float>& weight, const std::vector<float>& buffer) {
	int size = weight.size();
	std::vector<float> nVec(size, 0.0f);
	for (int i = 0; i < size; i = i + 2) {
		float madian = Median(weight[i + 1], weight[i]);
		nVec[int(i * 0.5f)] = madian;
	}
	int t = int(weight.size() * 0.5f);

	for (unsigned int i = 0; i < buffer.size(); i = i + 2) {
		float madian = Median(buffer[i + 1], buffer[i]);
		nVec[t + int(i * 0.5f)] = madian;
	}
	weight = nVec;
}

void MedianGraph::UpdateGraph(){
	for (unsigned int i = 0; i < weight.size(); ++i) {
		float x = this->position.x + i * this->scale.x;
		float y = this->position.y + this->graphSize.y - (this->scale.y * std::abs(this->weight[i]));
		//std::cout << "point pos = "<< x << "," << y << "," << this->weight[i] <<"\n";
		this->graph[i].position = sf::Vector2f(x, y);
		this->graph[i].color = sf::Color::Red;
	}
	//std::cout << "update Graph done \n\n\n";
}

