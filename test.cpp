# include "Tree.h"
# include "skipList.h"
# include <iostream>
# include <ctime>
using namespace std;

int main() {
	srand(time(NULL));

	Tree tree("testWords.txt",100);
	List list("testWords.txt",100);

	cout << "Tree" << endl;
	tree.printInOrder();
	cout << "\nSkip List" << endl;
	list.printInOrder();

	cout << "\nSkip List Structure" << endl;
	list.printPretty();
}
