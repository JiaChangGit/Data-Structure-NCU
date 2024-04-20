#include <iostream>
#include <stdlib.h> /* atoi */
#include <vector>
#include <algorithm>
using namespace std;

int G=0;
// Stores a Non-zero element.
class Vertex
{
public:
    int row = 0, col = 0, value = 0;
    Vertex() {}
    Vertex(int row, int col, int value)
    {
        this->row = row;
        this->col = col;
        this->value = value;
    }
    bool operator<(const Vertex &r) const;
};

// Stores a complete matrix, contains info and list of elems.
class Matrix
{
public:
    int row_count, col_count, val_count = 0;
    vector<Vertex> list;

    Matrix(int row, int col)
    {
        row_count = row;
        col_count = col;
    }
    // T-transform, as row major order. Return result.
    Matrix lazyTranspose();
    // Perform matrix multiplication algorithm. Return result. (this = A, another = B)
    Matrix multiplication(Matrix another);
    // Pushback a vertex to list, valcount++ either.
    void storeSum(Vertex v);
    // Print matrix's non-zero elements only.
    void print();
};

// Abstract the matrix's non-zero elements. Row major.
Matrix ParseInputMatrix(int row, int col);

//Compare two int value, if former is smaller then return -1.
int compare(int a, int b)
{
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    return 1;
}

int main()
{
    int row = 0, col = 0;
    cin >> row >> col;
    Matrix m1 = ParseInputMatrix(row, col);

    cin >> row >> col;
    Matrix m2 = ParseInputMatrix(row, col);

    Matrix result = m1.multiplication(m2);
    cout<<m1.row_count<<" "<<m2.col_count<<" "<<G<<"\n";
    result.print();
}

Matrix ParseInputMatrix(int row, int col)
{
    Matrix m(row, col); // declare and init
    char *input = new char[10];
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            // if non-zero element, pushback & valcount++
            cin >> input;
            int value = atoi(input); // convert string to int. Code review on var 'input' type: char(x), int(o) will be easier.
            if (value != 0)
                m.list.push_back(Vertex(r, c, value));
        }
    }
    m.val_count = m.list.size();
    return m;
}

// over load the operator<, compare 'row' , if equal then compare 'col'
bool Vertex::operator<(const Vertex &r) const
{
    if (row != r.row)
        return row < r.row;
    return col < r.col;
}

void Matrix::print()
{
    for (auto v : this->list)
        cout << v.row << " " << v.col << " " << v.value << endl;
}

void Matrix::storeSum(Vertex v)
{
    if (v.value == 0)
        return;
    G++;
    this->list.push_back(v);
    this->val_count = this->list.size();
}

Matrix Matrix::lazyTranspose()
{
    // init transpose matrix's header
    Matrix trans(this->col_count, this->row_count);
    trans.val_count = this->val_count;

    // Exchange every row & col
    for (auto v : this->list)
    {
        Vertex newv(v.col, v.row, v.value); // swap
        trans.list.push_back(newv);
    }

    // sort by row then col, make sure it's row major order. O(nlogn)
    std::sort(trans.list.begin(), trans.list.end());
    return trans;
}

Matrix Matrix::multiplication(Matrix another)
{
    Matrix result(this->row_count, another.col_count);

    // repalce another one with its transpose
    another = another.lazyTranspose();
    // need to pushback a dummy vertex as boundary condition? Yes! (Do not change valcount)
    this->list.push_back(Vertex(this->row_count, -1, 0));     // A
    another.list.push_back(Vertex(another.row_count, -1, 0)); // B

    int sum = 0, rowBegin = 0;
    int currentRow = this->list[0].row;   // Current calculating row number of result matrix
    int currentCol = another.list[0].row; // Current calculating col number of result matrix

    for (int i = 0; i < this->val_count;)
    { // "i" is index of vector in "this", increase manually
        currentCol = another.list[0].row;
        for (int j = 0; j < another.val_count + 1;)
        { // "j" is index of vector in "another", increase manually
            if (this->list[i].row != currentRow)
            {
                // Row number == currentRow in matrix "this" ends, go on next row. WTF is this comment ?!
                result.storeSum(Vertex(currentRow, currentCol, sum));
                sum = 0;
                i = rowBegin;
                for (; another.list[j].row == currentCol; j++);
                currentCol = another.list[j].row;
            }
            else if (another.list[j].row != currentCol)
            {
                result.storeSum(Vertex(currentRow, currentCol, sum));
                sum = 0;
                i = rowBegin;
                currentCol = another.list[j].row;
            }
            else
                switch (compare(this->list[i].col, another.list[j].col))
                {
                case -1: // A doen't has corresponding column, advance next term on A
                    i++;
                    break;
                case 0: // Has corresponding vertex, mutiply them
                    sum += (this->list[i++].value * another.list[j++].value);
                    break;
                case 1: // A doen't has corresponding column, advance next term on A
                    j++;
                    break;
                }
        } // end of for loop(B)
        // Find next row number of A/this, reset rowBegin & currentRow
        for (; this->list[i].row == currentRow; i++);
        rowBegin = i;
        currentRow = this->list[i].row;
    } // end of for loop(A)
    return result;
}