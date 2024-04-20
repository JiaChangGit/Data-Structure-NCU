#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Value
{
    T val;
    Value(T val) : val(val) {}
};

template <typename T>
struct Node
{
    Node(T val) : data(Value<T>(val)), left(nullptr), right(nullptr) {}
    Value<T> data;
    Node<T> *left;
    Node<T> *right;
};

template <typename T>
void inorderTraverse(Node<T> *node)
{
    if (node == nullptr)
        return;
    else
    {
        inorderTraverse(node->left);
        cout << node->data.val << " ";
        inorderTraverse(node->right);
    }
}

template <typename T>
Node<T> *completeBtree(T arr[], Node<T> *node, size_t pos, size_t arr_size)
{
    if (pos < arr_size)
    {
        node = new Node<T>(arr[pos]);
        node->left = completeBtree<T>(arr, node->left, 2 * pos + 1, arr_size);
        node->right = completeBtree<T>(arr, node->right, 2 * pos + 2, arr_size);
    }
    return node;
}

int main()
{
    vector<int> v1;
    int input = 0;
    while (cin >> input)
    {
        v1.push_back(input);
        if (cin.get() == '\n')
            break;
    }

    int size = v1.size();
    int *ptr = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < v1.size(); ++i)
        *(ptr + i) = v1[i];

    Node<int> *root = completeBtree<int>(ptr, root, 0, v1.size());
    inorderTraverse<int>(root);
    return 0;
}
