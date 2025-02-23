#include "util/random.hpp"

// Define static members outside the class
std::random_device Random::rd;
std::mt19937 Random::gen(Random::rd()); 

// Generate a random integer in the range [min, max]
int Random::getRandomInt(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

// Generate a boolean based on a percentage chance
bool Random::getBernoulliGate(double percentage) {
	// Convert percentage to a probability between 0.0 and 1.0
	double p = percentage / 100.0;
	std::bernoulli_distribution dist(p);
	return dist(gen);
}