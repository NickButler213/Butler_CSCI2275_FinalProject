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
		treeNode* root;
		void printInOrder(treeNode*);
	public:
		Tree();
		Tree(string,int); // loads in a file of words
		treeNode* search(string);
		void insert(string);
		void remove(string);
		void printInOrder();
		void removeAll();
		double searchAll();
};

# endif
