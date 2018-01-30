#include "Tree.h"
	Tree::Tree()
	{
		
	}
	Tree::~Tree()
	{
		RemoveAllChildren();
		
	}
	Node::Node() {
		name = "noName";
	}
	Node::Node(tString asName) {
		name = asName;
	}
	Node::Node(tString asName, int asitem) {
		name = asName;
		item = asitem;
	}
	void Node::AddChild(Node asnode) {
		children.push_back(asnode);
	}
	void Node::RemoveChild(Node asnode) {
		RemoveChild(asnode.name);
	}

	void Node::RemoveAllChildren() {
		for (int i = 0; i < children.size(); i++) {
				children.erase(children.begin() + i);
		}
	}

	void Node::AddChild(tString asName) {
		AddChild(Node(asName));
	}
	void Node::RemoveChild(tString asName) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i].name == asName) {
				children.erase(children.begin() + i);
				break;
			}
		}
	}

	void Node::ChangeItem(int asItem) {
		item = asItem;
	}
	int Node::GetItem() {
		return item;
	}
	Node::~Node() {
		RemoveAllChildren();
		
	}