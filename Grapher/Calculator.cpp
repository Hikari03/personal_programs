#include "Calculator.h"

double Calculator::calculate(const std::string &expression) {
//    printf("Tokenize\n");
//    printf(reportFmt, "Token", "Queue", "Stack", "");
    const auto tokens = tokenize(expression);
    auto queue = shuntingYard(tokens);
    std::vector<double> stack;

//    printf("\nCalculation\n");
//    printf(reportFmt, "Token", "Queue", "Stack", "");

    while(! queue.empty()) {
        std::string op;

        const auto token = queue.front();
        queue.pop_front();
        switch(token.type) {
        case Token::Type::Number:
            stack.push_back(std::stoi(token.value));
            op = "Push " + token.value;
            break;

        case Token::Type::Operator:
            {
                if(token.isUnary) {
                    // unary operators
                    const auto rhs = stack.back();
                    stack.pop_back();
                    switch(token.value[0]) {
                    default:
                        throw std::runtime_error("Operator error: " + token.value);

                    case 'm':                   // Special operator name for unary '-'
                        stack.push_back(-rhs);
                        break;
                    }
                    op = "Push (unary) " + token.value + " " + std::to_string(rhs);
                } else {
                    // binary operators
                    const auto rhs = stack.back();
                    stack.pop_back();
                    const auto lhs = stack.back();
                    stack.pop_back();

                    switch(token.value[0]) {
                    default:
                        throw std::runtime_error("Operator error: " + token.value);

                    case '^':
                        stack.push_back(static_cast<int>(pow(lhs, rhs)));
                        break;
                    case '*':
                        stack.push_back(lhs * rhs);
                        break;
                    case '/':
                        stack.push_back(lhs / rhs);
                        break;
                    case '+':
                        stack.push_back(lhs + rhs);
                        break;
                    case '-':
                        stack.push_back(lhs - rhs);
                        break;
                    }
                    op = "Push " + std::to_string(lhs) + " " + token.value + " " + std::to_string(rhs);
                }
            }
            break;

        default:
            throw std::runtime_error("Token error: " + token.value);
        }
        //debugReport(token, queue, stack, op);
    }

    return stack.back();
}

std::deque<Calculator::Token> Calculator::tokenize(const std::string & expression) {
    std::deque<Token> tokens;

    for(const auto * c = expression.c_str(); *c; ++c) {
        if(isblank(*c)) {
            continue;
        }
        else if(isdigit(*c)) {
            const auto ptr = c;
            while(isdigit(*c)) {
                ++c;
            }

            const auto s = std::string(ptr, c);

            tokens.push_back({Token::Type::Number, s});
            --c;
        }
        else {
            Token::Type type = Token::Type::Unknown;
            int precedence = -1;
            bool isRightAssociative = false;
            bool isUnary = false;
            char p = *c;

            switch (p) {
                default: break;
                case '(':
                    type = Token::Type::LeftParenthesis;
                    break;

                case ')':
                    type = Token::Type::RightParenthesis;
                    break;

                case '^':
                    type = Token::Type::Operator;
                    precedence = 4;
                    isRightAssociative = true;
                    break;

                case '*':
                case '/':
                    type = Token::Type::Operator;
                    precedence = 3;
                    break;

                case '+':
                    type = Token::Type::Operator;
                    precedence = 2;
                    break;

                case '-':
                    if( tokens.empty() || tokens.back().type == Token::Type::Operator || tokens.back().type == Token::Type::LeftParenthesis ) {
                        isUnary = true;
                        p = 'm';
                        type = Token::Type::Operator;
                        precedence = 5;
                    }
                    else {
                        type = Token::Type::Operator;
                        precedence = 2;
                    }
                    break;

            }

            const auto s = std::string(1, p);
            tokens.push_back({type, s, precedence, isRightAssociative, isUnary});
        }
    }

    return tokens;
}

std::deque<Calculator::Token> Calculator::shuntingYard(const std::deque<Token>& tokens) {
    std::deque<Token> queue;
    std::vector<Token> stack;

    // While there are tokens to be read:
    for(auto & token : tokens) {
        // Read a token
        switch(token.type) {
        case Token::Type::Number:
            // If the token is a number, then add it to the output queue
            queue.push_back(token);
            break;

        case Token::Type::Operator:
            {
                // If the token is operator, o1, then:
                const auto o1 = token;

                // while there is an operator token,
                while(!stack.empty()) {
                    // o2, at the top of stack, and
                    const auto o2 = stack.back();

                    // either o1 is left-associative and its precedence is
                    // *less than or equal* to that of o2,
                    // or o1 if right associative, and has precedence
                    // *less than* that of o2,
                    if(
                        (! o1.isRightAssociative && o1.precedence <= o2.precedence)
                    ||  (  o1.isRightAssociative && o1.precedence <  o2.precedence)
                    ) {
                        // then pop o2 off the stack,
                        stack.pop_back();
                        // onto the output queue;
                        queue.push_back(o2);

                        continue;
                    }

                    // @@ otherwise, exit.
                    break;
                }

                // push o1 onto the stack.
                stack.push_back(o1);
            }
            break;

        case Token::Type::LeftParenthesis:
            // If token is left parenthesis, then push it onto the stack
            stack.push_back(token);
            break;

        case Token::Type::RightParenthesis:
            // If token is right parenthesis:
            {
                bool match = false;

                // Until the token at the top of the stack
                // is a left parenthesis,
                while(! stack.empty() && stack.back().type != Token::Type::LeftParenthesis) {
                    // pop operators off the stack
                    // onto the output queue.
                    queue.push_back(stack.back());
                    stack.pop_back();
                    match = true;
                }

                if(!match && stack.empty()) {
                    // If the stack runs out without finding a left parenthesis,
                    // then there are mismatched parentheses.
                    printf("RightParen error (%s)\n", token.value.c_str());
                    return {};
                }

                // Pop the left parenthesis from the stack,
                // but not onto the output queue.
                stack.pop_back();
            }
            break;

        default:
            printf("error (%s)\n", token.value.c_str());
            return {};
        }

        //debugReport(token, queue, stack);
    }

    // When there are no more tokens to read:
    //   While there are still operator tokens in the stack:
    while(! stack.empty()) {
        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if(stack.back().type == Token::Type::LeftParenthesis) {
            printf("Mismatched parentheses error\n");
            return {};
        }

        // Pop the operator onto the output queue.
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }

    //debugReport(Token { Token::Type::Unknown, "End" }, queue, stack);

    //Exit.
    return queue;
}


