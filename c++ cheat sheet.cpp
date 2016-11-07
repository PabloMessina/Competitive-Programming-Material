/* ========================= */
/* ==== C++ CHEAT SHEET ==== */
/* ========================= */

//==========
// Template
//==========
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>

#include <bits/stdc++.h> // add everything in one shot
#include <tr1/unordered_map>
#include <tr1/unordered_set>
using namespace std;

// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap tr1::unordered_map
#define uset tr1::unordered_set

// typedefs
typedef vector<int> vi;
typedef vector<vi> vii;
typedef long long int ll;
typedef pair<int,int> pii;

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);  //debugging
  while(true) { 
  }
  return 0;
}

//=====================
// Reading from stdin
//=====================
scanf("%d",&a); //int
scanf("%lld",&a); //long long int
scanf("%c",&c); //char
scanf("%s",buffer); //string without whitespaces
scanf("%f",&f); //float
scanf("%lf",&d); //double
scanf("%d %*s %d",&a,&b);  //* = skip

//read until eol
//  - eol not included in buffer
//  - eol is not consumed
//  - nothing is written into buffer if EOF is found
scanf(" %[^\n]",buffer); 

//reading until EOL or EOF
//  - eol not included in buffer
//  - eol is consumed
//  - works with eof
char* output = gets(buffer);
if(feof(stind)) {//eof file found
}
if(output == buffer) {} //succesful read
if(output == NULL) {} //eof found without previous chars found
//example
while(gets(buffer) != NULL) {
  puts(buffer);
  if(feof(stdin)) {
    break;
  }
}

//read single char
getchar();
while(true) {c = getchar(); if (c == EOF || c== '\n') break;}

//=====================
//Printing to stdout
//=====================
printf("%d",a); //int
printf("%lld",a); //long long int
printf("%llu",a); //unsigned long long int
printf("%c",c); //char
printf("%s",buffer); //string until \0
printf("%f",f); //float
printf("%lf",d); //double
printf("%0*.*f",x,y,f); //padding = 0, width = x, decimals = y
printf("(%.5s)\n", buffer);// print  at most the first five characters (safe to use on short strings)

// make sure that n is an integer (with long long I had problems)
printf("(%.*s)\n", n, buffer);  /* print at most first n characters (safe) */
puts(buffer); //string + \n


//======================
//Reading from c string
//======================

//same as scanf but reading from s
int sscanf ( const char * s, const char * format, ...);

//======================
//Printing to c string
//======================

//same as printf but writing into str
//the number of characters is returned
// or negative if there is failure
int sprintf ( char * str, const char * format, ... );
//example:
int n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
printf ("[%s] is a string %d chars long\n",buffer,n);

//========================
// Peek last char of stdin
//=======================

bool peekAndCheck(char c) {
  char c2 = getchar();
  ungetc(c2, stdin); // return char to stdin
  return c == c2;
}

//==================
//Reading from cin
//==================

//------------------------------------
// reading a line of unknown length
#include <iostream>
#include <string>
int main ()
{
  std::string name;
  std::getline (std::cin,name);
  std::cout << "Hello, " << name << "!\n";
  return 0;
}


//=====================================
// CONVERTING FROM STRING TO NUMBERS
//=====================================

//------------------------
//string to int
//option #1:
#include <cstdlib>
int atoi (const char * str);
//option #2:
#include <cstdio>
sscanf(string,"%d",&i);

//--------------------------
//string to long int: 
//option #1:
#include <cstdlib>
long int strtol (const char* str, char** endptr, int base);
// it only works skipping whitespaces, so make sure your numbers
// are surrounded by whitespaces only
//example:
  char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
  char * pEnd;
  long int li1, li2, li3, li4;
  li1 = strtol (szNumbers,&pEnd,10);
  li2 = strtol (pEnd,&pEnd,16);
  li3 = strtol (pEnd,&pEnd,2);
  li4 = strtol (pEnd,NULL,0);
  printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
//option #2:
long int atol ( const char * str );
//option #3:
sscanf(string,"%ld",&l);

//----------------
//string to long long int:
//option #1:
long long int strtoll (const char* str, char** endptr, int base);
//option #2:
sscanf(string,"%lld", &l);

//--------------------------
//string to double:
//option #1:
double strtod (const char* str, char** endptr); //similar to strtol
//option #2:
double atof (const char* str);
//option #3:
sscanf(string,"%lf", &d);

//=============================
// C STRING UTILITY FUNCTIONS
//=============================

#include <cstring>
int strcmp ( const char * str1, const char * str2 ); // (-1,0,1)
int memcmp ( const void * ptr1, const void * ptr2, size_t num ); // (-1,0,1)
void * memcpy ( void * destination, const void * source, size_t num );

//==============================
// C++ STRING UTILITY FUNCTIONS
//==============================

