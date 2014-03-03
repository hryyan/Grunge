#include <stdio.h>
char stack[512];
int top=0;
void push(char c)
{
    stack[top]=c;
    top++;
}
char pop()
{
    top--;
    return stack[top];
}
int is_empty()
{
    return 0==top;
}
void main()
{
    push('1');
    push('2');
    push('3');
    push('4');
    push('5');
    while(!is_empty())
        putchar(pop());
    putchar('/n');
    getch();
}