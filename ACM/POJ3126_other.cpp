#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

bool ifPrime[10000];
bool ifVisit[10000];
int pathCount[10000];

int main()
{
    // freopen("POJ3126.input", "r", stdin);
    // freopen("POJ3126.allsource", "r", stdin);

    for ( int i = 0 ; i < 10000 ; i ++ )
        ifPrime[i] = true;
    ifPrime[0] = false;
    ifPrime[1] = false;
    for ( int i = 2 ; i < 100 ; i ++ )
    {
        if ( ifPrime[i] )
            for ( int j = 1 ; i*j < 10000 ; j ++ )
                ifPrime[i*j] = false;
    }
    int number;
    cin>>number;
    int num1, num2;
    for ( int i = 0 ; i < number ; i ++ )
    {
        cin>>num1>>num2;
        queue<int> q;
        for ( int j = 1000 ; j < 10000 ; j ++ )
        {
            ifVisit[j] = false;
            pathCount[j] = 0;
        }
        q.push(num1);
        ifVisit[num1] = true;
        while ( !q.empty() )
        {
            int tempInt = q.front();
            q.pop();
            if ( tempInt == num2 )
            {
                break;
            }
            for ( int t = 1 ; t <= 1000 ; t *= 10 )
            {
                int di = tempInt;
                di /= t;
                di %= 10;
                int w = tempInt - di*t; 
                for ( int j = 0 ; j < 10 ; j ++ )
                {
                    if ( t == 1000 && j == 0 )
                        continue;
                    if ( j != di )
                    {
                        int nowNum = j*t + w;
                        if ( ifPrime[nowNum] && !ifVisit[nowNum] )
                        {
                            q.push(nowNum);
                            pathCount[nowNum] = pathCount[tempInt] +1;
                            ifVisit[nowNum] = true;
                        }
                    }
                }
            }
        }
        cout<<pathCount[num2]<<endl;
    }
}
