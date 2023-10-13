#ifndef _PREFIX_TREE_H_
#define _PREFIX_TREE_H_

#include <iostream>
#include <string>

// Prefix tree class to perform checks quicker
class PrefixTree {
private:
	PrefixTree* children[26];

public:
	PrefixTree() {
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}

	PrefixTree* operator[](char c) {
		return children[c - 'a'];
	}

	~PrefixTree() {
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) { delete children[i]; } }
	}

	bool is_leaf() {
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) { return false; }
		}
		return true;
	}

	// Don't add duplicate words, always keeping the shortest word
	void add(std::string word, unsigned i) {
		if (i == word.length()) {
			// Delete any possible unnecessary children
			for (int j = 0; j < 26; j++) {
				if (children[j] != nullptr) {
					delete children[j];
					children[j] = nullptr;
				}
			}
			return;
		}

		int c = (int)(word[i] - 'a');
		if (children[c] == nullptr) {
			children[c] = new PrefixTree();
			children[c]->add(word, i + 1);
		} else if (!children[c]->is_leaf()) {
			children[c]->add(word, i + 1);
		}
	}

	void print(int depth) {
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) {
				for (int j = 0; j < depth; j++) {
					std::cout << "  ";
				}
				std::cout << (char) (i + 'a') << std::endl;
				children[i]->print(depth + 1);
			}
		}
	}
};

#endif

