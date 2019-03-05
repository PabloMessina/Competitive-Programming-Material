// tags: backtracking, pruning, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int R, C;
string names[4];
string digitsArray[5];

int cells[5][6];
int offsets[5][7] = {0};

bool isLetter(char c) {
	return ('a' <= c and c <= 'z') or ('A' <= c and c <= 'Z');
}

int parseNum(string& s, int i, int j) {
	int x = 0;
	rep(k,i,j) x = x * 10 + (s[k] - '0');
	return x;
}

void print_table() {
	rep(c,1,C-1) cout << "P" << c << " ";
	cout << "Totals\n";
	rep(r,0,R-2) {
		cout << names[r];
		rep(c,0,C-1) cout << " " << cells[r][c];
		cout << '\n';
	}
	cout << "TP";
	rep(c,0,C-1) cout << " " << cells[R-1][c];
	cout << '\n';
}

bool validate_row(int r) {
	int sum = 0;
	rep(c,0,C-2) sum += cells[r][c];
	return sum == cells[r][C-1];
}

bool validate_column(int c) {
	int sum = 0;
	rep(r,0,R-2) sum += cells[r][c];
	return sum == cells[R-1][c];
}

bool solve(int r, int c) {
	int offset = offsets[r][c];
	string& digits = digitsArray[r];
	int len = digits.size();
	int r_digits = len - offset;
	bool footer = r == R-1;
	int maxD1 = footer ? 4 : 3;
	int maxD2 = footer ? 5 : 4;

	if (c == C-1) {
		if (r_digits > maxD2) return false;
		if (digits[offset] == '0' and r_digits > 1) return false;
		int val = parseNum(digits, offset, len-1);
		cells[r][c] = val;
		if (footer) {
			if (validate_row(r) and validate_column(c)) return true;
		} else {
			if (validate_row(r) and solve(r+1, 0)) return true;
		}
		return false;
	}

	if (digits[offset] == '0') {
		cells[r][c] = 0;
		offsets[r][c+1] = offset + 1;
		if (footer) {
			if (validate_column(c) and solve(r, c+1)) return true;
		} else {
			if (solve(r, c+1)) return true;
		}
		return false;
	}

	int r_cols = C - c;
	int i_start = offset + max(r_digits - maxD2 - maxD1*(r_cols-2) - 1, 0);
	int i_end = offset + min(maxD1 - 1, r_digits - r_cols);
	rep(i, i_start, i_end) {
		int val = parseNum(digits, offset, i);
		cells[r][c] = val;
		offsets[r][c+1] = i+1;
		if (footer) {
			if (validate_column(c) and solve(r, c+1)) return true;			
		} else {
			if (solve(r, c+1)) return true;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(0);
	string line;
	int T; cin >> T;
	while (T--) {
		cin >> line;
		C = (line.size() - 6) / 2 + 1;
		R = 0;
		while (true) {
			cin >> line;
			if (memcmp("TP", line.c_str(), 2) == 0)
				break;
			int i = 0;
			while (isLetter(line[i])) i++;
			names[R] = line.substr(0,i);
			digitsArray[R++] = line.substr(i);
		}
		digitsArray[R++] = line.substr(2);
		solve(0, 0);
		print_table();
	}	
    return 0;
}