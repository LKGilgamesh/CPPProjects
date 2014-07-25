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
}
void Node::print_from_value(int sumval){
	if(left) 
		left->print_from_value(sumval);
	if(data < sumval)
		std::cout << data << " ";
	if(right)
		right->print_from_value(sumval);
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

