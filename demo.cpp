#include <iostream>
#include "parser.hpp"

using namespace std;

int main() {
    auto f = parse("sin(x) + cos(y)");
    cout << f(0, 3.14 / 2) << "\n";
}