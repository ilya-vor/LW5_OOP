#include <iostream>
#include <memory>
using namespace std;

class MyClass {
public:
    MyClass() {
        std::cout << "[MyClass()]" << std::endl;
    }

    ~MyClass() {
        std::cout << "[~MyClass()]" << std::endl;
    }

    void doSomething() {
        std::cout << "Doing something..." << std::endl;
    }
};

void functionWithUniquePtr(std::unique_ptr<MyClass> ptr) {
    ptr->doSomething();
    // ptr выйдет из области видимости здесь и вызовется деструктор
}



std::shared_ptr<MyClass> functionWithSharedPtr() {
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>();
    ptr->doSomething();
    return ptr;
    // ptr все еще в области видимости, потому что это shared_ptr
    // Он останется в памяти, пока на него ссылается хотя бы один другой shared_ptr
}

int main() {
    // Использование unique_ptr
    std::cout << "Использование unique_ptr" << std::endl;
    {
        std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>();
        uniquePtr->doSomething();
        // uniquePtr выйдет из области видимости здесь и вызовется деструктор
    }

    std::cout << "Использование shared_ptr" << std::endl;

    // Использование shared_ptr
    {
        std::shared_ptr<MyClass> sharedPtr = functionWithSharedPtr();
        sharedPtr->doSomething();
        // sharedPtr выйдет из области видимости здесь, но объект MyClass останется,
        // потому что на него все еще есть ссылка из main()
    }

    std::cout << "Использование shared_ptr с передачей в функцию" << std::endl;

    // Использование shared_ptr с передачей в функцию
    {
        std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
        functionWithUniquePtr(std::move(sharedPtr));
        // sharedPtr не доступен здесь, так как мы его передали в функцию functionWithUniquePtr
    }

    std::cout << "End" << std::endl;

    return 0;
}
