/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <math.h>
#define N 20
#define EPS 0.01

int main() {
    double diff, mean;
    int i, j;
    double u[N][N], w[N][N];
    printf("ok");
    /* setup dieu kien bien*/
    mean = 0.0;
    for (i = 0; i < N; i++) {
        u[i][0] = u[i][N - 1] = u[0][i] = 100.0;
        u[N - 1][i] = 0.0;
        mean = (u[i][0] + u[i][N - 1] + u[0][i] + u[N - 1][i]) / 4.0;
    }
    // khoi tao gia tri ban dau
    for (i = 1; i < N - 1; i++)
        for (j = 1; j < N - 1; j++)
            u[i][j] = mean;
    // tin toan tang thai can bang nhieu
    for (;;) {
        diff = 0.0;
        for (i = 1; i < N-1; i++)
            for (j = 1; j < N - 1; j++) {
                w[i][j] = (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1]) / 4.0;
                if (fabs(w[i][j] - u[i][j]) > diff)
                    diff = fabs(w[i][j] - u[i][j]);
            }
        if (diff <= EPS) break;
        for (i = 1; i < N - 1; i++)
            for (j = 1; j < N - 1; j++) u[i][j] = w[i][j];
    }

    //in ket qua
    for (i = 1; i < N ; i++) {
        for (j = 0; j < N; j++)
            printf("%6.2f", u[i][j]);
        printf("\n");
    }
    return 0;
}