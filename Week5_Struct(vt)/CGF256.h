#pragma once

using namespace std;

typedef unsigned char byte;

class CGF256 {	// GF(2^8) class
private:
	byte mData;	//	GF(2^8) 원소
public:
	CGF256() { mData = 0x00; };//기본생성자
	CGF256(byte data) { mData = data; };

	void SetValue(byte data) { mData = data; };
	byte GetValue() { return mData; };
	void PrintAsHex();
	void PrintAsPolynomial();
	CGF256 Add(CGF256 x);
	CGF256 Xtime();
	void Xtime2();
	CGF256 Xtime3();
	CGF256 Xtime4();
	CGF256 Mul(CGF256 x);
	CGF256 Inv();
};
