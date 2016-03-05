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
#include <bits/stdc++. h> //import all
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef long long int ll;

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
//method #1: override operator< and/or operator>
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







