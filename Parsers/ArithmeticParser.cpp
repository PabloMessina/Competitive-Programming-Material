/**
 * Implementation of LL(1), recursive-descent Parser
 * for Arithmetic Expressions
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
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
      double num = 0;
      do {
        num = num * 10 + c - '0';
        c = buffer[++offset];
      } while (isDigit(c));
      return new NumberToken(num);
    }
    sprintf(errorBuffer, "unexpected char '%c' at position %d\n", c, offset);
    throw std::runtime_error(errorBuffer);
  }
}

/**
 * Context Free Grammar:
 *  Root    ->  AddSum1 END
 *  AddSum1   ->  MultDiv1 AddSum2
 *  AddSum2   ->  + MultDiv1 AddSum2 | - MultDiv1 AddSum2 | epsilon
 *  MultDiv1  ->  Term MultDiv2
 *  MultDiv2  ->  * Term MultDiv2 | / Term MultiDiv2 | epsilon
 *  Term    ->  - Term | (AddSum1) | NUMBER
 */

struct ASTNode {
  virtual ~ASTNode() {};
  virtual double eval() = 0;
};
struct DoubleOpNode: ASTNode {
  ASTNode* left;
  ASTNode* right;
  DoubleOpNode(ASTNode* left, ASTNode* right): left(left), right(right) {}
  ~DoubleOpNode() { delete left; delete right; }
};
struct SingleOpNode: ASTNode {
  ASTNode* child;
  SingleOpNode(ASTNode* child): child(child) {}
  ~SingleOpNode() { delete child; }
};
struct AddNode : DoubleOpNode {
  AddNode(ASTNode* left, ASTNode* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() + right->eval(); }
};
struct SubNode : DoubleOpNode {
  SubNode(ASTNode* left, ASTNode* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() - right->eval(); }
};
struct MultNode : DoubleOpNode {
  MultNode(ASTNode* left, ASTNode* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() * right->eval(); }
};
struct DivNode : DoubleOpNode {
  DivNode(ASTNode* left, ASTNode* right) : DoubleOpNode(left, right) {}
  double eval() { return left->eval() / right->eval(); }
};
struct NegNode : SingleOpNode {
  NegNode(ASTNode* child) : SingleOpNode(child) {}
  double eval() { return -child->eval(); }
};
struct IntegerNode : ASTNode {
  double value;
  IntegerNode(double value) : value(value) {}
  double eval() { return value; }
};

void throwUnexpectedTerminalException(Terminal terminal, int offset);
void matchAndConsume(vtp tokens, int& offset, Terminal terminal);
void parseTerm(vtp tokens, int& offset, stack<ASTNode*>& nodes);
void parseMultDiv1(vtp& tokens, int& offset, stack<ASTNode*>& nodes);
void parseMultDiv2(vtp& tokens, int& offset, stack<ASTNode*>& nodes);
void parseAddSub1(vtp& tokens, int& offset, stack<ASTNode*>& nodes);
void parseAddSub2(vtp& tokens, int& offset, stack<ASTNode*>& nodes);
void parseRoot(vtp& tokens, int& offset, stack<ASTNode*>& nodes);

void throwUnexpectedTerminalException(Terminal terminal, int offset) {
  sprintf(errorBuffer, "unexpected terminal %s at position %d\n", terminal2String(terminal), offset);
  throw std::runtime_error(errorBuffer);
}
void matchAndConsume(vtp tokens, int& offset, Terminal terminal) {
  if (tokens[offset]->terminal != terminal) {
    sprintf(errorBuffer, "expected terminal %s but found %s\n",
      terminal2String(terminal),
      terminal2String(tokens[offset]->terminal));
    throw std::runtime_error(errorBuffer);
  }
  offset++;
}
void parseTerm(vtp tokens, int& offset, stack<ASTNode*>& nodes) {
  Token* t = tokens[offset];
  switch (t->terminal) {
    case MINUS: {
      offset++;
      parseTerm(tokens, offset, nodes);
      // generate node
      ASTNode* child = nodes.top(); nodes.pop();
      nodes.push(new NegNode(child));
      break;
    }
    case OPEN_PAREN: {
      offset++;
      parseAddSub1(tokens, offset, nodes);
      matchAndConsume(tokens, offset, CLOSE_PAREN);
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
void parseMultDiv1(vtp& tokens, int& offset, stack<ASTNode*>& nodes) {
  parseTerm(tokens, offset, nodes);
  parseMultDiv2(tokens, offset, nodes);
}
void parseMultDiv2(vtp& tokens, int& offset, stack<ASTNode*>& nodes) {
  Token* t = tokens[offset];
  switch (t->terminal) {
    case MULT: {
      offset++;
      parseTerm(tokens, offset, nodes);
      // generate node
      ASTNode* right = nodes.top(); nodes.pop();
      ASTNode* left = nodes.top(); nodes.pop();
      nodes.push(new MultNode(left, right));
      // resume parsing
      parseMultDiv2(tokens, offset, nodes);
      break;
    }
    case DIV: {
      offset++;
      parseTerm(tokens, offset, nodes);
      // generate node
      ASTNode* right = nodes.top(); nodes.pop();
      ASTNode* left = nodes.top(); nodes.pop();
      nodes.push(new DivNode(left, right));
      // resume parsing
      parseMultDiv2(tokens, offset, nodes);
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
void parseAddSub2(vtp& tokens, int& offset, stack<ASTNode*>& nodes) {
  Token* t = tokens[offset];
  switch (t->terminal) {
    case PLUS: {
      offset++;
      parseMultDiv1(tokens, offset, nodes);
      // generate node
      ASTNode* right = nodes.top(); nodes.pop();
      ASTNode* left = nodes.top(); nodes.pop();
      nodes.push(new AddNode(left, right));
      // resume parsing
      parseAddSub2(tokens, offset, nodes);
      break;
    }
    case MINUS: {
      offset++;
      parseMultDiv1(tokens, offset, nodes);
      // generate node
      ASTNode* right = nodes.top(); nodes.pop();
      ASTNode* left = nodes.top(); nodes.pop();
      nodes.push(new SubNode(left, right));
      // resume parsing
      parseAddSub2(tokens, offset, nodes);
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
void parseAddSub1(vtp& tokens, int& offset, stack<ASTNode*>& nodes) {
  parseMultDiv1(tokens, offset, nodes);
  parseAddSub2(tokens, offset, nodes);
}
void parseRoot(vtp& tokens, int& offset, stack<ASTNode*>& nodes) {
  parseAddSub1(tokens, offset, nodes);
  matchAndConsume(tokens, offset, END);
}


int main() {
  string line;
  while (true) {
    /*  read input */
    getline(cin, line);
    if (line == "exit") break;

    /* get tokens */
    vtp tokens;
    int offset = 0;
    while(true) {
      Token* t = getNextToken(line.c_str(), offset);
      tokens.push_back(t);
      if (t->terminal == END) break;
    }

    /* parse tokens to generate AST */
    stack<ASTNode*> nodes;
    offset = 0;
    parseRoot(tokens, offset, nodes);
    ASTNode* root = nodes.top();

    /* print result */
    printf("==> %lf\n", root->eval());

    /* clean memory */
    delete root;
    for (int i = 0, l = tokens.size(); i < l; ++i) delete tokens[i];
  }
  return 0;
}
