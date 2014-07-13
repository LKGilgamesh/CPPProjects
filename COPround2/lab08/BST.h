#ifndef BST_H
#define BST_H
class BST;
class Node{
	friend class BST;
public:
	Node(int sumval);
private:
	int data;
	Node *left;
	Node *right;
	void insert(int sumval);
	void print_inorder();
	bool find(int sumval);
	void print_from_value(int sumval);
	bool remove(int sumval,Node *parent);
	void deleteNode();
	int findSuccessor();
	void clearNodes();
	void nodeValue(int &sum);
	void nodeSize(int &size);
};
class BST{
	friend class Node;
public:
	BST();
	void insert(int sumval);
	void print_inorder();
	bool find(int sumval);
	void print_from_value(int sumval);
	void remove(int sumval);
	void clear();
	~BST();
	int sum();
	int size();
	float average();
private:
	Node *root;
	//Node *current;
};

#endif //BST_H