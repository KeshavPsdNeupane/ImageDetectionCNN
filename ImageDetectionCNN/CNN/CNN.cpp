#include "CNN.h"
#include"../Utility/Utility.h"
CNN::CNN(int batchSize, int inputSize, int hiddenSize, int outputSize):
batchSize(batchSize),
inputSize(inputSize),
hiddenSize(hiddenSize),
outputSize(outputSize),
input(batchSize, 0.0f),
hiddenWeight(hiddenSize, std::vector<float>(inputSize, 0.0f)),
hiddenBias(hiddenSize, 0.0f), 
outputWeight(outputSize, std::vector<float>(hiddenSize, 0.0f)),
outputBias(outputSize, 0.0f),
outputBCost(outputSize,0.0f),
hiddenBCost(hiddenSize,0.0f)
{}

CNN::~CNN(){}

void CNN::CnnOperate() {
	std::string weight("weight.txt");
	std::string bias("bias.txt");

	this->input = file.ReadBias("Data/input.txt", inputSize);

	// Read hidden layer weights/bias (corrected dimensions)
	this->hiddenWeight = file.ReadWeight(GMNumber::hiddenLocation + weight, hiddenSize, inputSize);
	this->hiddenBias = file.ReadBias(GMNumber::hiddenLocation + bias, hiddenSize);

	// Read output layer weights/bias (corrected dimensions)
	this->outputWeight = file.ReadWeight(GMNumber::outputLocation + weight, outputSize, hiddenSize);
	this->outputBias = file.ReadBias(GMNumber::outputLocation + bias, outputSize);

	// Forward Pass
	std::vector<float> A1 = Convulation(input, hiddenWeight, hiddenBias);               
	std::vector<float> final = ConvulationWithSoftmax(A1, outputWeight, outputBias);    

	file.PrintB(final);
}


std::vector<float> CNN::Convulation(std::vector<float>& input, std::vector<std::vector<float>>& weight, std::vector<float>& bias) {
	int outputSize = weight.size();
	int inputSize = input.size();
	std::vector<float> result(outputSize, 0.0f);
	for (int i = 0; i < outputSize; ++i) {
		for (int j = 0; j < inputSize; ++j) {
			result[i] += (weight[i][j] * input[j]);
		}
		result[i] += bias[i];
		result[i] = Sigmoid(result[i]);
	}
	return result;
}

std::vector<float> CNN::ConvulationWithSoftmax(std::vector<float>& input,
	std::vector<std::vector<float>>& weight, std::vector<float>& bias) {

	int outputSize = weight.size();
	int inputSize = input.size();
	std::vector<float> result(outputSize, 0.0f);

	for (int i = 0; i < outputSize; ++i) {
		for (int j = 0; j < inputSize; ++j) {
			result[i] += (weight[i][j] * input[j]);
		}
		result[i] += bias[i];
	}
	float maxVal = *std::max_element(result.begin(), result.end());
	std::vector<float> temp(result.size());
	float sum = 0.0f;

	for (int i = 0; i < result.size(); ++i) {
		temp[i] = std::exp(result[i] - maxVal);
		sum += temp[i];
	}
	for (int i = 0; i < result.size(); ++i) {
		result[i] = temp[i] / sum;
	}
	return result;
}

