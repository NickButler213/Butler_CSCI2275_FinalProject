# include "Tree.h"
# include "skipList.h"
# include <iostream>
# include <fstream>
using namespace std;

int main() {
	srand(time(NULL)); // for a random seed each time when building skip list

	int dataSize;
	Tree tree;
	List list;
	ofstream file;

	list = List("bigData.txt",dataSize);
	tree = Tree("bigData.txt",dataSize);

	// data for percent connected versus probability of failure
	// uses a constant data size of 10000 words
	dataSize = 10000;
	double data[14] = {0};
	for (int t = 0; t < 10; t++) { // run for 10 different skip lists
		list = List("bigData.txt",dataSize);
		double prob = 0.05;
		for (int i = 0; i < 14; i++) {
			int count{};
			double trials = 1000;
			for (int j = 0; j < trials; j++)
				count += list.failSim(prob);
			data[i] += count;
			prob += 0.05;
		}
	}
	file = ofstream("connect_vs_prob.txt");
	file << "prob,connected" << endl;
	for (int i = 0; i < 14; i++)
		file << 5*i+5 << ',' << data[i]/10000. << endl;
	file.close();
}
