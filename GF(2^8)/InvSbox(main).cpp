/*
GF_Print()
GF_Xtime()
GF_Mul()
GF_Inv()
AES_Affine()
*/
#include <iostream>
#include "GF_Calc.h"

using namespace std;

byte Affine(byte w);
void Make_Sbox(byte Sbox[256]);
void Inv_Sbox(byte Inv_Sbox[256], byte sbox[256]);

void Sbox_test() {
	byte Sbox[256];
	byte ISbox[256];
	Make_Sbox(Sbox);
	Inv_Sbox(Sbox, ISbox);
	printf("\n[S-box table]\n");

	for (int i = 0; i < 256; i++) {
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", Sbox[i]);
	}
	cout << endl;

	printf("\n[Inverse S-box table]\n");

	for (int i = 0; i < 256; i++) {
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", ISbox[i]);
	}
	cout << endl;
}

int main()
{
	Sbox_test();
	return 0;
}




byte Affine(byte w) {//Affine : Aw+b

	byte A[8][8] = {
		{1,0,0,0,1,1,1,1},//0x 8f
		{1,1,0,0,0,1,1,1},//0x c7
		{1,1,1,0,0,0,1,1},
		{1,1,1,1,0,0,0,1},
		{1,1,1,1,1,0,0,0},
		{0,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,0},
		{0,0,0,1,1,1,1,1}
	};
	byte b_vec[8] = { 1,1,0,0,0,1,1,0 };//0x c6
	byte w_vec[8], y_vec[8];
	byte y = 0x00;
	
	for (int i = 0; i < 8; i++)  // 이거한번봅시당
		w_vec[i] = (w >> i) & 0x01;
	

	for (int i = 0; i < 8; i++) {
		y_vec[i] = b_vec[i];
		for (int j = 0; j < 8; j++) {
				y_vec[i] ^= A[i][j] * w_vec[j];
			
		}
	}

	for (int i = 0; i < 8; i++)
		y ^= (y_vec[i] << i);

	return y;
}


void Make_Sbox(byte Sbox[256]) {//Ax^-1 + b

	Sbox[0] = Affine(0);
	for (int i = 1; i < 256; i++) 
		Sbox[i] = Affine(GF_Inv(byte(i)));// 사실 GF_Inv(0)=0이므로 위에 0을 따로 정의해줄 필요는 없다.
}

void Inv_Sbox(byte sbox[256], byte ISbox[256]) {
	for (int i = 0; i < 256; i++) {
		ISbox[sbox[i]] = byte(i);//왜 i인지 확인, 그냥 함수그림으로 이해, 갔다가 오니까 ㄱㄴ
	}
}