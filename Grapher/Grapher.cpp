#include "Grapher.h"

void Grapher::findAndReplaceAll(std::string &expression, char toReplace, const std::string &replaceWith) {
    size_t pos = expression.find(toReplace);
    while( pos != std::string::npos) {
        expression.replace(pos, 1, replaceWith);
        pos = expression.find(toReplace);
    }
}

int Grapher::get1stDot(const int number) const {
    return static_cast<int>(std::pow(2, (4-number)*2 ));
}

int Grapher::get2ndDot(int number) const {
    return static_cast<int>(std::pow(2, ((4-number)*2)+1 ));
}
