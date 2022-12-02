#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 101
#define _K 4
#define _L 4
#define _M 4

typedef struct {
    int value;
    int column;
    int row;
}matrix;


void print(matrix arr[]);
void multiply(matrix arr1[], matrix arr2[]);
void add(matrix data[]);

int main() {
    int sparse_1[_K][_L] = {
        {0,10,0,5},
        {0,2,4,0},
        {0,0,0,0},
        {3,0,0,7},
    };
    int sparse_2[_K][_L] = {
        {1,0,0,2},
        {0,0,3,0},
        {0,8,0,0},
        {5,0,10,0}
    };
    int transposed_sparse_2[_K][_L] = {};
    
    matrix compressed_1[MAX_TERM] = {};
    matrix compressed_2[MAX_TERM] = {};

    // Taking the transpose of the second sparse matrix
    for (int i = 0; i < _K; i++) {
        for (int j = 0; j < _L; j++) {
            transposed_sparse_2[j][i] = sparse_2[i][j];
        }
    }

    // compressing the first sparse matrix
    int count = 1;
    compressed_1[0].row = _K;
    compressed_1[0].column = _L;
    for (int i = 0; i < _K; i++) {
        for (int j = 0; j < _L; j++) {
            if (sparse_1[i][j] != 0) {
                compressed_1[count].row = i;
                compressed_1[count].column = j;
                compressed_1[count].value = sparse_1[i][j];
                count++;
            }
        }
    }
    compressed_1[0].value = count -1;

    // compressing the transposed version of the second sparse matrix
    count = 1;
    compressed_2[0].row = _K;
    compressed_2[0].column = _L;
    for (int i = 0; i < _K; i++) {
        for (int j = 0; j < _L; j++) {
            if (transposed_sparse_2[i][j] != 0) {
                compressed_2[count].row = i;
                compressed_2[count].column = j;
                compressed_2[count].value = transposed_sparse_2[i][j];
                count++;
            }
        }
    }

    compressed_2[0].value= count -1;
    multiply(compressed_1, compressed_2);
    return 0;
}

void multiply(matrix arr1[], matrix arr2[]) {
    
    int count = 1;
    int temp = 0;
    matrix data[MAX_TERM] = {};

    data[0].row = arr1[0].row;
    data[0].column = arr2[0].row;

    for (int i = 1; i <= arr1[0].value; i++) {
        for (int j = 1; j <= arr2[0].value; j++) {
            if (arr1[i].column == arr2[j].column) {
                data[count].value = arr1[i].value * arr2[j].value;
                data[count].row = arr1[i].row;
                data[count].column = arr2[j].row;
                count++;
            }
        }
    }
    data[0].value = count - 1;
    add(data);
}

void add(matrix data[]) {
    matrix result[MAX_TERM] = {};
    result[0].row = _K;
    result[0].column = _L;
    int count = 1;
    int sum = 0;
    int check = 0;
    for (int i = 1; i <= data[0].value; i++) {
        for (int j = 1; j <= data[0].value; j++) {
            if (data[i].row == data[j].row && data[i].column == data[j].column && i != j) {
                sum += data[i].value + data[j].value;
                data[i].value = 0;
                data[j].value = 0;
                check = 1;
            }
        }
        if (check == 0) {
            result[count].row = data[i].row + 1;
            result[count].column = data[i].column + 1;
            result[count].value = data[i].value;
            count++;
        }
        if (sum != 0) {
            result[count].row = data[i].row + 1 ;
            result[count].column = data[i].column + 1;
            result[count].value = sum;
            sum = 0;
            count++;
        }
        check = 0;
        
    }
    result[0].value = count - 1;
    print(result);
}


void print(matrix arr[]) {
    printf("Sparse Matrix Multiplication:\nRow\tColumn\tValue\n");
    for (int i = 0; i <= arr[0].value; i++)
    {
        printf("%d\t %d\t %d \n", arr[i].row, arr[i].column, arr[i].value);
    }
}




