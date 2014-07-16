#include <cstdio>
#include <vector>
using std::vector;

const int MAXN = 150;
vector<vector<int> > src;
vector<vector<int> > dst;
int map[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
vector<int> s_a, s_b, s_c, s_d, s_e, s_f, s_g, s_h;
vector<int> d_a, d_b, d_c, d_d, d_e, d_f, d_g, d_h;
src.push_back(s_a);
src.push_back(s_b);
src.push_back(s_c);
src.push_back(s_d);
src.push_back(s_e);
src.push_back(s_f);
src.push_back(s_g);
src.push_back(s_h);
dst.push_back(s_a);
dst.push_back(s_b);
dst.push_back(s_c);
dst.push_back(s_d);
dst.push_back(s_e);
dst.push_back(s_f);
dst.push_back(s_g);
dst.push_back(s_h);

bool verify()
{
    // 确认需要的牌在S1和S2中
    for (int j = 0; j < 8; ++j)
    {
        if (src.at(j).size() != dst.at(j).size())
            return false;
    }
    return true;
}

int main()
{
    freopen("POJ3087.input", "r", stdin);

    int n;
    scanf("%d\n", &n);
    for (int i = 1; i < n+1; ++i)
    {
        s_a.clear();
        s_b.clear();
        s_c.clear();
        s_d.clear();
        s_e.clear();
        s_f.clear();
        s_g.clear();
        s_h.clear();
        d_a.clear();
        d_b.clear();
        d_c.clear();
        d_d.clear();
        d_e.clear();
        d_f.clear();
        d_g.clear();
        d_h.clear();
        int c = 0, offset = 0;
        char str[MAXN];

        // 读取第一行和第二行，第二行要加一个offset
        scanf("%d\n", &c);
        for (int j = 0; j < 2; ++j)
        {
            scanf("%s", str);
            int o = 0;
            while (str[o] != '\n')
            {
                for (int k = 0; k < 8; ++k)
                    if (str[o] == map[k])
                        src.at(k).push_back(offset+o);
                o++;
            }
            offset = c;
        }

        // 读取结果
        scanf("%s", str);
        int o = 0;
        while (str[0] != '\n')
        {
            for (int j = 0; j < 8; ++j)
                if (str[o] == map[j])
                    dst.at[j].push_back(o);
            o++;
        }
        
        if (!verify())
            printf("%d -1\n", i);

        
    }
}