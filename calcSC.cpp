// Code by Wassim Sameh Makram Fahim 2001194
// Began on 21:15 - 5/10/22 - Finished on 4:40 - 5/13/22.

/*
 *
 Comment 1:
 All the functions has a parallel value, as a return value that can be used for extended tasks, e.g.: A Complete Linear
 Algebra Calculator that works with the results of these functions.
 Yet these uses are not in the scope of this project (Except for the Division Functions), thus rendered useless.
 For the scope of this project, please consider all functions as void functions that already display results.

 Comment 2:
 This project could've been done using OOP, but I intended not to use anything beyond the course content.

 Comment 3:
 Passed Tests:
 A -> Accepted
 B -> Accepted
 C -> Accepted
 D -> Accepted
 E -> Accepted
 F -> Accepted
 G -> Accepted
 H -> Accepted
 I -> Accepted

 Comment 4:
 Report 1:
 It's 3:45 - 5/11/22, I've submitted 6 out of the 9, and with 5 of them accepted, I believe I'm onto a good start.
 What's left is to debug the Determinant function and to try some more test cases with it.
 Also, I need to work on the Inverting Algorithm for the Division Function and the documentation of existing functions.
 Report is due on 6/4/22, so I think I've got enough time.
 Report 2:
 Worked on the Division functions. I feel tired.
 Report 3:
 It's 6:00 - 13/5/22, I've finished cleaning, and documentation the code, I've submitted (and passed) all test cases, 
 and all what's left to do is to write my report and to upload the final version of the code. That's been one tough yet 
 short journey. That is my final entry.
 *
 */


#include <bits/stdc++.h>
using namespace std;



//long double Det;
const double EPS = 1E-9;

/*
vector<vector<double>> sum;
vector<vector<double>> dif;
vector<vector<double>> pro;
vector<vector<double>> trn;
vector<vector<double>> inv;
vector<vector<double>> adj;
vector<vector<double>> cof;
vector<vector<double>> dvd;
 */

// Function to Display Matrix Values:
void Display(const vector<vector<double>>& Matrix){
    for(auto & i : Matrix){
        for(double Element : i){
            if(Element<0){
                Element -= 0.5;
            }
            else{
                Element += 0.5;
            }
            cout<<int(Element)<<" ";
        }
        cout<<"\n";
    }
}// Working Properly



// Round Function:
int Round(double x){
    if(x>=0)
        return int(x+0.5);
    else
        return int(x-0.5);
}// Working Properly



// Start of Basic Functions:
/*
 * Addition and Subtraction of matrices of the same size is defined as the Addition or Subtraction of all
 * parallel elements in the matrices.
 */

// Addition Function:
vector<vector<double>> Addition(vector<vector<double>>& A, vector<vector<double>>& B){
    int Arows = A.size(), Acols = A[0].size();
    vector<vector<double>> res (A.size());
    for(int i = 0; i < Arows; i++) // Iterator i to pass on each row.
        for(int j = 0; j < Acols; j++) // Iterator j to pass on each element in a row.
            res[i].push_back( A[i][j] + B[i][j] ); // Each entry in the sum matrix is the summation of all parallel elements in matrices A and B.
//    sum = res;
    return res;
}// Working Properly

// Subtraction Function:
vector<vector<double>> Subtraction(vector<vector<double>>& A, vector<vector<double>>& B){
    int Arows = A.size(), Acols = A[0].size();
    vector<vector<double>> res (A.size());
    for(int i = 0; i < Arows; i++) // Iterator i to pass on each row.
        for(int j = 0; j < Acols; j++) // Iterator j to pass on each element in a row.
            res[i].push_back( A[i][j] - B[i][j] ); // Each entry in the sum matrix is the difference of all parallel elements in matrices A and B.
//    dif = res;
    return res;
}// Working Properly

// End of Basic Functions.



// Start of Multiplication Functions:
/*
 * The basic idea of matrix multiplication is that if we have two matrices A(m×n) and B(x×y) and n=x,
 * and multiply them by each other, we get a resultant matrix R(m×y) in which each entry R(i,j) is equal
 * to the dot product of the row vector i in A and the column vector j in B.
 *
 * A row vector can easily be represented as A[i], yet you can't get a column vector by B[][J], so I implemented a
 * solution.
 */

