#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {
	int v;
	vector<Node*> c;
	Node* p;
	Node() : p(nullptr) {}
};

bool n_compare(Node* a, Node* b) {
	if (a->v != b->v)
		return false;

	for (auto i : a->c) {
		bool FOUND = false;
		for (auto j : b->c) {
			if (i->v == j->v) {
				FOUND = true;
				if (!n_compare(i, j))
					return false;
				break;
			}
		}
		if (!FOUND)
			return false;
	}
	return true;
}

void print(Node *n, int d) {
	for (auto i : n->c) {
		print(i, d+1);
	}
	cout << string(d, ' ') << n->v << endl;
}

int main() {
	string line;
	getline(cin, line);

	Node *root = new Node();
	root->v = stoi(line);
	int n = root->v;
	int digits=0;
	while (n) {
		n = n / 10;
		digits++;
	}

	Node *cur = root;
	for (int i = digits; i < line.size(); ++i) {
		char c = line[i];
		if (isdigit(c)) {
			int val = stoi(line.substr(i));
			int digits = 0;
			int n = val;
			while (n) {
				n = n / 10;
				digits++;
			}
			i += digits-1;
			cur->v = val;
			continue;
		}
		if (c == ' ') continue;
		if (c == ')') cur = cur->p;
		if (c == '(') {
			Node *nn = new Node();
			nn->p = cur;
			cur->c.push_back(nn);
			cur = nn;
		}
	}


	getline(cin, line);

	Node *root2 = new Node();
	root2->v = stoi(line);
	n = root2->v;
	digits=0;
	while (n) {
		n = n / 10;
		digits++;
	}
	cur = root2;
	for (int i = digits; i < line.size(); ++i) {
		char c = line[i];
		if (isdigit(c)) {
			int val = stoi(line.substr(i));
			int digits = 0;
			int n = val;
			while (n) {
				n = n / 10;
				digits++;
			}
			i += digits-1;
			cur->v = val;
			continue;
		}
		if (c == ' ') continue;
		if (c == ')') cur = cur->p;
		if (c == '(') {
			Node *nn = new Node();
			nn->p = cur;
			cur->c.push_back(nn);
			cur = nn;
		}
	}


	if (n_compare(root, root2)) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}


	//while (a->p) a = a->p;
	//while (b->p) b = b->p;
}
