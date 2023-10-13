#ifndef _WORD_SET_H_
#define _WORD_SET_H_

#include <algorithm>
#include <string>
#include <vector>
// #include <set>

// Clean up the type of the representation of WordSet
class EnumString {
private:
	std::string s;
	std::vector<int> i;

public:
	// Constructors
	EnumString() {
		s = std::string();
		i = std::vector<int>();
	}

	EnumString(std::string s) {
		this->s = s;
		i = std::vector<int>();
	}

	EnumString(std::string s, int index) {
		this->s = s;
		i = std::vector<int>();
		i.push_back(index);
	}

	// Setters
	void set_string(std::string s) {
		this->s = s;
	}

	void add_index(int index) {
		i.push_back(index);
	}

	// Reference getters
	// String
	const std::string& string() const {
		return s;
	}

	// Indices
	const std::vector<int>& indices() const {
		return i;
	}
};

class WordSet {
private: // Representation

	// Function to sort set in increasing order of length
	static bool sorter(const std::string &a, const std::string &b) {
		return a.length() > b.length();
	}

	// Indexed by letter
	std::vector< // A set of words which contain the index letter
		EnumString // A word with the locations of the index letter marked
		> words[26];
public:
	// Constructor
	WordSet(std::vector<std::string> &word_list) {
		// Sort in increasing order of length, for earlier returns
		std::sort(word_list.begin(), word_list.end(), sorter);

		// Initialize the vectors
		for (int i = 0; i < 26; i++) {
			words[i] = std::vector<EnumString>();
		}

		// Add the words to the set
		for (unsigned i = 0; i < word_list.size(); i++) {
			std::string word = word_list[i];

			// Add the word to the set
			for (unsigned j = 0; j < word.length(); j++) {
				// Check for valid character
				if (word[j] < 'a' || word[j] > 'z') { continue; }

				int c = word[j] - 'a';
				// Check if the word is already in the set
				bool found = false;
				for (unsigned k = 0; k < words[c].size(); k++) {
					if (words[c][k].string() == word) {
						// Add the index
						words[c][k].add_index(j);

						// Add mark found
						found = true;
						break;
					}
				}
				if (found) { continue; }

				// If not, add it
				words[c].push_back(EnumString(word, j));
			}
		}
	}

	// Subscript operator
	std::vector<EnumString>& operator[](char c) {
		return words[c - 'a'];
	}

	// Const subscript operator
	const std::vector<EnumString>& operator[](char c) const {
		return words[c - 'a'];
	}
};

#endif

