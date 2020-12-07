# include <iostream>
# include <fstream>
# include <iomanip>
# include "Tree.h"
# include <stack>
# include <ctime>
# include <vector>
using namespace std;

Tree::Tree() {
	root = nullptr;
}
// reads in a file, size is the number of words you wish to read
// the file bigData.txt has a maximum of 1,000,000 words in it
Tree::Tree(string fileName, int size) {
	root = nullptr;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Invalid File" << endl;
	} else {
		string word;
		for (int i = 0; i < size and file >> word; i++)
			insert(word);
	}
	file.close();
}

// iterative insert into BST
void Tree::insert(string key) {
	treeNode* node = root;
	treeNode* newNode = new treeNode(key);
	if (!node) {
		root = newNode;
		return;
	}
	while (node) {
		if (key < node->key) {
			if (!node->left) {
				node->left = newNode;
				newNode->parent = node;
				node = nullptr;
			} else {
				node = node->left;
			}
		} else if (key > node->key) {
			if (!node->right) {
				node->right = newNode;
				newNode->parent = node;
				node = nullptr;
			} else {
				node = node->right;
			}
		} else {
			node->count++;
			node = nullptr;
		}
	}
}

// iterative search of BST
treeNode* Tree::search(string key) {
	treeNode* node = root;
	while (node) {
		if (key < node->key)
			node = node->left;
		if (key > node->key)
			node = node->right;
		if (key == node->key)
			return node;
	}
	return nullptr;
}

// iterative removal of node from BST
void Tree::remove(string key) {
	treeNode* node = search(key);
	if (!node)
	        return;
	// if n has no chilren
	if (!node->right and !node->left) {
	        if (node != root) {
	                if (node->parent->left == node) {
	                        node->parent->left = nullptr;
	                } else if (node->parent->right == node) {
	                        node->parent->right = nullptr;
	                }
	        }
	// if node has only a right child
	} else if (node->right and !node->left) {
	        if (node == root) {
	                root = node->right;
			root->parent = nullptr;
	        } else {
	                node->right->parent = node->parent;
			if (node->parent->right == node)
		                node->parent->right = node->right;
			if (node->parent->left == node)
				node->parent->left = node->right;
	        }
	// if node only has a left child
	} else if (node->left and !node->right) {
	        if (node == root) {
	                root = node->left;
			root->parent = nullptr;
	        } else {
	                node->left->parent = node->parent;
			if (node->parent->right == node)
		                node->parent->right = node->left;
			if (node->parent->left == node)
				node->parent->left = node->left;
	        }
        // if node has both children
        } else if (node->right and node->left) {
                // replace n with the minvalue of the right subt>
                // find min node on right side
                treeNode* min = node->right;
                while (min->left) {
                        min = min->left;
                }
                // replace value at node
                node->key = min->key;
		node->count = min->count;
                if (min->parent->left == min) {
                        min->parent->left = min->right;
                } else if (min->parent->right == min) {
                        min->parent->right = min->right;
                }
                if (min->right)
                        min->right->parent = min->parent;
                node = min;
        }
	if (node != root) {
	        delete node;
        	node = nullptr;
	} else {
		root = nullptr;
	}
}

// recursive public print function
void Tree::printInOrder() {
	if (root)
		printInOrder(root);
}

// recursive private print function
void Tree::printInOrder(treeNode* node) {
	if (node->left)
		printInOrder(node->left);
	cout << node->key << ',' << node->count << endl;
	if (node->right)
		printInOrder(node->right);
}

// removes all nodes from BST and returns the run time
double Tree::removeAll() {
	vector<string> keys;
	stack<treeNode*> s;
	if (!root) return 0;
	treeNode* node = root;
	s.push(node);
	while (!s.empty()) {
		node = s.top();
		s.pop();
		keys.push_back(node->key);
		if (node->left)
			s.push(node->left);
		if (node->right)
			s.push(node->right);

	}
	clock_t start = clock();
	while (root)
		remove(root->key);
	return double(clock()-start)/CLOCKS_PER_SEC*1000; // in ms
}

// searches for all keys in BST and returns the run time
double Tree::searchAll() {
	vector<string> keys;
	stack<treeNode*> s;
	if (!root) return 0;
	treeNode* node = root;
	s.push(node);
	while (!s.empty()) {
		node = s.top();
		s.pop();
		keys.push_back(node->key);
		if (node->left)
			s.push(node->left);
		if (node->right)
			s.push(node->right);

	}
	clock_t start = clock();
	for (string key : keys)
		search(key);
	return double(clock()-start)/CLOCKS_PER_SEC*1000; // time in ms
}
