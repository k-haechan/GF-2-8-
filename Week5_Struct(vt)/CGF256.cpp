#include <iostream>
#include "CGF256.h"

CGF256 CGF256::Add(CGF256 x) {

	return x.GetValue() ^ mData;//���⼭�� mData�� �׳� ����Ϸ���
}

CGF256 CGF256::Xtime() {//�޸� ���� �ȴ�. �׳� void�������� ¥�� �ȵɱ�?
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

CGF256 CGF256::Xtime3() {//������ �ڵ�
	return(((mData >> 7) & 0x01) == 1 ? (mData << 1) ^ 0x1b : mData << 1);
}
CGF256 CGF256::Xtime4() {//������ �ڵ�
	CGF256 xtime(((mData >> 7) & 0x01) == 1 ? (mData << 1) ^ 0x1b : mData << 1);
	return xtime;
}

CGF256 CGF256::Mul(CGF256 x) {
	CGF256 result;
	result.SetValue(0x00);

	for (int i = 7; i >= 0; i--) {
		result = result.Xtime();
		if (((mData >> i) & 0x01) == 1)//Clsass  result�� ������ �ϹǷ� ���� Ŭ������ mData�� ���� ������ �ʴ´�.
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

void CGF256::PrintAsPolynomial() {//���׽� ���
	int coef;
	for (int i = 7; i >= 0; i--) {
		coef = (mData >> i) & 0x01;//GetData�� �ƴ϶� mData�� ������ڳ�..
		if (coef == 1)
			printf("+x^%d", i);
	}
	cout << endl;
}
