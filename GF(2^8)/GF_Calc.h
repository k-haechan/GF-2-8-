/*
GF�� ������ �����ϴ� �������
*/
#pragma once//include�� ���� �ι� include ���� �ʰڴٴ� ��
#include "GF_Data.h" // ���� �����ص� ������ ������ GF��� ���꿡�� GF������ �̿�ǹǷ� ���⿡ �����ص� �ȴ�.

void GF_Print(byte gf);
byte GF_Add(byte gf1, byte gf2);
byte GF_Xtime(byte gf);
byte GF_Mul(byte f, byte g);
byte GF_Inv(byte f);