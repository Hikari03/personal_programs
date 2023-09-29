#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

// Code from https://gist.github.com/t-mat/b9f681b7591cdae712f6

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <tuple>
#include <cstdio>
#include <cmath>

static const char* reportFmt = "|%-5s|%-32s|%17s| %s\n";

class Calculator {
public:
    static double calculate(const std::string& expression);

private:

    struct Token{
        enum class Type {
            Unknown,
            Number,
            Operator,
            LeftParenthesis,
            RightParenthesis
        };

        const Type type;
        const std::string value;
        const int precedence = -1;
        const bool isRightAssociative = false;
        const bool isUnary = false;
    };

    static std::deque<Token> tokenize(const std::string& expression);

    static std::deque<Token> shuntingYard(const std::deque<Token> &tokens);

    template<class T, class U>
    void debugReport(
          const Calculator::Token& token
        , const T& queue
        , const U& stack
        , const std::string& comment = ""
    ) {
        std::ostringstream ossQueue;
        for(const auto& t : queue) {
            ossQueue << " " << t;
        }

        std::ostringstream ossStack;
        for(const auto& t : stack) {
            ossStack << " " << t;
        }

        printf(reportFmt
               , token.value.c_str()
               , ossQueue.str().c_str()
               , ossStack.str().c_str()
               , comment.c_str()
        );
    }
};


#endif //CALCULATOR_CALCULATOR_H
