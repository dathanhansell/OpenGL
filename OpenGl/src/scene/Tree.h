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
	void RemoveChild(Node asNode);
	void RemoveAllChildren();
	void AddChild(tString asName);
	void RemoveChild(tString asName);
	void ChangeItem(T* asItem);
	T* GetItem();
	~Node();
};
template <typename T>
class Tree
{
	Node<T> root;
public:
	Node<T> GetRootNode();
	void AddBaseNode(tString asName);
	void AddBaseNode(tString asName, T* asitem);
	void AddBaseNode(Node<T> asNode);
	Tree();
	~Tree();
};



