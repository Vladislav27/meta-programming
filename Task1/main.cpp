#include "ClassC.h"

class D  : public Interface {
public:
    void read(std::string data="") {}
    void write(std::string data="") {}
};

void test_proxy() {
    D obj;

    ClassB b1(obj);
    ClassC<Role::Proxy> proxy(b1);

    ClassA A;

    A.read(proxy);
    std::cout << std::endl;
}

void test_mediator() {
    D obj;

    ClassB b1(obj);
    ClassB b2(obj);
    ClassB b3(obj);

    ClassC<Role::Mediator> mediator;

    mediator.add(b1);
    mediator.add(b2);
    mediator.add(b3);

    ClassA A;

    A.read(mediator);
    std::cout << std::endl;
}

void test_observer() {
    ClassA a1;
    ClassA a2;
    ClassC<Role::Observer> observer;
    observer.add(a1);
    observer.add(a2);

    ClassB B(observer);

    B.write("NEW_DATA");
    std::cout << std::endl;
}

int main() {
    test_mediator();
    test_proxy();
    test_observer();
    return 0;
}