#include <iostream>
#include <queue>

int main(void) {
	std::queue<std::string> q;
	q.push("a");
	q.push("b");
	q.push("c");
	
	// q.pop();/
	std::string q2 = q.front();
	std::cout << q2 << std::endl;
}