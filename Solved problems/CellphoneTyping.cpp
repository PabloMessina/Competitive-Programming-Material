#include <cstdio>
#include <cstring>
using namespace std;

class TrieNode {
public:

	TrieNode** children;
	int visited_count;
	bool has_children;
	bool finishes_word;
	char c;

	TrieNode(char _c) {
		children = new TrieNode*[26];
		has_children = false;
		finishes_word = false;
		for (int i = 0; i < 26; ++i) {
			children[i] = NULL;
		}
		visited_count = 0;
		c = _c;
	}

	~TrieNode() {
		delete[] children;
	}

};

int GlobalStrokesCount;
char buff[90];

void dfs(TrieNode* node, int visited_count, int strokes_count) {

	if (node->visited_count != visited_count) {
		strokes_count++;
	}
	if (node->finishes_word) {
		GlobalStrokesCount += strokes_count;
	}
	if (node->has_children) {
		for (int i = 0; i < 26; ++i) {
			if (node->children[i] == NULL)
				continue;
			dfs(node->children[i], node->visited_count, strokes_count);
		}
	}
}

int main() {

//	setvbuf(stdout, NULL, _IONBF, 0);

	int n;

	while (scanf("%d", &n) == 1) {

		TrieNode* root = new TrieNode('?');

		for (int i = 0; i < n; ++i) {
			scanf("%s", buff);
			int length = strlen(buff);

			TrieNode* node = root;

			for (int j = 0; j < length; ++j) {
				int c = buff[j] - 'a';
				if (node->children[c] == NULL) {
					node->children[c] = new TrieNode(buff[j]);
					node->has_children = true;
				}
				node = node->children[c];
				node->visited_count++;
			}
			node->finishes_word = true;
		}

		GlobalStrokesCount = 0;

		for (int i = 0; i < 26; ++i) {
			if (root->children[i] == NULL)
				continue;
			dfs(root->children[i], -1, 0);
		}

		float avg = (float) GlobalStrokesCount / (float) n;
		printf("%.2f\n", avg);

		delete root;

	}

	return 0;
}
