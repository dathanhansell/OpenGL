#pragma once
#include <vector>
#include "tString.h"
class Node
{
	
	int item;
	
public:
	tString name = "";
	Node();
	Node(tString asName);
	Node(tString asName, int asItem);
	void AddChild(Node asNode);
	void AddChild(tString asName);
	void RemoveChild(Node asNode);
	void RemoveChild(tString asName);
	void RemoveAllChildren();
	void ChangeItem(int asItem);
	std::vector<Node> children;
	int GetItem();
	~Node();
};
class Tree:public Node
{
public:
	Tree();
	~Tree();
};



