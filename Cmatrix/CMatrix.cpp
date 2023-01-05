#include "CMatrix.h"

CMat::CMat(int r, int c, double data[MAX][MAX]) {
    row = r;
    col = c;
    if ((r > MAX) || (c > MAX)) { 
        printf("[Error] The size (%d, %d) is too Large!\n", r, c);
        return;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] = data[i][j];
        }
    }
    IncreaseCounter();
}


CSQMat::CSQMat(CMat A) { // cast 연산자처럼 사용한다.
    row = A.GetRow();
    col = A.GetCol();
    //HW2: 정사각행렬인지 확인하는 코드
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] = A.GetValue(i, j);
        }
    }
}


void CMat::Print(const char* pName) {
    if (pName != nullptr) {
        cout << pName << " = " << endl;
    }
    for (int i = 0; i < row; i++) {
        printf("[");
        for (int j = 0; j < col; j++) {
            printf("%7.3f", M[i][j]);
        }
        printf(" ]\n");
    }
    printf("\n");
}

void CMat::ScalarMul(double value) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            M[i][j] *= value;
        }
    }
}

CMat CMat::Add(CMat M1, CMat M2) {//M1을 더해서 M2에 저장
    // HW2: 함수 내용 채우기
    if ((M1.row != M2.row) || (M1.col != M2.col)) {
        printf("[Error] The sizes of two matrices are not equal!\n");
        CMat F;
        return F;//의미없는 출력
    }
    CMat add(M1.row, M1.col);
    for (int r = 0; r < add.row; r++)
        for (int c = 0; c < add.col; c++)
            add.M[r][c] = M1.M[r][c] + M2.M[r][c];
        
    return M1;
}


void CMat::Mat_Exchange_Row(int row1, int row2) {
    double temp;
    for (int i = 0; i < col; i++) {
        temp = M[row1][i];
        M[row1][i] = M[row2][i];
        M[row2][i] = temp;
    }
}

void CMat::Mat_Scalar_Mul(double scalar, int row) {
    for (int i = 0; i < col; i++) {
        M[row][i] *= scalar;
    }
}

void CMat::Mat_Row_Add(double scalar, int row_src, int row_target) {
    for (int i = 0; i < col; i++) {
        M[row_target][i] += scalar * M[row_src][i];
    }
}

CMat CMat::Mul(CMat A, CMat B) {
    // HW2: 함수 내용 채우기
    if (A.col != B.row) {
        printf("행렬곱이 정의되지 않습니다.\n");
        return A;//의미없는 출력
    } 
    CMat mul(A.row, B.col);

    for (int i = 0; i < mul.row; i++) {
        for (int j = 0; j < mul.col; j++) {
            mul.M[i][j] = 0;
            for (int k = 0; k < A.col; k++) {
                mul.M[i][j] += A.M[i][k] * B.M[k][j];
                //printf("%f ", mul.M[i][j]);
            }
        }
    }
    return mul;
}

//===============
double CSQMat::Det() {
    double det;
    int sign, c_pos;
    CSQMat Adj(row - 1);

    if (row == 1) return GetValue(0, 0);

    //Adj.SetSize(row - 1, col - 1);
    det = 0.0;
    sign = -1;

    for (int c = 0; c < col; c++) {
        sign = sign * (-1);
        for (int i = 1; i < row; i++) {
            c_pos = 0;
            for (int j = 0; j < col; j++) {
                if (j != c) {
                    Adj.SetValue(i - 1, c_pos, M[i][j]);
                    c_pos++;
                }
            }
        }
        //Adj.Print();
        det += sign * GetValue(0, c) * Adj.Det();
        //cout << "sign*det(Adj) = " << sign*Adj.Det() << endl;
    }
    return det;
}


CSQMat CSQMat::Inv() {
    CSQMat MatInv(row);
    if (GetSize() * 2 > MAX) {
        cout << "[Error] Matrix is too large!" << endl;
        return MatInv;  //의미없는 출력
    }
    CMat AA(row, 2 * col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            AA.SetValue(i, j, GetValue(i, j));
            AA.SetValue(i, col + j, (i == j) ? 1.0 : 0.0);
        }
    }

    int pivot_row;
    for (int j = 0; j < col; j++) {
        pivot_row = -1;
        for (int i = j; i < row; i++) {
            if (abs(AA.GetValue(i, j)) > NEARLY_ZERO) {
                pivot_row = i;
                break;
            }
        }
        if (pivot_row == -1) {
            cout << "[Error] Not invertible!\n";
            return MatInv;  //의미없는 출력
        }
        if (pivot_row != j) {  // j번째 행 <--> pivot 행
            AA.Mat_Exchange_Row(j, pivot_row);
        }
        AA.Mat_Scalar_Mul(1. / AA.GetValue(j, j), j);
        for (int i = 0; i < row; i++) {
            if ((i != j) && (abs(AA.GetValue(i, j)) > NEARLY_ZERO)) {
                AA.Mat_Row_Add(-AA.GetValue(i, j), j, i);
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            MatInv.SetValue(i, j, AA.GetValue(i, j + col));
        }
    }
    return MatInv;
}

double CSQMat::Tr() {
    double tr=0.;
    for (int i = 0; i < row; i++)
        tr += M[i][i];
    return tr;
}