/*************************************************************************
	> File Name: PAT1035.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月09日 星期六 14时58分26秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    //freopen("PAT1035.input", "r", stdin);

    int N, count = 0;
    string a, b;
    bool modify = false;
    vector<string> a_vec, b_vec;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b;
        modify = false;
        for (int j = 0; j < b.size(); j++)
        {
            if (b[j] == '1')
            {
                b[j] = '@';
                modify = true;
            }
            else if (b[j] == '0')
            {
                b[j] = '%';
                modify = true;
            }
            else if (b[j] == 'l')
            {
                b[j] = 'L';
                modify = true;
            }
            else if (b[j] == 'O')
            {
                b[j] = 'o';
                modify = true;
            }
        }
        if (modify)
        {
            a_vec.push_back(a);
            b_vec.push_back(b);
            count++;
        }
    }
    
    if (count == 0)
    {
        if (N == 1)
            printf("There is 1 account and no account is modified");
        else
            printf("There are %d accounts and no account is modified", N);
    }
    else
    {
        cout << count << endl;
        for (int i = 0; i < a_vec.size(); i++)
        {
            cout << a_vec[i] << " " << b_vec[i] << endl;
        }
    }
}
