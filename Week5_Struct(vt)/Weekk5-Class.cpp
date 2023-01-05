#include <iostream>
#define MAX_SIZE 10

/*
struct stVector {
	int size;
	double v[MAX_SIZE];
};
*/
// C++ OOP (Objective Oriendted Programming, 객체지향): Encapsulation, Polymorhism, Inheritance
// Encapsulation: Data (set) + Operataions (structure, relateion...) - class
//
class CVector {//클래스 벡터
private:	//3가지 선택: private(기본값), public, protected - private는 참조수정이 불가능, public을 해주어야 참조수정이 가능하다. 참조자체가 안됨
	// 멤버 변수들 (Data)
	int mSize;//Private한 멤버변수에는 앞에 m또는 m_을 붙히는게 관행이다. 따라서 m을 붙힌 변수에는 public한 참조가 안된다는 의미도 내포한다.
	double mVec[MAX_SIZE] = { 0, };
public:
	// 멤버 함수들 (function, operation) method
	
	//생성자(constructor) : 변수(instance)가 생성될 때 호출되는 함수 // 생성자가 없으면 안되고 기본생성자(no parameter)가 하나는 있어야한다. 디폴트값으로라도
	//오버로딩(overloading) 밑에는 생성자 오버로딩이다. 오버로딩은 함수명은 동일하지만 파라미터와 그 호출 내용이 다른 경우이다.

	CVector() { mSize = 1; }//기본생성자. 기본생성자는 인스턴스만 선언했을 때 실행되는 경우이다.

	CVector(int size) {	mSize = size; };//함수의 본문까지 class 정의에 쓰는 경우 -> inline 함수로
	CVector(int size, double arr[]);//생성자는 리턴타입이 없다.
	
	void SetValue(int nPos, double value);//nPos-> n은 정수를 의미, Pos는 Position //이렇게 멤버함수로만 멤버변수들을 참조할 수 있게 하는게 좋다.(Encapsulation)
	double Get_Value(int nPos);//특정위치의 값을 반환하는 함수// 근데 이거 mVec[i]와 동일하잖아 역참조가 아닌 참조에는 변환도 시키지 않으니까 굳이 안써도 되지 않음? 복잡하기만 한데
	void Print();
	void SetSize(int size) { mSize = size; };//이렇게 짧은 함수들은 스코프 연산자를 사용하지 않아도 된다. ->inline함수
	int Size() { return mSize; };

	void ScalarMul(double value);
	CVector Add(CVector cv);//두개를 더할 거지만 내 자신이 있으므로 내거에 cv를 더하는 의미로 파라미터가 하나이다.//(현재)v3=v1.Add(v2) -> (개선) v3=v1+v2(가능하면)연산자 재정의
};

void CVector::ScalarMul(double value) {
	for (int i = 0; i < mSize; i++)
		mVec[i] *= value;
}

CVector CVector::Add(CVector cv) {//스택에 result가 더 올라가야해서 효율적이지 못하다. 해결하려면 포인터를 사용하면 된다.
	CVector result;
	//예외처리를 이렇게 말고 그냥 크기가 큰만큼 size를 잡고 두개를 더하는 메쏘드를 짜도 될듯.
	if (cv.Size() != mSize) {//cv.Msize로 안하고 cv.Size를 하는 이유? 왠만하면 private멤버변수는 직접 참조를 안하는 듯. 
		printf("Vector size mismatch!\n");
		return result;//무의미한 값
	}
	result.SetSize(mSize);
	for (int i = 0; i < mSize; i++)
		result.SetValue(i, mVec[i] + cv.Get_Value(i));//마찬가지로 직접참조인 cv.mVec[i] 대신 cv.Get_Value(i)
	
	return result;
}
CVector::CVector(int size, double arr[]) {//생성자는 리턴값이 없다.
	if (size > MAX_SIZE)
		printf("입력한 사이즈가 너무 큽니다.");
	mSize = size;
	for (int i = 0; i < size; i++)
		mVec[i] = arr[i];
}
void CVector::SetValue(int nPos, double value) {
	if (nPos >= mSize) {
		printf("Range error");
		return;
	}
	mVec[nPos] = value;//mVec은 private 이지만 SetValue함수가 private이기 때문에 참조할 수 있다.
}

double CVector::Get_Value(int nPos) {
	if (nPos >= mSize) {
		printf("Range error");
		return -1.0;
	}
	return mVec[nPos];
}

//::스코프 연산자
void CVector::Print() {  // (리턴타입)(클래스명)::(멤버함수이름)(...) {}
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
	//CVector : 클래스명 (int, double)
	//my_vector : 변수(인스턴스, 객체(object))

	printf("Start class_test()...\n");
	
	//my_vector.mSize = 3;
	my_vector.SetValue(0, 1.0);
	my_vector.SetValue(1, 2.0);
	my_vector.SetValue(2, 3.0);
	//my_vector.SetValue(3, 4.0);

	//CVector_Print(my_vector);
	my_vector.Print();

	printf("Start class_test(): 2nd test...\n");

	CVector vec2;//기본 생성자
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