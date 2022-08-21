#include <iostream>
#include <vector>
#include "innerProduct.cpp"
#include "outerProduct.cpp"
#include "sparseMatmul.cpp"
#include "utils.cpp"
#include "CSR.cpp"
#include "ctime"



using namespace std;

int main()
{
    const int I = 12, J = 12, K = 12;

    vector<vector<double>> matA(I, vector<double>(J));
    vector<vector<double>> matB(J, vector<double>(K));
    vector<vector<double>> matC(I, vector<double>(K));

    initMat(matA, I, J);
    initMat(matB, J, K);

    clock_t start, end;


    cout<<"inner product"<<endl;
    start=clock();
    innerProduct(matA, matB, matC, I, J, K);
    end=clock();	
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	cout<<"Total time:"<<endtime*1000<<"ms"<<endl;	
    showMat(matC, I, K);
    // outerProduct(matA, matB, matC, I, J, K);
    // showMat(matC, I, K);
    cout<<"sparse product"<<endl;
    start=clock();
    sparseMatmul(matA, matB, matC, I, J, K, 4);
    end=clock();	
	endtime=(double)(end-start)/CLOCKS_PER_SEC;
	cout<<"Total time:"<<endtime*1000<<"ms"<<endl;	
    
    showMat(matC, I, K);


    // showMat(matA, I, J);
    // showMat(matB, J, K);
    // showMat(matC, I, K);
}