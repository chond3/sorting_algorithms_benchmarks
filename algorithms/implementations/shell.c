#include "../headers/algorithms.h"

void shell(int*array, int n){
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = array[i];
            int j = i - gap;
            while (j >= 0 && array[j] > key) {
                array[j + gap] = array[j];
                j -= gap;
            }
            array[j + gap] = key;
        }
    }
}
