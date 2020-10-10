struct BTNode {
	string data;
	BTNode * left;
	BTNode * right;
	BTNode * parent;
};

struct Node {
	BTNode * data;
	Node * next;
};
