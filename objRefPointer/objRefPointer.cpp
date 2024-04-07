#include <iostream>
using namespace std;
class Base {
public:
    int id = rand() % 100;
    Base() { printf("[Base()] id = %d\n", id); }
    Base(const Base *b): id(b->id) { printf("[Base(const Base *b)] id = %d\n", id); }
    Base(const Base &b): id(b.id) { printf("[Base(const Base &b)] id = %d\n", id); }
    ~Base() { printf("[~Base()] id = %d\n", id); }
};
class Desc: public Base {
public:
    Desc() { printf("[Desc()] id = %d\n", id); }
    Desc(const Desc* d): Base(d) { printf("[Desc(const Desc* d)] id = %d\n", id); }
    Desc(const Desc& d): Base(d) { printf("[Desc(const Desc &b)] id = %d\n", id); }
    ~Desc() { printf("[~Desc()] id = %d\n", id); }
};

void func1(Base  obj) { printf("[func1(Base obj)]\n"); }
void func2(Base* obj) { printf("[func1(Base* obj)]\n"); }
void func3(Base& obj) { printf("[func1(Base& obj)]\n"); }

Base func1() { Base p; return p; }
Base* func2() { Base p; return &p; }
Base& func3() { Base p; return p; }
Base func4() { Base* p = new Base(); return *p; }
Base* func5() { Base* p = new Base(); return p; }
Base& func6() { Base* p = new Base(); return *p; }

int main()
{
    //
    // Механизмы передачи объектов как параметров в функции
    //
    {
        Base obj; //[Base()] id = 1 
        func1(obj);
        //[Base(const Base & b)] id = 1 Создался безымянный объект, скопировал obj и передался в функцию
        //[func1(Base obj)]
        //[~Base()] id = 1 Удалился скопированный объект
    }//[~Base()] id = 1

    printf("\n\nfunc2(&obj)\n");
    {
        Base obj; //[Base()] id = 7
        func2(&obj); //[func1(Base * obj)]
    }//[~Base()] id = 7

    printf("\n\nfunc3(obj)\n");
    {
        Base obj; //[Base()] id = 4
        func3(obj); //[func1(Base & obj)]  
    }//[~Base()] id = 4

    printf("\n\nfunc1(d)\n");
    {
        Desc d;
        //[Base()] id = 0
        //[Desc()] id = 0
        func1(d);
        //[Base(const Base & b)] id = 0  Создался безымянный объект, скопировал d (обрезанную до Base) и передался в функцию
        //[func1(Base obj)]
        //[~Base()] id = 0 Удалился скопированный объект
    } //[~Desc()] id = 0 [~Base()] id = 0

    printf("\n\nfunc2(&d)\n");
    {
        Desc d;
        //[Base()] id = 9
        //[Desc()] id = 9
        func2(&d); //[func1(Base * obj)]
    } //[~Desc()] id = 9 [~Base()] id = 9

    printf("\n\nfunc3(d)\n");
    {
        Desc d;
        //[Base()] id = 4
        //[Desc()] id = 4
        func3(d); //[func1(Base & obj)]
    } //[~Desc()] id = 4 [~Base()] id = 4

    //
    // Механизмы возврата объектов из функции
    //
    printf("\n\nfunc1()\n");
    {
        Base b; //[Base()] id = 78
        b = func1(); //[Base()] id = 58 [~Base()] id = 58
    }//[~Base()] id = 58

    printf("\n\nfunc2()\n");
    {
        Base* b;
        b = func2();
        //[Base()] id = 62
        //[~Base()] id = 62 
        //delete b; - ошибка, обьект уже удален
    }

    printf("\n\nfunc3()\n");
    {
        Base b; //[Base()] id = 5
        b = func3();
        //[Base()] id = 45
        //[~Base()] id = 45
    }//[~Base()] id = 45
    
    printf("\n\nfunc4()\n");
    {
        Base b; // [Base()] id = 81
        b = func4();
        //[Base()] id = 27
        //[Base(const Base & b)] id = 27
        //[~Base()] id = 27
    }//[~Base()] id = 27

    printf("\n\nfunc5()\n");
    {
        Base* b;
        b = func5();//[Base()] id = 27
        delete b;//[~Base()] id = 27
    }
    
    printf("\n\nfunc6()\n");
    {
        Base b;//[Base()] id = 61
        b = func6();//[Base()] id = 91
    }//[~Base()] id = 91
}
