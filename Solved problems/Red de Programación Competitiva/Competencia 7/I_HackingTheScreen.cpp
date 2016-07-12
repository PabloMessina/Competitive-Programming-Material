/**
 * Algorithms used: LL(1), recursive-descent parser
 */
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

#define FOR(i,i0,n) for(int i = i0; i < n; ++i)

int R,C;
typedef long long int ll;
string input[3];

enum Terminal {
  PLUS, MINUS, MULT, FRAC_BEGIN, FRAC_MID, FRAC_END, ROOT_BEGIN, ROOT_END, INTEGER, END
};

struct Token {
  Terminal term;
  Token(Terminal term) : term(term) {}
};
struct IntToken : Token {
  ll val;
  IntToken(ll val) : Token(INTEGER), val(val) {}
};

typedef vector<Token*> vtp;

bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

void tokenizeSimple(vtp& tokens, int col, int row, int limit) {
  while (col <= limit) {
    char c = input[row][col];
    switch (c) {
      case '-': tokens.push_back(new Token(MINUS)); col++; break;
      case '+': tokens.push_back(new Token(PLUS)); col++; break;
      case '*': tokens.push_back(new Token(MULT)); col++; break;
      default: {
        if (isDigit(c)) { //digit
          int num = 0;
          do {
            num = num * 10 + c - '0';
            c = input[row][++col];
          } while (col <= limit && isDigit(c));
          tokens.push_back(new IntToken(num));
        } else { // whitespace
          col++;
        }
        break;
      }
    }
  }
}

void collectTokens(vtp& tokens) {
  int mr = R / 2;
  int ur = mr - 1;
  int lr = mr + 1;
  int col = 0;
  char c;
  while(true) {
    c = input[mr][col];
    if (isDigit(c)) {
      int num = c - '0';
      while (true) {
        c = input[mr][++col];
        if (isDigit(c)) num = num * 10 + c - '0';
        else break;
      }
      tokens.push_back(new IntToken(num));
    } else {
      switch (c) {
        case '-': tokens.push_back(new Token(MINUS)); col++; break;
        case '+': tokens.push_back(new Token(PLUS)); col++; break;
        case '*': tokens.push_back(new Token(MULT)); col++; break;
        case '\\': {
          col+=2;
          int limit = col;
          while (input[ur][limit+1] == '_') limit++;
          tokens.push_back(new Token(ROOT_BEGIN));
          tokenizeSimple(tokens, col, mr, limit);
          tokens.push_back(new Token(ROOT_END));
          col = limit + 1;
          break;
        }
        case '=': {
          int limit = col;
          while (input[mr][limit+1] == '=') limit++;
          tokens.push_back(new Token(FRAC_BEGIN));
          tokenizeSimple(tokens, col, ur, limit);
          tokens.push_back(new Token(FRAC_MID));
          tokenizeSimple(tokens, col, lr, limit);
          tokens.push_back(new Token(FRAC_END));
          col = limit + 1;
          break;
        }
        case '\0': tokens.push_back(new Token(END)); return;
        default: col++; break; // whitespaces
      }
    }
  }
}

struct Node {
  virtual ~Node() {};
  virtual ll eval() = 0;
};
struct IntNode : Node {
  ll value;
  IntNode(ll value) : value(value) {}
  ll eval() { return value; }
};
struct BinOp : Node {
  Node* left;
  Node* right;
  BinOp(Node* left, Node* right) : left(left), right(right) {}
  ~BinOp() { delete left; delete right; }
};
struct AddNode : BinOp {
  AddNode(Node* l, Node* r) : BinOp(l,r) {}
  ll eval() { return left->eval() + right->eval(); }
};
struct SubNode : BinOp {
  SubNode(Node* l, Node* r) : BinOp(l,r) {}
  ll eval() { return left->eval() - right->eval(); }
};
struct MultNode : BinOp {
  MultNode(Node* l, Node* r) : BinOp(l,r) {}
  ll eval() { return left->eval() * right->eval(); }
};
struct DivNode : BinOp {
  DivNode(Node* l, Node* r) : BinOp(l,r) {}
  ll eval() { return left->eval() / right->eval(); }
};
struct SqrtNode : Node {
  Node* child;
  SqrtNode(Node* child) : child(child) {}
  ll eval() {
    ll cval = child->eval();
    ll val = (ll)sqrt(cval);
    ll val2 = val * val;
    if (val2 > cval) val--;
    else if (val2 < cval) val++;
    return val;
  }
};

typedef vector<Token*> vtp;
typedef stack<Node*> snp;