// Function to get a Column Vector in a matrix:
vector<double> getColumnVector(vector<vector<double>> Matrix, int j){
    //unsigned long long n = Matrix[0].size();
    vector<double> res;
    /*
    if(j>n){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
     */
    for(vector<double> Row : Matrix){
        res.push_back(Row[j]);  // We take the j-th element of each row of the matrix so that we get the j-th column.
    }
    return res;
}// Working Properly

// Function to get the Dot Product between two Vectors:
/*
 * The Dot Product of two vectors is defined as the summation of multiplications of all parallel elements in the two vectors.
 */
double dotProductVect(vector<double>& A, vector<double>& B){
    unsigned long long a = A.size();
    //b = B.size();
    double res = 0;
    /*
    if(a!=b){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
     */
    for(int i=0; i<a; i++)
        res += A[i] * B[i]; // the result is the summation of multiplications of all parallel elements in the two vectors.
    return res;
}// Working Properly

// Function to get the multiplications of the two matrices:
vector<vector<double>> crossProductMat(vector<vector<double>>& A, vector<vector<double>>& B){
    int Arows = A.size(), Bcols = B[0].size();
    vector<vector<double>> res (Arows);
    for(int i=0; i<Arows; i++){
        for(int j=0; j<Bcols; j++){
            vector<double> temp = getColumnVector(B, j);
            res[i].push_back(dotProductVect(A[i], temp)); // From the definition of matrix multiplications in lines 106-108
        }
    }
//    pro = res;
    return res;
}// Working Properly

// End of Multiplication Functions.



// Start of Determinant Function:

double Determinant(vector<vector<double>>& A){
    long double det = 1;
    int n = A.size();
    vector<vector<double>> B(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            B[i].push_back(A[i][j]);
        }
    }
    for (int i=0; i<n; ++i) {
        int k = i;
        for (int j=i+1; j<n; ++j) {
            if (abs(B[j][i]) > abs(B[k][i]))
                k = j;
        }
        if (abs (B[k][i]) < EPS) {
            det = 0;
            break;
        }
        swap (B[i], B[k]);
        if (i != k)
            det = -det;
        det *= B[i][i];
        for (int j=i+1; j<n; ++j) {
            B[i][j] /= B[i][i];
        }
        for (int j=0; j<n; ++j) {
            if (j != i && abs(B[j][i]) > EPS) {
                for (k = i + 1; k < n; ++k) {
                    B[j][k] -= B[i][k] * B[j][i];
                }
            }
        }
    }
//    Det = det;
    return det;
}// Working Properly

// End of Determinant Function.



// Start of Division Functions.
/*
 * If we have two matrices A(m×n) and B(x×y) with B being a square matrix and n=x=y=z, the division of the two matrices
 * will result in a matrix R(m×z) which is the result of the product of matrix A and the Multiplicative Inverse of
 * matrix B: B^-1.
 *
 * The Multiplicative Inverse of a Matrix A(m) is a Matrix A^-1(m), with which if Matrix A is multiplied it results
 * int the Identity Matrix I(m). The Multiplicative Inverse of a Matrix A can be obtained by dividing each element of
 * the Adjoint Matrix of A by the Determinant of A. There is no Multiplicative Inverse for Matrices with Zero.
 * Determinants.
 *
 * The Adjoint Matrix of Matrix A is the Transpose of the Cofactor Matrix of Matrix A.
 *
 * The Cofactor Matrix of Matrix A(m×n) is defined as a matrix C(m×n) in which, every entry C(i,j) is equal to the minor.
 * of A(i,j) multiplied by (-1)^(i+j)
 *
 * The Minor of any Entry A(i,j) in a matrix A is equal to the determinant of the Minor Matrix of Entry A(i,j).
 *
 * The Minor Matrix of any Entry A(i,j) in Matrix A, is the Matrix A excluding row i and column j.
 *
 * The Transpose of Matrix A, A^T, can be obtained by swapping elements diagonally on the matrix.
 * i.e. A[i][j], A[j][i] = A[j][i], A[i][j].
 */

// Function to get the Minor Matrix of entry A(x,y) in Matrix A: 
vector<vector<double>> minorMat(vector<vector<double>>& A, int x, int y){
    int n = A.size();
    int m = A[0].size();
    vector<vector<double>> res(n-1);
    for (int i = 0; i < n; ++i) {
        for(int j = 0; j<m; ++j){
            //The Minor Mat of any Entry A(x,y) in Mat A, is Mat A excluding row x and column y.
            if(i!=x&&j!=y){
                if(i<x)
                    res[i].push_back(A[i][j]);
                else
                    res[i-1].push_back(A[i][j]);
            }
        }
    }
    return res;
}// Working Properly

