#pragma once
#include "User.cpp"

using namespace std;
User users[] = 
{
    User(1, "AqilAliyev", "qifu", 3590, 0, 1),
    User(2, "Lenkeran", "advd", 3572, 0, 2),
    User(3, "vvp", "13rf", 3441, 0, 3),
    User(4, "crowdforces", "1488", 3396, 1, 4),
    User(5, "yxrix", "1344", 3375, 0, 5),
    User(6, "condor", "1344", 3331, 1, 6),
    User(7, "medv", "1344", 3020, 0, 7),
    User(8, "tyamgin", "1344", 2832, 0, 8),
    User(9, "bdp", "1344", 2811, 0, 9),
    User(10, "RVYTN2015GAA", "1344", 2641, 0, -1)
};
std::vector<std::vector<string> >commands = 
{
    {"insert-m", "1", "AqilAliyev", "qifu", "3590", "0"},
    {"insert-m", "2", "Lenkeran", "advd", "3572", "0",},
    {"insert-m", "3", "vvp", "13rf", "3441", "0",},
    {"insert-m", "4", "crowdforces", "1488", "3396", "1"},
    {"insert-m", "5", "yxrix", "1344", "3375", "0"},
    {"insert-s", "1", "1", "1", "WA"},
    {"insert-s", "2", "1", "1", "TL"},
    {"insert-s", "3", "1", "1", "WA"},
    {"insert-s", "4", "1", "1", "AC"},
    {"insert-s", "5", "2", "13", "WA"},
    {"insert-s", "6", "2", "11", "AC"},
};
