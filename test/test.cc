#include <iostream>
using namespace std;

class A {
public:
	A(int b): a(b) {}
	virtual void print() { cout << "a = " << endl; }
	int a;
};

class B: public A {
public:
	B(int b, int cc): A(b), c(cc) {}
	virtual void print() { cout << "a = " << a << ", c = " << c << endl;}
	int c;
};

int main()
{
	B *bp = new B(3, 4);
	A *ap = bp;
	cout << "bp =" << bp << endl;
	cout << "ap =" << ap << endl;
	cout << "size ap =" << sizeof ap << endl;

	cout << "size *bp = " << sizeof *bp << endl;
	cout << "size *ap =" << sizeof *ap << endl;
	ap->print();

	delete bp;

	return 0;
}
