// Copyright (c) 2025 Him
// Author: Him
// Date: 2025-08-19
// DEMO PROGRAM FOR
// class 的三种继承方式

#include <iostream>
#define PUBLIC_DATA_DEFAULT 100

class Base {
public:
    int public_data = PUBLIC_DATA_DEFAULT; 
    void public_cout() { std::cout << "Base public cout accessed.\n"; }
protected:
    int protected_data; 
    void protected_cout() { std::cout << "Base protected cout accessed.\n"; }
private:
    int private_data; 
    void private_cout() { std::cout << "Base private cout accessed.\n"; }
};

// Public Inheritance
class Derived : public Base {
public:
    int public_data = 1000;         // define a varible the same name as Base's
    // 在子类中访问基类成员
    void accessBaseMembers() {
        std::cout << "--- Inside Derived::accessBaseMembers() ---\n";

        // 1. access public member
        public_data = 10; 
        std::cout << "  Derived accessed Base's public_data: " << public_data << "\n";
        public_cout();   

        // 2. access protected member
        protected_data = 20; // OK
        std::cout << "  Derived accessed Base's protected_data: " << protected_data << "\n";
        protected_cout();

        // 3. access private member ------ not allowed
        // private_data = 30;                      // complie error
        // private_cout();                         // complie error
        std::cout << "  // Derived cannot directly access Base's private members.\n";
    }
protected:     
private:
};

class Derived2 : protected Base {
public:
    void accessBaseMembers() {
        std::cout << "--- Inside Derived2::accessBaseMembers() ---\n";

        // 1. access public member
        public_data = 10; 
        std::cout << "  Derived2 accessed Base's public_data: " << public_data << "\n";
        public_cout();   

        // 2. access protected member
        protected_data = 20; // OK
        std::cout << "  Derived2 accessed Base's protected_data: " << protected_data << "\n";
        protected_cout();

        // 3. access private member ------ not allowed
        // private_data = 30;                      // complie error
        // private_cout();                         // complie error
        std::cout << "  // Derived2 cannot directly access Base's private members.\n";

        // 4. access same name members
        std::cout << "  Derived2's public_data: " << public_data << "\n";
        std::cout << "  Derived2's Base's public_data: " << Base::public_data << "\n";
    }
private: 
    int public_data = 114514;               // 和基类同名函数无论定义,内部访问都默认指向自己的
};

int main() {
    ////////////////////// Demonstrating Public Inheritance /////////////////////////////
    std::cout << "--- Demonstrating Public Inheritance ---\n";
    Derived derived; 
    std::cout << " Calling derived.public_cout(); : ";
    derived.public_cout();
    // 如果子类有和父类同名的变量,则默认访问的是子类自己的该变量
    std::cout << " derived.public_data: " << derived.public_data << "\n";
    std::cout << " derived.base::public_data : " << derived.Base::public_data << "\n";

    ////////////////////// Demonstrating protected Inheritance /////////////////////////////
    std::cout << "--- Demonstrating Protected Inheritance ---\n";
    Derived2 derived2;
    // public & protected 中的属性被继承到子类的protected中,无法外部访问
    // derived2.public_cout();                             // Compile error
    // derived2.public_data = 100;                         // Compile error 
    derived2.accessBaseMembers();                          // 通过子类的成员函数访问基类成员

    return 0;
}