// split a string by a single char delimiter
#include <string>
#include <sstream>
#include <vector>
void split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
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


buffer (4)  

int compare (size_t pos, size_t len, const char* s, size_t n) const;


//======================
//Nested Unordered Maps
//=======================
#include <tr1/unordered_map>
typedef std::tr1::unordered_map<int, int> nested_hash;
typedef std::tr1::unordered_map<int, nested_hash> double_hash;

//============
//Struct Node
//============
struct node {
  vector<node*> children;
  node* parent;
}; //node *_node = new node;


//========================
//  OPERATOR OVERLOADING
//========================

//--------------------------
//method #1: inside struct
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
//method #2: outside struct
struct Point {int x, y; };
bool operator<(const Point& p1, const Point& p2) {
  if (p1.x != p2.x) return p1.x < p2.x;
  return p1.y < p2.y;
}
bool operator>(const Point& p1, const Point& p2) {
  if (p1.x != p2.x) return p1.x > p2.x;
  return p1.y > p2.y;
}
bool operator==(const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

// Note: if you overload the < operator for a custom struct,
// then you can use that struct with any library function
// or data structure that requires the < operator

// Examples:

priority_queue<Point> pq;
pq.top();

vector<Point> pts;
sort(pts.begin(), pts.end());
lower_bound(pts.begin(), pts.end(), {1,2});
upper_bound(pts.begin(), pts.end(), {1,2});

set<Point> pts;
map<Point, int> ptToId;


//=====================
// CUSTOM COMPARISONS
//=====================

// method #1: operator overloading

// method #2: custom comparison function
bool cmp(const Point& a, const Point& b) { 
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

// method #2: functor
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
pq.top();

vector<Point> pts;
sort(pts.begin(), pts.end(), cmp);
lower_bound(pts.begin(), pts.end(), {1,2}, cmp);
upper_bound(pts.begin(), pts.end(), {1,2}, cmp);

set<Point, cmp> pts;
map<Point, int, cmp> ptToId;

//=================
// functors
//=================
// this is a functor
struct add_x {
  add_x(int x) : x(x) {}
  int operator()(int y) const { return x + y; }
  private:
    int x;
};

// Now you can use it like this:
add_x add42(42); // create an instance of the functor class
int i = add42(8); // and "call" it

/* ======================== */
/* VECTOR UTILITY FUNCTIONS */
/* ======================== */

std::vector<int> myvector;
myvector.push_back(100);
myvector.back(); // peek reference to last element
myvector.front(); // peek reference to first element
myvector.pop_back(); // remove last element
myvector.clear(); // remove all elements

// sorting a vector
#include <algorithm>
#include <functional> //greater, less
vector<int> foo;
sort (foo.begin(), foo.end());
sort (foo.begin(), foo.end(), std::less<int>());
sort (foo.begin(), foo.end(), std::greater<int>());

/* ===================== */
/* MAP UTILITY FUNCTIONS */
/* ===================== */

struct Point {int x, y; };
bool operator<(const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
map<Point, int> toId;

// -----------------
// inserting into map

// method #1: operator[]
// it overwrites the value if the key already exists
toId[{1, 2}] = 1;

// method #2: .insert({ key, value })
// it returns a pair { iterator(key, value) , bool }
// if the key already exists, it doesn't overwrite the value
int tid = 0;
while (true) {
  int x,y; scanf("%d%d",&x,&y);
  auto res = toId.insert({x,y}, tid);
  int id = res.first->second;
  if (res->second) // insertion happened
    tid++; 
}


/* =============== */
/* RANDOM INTEGERS */
/* =============== */
#include <cstdlib>
#include <ctime>

srand(time(NULL));
// 0-99
int x = rand() % 100;
// a-b
int randBetween(int a, int b) {
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
int __builtin_clzll(long long x);

// binary length of non-negative number
int bitlen(int x) {
  return sizeof(x) * 8 - __builtin_clz(x);
}
int bitlen(ll x) {
  return sizeof(x) * 8 - __builtin_clzll(x);
}

// index of most significant bit
int log2(int x) {
  return sizeof(x) * 8 - __builtin_clz(x) - 1;
}
int log2(long long x) {
  return sizeof(x) * 8 - __builtin_clzll(x) - 1;
}
// or
int log2(int x) {
  int i = 0;
  while (x) x >>= 1, ++i;
  return i-1;
}
int log2(ll x) {
  int i = 0;
  while (x) x >>= 1, ++i;
  return i-1;
}

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
#include <algorithm>
int x = 1,  y = 2;
swap(x, y);

/* =========== */
/*    TIPS     */
/* =========== */

// 1) do not use .emplace(x, y) if your struct doesn't have an explicit constructor
//    instead you can use .push({x, y})

// 2) be careful while mixing scanf() with getline(), scanf will not consume \n unless
//    you explicitly tell it to do so (e.g scanf("%d\n", &x)) )