/**
 * Algorithms used:
 *  - while-and-switch tokenizer
 *  - LL(1), recursive-descent parser
 */
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

#define FOR(i,i0,n) for(int i = i0; i < n; ++i)

int R,C;
typedef long long int ll;
string input[3];

/* ==================== */
/* Tokenization Section */
/* ==================== */

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

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

vector<Token*> tokens;

void tokenizeSimple(int col, int row, int limit) {
    while (col <= limit) {
        char c = input[row][col];
        switch (c) {
            case '-': tokens.push_back(new Token(MINUS)); col++; break;
            case '+': tokens.push_back(new Token(PLUS)); col++; break;
            case '*': tokens.push_back(new Token(MULT)); col++; break;
            default: {
                if (isDigit(c)) { //digit
                    char* endp;
                    ll num = strtoll(input[row].c_str() + col, &endp, 10);
                    col = endp - input[row].c_str();
                    tokens.push_back(new IntToken(num));
                } else { // whitespace
                    col++;
                }
                break;
            }
        }
    }
}

void collectTokens() {
    int mr = R / 2;
    int ur = mr - 1;
    int lr = mr + 1;
    int col = 0;
    char c;
    while(true) {
        c = input[mr][col];
        if (isDigit(c)) {
            char* endp;
            ll num = strtoll(input[mr].c_str() + col, &endp, 10);
            col = endp - input[mr].c_str();
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
                    tokenizeSimple(col, mr, limit);
                    tokens.push_back(new Token(ROOT_END));
                    col = limit + 1;
                    break;
                }
                case '=': {
                    int limit = col;
                    while (input[mr][limit+1] == '=') limit++;
                    tokens.push_back(new Token(FRAC_BEGIN));
                    tokenizeSimple(col, ur, limit);
                    tokens.push_back(new Token(FRAC_MID));
                    tokenizeSimple(col, lr, limit);
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

/* ==================== */
/* AST Node Structure   */
/* ==================== */

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

/**
 * Context Free Grammar
 *  formula1-> complex formula2
 *  formula2 -> + complex formula2 | - complex formula2 | epsilon
 *  complex -> sqrt | fraction | term1
 *  sqrt -> ROOT_BEGIN  simple1 ROOT_END
 *  fraction -> FRAC_BEGIN simple1 FRAC_MID simple1 FRAC_END
 *  simple1 -> term1 simple2
 *  simple2 -> + term1 simple2 | - term1 simple2 | epsilon
 *  term1 -> INTEGER term2
 *  term2 -> * INTEGER term2 | epsilon
 */

int offset;
stack<Node*> nodes;

void parseRoot();
void parseFormula1();
void parseFormula2();
void parseComplex();
void parseSimple1();
void parseSimple2();
void parseTerm1();
void parseTerm2();
void parseInt();

void parseRoot() {
    parseFormula1();
}
void parseFormula1() {
    parseComplex();
    parseFormula2();
}
void parseFormula2() {
    Token* t = tokens[offset];
    switch (t->term) {
        case PLUS: {
            offset++;
            parseComplex();
            Node* right = nodes.top(); nodes.pop();
            Node* left = nodes.top(); nodes.pop();
            nodes.push(new AddNode(left, right));
            parseFormula2();
            break;
        }
        case MINUS: {
            offset++;
            parseComplex();
            Node* right = nodes.top(); nodes.pop();
            Node* left = nodes.top(); nodes.pop();
            nodes.push(new SubNode(left, right));
            parseFormula2();
            break;
        }
    }
}

void parseComplex() {
    Token* t = tokens[offset];
    switch (t->term) {
        case ROOT_BEGIN: {
            offset++;
            parseSimple1();
            offset++;
            Node* child = nodes.top(); nodes.pop();
            nodes.push(new SqrtNode(child));
            break;
        }
        case FRAC_BEGIN: {
            offset++;
            parseSimple1();
            offset++;
            parseSimple1();
            offset++;
            Node* right = nodes.top(); nodes.pop();
            Node* left = nodes.top(); nodes.pop();
            nodes.push(new DivNode(left, right));
            break;
        }
        case INTEGER:
            parseTerm1();
            break;
    }
}

void parseSimple1() {
    parseTerm1();
    parseSimple2();
}

void parseSimple2() {
    Token* t = tokens[offset];
    switch (t->term) {
        case PLUS: {
            offset++;
            parseTerm1();
            Node* right = nodes.top(); nodes.pop();
            Node* left = nodes.top(); nodes.pop();
            nodes.push(new AddNode(left, right));
            parseSimple2();
            break;
        }
        case MINUS: {
            offset++;
            parseTerm1();
            Node* right = nodes.top(); nodes.pop();
            Node* left = nodes.top(); nodes.pop();
            nodes.push(new SubNode(left, right));
            parseSimple2();
            break;
        }
    }
}

void parseTerm1() {
    parseInt();
    parseTerm2();
}

void parseTerm2() {
    if (tokens[offset]->term == MULT) {
        offset++;
        parseInt();
        Node* right = nodes.top(); nodes.pop();
        Node* left = nodes.top(); nodes.pop();
        nodes.push(new MultNode(left, right));
        parseTerm2();
    }
}

void parseInt() {
    ll val = static_cast<IntToken*>(tokens[offset++])->val;
    nodes.push(new IntNode(val));
}

int main() {
    while(scanf("%d %d", &R, &C) && R && C) {
        getchar(); // consume \n
        // read input
        FOR(i,0,R) getline(cin, input[i]);
        // collect tokens
        collectTokens();
        // generate AST
        parseRoot();
        Node* root = nodes.top();
        // print answer
        printf("%lld\n", root->eval());
        // clean memory
        FOR(i,0,tokens.size()) delete tokens[i];
        delete root;
        nodes.pop();
        tokens.clear();
        offset = 0;
    }
    return 0;
}