/**
 * Context Free Grammar
 *  form -> comp form2
 *  form2 -> + comp form2 | - comp form2 | epsilon
 *  comp -> sqrt | fraction | term
 *  sqrt -> ROOT_BEGIN  simple ROOT_END
 *  fraction -> FRAC_BEGIN simple FRAC_MID siple FRAC_END
 *  simple -> term simple2
 *  simple2 -> + term simple2 | - term simple2 | epsilon
 *  term -> INTEGER term2
 *  term2 -> * INTEGER term2 | epsilon
 */

void parseRoot(vtp& tokens, int& offset, snp& nodes);
void parseFormula1(vtp& tokens, int& offset, snp& nodes);
void parseFormula2(vtp& tokens, int& offset, snp& nodes);
void parseComplex(vtp& tokens, int& offset, snp& nodes);
void parseSimple1(vtp& tokens, int& offset, snp& nodes);
void parseSimple2(vtp& tokens, int& offset, snp& nodes);
void parseTerm1(vtp& tokens, int& offset, snp& nodes);
void parseTerm2(vtp& tokens, int& offset, snp& nodes);
void parseInt(vtp& tokens, int& offset, snp& nodes);

void parseRoot(vtp& tokens, int& offset, snp& nodes) {
  parseFormula1(tokens, offset, nodes);
}
void parseFormula1(vtp& tokens, int& offset, snp& nodes) {
  parseComplex(tokens, offset, nodes);
  parseFormula2(tokens, offset, nodes);
}
void parseFormula2(vtp& tokens, int& offset, snp& nodes) {
  Token* t = tokens[offset];
  switch (t->term) {
    case PLUS: {
      offset++;
      parseComplex(tokens, offset, nodes);
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new AddNode(left, right));
      parseFormula2(tokens, offset, nodes);
      break;
    }
    case MINUS: {
      offset++;
      parseComplex(tokens, offset, nodes);
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new SubNode(left, right));
      parseFormula2(tokens, offset, nodes);
      break;
    }
  }
}

void parseComplex(vtp& tokens, int& offset, snp& nodes) {
  Token* t = tokens[offset];
  switch (t->term) {
    case ROOT_BEGIN: {
      offset++;
      parseSimple1(tokens, offset, nodes);
      offset++;
      Node* child = nodes.top(); nodes.pop();
      nodes.push(new SqrtNode(child));
      break;
    }
    case FRAC_BEGIN: {
      offset++;
      parseSimple1(tokens, offset, nodes);
      offset++;
      parseSimple1(tokens, offset, nodes);
      offset++;
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new DivNode(left, right));
      break;
    }
    case INTEGER:
      parseTerm1(tokens, offset, nodes);
      break;
  }
}

void parseSimple1(vtp& tokens, int& offset, snp& nodes) {
  parseTerm1(tokens, offset, nodes);
  parseSimple2(tokens, offset, nodes);
}

void parseSimple2(vtp& tokens, int& offset, snp& nodes) {
  Token* t = tokens[offset];
  switch (t->term) {
    case PLUS: {
      offset++;
      parseTerm1(tokens, offset, nodes);
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new AddNode(left, right));
      parseSimple2(tokens, offset, nodes);
      break;
    }
    case MINUS: {
      offset++;
      parseTerm1(tokens, offset,  nodes);
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new SubNode(left, right));
      parseSimple2(tokens, offset, nodes);
      break;
    }
  }
}

void parseTerm1(vtp& tokens, int& offset, snp& nodes) {
  parseInt(tokens, offset, nodes);
  parseTerm2(tokens, offset, nodes);
}

void parseTerm2(vtp& tokens, int& offset, snp& nodes) {
  if (tokens[offset]->term == MULT) {
    offset++;
    parseInt(tokens, offset, nodes);
    Node* right = nodes.top(); nodes.pop();
    Node* left = nodes.top(); nodes.pop();
    nodes.push(new MultNode(left, right));
    parseTerm2(tokens, offset, nodes);
  }
}

void parseInt(vtp& tokens, int& offset, snp& nodes) {
  ll val = static_cast<IntToken*>(tokens[offset++])->val;
  nodes.push(new IntNode(val));
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);  //debugging
  while(scanf("%d %d", &R, &C) && R && C) {
    getchar(); // consume \n
    // read input
    FOR(i,0,R) getline(cin, input[i]);
    // collect tokens
    vtp tokens;
    collectTokens(tokens);
    // generate AST
    snp nodes;
    int offset = 0;
    parseRoot(tokens, offset, nodes);
    Node* root = nodes.top();
    // print answer
    printf("%lld\n", root->eval());
    // clean memory
    FOR(i,0,tokens.size()) delete tokens[i];
    delete root;

  }
  return 0;
}
