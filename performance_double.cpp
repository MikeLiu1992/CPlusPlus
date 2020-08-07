#include <stdio.h>
#include <iostream>
#include <vector>
#include "quant_vec.h"
#include <stdlib.h>     /* srand, rand */
#include <chrono>

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
    double *x1 = new double[SAMPLE_SIZE];
    double *x2 = new double[SAMPLE_SIZE];
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x1[i] = fRand(1, 100000);
        x2[i] = fRand(1, 100000);
    }

    //Assignment Speed:
    vector<double> x3(SAMPLE_SIZE, 0);
    vector<double> x4(SAMPLE_SIZE, 0);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SAMPLE_SIZE; i ++)
    {
        x3[i] = x1[i]; 
        x4[i] = x2[i];
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "normal vector assignment time: " << duration << "ms" <<endl;
    quant_double f1(x3);
    quant_double f2(x4);
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

