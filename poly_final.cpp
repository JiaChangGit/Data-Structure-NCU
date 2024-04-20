#include <iostream>
using namespace std;

/* 帶附加頭結點的單鏈表的類定義 */
typedef struct PolyNode PolyNode;
typedef struct PolyNode *Polynomial;
//指向結點的指針
struct PolyNode //鏈表結點類的定義
{
    int coef;        //系數
    int expon;       //指數
    Polynomial link; //鏈指針域
};

Polynomial ReadPoly();
void Attach(int c, int e, Polynomial *pRear);
Polynomial Add(Polynomial P1, Polynomial P2);

void PrintPoly(Polynomial P);

int main()
{
    Polynomial P1, P2, PS;

    P1 = ReadPoly();
    P2 = ReadPoly();
    PS = Add(P1, P2);
    PrintPoly(PS);

    return 0;
}

Polynomial ReadPoly() //讀入多項式構成鏈表，並返回鏈表的頭指針
{
    Polynomial first, rear, t;
    int N, c, e;
    scanf("%d", &N);

    first = new PolyNode; //鏈表附加頭結點,這樣可以免除首節點的判斷，保持了操作的一致性
    first->link = NULL;
    rear = first;
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &rear); //將當前項插入多項式鏈表尾部
    }
    t = first;
    first = first->link;
    delete t; //最后刪除附加頭結點
    return first;
}

void Attach(int c, int e, Polynomial *pRear) //將當前項插入多項式鏈表尾部
{
    Polynomial P;
    P = new PolyNode; //創建新節點
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P; //連接新結點
    *pRear = P;         //尾指針指向新節點
}

Polynomial Add(Polynomial P1, Polynomial P2) //多項式加法
{
    Polynomial first, rear, t;
    int sum;
    first = new PolyNode; //鏈表附加頭結點
    first->link = NULL;
    rear = first;
    while (P1 && P2)
    {
        if (P1->expon == P2->expon) //兩數據項指數相等
        {
            sum = P1->coef + P2->coef;
            Attach(sum, P1->expon, &rear);
            P1 = P1->link;
            P2 = P2->link;
        }
        else if (P1->expon > P2->expon) //P1中的數據項指數較大
        {
            Attach(P1->coef, P1->expon, &rear); //把此P1項結點插入到結果多項式鏈表中
            P1 = P1->link;
        }
        else
        {
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->link;
        }
    }
    /*  將未處理完的另一個多項式的所有節點依次復制到結果多項式中去  */
    for (; P1; P1 = P1->link)
        Attach(P1->coef, P1->expon, &rear);
    for (; P2; P2 = P2->link)
        Attach(P2->coef, P2->expon, &rear);

    t = first;
    first = first->link;
    delete t; //刪除附加頭結點
    return first;
}

void PrintPoly(Polynomial P) //輸出多項式
{
    while (P)
    {
        if (P->coef != 0)
        {

            printf("%d %d ", P->coef, P->expon);
            P = P->link;
        }
        else
        {
            P = P->link;
        }
    }
}