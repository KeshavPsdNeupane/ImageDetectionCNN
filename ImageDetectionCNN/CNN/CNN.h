#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include"../FileHandling/File.h"

class CNN{
	File file;
	int batchSize, inputSize,hiddenSize, outputSize;
	std::vector<float> input;
	std::vector<std::vector<float>>hiddenWeight;
	std::vector<float> hiddenBias;
	std::vector<std::vector<float>>outputWeight;
	std::vector<float> outputBias;
	std::vector<float>outputBCost;
	std::vector<float>hiddenBCost;
public:
	CNN(int batchSize,int inputSize,int hiddenSize, int outputSize);
	~CNN();

public:
	void CnnOperate();



private:
	std::vector<float> Convulation(std::vector<float>& input, std::vector<std::vector<float>>& weight, std::vector<float>& bias);
	std::vector<float> ConvulationWithSoftmax(std::vector<float>& input, std::vector<std::vector<float>>& weight, std::vector<float>& bias);




private:
	float Sigmoid(float x) { return 1.0f / (1 + std::exp(x)); }
	float SigmoidDerivative(float x) { return x*(1 - x); }
};

