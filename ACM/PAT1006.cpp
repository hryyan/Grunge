#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int N;

int transfer(int h, int m, int s)
{
    return h * 60 * 60 + m * 60 + s;
}

int main()
{
    // freopen("PAT1006.input", "r", stdin);

    cin >> N;
    string sign_in_id, sign_out_id, tmp_id;
    int min = 86399, max = 0;
    int i_h, i_m, i_s, in;
    int o_h, o_m, o_s, out;
    for (int i = 0; i < N; ++i)
    {
        cin >> tmp_id;
        scanf("%d:%d:%d %d:%d:%d\n", &i_h, &i_m, &i_s, &o_h, &o_m, &o_s);
        in  = transfer(i_h, i_m, i_s);
        out = transfer(o_h, o_m, o_s);
        min = min < in  ? min : in;
        sign_in_id  = (min == in)  ? tmp_id : sign_in_id;
        max = max > out ? max : out;
        sign_out_id = (max == out) ? tmp_id : sign_out_id;
    }
    cout << sign_in_id << " " << sign_out_id << endl;
}