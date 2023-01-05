#pragma once

typedef unsigned char byte; // 새로운 데이터 타입 : byte = GF(2^8)

void AES8_SubBytes(byte state[16]);
void AES8_ShiftRows(byte state[16]);
//GF(2^8) xtime()함수
byte GF_Xtime(byte gf);
void AES8_MixColumns(byte state[16]);
void AES8_AddRoundKey(byte in[16], byte roundkey[16], byte out[16]);
void AES8_Round(byte in[16], byte rk[16], byte out[16]);
void AES8_Encrypt(byte PT[16], byte RK[11][16], byte CT[16]);
void AES_Print_State(byte state[16], const char* msg = nullptr);