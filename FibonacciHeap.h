// MARK: Node declaration
/*Node for a Fibonacci Heap*/
struct Node {
	Node* prev;
	Node* next;
	Node* child;
	Node* parent;

	int degree;
	bool bChildCut;
	int value;

	Node(int);
};

// MARK: Fibonacci Heap declaration

class FibonacciHeap {
private:
	Node* fHeap;

public:
	FibonacciHeap();
	~FibonacciHeap();

	void insert(int);
	void meld(FibonacciHeap*);
	void increaseKey(Node*, int);

	int getMaximum();
	int removeMaximum();

private:
	Node* _meld(Node* a, Node* b);
	Node* _cut(Node*, Node*);
	Node* _removeMaximum(Node*);
	Node* _increaseKey(Node*, Node*, int);

	void _deleteHeap(Node*);
	void _addChild(Node*, Node*);
	void _unParentAll(Node*);
};