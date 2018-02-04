//
//  func.h
//  ThreadPool
//
//  Created by Gal Argov Sofer on 2/4/18.
//  Copyright © 2018 Gal Argov Sofer. All rights reserved.
//

#ifndef func_h
#define func_h

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

void parseLine(unsigned long long * N, unsigned long long * T, unsigned long long * F, unsigned long long * I, const char *argv[]);
float MontePI(int niter);

#endif /* func_h */
