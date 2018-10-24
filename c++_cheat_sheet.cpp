// Note: This Cheat Sheet is by no means complete
// If you want a thorough documentation of the Standard C++ Library
// please refer to this link: http://www.cplusplus.com/reference/

/* ========= */
// Template  //
/* ========= */
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;

int main() {
    ios::sync_with_stdio(false); // for greater performance if only using cin/cout
    cin.tie(0); // for greater performance if only using cin/cout
    // setvbuf(stdout, NULL, _IONBF, 0);  // if debugging with printf/scanf
    return 0;
}

/* ================== */
/* Reading from stdin */
/* ================== */
scanf("%d",&a); //int
scanf("%x",&a); // int in hexadecimal
scanf("%llx",&a); // long long in hexadecimal
scanf("%lld",&a); // long long int
scanf("%c",&c); // char
scanf("%s",buffer); // string without whitespaces
scanf("%f",&f); // float
scanf("%lf",&d); // double
scanf("%d %*s %d",&a,&b);  //* = consume but skip

// read until EOL
//  - EOL not included in buffer
//  - EOL is not consumed
//  - nothing is written into buffer if EOF is found
scanf(" %[^\n]",buffer); 

//reading until EOL or EOF
//  - EOL not included in buffer
//  - EOL is consumed
//  - works with EOF
char* output = gets(buffer);
if(feof(stind)) {} // EOF file found
if(output == buffer) {} // succesful read
if(output == NULL) {} // EOF found without previous chars found
//example
while(gets(buffer) != NULL) {
    puts(buffer);
    if(feof(stdin)) {
        break;
    }
}

// read single char
getchar();
while(true) {c = getchar(); if (c == EOF || c== '\n') break;}

/* ================== */
/* Printing to stdout */
/* ================== */
printf("%d",a); // int
printf("%u",a); // unsigned int
printf("%lld",a); // long long int
printf("%llu",a); // unsigned long long int
printf("%c",c); // char
printf("%s",buffer); // string until \0
printf("%f",f); // float
printf("%lf",d); // double
printf("%0*.*f",x,y,f); // padding = 0, width = x, decimals = y
printf("(%.5s)\n", buffer); // print  at most the first five characters (safe to use on short strings)

// print at most first n characters (safe)
printf("(%.*s)\n", n, buffer);  // make sure that n is integer (with long long I had problems)
//string + \n
puts(buffer);

/* ===================== */
/* Reading from c string */
/* ===================== */

// same as scanf but reading from s
int sscanf ( const char * s, const char * format, ...);

/* ==================== */
/* Printing to c string */
/* ==================== */
// Same as printf but writing into str, the number of characters is returned
// or negative if there is failure
int sprintf ( char * str, const char * format, ... );
//example:
int n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
printf ("[%s] is a string %d chars long\n",buffer,n);

/* ======================= */
/* Peek last char of stdin */
/* ======================= */
bool peekAndCheck(char c) {
    char c2 = getchar();
    ungetc(c2, stdin); // return char to stdin
    return c == c2;
}

/* ================ */
/* Reading from cin */
/* ================ */
// reading a line of unknown length
string line;
getline(cin, line);
while(getline(cin, line)) {}

/* ====================== */
/* USING PAIRS AND TUPLES */
/* ====================== */
// ii = pair<int,int>
ii p(5,5);
ii p = make_pair(5,5)
ii p = {5, 5};
int x = p.first, y = p.second;
// iii = tuple<int,int,int>
iii t(5,5,5);
tie(x,y,z) = t;
tie(x,y,z) = make_tuple(5,5,5);
get<0>(t)++;
get<1>(t)--;

/* ================================= */
/* CONVERTING FROM STRING TO NUMBERS */
/* ================================= */
//------------------------
// string to int
// option #1:
int atoi (const char * str);
// option #2:
sscanf(string,"%d",&i);
//--------------------------
// string to long int: 
// option #1:
long int strtol (const char* str, char** endptr, int base);
// it only works skipping whitespaces, so make sure your numbers
// are surrounded by whitespaces only
// Example:
    char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    char * pEnd;
    long int li1, li2, li3, li4;
    li1 = strtol (szNumbers,&pEnd,10);
    li2 = strtol (pEnd,&pEnd,16);
    li3 = strtol (pEnd,&pEnd,2);
    li4 = strtol (pEnd,NULL,0);
    printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
// option #2:
long int atol ( const char * str );
// option #3:
sscanf(string,"%ld",&l);
//---------------------------
// string to long long int:
// option #1:
long long int strtoll (const char* str, char** endptr, int base);
// option #2:
sscanf(string,"%lld", &l);
//--------------------------
// string to double:
// option #1:
double strtod (const char* str, char** endptr); //similar to strtol
// option #2:
double atof (const char* str);
// option #3:
sscanf(string,"%lf", &d);

/* ========================== */
/* C STRING UTILITY FUNCTIONS */
/* ========================== */
int strcmp ( const char * str1, const char * str2 ); // (-1,0,1)
int memcmp ( const void * ptr1, const void * ptr2, size_t num ); // (-1,0,1)
void * memcpy ( void * destination, const void * source, size_t num );

