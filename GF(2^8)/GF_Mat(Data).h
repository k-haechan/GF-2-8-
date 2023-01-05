/*
GF 행열의 정보(크기, )등을 저장하는 파일
*/
#pragma once//include한 것을 두번 include 하지 않겠다는 뜻
#define MAX 10

typedef unsigned char byte;



struct GF_Matrix {
	byte M[MAX][MAX * 2];
	int row;
	int col;
};