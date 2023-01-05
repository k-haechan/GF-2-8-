//AES ��ȣȭ ���� �Լ�
#include <iostream>
#include "GF_Mat(Calc).h"


//��ȣȭ �߰��� ���
void AES_Print_State(byte state[16], const char* msg = nullptr) {//���� �����ǰ� ���� ������ nullptr���� �ֶ�� ��, const�� ������ ������('pt'�� ����̹Ƿ�) ����� ������ ���� �ʴ� �� ���� ������ �ʴ´�. ���ͷ��� �޸𸮸� �������� �ʰ� �޸� Ǯ�� �ִ� ���� �̿� msg��� ���ͷ� Ǯ�� �ּҸ� ������
	if (msg != nullptr)
		printf("%s = ", msg);
	for (int i = 0; i < 16; i++)
		printf("%02x ", state[i]);
	printf("\n");
}

//�Ʒ� ������ ����. �������� �ڵ��� �������� ���ؼ� �迭�� �̿��ϰ� ũ�⸦ ������ ��.
//void AddRoundKey(byte* in, byte* key, byte* out)
//void AddRoundKey(byte in[],byte key[],byte out[]) 
//�Լ����� ������ ���ÿ� ����Ǿ� �������� ���̴ٰ� �Լ��� ���� �� �ֹߵȴ�.
void AES_AddRoundKey(byte in[16],byte key[16],byte out[16]) {//�迭�� ������ �����̹Ƿ� return ���� �ʿ����. ������ call by referrence
	for (int i = 0; i < 16; i++)
		out[i] = in[i] ^ key[i];
}



byte AES_Affine(byte w) {//Affine : Aw+b

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
	byte w_vec[8], y_vec[8], y = 0x00;

	for (int i = 0; i < 8; i++)  // �̰��ѹ����ô�
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


//Y = Sbox(x^-1) = Aw + b, w = x^(-1)
void AES_SubBytes(byte in[16], byte out[16]) {//S-Box, 8*16=128(AES_128) 128-bit �� 8-bit �� 1byte�� �ɰ���(16����) ���� Sbox�� ���� ġȯ�� ��´�. 
	//******************Sbox�� ���ϴ°��� �ƴ϶�, �ٷ� 16���� ����Ʈ�� Affine��ȯ�� ���ؼ� Sbox�� ���Ҹ� ���ϴ°Ŵ�. ������ ���� 256 ����Ʈ�� ��(Sbox)�� ���� �ʿ䰡 ���� ����.
	byte tmp;

	for (int i = 0; i < 16; i++) {
		tmp = GF_Inv(in[i]);
		out[i] = AES_Affine(tmp);
	}
}


/*
0	4	8	12			0	4	8	12
1	5	9	13  --->	5	9	13	1		i = 0,4,8,12 �� ���� ��ȭx
2	6	10	14  --->	10	14	2	6		1, 5, 9 ,13�� ���������� �ϳ�
3	7	11	15			15	3	7	11		�� �� ���ʿ��� ���Ҹ�ŭ ���������� ����Ʈ out[i]=in[i+4*i]=in[5i%16]
*/
void AES_ShiftRows(byte in[16], byte out[16]) {
	//int temp;
	for (int i = 0; i < 16; i++)
		out[i] = in[(i * 5) % 16];
}

void AES_MixCol(byte x[4], byte y[4]) {//4byte¥�� column�� �ٲ㼭 y'�� �ִ� �Լ�
	GF_Matrix MC = { { {0x02,0x03,0x01,0x01},
		{ 0x01, 0x02, 0x03, 0x01},
		{ 0x01 ,0x01 ,0x02 ,0x03 },
		{ 0x03 ,0x01 ,0x01 ,0x02 } } ,4,4 };//MixColumn��Ļ���

	GF_Matrix X, Y;//��Ŀ����Լ��� �̿��ϱ� ���ؼ� 4����Ʈ ¥���� ���� ũ�Ⱑ 4�� �����ͷ� ��ȯ
	X.col = 1; Y.col = 1;
	X.row = 4; Y.row = 4;
	for (int i = 0; i < 4; i++)
		X.M[i][0] = x[i];//��Ļ���(����Ʈ x�� 2�� ��ķ� ��ȯ)
	Y = GF_Mat_Mul(MC, X);//MixColumn����� Y�� ����

	for (int i = 0; i < 4; i++)
		y[i] = Y.M[i][0];
}
void AES_MixColumns(byte in[16], byte out[16]) {

	byte x[4], y[4];
	for (int col = 0; col < 4; col++) {
		for (int i = 0; i < 4; i++) {
			x[i] = in[col * 4 + i];//in 0,1,2,3 shift rowó�� ������ �Ʒ���.
		}
		AES_MixCol(x, y);//y�� x�� mixcul ������ ���
		for (int i = 0; i < 4; i++)//�����ڸ�
			out[col * 4 + i] = y[i];//0123 4567 891011 12131415
	}
}

void AES_MyMixColumns(byte in[16], byte out[16]) {

	GF_Matrix MC = { { {0x02,0x03,0x01,0x01},
		{ 0x01, 0x02, 0x03, 0x01},
		{ 0x01 ,0x01 ,0x02 ,0x03 },
		{ 0x03 ,0x01 ,0x01 ,0x02 } } ,4,4 };

	GF_Matrix X, Y;
	X.row = 4, Y.row = 4;
	X.col = 1, Y.col = 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			X.M[j][0] = in[4 * i + j];

		Y = GF_Mat_Mul(MC, X);
		for (int j = 0; j < 4; j++)
			out[4 * i + j] = Y.M[j][0];
	}
}
void AES_Round_Function(byte round_in[16], byte rkey[16], byte round_out[16]) {
	byte state1[16], state2[16];

	AES_SubBytes(round_in, state1);
	AES_Print_State(state1, "SubBytes_output");
	AES_ShiftRows(state1, state2);
	AES_Print_State(state2, "ShiftRows_output");
	AES_MyMixColumns(state2, state1);
	AES_Print_State(state1, "MixColumn_output");
	AES_AddRoundKey(state1, rkey, round_out);
}