// Function to get the Minor of entry A(x,y) in Matrix A: 
double Minor(vector<vector<double>>& A, int x, int y){
    vector<vector<double>> B = minorMat(A, x, y);
    //The Minor of any Entry A(x,y) in a Mat A is equal to the determinant of the Minor Mat of Entry A(x,y).
    return Determinant(B);
}// Working Properly

// Function to get the Cofactor Matrix of Matrix A:
vector<vector<double>> Cofactor(vector<vector<double>>& A){
    int n = A.size(); int m = A[0].size();
    vector<vector<double>> res(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            // The Cofactor Mat C in which, every entry C(i,j) is equal to the minor of A(i,j) multiplied by (-1)^(i+j)
            res[i].push_back(Minor(A, i, j)*pow(-1, i+j));
        }
    }
//    cof = res;
    return res;
}// Working Properly

// Function to get the Transpose of a Matrix:
vector<vector<double>> Transpose(vector<vector<double>>& A){
    int n = A.size();
    vector<vector<double>> B(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            B[i].push_back(A[j][i]); // Swapping Elements of the Matrix Diagonally, A[i][j], A[j][i] = A[j][i], A[i][j].
        }
    }
//    trn = B;
    return B;
}// Working Properly

// Function to get the Adjoint Matrix of Matrix A:
vector<vector<double>> Adjoint(vector<vector<double>>& A){
    vector<vector<double>> B = Cofactor(A);
    vector<vector<double>> C = Transpose(B);
    // The Adjoint Matrix of Matrix A is the Transpose of the Cofactor Matrix of Matrix A.
//    adj = C;
    return C;
}// Working Properly

// Function to get the Multiplicative Inverse of Matrix A:
vector<vector<double>> Inverse(vector<vector<double>>& A){
    vector<vector<double>> res = Adjoint(A);
    double f = 1.0/(1.0*Determinant(A));
    for(int i=0; i<res.size(); i++){
        for(int j=0; j<res[0].size(); j++){
            // The Multiplicative Inverse of a Matrix A can be obtained by dividing each element of the 
            // Adjoint Matrix of A by the Determinant of A.
            res[i][j] *= f;
        }
    }
//    inv = res;
    return res;
}// Working Properly

// Function to Divide Matrix A by Matrix B, i.e. Multiply Matrix A by the Multiplicative Inverse of Matrix B:
vector<vector<double>> Division(vector<vector<double>>& A, vector<vector<double>>& B){
    vector<vector<double>> C = Inverse(B);
    // The Division of Mat A by Mat B is the result of the product of Mat A and the Inverse of Mat B: B^-1.
//    dvd = crossProductMat(A, C);
    return crossProductMat(A, C);
}// Working Properly

// End of Division Functions.



int main() {

    ios_base::sync_with_stdio(false);

    //Begin Code:

    // Dimensions for Matrix A:

    int m, n;
    cout<<"Please enter dimensions of Matrix A:"<<endl;
    cin>>m>>n;

    // Dimensions for Matrix B:

    int x, y;
    cout<<"Please enter dimensions of Matrix B:"<<endl;
    cin>>x>>y;

    // Initializing the Matrices:

    vector<vector<double>> A(m), B(x);

    // Entering Values for Matrix A:

    cout<<"Please enter values of Matrix A:"<<endl;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            double a; cin>>a;
            A[i].push_back(a);
        }
    }

    // Entering Values for Matrix B:

    cout<<"Please enter values of Matrix B:"<<endl;
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            double b; cin>>b;
            B[i].push_back(b);
        }
    }

    int t=0;
    while(t!=7){
        cout<<"Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):"<<endl;
        cin>>t;
        switch (t) {
            case 1:
                if(m==x&&n==y)
                    Display(Addition(A, B));
                else
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                break;
            case 2:
                if(m==x&&n==y)
                    Display(Subtraction(A, B));
                else
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                break;
            case 3:
                if(n==x)
                    Display(crossProductMat(A, B));
                else
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                break;
            case 4:
                if((x==y)&&(n==x)&&(Round(Determinant(B))!=0))
                    Display(Division(A, B));
                else
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                break;
            case 5:
                if(m==n)
                    cout<<Round(Determinant(A))<<endl;
                else
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                break;
            case 6:
                if(x==y)
                    cout<<Round(Determinant(B))<<endl;
                else
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                break;
            case 7:
                break;
            default:
                break;
        }

    }
    cout<<"Thank you!"<<endl;

    return 0;
}
