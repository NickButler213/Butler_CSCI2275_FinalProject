# include <string>
using namespace std;

struct listNode {
	string key{};
	int count{};
	listNode* prev = nullptr;
	listNode* next = nullptr;
	listNode* below = nullptr;
	listNode* above = nullptr;
	bool visited = false;
	bool failed = false;
	listNode() {}
	listNode(string sKey) {
		key = sKey;
		count = 1;
	}
};

class List {
	private:
		listNode* head;
		int maxLevel{};
	public:
		List();
		List(string,int);
		int levelGenerator();
		listNode* search(string);
		double searchAll();
		void insert(string);
		void remove(string);
		void printInOrder();
		void removeAll();
		bool isConnected();
		bool failSim(double);
		void printPretty();

		int countFailed();
};
