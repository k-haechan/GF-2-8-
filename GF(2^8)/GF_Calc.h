/*
GF의 연산을 정의하는 헤더파일
*/
#pragma once//include한 것을 두번 include 하지 않겠다는 뜻
#include "GF_Data.h" // 따로 정의해도 되지만 어차피 GF행렬 연산에서 GF연산이 이용되므로 여기에 저장해도 된다.

void GF_Print(byte gf);
byte GF_Add(byte gf1, byte gf2);
byte GF_Xtime(byte gf);
byte GF_Mul(byte f, byte g);
byte GF_Inv(byte f);