#include <iostream>
#include <queue>
//#define NEW2D(H, W, TYPE) (TYPE **)new2d(H, W, sizeof(TYPE))
using namespace std;
typedef struct point point;
struct point
{
    int row;
    int col;
    point *link;
};

queue<point *> q;
int top = -1;
int found = 0;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void bfs(int **data, int **vis, point *start, point target, int **path);
void print(int **path);
void *new2d(int m, int n, int size);

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    //初始化陣列
    int **data = (int**)new2d(m + 2, n + 2, sizeof(int));
    int **vis = (int**)new2d(m + 2, n + 2, sizeof(int));
    int **path = (int**)new2d(m * n, 2, sizeof(int));
    /*
    int **data = NEW2D(m + 2, n + 2, int);
    int **vis = NEW2D(m + 2, n + 2, int);
    int **path = NEW2D(m * n, 2, int);
    */

    for (int t = 0; t < n + 2; t++)
    {
        data[0][t] = 1;
        data[m + 1][t] = 1;
    }
    for (int t = 0; t < m + 2; t++)
    {
        data[t][0] = 1;
        data[t][n + 1] = 1;
    }

    for (int i = 0; i < m + 2; i++)
    {
        for (int j = 0; j < n + 2; j++)
        {
            vis[i][j] = 0;
        }
    }

    for (int i = 1; i < m+1; i++)
    {
        for (int j = 1; j < n+1; j++)
        {
            scanf("%d", &data[i][j]);
        }
    }
    //設定起點終點
    point *start = new point;
    start->row = 1;
    start->col = 1;
    point target;
    target.row = m;
    target.col = n;

    vis[1][1] = 1;
    q.push(start);
    bfs(data, vis, start, target, path);
    print(path);
}

void *new2d(int h, int w, int size)
{
    int i;
    char **p;
    p = (char **)new char[h * sizeof(char *) + h * w * size];
    for (i = 0; i < h; i++)
    {
        p[i] = ((char *)(p + h)) + i * w * size;
    }
    return p;
}

void bfs(int **data, int **vis, point *start, point target, int **path)
{
    while (!q.empty())
    {
        point *position = q.front(); //取得queue儲存的第一個位置
        q.pop();
        if (position->row == target.row && position->col == target.col)
        {
            do
            {
                top++;
                path[top][0] = position->row;
                path[top][1] = position->col;
                position = position->link;
            } while ((position->row != start->row) || (position->col != start->col));
            top++;
            path[top][0] = position->row;
            path[top][1] = position->col;
            found = 1;
            break;
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                int row, col;
                row = position->row + dir[i][0];
                col = position->col + dir[i][1];
                if (data[row][col] == 0 && vis[row][col] == 0)
                {
                    point *temp = new point;
                    temp->row = row;
                    temp->col = col;
                    temp->link = position;
                    q.push(temp);
                    vis[row][col] = 1;
                }
            }
        }
    }
}

void print(int **path)
{
    if (found == 0)
    {
        printf("Can't reach the exit!");
    }
    else
    {
        while (top > -1)
        {
            printf("(%d,%d) ", path[top][0] - 1, path[top][1] - 1);
            top--;
        }
    }
}