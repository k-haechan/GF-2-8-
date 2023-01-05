/*
GF�� ��Ŀ����Լ��� �����ϴ� ����
*/
#pragma once//include�� ���� �ι� include ���� �ʰڴٴ� ��
#include "GF_Calc.h"//������ GF����� �����̹Ƿ� GF������ �ʿ��ϴ�.
#include "GF_Mat(Data).h"


void GF_Mat_Print(GF_Matrix Mat);
GF_Matrix GF_Mat_Mul(GF_Matrix Mat1, GF_Matrix Mat2);
void GF_Mat_Scalar_Mul(GF_Matrix& A, byte scalar, int row);
void GF_Mat_RowSwap(GF_Matrix& Mat, int row1, int row2);
void GF_Mat_PivotUnity(GF_Matrix& A, int pivot);
void GF_Mat_RowAdd(GF_Matrix& Mat, byte scalar, int pivot_row, int target_row);
GF_Matrix GF_Mat_Inv(GF_Matrix Mat);