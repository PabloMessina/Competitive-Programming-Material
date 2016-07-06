//#####################################################
//################## C++ CHEAT SHEET ##################
//#####################################################

//=========================================
//Template
//=========================================
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef long long int ll;

// for loop
#define FOR(i,n) for(int i = 0; i < n; ++i)
// declara a dynamic 2D matrix with the given type, width, height and name
#define vecMatrix(name,type,w,h) vector<vector<type> > name(h, vector<type>(w));

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);	 //debugging
	while(true) {	
	}
	return 0;
}

//=====================
//Reading from stdin
//=====================
scanf("%d",&a); //int
scanf("%lld",&a); //long long int
scanf("%c",&c); //char
scanf("%s",buffer); //string without whitespaces
scanf("%f",&f); //float
scanf("%lf",&d); //double
scanf("%d %*s %d",&a,&b);  //* = skip

//read until eol
//	- eol not included in buffer
//	- eol is not consumed
//	- nothing is written into buffer if EOF is found
scanf(" %[^\n]",buffer); 

//reading until EOL or EOF
//	- eol not included in buffer
//	- eol is consumed
//	- works with eof
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
//Peek last char of stdin
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



//============================================
//CONVERTING FROM STRING TO NUMBERS
//============================================

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

//--------------------------
//string to double:
//option #1:
double strtod (const char* str, char** endptr); //similar to strtol
//option #2:
double atof (const char* str);
//option #3:
sscanf(string,"%lf",&d);

//==========================
// STRING UTILITY FUNCTIONS
//==========================

//--------------------------
// lexicographic comparison (-1, 0, 1)
int strcmp ( const char * str1, const char * str2 );


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

//============================
//	CUSTOM COMPARISONS
//============================
struct Edge
{
    int from, to, weight;
};


//----------------------------------------------
//method #1: overlaod operator< and/or operator>
//syntax #1
struct Edge
{
  int from, to, weight;
  bool operator<(const Edge& other) const
  {
      return weight < other.weight;
  }
  bool operator>(const Edge& other) const
  {
      return weight > other.weight;
  }
  bool operator== (const Edge& other) {
   return weight == other.weight;
  }
};
//syntax #2
struct Edge
{
  int from, to, weight;
  friend bool operator<(const Edge& a, const Edge& b)
  {
    return a.weight < b.weight;
  }
  friend bool operator>(const Edge& a, const Edge& b)
  {
    return a.weight > b.weight;
  }
};


//----------------------------------------------
//method #2: custom comparison function
bool cmp(const Edge& a, const Edge& b)
{ 
	return a.weight < b.weight;
}


//----------------------------------------------
//method #3: functor
struct cmp
{
    bool operator()(const Edge& a, const Edge& b)
    {
        return occurrences[a] < occurrences[b];
    }
};
set<int, cmp> s;
priority_queue<int, vector<int>, cmp> pq;

//============================
//	DATA STRUCTURES
//============================

//greater, less
#include <functional>
std::sort (foo, foo+5, std::less<int>());
std::sort (bar, bar+3, std::less<int>());

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



