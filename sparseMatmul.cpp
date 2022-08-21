#pragma once
#include <vector>
#include <algorithm>
#include <queue>
#include "utils.cpp"
#include "CSR.cpp"
using namespace std;

void preZeroCount(vector<vector<double>> & mat, vector<vector<int>> & preSum, int rows, int cols)
{
    
    for(int row = 0; row < rows; row++)
    {
        double pre = mat[row][0];
        for(int col = 1; col < cols; col++)
        {
            preSum[row][col] = preSum[row][col - 1];
            if(pre == 0)
            {
                preSum[row][col] += 1; 
            }
            pre = mat[row][col];
        }
    }
}

void zeroElimination(vector<vector<double>> & mat, vector<vector<int>> & preSum, int rows, int cols)
{
    for(int row = 0; row < rows; row++)
    {
        for(int round = 1; round < cols; round *= 2)
        {
            // cout<<round<<endl;
            for(int col = round; col < cols; col++)
            {
                if(preSum[row][col] & 1 == 1)
                {
                    mat[row][col - round] = mat[row][col];
                    mat[row][col] = 0;
                    // cout<<"here"<<endl;
                }
                preSum[row][col] >>= 1;
            }
        }
    }
}

void condenseMatrix(vector<vector<double>> & mat, int rows, int cols)
{
    vector<vector<int>> preSum(rows, vector<int>(cols));
    preZeroCount(mat, preSum, rows, cols);
    zeroElimination(mat, preSum, rows, cols);
}


vector<vector<pair<pair<int, int>, double>>>  schedule(vector<vector<double>> &matA, vector<vector<double>> &matB, vector<vector<double>> &matC, int I, int J, int K, int schedulerPortNum)
{
    // showMat(matA, I, J);
    CSRMat<double> matACSR(matA);
    // matACSR.show();

    auto data = matACSR.getData();
    auto colIdx = matACSR.getColIdx();
    auto rowIdx = matACSR.getRowIdx();

    // for_each(colIdx.begin(), colIdx.end(), [](const auto & i){cout<<i<<" ";});

    int condensedCol = -1;

    for(int i = 1; i < rowIdx.size(); i++)
    {
        condensedCol = max(condensedCol, rowIdx[i] - rowIdx[i - 1]);
    }

    

    // cout<<initialfetchColNum<<endl;
    // cout<<condensedCol<<endl;
    // int schedulerPortNum = 1;

    vector<vector<pair<pair<int, int>, double>>> ports(condensedCol);



    for(int col = matA[0].size() - 1; col >= 1; ) // tranverse cols from tail to head
    {
        auto leftBorder = col - 1;
        
        for(int row = 1; row <= matA.size(); row++) // traverse each element in that row (rows)
        {
            auto rightBorder = min(col, rowIdx[row] - rowIdx[row - 1]);
            // cout<<"leftBorder"<<leftBorder<<"rightBorder"<<rightBorder<<endl;
            for(int idx = leftBorder + rowIdx[row - 1]; idx < rightBorder + rowIdx[row - 1]; idx++)
            {
                // cout<<idx<< " "<< data[idx]<< endl;
                auto val = data[idx];
                auto realCol = colIdx[idx];
                // cout<<val<< " "<< realCol<< endl;
                ports[idx - rowIdx[row - 1]].push_back({{row - 1, realCol}, val});
            }
            // cout<<endl;
           
        }
        // cout<<endl;
        col = leftBorder;
    }

    return ports;
}

vector<CSRMat<double>> partialMatrix(vector<vector<pair<pair<int, int>, double>>> & ports, vector<vector<double>> &matB, int I, int J, int K)
{
    // showMat(matB, J, K);
    CSRMat<double> matBCSR(matB);
    // matBCSR.show();

    auto data = matBCSR.getData();
    auto colIdx = matBCSR.getColIdx();
    auto rowIdx = matBCSR.getRowIdx();

    vector<vector<vector<double>>> partialMatrixs;
    vector<CSRMat<double>> partialMatrixsCSR;

    for(int denseCols = 0; denseCols < ports.size(); denseCols++)
    {
        vector<vector<double>> partial(I, vector<double>(K));
        CSRMat<double> partialCSR(I);


        for(auto ele : ports[denseCols])
        {
            // auto preFetchedRow = matB[ele.first.second];
            auto row = ele.first.first;
            auto realCol = ele.first.second;
            auto leftdata = ele.second;
            auto left = rowIdx[realCol];
            auto right = rowIdx[realCol + 1];
            // cout<<left<<" "<<right<<endl;

            // cout<<"leftdata "<<leftdata<<"realCol "<<realCol<<endl;
            // cout<<"rightdata ";
            for(auto idx = left; idx < right; idx++)
            {
                
                auto rightdata = data[idx];
                // cout<<rightdata<<" ";
                auto col = colIdx[idx];
                partial[row][col] = leftdata * rightdata;

                partialCSR.insert(row, col, leftdata * rightdata);
            }
            // cout<<endl;

        }
        partialMatrixs.push_back(partial);
        partialMatrixsCSR.push_back(partialCSR);

    }
    // return partialMatrixs;
    return partialMatrixsCSR;

    
    // cout<<"here"<<endl;
}


