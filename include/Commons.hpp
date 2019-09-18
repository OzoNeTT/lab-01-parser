#pragma once
#include <sstream>
#include <iostream>
#include <unordered_set>
using namespace std;

bool IsSpace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

int FindEnd(const string& s, int startInd, char openSym, char closeSym)
{

    int i = 0;
    int openC = 1;
    int closeC = 0;
    for(unsigned int j = startInd + 1; j < s.length(); j++) {
        char symbol = s[j];
        if(symbol == openSym)
            openC++;
        else if(symbol == closeSym)
            closeC++;

        if(openC == closeC) {
            i = j;
            break;
        }
    }
    return i + 1;
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

    if ((unsigned int)endStr >= s.length())
        throw exception();

    return s.substr(start + 1, endStr - start - 1);
}

bool IsNum(char ch)
{
    std::unordered_set<char> set{'0','9', '8','7','6','5','4','3','2','1', '.'};
    return set.find(ch) != set.cend();
}

pair<double, int> GetNumWithLen(const string &s, int start)
{
    double result;
    int cur = start;
    while ((unsigned int)cur < s.length() && IsNum(s[cur]))
        ++cur;

    if ((unsigned int)cur == s.length())
        throw exception();

    stringstream ss;
    string str = s.substr(start, cur - start);
    ss << str;
    ss >> result;

    return pair<double, int>(result, cur - start);
}
