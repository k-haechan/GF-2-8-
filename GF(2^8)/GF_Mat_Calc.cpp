/*
GF에서 행렬연산함수를 모아놓은 파일(행렬 출력, 행렬 곱하기, 행의 상수배, 행의 교환, 역행렬구하는 파일
*/
#include <iostream>
#include "GF_Mat(Calc).h"

void GF_Mat_Print(GF_Matrix Mat) {//GF_행렬출력
	for (int i = 0; i < Mat.row; i++) {
		std::cout << "[ ";
		for (int j = 0; j < Mat.col; j++) {
			printf("%02x ", Mat.M[i][j]);
		}std::cout << "]" << std::endl;
	}
	printf("\n");

}

GF_Matrix GF_Mat_Mul(GF_Matrix Mat1, GF_Matrix Mat2) {//GF_행렬곱
	if (Mat1.col != Mat2.row) {
		printf("행렬곱이 정의되지 않습니다.\n");
		return Mat1;//의미없는 반환
	}

	GF_Matrix Mul;
	Mul.row = Mat1.row;
	Mul.col = Mat2.col;

	for (int i = 0; i < Mat1.col; i++)
		for (int j = 0; j < Mat2.row; j++) {
			Mul.M[i][j] = 0x00;
			for (int k = 0; k < Mat1.col; k++)
				Mul.M[i][j] ^= GF_Mul(Mat1.M[i][k], Mat2.M[k][j]);
		}
	return Mul;
}

void GF_Mat_Scalar_Mul(GF_Matrix& A, byte scalar, int row) {//GF_행렬에서 행에 상수배하기	
	for (int i = 0; i < A.col; i++)
		A.M[row][i] ^= GF_Mul(scalar, A.M[row][i]);
}
void GF_Mat_RowSwap(GF_Matrix& Mat, int row1, int row2) {//GF_행렬에서 행교환

	//그냥 Mat[row1]<->Mat[row2]는 안되나? 어차피 포인터 변수일텐데-해봤는데 에러뜸 c++은 다른듯
	byte temp;
	
	for (int i = 0; i < Mat.col; i++)
	{
		temp = Mat.M[row1][i];
		Mat.M[row1][i] = Mat.M[row2][i];
		Mat.M[row2][i] = temp;
	}
}

void GF_Mat_PivotUnity(GF_Matrix& A, int pivot)//pivot행의 pivot의 크기를 1로 만들어주는 함수
{
	byte a = A.M[pivot][pivot];
	a = GF_Inv(a);
	for (int i = 0; i < A.col; i++)
		if (A.M[pivot][i] != 0)
			A.M[pivot][i] = GF_Mul(A.M[pivot][i], a);
}

void GF_Mat_RowAdd(GF_Matrix& Mat, byte scalar, int pivot_row, int target_row) {//상수배해서 더하기
	for (int i = 0; i < Mat.col; i++)
		Mat.M[target_row][i] ^= GF_Mul(scalar, Mat.M[pivot_row][i]);//pivot row의 scalar배 해서 target row에 더한다.
}

GF_Matrix GF_Mat_Inv(GF_Matrix Mat) {
	if (Mat.col != Mat.row)
	{
		printf("역행렬이 존재하지 않습니다.\n");
		return Mat;
	}

	GF_Matrix AugMat;//첨가행렬
	AugMat.row = Mat.row;
	AugMat.col = Mat.col * 2;

	for (int i = 0; i < Mat.row; i++) //첨가행렬 생성
		for (int j = 0; j < Mat.col; j++) {
			AugMat.M[i][j] = Mat.M[i][j];
			AugMat.M[i][j + Mat.col] = (i == j) ? 0x01 : 0x00;
		}
	
	for (int i = 0; i < Mat.col; i++) {
		int pivot_row = -1;

		for (int j = i; j < Mat.row; j++) {//i번째 열에서 0이 아닌 값을 가지는 원속 속한 행을 찾고 그 원소를 pivot으로 설정한다.
			if (AugMat.M[j][i] != 0) {
				pivot_row = j;
				break;
			}
		}
		if (pivot_row == -1) { // pivot이 존재하지 않는 열이 생기면 역원이 존재하지 않는다.
			printf("역행렬이 존재하지않습니다.\n");
			return Mat;
		}

		if (pivot_row != i)//M[i][i]이면 위치를 바꿔줄 필요가 없다(기약행사다리꼴 모양)
			GF_Mat_RowSwap(AugMat, pivot_row, i);

		GF_Mat_PivotUnity(AugMat, pivot_row);//피봇의 크기를 1로 바꾼다.-해당 행에 역원배 한것을 곱한다

		for (int k = 0; k < Mat.row; k++)
			if (k != pivot_row && AugMat.M[k][i] != 0)//피봇열 중 피봇과 0을 제외하고
				GF_Mat_RowAdd(AugMat, (AugMat.M[k][i]), pivot_row, k);//피봇열의 나머지 값들을 0으로 만들어준다.
	}
	GF_Matrix Inv_Mat;//역행렬
	Inv_Mat.row = Mat.row;
	Inv_Mat.col = Mat.col;
	for (int i = 0; i < Inv_Mat.row; i++)//첨가행렬에서 역행렬 복사
		for (int j = 0; j < Inv_Mat.col; j++)
			Inv_Mat.M[i][j] = AugMat.M[i][j + Mat.col];

	return Inv_Mat;
}
