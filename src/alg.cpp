// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Preority(char c) {
    if (c == '(')
        return 0;
    if (c == ')')
        return 1;
    if (c == '+' || c == '-')
        return 2;
    if (c == '*' || c == '/') {
        return 3;
    } else {
        return -1;
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> st1;
    std::string res;
    int k = 0;
    for (char a : inf) {
        bool flag = 1;
        if (Preority(a) == -1) {
            res += a;
            res += ' ';
            flag = 0;
        }
        if (Preority(a) == 0) {
            st1.Push(a);
            flag = 0;
        }
        if (Preority(a) > Preority(st1.get())) {
            st1.Push(a);
            flag = 0;
        }
        if (st1.isEmpty() && Preority(a) != -1) {
            st1.Push(a);
            flag = 0;
        }
        if (flag && a != ')') {
            while (Preority(st1.get()) >= Preority(a)) {
                res += st1.pop();
                res += ' ';
            }
            st1.Push(a);
        }
        if (a == ')') {
            while (st1.get() != '(') {
                res += st1.pop();
                res += ' ';
            }
            st1.pop();
        }
        if (k == inf.size() - 1) {
            while (!st1.isEmpty()) {
                res += st1.pop();
                if (st1.GetTop() != -1)
                    res += ' ';
            }
        }
        ++k;
    }
    return res;
}

int eval(std::string pref) {
    TStack<int, 100> st2;
    for (char a : pref) {
        if (a == ' ') {
            continue;
        }
        if (a == '+') {
            int p = st2.pop();
            p += st2.pop();
            st2.Push(p);
        }
        if (a == '-') {
            int p = st2.pop();
            p = st2.pop() - p;
            st2.Push(p);
        }
        if (a == '*') {
            int p = st2.pop();
            p *= st2.pop();
            st2.Push(p);
        }
        if (a == '/') {
            int p = st2.pop();
            p = st2.pop() / p;
            st2.Push(p);
        }
        if ((a - '0') > 0) {
            int o = a - '0';
            st2.Push(o);
        }
    }
    return st2.get();
}
