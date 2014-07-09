#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int MAXN = 100;
int heap[MAXN], length;

void push(int a);
int pop();

int main()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAXN; i++)
        push(rand() % 100);
    for (int i = 0; i < MAXN; i++)
        printf("%d ", pop());
    return 0;
}

void push(int insert_num)
{
    int parent, child;
    parent = child = length; 

    while (child > 0)  /* 该节点不是根节点 */
    {   
        parent = (child-1)/2;  /* 获得该节点的父节点 */
        if (insert_num < heap[parent])
        {
            heap[child] = heap[parent];
            child = parent;    /* 把父节点赋给子节点 */
        }
        else
        {
            break;
        }
    }

    heap[child] = insert_num;
    length++;
}

int pop()
{
    int parent, child;
    parent = child = 0;

    int r_value = heap[0];     /* 需要返回的值 */
    int tmp = 0;
    heap[0] = heap[length-1];  /* 将最后一个值挪到第一个 */
    length--;

    while (parent < length/2)  /* 这个节点有子节点 */
    {
        if (parent*2+2 < length)   /* 这个节点有两个子节点 */
        {
            if (heap[parent*2+1] < heap[parent*2+2])   /* 找值小的那个字节点 */
                child = parent*2+1;
            else
                child = parent*2+2;
        }
        else                       /* 这个节点只有左子节点 */
            child = parent*2+1;

        if (heap[parent] > heap[child])     /* 父节点的值比子节点的值大 */
        {
            tmp          = heap[child];
            heap[child]  = heap[parent];
            heap[parent] = tmp;
            parent = child;        /* 再根据子节点迭代下去 */
        }
        else
            break;
    }
    return r_value;
}