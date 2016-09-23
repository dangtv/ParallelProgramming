/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dang
 *
 * Created on September 21, 2016, 3:53 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <omp.h>

#define NT 4

using namespace std;
int M = 20;
float t = 0;
float time = 1;
float D = 0.1;
float dx = 0.1;
float dt = 0.01;
float bientrai = 100;
float bienphai = 25;
float T[100];
float Tnew[100];
float Daohambac2x[100];
int i = 0;
int Mc, start, stop, id;

/*
 * 
 */

float daohambac2(float a, float b, float c, float deltax) {
    return (a - 2 * b + c) / (deltax * deltax);
}

int main(int argc, char** argv) {

    // khoi tao
    for (i = 0; i < M; i++) {
        T[i] = 25;
    }

    Mc = M / NT;
    omp_set_num_threads(NT);

#pragma omp parallel private(i,id,start,stop, t)
    {
        id = omp_get_thread_num();
        start = Mc*id;
        stop = start + Mc;
        // lap 
        while (t < time) {
            // tinh dao ham bac 2 theo x
#pragma omp barrier 
            {
                for (i = start; i < stop; i++) {
                    if (i == 0) {
                        Daohambac2x[i] = daohambac2(bientrai, T[i], T[i + 1], dx);
                    } else if (i == M - 1) {
                        Daohambac2x[i] = daohambac2(T[i - 1], T[i], bienphai, dx);
                    } else {
                        Daohambac2x[i] = daohambac2(T[i - 1], T[i], T[i + 1], dx);
                    }
                    //            printf("%f; ",Daoham2x[i]);
                    //            printf("%f \n", Tnew[i]);
                }
            }
#pragma omp barrier
            for (i = start; i < stop; i++) T[i] = T[i] + D * Daohambac2x[i] * dt;
            t = t + dt;
        }

    }

    for (i = 0; i < M; i++) printf("%f, ", T[i]);
    return 0;
}

