/*
GF���� �����Լ��� ��Ƴ��� ����(���, ���ϱ�, ���ϱ�, ���� �������ϱ�)
*/
#include <iostream>
#include "GF_Data.h"


void GF_Print(byte gf) {//GF ����(ȯ ���׽�) ����Լ�
	printf("%d = 0x%02x = ", gf, gf);
	for (int i = 7; i >= 0; i--)
		if ((gf >> i) & 0x01)
			std::cout << "+x^" << i;
	std::cout << std::endl;
}

byte GF_Add(byte gf1, byte gf2) {//GF ���� ���ϱ� �Լ� ( XOR ) 
	return gf1 ^ gf2;
}

byte GF_Xtime(byte gf) {//Xtime
	return ((gf >> 7) & 0x01 ? (gf << 1) ^ 0x1b : gf << 1);//x^8�� �з������µ� x^8 = x^4 + x^3 + x^2 + x^0 = 0x1b
}

byte GF_Mul(byte f, byte g) {//GF ���� ���ϱ� �Լ�
	byte h = 0x00;

	for (int i = 7; i >= 0; i--)
	{
		h = GF_Xtime(h);
		if ((f >> i) & 0x01)//f(x)�� �ɰ��� �Լ�
			h = GF_Add(h, g);
	}
	return h;
}


byte GF_Inv(byte f) {//GF ���� ���ϱ� �Լ�, a^255 = 1(�丣������) -> a^254 = a^-1, 254 = 1111 1110 (2)
	byte temp = f;//0�� ������ 0�̴�.
	byte invf = 1;
	for (int i = 0; i < 7; i++)
	{
		temp = GF_Mul(temp, temp);
		invf = GF_Mul(temp, invf);
	}
	return invf;
}
