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
	virtual void AddChild(Node* asNode);
	virtual void AddChild(tString asName);
	virtual void RemoveChild(Node* asNode);
	virtual void RemoveChild(tString asName);
	virtual void RemoveAllChildren();
	virtual void ChangeItem(int asItem);
	virtual void ChangeParent(Node* newParent);
	virtual bool IsAncestor(Node* asNode);
	virtual bool IsChild(Node* asNode);
	virtual Node* GetChild(tString asName);
	Node* parent;
	std::vector<Node*> children;
	int GetItem();
	~Node();
};
class Tree:public Node
{
public:
	Tree();
	~Tree();
};



