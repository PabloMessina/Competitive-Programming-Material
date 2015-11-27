#include <cstdio>
#include <map>
#include <string>
using namespace std;

char buffer[201];
map<string, int> rep_counts;
string last10lines[10];
bool last10has4[10];

//a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
int is_cons[] = { 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 0, 1 };

bool isConsonant(char c) {
	if ('a' <= c && c <= 'z')
		return is_cons[c - 'a'];
	else if ('A' <= c && c <= 'Z')
		return is_cons[c - 'A'];
	return false;
}

enum ReadState {
	NoConsonant, Consonant
};

int main() {
	int n;
	scanf("%d", &n);
	int first = 0;
	int last = 9;
	getchar();

	int moreThan4Count = 0;

	for (int k = 0; k < n; ++k) {

//		printf("----------------\n");
//		printf("k = %d\n", k);

		ReadState rstate = NoConsonant;
		int num_cons = 0;

		bool accepted = true;
		bool has4cons = false;

		int i = 0;

		while (true) {
			char c = getchar();
			if (c == EOF || c == '\n')
				break;
			buffer[i++] = c;

			if (isConsonant(c)) {
				if (rstate == NoConsonant) {
					rstate = Consonant;
					num_cons = 0;
				}
				num_cons++;
				if (num_cons > 4) {
					has4cons = true;
					if (num_cons > 5) {
						accepted = false;
					}
				}
			} else if (rstate == Consonant) {
				rstate = NoConsonant;
			}
		}

		if (has4cons)
			moreThan4Count++;

		buffer[i] = '\0';
		string s(buffer);

		if (rep_counts.find(s) == rep_counts.end()) {
			rep_counts[s] = 1;
		} else {
			rep_counts[s]++;
		}

//		printf("s = %s\n", s.c_str());
//		printf("rep_counts[s] = %d\n", rep_counts[s]);

		if ((has4cons && moreThan4Count > 3) || rep_counts[s] > 2)
			accepted = false;

		if (k < 10) {
			last10lines[k] = s;
			last10has4[k] = has4cons;
		} else {

			if (last10has4[first])
				moreThan4Count--;

			if (--rep_counts[last10lines[first]] == 0)
				rep_counts.erase(last10lines[first]);

			last = (last + 1) % 10;
			first = (first + 1) % 10;

			last10has4[last] = has4cons;
			last10lines[last] = s;
		}

		if (accepted)
			printf("y\n");
		else
			printf("n\n");

	}
	return 0;
}
