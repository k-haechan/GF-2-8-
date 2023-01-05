#pragma once
#include <iostream>

using namespace std;

#define MAX 10
#define NEARLY_ZERO 1e-10

class CMat {
protected:
    double M[MAX][MAX];
    int row;
    int col;

    static int Counter;
public:
    CMat() { IncreaseCounter();  row = 1; col = 1; M[0][0] = 0.0; };
    CMat(int r, int c) { IncreaseCounter(); row = r; col = c; M[0][0] = 0.; };
    CMat(int r, int c, double data[MAX][MAX]);
    void Print(const char* pName = nullptr);
    void SetValue(int r, int c, double value) { M[r][c] = value; };
    double GetValue(int r, int c) { return M[r][c]; };
    void ScalarMul(double value);

    void SetSize(int r, int c) { row = r; col = c; };
    int GetRow() { return row; };
    int GetCol() { return col; };

    static int GetConter() { return Counter; };
    static void ResetCounter() { Counter = 0; };
    static void IncreaseCounter() { Counter++; };
    static CMat Mul(CMat A, CMat B);  // HW2
    static CMat Add(CMat A, CMat B);  // HW2

    // �Ʒ� �Լ��� CSQMat::Inv()���� �ӽ� ����� ����� ����ϴµ�
    // public �̶�� ȣ���� �� ����
    void Mat_Exchange_Row(int row1, int row2);
    void Mat_Scalar_Mul(double scalar, int row);
    void Mat_Row_Add(double scalar, int row_src, int row_target);
};



class CSQMat : public CMat {//�������
public:
    double Det();
    CSQMat() { row = 1; M[0][0] = 0.0; };
    CSQMat(int r) : CMat(r, r) {};
    CSQMat(CMat A);
    CSQMat Inv();
    double Tr(); // HW2 (�밢������ ��) 
    void SetSize(int n) { row = n; col = n; }; //overloading 
    int GetSize() { return row; };
};


