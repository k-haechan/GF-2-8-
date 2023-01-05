/*
GF에서 연산함수를 모아놓은 파일(출력, 더하기, 곱하기, 곱의 역원구하기)
*/
#include <iostream>
#include "GF_Data.h"


void GF_Print(byte gf) {//GF 원소(환 다항식) 출력함수
	printf("%d = 0x%02x = ", gf, gf);
	for (int i = 7; i >= 0; i--)
		if ((gf >> i) & 0x01)
			std::cout << "+x^" << i;
	std::cout << std::endl;
}

byte GF_Add(byte gf1, byte gf2) {//GF 원소 더하기 함수 ( XOR ) 
	return gf1 ^ gf2;
}

byte GF_Xtime(byte gf) {//Xtime
	return ((gf >> 7) & 0x01 ? (gf << 1) ^ 0x1b : gf << 1);//x^8이 밀려나가는데 x^8 = x^4 + x^3 + x^2 + x^0 = 0x1b
}

byte GF_Mul(byte f, byte g) {//GF 원소 곱하기 함수
	byte h = 0x00;

	for (int i = 7; i >= 0; i--)
	{
		h = GF_Xtime(h);
		if ((f >> i) & 0x01)//f(x)를 쪼개는 함수
			h = GF_Add(h, g);
	}
	return h;
}


byte GF_Inv(byte f) {//GF 역원 구하기 함수, a^255 = 1(페르마정리) -> a^254 = a^-1, 254 = 1111 1110 (2)
	byte temp = f;//0의 역원은 0이다.
	byte invf = 1;
	for (int i = 0; i < 7; i++)
	{
		temp = GF_Mul(temp, temp);
		invf = GF_Mul(temp, invf);
	}
	return invf;
}
