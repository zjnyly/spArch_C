#pragma once
#include <vector>
#include "utils.cpp"
using namespace std;

void outerProduct(vector<vector<double>> &matA, vector<vector<double>> &matB, vector<vector<double>> &matC, int I, int J, int K)
{

    for (int j = 0; j < J; j++)
    {
        for(int i = 0; i < I; i++)
        {
            for(int k = 0; k < K; k++)
            {
                matC[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }
}