#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

int** padMatrix(int** a, int d) {
  a = realloc(a, (d+1) * sizeof(a)); 
  a[d] = calloc(d+1, sizeof(**a) * (d+1)); 
  int i; 
  for (i = 0; i < d; i++) {
    a[i] = realloc(a[i], sizeof(**a) * (d+1)); 
    memset(a[d], 0, sizeof(**a)); 
  }
  return a; 
}

int** malloc_matrix(int d) {
  int** array = malloc(d * sizeof(array)); 
  int i; 
  for (i = 0; i < d; i++) {
    array[i] = calloc(d,sizeof(**array) * d);
    //memset(array[i], 0, sizeof(**array) * d);  
  }
  return array;
}

int** generate_matrix(int d, int* nums, int length) {
  int** array = malloc_matrix(d); 
  int i; 
  int i1 = 0; 
  int i2 = 0; 
  for (i = 0; i < length; i++) {
    i1 = i%d; 
    i2 = i/d; 
    array[i1][i2] = nums[i]; 
  }
  return array; 
}

void printMatrix(int** result, int d) {
  int i,j,k; 
  for (i = 0; i < d; i++) {
    for (j = 0; j < d; j++) {
      printf("%d\n", result[i][j]); 
    }
  }
}

void printDiagonal(int** result, int d) {
  int i; 
  for (i = 0; i < d; i++) {
    printf("%d\n", result[i][i]); 
  }
}

int** matrixSum(int** a, int** b, int** result, int d, int a1, int a2, int b1, int b2, int sign) {
  int i = 0;
  int j = 0; 
  int tempa2 = a2; 
  int tempb2 = b2;  
  //int** result = malloc_matrix(d); 
  for (i = 0; i < d; i++) {
    a2 = tempa2; 
    b2 = tempb2; 
    for (j = 0; j < d; j++) {
      if (sign == 1)
        result[i][j] = a[a1][a2] - b[b1][b2];
      else 
        result[i][j] = a[a1][a2] + b[b1][b2];
      a2++; 
      b2++;   
    }
    a1++; 
    b1++; 
  }
  return result; 
}

int** standardMult(int** a, int** b, int d, int a1, int a2, int b1, int b2) {
  int** result = malloc_matrix(d); 
  int i, j, k;
  int tempa2 = a2; 
  int tempb1 = b1; 
  int tempb2 = b2; 
  int sum = 0;  
  for (i = 0; i < d; i++) {
    b2 = tempb2; 
    for (j = 0; j < d; j++) {
      a2 = tempa2; 
      b1 = tempb1; 
      for (k = 0; k < d; k++) {
        sum += a[a1][a2] * b[b1][b2];
        a2++; 
        b1++;   
      }
      b2++;
      result[i][j] = sum; 
      sum = 0;
    }
    a1++;
  }
  return result; 
}

int** fastSum(int** a, int** b, int** c, int** d, int** result, int n, int sign, int num) {
  int i = 0;
  int j = 0; 
  //int** result = malloc_matrix(n); 
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (sign == 0) {
        if (num == 4)
          result[i][j] = a[i][j] + b[i][j] + c[i][j] + d[i][j];
        else 
          result[i][j] = a[i][j] + b[i][j];
      }
      else if (sign == 1)
        result[i][j] = a[i][j] + b[i][j] - c[i][j] + d[i][j];
      else
        result[i][j] = a[i][j] + b[i][j] - c[i][j] - d[i][j];    
    }
  }
  return result; 
}

int** standardSum(int** a, int**b, int d, int a1, int a2) {
  int i;
  int j; 
  int tempa2 = a2;; 
  for (i = 0; i < d; i++) { 
    a2 = tempa2;
    for (j = 0; j < d; j++) {
      a[a1][a2] = a[a1][a2] + b[i][j];    
      a2++; 
    }
    a1++;
  }
  return a; 
} 

