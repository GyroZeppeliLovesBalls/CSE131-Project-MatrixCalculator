// Code by Wassim Sameh Makram Fahim 2001194
// Began on 21:15 - 5/10/22

#include <bits/stdc++.h>
using namespace std;

/*
 *
 Comment 1:
 All the functions contain a data type, as the return value can be used for extended tasks.
 Yet these uses are not in the scope of this project, thus rendered useless.
 For the scope of this project, please consider all functions as void functions, as they already display results.

 Comment 2:
 This project could've been done using OOP, but I intended not to use anything beyond the course content.

 Comment 3:
 Passed Tests:
 A -> Accepted
 B -> Accepted
 C -> Accepted
 D -> Accepted
 E -> Wrong Answer on test 3
 F -> Accepted
 G -> Pending
 H -> Pending
 I -> Pending

 Comment 4:
 Report 1:
 It's 3:45 - 5/11/22, I've submitted 6 out of the 9, and with 5 of them accepted, I believe I'm onto a good start.
 What's left is to debug the Determinant function and to try some more test cases with it.
 Also, I need to work on the Inverting Algorithm for the Division Function and the documentation of existing functions.
 Report is due on 6/4/22, so I think I've got enough time. 
 *
 */

double Det;

/*

// Functions for Testing:

void Display(const vector<vector<double>>& Matrix){
    for(auto & i : Matrix){
        for(double Element : i){
            cout<<Element<<" ";
        }
        cout<<"\n";
    }
}// Working Properly, Overloaded, Just for Testing

void Display(const vector<int>& Matrix){
    for(auto & Element : Matrix){
        cout<<Element<<" ";
    }
}// Working Properly, Overloaded, Just for Testing

*/

void Display(const vector<vector<int>>& Matrix){
    for(auto & i : Matrix){
        for(int Element : i){
            cout<<Element<<" ";
        }
        cout<<"\n";
    }
}// Working Properly

vector<vector<int>> Addition(vector<vector<int>>& A, vector<vector<int>>& B, int Arows, int Acols, int Brows,int Bcols){
    vector<vector<int>> res (A.size());
    if((Arows!=Brows)||(Acols!=Bcols)){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(int i = 0; i < Arows; i++)
        for(int j = 0; j < Acols; j++)
            res[i].push_back( A[i][j] + B[i][j] );
    Display(res);
    return res;
}// Working Properly

vector<vector<int>> Subtraction(vector<vector<int>>& A, vector<vector<int>>& B, int Arows, int Acols, int Brows,int Bcols){
    vector<vector<int>> res (A.size());
    if((Arows!=Brows)||(Acols!=Bcols)){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(int i = 0; i < Arows; i++)
        for(int j = 0; j < Acols; j++)
            res[i].push_back( A[i][j] - B[i][j] );
    Display(res);
    return res;
}// Working Properly

int dotProductVect(vector<int>& A, vector<int>& B){
    unsigned long long a = A.size(), b = B.size();
    int res = 0;
    if(a!=b){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(int i=0; i<a; i++)
        res += A[i] * B[i];
    return res;
}// Working Properly

vector<int> getColumnVector(vector<vector<int>> Matrix, int Column){
    unsigned long long n = Matrix[0].size();
    vector<int> res;
    if(Column>n){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(vector<int> Row : Matrix){
        res.push_back(Row[Column]);
    }
    return res;
}// Working Properly

vector<vector<int>> crossProductMat(vector<vector<int>>& A, vector<vector<int>>& B, int Arows, int Acols, int Brows, int Bcols){
    vector<vector<int>> res (Arows);
    if(Acols!=Brows){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return res;
    }
    for(int i=0; i<Arows; i++){
        for(int j=0; j<Bcols; j++){
            vector<int> temp = getColumnVector(B, j);
            res[i].push_back(dotProductVect(A[i], temp));
        }
    }
    Display(res);
    return res;
}// Working Properly

void Determinant(vector<vector<int>>& A, int Arows, int Acols, int x){
    double det = 1;
    if(Arows!=Acols){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
        return;
    }
    int n = Arows;
    vector<vector<double>> B(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            B[i].push_back(A[i][j]);
        }
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            double a = B[i][i], b = B[j][i];
            double factor = (b*1.0)/(a*1.0);
            for(int k=0; k<n; k++){
                B[j][k] -= factor*(B[i][k]);
            }
        }
    }
    for(int i=0; i<n; i++){
        det *= B[i][i];
    }
    Det = det;
    if(x==1) {
        if (det == 0)
            cout << 0 << endl;
        else
            cout << det << endl;
    }
}// Working Properly

/*
vector<vector<double>> Inverse(vector<vector<int>>& A, int Arows, int Acols){
    Determinant(A, Arows, Acols, 0);
    if((Arows!=Acols)||Det==0){
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
    }
    int n = Arows;
    vector<vector<double>> B(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            B[i].push_back(A[i][j]);
        }
    }

}
*/

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

    vector<vector<int>> A(m), B(x);

    // Entering Values for Matrix A:

    cout<<"Please enter values of Matrix A:"<<endl;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            int a; cin>>a;
            A[i].push_back(a);
        }
    }

    // Entering Values for Matrix B:

    cout<<"Please enter values of Matrix B:"<<endl;
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            int b; cin>>b;
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
