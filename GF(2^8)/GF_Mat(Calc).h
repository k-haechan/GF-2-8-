/*
GF의 행렬연산함수를 정의하는 파일
*/
#pragma once//include한 것을 두번 include 하지 않겠다는 뜻
#include "GF_Calc.h"//어차피 GF행렬의 연산이므로 GF연산이 필요하다.
#include "GF_Mat(Data).h"


void GF_Mat_Print(GF_Matrix Mat);
GF_Matrix GF_Mat_Mul(GF_Matrix Mat1, GF_Matrix Mat2);
void GF_Mat_Scalar_Mul(GF_Matrix& A, byte scalar, int row);
void GF_Mat_RowSwap(GF_Matrix& Mat, int row1, int row2);
void GF_Mat_PivotUnity(GF_Matrix& A, int pivot);
void GF_Mat_RowAdd(GF_Matrix& Mat, byte scalar, int pivot_row, int target_row);
GF_Matrix GF_Mat_Inv(GF_Matrix Mat);