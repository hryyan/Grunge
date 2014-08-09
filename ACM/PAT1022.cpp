/*************************************************************************
	> File Name: PAT1022.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月05日 星期二 12时13分26秒
 ************************************************************************/

#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Book
{
    int id;
    string title;
    string author;
    vector<string> keyword;
    string publisher;
    int publishyear;
    Book(int _id, string _title, string _author, string _keyword, string _publisher, int _publishyear)\
    :id(_id), title(_title), author(_author), publisher(_publisher), publishyear(_publishyear){compile(_keyword);};
    void compile(string str);
};

void Book::compile(string str)
{
    vector<int> pos;
    pos.push_back(0);
    for (int n = 1; n < str.size(); n++)
    {
        if (str[n] == ' ')
            pos.push_back(n+1);
    }
    pos.push_back(str.size()+2);
    for (int i = 0; i < pos.size()-1; i++)
        keyword.push_back(str.substr(pos[i], pos[i+1]-pos[i]-1));
}

vector<Book> vec;

vector<int> search_year(int year)
{
    vector<int> v;
    for (int i = 0; i < vec.size(); i++)
        if (year == vec[i].publishyear)
            v.push_back(vec[i].id);
    return v;
}

vector<int> search_title(string str)
{
    vector<int> v;
    for (int i = 0; i < vec.size(); i++)
        if (str == vec[i].title)
            v.push_back(vec[i].id);
    return v;
}

vector<int> search_author(string str)
{
    vector<int> v;
    for (int i = 0; i < vec.size(); i++)
        if (str == vec[i].author)
            v.push_back(vec[i].id);
    return v;
}

vector<int> search_publisher(string str)
{
    vector<int> v;
    for (int i = 0; i < vec.size(); i++)
        if (str == vec[i].publisher)
            v.push_back(vec[i].id);
    return v;
}

vector<int> search_keyword(string str)
{
    vector<int> v;

    for (int j = 0; j < vec.size(); j++)
    {
        bool next = false;
        for (int k = 0; k < vec[j].keyword.size(); k++)
        {
            if (!next && str == vec[j].keyword[k])
            {
                v.push_back(vec[j].id);
                next = true;
            }  
        }
    }
    return v;
}


void print(vector<int> v)
{
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        printf("%07d\n", v[i]);
}

int main()
{
    //freopen("PAT1022.input", "r", stdin);

    int N;
    cin >> N;
    int id, publishyear;
    string title, author, keyword, publisher;
    while (N--)
    {
        scanf("%d\n", &id);
        getline(cin, title);
        getline(cin, author);
        getline(cin, keyword);
        getline(cin, publisher);
        scanf("%d\n", &publishyear);
        Book b = Book(id, title, author, keyword, publisher, publishyear);
        vec.push_back(b);
    }

    /*for (int i = 0; i < vec.size(); i++)
    {
        cout << "id: " << vec[i].id << endl;
        cout << "title: " << vec[i].title << endl;
        cout << "author: " << vec[i].author << endl;
        cout << "keyword: ";
        for (int j = 0; j < vec[i].keyword.size(); j++)
        {
            cout << vec[i].keyword[j] << " ";
        }
        cout << endl;
        cout << "publisher: " << vec[i].publisher << endl;
        cout << "publishyear: " << vec[i].publishyear << endl;
    }*/

    cin >> N;
    string str;
    while (N--)
    {
        int a = 0;
        scanf("%d: ", &a);
        getline(cin, str);
        printf("%d: ", a);
        cout << str << endl;
        if (str.size() == 4 &&
            str[0] >= '0' && str[0] <= '9' &&
            str[1] >= '0' && str[1] <= '9' &&
            str[2] >= '0' && str[2] <= '9' &&
            str[3] >= '0' && str[3] <= '9'
           )
        {
            int year = 0;
            for (int i = 0; i <= 3; i++)
                year += (str[i]-'0') * pow(10, 3-i);
            vector<int> res = search_year(year);
            print(res);
            if (res.empty())
                cout << "Not Found" << endl;
        }
        else
        {
            vector<int> res;
            if (res = search_title(str), res.size() != 0)
                print(res);
            else if (res = search_author(str), res.size() != 0)
                print(res);
            else if (res = search_keyword(str), res.size() != 0)
                print(res);
            else if (res = search_publisher(str), res.size() != 0)
                print(res);

            if (res.empty())
                cout << "Not Found" << endl;
        }
    }
}
