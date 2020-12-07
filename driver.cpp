# include "Tree.h"
# include "skipList.h"
# include <iostream>
# include <fstream>
# include <ctime>
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
	double data[14] = {0};
	for (int t = 0; t < 10; t++) { // run for 10 different skip lists
		list = List("bigData.txt",10000);
		double prob = 0.0;
		for (int i = 0; i < 14; i++) {
			int count{};
			for (int j = 0; j < 1000; j++)
				data[i] += list.failSim(prob);
			prob += 0.05;
		}
	}
	file = ofstream("connectivity.txt");
	file << "prob,connected" << endl;
	for (int i = 0; i < 14; i++) {
		file << 5*i << ',' << data[i]/100. << endl;
		data[i] = 0;
	}
	file.close();


	// data for percent connected versus data size in words read
	// tested at probability 0.05, 0.1, 0.15, 0.2
	file = ofstream("inputSize.txt");
	file << "size,5%,10%,15%,20%" << endl;
	dataSize = 0;
	for (int i = 0; i < 14; i++) { // run 14 different sizes
		dataSize += 50000;
		int count5{}, count10{}, count15{}, count20{};
		for (int j = 0; j < 10; j++) { // run 10 different skip lists for each size
			list = List("bigData.txt",dataSize);
			for (int k = 0; k < 1000; k++)
				count5 += list.failSim(0.05);
			list = List("bigData.txt",dataSize);
			for (int k = 0; k < 1000; k++)
				count10 += list.failSim(0.1);
			list = List("bigData.txt",dataSize);
			for (int k = 0; k < 1000; k++)
				count15 += list.failSim(0.15);
			list = List("bigData.txt",dataSize);
			for (int k = 0; k < 1000; k++)
				count20 += list.failSim(0.2);
		}
		file << dataSize << ',' << count5/100. << ',' << count10/100. << ',' << count15/100. << ',' << count20/100. << endl;
	}
	file.close();

	// data for insert, search, and removal times of both the skip list and the BST
	ofstream fileInsert ("insertTime.txt");
	fileInsert << "list,tree" << endl;
	ofstream fileSearch ("searchTime.txt");
	fileSearch << "list,tree" << endl;
	ofstream fileRemove ("removeTime.txt");
	fileRemove << "list,tree" << endl;
	for (int i = 0; i < 10; i++) {

		// insert time for skip list
		clock_t start = clock();
		List list = List("bigData.txt",(i+1)*100000);
		double time = double(clock()-start)/CLOCKS_PER_SEC;
		fileInsert << time << ','; // in seconds

		// insert time for BST
		start = clock();
		tree = Tree("bigData.txt",(i+1)*100000);
		time = double(clock()-start)/CLOCKS_PER_SEC;
		fileInsert << time << endl; // in seconds

		// time search and remove
		fileSearch << list.searchAll() << ',';
		fileSearch << tree.searchAll() << endl;
		fileRemove << list.removeAll() << ',';
		fileRemove << tree.removeAll() << endl;
	}
}
