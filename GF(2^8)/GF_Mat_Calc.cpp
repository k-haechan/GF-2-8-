/*
GF���� ��Ŀ����Լ��� ��Ƴ��� ����(��� ���, ��� ���ϱ�, ���� �����, ���� ��ȯ, ����ı��ϴ� ����
*/
#include <iostream>
#include "GF_Mat(Calc).h"

void GF_Mat_Print(GF_Matrix Mat) {//GF_������
	for (int i = 0; i < Mat.row; i++) {
		std::cout << "[ ";
		for (int j = 0; j < Mat.col; j++) {
			printf("%02x ", Mat.M[i][j]);
		}std::cout << "]" << std::endl;
	}
	printf("\n");

}

GF_Matrix GF_Mat_Mul(GF_Matrix Mat1, GF_Matrix Mat2) {//GF_��İ�
	if (Mat1.col != Mat2.row) {
		printf("��İ��� ���ǵ��� �ʽ��ϴ�.\n");
		return Mat1;//�ǹ̾��� ��ȯ
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

void GF_Mat_Scalar_Mul(GF_Matrix& A, byte scalar, int row) {//GF_��Ŀ��� �࿡ ������ϱ�	
	for (int i = 0; i < A.col; i++)
		A.M[row][i] ^= GF_Mul(scalar, A.M[row][i]);
}
void GF_Mat_RowSwap(GF_Matrix& Mat, int row1, int row2) {//GF_��Ŀ��� �౳ȯ

	//�׳� Mat[row1]<->Mat[row2]�� �ȵǳ�? ������ ������ �������ٵ�-�غôµ� ������ c++�� �ٸ���
	byte temp;
	
	for (int i = 0; i < Mat.col; i++)
	{
		temp = Mat.M[row1][i];
		Mat.M[row1][i] = Mat.M[row2][i];
		Mat.M[row2][i] = temp;
	}
}

void GF_Mat_PivotUnity(GF_Matrix& A, int pivot)//pivot���� pivot�� ũ�⸦ 1�� ������ִ� �Լ�
{
	byte a = A.M[pivot][pivot];
	a = GF_Inv(a);
	for (int i = 0; i < A.col; i++)
		if (A.M[pivot][i] != 0)
			A.M[pivot][i] = GF_Mul(A.M[pivot][i], a);
}

void GF_Mat_RowAdd(GF_Matrix& Mat, byte scalar, int pivot_row, int target_row) {//������ؼ� ���ϱ�
	for (int i = 0; i < Mat.col; i++)
		Mat.M[target_row][i] ^= GF_Mul(scalar, Mat.M[pivot_row][i]);//pivot row�� scalar�� �ؼ� target row�� ���Ѵ�.
}

GF_Matrix GF_Mat_Inv(GF_Matrix Mat) {
	if (Mat.col != Mat.row)
	{
		printf("������� �������� �ʽ��ϴ�.\n");
		return Mat;
	}

	GF_Matrix AugMat;//÷�����
	AugMat.row = Mat.row;
	AugMat.col = Mat.col * 2;

	for (int i = 0; i < Mat.row; i++) //÷����� ����
		for (int j = 0; j < Mat.col; j++) {
			AugMat.M[i][j] = Mat.M[i][j];
			AugMat.M[i][j + Mat.col] = (i == j) ? 0x01 : 0x00;
		}
	
	for (int i = 0; i < Mat.col; i++) {
		int pivot_row = -1;

		for (int j = i; j < Mat.row; j++) {//i��° ������ 0�� �ƴ� ���� ������ ���� ���� ���� ã�� �� ���Ҹ� pivot���� �����Ѵ�.
			if (AugMat.M[j][i] != 0) {
				pivot_row = j;
				break;
			}
		}
		if (pivot_row == -1) { // pivot�� �������� �ʴ� ���� ����� ������ �������� �ʴ´�.
			printf("������� ���������ʽ��ϴ�.\n");
			return Mat;
		}

		if (pivot_row != i)//M[i][i]�̸� ��ġ�� �ٲ��� �ʿ䰡 ����(������ٸ��� ���)
			GF_Mat_RowSwap(AugMat, pivot_row, i);

		GF_Mat_PivotUnity(AugMat, pivot_row);//�Ǻ��� ũ�⸦ 1�� �ٲ۴�.-�ش� �࿡ ������ �Ѱ��� ���Ѵ�

		for (int k = 0; k < Mat.row; k++)
			if (k != pivot_row && AugMat.M[k][i] != 0)//�Ǻ��� �� �Ǻ��� 0�� �����ϰ�
				GF_Mat_RowAdd(AugMat, (AugMat.M[k][i]), pivot_row, k);//�Ǻ����� ������ ������ 0���� ������ش�.
	}
	GF_Matrix Inv_Mat;//�����
	Inv_Mat.row = Mat.row;
	Inv_Mat.col = Mat.col;
	for (int i = 0; i < Inv_Mat.row; i++)//÷����Ŀ��� ����� ����
		for (int j = 0; j < Inv_Mat.col; j++)
			Inv_Mat.M[i][j] = AugMat.M[i][j + Mat.col];

	return Inv_Mat;
}
