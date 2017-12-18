#include "student.h"

void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

bool AscentByNo(Student &x, Student &y)
{
    return x.info[0] < y.info[0];
}

bool DescentByNo(Student &x, Student &y)
{
    return x.info[0] > y.info[0];
}

bool AscentByName(Student &x, Student &y)
{
    return x.info[1] < y.info[1];
}

bool DescentByName(Student &x, Student &y)
{
    return x.info[1] > y.info[1];
}

Students::Students()
{
    m_filename = "";
    Student_List.clear();
}

void Students::ReadRecords(QString filename)
{
    Student_List.clear();

    if(filename=="")
    {
        m_filename = "";
        return;
    }

    m_filename = filename.toStdString();
    ifstream in_file(m_filename);
    string line;

    while(getline(in_file, line))
    {
        vector<string> temp;
        SplitString(line, temp, " ");
        QString info[info_len];
        for(int i=0; i<info_len; i++)
        {
            info[i] = QString::fromStdString(temp[i]);
        }

        Student s(info);
        Student_List.push_back(s);
    }

    in_file.close();
}

void Students::AddRecord(Student &s)
{
    Student_List.push_back(s);
}

void Students::WriteRecords()
{
    if(m_filename=="")
        return;

    ofstream ofile;
    ofile.open(m_filename);

    for(int i=0; i<Student_List.size();i++)
    {
        for(int j=0; j<info_len; j++)
        {
            ofile << Student_List[i].info[j].toStdString();
            if(j!=info_len-1)
                ofile<<" ";
        }
        ofile << endl;
    }
    ofile.close();
}

void Students::DeleteRecord(int no)
{
    Student_List.removeAt(no);
}

void Students::ModifyRecord(int no, Student &s)
{
    Student_List[no] = s;
}

void Students::ClearRecords()
{
    m_filename="";
    Student_List.clear();
}

void Students::SortRecords(int way, bool order)
{
    switch(way)
    {
    case 0:
        if(order)
            qSort(Student_List.begin(), Student_List.end(), AscentByNo);
        else
            qSort(Student_List.begin(), Student_List.end(), DescentByNo);
        break;

    case 1:
        if(order)
            qSort(Student_List.begin(), Student_List.end(), AscentByName);
        else
            qSort(Student_List.begin(), Student_List.end(), DescentByName);
        break;

    default:
        break;
    }
}

QList<Student> Students::GetList()
{
    return Student_List;
}

int Students::GetSize()
{
    return Student_List.size();
}

QString Students::GetFile()
{
    return QString::fromStdString(m_filename);
}

void Students::SetFile(QString filename)
{
    m_filename = filename.toStdString();
}
