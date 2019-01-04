#include <iostream>




using namespace std;


#if 0
class B {
    friend class A;
protected:
    B(int v): b(v) {
        cout << "init B" << endl;
    }
protected:
    int getValue() const {
        cout << "B getValue" << endl;
        return b;
    }
private:
    int b;
};


class A {
public:
    A(int v, int v1): a(v), bb(v1) {
        cout << "init A" << endl;
    } 
    int getValue() const {
        cout << "A getValue" << endl;
        ////return bb.getValue() * 2 + a;
        return bb.b * 2 + a;
    }

private:
    int a;
    B bb;
};

int main()
{
    class A val(3, 5);
    cout << val.getValue() << endl;
}
#else
class B {
    friend class A;//// can access b
protected:
    B(int v): b(v) {
        cout << "init B" << endl;
    }
protected:
    int getValue() const {
        cout << "B getValue" << endl;
        return b;
    }
private:
    int b;
};


class A: public B {
public:
    A(int v, int v1): a(v), B(v1) {
        cout << "init A" << endl;
    } 
    int getValue() const {
        cout << "A getValue" << endl;
        ////return bb.getValue() * 2 + a;
        return b * 2 + a;
    }

private:
    int a;
};

int main()
{
    class A val(3, 5);
    cout << val.getValue() << endl;
}
#endif