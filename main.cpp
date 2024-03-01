#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "TextProcessing.cpp"
#include "FileOperations.cpp"
#include "CommandProccessing.cpp"
// #include <bits/stdc++.h>

#include "MasterFile.cpp" //БДшка юзерів для прикладу

struct Delivery
{
    uint32_t supplier_code = 0;
    uint32_t part_code = 0;
    uint32_t price = 0;
    uint32_t quantity = 0;

    char name[25] = {};

    int32_t next = -1;
};

// bool SetNextPtr(std::fstream& file, const std::streampos& record_pos, const std::streampos& next_record_pos)
// {
//     Delivery tmp;

//     if (!Read(tmp, file, record_pos))
//     {
//         std::cerr << "Unable to set next ptr. Read failed" << std::endl;
//         return false;
//     }

//     tmp.next = next_record_pos;

//     if (!Write(tmp, file, record_pos))
//     {
//         std::cerr << "Unable to set next ptr. Read failed" << std::endl;
//         return false;
//     }

//     return true;
// }

// bool AddNode(const Delivery& record, std::fstream& file, const std::streampos& pos, const std::streampos& prev_record_pos = -1)
// {
//     if (!Write(record, file, pos))
//     {
//         return false;
//     }

//     if (prev_record_pos == -1)
//         return true;

//     return SetNextPtr(file, prev_record_pos, pos);
// }

// void PrintNodes(std::fstream& file, const std::streampos& record_pos)
// {
//     Delivery tmp;

//     std::streampos read_pos = record_pos;

//     while (read_pos != -1)
//     {
//         if (!Read(tmp, file, read_pos))
//         {
//             std::cerr << "Unable to update next_ptr. Error: read failed" << std::endl;
//             return;
//         }

//         std::cout << tmp << std::endl;
//         read_pos = tmp.next;
//     }
// }

using namespace std;

std::fstream initFile(string FileName)
{
    std::fstream file(FileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    auto err = errno;

    if (err == ENOENT)
    {
         file = std::fstream(FileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    }

    if (!file) {
        std::cerr << "Unable to open file=" << FileName << std::endl;
    }
    Header Mainheader = Header(0, 0, -1, -1, -1);
    Write(Mainheader, file, GetHeaderPos());
    return file;
}
int main()
{
    const std::string MasterFileName = "Users.bin";
    const std::string SlaveFileName = "Submissions.bin";
    std::fstream MasterFile = initFile(MasterFileName);
    std::fstream SlaveFile = initFile(SlaveFileName);
    
    for(auto words : commands)
    {
        ProcessCommand(words, SlaveFile, MasterFile);
    }

    string input;
    while(true)
    {
        try
        {
            getline(cin, input);
            if(input == "exit")
            {
                break;
            }
            if(!input.empty())
            {
                vector<string>words = Split(input, ' ');
                ProcessCommand(words, SlaveFile, MasterFile);
            }
        }
        catch(exception e)
        {
            std::cout << "An error has occured during the execution of a program.\n" << e.what() << std::endl;
            break;
        }
    }

    return 0;
}