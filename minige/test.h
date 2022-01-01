#pragma once
#include <iostream>

template<typename T>
bool test(T expected, T actual, const char * message) {
	if (expected == actual) {
		return true;
	}
	else {
		std::cout << message;
		throw message;
	}
}

bool test(double expected, double actual, const char * message, double epsilon = 0.001) {
	double difference = expected - actual;
	difference = difference > 0 ? difference : -difference;
	if (difference <= epsilon) {
		return true;
	}
	else {
		std::cout << message;
		throw message;
	}
}