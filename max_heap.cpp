#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &a1, vector<string> &s1, int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && a1[l] > a1[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && a1[r] > a1[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(a1[i], a1[largest]);
        swap(s1[i], s1[largest]);

        // Recursively heapify the affected sub-tree
        heapify(a1, s1, n, largest);
    }
}

// Function to delete the root from Heap
void deleteRoot(vector<int> &a1, vector<string> &s1, int &n)
{
    // Get the last element
    int lastElement = a1[n - 1];
    string lastString = s1[n - 1];
    cout << s1[0] << endl;
    // Replace root with last element
    a1[0] = lastElement;
    s1[0] = lastString;

    // Decrease size of heap by 1
    n = n - 1;

    // heapify the root node
    heapify(a1, s1, n, 0);
}

void build_maxheap(vector<int> &a1, vector<string> &s1, int n)
{
    int k;
    for (k = n / 2; k >= 0; k--)
    {
        heapify(a1, s1, n, k);
    }
}

int main()
{
    int size;
    cin >> size;
    vector<string> s1;
    vector<int> a1;
    
    for (int i = 0; i < size; ++i)
    {
        string stmp;
        cin >> stmp;
        s1.push_back(stmp);
        int tmp;
        cin >> tmp;
        a1.push_back(tmp);
    }

    cout << "First three things to do:" << endl;
    build_maxheap(a1, s1, size);
    deleteRoot(a1, s1, size);
    deleteRoot(a1, s1, size);
    deleteRoot(a1, s1, size);
    return 0;
}
