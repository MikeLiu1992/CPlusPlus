#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <chrono>
#include "quant_vec.h"

#define SAMPLE_SIZE 10000000

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main()
{
    //Generate value:
    double *x1 = new (std::align_val_t(32)) double[SAMPLE_SIZE];
    double *x2 = new (std::align_val_t(32)) double[SAMPLE_SIZE];
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x1[i] = fRand(1, 100000);
        x2[i] = fRand(1, 100000);
    }

    //Assignment Speed:
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<double> x3(SAMPLE_SIZE, 0);
    vector<double> x4(SAMPLE_SIZE, 0);
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x3[i] = x1[i]; 
        x4[i] = x2[i];
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "normal vector assignment time: " << duration << "ms" <<endl;
    t1 = std::chrono::high_resolution_clock::now();
    quant_double f1(x1, SAMPLE_SIZE);
    quant_double f2(x2, SAMPLE_SIZE);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "avx vector assignment time: " << duration << "ms" <<endl;
    double difference = 0;
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        if (abs(f1[i] - x3[i]) > difference)
            difference = abs(f1[i] - x3[i]);
    }
    cout << "max value diff is: " << difference << endl;

    //Element Summing Speed:
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x3[i] += x4[i];
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "normal vector plus time: " << duration  << "ms" << endl;
    t1 = std::chrono::high_resolution_clock::now();
    f1 += f2;
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "avx vector plus time: " << duration  << "ms" << endl;
    difference = 0;
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        if (abs(f1[i] - x3[i]) > difference)
            difference = abs(f1[i] - x3[i]);
    }
    cout << "max value diff is: " << difference << endl;

    //Element Substract Speed:
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x3[i] -= x4[i];
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "normal vector minus time: " << duration  << "ms" << endl;
    t1 = std::chrono::high_resolution_clock::now();
    f1 -= f2;
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "avx vector minus time: " << duration  << "ms" << endl;
    difference = 0;
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        if (abs(f1[i] - x3[i]) > difference)
            difference = abs(f1[i] - x3[i]);
    }
    cout << "max value diff is: " << difference << endl;

    //Element Multiply Speed:
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x3[i] *= x4[i];
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "normal vector multiply time: " << duration  << "ms" << endl;
    t1 = std::chrono::high_resolution_clock::now();
    f1 *= f2;
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "avx vector multiply time: " << duration  << "ms" << endl;
    difference = 0;
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        if (abs(f1[i] - x3[i]) > difference)
            difference = abs(f1[i] - x3[i]);
    }
    cout << "max value diff is: " << difference << endl;

    //Element Divide Speed:
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x3[i] /= x4[i];
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "normal vector divide time: " << duration  << "ms" << endl;
    t1 = std::chrono::high_resolution_clock::now();
    f1 /= f2;
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "avx vector divide time: " << duration  << "ms" << endl;
    difference = 0;
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        if (abs(f1[i] - x3[i]) > difference)
            difference = abs(f1[i] - x3[i]);
    }
    cout << "max value diff is: " << difference << endl;

    delete[] x1;
    delete[] x2;
}

