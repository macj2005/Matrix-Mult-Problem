// Author: Mac Johnson
// Assignment Title: Program 4
// Assignment Description: solves the Matrix Multiplication problem
// Date Created: 02/16/2025
// Due Date: 02/14/2025
// Date Last Modified: 02/14/2025

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    
    vector<vector<int>> data;
    
public:
    Matrix(int r, int c): rows(r), cols(c) {
        data.resize(r);
        for (int i = 0; i < r; i++) {
            data[i].resize(c);
            for (int j = 0; j < c; j++) {
                data[i][j] = 0;
            }
        }
    }
    
    int getRows() const {
        return rows;
    }
    int getCols() const {
        return cols;
    }
    
    void setRows(int r) {
        rows = r;
    }
    void setCols(int c) {
        cols = c;
    }
    
    int get(int r, int c) const {
        return data[r][c];
    }
    
    void set(int r, int c, int v) {
        data[r][c] = v;
    }
    
    void print(int l, int h) {
        for (int i = l; i < h; i++) {
            cout << "[";
            for (int j = l; j < h; j++) {
                cout << right << setw(4) << data[i][j];
                if (j != h - 1) {
                    cout << " ,";
                }
            }
            cout << "]" << endl;
        }
    }
};

void matrixChainOrder(vector<int>& p, Matrix& m, Matrix& s, int n) {
    for (int i = 1; i < n + 1; i++) {
        m.set(i, i, 0);
    }
    
    for (int l = 2; l < n + 1; l++) {
        for (int i = 1; i < n - l + 2; i++) {
            int j = i + l - 1;
            m.set(i, j, -1);
            
            for (int k = i; k < j; k++) {
                int q = m.get(i, k) + m.get(k + 1, j) + p[i - 1] * p[k] * p[j];
                if (q < m.get(i, j) or m.get(i, j) == -1) {
                    m.set(i, j, q);
                    s.set(i, j, k);
                }
            }
        }
    }
}

void printSolution(Matrix s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        printSolution(s, i, s.get(i, j));
        printSolution(s, s.get(i, j) + 1, j);
        cout << ")";
    }
}

int main(int argc, const char * argv[]) {
    int n;
    vector<Matrix> matrixList;
    vector<int> p;
    //ifstream inputFile;
    
    //inputFile.open("data.txt");
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c;
        matrixList.push_back(Matrix(r, c));
    }
    //inputFile.close();
    
    p.push_back(matrixList[0].getRows());
    for (unsigned int i = 0; i < matrixList.size(); i++) {
        p.push_back(matrixList[i].getCols());
    }
    
    cout << "M" << endl;
    cout << "[";
    for (unsigned int i = 0; i < p.size(); i++) {
        cout << p[i];
        if (i != p.size() - 1) {
            cout << " , ";
        }
    }
    cout << "]" << endl << endl;
    
    Matrix m(n + 1, n + 1);
    Matrix s(n + 1, n + 1);
    
    matrixChainOrder(p, m, s, n);
    
    cout << "C(i, j)" << endl;
    m.print(1, n + 1);
    cout << endl;
    
    cout << "S" << endl;
    for (int i = 1; i < n; i++) {
        cout << "[";
        for (int j = 2; j < n + 1; j++) {
            cout << right << setw(4) << s.get(i, j);
            if (j != n) {
                cout << " ,";
            }
        }
        cout << "]" << endl;
    }
    cout << endl;
    
    cout << "Total Multiplications = " << m.get(1, n) << endl << endl;
    
    
    printSolution(s, 1, n);
    cout << endl;
    
    
    
    return 0;
}
