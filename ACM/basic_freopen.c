#define LOCAL
#include <stdio.h>
#define INF 1000000000

int main()
{
    #ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    #endif
}

int main()
{
    FILE *fin, *fout;
    fin = fopen("data.in", "rb");
    fout = fopen("data.out", "wb");

    while(fscanf(fin, "%d", &x) == 1)
    {

    }

    fprintf(fout, "%s\n", );
    fclose(fin);
    fclose(fout);
    return 0;
}