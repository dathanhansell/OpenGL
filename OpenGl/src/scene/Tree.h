#pragma once
#include <vector>
#include "tString.h"
template <class T>
class Node
{
	std::vector<Node> children;
	T* item;
	tString name;
public:
	Node();
	Node(tString asName);
	Node(tString asName, T* asItem);
	void AddChild(Node asNode);
	void AddChild(tString asName);
	void RemoveChild(Node asNode);
	void RemoveChild(tString asName);
	void RemoveAllChildren();
	void ChangeItem(T* asItem);
	std::vector<Node> GetChildren();
	T* GetItem();
	~Node();
};
template <typename T>
class Tree:public Node<T>
{
public:
	Tree();
	~Tree();
};



