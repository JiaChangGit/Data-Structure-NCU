#include <stdio.h>
#include <stdlib.h>

struct poly
{
    int coef;
    int exp;
    struct poly *next;
};

typedef struct poly Node;
void Enq(int, int, Node, Node *, Node *);
void Deq(Node, Node *, Node *);
void Add();
void PrintPoly(Node *);

Node P1, P2, P3;
Node *front1 = NULL, *rear1 = NULL;
Node *front2 = NULL, *rear2 = NULL;
Node *front3 = NULL, *rear3 = NULL;

int main()
{
    int size, c, e;
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d %d", &c, &e);
        Enq(c, e, P1, front1, rear1);
    }

    scanf("%d", &size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d %d", &c, &e);
        Enq(c, e, P2, front2, rear2);
    }
    Add();
    PrintPoly(front3);
    return 0;
}

void Enq(int c, int e, Node p, Node *front, Node *rear)
{
    Node *t = (Node *)malloc(sizeof(Node));
    t->coef = c;
    t->exp = e;
    t->next = NULL;
    printf("進入enq\n"); //////////////////////////
    if (front == NULL)
    {
        front = t;
        printf("front=t\n"); /////////////////////////////
    }
    else
    {
        rear->next = t;
        rear = t;
    }
    printf("出來enq\n"); ////////////////////////
}
void Deq(Node p, Node *front, Node *rear)
{
    
    Node *t = (Node *)malloc(sizeof(Node));
    printf("進入d\n"); ///////////////////////////
    if (front == NULL)
    {
        return;
    }
    else
    {
        t = front;
//        i = front->coef; //////////////////
        front = front->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        free(t);
        printf("free\n"); ////////////////////
        return;
    }
    printf("deqnonono\n"); /////////////////////
}
void Add()
{
    int temp_c, temp_e;
    while (front1 != NULL && front2 != NULL)
    {printf("add之while\n"); /////////////////////////
        if (front1->exp == front2->exp)
        {
            temp_c = front1->coef + front2->coef;
            temp_e = front1->exp + front2->exp;
            Enq(temp_c, temp_e, P3, front3, rear3);
            Deq(P1, front1, rear1);
            Deq(P2, front2, rear2);
        }
        else if (front1->exp > front2->exp)
        {
            temp_c = front1->coef;
            temp_e = front1->exp;
            Enq(temp_c, temp_e, P3, front3, rear3);
            Deq(P1, front1, rear1);
        }
        else{
                temp_c = front2->coef;
                temp_e = front2->exp;
                Enq(temp_c, temp_e, P3, front3, rear3);
                Deq(P2, front2, rear2);
        }
    }
}
void PrintPoly(Node *front) //輸出多項式
{
printf("print\n"); /////////////////////////
    while (front)
    {
        if (front->coef != 0)
        {
            printf("%d %d ", front->coef, front->exp);
            front = front->next;
        }
        front = front->next;
    }
}