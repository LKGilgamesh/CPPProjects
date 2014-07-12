#include "BST.h"
#include <iostream>
Node::Node(int sumval){
	data = sumval;
	left = NULL;
	right = NULL;
}


void Node::insert(int sumval){
	if(data > sumval){ //if current node value is greater than insert node value
		if(left == NULL){
			Node *tempNode = new Node(sumval);
			left = tempNode;
		}
		else{
			left->insert(sumval);
		}
	}
	if(data < sumval){ //if current node value is smaller than insert node value
		if(right == NULL){
			Node *tempNode = new Node(sumval);
			right = tempNode;
		}
		else{
			right->insert(sumval);
		}
	}
}
void Node::print_inorder(){
	if(left) 
		left->print_inorder();
	std::cout << data << " ";
	if(right)
		right->print_inorder();
}
bool Node::find(int sumval){
	if(data == sumval)
		return true;
	else if(data > sumval){ //if current node value is greater than insert node value
		if(left == NULL){
			return false;
		}
		else{
			left->find(sumval);
		}
	}
	else if(data < sumval){ //if current node value is smaller than insert node value
		if(right == NULL){
			return false;
		}
		else{
			right->find(sumval);
		}
	}
	else{
		std::cout << "something went wrong" << std::endl;
		return false;
	}
}
void Node::print_from_value(int sumval){
	if(left) 
		left->print_from_value(sumval);
	if(data < sumval)
		std::cout << data << " ";
	if(right)
		right->print_from_value(sumval);
}
void Node::remove(int sumval,Node *parent){
	if (data > sumval){
		left->remove(sumval, left);
	}
	else if (data < sumval){
		right->remove(sumval, right);
	}
	else if (data == sumval){
		if (right == NULL && left == NULL){
			parent = NULL;
			deleteNode();
			
		}
		else if (right && left){
			data = right->findSuccessor();
			right->remove(data,right);
		}
		else if (right || left){
			if (right){
				parent = right;
				deleteNode();
			}
			else if (left){
				parent = left;
				deleteNode();
			}
		}
	}
}
void Node::clearNodes(){
	if (left)
		left->clearNodes();
	if (right)
		right->clearNodes();
	deleteNode();
}
void Node::deleteNode(){
	delete this;
}
int Node::findSuccessor(){
	if (left)
		left->findSuccessor();
	else
		return data;
}
void Node::nodeValue(int &sum){
	if (left)
		left->nodeValue(sum);
	if (right)
		right->nodeValue(sum);
	sum += data;
	
}
void Node::nodeSize(int &size){
	if (left)
		left->nodeSize(size);
	if (right)
		right->nodeSize(size);
	size++;
}
BST::BST(){
	root = NULL;
	//current = NULL;
}
void BST::insert(int sumval){
	if(root == NULL){
		Node *tempNode = new Node(sumval);
		root = tempNode;
	}
	else
		root->insert(sumval);
}
void BST::print_inorder(){
	if(root != NULL){
		root->print_inorder();
	}
	else{
		std::cout << "Tree empty" << std::endl;
	}
}
bool BST::find(int sumval){
	return root->find(sumval);
}
void BST::print_from_value(int sumval){
	if(root != NULL){
		root->print_from_value(sumval);
	}
	else{
		std::cout << "Tree empty" << std::endl;
	}
}
void BST::remove(int sumval){
	root->remove(sumval, root);
}
void BST::clear(){
	root->clearNodes();
	root = NULL;
}
BST::~BST(){
	clear();
}
int BST::sum(){
	int sumOfNodes = 0;
	if (root){
		root->nodeValue(sumOfNodes);
		return sumOfNodes;
	}
	else
		return sumOfNodes;
}
int BST::size(){
	int sizeOfBST = 0;
	if (root){
		root->nodeSize(sizeOfBST);
		return sizeOfBST;
	}
	else
		return sizeOfBST;
}
float BST::average(){
	float average = (float)(sum() / size());
	return average;
}

