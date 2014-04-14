#include<stdio.h>
//#define DEBUG

void _swap(int *p1, int *p2) {
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void quickSort(int *arr, int size) {
    if (size < 2)
        return;

    int pivot = arr[0];

    int l = 0;
    int u = size;

    while (l < u) {
        do l++; while (arr[l] < pivot && l <= u);
        do u--; while (arr[u] > pivot);
        if (l > u)
            break;
        _swap(arr + l, arr + u);
    }
    _swap(arr, arr + u);
    quickSort(arr, u);
    quickSort(arr + u + 1, size - u - 1);
}

#ifdef DEBUG
int main() {
    int i;
    int a[100] = {-100, 10, 4, 2, 342, 2111, 0, -2, 31121, 3131, 1, 212, 12, 313, 423, 54,
        8658, 4, 54, 32, -223, 424, -535, -555, -33, 34, 5, 3, 0, 33, 5332, -3333333, 333333,
        434, 532225, 5600, 33232, 53333, -3323, 0, 0, 22332, 3235532, 44, 45, 46, 47, 48, 49,
        50, 4142, 3213, 21213, 12, 2424, 532, -343, 31232, 1233214, 421245, 3232432,
        1231312, 42, 0, 42, 4222, 3, -424242424, 4222, 78900, 776, 72, 73, 74, 454, 64343,
        2234, 113, 1244, 242, 4333553, 23432, 83, 49902, 3323, -2324, -42442, -323, 89, 90,
        3333, 323, 44, 2, 2222, 323, 97, 98, 99, 100};
    quickSort(a, 100);
    for (i = 0; i < 100; i++)
        printf("%d\n", a[i]);
}
#endif
