#include "SharedPointer.h"


class MyClass {
    int value;

public:
    MyClass(): value(0) {}

    MyClass(int value): value(value) {}

    ~MyClass() {
        std::cout << "Call Destructor" << std::endl;
    }

    void ShowValue() {
        std::cout << "Value: " << value << std::endl;
    }
};

void testOriginalSharedPtr() {
    std::cout << "Original shared_ptr:" << std::endl;

    std::shared_ptr<MyClass> x_ptr(new MyClass(42));
    std::shared_ptr<MyClass> y_ptr(new MyClass(13));
    x_ptr->ShowValue();
    y_ptr->ShowValue();

    y_ptr = x_ptr;
    x_ptr->ShowValue();
    y_ptr->ShowValue();
}

void testMySharedPtr() {
    std::cout << "My shared_ptr:" << std::endl;

    SharedPointer<MyClass> x_ptr(new MyClass(42));
    SharedPointer<MyClass> y_ptr(new MyClass(13));
    x_ptr->ShowValue();
    y_ptr->ShowValue();

    y_ptr = x_ptr;
    x_ptr->ShowValue();
    y_ptr->ShowValue();
}

int main() {
    testOriginalSharedPtr();
    std::cout << std::endl;
    testMySharedPtr();
    return 0;
}