void AES_Encrypt(byte pt[16], byte rk[11][16], byte ct[16]) {
	
	byte state1[16], state2[16];

	AES_AddRoundKey(pt, rk[0], state1);//Round 1
	AES_Print_State(state1, "AddRoundKey[0]");

	for (int i = 1; i < 10; i++) {// Round 2~10
		AES_Round_Function(state1, rk[i], state2);
		AES_Print_State(state2, "Round output");
		for (int j = 0; j < 16; j++) {
			state1[j] = state2[j];
		}
	}

	AES_SubBytes(state1, state2);//Round 11
	AES_ShiftRows(state2, state1);
	AES_AddRoundKey(state1, rk[10], ct);
}



void Run_AES_round_test() {
	byte pt[16] = { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff };//plain text
	AES_Print_State(pt, "pt");//msg = "pt"    ---------------pt�� 3����¥�� ���ڿ� [p][t][\0], \0�� �ƽ�Ű�ڵ� 0 �� pt�� const char* �� ���ͷ�����(���) ��������� �ٸ���.
	AES_Print_State(pt);//msg = nullptr

	byte rk[11][16] = {//11���� ���� Ű
		{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f},
		{0xd6, 0xaa, 0x74, 0xfd, 0xd2, 0xaf, 0x72, 0xfa, 0xda, 0xa6, 0x78, 0xf1, 0xd6, 0xab, 0x76, 0xfe },
		{	0xb6, 0x92, 0xcf, 0x0b, 0x64, 0x3d, 0xbd, 0xf1, 0xbe, 0x9b, 0xc5, 0x00, 0x68, 0x30, 0xb3, 0xfe},
		{	0xb6, 0xff, 0x74, 0x4e, 0xd2, 0xc2, 0xc9, 0xbf, 0x6c, 0x59, 0x0c, 0xbf, 0x04, 0x69, 0xbf, 0x41},
		{	0x47, 0xf7, 0xf7, 0xbc, 0x95, 0x35, 0x3e, 0x03, 0xf9, 0x6c, 0x32, 0xbc, 0xfd, 0x05, 0x8d, 0xfd},
		{	0x3c, 0xaa, 0xa3, 0xe8, 0xa9, 0x9f, 0x9d, 0xeb, 0x50, 0xf3, 0xaf, 0x57, 0xad, 0xf6, 0x22, 0xaa},
		{	0x5e, 0x39, 0x0f, 0x7d, 0xf7, 0xa6, 0x92, 0x96, 0xa7, 0x55, 0x3d, 0xc1, 0x0a, 0xa3, 0x1f, 0x6b},
		{	0x14, 0xf9, 0x70, 0x1a, 0xe3, 0x5f, 0xe2, 0x8c, 0x44, 0x0a, 0xdf, 0x4d, 0x4e, 0xa9, 0xc0, 0x26},
		{	0x47, 0x43, 0x87, 0x35, 0xa4, 0x1c, 0x65, 0xb9, 0xe0, 0x16, 0xba, 0xf4, 0xae, 0xbf, 0x7a, 0xd2},
		{	0x54, 0x99, 0x32, 0xd1, 0xf0, 0x85, 0x57, 0x68, 0x10, 0x93, 0xed, 0x9c, 0xbe, 0x2c, 0x97, 0x4e},
		{	0x13, 0x11, 0x1d, 0x7f, 0xe3, 0x94, 0x4a, 0x17, 0xf3, 0x07, 0xa7, 0x8b, 0x4d, 0x2b, 0x30, 0xc5 } };
	byte ct[16];

	AES_Encrypt(pt, rk, ct);
	AES_Print_State(ct, "ct");
}
int main()
{
	Run_AES_round_test();
}