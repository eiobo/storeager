// Copyright (c) 2025 Him
// Author: Him
// Date: 2025-08-19

#include <bits/stdc++.h>


class Father {
public:
    Father() {std::cout << " ---Father() ! " << std::endl;}
    Father(int money_, std::string wifename_) : money(money_), wifename(wifename_) {std::cout << " ---Father(int money_) ! " << std::endl;}  
    ~Father() {std::cout << " ---~Father() ! " << std::endl;}

    // getters
    void GetMoney() {std::cout << " Father::money is : " << money << std::endl;}
protected:
    uint32_t money = 10000;
private:
    std::string wifename;
};

class Son : public Father {
public:
    // Son() = default;
    Son() {std::cout << " ---Son() ! " << std::endl;}
    Son(std::string wifename_, int height_) : wifename(wifename_), height(height_){std::cout << " ---Son(std::string wifename_) ! " << std::endl;}
    ~Son() {std::cout << " ---~Son() ! " << std::endl;}
private:
    std::string wifename;
    int height;
    int weight;

};

void showMoney(Father in) {
    in.GetMoney();
}



int main() {
    ///////////////////// 1. 子类父类的构造析构顺序  //////////////////////
    // Son s1;                  // 调用编译器默认分配的构造函数
    Son s2("tiger", 170);            // 调用参数构造函数

    //////////////////// 2. 父类指针可以直接指向子类 /////////////////////
    Father* fptr = &s2;         // 父类指针可以指向子类对象
    fptr->GetMoney();           // 可以通过指向子类的父类指针访问父类方法

    Son* sptr = &s2;
    std::cout << "sptr : " << sptr << std::endl;    // 输出和fptr一样的值

    //////////////////// 3. 子类属性在内存中的排布 /////////////////////
    // ↓： 对象首地址
    // ------------------------------------------------------------------
    // |  Father  | string : wifename |  int : height |  int : weight   |
    // ------------------------------------------------------------------
    std::cout << "fptr : " << fptr << std::endl;
    std::cout << "*fptr : " << *(uint32_t*)fptr << std::endl;           // 子类起始地址
    std::cout << "sizeof(Father) : " << sizeof(Father) << std::endl;    
    std::cout << "fptr+1 : " << fptr+1 << std::endl;                    // 子类属性起始地址
    std::cout << "*(std::string*)(fptr+1): " << *(std::string*)(fptr+1) << std::endl;   // 输出 tiger
    std::cout << *((int*)((std::string*)(fptr+1) + 1)) << std::endl;    // 输出 170
    // std::cout << alignof(std::string) << std::endl;      // 输出：8
    // std::cout << alignof(Father) << std::endl;           // 输出：8

    //////////////////// 4. 兼容性: 子类可以兼容父类 /////////////////////
    showMoney(s2);                  // 子类对象可以直接当作父类来使用
    Father farther = s2;            // 子类对象可以直接给父类对象赋值
    showMoney(farther);

    Father farther2(s2);            // 父类对象可以通过拷贝构造子类对象初始化
    showMoney(farther2);            

    Father& s2_ref = s2;            // 父类引用可以引用子类对象
    s2_ref.GetMoney();              

    return 0;
}