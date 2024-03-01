#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<iostream>
#include "TextProcessing.cpp"
#include <iomanip> 
#include "User.cpp"
#include "Submission.cpp"
#include "FileOperations.cpp"

bool GetM(std::vector<std::string> &input, std::fstream &file);
bool InsertM(std::vector<std::string> &input, std::fstream &file);
bool DelM(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile);
bool CalcM(std::vector<std::string> &input, std::fstream &file);
bool UpdateM(std::vector<std::string> &input, std::fstream &file);
bool UtM(std::vector<std::string> &input, std::fstream &file);
bool DelS(int32_t index, std::fstream &MasterFile, std::fstream &SlaveFile);
bool GetS(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile);
bool InsertS(std::vector<std::string> &input, std::fstream &Masterfile, std::fstream &Slavefile);
bool CalcS(std::vector<std::string> &input, std::fstream &file);
bool UpdateS(std::vector<std::string> &input, std::fstream &Masterfile, std::fstream &Slavefile);
bool UtS(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile);

void ProcessCommand(std::vector<std::string> &input, std::fstream& SlaveFile, std::fstream& MasterFile)
{
    if(input[0] == "get-m")
    {
        if(!GetM(input, MasterFile))
        {
            std::cout<<"Invalid argument. Operation unsuccessful.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "get-s")
    {
        if(!GetS(input, MasterFile, SlaveFile))
        {
            std::cout<<"Invalid argument. Operation unsuccessful.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "del-m")
    {
        if(!DelM(input, MasterFile, SlaveFile))
        {
            std::cout << "Operation unsuccessful.\n"<<std::endl;
        } else
        {
            std::cout << "User was successfully deleted from the database.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "del-s")
    {
        int32_t index = 0;
        if(input[1] == "id:")
        {
            if(!IsNumber(input[2]))
            {
                std::cout << "Argument should be an integer that represents the index of the table or user id."<<std::endl;
                return;
            }
            index = GetIndexByID(SlaveFile, StringToInt(input[2]), Submission());
            if(index == -1)
            {
                std::cout << "Submission with such ID doesn't exist.\n" << std::endl;
                return;
            }
        } else
        if(IsNumber(input[1]))
        {
            index = StringToInt(input[1]);
            index--;
            if(index >= GetTableCapacity(SlaveFile) || index < 0)
            {
                std::cout<< "Index is out of bounds" << std:: endl;
                return;
            }
        } else
        {
            std::cout << "Argument should be an integer that represents the index of the table or user id."<<std::endl;
            return;
        }
        if(DelS(index, MasterFile, SlaveFile))
        {
            std::cout << "Submission deleted successfully.\n" <<std::endl;
        } else
        {
            std::cout<< "Operation Unsuccessful.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "update-m")
    {
        if(input.size() == 1)
        {
            string s;
            std::cout<<"Enter ID of the user which information you wish to update: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            if(GetIndexByID(MasterFile, StringToInt(s), User()) == -1)
            {
                std::cout << "User with this ID doesn't exists." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter updated user login: ";
            cin>>s;
            input.push_back(s);

            std::cout<<"Enter updated user password hash: ";
            cin>>s;
            input.push_back(s);

            std::cout<<"Enter updated user rating: ";
            cin>>s;
            if(!IsNumber(s))
            {
                std::cout << "Rating should be an integer." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter the updated bool value of user being an admin: ";
            cin>>s;
            if(!IsBool(s))
            {
                std::cout << "Value entered wasn't of the bool type." << std::endl << std::endl;
                return;
            }
            input.push_back(s);
        }

        if(!UpdateM(input, MasterFile))
        {
            std::cout << "Operation Unsuccessful." << std::endl << std::endl;
        } else
        {
            std::cout << "User's information successfully updated." << std::endl << std::endl;
        }
        return;
    }

    if(input[0] == "update-s")
    {
        if(input.size() == 1)
        {
            string s;
            std::cout<<"Enter ID of the submission which information you wish to update: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "Submission ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            if(GetIndexByID(SlaveFile, StringToInt(s), Submission()) == -1)
            {
                std::cout << "Submission with this ID doesn't exists." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter updated submitter ID: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "User ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            if(GetIndexByID(MasterFile, StringToInt(s), User()) == -1)
            {
                std::cout << "User with this ID doesn't exists." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter updated problem ID: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "Problem ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter updated verdict: ";
            cin>>s;
            input.push_back(s);
        }

        if(!UpdateS(input, MasterFile, SlaveFile))
        {
            std::cout << "Operation Unsuccessful." << std::endl << std::endl;
        } else
        {
            std::cout << "User's information successfully updated." << std::endl << std::endl;
        }
        return;
    }

    if(input[0] == "insert-m")
    {
        if(input.size() == 1)
        {
            string s;
            std::cout<<"Enter user ID: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            if(GetIndexByID(MasterFile, StringToInt(s), User()) != -1)
            {
                std::cout << "User with this ID already exists." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter user login: ";
            cin>>s;
            input.push_back(s);

            std::cout<<"Enter user password hash: ";
            cin>>s;
            input.push_back(s);

            std::cout<<"Enter user rating: ";
            cin>>s;
            if(!IsNumber(s))
            {
                std::cout << "Rating should be an integer." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter the bool value of user being an admin: ";
            cin>>s;
            if(!IsBool(s))
            {
                std::cout << "Value entered wasn't of the bool type." << std::endl << std::endl;
                return;
            }
            input.push_back(s);
        }

        if(!InsertM(input, MasterFile))
        {
            std::cout << "Operation Unsuccessful." << std::endl << std::endl;
        } else
        {
            std::cout << "User successfully added to the database." << std::endl << std::endl;
        }
        return;
    }

    if(input[0] == "insert-s")
    {
        if(input.size() == 1)
        {
            string s;
            std::cout<<"Enter submission ID: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            if(GetIndexByID(SlaveFile, StringToInt(s), Submission()) != -1)
            {
                std::cout << "Submission with this ID already exists." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter user ID: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            if(GetIndexByID(MasterFile, StringToInt(s), User()) == -1)
            {
                std::cout << "There is no user with such ID" << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter the problem ID: ";
            cin>>s;
            if(!IsNumber(s) || s[0] == '-')
            {
                std::cout << "ID should be a positive integer." << std::endl << std::endl;
                return;
            }
            input.push_back(s);

            std::cout<<"Enter verdict: ";
            cin>>s;
            input.push_back(s);
        }

        if(!InsertS(input, MasterFile, SlaveFile))
        {
            std::cout << "Operation unsuccessful." << std::endl << std::endl;
        } else
        {
            std::cout << "Submission successfully added to the database." << std::endl << std::endl;
        }
        return;
    }

    if(input[0] == "calc-m")
    {
        if(input.size() > 1)
        {
            cout<<"Invalid arguments. Operation unsuccessful.\n"<<std::endl;
            return;
        }
        int32_t size = GetHeader(MasterFile).TableSize;
        if(size == 1)
        {
            std::cout<<"There is "<<size<<" element in the current table.\n"<<std::endl;
        } else
        {
            std::cout<<"There are "<<size<<" elements in the current table.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "calc-s")
    {
        if(input.size() > 3)
        {
            cout<<"Invalid arguments. Operation unsuccessful.\n"<<std::endl;
            return;
        }
        if(input.size()> 1 && input[1] == "userid:")
        {
            if(!IsNumber(input[2]) || input[2][0]=='-')
            {
                std::cout<<"Invalid arguments. Operation Unsuccessful.\n"<<std::endl;
                return;
            }
            int32_t UserIndex = GetIndexByID(MasterFile, StringToInt(input[2]), User());
            if(UserIndex == -1)
            {
                std::cout<<"There is no user with such ID.\n"<<std::endl;
                return;
            }
            User user;
            Read(user, MasterFile, PosByIndex(UserIndex, user));
            std::cout <<"User with ID "<<user.UserID.value <<" has "<<user.SubsetSize<<" submission";
            if(user.SubsetSize!=1)
            {
                std::cout<<"s";
            }
            std::cout<<".\n"<<std::endl;
            return;
        }
        int32_t size = GetHeader(SlaveFile).TableSize;
        if(size == 1)
        {
            std::cout<<"There is "<<size<<" element in the current table.\n"<<std::endl;
        } else
        {
            std::cout<<"There are "<<size<<" elements in the current table.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "ut-m")
    {
        if(!UtM(input, MasterFile))
        {
            std::cout<<"Something went wrong. Operation Unsuccessful.\n"<<std::endl;
        }
        return;
    }

    if(input[0] == "ut-s")
    {
        if(!UtS(input, MasterFile, SlaveFile))
        {
            std::cout<<"Something went wrong. Operation Unsuccessful.\n"<<std::endl;
        }
        return;
    }

    std::cout << "Unrecognized command. Please make sure you've entered all the characters correctly." << endl;
    return;
}
#pragma region Master commands
bool InsertM(std::vector<std::string> &input, std::fstream &file) //inserting rows to masterfile
{
    if(input.size() != 6 || !IsNumber(input[1]) || input[2].size() > 25 || input[3].size() > 25 || !IsNumber(input[4]) || !IsBool(input[5])) 
    { 
        return false;
    }

    if(GetIndexByID(file, StringToInt(input[1]), User()) != -1)
    {
        std::cout << "User with this ID already exists.\n" << std::endl;
        return false;
    }


    Header header = GetHeader(file);
    int32_t InsertIndex;
    if(header.TableCapacity == header.TableSize)
    {
        InsertIndex = header.TableCapacity;
        header.TableCapacity++;
        header.TableSize++;
    } else
    {
        InsertIndex = header.LastEmptyElement;
        User LastEmpty = User();
        Read(LastEmpty, file, PosByIndex(header.LastEmptyElement, LastEmpty));
        header.LastEmptyElement = LastEmpty.PreviousEmpty;
        header.TableSize++;
    }
    User user = User(StringToInt(input[1]), input[2], input[3], StringToInt(input[4]), StringToBool(input[5]));
    user.PreviousElement = header.LastElement;
    if(header.LastElement != -1)
    {
        User last = User();
        Read(last, file, PosByIndex(header.LastElement, last));
        last.NextElement = InsertIndex;
        Write(last, file, PosByIndex(header.LastElement, last));
        Write(user, file, PosByIndex(InsertIndex, user));
        header.LastElement = InsertIndex;
        Write(header, file, GetHeaderPos());
        return true;
    } else
    {
        header.FirstElement = InsertIndex;
        header.LastElement = InsertIndex;
        Write(header, file, GetHeaderPos());
        Write(user, file, PosByIndex(InsertIndex, user));
        return true;
    }
    return false;
}

bool GetM(std::vector<std::string> &input, std::fstream &file) //getting masterfile queries
{
    std::string errors;
    std::vector<std::string>ValidQueries;
    std::vector<int32_t>PrintSize;
    if(input.size()<2)
    {
        std::cout<<std::endl;
        return false;
    }
    if(input.size() > 2 + (input[1] == "id:"))
    {
        User user = User();
        for(int32_t j = 2 + (input[1] == "id:"); j < input.size(); j++)
        {
            string i = input[j];
            try
            {
                user.FindProperty(i);
                ValidQueries.push_back(i);
                PrintSize.push_back(i.size()+1);
            }
            catch(std::string error)
            {
                errors +=error+"\n";
            }
        }
    } else
    {
        ValidQueries = {"userid", "login", "passwordhash", "rating", "isadmin"};
        PrintSize = {7, 6, 13, 7, 8};
    }
    std::vector<User>users;
    if(input[1] == "all")
    {
        User user;
        if(GetHeader(file).FirstElement >= 0)
        {
            for(Read(user, file, PosByIndex(GetHeader(file).FirstElement, user));; Read(user, file, PosByIndex(user.NextElement, user)))
            {
                users.push_back(user);
                if(user.NextElement == -1)
                {
                    break;
                }
            }
        }
    } else
    if(input[1] == "id:")
    {
        int32_t index = GetIndexByID(file, StringToInt(input[2]), User());
        if(index == -1)
        {
            std::cout << "User with such ID doesn't exist.\n" << std::endl;
            return false;
        }
        User user = User();
        Read(user, file, PosByIndex(index, user));
        users.push_back(user);
    } 
    else
    if(IsNumber(input[1]))
    {
        std::string ans;
        User user = User();
        int32_t number = StringToInt(input[1]);
        number--;
        if(number >= GetTableCapacity(file) || number < 0)
        {
            std::cout<< "Index is out of bounds" << std:: endl;
            return false;
        }
        Read(user, file, PosByIndex(number, user));
        if(user.PreviousElement == -1 && user.NextElement == -1)
        {
            std::cout<< "This element has been deleted" << std:: endl;
            return false;
        }
        users.push_back(user);
    } else
    {
        std::cout << "Invalid argument." << std::endl;
        return false;
    }

    for(auto user: users)
    {
        for(int32_t i = 0; i<ValidQueries.size(); i++)
        {
            std::string s = user.FindProperty(ValidQueries[i]);
            PrintSize[i] = max(PrintSize[i], (int32_t)s.size()+1);
        }
    }

    std::cout<<std::endl;
    std::string DivStr = DividingStr(PrintSize);
    std::cout <<  DivStr << std::endl;
    std::cout<<"|";
    for(int32_t i = 0; i<ValidQueries.size(); i++)
    {
        std::cout<<setw(PrintSize[i])<<StringToUpper(ValidQueries[i]);
        std::cout<<"|";
    }
    std::cout<< "\n" + DivStr << std::endl;
    for(auto user: users)
    {
        std::cout<<"|";
        for(int32_t i = 0; i<ValidQueries.size(); i++)
        {
            std::string s = user.FindProperty(ValidQueries[i]);
            std::cout<<setw(PrintSize[i])<<s;
            std::cout<<"|";
        }
        std::cout<<"\n"+DivStr<<std::endl;
    }
    std::cout << std::endl;
    if(errors.size()>0)
    {
        std::cout << errors << std::endl;
    }
    return true;
}

bool UtM(std::vector<std::string> &input, std::fstream &file) //виводить всі поля, разом із службовими, має модифікатори "all", "id:", num
{
    std::vector<std::string>ValidQueries;
    std::vector<int32_t>PrintSize;
    if(input.size() > 3)
    {
        std::cout<<std::endl;
        return false;
    }
    ValidQueries = {"userid", "login", "passwordhash", "rating", "isadmin", "firstsubmission", "lastsubmission", "previousempty", "nextelement", "previouselement", "subsetsize"};
    for(auto i:ValidQueries)
    {
        PrintSize.push_back(i.size()+1);
    }
    std::vector<User>users;
    if(input.size() == 1)
    {
        User user;
        for(int32_t i = 0; i<GetHeader(file).TableCapacity; i++)
        {
            Read(user, file, PosByIndex(i, user));
            users.push_back(user);
        }
    } else
    if(input[1] == "all")
    {
        User user;
        for(Read(user, file, PosByIndex(GetHeader(file).FirstElement, user));; Read(user, file, PosByIndex(user.NextElement, user)))
        {
            users.push_back(user);
            if(user.NextElement == -1)
            {
                break;
            }
        }
    } else
    if(input[1] == "id:")
    {
        int32_t index = GetIndexByID(file, StringToInt(input[2]), User());
        if(index == -1)
        {
            std::cout << "User with such ID doesn't exist.\n" << std::endl;
            return false;
        }
        User user = User();
        Read(user, file, PosByIndex(index, user));
        users.push_back(user);
    } 
    else
    if(IsNumber(input[1]))
    {
        std::string ans;
        User user = User();
        int32_t number = StringToInt(input[1]);
        number--;
        if(number >= GetTableCapacity(file) || number < 0)
        {
            std::cout<< "Index is out of bounds" << std:: endl;
            return false;
        }
        Read(user, file, PosByIndex(number, user));
        users.push_back(user);
    } else
    {
        std::cout << "Invalid argument." << std::endl;
        return false;
    }

    for(auto user: users)
    {
        for(int32_t i = 0; i<5; i++)
        {
            std::string s = user.FindProperty(ValidQueries[i]);
            PrintSize[i] = max(PrintSize[i], (int32_t)s.size()+1);
        }
    }

    std::cout<<std::endl;
    std::string DivStr = DividingStr(PrintSize);
    std::cout <<  DivStr << std::endl;
    std::cout<<"|";
    for(int32_t i = 0; i<ValidQueries.size(); i++)
    {
        std::cout<<setw(PrintSize[i])<<StringToUpper(ValidQueries[i]);
        std::cout<<"|";
    }
    std::cout<< "\n" + DivStr << std::endl;
    for(auto user: users)
    {
        std::cout<<"|";
        for(int32_t i = 0; i<5; i++)
        {
            std::string s = user.FindProperty(ValidQueries[i]);
            std::cout<<setw(PrintSize[i])<<s;
            std::cout<<"|";
        }
        std::cout<<setw(PrintSize[5])<<user.FirstSubmission;
        std::cout<<"|";

        std::cout<<setw(PrintSize[6])<<user.LastSubmission;
        std::cout<<"|";

        std::cout<<setw(PrintSize[7])<<user.PreviousEmpty;
        std::cout<<"|";

        std::cout<<setw(PrintSize[8])<<user.NextElement;
        std::cout<<"|";

        std::cout<<setw(PrintSize[9])<<user.PreviousElement;
        std::cout<<"|";

        std::cout<<setw(PrintSize[10])<<user.SubsetSize;
        std::cout<<"|";

        std::cout<<"\n"+DivStr<<std::endl;
    }
    std::cout << std::endl;
    return true;
}

bool UpdateM(std::vector<std::string> &input, std::fstream &file) //updating user information
{
    if(input.size() < 6 || !IsNumber(input[1]) || input[2].size() > 25 || input[3].size() > 25 || !IsNumber(input[4]) || !IsBool(input[5])) 
    { 
        return false;
    }
    int32_t index = GetIndexByID(file, StringToInt(input[1]), User());
    if(index == -1)
    {
        std::cout << "There in no users with iD " << input[1] << " in the database.\n" << std::endl;
        return false;
    }
    User NewUser = User(StringToInt(input[1]), input[2], input[3], StringToInt(input[4]), StringToBool(input[5]));
    User user = User();
    Read(user, file, PosByIndex(index, user));
    user.NewValues(NewUser);
    return Write(user, file, PosByIndex(index, user));
}

bool DelM(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile)
{
    int32_t index = 0;
    if(input[1] == "id:")
    {
        if(!IsNumber(input[2]))
        {
            std::cout << "Argument should be an integer that represents the index of the table or user id."<<std::endl;
            return false;
        }
        index = GetIndexByID(MasterFile, StringToInt(input[2]), User());
        if(index == -1)
        {
            std::cout << "User with such ID doesn't exist.\n" << std::endl;
            return false;
        }
    } else
    if(IsNumber(input[1]))
    {
        index = StringToInt(input[1]);
        index--;
        if(index >= GetTableCapacity(MasterFile) || index < 0)
        {
            std::cout<< "Index is out of bounds" << std:: endl;
            return false;
        }
    } else
    {
        std::cout << "Argument should be an integer that represents the index of the table or user id."<<std::endl;
        return false;
    }
    User user = User();
    Read(user, MasterFile, PosByIndex(index, user));

    if(user.NextElement == -1 && user.PreviousElement == -1 && GetHeader(MasterFile).TableSize != 1)
    {
        std::cout<<"Row at this index is already deleted.\n"<<std::endl;
        return false;
    }
    User PreviousUser = User();
    User NextUser = User();
    Header header = GetHeader(MasterFile);
    if(user.PreviousElement != -1)
    {
        Read(PreviousUser, MasterFile, PosByIndex(user.PreviousElement, PreviousUser));
    }
    if(user.NextElement != -1)
    {
        Read(NextUser, MasterFile, PosByIndex(user.NextElement, NextUser));
    }
    PreviousUser.NextElement = user.NextElement;
    NextUser.PreviousElement = user.PreviousElement;
    header.TableSize--;

    user.PreviousEmpty = header.LastEmptyElement;
    header.LastEmptyElement = index;

    if(user.NextElement == -1)
    {
        header.LastElement = user.PreviousElement;
    }

    if(user.PreviousElement == -1)
    {
        header.FirstElement = user.NextElement;
    }

    while(user.FirstSubmission != -1)
    {
        Write(user, MasterFile, PosByIndex(index, user));
        if(!DelS(user.FirstSubmission, MasterFile, SlaveFile))
        {
            break;
        }
        Read(user, MasterFile, PosByIndex(index, user));
    }
    if(user.PreviousElement != -1)
    {
        Write(PreviousUser, MasterFile, PosByIndex(user.PreviousElement, PreviousUser));
    }
    if(user.NextElement != -1)
    {
        Write(NextUser, MasterFile, PosByIndex(user.NextElement, NextUser));
    }

    user.PreviousElement = -1;
    user.NextElement = -1;
    // user.FirstSubmission = -1;
    // user.LastSubmission = -1;
    Write(user, MasterFile, PosByIndex(index, user));
    Write(header, MasterFile, GetHeaderPos());

    return true;
}
#pragma endregion

#pragma region Slave commands
bool InsertS(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile) //inserting rows to slavefile
{
    if(!SlaveFile.is_open())
    {
        SlaveFile.open("Submissions.bin");
    }

    if(input.size() != 5 || !IsNumber(input[1]) || !IsNumber(input[2]) || !IsNumber(input[3]) || input[4].size() > 25) 
    { 
        return false;
    }

    if(GetIndexByID(SlaveFile, StringToInt(input[1]), Submission()) != -1)
    {
        std::cout << "Submission with this ID already exists.\n" << std::endl;
        return false;
    }
    
    int32_t UserIndex = GetIndexByID(MasterFile, StringToInt(input[2]), User());
    if(UserIndex == -1)
    {
        std::cout << "User with this ID doesn't exist.\n" << std::endl;
        return false;
    }
    User user = User();
    Read(user, MasterFile, PosByIndex(UserIndex, user));
    Header header = GetHeader(SlaveFile);
    // std::cout<<"BEFORE:\n";
    // header.Print("header");

    int32_t InsertIndex = 0;
    if(header.TableCapacity == header.TableSize)
    {
        InsertIndex = header.TableCapacity;
        header.TableCapacity++;
        header.TableSize++;
        //std::cout<<"InsertIndex = "<<InsertIndex<<std::endl;
    } else
    {
        InsertIndex = header.LastEmptyElement;
        Submission LastEmpty = Submission();
        Read(LastEmpty, SlaveFile, PosByIndex(header.LastEmptyElement, LastEmpty));
        header.LastEmptyElement = LastEmpty.PreviousEmpty;
        header.TableSize++;
    }

    Submission submission = Submission(StringToInt(input[1]), StringToInt(input[2]), StringToInt(input[3]), input[4]);
    submission.PreviousElementInFile = header.LastElement;
    submission.Previoussubmission = user.LastSubmission;

    if(header.LastElement != -1)
    {
        Submission last = Submission();
        Read(last, SlaveFile, PosByIndex(header.LastElement, last));
        last.NextElementInFile = InsertIndex;
        Write(last, SlaveFile, PosByIndex(header.LastElement, last));
    } else
    {
        header.FirstElement = InsertIndex;
    }

    if(user.LastSubmission != -1)
    {
        Submission lastSub = Submission();
        Read(lastSub, SlaveFile, PosByIndex(user.LastSubmission, lastSub));
        lastSub.NextSubmission = InsertIndex;
        Write(lastSub, SlaveFile, PosByIndex(user.LastSubmission, lastSub));
    } else
    {
        user.FirstSubmission = InsertIndex;
    }
    user.LastSubmission = InsertIndex;
    user.SubsetSize++;
    header.LastElement = InsertIndex;


    Write(submission, SlaveFile, PosByIndex(InsertIndex, submission));
    // std::cout<<"AFTER:\n";
    // header.Print("header");

    Write(user, MasterFile, PosByIndex(UserIndex, user));
    Write(header, SlaveFile, GetHeaderPos());
    return true;
}

bool GetS(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile) //getting masterfile queries
{
    std::string errors;
    std::vector<std::string>ValidQueries;
    std::vector<int32_t>PrintSize;
    if(input.size()<2)
    {
        std::cout<<std::endl;
        return false;
    }
    if(input.size() > 2 + (input[1] == "userid:" || input[1] == "submissionid:"))
    {
        Submission submission = Submission();
        for(int32_t j = 2 + (input[1] == "userid:" || input[1] == "submissionid:"); j < input.size(); j++)
        {
            string i = input[j];
            try
            {
                submission.FindProperty(i);
                ValidQueries.push_back(i);
                PrintSize.push_back(i.size()+1);
            }
            catch(std::string error)
            {
                errors +=error+"\n";
            }
        }
    } else
    {
        ValidQueries = {"submissionid", "submittedby", "problemid", "verdict"};
        PrintSize = {13, 12, 10, 8};
    }
    std::vector<Submission>submissions;
    if(input[1] == "all")
    {
        Submission submission;
        if(GetHeader(SlaveFile).FirstElement >= 0)
        {
            for(Read(submission, SlaveFile, PosByIndex(GetHeader(SlaveFile).FirstElement, submission));; Read(submission, SlaveFile, PosByIndex(submission.NextElementInFile, submission)))
            {
                submissions.push_back(submission);
                if(submission.NextElementInFile == -1)
                {
                    break;
                }
            }
        }
    } else
    if(input[1] == "userid:")
    {
        int32_t index = GetIndexByID(MasterFile, StringToInt(input[2]), User());
        if(index == -1)
        {
            std::cout << "User with such ID doesn't exist.\n" << std::endl;
            return false;
        }
        User user = User();
        Read(user, MasterFile, PosByIndex(index, user));
        if(user.FirstSubmission == -1)
        {
            std:: cout << "This user didn't submit anything.";
            return false;
        }
        Submission submission = Submission();
        for(Read(submission, SlaveFile, PosByIndex(user.FirstSubmission, submission));; Read(submission, SlaveFile, PosByIndex(submission.NextSubmission, submission)))
        {
            submissions.push_back(submission);
            if(submission.NextSubmission == -1)
            {
                break;
            }
        }
    } 
    else
    if(input[1] == "submissionid:")
    {
        int32_t index = GetIndexByID(SlaveFile, StringToInt(input[2]), Submission());
        if(index == -1)
        {
            std::cout << "Submission with such ID doesn't exist.\n" << std::endl;
            return false;
        }
        Submission submission = Submission();
        Read(submission, SlaveFile, PosByIndex(index, submission));
        submissions.push_back(submission);
    } else
    if(IsNumber(input[1]))
    {
        std::string ans;
        Submission submission = Submission();
        int32_t number = StringToInt(input[1]);
        number--;
        if(number >= GetTableCapacity(SlaveFile) || number < 0)
        {
            std::cout<< "Index is out of bounds" << std:: endl;
            return false;
        }
        Read(submission, SlaveFile, PosByIndex(number, submission));
        if(submission.PreviousElementInFile == -1 && submission.NextElementInFile == -1)
        {
            std::cout<< "This element has been deleted" << std:: endl;
            return false;
        }
        submissions.push_back(submission);
    } else
    {
        std::cout << "Invalid argument." << std::endl;
        return false;
    }

    for(auto submission: submissions)
    {
        for(int32_t i = 0; i<ValidQueries.size(); i++)
        {
            std::string s = submission.FindProperty(ValidQueries[i]);
            PrintSize[i] = max(PrintSize[i], (int32_t)s.size()+1);
        }
    }

    std::cout<<std::endl;
    std::string DivStr = DividingStr(PrintSize);
    std::cout <<  DivStr << std::endl;
    std::cout<<"|";
    for(int32_t i = 0; i<ValidQueries.size(); i++)
    {
        std::cout<<setw(PrintSize[i])<<StringToUpper(ValidQueries[i]);
        std::cout<<"|";
    }
    std::cout<< "\n" + DivStr << std::endl;
    for(auto submission: submissions)
    {
        std::cout<<"|";
        for(int32_t i = 0; i<ValidQueries.size(); i++)
        {
            std::string s = submission.FindProperty(ValidQueries[i]);
            std::cout<<setw(PrintSize[i])<<s;
            std::cout<<"|";
        }
        std::cout<<"\n"+DivStr<<std::endl;
    }
    std::cout << std::endl;
    if(errors.size()>0)
    {
        std::cout << errors << std::endl;
    }
    return true;
}

bool UtS(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile) //виводить всі поля, разом із службовими, має модифікатори "all", "id:", num
{
    std::string errors;
    std::vector<std::string>ValidQueries;
    std::vector<int32_t>PrintSize;
    if(input.size() < 2 && input.size() != 1)
    {
        std::cout<<std::endl;
        return false;
    }
    if(input.size() > 2 + (input[1] == "userid:" || input[1] == "submissionid:"))
    {
        Submission submission = Submission();
        for(int32_t j = 2 + (input[1] == "userid:" || input[1] == "submissionid:"); j < input.size(); j++)
        {
            string i = input[j];
            try
            {
                submission.FindProperty(i);
                ValidQueries.push_back(i);
                PrintSize.push_back(i.size()+1);
            }
            catch(std::string error)
            {
                errors +=error+"\n";
            }
        }
    } else
    {
        ValidQueries = {"submissionid", "submittedby", "problemid", "verdict", "previouselementinfile", "nextelementinfile", "previoussubmission", "nextsubmission", "previousempty"};
        PrintSize = {13, 12, 10, 8, 22, 18, 19, 15, 14};
    }
    std::vector<Submission>submissions;
    if(input.size() == 1)
    {
        if(GetHeader(SlaveFile).FirstElement >= 0)
        {
            for(int32_t i = 0; i<GetHeader(SlaveFile).TableCapacity; i++)
            {
                submissions.push_back(GetSubmissionByIndex(SlaveFile, i));
            }
        }
    } else
    if(input[1] == "all")
    {
        Submission submission;
        if(GetHeader(SlaveFile).FirstElement >= 0)
        {
            for(Read(submission, SlaveFile, PosByIndex(GetHeader(SlaveFile).FirstElement, submission));; Read(submission, SlaveFile, PosByIndex(submission.NextElementInFile, submission)))
            {
                submissions.push_back(submission);
                if(submission.NextElementInFile == -1)
                {
                    break;
                }
            }
        }
    } else
    if(input[1] == "userid:")
    {
        int32_t index = GetIndexByID(MasterFile, StringToInt(input[2]), User());
        if(index == -1)
        {
            std::cout << "User with such ID doesn't exist.\n" << std::endl;
            return false;
        }
        User user = User();
        Read(user, MasterFile, PosByIndex(index, user));
        if(user.FirstSubmission == -1)
        {
            std:: cout << "This user didn't submit anything.";
            return false;
        }
        Submission submission = Submission();
        for(Read(submission, SlaveFile, PosByIndex(user.FirstSubmission, submission));; Read(submission, SlaveFile, PosByIndex(submission.NextSubmission, submission)))
        {
            submissions.push_back(submission);
            if(submission.NextSubmission == -1)
            {
                break;
            }
        }
    } 
    else
    if(input[1] == "submissionid:")
    {
        int32_t index = GetIndexByID(SlaveFile, StringToInt(input[2]), Submission());
        if(index == -1)
        {
            std::cout << "Submission with such ID doesn't exist.\n" << std::endl;
            return false;
        }
        Submission submission = Submission();
        Read(submission, SlaveFile, PosByIndex(index, submission));
        submissions.push_back(submission);
    } else
    if(IsNumber(input[1]))
    {
        std::string ans;
        Submission submission = Submission();
        int32_t number = StringToInt(input[1]);
        number--;
        if(number >= GetTableCapacity(SlaveFile) || number < 0)
        {
            std::cout<< "Index is out of bounds" << std:: endl;
            return false;
        }
        Read(submission, SlaveFile, PosByIndex(number, submission));
        submissions.push_back(submission);
    } else
    {
        std::cout << "Invalid argument." << std::endl;
        return false;
    }

    for(auto submission: submissions)
    {
        for(int32_t i = 0; i<4; i++)
        {
            std::string s = submission.FindProperty(ValidQueries[i]);
            PrintSize[i] = max(PrintSize[i], (int32_t)s.size()+1);
        }
    }

    std::cout<<std::endl;
    std::string DivStr = DividingStr(PrintSize);
    std::cout <<  DivStr << std::endl;
    std::cout<<"|";
    for(int32_t i = 0; i<ValidQueries.size(); i++)
    {
        std::cout<<setw(PrintSize[i])<<StringToUpper(ValidQueries[i]);
        std::cout<<"|";
    }
    std::cout<< "\n" + DivStr << std::endl;
    for(auto submission: submissions)
    {
        std::cout<<"|";
        for(int32_t i = 0; i<4; i++)
        {
            std::string s = submission.FindProperty(ValidQueries[i]);
            std::cout<<setw(PrintSize[i])<<s;
            std::cout<<"|";
        }
        std::cout<<setw(PrintSize[4])<<submission.PreviousElementInFile;
        std::cout<<"|";

        std::cout<<setw(PrintSize[5])<<submission.NextElementInFile;
        std::cout<<"|";

        std::cout<<setw(PrintSize[6])<<submission.Previoussubmission;
        std::cout<<"|";

        std::cout<<setw(PrintSize[7])<<submission.NextSubmission;
        std::cout<<"|";

        std::cout<<setw(PrintSize[8])<<submission.PreviousEmpty;
        std::cout<<"|";

        std::cout<<"\n"+DivStr<<std::endl;
    }
    std::cout << std::endl;
    return true;
}

bool UpdateS(std::vector<std::string> &input, std::fstream &MasterFile, std::fstream &SlaveFile) //updating user information
{
    if(input.size() != 5 || !IsNumber(input[1]) || !IsNumber(input[2]) || !IsNumber(input[3]) || input[4].size() > 25) 
    { 
        return false;
    }
    int32_t index = GetIndexByID(SlaveFile, StringToInt(input[1]), Submission());
    if(index == -1)
    {
        std::cout << "Submission with this ID doesn't exist.\n" << std::endl;
        return false;
    }
    
    int32_t UserIndex = GetIndexByID(MasterFile, StringToInt(input[2]), User());
    if(UserIndex == -1)
    {
        std::cout << "User with this ID doesn't exist.\n" << std::endl;
        return false;
    }
    if(DelS(index, MasterFile, SlaveFile) && InsertS(input, MasterFile, SlaveFile))
    {
        return true;
    }
    return false;
}

bool DelS(int32_t DeleteIndex, std::fstream &MasterFile, std::fstream &SlaveFile)
{
    if(DeleteIndex >= GetTableCapacity(SlaveFile) || DeleteIndex < 0)
    {
        std::cout<< "Index is out of bounds" << std:: endl;
        return false;
    }
    Submission submission = Submission();
    Read(submission, SlaveFile, PosByIndex(DeleteIndex, submission));

    if(submission.NextElementInFile == -1 && submission.PreviousElementInFile == -1 && GetHeader(SlaveFile).TableSize != 1)
    {
        std::cout<<"Row at this index is already deleted.\n"<<std::endl;
        return false;
    }
    Submission PreviousSubmission = GetSubmissionByIndex(SlaveFile, submission.PreviousElementInFile);
    Submission NextSubmission = GetSubmissionByIndex(SlaveFile, submission.NextElementInFile);

    int32_t UserIndex = GetIndexByID(MasterFile, submission.SubmittedBy.value, User());

    User user = GetUserByIndex(MasterFile, UserIndex);

    Header header = GetHeader(SlaveFile);
    Submission PrevUserSub = GetSubmissionByIndex(SlaveFile, submission.Previoussubmission);
    Submission NextUserSub = GetSubmissionByIndex(SlaveFile, submission.NextSubmission);

    PreviousSubmission.NextElementInFile = submission.NextElementInFile;
    NextSubmission.PreviousElementInFile = submission.PreviousElementInFile;
    header.TableSize--;

    if(submission.PreviousElementInFile == submission.Previoussubmission)
    {
        PrevUserSub = PreviousSubmission;
    }
    if(submission.NextElementInFile == submission.NextSubmission)
    {
        NextUserSub = NextSubmission;
    }

    PrevUserSub.NextSubmission = submission.NextSubmission;
    NextUserSub.Previoussubmission = submission.Previoussubmission;
    user.SubsetSize--;

    submission.PreviousEmpty = header.LastEmptyElement;
    header.LastEmptyElement = DeleteIndex;



    if(submission.NextElementInFile == -1)
    {
        header.LastElement = submission.PreviousElementInFile;
    }

    if(submission.PreviousElementInFile == -1)
    {
        header.FirstElement = submission.NextElementInFile;
    }

    if(submission.PreviousElementInFile != -1)
    {
        Write(PreviousSubmission, SlaveFile, PosByIndex(submission.PreviousElementInFile, PreviousSubmission));
    }
    if(submission.NextElementInFile != -1)
    {
        Write(NextSubmission, SlaveFile, PosByIndex(submission.NextElementInFile, NextSubmission));
    }

    if(submission.NextSubmission == -1)
    {
        user.LastSubmission = submission.Previoussubmission;
    }

    if(submission.Previoussubmission == -1)
    {
        user.FirstSubmission = submission.NextSubmission;
    }

    if(submission.Previoussubmission != -1)
    {
        Write(PrevUserSub, SlaveFile, PosByIndex(submission.Previoussubmission, PrevUserSub));
    }
    if(submission.NextSubmission != -1)
    {
        Write(NextUserSub, SlaveFile, PosByIndex(submission.NextSubmission, NextUserSub));
    }

    submission.PreviousElementInFile = -1;
    submission.NextElementInFile = -1;
    submission.Previoussubmission = -1;
    submission.NextSubmission = -1;

    Write(submission, SlaveFile, PosByIndex(DeleteIndex, submission));
    Write(header, SlaveFile, GetHeaderPos());
    Write(user, MasterFile, PosByIndex(UserIndex, user));

    return true;
}


#pragma endregion