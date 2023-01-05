//GF(2^8)ÀÇ MixColumn¿¬»ê
/*
*/
#include <iostream>
#include "GF_Mat(Calc).h"
void MixColumn() {

	GF_Matrix MC = { { {0x02,0x03,0x01,0x01},
		{ 0x01, 0x02, 0x03, 0x01},
		{ 0x01 ,0x01 ,0x02 ,0x03 },
		{ 0x03 ,0x01 ,0x01 ,0x02 } } ,4,4 };

	GF_Matrix InvMC;
	InvMC = GF_Mat_Inv(MC);

	std::cout << "Matrix MC " << std::endl;
	GF_Mat_Print(MC);

	std::cout << "Inverse Matrix of MC " << std::endl;
	
	GF_Mat_Print(InvMC);
}
int main() 
{
	MixColumn();
	return 0;
}