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
	void Node::AddChild(tString asName) {
		AddChild(new Node(asName));
	}
	void Node::AddChild(Node* asnode) {
		children.push_back(asnode);
		asnode->parent = this;
	}
	void Node::RemoveChild(tString asName) {
		RemoveChild(GetChild(asName));
	}
	void Node::RemoveChild(Node* asnode) {

		RemoveChild(asnode->name);
	}
	void Node::RemoveAllChildren() {
		for (int i = 0; i < children.size(); i++) {
			children.erase(children.begin() + i);
		}
	}
	void Node::ChangeParent(Node* newParent) {
		for (int i = 0; i < parent->children.size(); i++) {
			if (children[i]->name == this->name) {
				children.erase(children.begin() + i);
				break;
			}
		}
		parent = newParent;
		parent->AddChild(this);
	}
	void Node::ChangeItem(int asItem) {
		item = asItem;
	}
	bool Node::IsAncestor(Node* asNode) {
		if (IsChild(asNode))return true;
		for (int x = 0; x < asNode->children.size(); x++) {
			return IsAncestor(asNode->children[x]);
		};
	}
	bool Node::IsChild(Node* asNode) {
		for (int i = 0; i < asNode->children.size(); i++) {
			if (asNode->children[i]->name == asNode->name) {
				return true;
			}
		}
		return false;
	}
	Node* Node::GetChild(tString asName) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i]->name == asName) {
				return children[i];
			}
		}
	}
	int Node::GetItem() {
		return item;
	}
	Node::~Node() {
		RemoveAllChildren();
	}