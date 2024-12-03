# 构造函数 析构函数 虚函数 纯虚函数



1. **构造函数和析构函数**：
   - 构造函数确实不能被“重写”（在面向对象术语中，我们通常不说重写构造函数，因为构造函数与类的实例化直接相关，并且每个类都有自己的构造函数）。每个类都有自己特定的构造函数，用于初始化该类的对象。
   - 析构函数同样不是“重写”的对象。然而，当基类有一个虚析构函数时，派生类的析构函数通常会被定义（即使它只是简单地调用基类的析构函数），以确保通过基类指针删除派生类对象时能够正确调用析构链。但这里我们不说“重写”析构函数，而是说“派生类提供了自己的析构函数实现”。

2. **虚函数**：
   - 虚函数可以在派生类中被重写（也称为覆盖）。这意味着派生类可以提供一个与基类虚函数具有相同签名（返回类型、函数名和参数列表）的函数，从而改变该函数的行为。

3. **纯虚函数**：
   - 纯虚函数是必须在派生类中被重写的函数。它们在基类中被声明为`= 0`，表示基类不提供该函数的实现。任何试图实例化包含纯虚函数的类的尝试都将导致编译错误。因此，包含纯虚函数的类通常是抽象基类，它们不能被直接实例化，只能作为其他类的基类使用。

综上所述，您的说法“构造函数和析构函数不需要重写，虚函数可以重写，纯虚函数必须重写”在核心意义上是正确的，但需要注意我们通常不使用“重写”来描述构造函数和析构函数的行为，因为这两个概念与类的实例化和资源清理直接相关，并且每个类都有自己独特的实现方式。对于虚函数和纯虚函数，重写（或覆盖）是面向对象编程中多态性的关键部分。


纯虚函数是在基类中声明但没有实现的函数，它强制要求任何从该基类继承的派生类都必须提供该函数的实现。包含纯虚函数的类被称为抽象基类，它们不能被直接实例化。

以下是将纯虚函数添加到您的代码中的示例：

```cpp
#include <iostream>
using namespace std;

// 基类Base，现在包含一个纯虚函数pureVirtualFunction
class Base {
public:
    // 构造函数
    Base() { cout << "Base Constructor\n"; }

    // 虚析构函数
    virtual ~Base() { cout << "Base Destructor\n"; }

    // 虚函数
    virtual void show() const { 
        cout << "Base show()\n"; 
    }

    // 纯虚函数声明
    virtual void pureVirtualFunction() const = 0;
};

// 派生类Derived，从Base继承并实现了pureVirtualFunction
class Derived : public Base {
public:
    // 派生类的构造函数
    Derived() { cout << "Derived Constructor\n"; }

    // 派生类的析构函数
    ~Derived() { cout << "Derived Destructor\n"; }

    // 重写基类的虚函数
    void show() const override {
        cout << "Derived show()\n";
    }

    // 实现基类的纯虚函数
    void pureVirtualFunction() const override {
        cout << "Derived pureVirtualFunction()\n";
    }
};

int main() {
    // 由于Base包含纯虚函数，因此不能直接实例化Base对象
    // Base obj; // 这行代码会导致编译错误

    cout << "== Dynamic Object ==\n";
    Base* ptr = new Derived(); // 动态创建派生类对象，通过基类指针管理
    ptr->show();               // 动态绑定，调用派生类的show函数
    ptr->pureVirtualFunction(); // 调用派生类实现的纯虚函数
    delete ptr;                // 调用派生类和基类的析构函数
    return 0;
}
```

在这个修改后的代码中，`Base`类现在包含一个纯虚函数`pureVirtualFunction`，它在`Base`类中被声明为`= 0`。`Derived`类从`Base`类继承，并提供了`pureVirtualFunction`的实现。因此，`Derived`类可以被实例化，而`Base`类则不能。

在`main`函数中，我们创建了一个指向`Derived`对象的`Base`类指针，并通过该指针调用了`show`函数和`pureVirtualFunction`函数。由于多态性，这些调用将解析为`Derived`类中的相应实现。最后，我们删除了通过`new`操作符分配的对象，这导致首先调用`Derived`类的析构函数，然后调用`Base`类的析构函数。