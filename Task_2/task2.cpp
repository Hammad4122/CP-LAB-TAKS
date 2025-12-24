#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void processBuffer(int* ptr, int size, int X) {
    if (X % 2 == 0) {
        int* left = ptr;
        int* right = ptr + size - 1;
        
        while (left < right) {
            while (left < right && (*(left) % 2 == 0)) {
                left++;
            }
            
            while (left < right && (*(right) % 2 == 1)) {
                right--;
            }
            
            if (left < right) {
                swap(left, right);
                left++;
                right--;
            }
        }
        
        int* boundary = ptr;
        while (boundary < ptr + size && (*(boundary) % 2 == 0)) {
            boundary++;
        }
        
        for (int* i = ptr; i < boundary; i++) {
            for (int* j = i + 1; j < boundary; j++) {
                if (*(i) < *(j)) {
                    swap(i, j);
                }
            }
        }
        
        for (int* i = boundary; i < ptr + size; i++) {
            for (int* j = i + 1; j < ptr + size; j++) {
                if (*(i) > *(j)) {
                    swap(i, j);
                }
            }
        }
        
    } else {
        int* left = ptr;
        int* right = ptr + size - 1;
        
        while (left < right) {
            while (left < right && (*(left) % 2 == 0)) {
                left++;
            }
            
            while (left < right && (*(right) % 2 == 1)) {
                right--;
            }
            
            if (left < right) {
                swap(left, right);
                left++;
                right--;
            }
        }
        
        int* boundary = ptr;
        while (boundary < ptr + size && (*(boundary) % 2 == 0)) {
            boundary++;
        }
        
        for (int* i = ptr; i < boundary; i++) {
            for (int* j = i + 1; j < boundary; j++) {
                if (*(i) > *(j)) {
                    swap(i, j);
                }
            }
        }
        
        for (int* i = boundary; i < ptr + size; i++) {
            for (int* j = i + 1; j < ptr + size; j++) {
                if (*(i) > *(j)) {
                    swap(i, j);
                }
            }
        }
    }
}

void printBuffer(int* ptr, int size) {
    for (int i = 0; i < size; i++) {
        cout << *(ptr + i);
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    int buffer[11];
    
    int sample[11] = {0,9,1,3,1,2,5,2,0,4,6};
    for (int i = 0; i < 11; i++) {
        buffer[i] = sample[i];
    }
    
    cout << "Original Buffer: ";
    printBuffer(buffer, 11);
    
    int X = sample[10];
    
    processBuffer(buffer, 11, X);
    
    cout << "\nProcessed Buffer: ";
    printBuffer(buffer, 11);
    
    return 0;
}