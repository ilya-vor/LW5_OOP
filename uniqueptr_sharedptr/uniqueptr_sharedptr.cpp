#include <iostream>
#include <memory>
using namespace std;

class MyClass {
public:
    MyClass() {
        cout << "[MyClass()]" << endl;
    }

    ~MyClass() {
        cout << "[~MyClass()]" << endl;
    }

    void doSomething() {
        cout << "Doing something..." << endl;
    }
};

void functionWithUniquePtrDelete(unique_ptr<MyClass> ptr) {
    ptr->doSomething();
    // ptr выйдет из области видимости здесь и вызовется деструктор
}

unique_ptr<MyClass> functionWithUniquePtrNoDelete(unique_ptr<MyClass> ptr) {
    ptr->doSomething();
    return ptr;
}

shared_ptr<MyClass> functionWithSharedPtr(shared_ptr<MyClass> ptr) {
    ptr->doSomething();
    return ptr;
    // ptr все еще в области видимости, потому что это shared_ptr
    // Он останется в памяти, пока на него ссылается хотя бы один другой shared_ptr
}

int main() {

    setlocale(NULL, "RU");

    // Использование unique_ptr
    cout << "Использование unique_ptr" << endl;
    {
        unique_ptr<MyClass> uniquePtr = make_unique<MyClass>();
        uniquePtr->doSomething();
        // uniquePtr выйдет из области видимости здесь и вызовется деструктор
    }

    unique_ptr<MyClass> uniquePtr = make_unique<MyClass>();
    uniquePtr = functionWithUniquePtrNoDelete(move(uniquePtr)); //не удалится, так как uniquePtr возвращаем
                                                                //(передаем функции ответственность за время жизни объекта
                                                                //и забираем ответственность при выходе из функции)

    functionWithUniquePtrDelete(move(uniquePtr)); //удалится, так как uniquePtr не возвращаем 
                                                  //(передаем функции ответственность за время жизни объекта
                                                  //и не забираем ответственность при выходе из функции)

    cout << "Использование shared_ptr" << endl;

    // Использование shared_ptr
    shared_ptr<MyClass> sharedPtr1;
    {
        shared_ptr<MyClass> sharedPtr = make_shared<MyClass>();
        sharedPtr1 = sharedPtr;
        sharedPtr->doSomething();
        // sharedPtr выйдет из области видимости здесь, и на обьект MyClass будет 1 ссылка, поэтому обьект не удалится
    } 

    cout << "Использование shared_ptr с передачей в функцию" << endl;

    // Использование shared_ptr с передачей в функцию
    {
        functionWithSharedPtr(move(sharedPtr1));
        //Мы передали sharedPtr в функцию functionWithSharedPtr и объект удалился после вызова функции, так как на него
        //не осталось ссылок после завершения функции
    }

    cout << "End" << endl;
    
    return 0;
}
