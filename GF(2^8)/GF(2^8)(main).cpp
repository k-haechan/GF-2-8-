/*
GF_Add
GF_Print
GF_Xtime
GF_mul
*/


#include "GF_Calc.h"

//AES+Affine Aw+b (w = x^(-1))
byte AES_Affine(byte w) {

	byte A[8][8] = {
		{1,0,0,0,1,1,1,1},
		{1,1,0,0,0,1,1,1},
		{1,1,1,0,0,0,1,1},
		{1,1,1,1,0,0,0,1},
		{1,1,1,1,1,0,0,0},
		{0,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,0},
		{0,0,0,1,1,1,1,1}
	};

	byte y_vec[8], w_vec[8], y;
	byte b_vec[8] = { 1,1,0,0,0,1,1,0 };

	for (int i = 0; i < 8; i++)
	{
		w_vec[i] = (w >> i) & 0x01;
	}

	for (int i = 0; i < 8; i++)
	{
		y_vec[i] = b_vec[i];
		for (int j = 0; j < 8 ; j++)
			y_vec[j] ^= A[i][j] * w_vec[j];
	}

	y = 0x00;
	for (int i = 0; i < 8; i++)
		y ^= (y_vec[i] << i);

	return y;
}

void Get_AES_Sbox(byte sbox[256]) {

	//0^(-1) = 0 으로 간주한다.
	sbox[0] = AES_Affine(0);
	for (int i = 1; i < 256; i++) {
		sbox[i] = AES_Affine(GF_Inv(i));
	}
}

void GF_Sbox(byte gf[])
{
	gf[0] = 0;
	for (int i = 1; i < 256; i++)
		gf[i] = AES_Affine(i);
	for (int j = 1; j < 256; j++)
	{
		if (j % 16 == 0)
			std::cout << std::endl;
		printf("%02x", gf[j]);
	}
}
void test()
{
	byte gf1 = 0x80;
	byte gf2 = 0x01;
	byte gf3 = GF_Add(gf1, gf2);
	
	GF_Print(gf1);
	GF_Print(gf2);
	GF_Print(gf3);

	GF_Print(GF_Xtime(gf1));

	GF_Print(GF_Mul(gf1, gf2));

	byte gf1_inv = GF_Inv(gf1);
	GF_Print(gf1_inv);
	GF_Print(GF_Mul(gf1,gf1_inv));
	
	byte gfe[256];
	GF_Sbox(gfe);
}
void Sbox_test() {
	byte Sbox[256];
	Get_AES_Sbox(Sbox);

	std::cout << "Sbox = " << std::endl;
	for (int i = 0; i < 256; i++)
	{
		if ((i % 16) == 0) printf("\n");
		printf("%02x ", Sbox[i]);
	}
}
int main()
{
	Sbox_test();
}
