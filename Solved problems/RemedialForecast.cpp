#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

char buffer[100];

struct Student {
	int in;
	int a;
	int sh;
	int ch;
	int r;
	int index;
};

struct AuxData {
	int distance;
	int studentIndex;
};

bool cmp(const AuxData& a, const AuxData& b) {
	return (a.distance < b.distance
			|| (a.distance == b.distance && a.studentIndex < b.studentIndex));
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);	 //debugging
	int in, a, sh, ch, r;
	vector<Student> students;
	int index = 0;
	while (true) {
		gets(buffer);
		if (strlen(buffer) == 0)
			break;
		sscanf(buffer, "%d %d %d %d %d", &in, &a, &sh, &ch, &r);
		students.push_back( { in, a, sh, ch, r, index++ });
	}
	while (!feof(stdin)) {
		int k;
		gets(buffer);
		sscanf(buffer, "%d", &k);

		while (gets(buffer) != NULL && strlen(buffer) > 0) {

			sscanf(buffer, "%d %d %d %d", &in, &a, &sh, &ch);
			vector<AuxData> auxdata;
			for (int i = 0; i < students.size(); ++i) {
				Student& s = students[i];
				auxdata.push_back(
						{ abs(a - s.a) + abs(sh - s.sh) + abs(ch - s.ch), i });
			}
			sort(auxdata.begin(), auxdata.end(), cmp);
			int count = 0;
			for (int i = 0; i < k; ++i) {
				count += students[auxdata[i].studentIndex].r;
			}
			int r = (count > k / 2) ? 1 : 0;
			printf("%d %d\n", in, r);
		}
	}

	return 0;
}
