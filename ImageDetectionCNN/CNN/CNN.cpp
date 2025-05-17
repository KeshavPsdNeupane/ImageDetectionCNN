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
outputBias(outputSize, 0.0f){
	ReadWeightAndBiases(GMNumber::WEIGHT, GMNumber::BIAS);
}

CNN::~CNN(){}

void CNN::CnnOperate() {
	// Load input and weights/biases
	int testAnswer = 3;

	// Forward pass: input -> hidden layer -> output layer with softmax
	std::vector<float> A1 = Convulation(input, hiddenWeight, hiddenBias);
	std::vector<float> final = ConvulationWithSoftmax(A1, outputWeight, outputBias);

	// Compute cost gradient at output layer (softmax + cross-entropy)
	std::vector<float> softMaxCostFuncCosts = CostForSigmoid(final, testAnswer);
	auto& outputBackError = softMaxCostFuncCosts; 
	// Backpropagate error to hidden layer
	std::vector<float> backPrpForHidden = BackPropError(this->outputWeight, outputBackError);

	// Update weights and biases for output layer
	UpdateWeightAndBias(this->outputWeight, this->outputBias, softMaxCostFuncCosts, A1);

	// Compute activation cost for hidden layer (with sigmoid derivative)
	std::vector<float> ActivationCOstHiddenLayer = ActivationCost(A1, backPrpForHidden);

	// Update weights and biases for hidden layer
	UpdateWeightAndBias(this->hiddenWeight, this->hiddenBias, ActivationCOstHiddenLayer, this->input);

	file.PrintB(final);
	std::cout << "Total cost = " << TotalCost(final, testAnswer) << "\n";
	// Save updated weights and biases to files
	WriteWeightAndBiases(GMNumber::WEIGHT, GMNumber::BIAS);
}


std::vector<float> CNN::Convulation(
	std::vector<float>& input,
	std::vector<std::vector<float>>& weight,
	std::vector<float>& bias){

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

std::vector<float> CNN::ConvulationWithSoftmax(
	std::vector<float>& input,
	std::vector<std::vector<float>>& weight,
	std::vector<float>& bias){

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

	for (unsigned int i = 0; i < result.size(); ++i) {
		temp[i] = std::exp(result[i] - maxVal);
		sum += temp[i];
	}
	for (unsigned int i = 0; i < result.size(); ++i) {
		result[i] = temp[i] / sum;
	}
	return result;
}

std::vector<float> CNN::CostForSigmoid(
	std::vector<float> result,
	int y){

	int it = result.size();
	std::vector<float> cost (it, 0.0f) ;
	for (int i = 0; i < it; ++i) {
		cost[i] = SoftMaxPlusCostDerivative(result[i], ((i == y) ? 1.0f : 0.0f) );
	}
	return cost;
}

std::vector<float> CNN::BackPropError(
	const std::vector<std::vector<float>>& currentWeight,
	const std::vector<float> cost){

	int m = currentWeight.size() , n = currentWeight[0].size();
	std::vector<float>backError(n, 0.0f);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m ; ++j) {
			backError[i] += currentWeight[j][i] * cost[j];
		}
	}
	return backError;
}

std::vector<float> CNN::ActivationCost(
	const std::vector<float>& activelayer,
	const std::vector<float>& backPropagationCost){

	int m = activelayer.size();
	std::vector<float> activeCost(m, 0.0f);
	for (int i = 0; i < m; ++i) {
		activeCost[i] = backPropagationCost[i] * SigmoidDerivation(activelayer[i]);
	}
	return activeCost;
}

void CNN::UpdateWeightAndBias(std::vector<std::vector<float>>& weight, std::vector<float>& bias,
	const std::vector<float>& cost, const std::vector<float>& input){
	int m = cost.size(), n = input.size();
	float rate = GMNumber::LEARN_RATE;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			weight[i][j] -= ( rate * cost[i] * input[j]);
		}
		bias[i] -= (rate * cost[i]) ;
	}
	return;
}

void CNN::ReadWeightAndBiases(
	const std::string& weight,
	const std::string& bias){

	this->input = file.ReadBias("Data/input.txt", inputSize);
	this->hiddenWeight = file.ReadWeight(GMNumber::HIDDEN_LAYER_FILES_LOCATION + weight, hiddenSize, inputSize);
	this->hiddenBias = file.ReadBias(GMNumber::HIDDEN_LAYER_FILES_LOCATION + bias, hiddenSize);
	this->outputWeight = file.ReadWeight(GMNumber::OUTPUT_LAYER_FILES_LOCATION + weight, outputSize, hiddenSize);
	this->outputBias = file.ReadBias(GMNumber::OUTPUT_LAYER_FILES_LOCATION + bias, outputSize);
}

void CNN::WriteWeightAndBiases(
	const std::string& weight,
	const std::string& bias){

	file.WriteWeight(GMNumber::HIDDEN_LAYER_FILES_LOCATION + weight, this->hiddenWeight);
	file.WriteBias(GMNumber::HIDDEN_LAYER_FILES_LOCATION + bias, this->hiddenBias);
	file.WriteWeight(GMNumber::OUTPUT_LAYER_FILES_LOCATION + weight, this->outputWeight);
	file.WriteBias(GMNumber::OUTPUT_LAYER_FILES_LOCATION + bias, this->outputBias);
}


