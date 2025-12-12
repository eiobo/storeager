// Copyright (c) 2025 Him
// Author: Him
// Date: 2025-08-19
// DEMO PROGRAM FOR
// 类的友元函数

/*
题目：设计一个简单的“配置管理器”类 ConfigManager，该类用于存储和管理一对配置项（键值对）。
要求：

ConfigManager 类:
私有成员:
    const std::string key: 配置项的键（名称），一旦初始化，不可改变。
    int value: 配置项的值。
构造函数:
    ConfigManager(const std::string& configKey, int initialValue)
    必须使用初始化列表为 key 和 value 成员提供初始值。key 成员是一个 const 成员，因此必须通过初始化列表初始化。
成员函数:
    int getValue() const: 返回当前的 value。此函数是 const 成员函数。
    void updateValue(int newValue): 更新 value 的值。
友元函数:
    void resetConfigValue(ConfigManager& config, int defaultValue): 
        此函数被声明为 ConfigManager 类的友元。
        它接收一个 ConfigManager 对象的非 const 引用。
        该函数的主要作用是直接修改传入的 ConfigManager 对象的 value 成员为其提供的 defaultValue。
main 函数:
    创建一个 ConfigManager 对象，例如，键为 "timeout"、初始值为 300。
    使用 getValue() 成员函数显示初始值。
    调用 updateValue() 成员函数修改值。
    再次使用 getValue() 显示更新后的值。
    使用友元函数 resetConfigValue() 来重置配置的值，例如重置为 0。
    最后，再次使用 getValue() 显示重置后的值，并打印 key 的值（可以直接访问，因为友元函数可以访问私有成员）。

你的任务是：
    编写 ConfigManager 类的定义（包括成员变量、构造函数、成员函数和友元声明），
    以及 resetConfigValue 友元函数的实现。同时，编写 main 函数来测试这些功能。

关键点提示：
const 成员变量 key 必须在构造函数的初始化列表中进行初始化。
友元函数的声明在类内部，定义在类外部。
友元函数可以访问类的私有成员，但它不能绕过变量本身的 const 限制（在这里 key 是 const 的，但 value 是可变的）。
请尝试编写代码实现上述要求。
*/

#include <bits/stdc++.h>

using namespace std;

class ConfigManager {
private:
    const string key;       // 配置项的key，一旦初始化不能改变，且是const成员，必须只能通过初始化列表初始化
    int val;
public:
    ConfigManager(const string& configKey, int initval) : key(configKey), val(initval) {}
    inline int getValue() const;
    inline void updateValue(int newVal);
    inline friend void ResetConfigVal(ConfigManager& config, int newVal);
};

inline void ResetConfigVal(ConfigManager& config, int newVal) {
    cout << "Resetting Config : " << " {Key} : " << config.key << " {val} : " << config.val << endl;
    config.val = newVal;
    cout << "After Resetting Config : " << " {Key} : " << config.key << " {val} : " << config.val << endl;
}

inline int ConfigManager::getValue() const {
    return this->val;
}

inline void ConfigManager::updateValue(int newVal) {
    this->val = newVal;
}

int main() {
    ConfigManager cfm("timeout", 300);
    cout << "cfm.getValue() : " << cfm.getValue() << endl;
    cfm.updateValue(100);
    cout << "cfm.getValue() : " << cfm.getValue() << endl;
    ResetConfigVal(cfm, 300);
    return 0;
}