#pragma once
#include <vector>
#include "utils.cpp"
using namespace std;

void innerProduct(vector<vector<double>> & matA,  vector<vector<double>> & matB,  vector<vector<double>> & matC, int I, int J, int K)
{
    for(int i = 0; i < I; i++)
    {
        for(int k = 0; k < K; k++)
        {
            for(int j = 0; j < J; j++)
            {
                matC[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }
}