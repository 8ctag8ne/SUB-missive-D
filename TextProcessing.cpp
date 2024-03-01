#pragma once
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
vector<string> Split(string input, char delimiter)
{
    vector<string>ans;
    for(int32_t i = 0; i< input.size(); i++)
    {
        int32_t j = i;
        while(j < input.size() && input[j] != delimiter)
        {
            j++;
        }
        string s = input.substr(i, j-i);
        if(s.size() > 0)
        {
            ans.push_back(s);
        }

        i = j;
    }

    return ans;
}

bool IsNumber(string s)
{
    if(!isdigit(s[0]) && s[0] != '-')
    {
        return false;
    }
    for(int32_t i = 1; i < s.size(); i++)
    {
        if(!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

int32_t StringToInt(string s)
{
    int32_t i = (s[0] == '-');
    int32_t ans = 0;
    for(int32_t j = i; j < s.size(); j++)
    {
        if(!isdigit(s[j]))
        {
            return -1;
        }
        ans = ans * 10 + s[j] - '0';
    }

    if(i)
    {
        ans *= -1;
    }
    return ans;
}

string IntToString(int32_t n)
{
    if(n == 0)
    {
        return "0";
    }

    string s;
    while(n)
    {
        s += n%10 + '0';
        n /= 10;
    }
    reverse(s.begin(), s.end());

    return s;
}

string BoolToString(bool f)
{
    if(f)
    {
        return "true";
    }
    return "false";
}

string StringToUpper(string s)
{
    string ans;
    for(auto i:s)
    {
        ans+=toupper(i);
    }
    return ans;
}

bool IsBool(string s)
{
    return (s == "0" || s == "1" || s == "true" || s == "false");
}

bool StringToBool(string s)
{
    if(s == "true" || s == "1")
    {
        return true;
    }
    return false;
}

std::string DividingStr(std::vector<int32_t>sizes)
{
    std::string s = "+";
    for(auto i : sizes)
    {
        for(int32_t j = 0; j<i; j++)
        {
            s+="-";
        }
        s+="+";
    }
    return s;
}