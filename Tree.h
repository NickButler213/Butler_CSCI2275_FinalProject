# include <string>
using namespace std;

# ifndef TREE_H
# define TREE_H

struct treeNode {
	string key{};
	int count{};
	treeNode* parent;
	treeNode* left;
	treeNode* right;
	treeNode() {
		parent = nullptr;
		right  = nullptr;
		left   = nullptr;
	}
	treeNode(string sKey) {
		key = sKey;
		count = 1;
		parent = nullptr;
		right  = nullptr;
		left   = nullptr;
	}
};

class Tree {
	private:
		treeNode* root = nullptr;
		void printInOrder(treeNode*);
	public:
		Tree();
		Tree(string,int); // loads in a file of words
		treeNode* search(string); // iterative search
		void insert(string); // iterative insert
		void remove(string); // iterative remove
		void printInOrder(); // recursive print in order
		double removeAll(); // returns the run time of removing all elements from BST
		double searchAll(); // returns the run time of searching all elements from BST
};

# endif
