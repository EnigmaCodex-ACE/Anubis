#include<iostream>
#include<string>
#include<vector>
#include<map>
// TOKS
#define NONEC (char)0

constexpr std::string_view INT = "INT";
constexpr std::string_view FLOAT = "FLOAT";

constexpr std::string_view ID = "ID";

constexpr std::string_view ADD = "ADD";
constexpr std::string_view SUB = "SUB";
constexpr std::string_view MUL = "MUL";
constexpr std::string_view DIV = "DIV";
constexpr std::string_view MOD = "MOD";
constexpr std::string_view EQL = "EQL";
constexpr std::string_view LPAR = "LPAR";
constexpr std::string_view RPAR = "RPAR";
constexpr std::string_view ERR = "ERR";


using namespace std;

class Token {
    public:
    string type;
    string value;

    Token(string_view type, string value = ""){
        this->type = type;
        this->value = value;
    }

    string repr(){
        if(value == ""){
            return "OP:" + type;
        }
        return "OP:" + type + " :: VAL:" + value;
    }

    operator string() const{
        if(value == ""){
            return this->type;
        }else{
            return this->type + ":" + this->value;
        }
    }
};

class LexicalInterpreter {
    private:
    bool isDigit(char c){
        return c >= '0' && c <= '9';
    }

    Token makeNumberToken(){
        string number = "";
        int dots = 0;
        while(isDigit(this->current) || this->current == '.'){
            if(this->current == '.'){
                dots++;
            }
            if(dots > 1){
                break;
                return Token(ERR, "Last time I Checked Numbers only have single dot");
            }
            number += this->current;
            this->nxt_line();
        }
        if(dots == 0){
            return Token(INT, number);
        }else{
            return Token(FLOAT, number);
        }
    }


    public:
    string text;
    int pos;
    char current;

    LexicalInterpreter(string text){
        this->text = text;
        this->pos = -1;
        this->current = NONEC;
        this->nxt_line();
    }

    void nxt_line(){
        this->pos++;
        if(this->pos >= this->text.length()){
            this->current = NONEC;
        }else{
            this->current = this->text[this->pos];
        }
    }

    vector<Token> make_tokens(){
        vector<Token> Tokens;
        while(this->current != NONEC){
            if(this->current ==  '\t'){
                this->nxt_line();
                continue;
            }else if(this->current == ' '){
                this->nxt_line();
                continue;
            }else if(this->current == '\n'){
                this->nxt_line();
                continue;
            }else if(isDigit(this->current)){
                Tokens.push_back(this->makeNumberToken());
            }else if(this->current == '+'){
                Tokens.push_back(Token(ADD));
                this->nxt_line();
            }else if(this->current == '-'){
                Tokens.push_back(Token(SUB));
                this->nxt_line();
            }else if(this->current == '*'){
                Tokens.push_back(Token(MUL));
                this->nxt_line();
            }else if(this->current == '/'){
                Tokens.push_back(Token(DIV));
                this->nxt_line();
            }else if(this->current == '%'){
                Tokens.push_back(Token(MOD));
                this->nxt_line();
            }else if(this->current == '='){
                Tokens.push_back(Token(EQL));
                this->nxt_line();
            }else if(this->current == '('){
                Tokens.push_back(Token(LPAR));
                this->nxt_line();
            }else if(this->current == ')'){
                Tokens.push_back(Token(RPAR));
                this->nxt_line();
            }else{         
                return Tokens = {Token(ERR, "WhatDidYouTypeError: Error Occured at" + this->pos)};
            }
        }
        return Tokens;
    }

};


int main(void){
    while(true){
        string input;
        cin >> input;
        LexicalInterpreter lex = LexicalInterpreter(input);
        vector<Token> tokens = lex.make_tokens();
        for(Token token : tokens){
            cout << token.repr() << endl;
        }
    }
}
