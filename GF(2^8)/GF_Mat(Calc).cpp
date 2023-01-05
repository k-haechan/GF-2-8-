#include "GF_Mat(Calc).h"

void Mat_Print(Matrix Mat) {
	for (int i = 0; i < Mat.row; i++) {
		std::cout << "[ ";
		for (int j = 0; j < Mat.col; j++) {
			printf("%02x ", Mat.M[i][j]);
		}std::cout << "]" << std::endl;
	}
	printf("\n");

}

Matrix GF_Mat_Mul(Matrix Mat1, Matrix Mat2) {
	if (Mat1.col != Mat2.row) {
		printf("행렬곱이 정의되지 않습니다.\n");
		return Mat1;
	}

	Matrix Mul;
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

void Mat_RowSwap(Matrix& Mat, int row1, int row2) {//그냥 Mat[row1]<->Mat[row2]는 안되나? 어차피 포인터 변수일텐데

	byte temp;
	for (int i = 0; i < Mat.col; i++)
	{
		temp = Mat.M[row1][i];
		Mat.M[row1][i] = Mat.M[row2][i];
		Mat.M[row2][i] = temp;
	}
}

void Mat_PivotUnity(Matrix& A, int pivot)//pivot의 크기를 1로 바꾸는 함수
{
	byte a = A.M[pivot][pivot];
	a = GF_Inv(a);
	for (int i = 0; i < A.col; i++)
		if (A.M[pivot][i] != 0)
			A.M[pivot][i] = GF_Mul(A.M[pivot][i], a);
}

void Mat_RowAdd(Matrix& Mat, int pivot_row, int target_row) {
	byte temp = Mat.M[target_row][pivot_row];
	for (int i = 0; i < Mat.col; i++)
		Mat.M[target_row][i] ^= GF_Mul(Mat.M[pivot_row][i], temp);
}

Matrix Mat_Inv(Matrix Mat) {
	if (Mat.col != Mat.row)
	{
		printf("역행렬이 존재하지 않습니다.\n");
		return Mat;
	}

	Matrix AugMat;
	AugMat.row = Mat.row;
	AugMat.col = Mat.col * 2;

	for (int i = 0; i < Mat.row; i++)
		for (int j = 0; j < Mat.col; j++) {
			AugMat.M[i][j] = Mat.M[i][j];
			AugMat.M[i][j + Mat.col] = (i == j);
		}
	Mat_Print(AugMat);
	//printf("%02x", GF_Mul(GF_inv(2), 3));
	for (int i = 0; i < Mat.col; i++) {
		int pivot_row = -1;

		for (int j = i; j < Mat.row; j++) {
			if (AugMat.M[j][i] != 0) {
				pivot_row = j;

				break;
			}
		}
		if (pivot_row == -1) {
			printf("역행렬이 존재하지않습니다.\n");
			return Mat;
		}

		if (pivot_row != i)
			Mat_RowSwap(AugMat, pivot_row, i);

		Mat_PivotUnity(AugMat, pivot_row);

		for (int k = 0; k < Mat.row; k++)
			if (k != pivot_row)
				Mat_RowAdd(AugMat, pivot_row, k);
		printf("\nstep%d\n", i + 1);
		Mat_Print(AugMat);


	}
	Matrix Inv_Mat;
	Inv_Mat.row = Mat.row;
	Inv_Mat.col = Mat.col;
	for (int i = 0; i < Inv_Mat.row; i++)
		for (int j = 0; j < Inv_Mat.col; j++)
			Inv_Mat.M[i][j] = AugMat.M[i][j + Mat.col];
	Mat_Print(Inv_Mat);

	return Inv_Mat;
}
