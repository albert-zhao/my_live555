#include <iostream>




using namespace std;




#if 0
class A {
public:
    A(int val): a(val) {
        cout << "init A" << endl;
    }
    int getValue() const {
        return a;
    }
private:
    int a;
};

A aa(3);

class B {
public:
    B(int v): b(v) {
        cout << "init B" << endl;
    }
    int getValue() const {
        return aa.getValue() * b;
    }
private:
    int b;
};

int main()
{
    B bb(4);
    cout << bb.getValue() << endl;
}
#else


class C {
public:
    C(int val): c(val) {
        cout << "class C init finished" << endl;
    }

    bool operator==(const C &v) {
        cout << "class C operator==" << endl;
        return c == v.c;
    }

private:
    int c;
};


class A: public C {
public:
    A(int val): C(val) {
        cout << "init A" << endl;
    }
};

A aa(3);

class B : public C {
public:
    B(int v): C(v) {
        cout << "init B" << endl;
    }
};

int main()
{
    B bb(3);
    cout << (bb == aa) << endl;
}
#endif