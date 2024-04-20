#include <stdio.h>
#include <stdlib.h>

void selectionSort(int[], int[], int arr_size);
// not to use swap

void selectionSort(int grade[], int student[], int arr_size)
{
    for (int i = 0; i < arr_size - 1; i++)
    {
        int max = i;

        for (int j = i + 1; j < arr_size; j++)
        {
            if (grade[max] < grade[j])
                max = j;
        }

        int key_g = grade[max];
        int key_s = student[max];
        while (max > i)
        {
            grade[max] = grade[max - 1];
            student[max] = student[max - 1];
            max--;
        }
        grade[i] = key_g;
        student[i] = key_s;
    }
}
int main()
{
    int arr_size;

    scanf("%d", &arr_size);                    // get the number of students
    int *arr1 = calloc(arr_size, sizeof(int)); // for grade
    int *arr2 = calloc(arr_size, sizeof(int)); // for student number

    for (int i = 0; i < arr_size; i++)
    {
        scanf("%d%d", arr2 + i, arr1 + i);
    }

    selectionSort(arr1, arr2, arr_size);

    for (int i = 0; i < arr_size; i++)
    {
        printf("%d\n", *(arr2 + i));
    }

    return 0;
}