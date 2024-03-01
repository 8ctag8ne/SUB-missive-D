#pragma once
#include <fstream>
#include <iostream>
#include "User.cpp"
#include "Submission.cpp"

bool Read(User& record, std::fstream& file, const std::streampos& pos)
{
    if (!file)
        return false;

    file.seekg(pos);
    file.read(reinterpret_cast<char*>(&record), sizeof(User));

    return !file.fail();
}

bool Read(Submission& record, std::fstream& file, const std::streampos& pos)
{
    if (!file)
        return false;

    file.seekg(pos);
    file.read(reinterpret_cast<char*>(&record), sizeof(Submission));

    return !file.fail();
}

bool Read(Header& record, std::fstream& file, const std::streampos& pos)
{
    if (!file)
        return false;

    file.seekg(pos);
    file.read(reinterpret_cast<char*>(&record), sizeof(Header));

    return !file.fail();
}

bool Write(const Submission& record, std::fstream& file, const std::streampos& pos)
{
    if (!file)
    {
        return false;
    }

    file.seekp(pos);
    file.write(reinterpret_cast<const char*>(&record), sizeof(Submission));
    file.flush();

    return !file.fail();
}

bool Write(const User& record, std::fstream& file, const std::streampos& pos)
{
    if (!file)
        return false;

    file.seekp(pos);
    file.write(reinterpret_cast<const char*>(&record), sizeof(User));
    file.flush();

    return !file.fail();
}

bool Write(const Header& record, std::fstream& file, const std::streampos& pos)
{
    if (!file)
        return false;

    file.seekp(pos);
    file.write(reinterpret_cast<const char*>(&record), sizeof(Header));
    file.flush();

    return !file.fail();
}

std::streampos PosByIndex(int32_t index, User& user)
{
    return static_cast<std::streamoff>(sizeof(Header) + sizeof(User) * index);
}

std::streampos PosByIndex(int32_t index, Submission& submission)
{
    return static_cast<std::streamoff>(sizeof(Header) + sizeof(Submission) * index);
}

std::streampos GetHeaderPos()
{
    return static_cast<std::streamoff>(0);
}

int32_t GetTableSize(std::fstream &file)
{
    Header header = Header();
    Read(header, file, GetHeaderPos());
    return header.TableSize;
}

int32_t GetTableCapacity(std::fstream &file)
{
    Header header = Header();
    Read(header, file, GetHeaderPos());
    return header.TableCapacity;
}

int32_t GetTableFirstElement(std::fstream &file)
{
    Header header = Header();
    Read(header, file, GetHeaderPos());
    return header.FirstElement;
}

Header GetHeader(std::fstream &file)
{
    Header header = Header();
    Read(header, file, GetHeaderPos());
    return header;
}

int32_t GetIndexByID(std::fstream &file, int32_t ID, User user)//пошук індекса елемента з певним айді
{                                           //повертає -1, якщо такого айді нема у файлі та індекс елементу, якщо він присутній у файлі
    int32_t CurrentIndex = GetHeader(file).FirstElement; //поточна позиція у файлі
    if(CurrentIndex < 0)
    {
        return -1;
    }
    for(Read(user, file, PosByIndex(CurrentIndex, user)); ; Read(user, file, PosByIndex(user.NextElement, user))) // проходимося по всіх записах та перевіряємо айдішки
    {
        if(user.UserID.value == ID) //знайшли айдішку
        {
            return CurrentIndex;
        }
        CurrentIndex = user.NextElement;
        if(CurrentIndex == -1)
        {
            break;
        }
    }

    return -1; // не знайшли айдішку (((
}

int32_t GetIndexByID(std::fstream &file, int32_t ID, Submission submission)//пошук індекса елемента з певним айді
{                                           //повертає -1, якщо такого айді нема у файлі та індекс елементу, якщо він присутній у файлі
    int32_t CurrentIndex = GetHeader(file).FirstElement; //поточна позиція у файлі
    if(CurrentIndex < 0)
    {
        return -1;
    }
    for(Read(submission, file, PosByIndex(CurrentIndex, submission)); ; Read(submission, file, PosByIndex(submission.NextElementInFile, submission))) // проходимося по всіх записах та перевіряємо айдішки
    {
        if(submission.SubmissionID.value == ID) //знайшли айдішку
        {
            return CurrentIndex;
        }
        CurrentIndex = submission.NextElementInFile;
        if(CurrentIndex == -1)
        {
            break;
        }
    }

    return -1; // не знайшли айдішку (((
}

Submission GetSubmissionByIndex(std::fstream &file, int32_t index)
{
    Submission submission = Submission();
    if(index >= 0)
    {
        Read(submission, file, PosByIndex(index, submission));
    }
    return submission;
}

User GetUserByIndex(std::fstream &file, int32_t index)
{
    User user = User();
    if(index >= 0)
    {
        Read(user, file, PosByIndex(index, user));
    }
    return user;
}



