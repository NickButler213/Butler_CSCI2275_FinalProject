# include <iostream>
# include <fstream>
# include <stack>
# include "skipList.h"
# include <vector>
# include <ctime>
using namespace std;

List::List() {
	head = new listNode;
	maxLevel = 0;
}

// reads in a file, size is the number of words you wish to read
// the file bigData.txt has a maximum of 1,000,000 words in it
List::List(string fileName, int size) {
	head = new listNode;
	maxLevel = 0;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Invalid Filename" << endl;
		return;
	}
	string word;
	for (int i = 0; i < size and file >> word; i++)
		insert(word);
	file.close();
}

// this is the "coin flip".  It determines the height
// that a new node will be inserted at
int List::levelGenerator() {
	int l{};
	while (rand()%2)
		l++;
	return l;
}

// simple search function.  Pushes right through the list
// as much as possible before having to drop down a level
listNode* List::search(string key) {
	listNode* node = head;
	while (node) {
		if (!node->next) {
			node = node->below;
		} else if (key == node->next->key) {
			return node->next;
		} else if (key > node->next->key) {
			node = node->next;
		} else if (key < node->next->key) {
			node = node->below;
		}
	}
	return nullptr;
}

// This is the most complication function it is broken into parts
// for ease of understanding
void List::insert(string key) {
	// If the node already exists adjust the count throught the levels
	listNode* node = search(key);
	if (node) {
		while (node) {
			node->count++;
			node = node->below;
		}
		return;
	}

	int l = levelGenerator(); // get random level
	// adjust height of list if new node will be higher than current max level
	if (l > maxLevel) {
		listNode* newHead = new listNode;
		node = newHead;
		maxLevel++;
		while (maxLevel < l) {
			listNode* belowNode = new listNode;
			node->below = belowNode;
			belowNode->above = node;
			node = node->below;
			maxLevel++;
		}
		node->below = head;
		head->above = node;
		head = newHead;
	}
	// make l new nodes linked below eachother
	listNode* newNode = new listNode(key);
	node = newNode;
	for (int i = 0; i < l; i++) {
		listNode* belowNode = new listNode(key);
		node->below = belowNode;
		belowNode->above = node;
		node = node->below;
	}

	// drop node representing head to proper level
	node = head;
	for (int i = l; i < maxLevel; i++)
		node = node->below;

	// insert process
	while (node) {
		while (!newNode->prev) {
			if (!node->next) {
				node->next = newNode;
				newNode->prev = node;
			} else if (node->next->key < key) {
				node = node->next;
			} else if (node->next->key > key) {
				newNode->next = node->next;
				newNode->prev = node;
				node->next->prev = newNode;
				node->next = newNode;
			}
		}
		node = node->below;
		newNode = newNode->below;
	}
}

// works similar to search where the function push as much as
// it can before it drops down a level
void List::remove(string key) {
	listNode* node = search(key);
	while (node) {
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		listNode* delNode = node;
		node = node->below;
		delete delNode;
	}
}

//prints by dropping to level 0 then reading node by node
void List::printInOrder() {
	listNode* node = head;
	while (node->below)
		node = node->below;
	node = node->next;
	while (node) {
		cout << node->key << ',' << node->count << endl;
		node = node->next;
	}
}

// stores all keys in a vector, then removes them all using the
// remove function.
// Returns the time in milliseconds of run time
double List::removeAll() {
	vector<string> keys;
	listNode* node = head;
	while (node->below)
		node = node->below;
	while (node->next) {
		node = node->next;
		keys.push_back(node->key);
	}
	clock_t start = clock();
	for (string key : keys)
		remove(key);
	return double(clock()-start)/CLOCKS_PER_SEC*1000; // time in ms
}

// stores all keys in a vector, then search them all using the
// search function.
// Returns the time in milliseconds of run time
double List::searchAll() {
	vector<string> keys;
	listNode* node = head;
	while (node->below)
		node = node->below;
	while (node->next) {
		node = node->next;
		keys.push_back(node->key);
	}
	clock_t start = clock();
	for (string key : keys)
		search(key);
	return double(clock()-start)/CLOCKS_PER_SEC*1000; // time in ms
}

// used for the failure simulation
bool probability(double prob) {
	double randNum = (double) rand()/RAND_MAX;
	if (randNum <= prob)
		return true;
	return false;
}

// determines if by starting at the head, the last node can be recoved
// this is a DFS and it skip around node where failed == true
bool List::isConnected() {
	listNode* node = head;
	while (node->below)
		node = node->below;
	while (node->next)
		node = node->next;
	node->failed = false;
	string lastElement = node->key;
	node = head;
	stack<listNode*> s;
	node->failed = true;
	s.push(node);
	while (!s.empty()) {
		node = s.top();
		s.pop();
		if (node->key == lastElement)
			return true;
		if (node->prev and !node->prev->failed and node->prev->key != "") {
			node->prev->failed = true;
			s.push(node->prev);
		}
		if (node->next and !node->next->failed and node->next->key != "") {
			node->next->failed = true;
			s.push(node->next);
		}
		if (node->below and !node->below->failed and node->below->key != "") {
			node->below->failed = true;
			s.push(node->below);
		}
		if (node->above and !node->above->failed and node->above->key != "") {
			node->above->failed = true;
			s.push(node->above);
		}
	}
	return false;
}

// simulate failure of multiple node in the skip list
// parameter is a double between 0 and 1 which gives the
// probability than any given node will fail
bool List::failSim(double prob) {
	// Step 1: choose which nodes to have fail
	for (listNode* level = head; level->below; level = level->below) {
		listNode* node = level->next;
		while (node) {
			if (probability(prob))
				node->failed = true;
			node = node->next;
		}
	}
	// Step 2: see if the list head is still connected to the
	// last node
	bool connected = isConnected();
	// Step 3: reset nodes to not failed
	for (listNode* level = head; level; level = level->below) {
		listNode* node = level;
		while (node) {
			node->failed = false;
			node = node->next;
		}
	}
	return connected;
}

// used to see the functionality of the skiplist
// inly use this on small data sets
void List::printPretty() {
	listNode* row = head;
	for (int i = maxLevel; i >= 0; i--) {
		cout << i << ": ";
		listNode* column = row->next;
		while (column) {
			cout << column->key << "->";
			column = column->next;
		}
		cout << endl;
		row = row->below;
	}
}
