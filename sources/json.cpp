#include <iostream>

#include "../include/my_json.hpp"
#include "../include/Commons.hpp"

using namespace std;


Json::Json(const string & s)
{
    int i = 0;
    i = MissSpaces(s, i);

    if (s[i] == '{')
    {
        _isArray = false;
        _obj = GetMap(s, i + 1);
    }
    else if (s[i] == '[')
    {
        _isArray = true;
        _arr = GetArray(s, i + 1);
    }
    else
        throw exception();
}

bool Json::is_array() const
{
    return _isArray;
}

bool Json::is_object() const
{
    return !_isArray;
}

int Json::GetArrSize() const
{
    if (is_array())
        return _arr.size();
    else
        throw;
}

pair<any, int> GetValueAndLen(const string &s, int start)
{
    any result;
    int i = start;
    int endObj = 0;

    if (s[i] == '{')
    {
        endObj = FindEnd(s, i, '{', '}');

        string str = s.substr(i, endObj - i);
        result = Json(str);
        i = endObj;
    }
    else if (s[i] == '[')
    {
        endObj = FindEnd(s, i, '[', ']');

        string str = s.substr(i, endObj - i);
        result = Json(str);
        i = endObj;
    }
    else if (s[i] == '\"')
    {
        string str = GetString(s, i);
        i += str.length() + 2;
        result = str;
    }
    else if (IsNum(s[i]))
    {
        pair<any, int> p = GetNumWithLen(s, i);
        i += p.second;
        result = p.first;
    }
    else if (s.substr(i, 5) == "false")
    {
        i += 5;
        result = false;
    }
    else if (s.substr(i, 4) == "true")
    {
        i += 4;
        result = true;
    }
    else if (s.substr(i, 4) == "null")
    {
        i += 4;
        result = nullptr;
    }
    else
        throw exception();

    return pair<any, int>(result, i - start);
}

any & Json::operator[](const std::string & key)
{
    if (is_object())
        return _obj[key];

    throw exception();
}

any & Json::operator[](int index)
{
    if (is_array())
        return _arr[index];

    throw exception();
}

Json Json::parse(const std::string & s)
{
    return Json(s);
}

vector<any> Json::GetArray(const string &s, int start) const
{
    vector<any> result;
    unsigned int i = start;

    while (i < s.length())
    {
        i = MissSpaces(s, i);
        pair<any, int> p = GetValueAndLen(s, i);

        i += p.second;
        result.push_back(p.first);

        i = MissSpaces(s, i);
        if (s[i] == ']')
            break;

        if (s[i++] == ',')
            continue;

        throw exception();
    }

    return result;
}

std::map<std::string, any> Json::GetMap(const std::string & s, int start) const
{
    std::map<std::string, any> result;

    unsigned int i = start;

    while (i < s.length())
    {
        i = MissSpaces(s, i);
        if (s[i] != '\"')
            throw exception();

        string key = GetString(s, i);
        i += key.length() + 2;
        i = MissSpaces(s, i);
        if (s[i++] != ':')
            throw exception();

        i = MissSpaces(s, i);
        pair<any, int> p = GetValueAndLen(s, i);

        result[key] = p.first;

        i += p.second;

        i = MissSpaces(s, i);
        if (s[i] == '}')
            break;

        if (s[i++] == ',')
            continue;

        throw exception();
    }

    return result;
}
