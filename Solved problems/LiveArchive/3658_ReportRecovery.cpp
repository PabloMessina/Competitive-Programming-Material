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
	int offset = offsets[r][c]; // build number in row 'r' and column 'c'
	// only using digits in range [offset .. digitsArray[r].size()-1]
	string& digits = digitsArray[r]; // row r's digits
	int len = digits.size();
	int r_digits = len - offset; // remaining digits
	bool footer = r == R-1; // if row r is footer (TP row)
	int maxD1 = footer ? 4 : 3; // max number of digits for number in non-last column
	int maxD2 = maxD1 + 1; // max number of digits for number in last column

	if (c == C-1) { // if we are in the last column
		if (r_digits > maxD2) return false; // check if enough digits
		if (digits[offset] == '0' and r_digits > 1) return false; // no leading 0s
		int val = parseNum(digits, offset, len-1); // read all remaining digits
		cells[r][c] = val; // save value
		if (footer) { // if footer -> validate both row and column
			if (validate_row(r) and validate_column(c)) return true;
		} else { // not footer -> validate row and keep solving
			if (validate_row(r) and solve(r+1, 0)) return true;
		}
	} else if (digits[offset] == '0') { // non-last column and leading 0
		// -> we are forced to make cells[r][c] = 0 because leading zeros are not allowed
		cells[r][c] = 0;
		offsets[r][c+1] = offset + 1; // set the offset for next cell
		if (footer) { // if footer -> validate column and keep solving
			if (validate_column(c) and solve(r, c+1)) return true;
		} else { // not footer -> keep solving
			if (solve(r, c+1)) return true;
		}
	} else { // non-last column and no leading zeroes
		int r_cols = C - c; // remaining columns to the right
		int i_start = offset + max(r_digits - maxD2 - maxD1*(r_cols-2) - 1, 0);
		int i_end = offset + min(maxD1 - 1, r_digits - r_cols);
		rep(i, i_start, i_end) { // for each i in valid range
			int val = parseNum(digits, offset, i); // read number digits[offset .. i]
			cells[r][c] = val; // save value
			offsets[r][c+1] = i+1; // set the offset for next cell
			if (footer) { // if footer -> validate column and keep solving
				if (validate_column(c) and solve(r, c+1)) return true;			
			} else { // not footer -> keep solving
				if (solve(r, c+1)) return true;
			}
		}
	}	
	return false; // nothing worked
}

int main() {
	// for faster input/output
	ios::sync_with_stdio(false);
    cin.tie(0);
	// -----------
	int T; cin >> T;
	while (T--) {
		string line;
		cin >> line; // read header
		C = (line.size() - 6) / 2 + 1; // number of columns
		R = 0; // number of rows
		while (true) { // for each remaining line
			cin >> line;
			if (memcmp("TP", line.c_str(), 2) == 0) // TP row
				break;
			int i = 0;
			while (isLetter(line[i])) i++;
			names[R] = line.substr(0,i); // name
			digitsArray[R++] = line.substr(i); // digits
		}
		digitsArray[R++] = line.substr(2); // TP row's digits
		solve(0, 0); // backtracking
		print_table(); 
	}	
    return 0;
}