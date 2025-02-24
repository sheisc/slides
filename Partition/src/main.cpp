
#include <iostream>
using namespace std;

typedef bool (*CompareFunc) (long, long);

static void swap(long *pa, long *pb) {
    long tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

// >
static bool is_larger(long x, long pivot) {
    return x > pivot;
}

// >=
static bool is_larger_or_equal(long x, long pivot) {
    return x >= pivot;
}

/*
    [left, right]
    This return the position i of the least element arr[i] which satisfies compare(arr[i], pivot).
    If found
        return i
    else
        return -1
 */
static long get_least_elem_pos(long arr[], long left, long right, CompareFunc compare, long pivot) {
    long pos = -1;
    for (long i = left; i <= right; i++) {
        if (compare(arr[i], pivot)) {
            if (pos != -1) {
                if (arr[i] < arr[pos]) {
                    pos = i;
                }
            } else {
                pos = i;
            }
        }
    }
    return pos;
}

static void PrintArr(long arr[], long n) {
    for (long i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*
    Return the position of pivot in arr[]. 
    If it does not exist
        return -1
    eles
        return i, where arr[i] is the least element, satisfying compare(arr[i], pivot)
 */
long partition(long arr[], long left, long right, CompareFunc compare, long pivot) {
    if (left >= right) {
        return left;
    }

    long pos = get_least_elem_pos(arr, left, right, compare, pivot);
    if (pos == -1) {
        return -1;
    }
    //
    swap(arr + left, arr + pos);
    long last = left;
    // pivot, {< pivot}, {>= pivot}
    for (long i = left + 1; i <= right; i++) {
        if (arr[i] < arr[left]) {
            last++;
            swap(arr + i, arr + last);
        }
    }
     // {< pivot}, pivot, {>= pivot}
    swap(arr + left, arr + last);
    return last;
}

int main(int argc, char **argv) {
    long pivot = 0;
    if (argc > 1) {
        pivot = atol(argv[1]);        
    }
    long arr[] = {0, 0, 0, 3, 3, 0, -2, -2, 7, 6, 0, 7, -4, -4};
    long n = sizeof(arr) / sizeof(arr[0]);
    PrintArr(arr, n);
    long pos = partition(arr, 0, n - 1, is_larger_or_equal, pivot);
    if (pos != -1) {
        partition(arr, pos, n - 1, is_larger, pivot);
    }
    cout << "pivot = " << pivot << endl;
    PrintArr(arr, n);
    return 0;
}


