#include <iostream>

using namespace std;

void merge(long a[], long workSpc[], int lowPtr, int highPtr, int upBound) {
    int j = 0;                             // workspace index
    int lowBound = lowPtr;
    int mid = highPtr-1;
    int n = upBound-lowBound+1;       // # of items

    while(lowPtr <= mid && highPtr <= upBound)
        if(a[lowPtr] < a[highPtr] )
            workSpc[j++] = a[lowPtr++];
        else
            workSpc[j++] = a[highPtr++];

    while(lowPtr <= mid)
        workSpc[j++] = a[lowPtr++];

    while(highPtr <= upBound)
        workSpc[j++] = a[highPtr++];

    for(j=0; j<n; j++)
        a[lowBound+j] = workSpc[j];
}

void merge2(int orig[], int temp[], int size, int subSize) {
    for (int j = 0; j < size; j += subSize * 2) {
        int index1 = j;
        int index2 = j + subSize;
        int count1 = 0;
        int count2 = 0;
        while (count1 < subSize && count2 < subSize && index2 + count2 < size) {
            if (orig[index1 + count1] < orig[index2 + count2]) {
                temp[index1 + count1 + count2] = orig[index1 + count1];
                count1++;
            } else {
                temp[index1 + count1 + count2] = orig[index2 + count2];
                count2++;
            }
        }
        if (index2 + count2 >= size) {
            while (index1 + count1 < size) {
                temp[index1 + count1 + count2] = orig[index1 + count1];
                count1++;
            }
        } else if (count1 == subSize) {
            while (count2 < subSize) {
                temp[index1 + count1 + count2] = orig[index2 + count2];
                count2++;
            }
        } else if (count2 == subSize) {
            while (count1 < subSize) {
                temp[index1 + count1 + count2] = orig[index1 + count1];
                count1++;
            }
        }
    }
}

int main() {
    // long a[10] = {12,20,100,143,179,5,12,121,320,430}; // two sorted halves to merge
    // long * temp = new long[10];
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << a[i] << ",";
    // }
    // cout << endl;
    // merge(a, temp, 0, 5, 9); // 0-4 and 5-9
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << a[i] << ",";
    // }
    
    int const size = 127;
    int* test = new int[size];
    for (int i = 0; i < size; i++) {
        test[i] = size-i;
    }
    for (int i = 0; i < size; i++) {
        cout << test[i] << " ";
    }
    cout << endl;
    int* testTemp = new int[size];
    int runCount = 0;
    for (int i = 1; i < size * 2; i *= 2) {
        if (runCount % 2 == 0) { 
            merge2(test, testTemp, size, i);
        } else {
            merge2(testTemp, test, size, i);
        }        
        runCount++;
    }
    if (runCount % 2 == 1) {
        for (int i = 0; i < size; i++) {
            test[i] = testTemp[i];
        }
    }
    for (int i = 0; i < size; i++) {
        cout << test[i] << " ";
    }
    // delete test;
    // test = NULL;
    // delete testTemp;
    // testTemp = NULL;
    cout << endl;

}