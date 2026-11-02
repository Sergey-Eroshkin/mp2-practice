#include <iostream>
#include "postfix_form.h"

using namespace std;

int main()
{
    try {
        string s;
        cout << "Insert expression: ";
        cin >> s;
        ArithmeticExpression one(s);
        one.GetPostfixForm();
        one.GetValues();
        cout << s << " = " << one.compute() << endl;
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
