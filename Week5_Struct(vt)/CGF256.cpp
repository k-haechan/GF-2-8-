#include <iostream>
#include "CGF256.h"

CGF256 CGF256::Add(CGF256 x) {

	return x.GetValue() ^ mData;//여기서는 mData를 그냥 사용하려고
}

CGF256 CGF256::Xtime() {//메모리 낭비가 된다. 그냥 void형식으로 짜면 안될까?
	CGF256 Cxtime;
	if (((mData >> 7) & 0x01) == 1)
		Cxtime.SetValue((mData << 1) ^ 0x1b);
	else
		Cxtime.SetValue(mData << 1);
	return Cxtime;
}

void CGF256::Xtime2() {
	if (((mData >> 7) & 0x01) == 1)
		SetValue((mData << 1) ^ 0x1b);
	else
		SetValue(mData << 1);
}

CGF256 CGF256::Xtime3() {//교수님 코드
	return(((mData >> 7) & 0x01) == 1 ? (mData << 1) ^ 0x1b : mData << 1);
}
CGF256 CGF256::Xtime4() {//태진이 코드
	CGF256 xtime(((mData >> 7) & 0x01) == 1 ? (mData << 1) ^ 0x1b : mData << 1);
	return xtime;
}

CGF256 CGF256::Mul(CGF256 x) {
	CGF256 result;
	result.SetValue(0x00);

	for (int i = 7; i >= 0; i--) {
		result = result.Xtime();
		if (((mData >> i) & 0x01) == 1)//Clsass  result에 연산을 하므로 원래 클래스의 mData의 값은 변하지 않는다.
			result = result.Add(x);
	}
	return result;
}

CGF256 CGF256::Inv() {
	CGF256 temp(mData);
	CGF256 inv(0x01);

	for (int i = 0; i < 7; i++) {
		temp = temp.Mul(temp);
		inv = inv.Mul(temp);
	}
	return inv;
}
void CGF256::PrintAsHex() {
	printf("0x%02x", mData);
}

void CGF256::PrintAsPolynomial() {//다항식 출력
	int coef;
	for (int i = 7; i >= 0; i--) {
		coef = (mData >> i) & 0x01;//GetData가 아니라 mData를 사용하자너..
		if (coef == 1)
			printf("+x^%d", i);
	}
	cout << endl;
}
