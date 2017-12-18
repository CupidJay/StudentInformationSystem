#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <fstream>
#include <QString>
#include <QList>
#include <QDebug>
using namespace std;

#define info_len 6

class Student
{
public:
    QString info[info_len];  //s_no, s_name, s_sex, s_date, s_city, s_majo

    Student()
    {
        for(int i=0; i<info_len; i++)
            info[i] = "";
    }

    Student(QString *temp)
    {
        for(int i=0; i<info_len; i++)
            info[i] = temp[i];
    }
};


void SplitString(const string& s, vector<string>& v, const string& c);
bool AscentByName(Student &x, Student &y);
bool DescentByName(Student &x, Student &y);
bool AscentByNo(Student &x, Student &y);
bool DescentByNo(Student &x, Student &y);



class Students
{
private:
    QList<Student> Student_List;
    string m_filename;

public:
    Students();
    void ReadRecords(QString filename);
    void AddRecord(Student &s);
    void DeleteRecord(int no);
    void ModifyRecord(int no, Student &s);
    void WriteRecords();
    void ClearRecords();
    void SortRecords(int way, bool order); //order=false for ascent, order=true for descent
    QList<Student> GetList();
    int GetSize();
    QString GetFile();
    void SetFile(QString filename);
};


#endif // STUDENT_H
