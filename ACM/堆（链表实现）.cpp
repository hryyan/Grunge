#include <stdio.h>
#include <stdlib.h>

struct _node
{
    int data;
    struct _node *next;
};
typedef struct _node node, *pnode;

struct _linkqueue
{
    pnode front;
    pnode rear;
};
typedef struct _linkqueue linkqueue, *linkqueue;

linkqueue init_queue()
{
    linkqueue lq;
    lq.front = lq.rear = (pnode)malloc(sizeof(node));
    if (lq.front == NULL)
    {
        printf("Error, malloc failed...\n");
        return NULL;
    }
    lq.rear->data = -1;
    lq.rear->next = NULL;
}

int isEmpty_queue(linkqueue lq)
{
    if (lq.front == lq.rear)
        return 1;
    else
        return 0;
}

linkqueue insert_item(linkqueue lq, int data)  
{  
    pnode pq;  
    pq=(pnode)malloc(sizeof(node));  
    if(pq == NULL)  
    {  
        printf("Error. malloc is fail.../n");  
        exit(1);  
    }  
    pq->data=data;  
    pq->next=lq.rear->next;  
    lq.rear->next=pq;  
    lq.rear=lq.rear->next;  
    return lq;  
}  
linkqueue delete_item(linkqueue lq, int *data)  
{  
    if(empty_queue(lq))  
    {  
        printf("queue is empty.../n");  
        exit(1);  
    }  
    *data=lq.front->data;  
    lq.front=lq.front->next;  
    return lq;  
}  
int len_queue(linkqueue lq)  
{  
    int len=0;  
    while(lq.front)  
    {  
        len++;  
        lq.front=lq.front->next;  
    }  
    return len;  
}  
void display(linkqueue lq)  
{  
    linkqueue p;  
    p=lq;  
    if(empty_queue(lq))  
    {  
        printf("queue is empty.../n");  
        return;  
    }  
    while(p.front->next)  
    {  
        printf("%4d", p.front->data);  
        p.front=p.front->next;  
    }  
    printf("%4d/n/n", p.front->data);  
}  
void main()  
{  
    int *data = (int *)malloc(sizeof(int));  
    linkqueue lq;  
    lq=init_queue();  
    lq=insert_item(lq, 1);  
    lq=insert_item(lq, 2);  
    lq=insert_item(lq, 3);  
    lq=insert_item(lq, 4);  
    lq=insert_item(lq, 5);  
    display(lq);  
    printf("len of queue is: %d/n/n", len_queue(lq));  
    lq=delete_item(lq, data);  
    printf("delete %d/n", *data);  
    display(lq);  
    lq=delete_item(lq, data);  
    printf("delete %d/n", *data);  
    display(lq);  
    getch();  
}  