#ifndef SORT_H
#define SORT_H

#if (CPP)
void sort_vector_vector() {
    vector<vector<int>> items1;
    sort(items1.begin(), items1.end(), [&](const vector<int>& x, const vector<int>& y) {
        // ascending order
        return (x[0] < y[0]);
    });

    vector<vector<int>> items11;
    sort(items11.begin(), items11.end(), [&](const vector<int>& x, const vector<int>& y) {
        // ascending order
        if (x[1] == y[1]) {
            return (x[0] < y[0]);
        }
        return (x[1] < y[1]);
    });

    vector<int> items2;
    sort(items2.begin(), items2.end(), [&](const int& x, const int& y) {
        // descending order
        return (x > y);
    });

    vector<pair<int, int>> occurrencesSort(occurrences.begin(), occurrences.end());
    sort(occurrencesSort.begin(), occurrencesSort.end(), [&](auto x1, auto x2) {
        // ascending order
        return x1.second < x2.second;
    });
}
#else
int qsort_ascending_compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int qsort_descending_compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int qsort_ascending_compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 > *(char*)c2);
}
int qsort_descending_compareChar(const void* c1, const void* c2) {
    // descending order
    return (*(char*)c1 < *(char*)c2);
}
int qsort_ascending_compareString(const void* str1, const void* str2) {
    // ascending order
    return strcmp(*(char**)str1, *(char**)str2);
}
int qsort_descending_compareString(const void* str1, const void* str2) {
    // descending order
    return strcmp(*(char**)str2, *(char**)str1);
}
int qsort_ascending_compareIntArray(const void* a1, const void* a2) {
#if (1)  // A[][]
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;
#else    // int** pA = (int**)malloc(n * sizeof(int*));
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;
#endif

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int qsort_descending_compareIntArray(const void* a1, const void* a2) {
#if (1)  // A[][]
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;
#else    // int** pA = (int**)malloc(n * sizeof(int*));
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;
#endif

    // descending order
    if (p1[0] == p2[0]) {
        return (p1[1] < p2[1]);
    }

    return (p1[0] < p2[0]);
}

typedef struct {
    int number;
    int times;
} pair;
int qsort_descending_compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->times;
    int pb = ((pair*)b)->times;

    // ascending order
    return (pa > pb);
}
#endif

#endif  // SORT_H
