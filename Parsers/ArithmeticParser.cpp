/**
 * Implementation of LL(1), recursive-descent Parser
 * for Arithmetic Expressions
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cstdlib>
#include <stdexcept>
using namespace std;

char errorBuffer[200];

enum Terminal { NUMBER, MINUS, PLUS, DIV, MULT, OPEN_PAREN, CLOSE_PAREN, END };

const char * terminal2String(Terminal t) {
  switch (t) {
  case NUMBER: return "NUMBER";
  case MINUS: return "MINUS";
  case PLUS: return "PLUS";
  case DIV: return "DIV";
  case MULT: return "MULT";
  case OPEN_PAREN: return "OPEN_PAREN";
  case CLOSE_PAREN: return "CLOSE_PAREN";
  default: return "END";
  }
}

struct Token {
  Terminal terminal;
  Token(Terminal t) :
      terminal(t) {
  }
};

struct NumberToken: Token {
  double value;
  NumberToken(double value) :
      Token(NUMBER), value(value) {
  }
};

typedef vector<Token*> vtp;


void skipWhitespace(const char* buffer, int& offset) {
  while (true) {
    char c = buffer[offset];
    if (c == ' ' || c == '\t') offset++;
    else break;
  }
}

bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

Token* getNextToken(const char* buffer, int& offset) {
  skipWhitespace(buffer, offset);
  char c = buffer[offset];
  switch (c) {
  case '(':
    offset++;
    return new Token(OPEN_PAREN);
  case ')':
    offset++;
    return new Token(CLOSE_PAREN);
  case '*':
    offset++;
    return new Token(MULT);
  case '/':
    offset++;
    return new Token(DIV);
  case '+':
    offset++;
    return new Token(PLUS);
  case '-':
    offset++;
    return new Token(MINUS);
  case '\0':
    return new Token(END);
  default:
    if (isDigit(c)) {
      char* endp;
      double num = strtod(buffer + offset, &endp);
      offset = endp - buffer;
      return new NumberToken(num);
    }
    sprintf(errorBuffer, "unexpected char '%c' at position %d\n", c, offset);
    throw std::runtime_error(errorBuffer);
  }
}

struct Node {
  virtual ~Node() {};
  virtual double eval() = 0;
};
struct DoubleOpNode: Node {
  Node* left;
  Node* right;
  DoubleOpNode(Node* left, Node* right): left(left), right(right) {}
  ~DoubleOpNode() { delete left; delete right; }
};
struct SingleOpNode: Node {
  Node* child;
  SingleOpNode(Node* child): child(child) {}
  ~SingleOpNode() { delete child; }
};
struct AddNode : DoubleOpNode {
  AddNode(Node* left, Node* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() + right->eval(); }
};
struct SubNode : DoubleOpNode {
  SubNode(Node* left, Node* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() - right->eval(); }
};
struct MultNode : DoubleOpNode {
  MultNode(Node* left, Node* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() * right->eval(); }
};
struct DivNode : DoubleOpNode {
  DivNode(Node* left, Node* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() / right->eval(); }
};
struct NegNode : SingleOpNode {
  NegNode(Node* child) : SingleOpNode(child) {}
  double eval() { return -child->eval(); }
};
struct IntegerNode : Node {
  double value;
  IntegerNode(double value) : value(value) {}
  double eval() { return value; }
};

/**
 * Context Free Grammar:
 *  Root    ->  AddSum1 END
 *  AddSum1   ->  MultDiv1 AddSum2
 *  AddSum2   ->  + MultDiv1 AddSum2 | - MultDiv1 AddSum2 | epsilon
 *  MultDiv1  ->  Term MultDiv2
 *  MultDiv2  ->  * Term MultDiv2 | / Term MultiDiv2 | epsilon
 *  Term    ->  - Term | (AddSum1) | NUMBER
 */

vector<Token*> tokens;
int offset;
stack<Node*> nodes;

void throwUnexpectedTerminalException(Terminal terminal, int offset);
void matchAndConsume(Terminal terminal);
void parseTerm();
void parseMultDiv1();
void parseMultDiv2();
void parseAddSub1();
void parseAddSub2();
void parseRoot();

void throwUnexpectedTerminalException(Terminal terminal, int offset) {
  sprintf(errorBuffer, "unexpected terminal %s at position %d\n", terminal2String(terminal), offset);
  throw std::runtime_error(errorBuffer);
}
void matchAndConsume(Terminal terminal) {
  if (tokens[offset]->terminal != terminal) {
    sprintf(errorBuffer, "expected terminal %s but found %s\n",
      terminal2String(terminal),
      terminal2String(tokens[offset]->terminal));
    throw std::runtime_error(errorBuffer);
  }
  offset++;
}
void parseTerm() {
  Token* t = tokens[offset];
  switch (t->terminal) {
    case MINUS: {
      offset++;
      parseTerm();
      // generate node
      Node* child = nodes.top(); nodes.pop();
      nodes.push(new NegNode(child));
      break;
    }
    case OPEN_PAREN: {
      offset++;
      parseAddSub1();
      matchAndConsume(CLOSE_PAREN);
      break;
    }
    case NUMBER: {
      offset++;
      // generate node
      double value = static_cast<NumberToken*>(t)->value;
      nodes.push(new IntegerNode(value));
      break;
    }
    default:
      throwUnexpectedTerminalException(t->terminal, offset);
      break;
  }
}
void parseMultDiv1() {
  parseTerm();
  parseMultDiv2();
}
void parseMultDiv2() {
  Token* t = tokens[offset];
  switch (t->terminal) {
    case MULT: {
      offset++;
      parseTerm();
      // generate node
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new MultNode(left, right));
      // resume parsing
      parseMultDiv2();
      break;
    }
    case DIV: {
      offset++;
      parseTerm();
      // generate node
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new DivNode(left, right));
      // resume parsing
      parseMultDiv2();
      break;
    }
    // follow set
    case PLUS: case MINUS: case END: case CLOSE_PAREN:
      break;
    default:
      throwUnexpectedTerminalException(t->terminal, offset);
      break;
  }
}
void parseAddSub2() {
  Token* t = tokens[offset];
  switch (t->terminal) {
    case PLUS: {
      offset++;
      parseMultDiv1();
      // generate node
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new AddNode(left, right));
      // resume parsing
      parseAddSub2();
      break;
    }
    case MINUS: {
      offset++;
      parseMultDiv1();
      // generate node
      Node* right = nodes.top(); nodes.pop();
      Node* left = nodes.top(); nodes.pop();
      nodes.push(new SubNode(left, right));
      // resume parsing
      parseAddSub2();
      break;
    }
    // follow set
    case END: case CLOSE_PAREN:
      break;
    default:
      throwUnexpectedTerminalException(t->terminal, offset);
      break;
  }
}
void parseAddSub1() {
  parseMultDiv1();
  parseAddSub2();
}
void parseRoot() {
  parseAddSub1();
  matchAndConsume(END);
}


int main() {
  string line;
  while (true) {
    /*  read input */
    getline(cin, line);
    if (line == "exit") break;

    /* get tokens */
    int index = 0;
    while(true) {
      Token* t = getNextToken(line.c_str(), index);
      tokens.push_back(t);
      if (t->terminal == END) break;
    }

    /* parse tokens to generate AST */
    parseRoot();
    Node* root = nodes.top();

    /* print result */
    printf("==> %lf\n", root->eval());

    /* clean memory */
    delete root;
    for (int i = 0, l = tokens.size(); i < l; ++i) delete tokens[i];
    tokens.clear();
    nodes.pop();
    offset = 0;
  }
  return 0;
}
