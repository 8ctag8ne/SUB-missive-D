#pragma once
#include <string>
#include<fstream>
#include <iostream>
template <class T>
struct Property
{
    char type[15];
    T value;
};
class Header
{
    public:
        int32_t LastEmptyElement = -1;
        int32_t TableCapacity = 0;
        int32_t TableSize = 0;
        int32_t LastElement = -1;
        int32_t FirstElement = -1;
        Header(int32_t capacity, int32_t size, int32_t lastempty, int32_t firstelement, int32_t lastelement)
        {
            this -> LastEmptyElement = lastempty;
            this -> TableCapacity = capacity;
            this -> TableSize = size;
            this -> FirstElement = firstelement;
            this -> LastElement = lastelement;
        }
        Header(){}
        void Print(std::string name)
        {
            std::cout << name+".FirstElement: "<<this -> FirstElement<<"\n";
            std::cout << name+".LastElement: "<<this -> LastElement<<"\n";
            std::cout << name+".LastEmptyElement: "<<this->LastEmptyElement<<"\n";
            std::cout << name+".TableCapacity: "<<this->TableCapacity<<"\n";
            std::cout << name+".TableSize: "<<this->TableSize<<"\n"<<std::endl;
        }
};