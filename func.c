//
//  func.c
//  ThreadPool
//
//  Created by Gal Argov Sofer on 2/4/18.
//  Copyright © 2018 Gal Argov Sofer. All rights reserved.
//

#include "func.h"

// Functions
void parseLine(unsigned long long * N, unsigned long long * T, unsigned long long * F, unsigned long long * I, const char *argv[]){
    *N = atoi(argv[1]);
    *T = atoi(argv[2]);
    *F = atoi(argv[3]);
    *I = atoi(argv[4]);
}

float MontePI(int niter){
    int count=0,i;
    double x,y,z;
    for ( i=0; i < niter; i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        z = x*x+y*y;
        if (z<=1) count++;
    }
    return (double)count/niter*4;
}
