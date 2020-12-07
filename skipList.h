# include <string>
using namespace std;

struct listNode {
	string key{};
	int count{};
	listNode* prev = nullptr;
	listNode* next = nullptr;
	listNode* below = nullptr;
	listNode* above = nullptr;
	bool failed = false;
	listNode(){}
	listNode(string sKey) {
		key = sKey;
		count = 1;
	}
};

class List {
	private:
		listNode* head = nullptr;
		int maxLevel{};
	public:
		List();
		List(string,int); // reads in a file calls insert(string)
		int levelGenerator(); // generates a random level to insert a new node
		listNode* search(string);
		double searchAll(); // returns run time for searching all nodes
		void insert(string);
		void remove(string);
		void printInOrder();
		double removeAll(); // returns run time for removing all nodes
		bool isConnected(); // returns true is the head of the list can access the last node
		bool failSim(double); // simulates mass failure of nodes
		void printPretty(); // used for showing the functionality of skip lists on small data sets
};
