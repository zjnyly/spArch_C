#pragma once
#include <vector>
// #include "utils.cpp"

using namespace std;

template <class T>
class CSRMat
{
public:
    CSRMat(int cols)
    {
        rowIdx.resize(cols+ 1);
        rowIdx[0] = 0;
    };

    vector<vector<double>> restore(int rows, int cols)
    {
        vector<vector<double>> restoredMat(rows, vector<double>(cols));
  

        auto border = rowIdx[1];
        int row = 0;
        for(auto i = 0; i < dataSequence.size(); i++)
        {
            if(i >= border)
            {
                row++;
                border = rowIdx[row + 1];
            }
            restoredMat[row][colIdx[i]] = dataSequence[i];
        }

        // showMat(restoredMat, rows, cols);
        return restoredMat;
    };

    void insert(int row, int col, double data)
    {

        // rowIdx[row + 1] ++;
        for(int i = row + 1; i < rowIdx.size(); i++)
        {
            rowIdx[i]++;
        }
        dataSequence.push_back(data);
        colIdx.push_back(col);
    }

    CSRMat(vector<vector<T>> & data)
    {
        rowIdx.resize(data.size() + 1);
        rowIdx[0] = 0;
        for(int i = 0; i < data.size(); i++) // row
        {
            for(int j = 0; j < data[0].size(); j++) // col
            {
               
                if(data[i][j] != 0)
                {
                    dataSequence.push_back(data[i][j]);
                    colIdx.push_back(j);
                    rowIdx[i + 1]++;
                }
            }
        }
        
        // rowIdxEnd = rowIdx;

        
        for(int i = 2; i <= data.size(); i++)
        {
            rowIdx[i] += rowIdx[i - 1];
        }
        // cout<<"hi"<<endl;
        
    };

    void show()
    {
        cout<<"data>>>>"<<endl;
        for(int i = 0; i < dataSequence.size(); i++)
        {
            cout<<dataSequence[i]<<" ";
        }
        cout<<endl;
        cout<<"colIdx>>>>"<<endl;
        for(int i = 0; i < colIdx.size(); i++)
        {
            cout<<colIdx[i]<<" ";
        }
        cout<<endl;
        cout<<"rowIdx>>>>"<<endl;
        for(int i = 0; i < rowIdx.size(); i++)
        {
            cout<<rowIdx[i]<<" ";
        }
        cout<<endl;
    }

    // int getRowIdxEnd(int row)
    // {
    //     return rowIdxEnd[row];
    // }

    // int getRowIdx(int row)
    // {
    //     return rowIdxEnd[row];
    // }

    // void updateRowIdxEnd(int row)
    // {
    //     rowIdxEnd[row] -= 1;
    // }

    auto getData()
    {
        return dataSequence;
    }

    auto getColIdx()
    {
        return colIdx;
    }

    auto getRowIdx()
    {
        return rowIdx;
    }

    

private:
    vector<T> dataSequence;
    vector<int> colIdx;
    vector<int> rowIdx;
};