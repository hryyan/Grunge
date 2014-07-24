#include<iostream>
const int MAX_NODES = 20;
int node_num = 0;
int max_traffic, choose_num, un_choose_num;
int choose[MAX_NODES], un_choose[MAX_NODES];
int net[MAX_NODES][MAX_NODES];
void dfs(int cur) {
    int temp_max;
    if (cur == node_num) {
        temp_max = 0;
        for (int i = 0;i < choose_num;i++) {
            for (int j = 0;j < un_choose_num;j++) {
                temp_max += net[choose[i]][un_choose[j]];
            }
        }
        if (temp_max > max_traffic) {
            max_traffic = temp_max;
            return ;
        }
    } else {
        choose[choose_num++] = cur;
        dfs(cur+1);
        choose_num--;
        un_choose[un_choose_num++] = cur;
        dfs(cur+1);
        un_choose_num--;
    }
}
int main()
{
    std::cin >> node_num;
    for (int i = 0;i < node_num;i++) {
        for (int j = 0;j < node_num;j++) {
            std::cin >> net[i][j];
        }
    }
    max_traffic = 0;
    dfs(0);
    std::cout << max_traffic << std::endl;
    return 0;
}