/* ============================ */
/* C++ STRING UTILITY FUNCTIONS */
/* ============================ */
// read tokens from string
string s = "tok1 tok2 tok3";
string tok;
stringstream ss(s);
while (getline(ss, tok, ' ')) printf("tok = %s\n", tok.c_str());

// split a string by a single char delimiter
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
}

// find index of string or char within string
string str = "random";
std:size_t pos = str.find("ra");
std:size_t pos = str.find('m');
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
int compare (const string& str) const;
int compare (size_t pos, size_t len, const string& str) const;
int compare (size_t pos, size_t len, const string& str,
                         size_t subpos, size_t sublen) const;
int compare (const char* s) const;
int compare (size_t pos, size_t len, const char* s) const;

// examples
// 1) check string begins with another string
string prefix = "prefix";
string word = "prefix suffix";
word.compare(0, prefix.size(), prefix);

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


/* ================== */
/* CUSTOM COMPARISONS */
/* ================== */
// method #1: operator overloading
// method #2: custom comparison function
bool cmp(const Point& a, const Point& b) { 
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
// method #3: functor
struct cmp {
    bool operator()(const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }
};
// without operator overloading, you would have to use
// an explicit comparison method when using library
// functions or data structures that require sorting
priority_queue<Point, vector<Point>, cmp> pq;
vector<Point> pts;
sort(pts.begin(), pts.end(), cmp);
lower_bound(pts.begin(), pts.end(), {1,2}, cmp);
upper_bound(pts.begin(), pts.end(), {1,2}, cmp);
set<Point, cmp> pt_set;
map<Point, int, cmp> pt_map;

/* ======================== */
/* VECTOR UTILITY FUNCTIONS */
/* ======================== */
vector<int> myvector;
myvector.push_back(100);
myvector.pop_back(); // remove last element
myvector.back(); // peek reference to last element
myvector.front(); // peek reference to first element
myvector.clear(); // remove all elements
// sorting a vector
vector<int> foo;
sort (foo.begin(), foo.end());
sort (foo.begin(), foo.end(), std::less<int>()); // increasing
sort (foo.begin(), foo.end(), std::greater<int>()); // decreasing

/* ===================== */
/* SET UTILITY FUNCTIONS */
/* ===================== */
set<int> myset;
myset.begin(); // iterator to first elemnt
myset.end(); // iterator to after last element
myset.rbegin(); // iterator to last element
myset.rend(); // iterator to before first element
for (auto it = myset.begin(); it != myset.end(); ++it) { do_something(*it); } // left -> right
for (auto it = myset.rbegin(); it != myset.rend(); ++it) { do_something(*it); } // right -> left
for (auto& i : myset) { do_something(i); } // left->right shortcut
auto ret = myset.insert(5); // ret.first = iterator, ret.second = boolean (inserted / not inserted)
int count = mysert.erase(5); // count = how many items were erased
if (!myset.empty()) {}
// custom comparator 1: functor
struct cmp { bool operator()(int i, int j) { return i > j; } };
set<int, cmp> myset;
// custom comparator 2: function
bool cmp(int i, int j) { return i > j; }
set<int, bool(*)(int,int)> myset(cmp);

/* ===================== */
/* MAP UTILITY FUNCTIONS */
/* ===================== */
struct Point {int x, y; };
bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
map<Point, int> ptcounts;

// --------------------
// inserting into map

// method #1: operator[]
// it overwrites the value if the key already exists
ptcounts[{1, 2}] = 1;

// method #2: .insert(pair<key, value>)
// it returns a pair { iterator(key, value) , bool }
// if the key already exists, it doesn't overwrite the value
void update_count(Point& p) {
    auto ret = ptcounts.emplace(p, 1);
    // auto ret = ptcounts.insert(make_pair(p, 1)); //
    if (!ret.second) ret.first->second++;
}

// -------------------------
// generating ids with map
int get_id(string& name) {
    static int id = 0;
    static map<string,int> name2id;
    auto it = name2id.find(name);
    if (it == name2id.end())
        return name2id[name] = id++;
    return it->second;
}

/* ======================== */
/* BITSET UTILITY FUNCTIONS */
/* ======================== */
bitset<4> foo; // 0000
foo.size(); // 4
foo.set(); // 1111
foo.set(1,0); // 1011
foo.test(1); // false
foo.set(1); // 1111
foo.test(1); // true

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

/* ======= */
/* CLIMITS */
/* ======= */
#include <climits>
INT_MIN
INT_MAX
UINT_MAX
LONG_MIN
LONG_MAX
ULONG_MAX
LLONG_MIN
LLONG_MAX
ULLONG_MAX

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

/* ============ */
/* Other Tricks */
/* ============ */
// swap stuff
int x = 1,  y = 2;
swap(x, y);

/* =========== */
/*    TIPS     */
/* =========== */
// 1) do not use .emplace(x, y) if your struct doesn't have an explicit constructor
//    instead you can use .push({x, y})
// 2) be careful while mixing scanf() with getline(), scanf will not consume \n unless
//    you explicitly tell it to do so (e.g scanf("%d\n", &x)) )