int** strassenMult(int** a, int** b, int d, int a1, int a2, int b1, int b2) {
  if (d == 1) { 
    return standardMult(a, b, d, a1, a2, b1, b2); 
  }
  if (d % 2 == 1) {
    return strassenMult(padMatrix(a,d), padMatrix(b,d), d+1, a1, a2, b1, b2); 
  }

  int** sum = malloc_matrix(d/2); 
  int** sum2 = malloc_matrix(d/2); 
  int** p1 = malloc_matrix(d/2); 
  int** p2 = malloc_matrix(d/2); 
  int** p3 = malloc_matrix(d/2); 
  int** p4 = malloc_matrix(d/2); 
  int** p5 = malloc_matrix(d/2); 
  int** p6 = malloc_matrix(d/2); 
  int** p7 = malloc_matrix(d/2); 

  sum = matrixSum(b, b, sum, d/2, b1 + 0, b2 + d/2, b1 + d/2, b2 + d/2, 1);
  p1 = strassenMult(a, sum, d/2, a1 + 0, a2 + 0, 0, 0); 
  sum = matrixSum(a, a, sum, d/2, a1 + 0, a2 + 0, a1 + 0, a2 + d/2, 0); 
  p2 = strassenMult(sum, b, d/2, 0, 0, b1 + d/2, b2 + d/2); 
  sum = matrixSum(a, a, sum, d/2, a1 + d/2, a2 + 0, a1 + d/2, a2 + d/2, 0); 
  p3 = strassenMult(sum, b, d/2, 0, 0, b1 + 0, b2 + 0); 
  sum = matrixSum(b, b, sum, d/2, b1 + d/2, b2 + 0, b1 + 0, b2 + 0, 1); 
  p4 = strassenMult(a, sum, d/2, a1 + d/2, a2 + d/2, 0, 0); 
  sum = matrixSum(a, a, sum, d/2, a1 + 0, a2 + 0, a1 + d/2, a2 + d/2, 0); 
  sum2 = matrixSum(b, b, sum2, d/2, b1 + 0, b2 + 0, b1 + d/2, b2 + d/2, 0); 
  p5 = strassenMult(sum, sum2, d/2, 0, 0, 0, 0);  
  sum = matrixSum(a, a, sum, d/2, a1 + 0, a2 + d/2, a1 + d/2, a2 + d/2, 1); 
  sum2 = matrixSum(b, b, sum2, d/2, b1 + d/2, b2 + 0, b1 + d/2, b2 + d/2, 0); 
  p6 = strassenMult(sum, sum2, d/2, 0, 0, 0, 0); 
  sum = matrixSum(a, a, sum, d/2, a1 + 0, a2 + 0, a1 + d/2, a2 + 0, 1); 
  sum2 = matrixSum(b, b, sum2, d/2, b1 + 0, b2 + 0, b1 + 0, b2 + d/2, 0); 
  p7 = strassenMult(sum, sum2, d/2, 0, 0, 0, 0); 

  int** result = malloc_matrix(d); 
  sum = fastSum(p5, p4, p2, p6, sum, d/2, 1, 4); 
  result = standardSum(result, sum, d/2, 0, 0); 
  sum = fastSum(p1, p2, p1, p2, sum, d/2, 0, 2); 
  result = standardSum(result, sum, d/2, 0, d/2); 
  sum = fastSum(p3, p4, p3, p4, sum, d/2, 0, 2);
  result = standardSum(result, sum, d/2, d/2, 0);  
  sum = fastSum(p5, p1, p3, p7, sum, d/2, 2, 4);
  result = standardSum(result, sum, d/2, d/2, d/2); 

  free(sum); 
  free(sum2); 
  free(p1);
  free(p2);
  free(p3);
  free(p4);
  free(p5);
  free(p6);
  free(p7);

  return result;  

  // printf("Diagonal of strassen: \n"); 
  // printDiagonal(sum11, d/2); 
  // printDiagonal(sum22, d/2); 
  
}

int** readFile(char* filename, int d) {
  FILE* f; 
  f = fopen(filename, "r"); 
  if (f == NULL) {
    printf("error opening file\n"); 
    exit(-1); 
  }
  int** nums = malloc(sizeof(*nums) * 2); 
  nums[0] = malloc(sizeof(int) * d * d); 
  nums[1] = malloc(sizeof(int) * d * d); 
  int i;
  int c = d*d;
  for (i = 0; i < c; i++) {
    fscanf(f, "%d\n", &nums[0][i]); 
  }
  for (i = 0; i < c; i++) {
    fscanf(f, "%d\n", &nums[1][i]); 
  }
  fclose(f); 
  return nums; 
}

void writeFile(int d, char* filename) {
  int array[3] = {0,1,2}; 
  FILE* f; 
  f = fopen(filename, "w"); 
  if (f == NULL) {
    printf("error writing to file\n"); 
    exit(-1); 
  }
  int num; 
  int i; 
  int c = d*d*2; 
  for (i = 0; i<c; i++) {
    num = rand() % 3; 
    fprintf(f, "%d\n", array[num]); 
  }
  fclose(f); 
}

int main() {
  srand(time(NULL));
  clock_t start; 
  clock_t diff; 
  int duration = 0;
  int d = 8;
  int i; 
  writeFile(d, "nums.txt"); 
  int** nums = readFile("nums.txt", d); 
  int** a = generate_matrix(d, nums[0], d*d); 
  int** b = generate_matrix(d, nums[1], d*d); 
  int** a2 = generate_matrix(d, nums[0], d*d);  
  int** b2 = generate_matrix(d, nums[1], d*d); 
  int j;
  // printf("a matrix: \n"); 
  // printMatrix(a, d); 
  // printf("b matrix: \n");
  // printMatrix(b, d); 
  // printf("after pad:\n"); 
  // printf("a matrix:\n"); 
  // printMatrix(padMatrix(a, d), d+1); 
  // printf("b matrix:\n"); 
  // printMatrix(padMatrix(b, d), d+1); 

  printf("strassen:\n"); 
  start = clock(); 
  printMatrix(strassenMult(a, b, d, 0, 0, 0, 0), d);
  diff = clock() - start; 
  duration = diff/ CLOCKS_PER_SEC; 
  printf("regular: \n"); 
  //printMatrix(a2, d); 
  int** standard = standardMult(a2, b2, d, 0, 0, 0, 0); 
  printMatrix(standard, d);
  free(standard); 
  free(a); 
  free(b);  

  //standardMult(a, b, d, 0, 0); 
  //standardMult(a,b,d/2, 0, d/2, d/2, 0); 
   // printf("sum:\n");
   // printMatrix(matrixSum(a, b, d/2, d/2, d/2, 0, d/2, 1), d/2); 
}
  
