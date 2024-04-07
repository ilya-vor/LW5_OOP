#include <iostream>
using namespace std;

class Object {
public:
    virtual bool isA(string name) {
        printf("[Object::is_it(string name)]\n"); 
        return "Object" == name; 
    }
    void say_your_name() { printf("[Object] Object\n"); }
    virtual ~Object() { printf("[virtual ~Object()]\n"); }
};

class Point: public Object {
private: 
    int x, y;
public:
    Point() : x(rand() % 100), y(rand() % 100){}
    bool isA(string name) override {
        printf("[Point::is_it(string name)]\n"); 
        return "Point" == name || Object::isA(name);
    }
    void say_your_name() { printf("[Point] Point\n"); }
    void say_your_center() { printf("[Point] x = %d, y = %d\n", x, y); }
    double get_distance_from_ref(const Point& p) { return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)); }
    double get_distance_from_obj(const Point p) { return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)); }
    double get_distance_from_adress(const Point* p) { return sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y)); }
    ~Point() override { printf("[~Point()]\n"); }
};

class ColoredPoint: public Point {
private:
    int color;
public:
    ColoredPoint() : Point(), color(rand() % 256) {}
    bool isA(string name) override {
        printf("[ColoredPoint::is_it(string name)]\n"); 
        return "ColoredPoint" == name || Point::isA(name);
    }
    void say_your_name() { printf("[ColoredPoint] ColoredPoint\n"); }
    void say_your_color() { printf("[ColoredPoint::say_your_color()] color = %d\n", color); }
    ~ColoredPoint() override { printf("[~ColoredPoint()]\n"); }
};

int main()
{
    setlocale(NULL, "RU");

    // Определения перекрываемых методов
    cout << "\n Определения перекрываемых методов \n";
    {
        ColoredPoint cp;
        cp.say_your_name();   // Вызов перекрытого метода
        cp.say_your_center(); // Вызов наследуемого метода
    }

    // Определения виртуальных методов, в т.ч. деструкторов 
    cout << "\n Определения виртуальных методов, в т.ч. деструкторов \n";
    Object* o = new Point(); // Помещаем указатель в переменную-указатель на объект 
                             // предка чтобы увидеть зачем делать методы виртуальными

    o->say_your_name(); // Вызов базового метода
    o->isA("Point");    // Вызов виртуального метода
    delete o;

    // Реализация проверки на принадлежность некоторому классу
    cout << "\n Реализация проверки на принадлежность некоторому классу \n";
    Object* o1 = new Point();
    cout << o1->isA("Object") << endl;
    cout << o1->isA("Point") << endl;        // Демонстрация реализации проверки 
    cout << o1->isA("ColoredPoint") << endl; // на принадлежность некоторому классу
    delete o1;

    // Реализация безопасного приведения типов (dynamic_cast)  
    cout << "\n Реализация безопасного приведения типов (dynamic_cast) \n";
    Object* o2 = new ColoredPoint();
    ColoredPoint* cp = dynamic_cast<ColoredPoint*>(o2);
    if (cp) { cp->say_your_color(); }
    delete o2;
    cp = nullptr;

    // Реализация безопасного приведения типов (вручную) 
    cout << "\n Реализация безопасного приведения типов (вручную) \n";
    Object* o3 = new ColoredPoint();
    if (o3->isA("ColoredPoint")) { ((ColoredPoint*) o3)->say_your_color(); }
    delete o3;

    // Передача объектов как параметров в функции и возвращения объектов 
    // как результата из функции, контроль их жизненного цикла

    // Смотреть objRefPointer.cpp


}

