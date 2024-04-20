#include <iostream>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

// Create a node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert a node
struct node *insert(struct node *node, int key)
{
    // Return a new node if the tree is empty
    if (node == NULL)
        return newNode(key);

    // Traverse to the right place and insert the node
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

bool hasPathSum(node *Node, int sum)
{

    bool ans = 0;

    int subSum = sum - Node->key;

    /* If we reach a leaf node and sum becomes 0 then return true*/
    if (subSum == 0 && Node->left == NULL && Node->right == NULL)
        return 1;

    /* otherwise check both subtrees */
    if (Node->left)
        ans = ans || hasPathSum(Node->left, subSum);
    if (Node->right)
        ans = ans || hasPathSum(Node->right, subSum);

    return ans;
}

int main()
{
    struct node *root = NULL;
    int tmp, sum, size;
    cin >> size;
    for (size_t i = 0; i < size; ++i)
    {
        cin >> tmp;
        root = insert(root, tmp);
    }
    cin >> sum;

    if (hasPathSum(root, sum))
        cout << "There exit at least one path in binary search tree.";
    else
        cout << "There have no path in binary search tree.";

    return 0;
}