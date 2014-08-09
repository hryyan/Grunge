/*************************************************************************
	> File Name: PAT1036.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月09日 星期六 15时19分51秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct Student
{
    string id;
    string name;
    int grade;
    Student(string _id, string _name, int _grade):id(_id), name(_name), grade(_grade){};
};

bool comp(Student s1, Student s2)
{
    return s1.grade > s2.grade;
}

int main()
{
    //freopen("PAT1036.input", "r", stdin);

    int N;
    cin >> N;
    vector<Student> male;
    vector<Student> female;

    string name, gender, id;
    int grade;
    for (int i = 0; i < N; i++)
    {
        cin >> name >> gender >> id >> grade;
        if (gender[0] == 'M')
            male.push_back(Student(id, name, grade));
        else
            female.push_back(Student(id, name, grade));
    }

    sort(male.begin(), male.end(), comp);
    sort(female.begin(), female.end(), comp);

    bool on = false;
    if (female.empty())
        on = true, cout << "Absent" << endl;
    else
        cout << female[0].name << " " << female[0].id << endl;

    if (male.empty())
        on = true, cout << "Absent" << endl;
    else
        cout << male[male.size()-1].name << " " << male[male.size()-1].id << endl;

    if (on)
        cout << "NA";
    else
        cout << female[0].grade - male[male.size()-1].grade << endl;
}
