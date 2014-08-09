/*************************************************************************
	> File Name: PAT1025.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月05日 星期二 15时50分02秒
 ************************************************************************/

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Record
{
    string id;
    int group;
    int score;
    int final_rank;
    int group_rank;
    Record(string _id, int _group, int _score):id(_id), group(_group), score(_score){};
};

bool comp(Record r1, Record r2)
{
    if (r1.score > r2.score)
        return true;
    else if (r1.score == r2.score)
        if (r1.id < r2.id)
            return true;
    return false;
}

bool compInGroup(Record r1, Record r2)
{
    if (r1.group < r2.group)
        return true;
    else if (r1.group == r2.group)
        if (r1.score > r2.score)
            return true;
    return false;
}

vector<Record> vec;

int main()
{
    //freopen("PAT1025.input", "r", stdin);

    int groups, score, record_num, total = 0;
    string id;
    cin >> groups;
    for (int i = 0; i < groups; i++)
    {
        cin >> record_num;
        total += record_num;
        while (record_num--)
        {
            cin >> id >> score;
            Record r = Record(id, i+1, score);
            vec.push_back(r);
        }
    }

    sort(vec.begin(), vec.end(), comp);

    int pre = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].score != pre)
        {
            vec[i].final_rank = i+1;
            pre = vec[i].score;
        }
        else
        {
            vec[i].final_rank = vec[i-1].final_rank;
        }
    }

    sort(vec.begin(), vec.end(), compInGroup);

    pre = -1;
    int pregroup = -1, group_start_position = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].group != pregroup)
        {
            vec[i].group_rank = 1;
            group_start_position = i;
            pre = vec[i].score;
            pregroup = vec[i].group;
        }
        else
        {
            if (vec[i].score != pre)
            {
                vec[i].group_rank = i-group_start_position+1;
                pre = vec[i].score;
            }
            else
            {
                vec[i].group_rank = vec[i-1].group_rank;
            }
        }
    }

    sort(vec.begin(), vec.end(), comp);

    cout << total << endl;
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i].id << " " << vec[i].final_rank << " " << vec[i].group << " " << vec[i].group_rank << endl;
}

