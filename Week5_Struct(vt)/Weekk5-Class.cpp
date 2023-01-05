#include <iostream>
#define MAX_SIZE 10

/*
struct stVector {
	int size;
	double v[MAX_SIZE];
};
*/
// C++ OOP (Objective Oriendted Programming, ��ü����): Encapsulation, Polymorhism, Inheritance
// Encapsulation: Data (set) + Operataions (structure, relateion...) - class
//
class CVector {//Ŭ���� ����
private:	//3���� ����: private(�⺻��), public, protected - private�� ���������� �Ұ���, public�� ���־�� ���������� �����ϴ�. ������ü�� �ȵ�
	// ��� ������ (Data)
	int mSize;//Private�� ����������� �տ� m�Ǵ� m_�� �����°� �����̴�. ���� m�� ���� �������� public�� ������ �ȵȴٴ� �ǹ̵� �����Ѵ�.
	double mVec[MAX_SIZE] = { 0, };
public:
	// ��� �Լ��� (function, operation) method
	
	//������(constructor) : ����(instance)�� ������ �� ȣ��Ǵ� �Լ� // �����ڰ� ������ �ȵǰ� �⺻������(no parameter)�� �ϳ��� �־���Ѵ�. ����Ʈ�����ζ�
	//�����ε�(overloading) �ؿ��� ������ �����ε��̴�. �����ε��� �Լ����� ���������� �Ķ���Ϳ� �� ȣ�� ������ �ٸ� ����̴�.

	CVector() { mSize = 1; }//�⺻������. �⺻�����ڴ� �ν��Ͻ��� �������� �� ����Ǵ� ����̴�.

	CVector(int size) {	mSize = size; };//�Լ��� �������� class ���ǿ� ���� ��� -> inline �Լ���
	CVector(int size, double arr[]);//�����ڴ� ����Ÿ���� ����.
	
	void SetValue(int nPos, double value);//nPos-> n�� ������ �ǹ�, Pos�� Position //�̷��� ����Լ��θ� ����������� ������ �� �ְ� �ϴ°� ����.(Encapsulation)
	double Get_Value(int nPos);//Ư����ġ�� ���� ��ȯ�ϴ� �Լ�// �ٵ� �̰� mVec[i]�� �������ݾ� �������� �ƴ� �������� ��ȯ�� ��Ű�� �����ϱ� ���� �Ƚᵵ ���� ����? �����ϱ⸸ �ѵ�
	void Print();
	void SetSize(int size) { mSize = size; };//�̷��� ª�� �Լ����� ������ �����ڸ� ������� �ʾƵ� �ȴ�. ->inline�Լ�
	int Size() { return mSize; };

	void ScalarMul(double value);
	CVector Add(CVector cv);//�ΰ��� ���� ������ �� �ڽ��� �����Ƿ� ���ſ� cv�� ���ϴ� �ǹ̷� �Ķ���Ͱ� �ϳ��̴�.//(����)v3=v1.Add(v2) -> (����) v3=v1+v2(�����ϸ�)������ ������
};

void CVector::ScalarMul(double value) {
	for (int i = 0; i < mSize; i++)
		mVec[i] *= value;
}

CVector CVector::Add(CVector cv) {//���ÿ� result�� �� �ö󰡾��ؼ� ȿ�������� ���ϴ�. �ذ��Ϸ��� �����͸� ����ϸ� �ȴ�.
	CVector result;
	//����ó���� �̷��� ���� �׳� ũ�Ⱑ ū��ŭ size�� ��� �ΰ��� ���ϴ� �޽�带 ¥�� �ɵ�.
	if (cv.Size() != mSize) {//cv.Msize�� ���ϰ� cv.Size�� �ϴ� ����? �ظ��ϸ� private��������� ���� ������ ���ϴ� ��. 
		printf("Vector size mismatch!\n");
		return result;//���ǹ��� ��
	}
	result.SetSize(mSize);
	for (int i = 0; i < mSize; i++)
		result.SetValue(i, mVec[i] + cv.Get_Value(i));//���������� ���������� cv.mVec[i] ��� cv.Get_Value(i)
	
	return result;
}
CVector::CVector(int size, double arr[]) {//�����ڴ� ���ϰ��� ����.
	if (size > MAX_SIZE)
		printf("�Է��� ����� �ʹ� Ů�ϴ�.");
	mSize = size;
	for (int i = 0; i < size; i++)
		mVec[i] = arr[i];
}
void CVector::SetValue(int nPos, double value) {
	if (nPos >= mSize) {
		printf("Range error");
		return;
	}
	mVec[nPos] = value;//mVec�� private ������ SetValue�Լ��� private�̱� ������ ������ �� �ִ�.
}

double CVector::Get_Value(int nPos) {
	if (nPos >= mSize) {
		printf("Range error");
		return -1.0;
	}
	return mVec[nPos];
}

//::������ ������
void CVector::Print() {  // (����Ÿ��)(Ŭ������)::(����Լ��̸�)(...) {}
	printf("[ ");
	for (int i = 0; i < mSize; i++)
		printf("%7.3f", mVec[i]);
	printf(" ]\n");
}


/*
void CVector_Print(CVector vec) {
	printf("[ ");
	for (int i = 0; i < vec.size; i++)
		printf("%7.3f", vec.v[i]);
	printf(" ]\n");
}
*/
void Class_Test() {
	CVector my_vector(3);
	//CVector : Ŭ������ (int, double)
	//my_vector : ����(�ν��Ͻ�, ��ü(object))

	printf("Start class_test()...\n");
	
	//my_vector.mSize = 3;
	my_vector.SetValue(0, 1.0);
	my_vector.SetValue(1, 2.0);
	my_vector.SetValue(2, 3.0);
	//my_vector.SetValue(3, 4.0);

	//CVector_Print(my_vector);
	my_vector.Print();

	printf("Start class_test(): 2nd test...\n");

	CVector vec2;//�⺻ ������
	vec2.SetSize(5);

	double a[5] = { 0.1,0.2,0.3,0.4,0.5 };
	CVector vec3(5, a);
	vec3.Print();

	vec3.ScalarMul(10);
	vec3.Print();

	CVector vec4(5, a);
	CVector vec5;
	vec5 = vec3.Add(vec4);
	vec5.Print();
}

int main()
{
	Class_Test();
}