#include "CMatrix.h"

// 정적 변수의 초기화 (함수밖에서)
//The initialisation of the static variable must be done outside of any function.
int CMat::Counter = 0;

/*
A =
[ 1.000 0.000 0.000 ]
[ 0.000 1.000 2.000 ]
[ 0.000 2.000 1.000 ]
B =
[ 1.000 2.000 3.000 ]
[ 2.000 3.000 1.000 ]
[ 3.000 1.000 2.000 ]
*/
void CMat_test() {
    double a[MAX][MAX] = {
        {1.0,0.0,0.0,},
        {0.0,1.0,2.0,},
        {0.0,2.0,1.0,}
    };
    double b[MAX][MAX] = {
        {1.0,2.0,3.0,},
        {2.0,3.0,1.0,},
        {3.0,1.0,2.0,}
    };

    double d[MAX][MAX] = {
        {1.0,2.0,3.0,},
        {0.0,1.0,2.0,},
    };
    CMat c_A(3, 3, a);
    CMat c_B(3, 3, b);
    CMat c_D(2, 3, d);
    CSQMat A(c_A);
    CSQMat B(c_B);
    CSQMat D(c_D);

    A.Print("A");
    B.Print("B");

    printf("Trace Tr(A) = %f\n", A.Tr());
    printf("Trace Tr(B) = %f\n", B.Tr());

    printf("\n");
    CMat c_AB = CMat::Mul(A, B);
    CSQMat AB(c_AB);
    AB.Print("AB");

    CMat c_BA = CMat::Mul(B, A);
    CSQMat BA(c_BA);
    BA.Print("BA");

    printf("Trace Tr(AB) = %f\n", AB.Tr());
    printf("Trace Tr(BA) = %f\n", BA.Tr());

    A.Print("A");
    D.Print("D");

    (CMat::Add(A, D)).Print("A+D = F");

    printf("Det (A) = %1.0f\n", A.Det());
   
}
void Matrix_Inv_test() {
    double a[MAX][MAX] = {
        {0.5,-0.25,0.0,},
        {-0.25,0.5,-0.25,},
        {0.0,-0.25,0.5,}
    };
    CMat c_A(3, 3, a);
    CSQMat A(c_A);
    A.Print("A");
    CSQMat Inv_A = A.Inv();
    Inv_A.Print("Inverse A");

    (CMat::Mul(A, Inv_A)).Print("C");

  
}



int main()
{
    /*
    CMat_test();
    Matrix_Inv_test();

    
    CMat C;
    CSQMat D;
    
    D = (CSQMat) C;  // 생성자 CSQMat(CMat A) 호출
    

    cout << endl << "Matrix Counter = " << CMat::GetConter() << endl;
    */

    unsigned char b[4] = { 0x01,0x02,0x03,0x04 };
    for (int i = 0; i < 3; i++)
        printf("%02x", *(b + i));
    printf("\n");
    int a = *(int*)b;
   
    a = 0x01020304;
    printf("0x%02x\n", a);

    for (int i = 3; i >= 0; i--)
        printf("%02x ", (a >> (8 * i) & 0xff));
}
