#include "Tree.h"
template <typename T>
	Tree<T>::Tree()
	{
		root = {"_root"};
	}
	template <typename T>
	Tree<T>::~Tree()
	{
		root.RemoveAllChildren();
		root.~Node();
	}
	template <typename T>
	Node<T> Tree<T>::GetRootNode() {
		return root;
	}
	template <typename T>
	void Tree<T>::AddBaseNode(tString asName) {
		root.AddChild(asName);
	}

	template <typename T>
	void Tree<T>::AddBaseNode(tString asName, T* asitem) {
		root.AddChild(Node<T>(asName, asitem));
	}
	template <typename T>
	void Tree<T>::AddBaseNode(Node<T> asNode) {
		root.AddChild(asNode);
	}
	template <typename T>
	Node<T>::Node() {
		name = "noName";
	}
	template <typename T>
	Node<T>::Node(tString asName) {
		name = asName;
	}
	template <typename T>
	Node<T>::Node(tString asName, T* asitem) {
		name = asName;
		item = asitem;
	}
	template <typename T>
	void Node<T>::AddChild(Node asnode) {
		children.push_back(asnode);
	}
	template <typename T>
	void Node<T>::RemoveChild(Node asnode) {
		RemoveChild(asnode.name);
	}

	template <typename T>
	void Node<T>::RemoveAllChildren() {
		for (int i = 0; i < children.size(); i++) {
				children.erase(children.begin() + i);
		}
	}

	template <typename T>
	void Node<T>::AddChild(tString asName) {
		AddChild(Node(asName));
	}
	template <typename T>
	void Node<T>::RemoveChild(tString asName) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i].name == asName) {
				children.erase(children.begin() + i);
				break;
			}
		}
	}

	template <typename T>
	void Node<T>::ChangeItem(T* asItem) {
		item = asItem;
	}
	template <typename T>
	T* Node<T>::GetItem() {
		return item;
	}
	template <typename T>
	Node<T>::~Node() {
		RemoveAllChildren();
		delete item;
	}