CSRMat<double> mergePartialMat(vector<pair<pair<int, int>, CSRMat<double>>> & partialMatrixs)
{
    // cout<<"here"<<endl;
    auto cmp = [](auto & A, auto & B)->bool{return A.first.first > B.first.first ||  A.first.first == B.first.first &&  A.first.second > B.first.second;};
    priority_queue<pair<pair<int, int>, double>, vector<pair<pair<int, int>, double>>, decltype(cmp)> pq(cmp);

    for(auto i = 0 ; i < partialMatrixs.size(); i++)
    {
        // partialMatrixs[i].second.show();
        auto data = partialMatrixs[i].second.getData();
        auto colIdx = partialMatrixs[i].second.getColIdx();
        auto rowIdx = partialMatrixs[i].second.getRowIdx();

        auto border = rowIdx[1];
        int row = 0;
        for(int j = 0; j < data.size(); j++)
        {
            // cout<<row<<" "<<colIdx[j]<<endl;
            
            if(j >= border)
            {
                row++;
                border = rowIdx[row + 1];
            }
            pq.push({{row, colIdx[j]}, data[j]});
        }
        // pq.push()
    }

    auto rows = partialMatrixs[0].second.getRowIdx().size();

    CSRMat<double> mergetCSR(rows);

    pair<int, int> prev  = pq.top().first;
    
    double sum = pq.top().second;
    pq.pop();

    while(!pq.empty())
    {
        auto ele = pq.top();
        if(ele.first.first == prev.first && ele.first.second == prev.second)
        {
            sum += ele.second;
        }
        else
        {
            // cout<<sum<<" ";
            mergetCSR.insert(prev.first, prev.second, sum);
            prev = ele.first;
            sum = ele.second;
        }
        pq.pop();
    }

    // mergetCSR.show();
    return mergetCSR;
    // cout<<"hahahahahhha"<<endl;
}


CSRMat<double> huffmanScheduler(vector<vector<pair<pair<int, int>, double>>> & ports, vector<CSRMat<double>> & partialMatrixs, int initialfetchColNum, int schedulerPortNum)
{
    auto cmp = [](auto & A, auto & B)->bool{return A.first.first > B.first.first ||  A.first.first == B.first.first &&  A.first.second > B.first.second;};
    priority_queue<pair<pair<int, int>, CSRMat<double>>, vector<pair<pair<int, int>, CSRMat<double>>>, decltype(cmp)> pq(cmp);
    // pq.push({{10, 1}, partialMatrixs[0]});
    // pq.push({{2, 2}, partialMatrixs[0]});
    // pq.push({{2, 1}, partialMatrixs[0]});

    for(auto i = 0; i < ports.size(); i++)
    {
        // partialMatrixs[i].show();
        pq.push({{ports[i].size(),1}, partialMatrixs[i]});
    }

    // cout<<initialfetchColNum<< " "<< schedulerPortNum<<endl;
    bool firstRound = true;

    while(pq.size() > 1)
    {
        
        int cnt = 0;
        vector<pair<pair<int, int>, CSRMat<double>>> prepare;
        while(cnt < schedulerPortNum)
        {
            auto ele = pq.top();
            cnt++;
            prepare.push_back({{ele.first.first, ele.first.second},ele.second});
            pq.pop();
            // cout<<ele.first.second<<endl;
            // cout<<pq.size()<<endl;
           
            if(firstRound && cnt == initialfetchColNum)
            {
                // cout<<"break"<<endl;
                firstRound = false;
                break;
            }
        }
        // cout<<"here";

        // cout<<cnt;
        
        int workLoad = 0;
        int layer = -1;
        for(int i = 0; i < prepare.size(); i++)
        {
            workLoad += prepare[i].first.first;
            layer = max(layer, prepare[i].first.second);
        }

        auto newPartialMat = mergePartialMat(prepare);

        // newPartialMat.show();

        pq.push({{workLoad, layer}, newPartialMat});
            // cout<<pq.size()<<endl;

        // break;
    }


    auto remain = pq.top();
    auto csrMat = remain.second;
    return csrMat;
    // cout<<"here"<<endl;

    // cout<<pq.top().first.first<<endl;
    // cout<<pq.top().first.second<<endl;

}


void sparseMatmul(vector<vector<double>> &matA, vector<vector<double>> &matB, vector<vector<double>> &matC, int I, int J, int K, int schedulerPortNum)
{

    auto ports = schedule(matA, matB, matC, I, J, K, schedulerPortNum);

    auto partialMatrixs = partialMatrix(ports, matB, I, J, K);

    CSRMat<double> matACSR(matA);
    // matACSR.show();

    auto data = matACSR.getData();
    auto colIdx = matACSR.getColIdx();
    auto rowIdx = matACSR.getRowIdx();

    // for_each(colIdx.begin(), colIdx.end(), [](const auto & i){cout<<i<<" ";});

    int condensedCol = -1;

    for(int i = 1; i < rowIdx.size(); i++)
    {
        condensedCol = max(condensedCol, rowIdx[i] - rowIdx[i - 1]);
    }

    int initialfetchColNum = (condensedCol - 2) % (schedulerPortNum - 1) + 2;

    auto finalCSRMAT = huffmanScheduler(ports, partialMatrixs, initialfetchColNum, schedulerPortNum);
    matC = finalCSRMAT.restore(I, K);
    // finalCSRMAT.show();
    // cout<<matC.size()<<endl;
    // showMat(matC, I, K);

}