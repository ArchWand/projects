/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

#include <iostream>
#include <vector>
#include <algorithm>

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
class BPlusTree{
private:
	int max_degree;
	BPlusTreeNode<T>* root;
public:
	BPlusTree(int max_degree): max_degree(max_degree), root(nullptr) {};
	~BPlusTree();
	void insert(const T& key);
	BPlusTreeNode<T>* find(const T& key);
	void print_sideways(std::ostream& out);
	void print_BFS(std::ostream& out);

private:
	// Helper methods
	void print_sideways(std::ostream& out, BPlusTreeNode<T>* node, int level);
	void split(BPlusTreeNode<T>* node);
	void insert(const T& key, BPlusTreeNode<T>* node);
};

// Destructor
template <class T>
BPlusTree<T>::~BPlusTree() {
	if (root == nullptr) { return; }

	// Delete all children
	for (unsigned i = 0; i < root->children.size(); i++) {
		delete root->children[i];
	}
}

// Find
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key) {
	if (root == nullptr) { return nullptr; }

	BPlusTreeNode<T>* curr = root;

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

// Split
template <class T>
void BPlusTree<T>::split(BPlusTreeNode<T>* node) {
	// Check if node needs to be split
	if (node->keys.size() < (unsigned)max_degree) { return; }

	// Handle splitting root node
	if (node == root) {
		// Create new root
		root = new BPlusTreeNode<T>();
		// Set parent
		node->parent = root;
		// Add node as child
		root->children.push_back(node);
	}

	// Create new node
	BPlusTreeNode<T>* new_node = new BPlusTreeNode<T>();
	// Set parent
	new_node->parent = node->parent;

	// Find index of node in parent
	int index = 0;
	for (unsigned i = 0; i < node->parent->children.size(); i++) {
		if (node->parent->children[i] == node) {
			index = i;
			break;
		}
	}

	// Move keys to new node
	for (unsigned i = node->keys.size() / 2; i < node->keys.size(); i++) {
		new_node->keys.push_back(node->keys[i]);
	}

	// Remove keys from old node
	node->keys.erase(node->keys.begin() + node->keys.size() / 2, node->keys.end());

	// Insert new node into parent
	node->parent->children.insert(node->parent->children.begin() + index + 1, new_node);

	// Insert key into parent
	node->parent->keys.insert(node->parent->keys.begin() + index, new_node->keys[0]);

	// If node is not a leaf, remove the duplicate key
	if (!node->is_leaf()) {
		node->keys.erase(node->keys.begin(), node->keys.begin() + 1);
	}
}

// Insert helper
template <class T>
void BPlusTree<T>::insert(const T& key, BPlusTreeNode<T>* node) {
	// Handle leaf node base case
	if (node->is_leaf()) {
		// Insert key
		node->keys.push_back(key);
		// Sort keys
		std::sort(node->keys.begin(), node->keys.end());

		// Split node if necessary
		split(node);
		return;
	}

	// Find child to insert into
	for (unsigned i = 0; i < node->keys.size(); i++) {
		if (key < node->keys[i]) {
			// Insert key
			insert(key, node->children[i]);
			// Split node if necessary
			split(node->children[i]);
			break;
		}
	}

}

// Insert
template <class T>
void BPlusTree<T>::insert(const T& key) {
	// Handle empty tree
	if (root == nullptr) {
		root = new BPlusTreeNode<T>();
		root->keys.push_back(key);
		return;
	}

	// Insert key
	insert(key, root);

	// Split root if necessary
	split(root);
}

// Printing
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
	if (root == nullptr) { return; }

	for (unsigned i = 0; i < root->children.size(); i++) {
		print_sideways(out, root->children[i], 0);
	}
}

template <class T>
void BPlusTree<T>::print_BFS(std::ostream& /* out */) {
}

#endif
