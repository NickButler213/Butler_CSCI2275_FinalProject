// Script for easy recompilation and run or main driver file

# include <fstream>

int main() {
	system("g++ -std=c++11 driver.cpp skipList.cpp Tree.cpp -o driver");
	std::ifstream file("driver");
	if (file.is_open()) {
		system("./driver");
		system("rm driver");
	}
}
