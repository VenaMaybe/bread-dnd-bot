#include <iostream>
#include <stack>

#include "util/graph.hpp"
#include "world_gen/dungeonNodePath.hpp"

template <typename T>
void printStack(std::stack<T> s) {
	// First one
	std::cout << "first: \t" << s.top()->getObjAtVert().getId() << "\t <- Being expanded" << "\n";
	s.pop();

	// After first
	while (!s.empty()) {
		std::cout << "\t" << s.top()->getObjAtVert().getId() << "\t <- Candidate for further expansion" << "\n";
		s.pop();
	}
	std::cout << std::endl;
}
