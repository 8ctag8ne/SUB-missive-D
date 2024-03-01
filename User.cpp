#pragma once
#include "NeccessaryThings.cpp"
#include "TextProcessing.cpp"
class User
{
    public: 

        Property<int32_t> UserID = {"userid", 0};
        Property<char[25]> Login = {"login", ""};
        Property<char[25]>PasswordHash = {"passwordhash", ""};
        Property<int32_t>Rating = {"rating", 0};
        Property<bool>IsAdmin = {"isadmin", 0};
        int32_t FirstSubmission = -1; //індекс першої відправки у slave - файлі
        int32_t LastSubmission = -1; //індекс останньої відправки у slave - файлі
        int32_t PreviousEmpty = -1;
        int32_t NextElement = -1;
        int32_t PreviousElement = -1;
        int32_t SubsetSize = 0; //кількість відправок поточного користувача
        User(){}

        User(int32_t userid, std::string login, std::string passwordhash, int32_t rating, bool isadmin)
        {
            this->UserID.value = userid;
            SetLogin(login);
            SetPassword(passwordhash);
            this->Rating.value = rating;
            this->IsAdmin.value = isadmin;   
        }
        User(int32_t userid, std::string login, std::string passwordhash, int32_t rating, bool isadmin, int32_t nextelement)
        {
            this->UserID.value = userid;
            SetLogin(login);
            SetPassword(passwordhash);
            this->Rating.value = rating;
            this->IsAdmin.value = isadmin; 
            this -> NextElement = nextelement;
        }
        bool SetLogin(std::string s)
        {
            if(s.size()>25)
            {
                return false;
            }
            for(int32_t i = 0; i<s.size(); i++)
            {
                this->Login.value[i] = s[i];
            }
            return true;
        }

        bool SetPassword(std::string s)
        {
            if(s.size()>25)
            {
                return false;
            }
            for(int32_t i = 0; i<s.size(); i++)
            {
                this->PasswordHash.value[i] = s[i];
            }
            return true;
        }

        std::string FindProperty(std::string s)
        {
            if(UserID.type == s)
            {
                return IntToString(UserID.value);
            }
            if(Login.type == s)
            {
                return Login.value;
            }
            if(PasswordHash.type == s)
            {
                return PasswordHash.value;
            }
            if(Rating.type == s)
            {
                return IntToString(Rating.value);
            }
            if(IsAdmin.type == s)
            {
                return BoolToString(IsAdmin.value);
            }
            throw ("there is no such property as "+s);
        }
        void NewValues (User NewUser)
        {
            this->UserID = NewUser.UserID;
            this->IsAdmin = NewUser.IsAdmin;
            this->Login= NewUser.Login;
            this->PasswordHash = NewUser.PasswordHash;
            this->Rating = NewUser.Rating;
        }
        void Printout(string name)
        {
            std::cout<<name+".UserID: "<<this -> UserID.value <<"\n";
            std::cout<<name+".Login: "<<this -> Login.value <<"\n";
            std::cout<<name+".PasswordHash: "<<this -> PasswordHash.value <<"\n";
            std::cout<<name+".Rating: "<<this -> Rating.value <<"\n";
            std::cout<<name+".IsAdmin: "<<this -> IsAdmin.value <<"\n";
            std::cout<<name+".NextElement: "<<this -> NextElement <<"\n";
            std::cout<<name+".PreviousElement: "<<this -> PreviousElement <<"\n";
            std::cout<<name+".FirstSubmission: "<<this -> FirstSubmission <<"\n";
            std::cout<<name+".LastSubmission: "<<this -> LastSubmission <<"\n";
            std::cout<<name+".SubsetSize: "<<this -> SubsetSize <<"\n";
        }
};