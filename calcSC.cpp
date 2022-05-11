// Code by Wassim Sameh Makram Fahim 2001194
// Began on 21:15 - 5/10/22

/*
 *
 Comment 1:
 All the functions has a parallel value, as a return value that can be used for extended tasks, e.g.: A Complete Linear
 Algebra Calculator that works with the results of these functions.
 Yet these uses are not in the scope of this project (Except for the Division Function), thus rendered useless.
 For the scope of this project, please consider all functions as void functions, as they already display results.

 Comment 2:
 This project could've been done using OOP, but I intended not to use anything beyond the course content.

 Comment 3:
 Passed Tests:
 A -> Accepted
 B -> Accepted
 C -> Accepted
 D -> Accepted
 E -> Accepted (Using the Gauss-Jordan Elimination Algorithm, and not with the Echelon Form Algorithm)
 F -> Accepted
 G -> Accepted
 H -> Wrong answer on test 3
 I -> Accepted

 Comment 4:
 Report 1:
 It's 3:45 - 5/11/22, I've submitted 6 out of the 9, and with 5 of them accepted, I believe I'm onto a good start.
 What's left is to debug the Determinant function and to try some more test cases with it.
 Also, I need to work on the Inverting Algorithm for the Division Function and the documentation of existing functions.
 Report is due on 6/4/22, so I think I've got enough time.
 Report 2:
 Began on 19:30 - 5/11/22, Ended on.
 *
 */

#include <bits/stdc++.h>
using namespace std;



long double Det;
const double EPS = 1E-9;

vector<vector<double>> sum;
vector<vector<double>> dif;
vector<vector<double>> pro;
vector<vector<double>> trn;



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

void Addition(vector<vector<double>>& A, vector<vector<double>>& B, int Arows, int Acols, int Brows,int Bcols){
    vector<vector<double>> res (A.size());
    if((Arows!=Brows)||(Acols!=Bcols)){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return;
    }
    for(int i = 0; i < Arows; i++)
        for(int j = 0; j < Acols; j++)
            res[i].push_back( A[i][j] + B[i][j] );
    Display(res);
    sum = res;
    return;
}// Working Properly

void Subtraction(vector<vector<double>>& A, vector<vector<double>>& B, int Arows, int Acols, int Brows,int Bcols){
    vector<vector<double>> res (A.size());
    if((Arows!=Brows)||(Acols!=Bcols)){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return;
    }
    for(int i = 0; i < Arows; i++)
        for(int j = 0; j < Acols; j++)
            res[i].push_back( A[i][j] - B[i][j] );
    Display(res);
    dif = res;
    return;
}// Working Properly

double dotProductVect(vector<double>& A, vector<double>& B){
    unsigned long long a = A.size(), b = B.size();
    double res = 0;
    if(a!=b){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(int i=0; i<a; i++)
        res += A[i] * B[i];
    return res;
}// Working Properly

vector<double> getColumnVector(vector<vector<double>> Matrix, int Column){
    unsigned long long n = Matrix[0].size();
    vector<double> res;
    if(Column>n){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(vector<double> Row : Matrix){
        res.push_back(Row[Column]);
    }
    return res;
}// Working Properly

void crossProductMat(vector<vector<double>>& A, vector<vector<double>>& B, int Arows, int Acols, int Brows, int Bcols){
    vector<vector<double>> res (Arows);
    if(Acols!=Brows){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return;
    }
    for(int i=0; i<Arows; i++){
        for(int j=0; j<Bcols; j++){
            vector<double> temp = getColumnVector(B, j);
            res[i].push_back(dotProductVect(A[i], temp));
        }
    }
    Display(res);
    pro = res;
    return;
}// Working Properly

void Determinant(vector<vector<double>>& A, int Arows, int Acols, int x){
    long double det = 1;
    if(Arows!=Acols){
        if(x==1) {
            cout << "The operation you chose is invalid for the given matrices." << endl;
        }
        return;
    }
    int n = Arows;
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
    Det = det;
    if(x==1) {
        if (det == 0)
            cout << 0 << endl;
        else
            cout << det << endl;
    }
}// Working Properly

double determinantRet(vector<vector<double>>& A){
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
    return det;
}// Working Properly

vector<vector<double>> Transpose(vector<vector<double>>& A){
    int n = A.size();
    vector<vector<double>> B(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            B[i].push_back(A[j][i]);
        }
    }
    return B;
}// Working Properly

vector<vector<double>> minorMat(vector<vector<double>>& A, int x, int y){
    int n = A.size();
    int m = A[0].size();
    vector<vector<double>> res(n-1);
    for (int i = 0; i < n; ++i) {
        for(int j = 0; j<m; ++j){
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

double Minor(vector<vector<double>>& A, int x, int y){
    vector<vector<double>> B = minorMat(A, x, y);
    return determinantRet(B);
}// Working Properly

vector<vector<double>> Cofactor(vector<vector<double>>& A){
    int n = A.size(); int m = A[0].size();
    vector<vector<double>> res(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            res[i].push_back(Minor(A, i, j)*pow(-1, i+j));
        }
    }
    return res;
}// Working Properly

vector<vector<double>> Adjoint(vector<vector<double>>& A){
    vector<vector<double>> B = Cofactor(A);
    vector<vector<double>> C = Transpose(B);
    return C;
}// Working Properly

vector<vector<double>> Inverse(vector<vector<double>>& A){
    vector<vector<double>> res = Adjoint(A);
    double f = 1.0/(1.0*determinantRet(A));
    for(int i=0; i<res.size(); i++){
        for(int j=0; j<res[0].size(); j++){
            res[i][j] *= f;
        }
    }
    return res;
}// Working Properly

void Division(vector<vector<double>>& A, vector<vector<double>>& B){
    int n = determinantRet(B);
    if(n==0){
        cout << "The operation you chose is invalid for the given matrices." << endl;
        return;
    }
    vector<vector<double>> C = Inverse(B);
    crossProductMat(A, C, A.size(), A[0].size(), C.size(), C[0].size());
}// Working Properly

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
                Addition(A, B, m, n, x, y);
                break;
            case 2:
                Subtraction(A, B, m, n, x, y);
                break;
            case 3:
                crossProductMat(A, B, m, n, x, y);
                break;
            case 4:
                Division(A, B);
                break;
            case 5:
                Determinant(A, m, n, 1);
                break;
            case 6:
                Determinant(B, x, y, 1);
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
