// Copyright (c) 2025 Him
// Author: Him
// Date: 2025-08-19
// DEMO program： 函数重载，（虚）函数覆写，函数重定义

#include <bits/stdc++.h>

class Base {
public:
    Base() = default;                              // 编译器默认给一个构造函数
    Base(int any_) {}                              // 带参构造函数
    // 👇 三个show都是重载关系
    void Show();
    void Show(int i);
    virtual void Show(int i, int j) /*= 0*/;       // 一旦有纯虚函数，就说明是抽象类，无法实例化
};

void Base::Show() {std::cout << "--- Call Base::Show() " << std::endl;}
void Base::Show(int i) {std::cout << "--- Call Base::Show(int i) " << std::endl;}
void Base::Show(int i, int j) {std::cout << "--- Call virtual Base::Show(int i, int j) " << std::endl;}


class Derived : public Base {
public:
    // using Base::Show;        // 这条指令将Show改回默认基类的实现
    // 👇 三个show都是重载关系
    // void Show()和基类中的Show是重定义关系，在子类中定义了父类中同名函数，父类的就无法访问，除非用Base::
    void Show() {std::cout << "--- Call Derived::Show() " << std::endl;}
    void Show(char a);          // 子类覆盖父类同名函数，通过子类对象调用的默认是子类下的同名函数，父类被hiding
    void Show(int i, int j) override;     // 与父类中的void Show(int i, int j)是覆写关系
};

void Derived::Show(int i, int j) {std::cout << "--- Call virtual Derived::Show(int i, int j) " << std::endl;}
void Derived::Show(char a) {std::cout << "--- Call Derived::Show(char a) " << std::endl;}

int main() {
    ////////////////////////////////// 1. 函数的重载 //////////////////////////////////////
    // 同一作用域下的函数名重载
    Base* bptr = new Base;          // 可以用基类指针
    Base bobj;                      // 可以用基类对象
    bobj.Show();
    bobj.Show(100, 200);
    bobj.Show(199);
    bptr->Show();
    bptr->Show(100,200);
    bptr->Show(199);
    std::cout << " ------------------------------------------- " << std::endl;

    ////////////////////////////////// 2. 函数重写 + 函数重定义 ////////////////////////////
    Derived dobj;
    dobj.Show('a');       // 派生类对象调用
    dobj.Show(1, 100);    // 派生类对象调用重载后的函数
    std::cout << " ------------------------------------------- " << std::endl;

    ///////////////////////////////// 3. 基类指针指向派生类对象 ///////////////////
    Base* bp = &dobj;     // 基类指针指向派生类的对象
    bp->Show();           // 基类的show
    bp->Show(1, 100);     // 根据实际类型选择了派生类的函数
    bp->Show(199);
    
    return 0;
}