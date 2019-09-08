#pragma once
#include <sstream>
#include <iostream>
using namespace std;

bool IsSpace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

int FindEnd(const string& s, int startInd, char openSym, char closeSym)
{
    int counter = 0;
    int i = startInd;
    do
    {
        char sym = s[i++];
        if (sym == openSym)
            ++counter;
        else if (sym == closeSym)
            --counter;
    } while ((unsigned int)i < s.length() && counter != 0);

    return i;
}

// Находит позицию первого непробельного символа, начиная с current.
int MissSpaces(const string&s, int current)
{
    while ((unsigned int)current < s.length() && IsSpace(s[current]))
        ++current;

    return current;
}

string GetString(const string &s, int start)
{
    int endStr = start + 1;
    while ((unsigned int)endStr < s.length() && s[endStr] != '\"')
        ++endStr;

    if ((unsigned int)endStr == s.length())
        throw exception();

    return s.substr(start + 1, endStr - start - 1);
}

bool IsNum(char ch)
{
    return ch >= '0' && ch <= '9';
}

pair<double, int> GetNumWithLen(const string &s, int start)
{
    double result;

    int cur = start;
    //bool isDouble = false;
    while ((unsigned int)cur < s.length() && IsNum(s[cur]))
        ++cur;

    if ((unsigned int)cur == s.length())
        throw exception();

    if (s[cur] == '.')
    {
        ++cur;
        while ((unsigned int)cur < s.length() && IsNum(s[cur]))
            ++cur;
    }

    if ((unsigned int)cur == s.length())
        throw exception();


    stringstream ss;
    string str = s.substr(start, cur - start);
    ss << str;
    ss >> result;

    return pair<double, int>(result, cur - start);
}
