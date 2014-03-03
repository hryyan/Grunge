#include <stdio.h>

int main()
{
    //freopen("13.input", "r", stdin);
    unsigned int hashmat, opponent;
    while(scanf("%d %d", &hashmat, &opponent) == 2)
    {
        printf("%d\n", opponent - hashmat);
    }
    return 0;
}