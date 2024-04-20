#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct node *Nodeptr;
struct node
{
    int data;
    Nodeptr link;
};

void add_b(Nodeptr *start, int value);
void del(Nodeptr *start, int index);
void ins(Nodeptr *start, int value, int index);
void show(Nodeptr *start);

int main()
{
    Nodeptr ptr = NULL; //宣告一個指向node型 別的指標(作head)，預設為空
    char command[15] = {0};
    int value = 0;
    int index = 0;
    while (scanf("%s", command) != EOF)
    {
        if (strcmp(command, "addBack") == 0)
        {
            scanf("%d", &value);
            add_b(&ptr, value);
        }
        else if (strcmp(command, "addFront") == 0)
        {
            scanf("%d", &value);
            ins(&ptr, value, 0);
        }
        else if (strcmp(command, "addIndex") == 0)
        {
            scanf("%d", &index);
            scanf("%d", &value);
            ins(&ptr, value, index);
        }
        else if (strcmp(command, "deleteIndex") == 0)
        {
            scanf("%d", &index);
            del(&ptr, index);
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }
    show(&ptr);
}

void add_b(Nodeptr *start, int value)
{                          //輸入指向node指標的位址&新增的值
    Nodeptr head = *start; //設一head指向start所指向的node
    Nodeptr temp = (node *)malloc(sizeof(node));
    temp->data = value;
    temp->link = NULL;

    if (*start == NULL)
    {
        *start = temp;
        return;
    }

    while (head && head->link)
    {
        head = head->link;
        if (head->link == NULL)
            break;
    }
    head->link = temp;
}

void del(Nodeptr *start, int index)
{
    if (*start)
    {
        if (index == 0)
        {
            Nodeptr tempptr = *start;
            *start = (*start)->link;
            free(tempptr);
            return;
        }
        else
        {
            int count = 0;
            Nodeptr curptr = *start;
            Nodeptr preptr = *start;
            while (count != index)
            {
                if (curptr->link)
                {
                    count++;
                    preptr = curptr;
                    curptr = curptr->link;
                }
                else
                    break;
            }
            if (count == index)
            {
                preptr->link = curptr->link;
                free(curptr);
                return;
            }
        }
    }
}

void ins(Nodeptr *start, int value, int index)
{
    Nodeptr temp = (node *)malloc(sizeof(node));
    temp->data = value;
    if (index == 0)
    {
        temp->link = *start;
        *start = temp;
        return;
    }
    else if (*start)
    {
        int count = 1;
        Nodeptr curptr = *start;
        while (count != index)
        {
            if (curptr->link)
            {
                count++;
                curptr = curptr->link;
            }
            else
                break;
        }
        if (count == index)
        {
            temp->link = curptr->link;
            curptr->link = temp;
            return;
        }
    }
}

void show(Nodeptr *start)
{
    Nodeptr head = *start;
    while (head)
    {
        printf("%d-->", head->data);
        head = head->link;

    }
    printf("null\n");
}