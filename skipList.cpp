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
}

int List::levelGenerator() {
	int l{};
	while (random()%2)
		l++;
	return l;
}

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
	// adjust height is necessary
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

void List::removeAll() {
	listNode* node = head;
	while (node->below)
		node = node->below;
	node = node->next;
	while (node) {
		listNode* delNode = node;
		node = node->next;
		remove(delNode->key);
	}
}

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
	return (clock()-start)*1000./CLOCKS_PER_SEC; // time in ms
}

bool probability(double prob) {
	double randNum = (double) rand()/RAND_MAX;
	if (randNum <= prob)
		return true;
	return false;
}

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

int List::countFailed() {
	int count{};
	for (listNode* level = head; level->below; level = level->below) {
	        listNode* node = level->next;
	        while (node) {
	                if (node->failed)
	                        count++;
	                node = node->next;
	        }
	}
	return count;
}

bool List::failSim(double prob) {
	for (listNode* level = head; level->below; level = level->below) {
		listNode* node = level->next;
		while (node) {
			if (probability(prob))
				node->failed = true;
			node = node->next;
		}
	}
	bool connected = isConnected();
	for (listNode* level = head; level; level = level->below) {
		listNode* node = level;
		while (node) {
			node->failed = false;
			node = node->next;
		}
	}
	return connected;
}

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
