#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->nbColumns = nrCols;
	this->nbLines = nrLines;
	this->root = NULL;
	//Theta(1)
}


int Matrix::nrLines() const {
	return this->nbLines;
	//Theta(1)
}


int Matrix::nrColumns() const {
	return this->nbColumns;
	//Theta(1)
}


TElem Matrix::element(int i, int j) const {///this is in fact bst search
	if ((i < 0 || this->nbLines < i) || (j < 0 || this->nbColumns < i))
		throw exception();

	Node* copyRoot = this->root;
	TElem result = NULL_TELEM;

	while (copyRoot != NULL)///while the node is valid
	{
		if (copyRoot->line == i && copyRoot->column == j)
		{
		result = copyRoot->value;
		copyRoot = NULL;
		}
		else if (i < copyRoot->line || (i == copyRoot->line && j < copyRoot->column)) {///go left
			copyRoot = copyRoot->left;
		}
		else///go right
		{
			copyRoot = copyRoot->right;
		}
	}
	return result;

}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if ((i < 0 || this->nbLines < i) || (j < 0 || this->nbColumns < i))
		throw exception();

	TElem result = NULL_TELEM;
	if (this->root == NULL) {//insert the root
		Node* newNode = new Node;
		newNode->line = i;
		newNode->column = j;
		newNode->value = e;
		newNode->left = NULL;
		newNode->right = NULL;

		this->root = newNode;
	}
	else {///look for the node with line = i and column = j
		Node* copyRoot = this->root;
		Node* prevRoot = NULL;

		while (copyRoot != NULL && (copyRoot->line != i || (copyRoot->line == i && copyRoot->column != j)))///while the node is valid and the value hasn't been found
		{
			prevRoot = copyRoot;///save the parent node

			if (i < copyRoot->line || (i == copyRoot->line && j < copyRoot->column)) {///go left
				copyRoot = copyRoot->left;
			}
			else///go right
			{
				copyRoot = copyRoot->right;
			}
		}

		if (copyRoot != NULL)///if we found the node
		{
			result = copyRoot->value;
			copyRoot->value = e;
		}
		else///if there is no such node, create a new one and add it
		{///copmare it to the parent node, to see where to add it (w.r.t. the parent)
			Node* newNode = new Node;
			newNode->line = i;
			newNode->column = j;
			newNode->value = e;
			newNode->left = NULL;
			newNode->right = NULL;

			if (i < prevRoot->line || (i == prevRoot->line && j < prevRoot->column)) {///add it to the left
				prevRoot->left = newNode;
			}
			else///add it to the right
			{
				prevRoot->right = newNode;
			}
		}
	}

	return result;
}


