#pragma once
#include <iostream>
#include <vector>
#include "CSR.cpp"

using namespace std;

void initMat(vector<vector<double>> & mat, int rows, int cols)
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if((row * cols + col) % 2 == 0)
            {
                mat[row][col] = 0;
            }
            else
            {
                mat[row][col] = row + 1;
            }
            
        }
    }
}

template<class T>
void showMat(vector<vector<T>> & mat, int rows, int cols)
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            cout<<mat[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}