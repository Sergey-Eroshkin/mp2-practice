#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    string s;
    cout << "Insert expression: ";
    cin >> s;
    ArithmeticExpression one(s);
    return 0;
}
