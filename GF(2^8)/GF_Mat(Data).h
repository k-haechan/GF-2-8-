/*
GF �࿭�� ����(ũ��, )���� �����ϴ� ����
*/
#pragma once//include�� ���� �ι� include ���� �ʰڴٴ� ��
#define MAX 10

typedef unsigned char byte;



struct GF_Matrix {
	byte M[MAX][MAX * 2];
	int row;
	int col;
};