// Задание на защите лабораторной

#include <iostream>
#include <stack>
#include <map>

using namespace std;

map<char, char> brackets = {
    {')', '('},
    {'}', '{'},
    {']', '['}
    // миллион скобок
};

bool isOpened(char c) {
     for (const auto& [close, open] : brackets) {
        if (c == open) {
            return true;
        }
    }
    return false;
}

bool isClosed(char c) {
    return brackets.find(c) != brackets.end();
}

char openBracket(char close) {
    return brackets[close];
}

bool isValid(string s) {
    stack<char> st;

    for (int i = 0; i < s.size(); ++i) {
        if (isOpened(s[i])) {
            st.push(s[i]);
        } 
        else if (st.empty()) {
            return false;
        }
        else if (isClosed(s[i])) {
            if (st.top() == openBracket(s[i])) {
                st.pop();
            }
            else {
                return false;
            }
        }
    }

    return st.empty();
}

void isOkay(string s) {
    if (isValid(s)) {
        cout << "OK" << '\n';
    }
    else {
        cout << "BAD" << '\n';
    }
}

int main() {
    {
        string s = "()";
        isOkay(s);
    }

    {
        string s = "()[]{}";
        isOkay(s);
    }

    {
        string s = "(]";
        isOkay(s);
    }

    {
        string s = "([)]";
        isOkay(s);
    }

    {
        string s = "()]";
        isOkay(s);
    }

    return 0;
}