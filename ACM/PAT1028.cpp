/*************************************************************************
	> File Name: PAT1028.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月07日 星期四 09时52分18秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Student
{
    int id;
    char name[9];
    int grade;
    Student(int _id, char* _name, int _grade):id(_id), grade(_grade)
    {
        memcpy(name, _name, 8*sizeof(char));
    };
    Student(){};
};

int N, C;
//vector<Student> vec;
Student v[100100];
int v_index;

bool comp1(Student s1, Student s2)
{
    return s1.id < s2.id;
}

bool comp2(Student s1, Student s2)
{
    int i = strcmp(s1.name, s2.name);
    if (i < 0)
        return true;
    else if (i == 0 && s1.id < s2.id)
        return true;
    return false;
}

bool comp3(Student s1, Student s2)
{
    if (s1.grade < s2.grade)
        return true;
    else if (s1.grade == s2.grade && s1.id < s2.id)
        return true;
    return false;
}

int main()
{
    //freopen("PAT1028.input", "r", stdin);

    int id, grade;
    char name[9];
    memset(name, 0, sizeof(char)*8);
    cin >> N >> C;
    while (N--)
    {
        //cin >> id >> name >> grade;
        //Student s = Student(id, name, grade);
        //vec.push_back(s);
        memset(name, 0, sizeof(char)*8);
        scanf("%d %s %d", &id, name, &grade);
        v[v_index++] = Student(id, name, grade);
    }

    if (C == 1)
    {
        //sort(vec.begin(), vec.end(), comp1);
        //for (int i = 0; i < vec.size(); i++)
        //    printf("%06d %s %d\n", vec[i].id, vec[i].name.c_str(), vec[i].grade);
        sort(v, v+v_index, comp1);
        for (int i = 0; i < v_index; i++)
            printf("%06d %s %d\n", v[i].id, v[i].name, v[i].grade);
    }

    if (C == 2)
    {
        //sort(vec.begin(), vec.end(), comp2);
        //for (int i = 0; i < vec.size(); i++)
        //    printf("%06d %s %d\n", vec[i].id, vec[i].name.c_str(), vec[i].grade);
        sort(v, v+v_index, comp2);
        for (int i = 0; i < v_index; i++)
            printf("%06d %s %d\n", v[i].id, v[i].name, v[i].grade);
    }

    if (C == 3)
    {
        //sort(vec.begin(), vec.end(), comp3);
        //for (int i = 0; i < vec.size(); i++)
        //    printf("%06d %s %d\n", vec[i].id, vec[i].name.c_str(), vec[i].grade);
        sort(v, v+v_index, comp3);
        for (int i = 0; i < v_index; i++)
            printf("%06d %s %d\n", v[i].id, v[i].name, v[i].grade);
    }
}
