#pragma once
#include "User.cpp"
class Submission
{
    public:
        Property<int32_t> SubmissionID = {"submissionid", 0};
        Property<int32_t> SubmittedBy = {"submittedby", 0}; //ID юзера, який відправив посилку
        Property<int32_t> ProblemID = {"problemid", 0};
        Property<char[25]> Verdict = {"verdict", ""};
        int32_t PreviousElementInFile = -1; //попередній елемент у файлі
        int32_t NextElementInFile = -1; //наступний елемент у файлі
        int32_t Previoussubmission = -1; //попередній елемент у списку користувача
        int32_t NextSubmission = -1; //наступний елемент у списку користувача
        int32_t PreviousEmpty = -1; //попередній порожній елемент у файлі (використовується, якщо поточний елемент є видаленим)
        Submission()
        {

        }
        Submission(int32_t submissionid, int32_t submittedby, int32_t problemid, string verdict)
        {
            this->SubmissionID.value = submissionid;
            this->SubmittedBy.value = submittedby;
            this->ProblemID.value = problemid;
            SetVerdict(verdict);
        }
        Submission(int32_t submissionid, int32_t submittedby, int32_t problemid, string verdict, int32_t previousElementInFile, int32_t nextElementInFile)
        {
            this->SubmissionID.value = submissionid;
            this->SubmittedBy.value = submittedby;
            this->ProblemID.value = problemid;
            SetVerdict(verdict);
            this->PreviousElementInFile = previousElementInFile;
            this->NextElementInFile = nextElementInFile;
        }
        bool SetVerdict(std::string s)
        {
            if(s.size()>25)
            {
                return false;
            }
            for(int32_t i = 0; i<s.size(); i++)
            {
                this->Verdict.value[i] = s[i];
            }
            return true;
        }
        std::string FindProperty(std::string s)
        {
            if(SubmissionID.type == s)
            {
                return IntToString(SubmissionID.value);
            }
            if(SubmittedBy.type == s)
            {
                return IntToString(SubmittedBy.value);
            }
            if(ProblemID.type == s)
            {
                return IntToString(ProblemID.value);
            }
            if(Verdict.type == s)
            {
                return Verdict.value;
            }
            throw ("there is no such property as "+s);
        }

        void Printout(string name)
        {
            std::cout<<name+".SubmisssionID: "<<this -> SubmissionID.value<<"\n";
            std::cout<<name+".SubmittedBy: "<<this -> SubmittedBy.value<<"\n";
            std::cout<<name+".ProblemID: "<<this -> ProblemID.value<<"\n";
            std::cout<<name+".PreviousElementInFile: "<<this -> PreviousElementInFile<<"\n";
            std::cout<<name+".NextElementInFile: "<<this -> NextElementInFile<<"\n";
            std::cout<<name+".Previoussubmission: "<<this -> Previoussubmission<<"\n";
            std::cout<<name+".NextSubmission: "<<this -> NextSubmission<<"\n";
            std::cout<<name+".PreviousEmpty: "<<this -> PreviousEmpty<<"\n";
            return;
        }
};