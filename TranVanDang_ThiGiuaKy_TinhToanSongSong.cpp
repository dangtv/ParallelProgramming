/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <math.h>
#include <omp.h>
#define NT 6
#define N 20
#define EPS 0.01
int Mc, start, stop, id;
double diff[NT], mean; // diff là mảng các diff của từng luồng 
double max;
int i, j;
double u[N][N], w[N][N];
int done = 0;

/* setup dieu kien bien*/

int main(int argc, char** argv) {
    mean = 0.0;
    for (i = 0; i < N; i++) {
        u[i][0] = u[i][N - 1] = u[0][i] = 100.0;
        u[N - 1][i] = 0.0;
        mean = (u[i][0] + u[i][N - 1] + u[0][i] + u[N - 1][i]) / 4.0;
    }
    // khởi tạo giá trị đầu
    for (i = 1; i < N - 1; i++)
        for (j = 1; j < N - 1; j++)
            u[i][j] = mean;

    // chia mien tinh toan theo hang
    Mc = (N - 2) / NT;
    omp_set_num_threads(NT);

    // tin toan tang thai can bang nhieu
#pragma omp parallel private(i,j,id,start,stop,done)
    {
        id = omp_get_thread_num();
        // xác định khoảng tính toán ứng với thread này 
        start = 1 + Mc*id;
        stop = start + Mc;

        while (!done) {

            {
                // tính toán trên khoảng tương ứng cho mỗi luồng
                diff[id] = 0.0;
                for (i = start; i < stop; i++) {
                    for (j = 1; j < N - 1; j++) {
                        w[i][j] = (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1]) / 4.0;
                        if (fabs(w[i][j] - u[i][j]) > diff[id])
                            diff[id] = fabs(w[i][j] - u[i][j]);
                    }
                }

            }
#pragma omp barrier
            // xác định biến diff lớn nhất của các luồng
            if (id == 0) {
                max = 0;
                for (i = 0; i < NT; i++) {
                    if (max < diff[i]) max = diff[i];
                }
            }
#pragma omp barrier
            // kiểm tra xem max (diff) có thảo mãn điều kiện dừng không
            if (max <= EPS) done = 1;

#pragma omp barrier
            //cập nhập
            if(!done){
            for (i = start; i < stop; i++)
                for (j = 1; j < N - 1; j++) u[i][j] = w[i][j];
            }
#pragma omp barrier
        }

    }

    //in ket qua
    for (i = 1; i < N - 1; i++) {
        for (j = 0; j < N; j++)
            printf("%6.2f", u[i][j]);
        printf("\n");
    }
    return 0;
}
