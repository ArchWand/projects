/* ASSUMPTIONS:
1.When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iostream>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(nullptr) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
	BPlusTreeNode<T>* root_;
	unsigned int b_;

	void copy(BPlusTree<T>& other);
	void destroy();

	void split(BPlusTreeNode<T>* node);
	void insert(const T& key, BPlusTreeNode<T>* node);
	void print_sideways(std::ostream& out, BPlusTreeNode<T>* node, int level);

public:
	BPlusTree(unsigned int b) : root_(nullptr), b_(b) {}

	void insert(T val);
	BPlusTreeNode<T>* find(const T& val);

	void print_sideways(std::ostream& out_f);
	void print_BFS(std::ostream& out_f);
};

template <class T>
void BPlusTree<T>::insert(T val) {
	if (!root_) {
		root_ = new BPlusTreeNode<T>();
		root_->keys.push_back(val);
		return;
	}

	this->insert(val, root_);
}

// Find
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key) {
	if (root_ == nullptr) { return nullptr; }

	BPlusTreeNode<T>* curr = root_;

	while (!curr->is_leaf()) {
		bool found = false;
		for (unsigned i = 0; i < curr->keys.size(); i++) {
			if (key < curr->keys[i]) {
				curr = curr->children[i];
				found = true;
				break;
			}
		}
		if (!found) { curr = curr->children.back(); }

		if (curr == nullptr) { return nullptr; }
		if (curr->contains(key)) { return curr; }
	}

	return nullptr;
}

template <class T>
void BPlusTree<T>::insert(const T& key, BPlusTreeNode<T>* node) {
	if (node->is_leaf()) {
		node->keys.push_back(key);
		std::sort(node->keys.begin(), node->keys.end());
		split(node);
		return;
	}
	for (unsigned i = 0; i < node->keys.size(); ++i) {
		if (key < node->keys[i]) {
			insert(key, node->children[i]);
			split(node->children[i]);
			return;
		}
	}
	insert(key, node->children[-1]);
	split(node->children[-1]);
}

template <class T>
void BPlusTree<T>::split(BPlusTreeNode<T>* node) {
	if (node->keys.size() < b_) return; 

	if (node == root_) {
		root_ = new BPlusTreeNode<T>();
		node->parent = root_;
		root_->children.push_back(node);
	}

	BPlusTreeNode<T>* new_node = new BPlusTreeNode<T>();
	new_node->parent = node->parent;

	int index = 0;
	for (unsigned i = 0; i < node->parent->children.size(); i++)
		if (node->parent->children[i] == node) {
			index = i;
			break;
		}

	if (node->is_leaf()) {
		for (unsigned i = node->keys.size() / 2; i < node->keys.size(); ++i)
			new_node->keys.push_back(node->keys[i]);

		node->keys.erase(node->keys.begin() + node->keys.size() / 2, node->keys.end());

		node->parent->children.insert(node->parent->children.begin() + index + 1, new_node);

		split(node->parent);
	} else {
		node->parent->keys.push_back(node->keys[node->keys.size() / 2]);
		for (unsigned i = (node->keys.size() / 2) + 1; i < node->keys.size(); ++i)
			new_node->keys.push_back(node->keys[i]);

		node->keys.erase(node->keys.begin() + node->keys.size() / 2, node->keys.end());

		node->parent->children.insert(node->parent->children.begin() + index + 1, new_node);

		for (unsigned i = 0; i < node->children.size(); ++i)
			if (node->children[i]->keys[0] > node->keys[-1])
				index = i;

		for (unsigned i = index; i < node->children.size(); ++i)
			new_node->children.push_back(node->children[i]);
	}
}

template<class T>
void BPlusTree<T>::print_sideways(std::ostream& out, BPlusTreeNode<T>* node, int level) {
	if (node == nullptr) { return; }

	// Print first child
	print_sideways(out, node->children[0], level + 1);

	// Print yourself
	out << '\t' << node->keys[0] << std::endl;
	for (unsigned i = 1; i < node->keys.size(); i++) {
		out << ',' << node->keys[i];
	}
	out << std::endl;

	// Print children
	for (unsigned i = 1; i < node->children.size(); i++) {
		print_sideways(out, node->children[i], level + 1);
	}
}

template <class T>
void BPlusTree<T>::print_sideways(std::ostream& out) {
	if (root_ == nullptr) { return; }

	for (unsigned i = 0; i < root_->children.size(); i++) {
		print_sideways(out, root_->children[i], 0);
	}
}

template <class T>
void BPlusTree<T>::print_BFS(std::ostream& /* out */) {
}

#endif
