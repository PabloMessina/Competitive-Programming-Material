/* ================================= */
/* Input/Output with C++: cin & cout */
/* ================================= */

// reading many lines of unknown length
string line;
while(getline(cin, line)) {}

// reading tokens from a line
string token;
stringstream ss(line);
while (ss >> token) { /* do something with token */}

// printing floating with fixed precision
cout << setprecision(6) << fixed;
cout << 12312.12312355;

/* ================================= */
/* CONVERTING FROM STRING TO NUMBERS */
/* ================================= */

// 1) stringstream
string s = "12345"; 
stringstream ss(s);
int x;
ss >> x; // x = 12345
ss << "12345678910";
long long y;
ss >> y; // y = 12345678910

// 2) stoi, stoll
string str_dec = "2001, A Space Odyssey";
string str_hex = "40c3";
string str_bin = "-10010110001";
string str_auto = "0x7f";
int sz;
int i_dec = stoi(str_dec,&sz);
int i_hex = stoi(str_hex,0,16);
int i_bin = stoi(str_bin,0,2);
int i_auto = stoi(str_auto,0,0);
cout << str_dec << ": " << i_dec << " and [" << str_dec.substr(sz) << "]\n";
cout << str_hex << ": " << i_hex << '\n';
cout << str_bin << ": " << i_bin << '\n';
cout << str_auto << ": " << i_auto << '\n';
// 2001, A Space Odyssey: 2001 and [, A Space Odyssey]
// 40c3:  16579
// -10010110001: -1201
// 0x7f: 127
string str = "8246821 0xffff 020";
int sz = 0;
while (!str.empty()) {
    long long ll = stoll(str,&sz,0);
    cout << str.substr(0,sz) << " interpreted as " << ll << '\n';
    str = str.substr(sz);
}
// 8246821 interpreted as 8246821
//  0xffff interpreted as 65535
//  020 interpreted as 16

/* ========================== */
/* C STRING UTILITY FUNCTIONS */
/* ========================== */
int strcmp ( const char * str1, const char * str2 ); // (-1,0,1)
int memcmp ( const void * ptr1, const void * ptr2, size_t num ); // (-1,0,1)
void * memcpy ( void * destination, const void * source, size_t num );

/* ============================ */
/* C++ STRING UTILITY FUNCTIONS */
/* ============================ */

// split a string by a single char delimiter
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
}

// find index of string or char within string
string str = "random";
size_t pos = str.find("ra");
size_t pos = str.find('m');
if (pos == string::npos) // not found

// substrings
string subs = str.substr(pos, length);
string subs = str.substr(pos); // default: to the end of the string

// std::string from cstring's substring
const char* s = "bla1 bla2";
int offset = 5, len = 4;
string subs(s + offset, len); // bla2

// -------------------------
// string comparisons
string str1("green apple");
string str2("red apple");
if (str1.compare(str2) != 0)
    cout << str1 << " is not " << str2 << '\n';
if (str1.compare(6,5,"apple") == 0)
    cout << "still, " << str1 << " is an apple\n";
if (str2.compare(str2.size()-5,5,"apple") == 0)
    cout << "and " << str2 << " is also an apple\n";
if (str1.compare(6,5,str2,4,5) == 0)
    cout << "therefore, both are apples\n";
// green apple is not red apple
// still, green apple is an apple
// and red apple is also an apple
// therefore, both are apples

/* ===================== */
/*  OPERATOR OVERLOADING */
/* ===================== */

//--------------------------
// method #1: inside struct
struct Point {
    int x, y; 
    bool operator<(const Point& p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator>(const Point& p) const {
        if (x != p.x) return x > p.x;
        return y > p.y;
    }
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

//--------------------------
// method #2: outside struct
struct Point {int x, y; };
bool operator<(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool operator>(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x > b.x;
    return a.y > b.y;
}
bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}
// Note: if you overload the < operator for a custom struct,
// then you can use that struct with any library function
// or data structure that requires the < operator
// Examples:
priority_queue<Point> pq;
vector<Point> pts;
sort(pts.begin(), pts.end());
lower_bound(pts.begin(), pts.end(), {1,2});
upper_bound(pts.begin(), pts.end(), {1,2});
set<Point> pt_set;
map<Point, int> pt_map;

/* =============== */
/* RANDOM INTEGERS */
/* =============== */
#include <cstdlib>
#include <ctime>
srand(time(NULL));
int x = rand() % 100; // 0-99
int randBetween(int a, int b) { // a-b
    return a + (rand() % (1 + b - a));
}

/* ============== */
/* Bitwise Tricks */
/* ============== */
// amount of one-bits in number
int __builtin_popcount(int x);
int __builtin_popcountl(long x);
int __builtin_popcountll(long long x);
// amount of leading zeros in number
int __builtin_clz(int x);
int __builtin_clzl(long x);
int __builtin_clzll(ll x);
// binary length of non-negative number
int bitlen(int x) { return sizeof(x) * 8 - __builtin_clz(x); }
int bitlen(ll x) { return sizeof(x) * 8 - __builtin_clzll(x); }
// index of most significant bit
int log2(int x) { return sizeof(x) * 8 - __builtin_clz(x) - 1; }
int log2(ll x) { return sizeof(x) * 8 - __builtin_clzll(x) - 1; }
// reverse the bits of an integer
int reverse_bits(int x) {
    int v = 0;
    while (x) v <<= 1, v |= x&1, x >>= 1;
    return v;
}
// get string binary representation of an integer
string bitstring(int x) {
    int len = sizeof(x) * 8 - __builtin_clz(x);
    if (len == 0) return "0";

    char buff[len+1]; buff[len] = '\0';
    for (int i = len-1; i >= 0; --i, x >>= 1)
        buff[i] = (char)('0' + (x&1));
    return string(buff);
}

/* ================== */
/* Hexadecimal Tricks */
/* ================== */
// get string hex representation of an integer
string to_hex(int num) {
    static char buff[100];
    static const char* hexdigits = "0123456789abcdef";
    buff[99] = '\0';
    int i = 98;
    do {
        buff[i--] = hexdigits[num & 0xf];
        num >>= 4;
    } while (num);
    return string(buff+i+1);
}
// ['0'-'9' 'a'-'f'] ->  [0 - 15]
int char_to_digit(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    return 10 + c - 'a';
}

/* ================= */
/* CLIMITS CONSTANTS */
/* ================= */
INT_MIN INT_MAX UINT_MAX LONG_MIN LONG_MAX ULONG_MAX LLONG_MIN LLONG_MAX ULLONG_MAX