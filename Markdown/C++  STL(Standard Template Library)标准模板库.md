

---
layout: post
title:  C++ std(Standard Template Library) 标准模板库
date:   2023-03-02 16:30:10 +0300
image:  c++封面.png
tags:   study  c++

---

 

### 1 [STL](https://so.csdn.net/so/search?q=STL&spm=1001.2101.3001.7020)基础

STL 组成结构 (6个)

| STL的组成  | 含义                                                         |
| :--------- | :----------------------------------------------------------- |
| 容器       | 一些封装数据结构的模板类，例如 vector 向量容器、list 列表容器等。 |
| 算法       | STL 提供了非常多（大约 100 个）的数据结构算法，它们都被设计成一个个的模板函数，这些算法在 std 命名空间中定义，其中大部分算法都包含在头文件 中，少部分位于头文件 中。 |
| 迭代器     | 在 C++ STL 中，对容器中数据的读和写，是通过迭代器完成的，扮演着容器和算法之间的胶合剂。 |
| 函数对象   | 如果一个类将 () 运算符重载为成员函数，这个类就称为函数对象类，这个类的对象就是函数对象（又称仿函数）。 |
| 适配器     | 可以使一个类的接口（模板的参数）适配成用户指定的形式，从而让原本不能在一起工作的两个类工作在一起。值得一提的是，容器、迭代器和函数都有适配器。 |
| 内存分配器 | 为容器类模板提供自定义的内存申请和释放功能，由于往往只有高级用户才有改变内存分配策略的需求，因此内存分配器对于一般用户来说，并不常用。 |

C++ STL头文件 (13个)  
<[iterator](https://so.csdn.net/so/search?q=iterator&spm=1001.2101.3001.7020)\> <functional> <vector> <deque> <list> <queue> <stack> <set> <map> <algorithm> <numeric> <memory> <utility>

STL [容器](https://so.csdn.net/so/search?q=%E5%AE%B9%E5%99%A8&spm=1001.2101.3001.7020)种类和功能

| 容器种类 | 功能  |
| :---------------- | :---------------------------------------------------------------------- |
| 序列容器 | 主要包括 vector 向量容器、list 列表容器以及 deque 双端队列容器。之所以被称为序列容器，是因为元素在容器中的位置同元素的值无关，即容器不是排序的。将元素插入容器时，指定在什么位置，元素就会位于什么位置。 |
| 排序容器 | 包括 set 集合容器、multiset多重集合容器、map映射容器以及 multimap 多重映射容器。排序容器中的元素默认是由小到大排序好的，即便是插入元素，元素也会插入到适当位置。所以关联容器在查找时具有非常好的性能。 |
| 哈希容器 | C++ 11 新加入 4 种关联式容器，分别是 unordered\_set 哈希集合、unordered\_multiset 哈希多重集合、unordered\_map 哈希映射以及 unordered\_multimap 哈希多重映射。和排序容器不同，哈希容器中的元素是未排序的，元素的位置由哈希函数确定。 |

| 容器                                          | 区别                                                         | 使用建议                                                     |
| --------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1. std::vector：                              | - 底层实现为动态数组，可以高效地随机访问元素。<br/>   - 支持快速的尾部插入和删除操作。<br/>   - 在需要频繁执行插入和删除操作时，效率较低。 | 需要随机访问、频繁进行插入和删除操作，可以选择 std::vector； |
| 2. std::list：                                | - 底层实现为双向链表，可以高效地在任意位置插入和删除元素。<br/>   - 不支持随机访问，只能通过迭代器进行顺序访问。<br/>   - 在需要频繁执行插入和删除操作、不需要随机访问的情况下，效率较高。 | 需要频繁进行插入和删除操作且不需要随机访问，可以选择 std::list； |
| 3. std::deque：                               | - 底层实现为双端队列，可以高效地在两端插入和删除元素。<br/>   - 支持快速的随机访问，但相对于 std::vector，在插入和删除操作上效率稍低。 | 需要在两端进行高效的插入和删除操作，可以选择 std::deque；    |
| 4. std::set：                                 | - 底层实现为红黑树（自平衡二叉搜索树），**元素自动按照键值排序**。<br/>   - **不允许重复元素**，插入和查找操作的时间复杂度为 O(log N)。<br/>   - 适用于需要有序不重复元素集合的场景。 | 需要有序不重复的元素集合，可以选择 std::set；                |
| 5. std::map：                                 | - 底层实现为红黑树，以键值对的形式存储元素。<br/>   - **键值唯一且按照键值排序**，插入和查找操作的时间复杂度为 O(log N)。<br/>   - 适用于需要根据键值进行快速查找的场景。 | 需要根据键值进行快速查找，可以选择 std::map；                |
| 6. std::unordered_set 和 std::unordered_map： | - 底层实现为哈希表，元素无序存储。<br/>   - 插入和查找操作的平均时间复杂度为 O(1)，但最坏情况下可能达到 O(N)。<br/>   - 适用于对插入和查找性能要求较高的场景，但不要求元素有序。 | 对插入和查找性能要求较高且不需要元素有序，可以选择 std::unordered_set 或 std::unordered_map。 |



### 2 STL序列式容器

所谓序列容器，即以线性排列（类似普通数组的存储方式）来存储某一指定类型（例如 int、double 等）的数据，需要特殊说明的是，该类容器并不会自动对存储的元素按照值的大小进行排序。  
![在这里插入图片描述](https://img-blog.csdnimg.cn/31f822593d4e4f90879b392382b171a9.png#pic_center)

#### 2-1 array<T,N>（数组容器）

array<T,N>（数组容器）：表示可以存储 N 个 T 类型的元素，是 C++ 本身提供的一种容器。此类容器一旦建立，其长度就是固定不变的，这意味着不能增加或删除元素，只能改变某个元素的值；

array 容器以类模板的形式定义在 头文件，并位于命名空间 std 中

```cpp
#include <array>
using namespace std
```

初始化

```cpp
std::array<double, 10> values;     // array 容器不会做默认初始化操作
std::array<double, 10> values {};
std::array<double, 10> values {0.5,1.0,1.5,,2.0};

```

array容器成员函数

| 成员函数            | 功能                                                         |
| :------------------ | :----------------------------------------------------------- |
| begin()             | 返回指向容器中第一个元素的随机访问迭代器。                   |
| end()               | 返回指向容器最后一个元素之后一个位置的随机访问迭代器，通常和 begin() 结合使用。 |
| rbegin()            | 返回指向最后一个元素的随机访问迭代器。                       |
| rend()              | 返回指向第一个元素之前一个位置的随机访问迭代器。             |
| cbegin()            | 和 begin() 功能相同，只不过在其基础上增加了 const 属性，不能用于修改元素。 |
| cend()              | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()           | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()             | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| size()              | 返回容器中当前元素的数量，其值始终等于初始化 array 类的第二个模板参数 N。 |
| max\_size()         | 返回容器可容纳元素的最大数量，其值始终等于初始化 array 类的第二个模板参数 N。 |
| empty()             | 判断容器是否为空，和通过 size( )==0 的判断条件功能相同，但其效率可能更快。 |
| at(n)               | 返回容器中 n 位置处元素的引用，该函数自动检查 n 是否在有效的范围内，如果不是则抛出 out\_of\_range 异常。 |
| front()             | 返回容器中第一个元素的直接引用，该函数不适用于空的 array 容器。 |
| back()              | 返回容器中最后一个元素的直接应用，该函数同样不适用于空的 array 容器。 |
| data()              | 返回一个指向容器首个元素的指针。利用该指针，可实现复制容器中所有元素等类似功能。 |
| fill(val)           | 将 val 这个值赋值给容器中的每个元素。                        |
| array1.swap(array2) | 交换 array1 和 array2 容器中的所有元素，但前提是它们具有相同的长度和类型。 |
| get()               | 全局函数，该重载函数的功能是访问容器中指定的元素，并返回该元素的引用。 |

示例

```cpp
#include <iostream>
//需要引入 array 头文件
#include <array>
using namespace std;
int main()
{
    std::array<int, 4> values{};
    //初始化 values 容器为 {0,1,2,3}
    for (int i = 0; i < values.size(); i++) {
        values.at(i) = i;
    }
    //使用 get() 重载函数输出指定位置元素
    cout << get<3>(values) << endl;
    //如果容器不为空，则输出容器中所有的元素
    if (!values.empty()) {
        for (auto val = values.begin(); val < values.end(); val++) {
            cout << *val << " ";
        }
    }
}
```

#### 2-2 vector  <T>（向量容器）

vector <T>（向量容器）（动态数组）：用来存放 T 类型的元素，是一个长度可变的序列容器，即在存储空间不足时，会自动申请更多的内存。使用此容器，在尾部增加或删除元素的效率最高（时间复杂度为 O(1) 常数阶），在其它位置插入或删除元素效率较差（时间复杂度为 O(n) 线性阶，其中 n 为容器中元素的个数）；

`std::vector` 具有以下特点：

1. 动态大小：`std::vector` 是一个动态数组，可以在运行时根据需要动态调整其大小。它会自动处理内存管理和扩容，使得向 `std::vector` 中插入或删除元素都相对高效。
2. 连续存储：`std::vector` 中的元素在内存中是连续存储的，这使得元素的访问非常高效。通过指针或迭代器访问 `std::vector` 的元素可以实现常数时间复杂度的操作。
3. 随机访问：由于 `std::vector` 中的元素是连续存储的，因此可以通过索引直接访问任意位置的元素，实现随机访问。这使得对 `std::vector` 中的元素进行快速查找、遍历和修改成为可能。
4. **尾部插入和删除高效**：`std::vector` 提供了 `push_back()` 和 `pop_back()` 方法，可以在常数时间内在尾部插入和删除元素。这对于需要频繁进行插入和删除操作的场景非常有用。
5. 可变大小：`std::vector` 的大小可以随时改变，通过调用 `resize()` 方法可以增加或减少元素的数量。这种灵活性使得 `std::vector` 适用于需要动态调整大小的情况。
6. 迭代器支持：`std::vector` 支持使用迭代器进行元素的访问和遍历，可以通过迭代器实现对 `std::vector` 中元素的顺序访问或逆序访问。

需要注意的是，虽然 `std::vector` 在大多数情况下是一种高效的容器，但当需要频繁在中间位置插入或删除元素时，由于需要移动元素，可能会比较低效。如果对插入和删除操作的效率有更高要求，可以考虑其他容器，如 `std::list` 或 `std::deque`。

vector 容器以类模板 vector（ T 表示存储元素的类型）的形式定义在 头文件中，并位于 std 命名空间中。

```cpp
#include <vector>
using namespace std;
12
```

初始化

```cpp
std::vector<double> values;
std::vector<int> primes {2, 3, 5, 7, 11, 13, 17, 19};
std::vector<double> values(20);
std::vector<char> value1(5, 'c');
std::vector<char> value2(value1);
12345
```

vector 容器的成员函数

| 函数成员           | 函数功能                                                     |
| :----------------- | :----------------------------------------------------------- |
| begin()            | 返回指向容器中第一个元素的迭代器。                           |
| end()              | 返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。 |
| rbegin()           | 返回指向最后一个元素的迭代器。                               |
| rend()             | 返回指向第一个元素所在位置前一个位置的迭代器。               |
| cbegin()           | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()             | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()          | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()            | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| size()             | 返回实际元素个数。                                           |
| max\_size()        | 返回元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 |
| resize()           | 改变实际元素的个数。                                         |
| capacity()         | 返回当前容量。                                               |
| empty()            | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| reserve()          | 增加容器的容量。                                             |
| shrink \_to\_fit() | 将内存减少到等于当前元素实际所使用的大小。                   |
| operator\[ ]       | 重载了 \[ \] 运算符，可以向访问数组中元素那样，通过下标即可访问甚至修改 vector 容器中的元素。 |
| **at()**           | 使用经过边界检查的索引访问元素。                             |
| **front()**        | 返回第一个元素的引用。                                       |
| **back()**         | 返回最后一个元素的引用。                                     |
| **data()**         | 返回指向容器中第一个元素的指针。                             |
| **assign()**       | 用新元素替换原有内容。                                       |
| **push\_back()**   | **在序列的尾部添加一个元素。**                               |
| **pop\_back()**    | **移出序列尾部的元素。**                                     |
| insert()           | 在指定的位置插入一个或多个元素。                             |
| erase()            | 移出一个元素或一段元素。                                     |
| clear()            | 移出所有的元素，容器大小变为 0。                             |
| swap()             | 交换两个容器的所有元素。                                     |
| emplace()          | 在指定的位置直接生成一个元素。                               |
| emplace\_back()    | 在序列尾部生成一个元素。                                     |

示例

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    //初始化一个空vector容量
    vector<char>value;
    //向value容器中的尾部依次添加 S、T、L 字符
    value.push_back('S');
    value.push_back('T');
    value.push_back('L');
    //调用 size() 成员函数容器中的元素个数
    printf("元素个数为：%d\n", value.size());
    //使用迭代器遍历容器
    for (auto i = value.begin(); i < value.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    //向容器开头插入字符
    value.insert(value.begin(), 'C');
    cout << "首个元素为：" << value.at(0) << endl;
    return 0;
}

```

**emplace\_back()和push\_back()的区别**  
emplace\_back() 和 push\_back() 的区别，就在于底层实现的机制不同。push\_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；而 emplace\_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。

**emplace() 和insert()的区别**  
通过 insert() 函数向 vector 容器中插入 testDemo 类对象，需要调用类的构造函数和移动构造函数（或拷贝构造函数）；而通过 emplace() 函数实现同样的功能，只需要调用构造函数即可。

**vector不是容器**  
vector不是容器，为了节省空间，其内部是用一个bit来表示一个bool值的，operator\[\]不会返回一个指向bool值的引用，而是返回一个代理（proxy）  
试图以数组的形式来使用vector会引发错误。

```cpp
vector<bool> some(5, true);
memset(&some[0], 0, sizeof(false) * 5); // 引发错误
12
```

**释放内存**

```cpp
vector<int>().swap(a);
//或者如下所示 加一对大括号都可以，意思一样的：
{
 std::vector<int> tmp;   
 ivec.swap(tmp);
}     
//加一对大括号是可以让tmp退出{}的时候自动析构
cout<<a.size()<<endl;//输出 0
cout<<a.capacity()<<endl;.// 输出 0
123456789
```

**去重复操作**

```cpp
std::vector<int> ModuleArr;
//排序
std::sort(ModuleArr.begin(), ModuleArr.end());
//去重
ModuleArr.erase(unique(ModuleArr.begin(), ModuleArr.end()), ModuleArr.end());
12345
```

#### 2-3 [deque](https://so.csdn.net/so/search?q=deque&spm=1001.2101.3001.7020)（双端队列容器）

deque（双端队列容器）：和 vector 非常相似，区别在于使用该容器不仅尾部插入和删除元素高效，在头部插入或删除元素也同样高效，时间复杂度都是 O(1) 常数阶，但是在容器中某一位置处插入或删除元素，时间复杂度为 O(n) 线性阶；

当需要向序列两端频繁的添加或删除元素时，应首选 deque 容器。

```cpp
#include <deque>
using namespace std;
12
```

初始化

```cpp
std::deque<int> d;
std::deque<int> d(10);
std::deque<int> d(10, 5)
std::deque<int> d2(d);
1234
```

deque 容器的成员函数

| 函数成员           | 函数功能                                                     |
| :----------------- | :----------------------------------------------------------- |
| begin()            | 返回指向容器中第一个元素的迭代器。                           |
| end()              | 返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。 |
| rbegin()           | 返回指向最后一个元素的迭代器。                               |
| rend()             | 返回指向第一个元素所在位置前一个位置的迭代器。               |
| cbegin()           | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()             | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()          | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()            | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| size()             | 返回实际元素个数。                                           |
| max\_size()        | 返回容器所能容纳元素个数的最大值。这通常是一个很大的值，一般是 232-1，我们很少会用到这个函数。 |
| resize()           | 改变实际元素的个数。                                         |
| empty()            | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| shrink \_to\_fit() | 将内存减少到等于当前元素实际所使用的大小。                   |
| at()               | 使用经过边界检查的索引访问元素。                             |
| front()            | 返回第一个元素的引用。                                       |
| back()             | 返回最后一个元素的引用。                                     |
| assign()           | 用新元素替换原有内容。                                       |
| push\_back()       | 在序列的尾部添加一个元素。                                   |
| push\_front()      | 在序列的头部添加一个元素。                                   |
| pop\_back()        | 移除容器尾部的元素。                                         |
| pop\_front()       | 移除容器头部的元素。                                         |
| insert()           | 在指定的位置插入一个或多个元素。                             |
| erase()            | 移除一个元素或一段元素。                                     |
| clear()            | 移出所有的元素，容器大小变为 0。                             |
| swap()             | 交换两个容器的所有元素。                                     |
| emplace()          | 在指定的位置直接生成一个元素。                               |
| emplace\_front()   | 在容器头部生成一个元素。和 push\_front() 的区别是，该函数直接在容器头部构造元素，省去了复制移动元素的过程。 |
| emplace\_back()    | 在容器尾部生成一个元素。和 push\_back() 的区别是，该函数直接在容器尾部构造元素，省去了复制移动元素的过程。 |

示例

```cpp
#include <iostream>
#include <deque>
using namespace std;
int main()
{
    //初始化一个空deque容量
    deque<int>d;
    //向d容器中的尾部依次添加 1，2,3
    d.push_back(1); //{1}
    d.push_back(2); //{1,2}
    d.push_back(3); //{1,2,3}
    //向d容器的头部添加 0 
    d.push_front(0); //{0,1,2,3}
    //调用 size() 成员函数输出该容器存储的字符个数。
    printf("元素个数为：%d\n", d.size());
   
    //使用迭代器遍历容器
    for (auto i = d.begin(); i < d.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}

```

#### 2-4 list（链表容器）

list（链表容器）：是一个长度可变的、由 T 类型元素组成的序列，它以双向链表的形式组织元素，在这个序列的任何地方都可以高效地增加或删除元素（时间复杂度都为常数阶 O(1)），但访问容器中任意元素的速度要比前三种容器慢，这是因为 list 必须从第一个元素或最后一个元素开始访问，需要沿着链表移动，直到到达想要的元素。

实际场景中，如果需要对序列进行大量添加或删除元素的操作，而直接访问元素的需求却很少，这种情况建议使用 list 容器存储序列。

```cpp
#include <list>
using namespace std;
12
```

初始化

```cpp
std::list<int> values;
std::list<int> values(10);
std::list<int> values(10, 5);
std::list<int> value2(value);
1234
```

list 容器可用的成员函数

| 成员函数         | 功能                                                         |
| :--------------- | :----------------------------------------------------------- |
| begin()          | 返回指向容器中第一个元素的双向迭代器。                       |
| end()            | 返回指向容器中最后一个元素所在位置的下一个位置的双向迭代器。 |
| rbegin()         | 返回指向最后一个元素的反向双向迭代器。                       |
| rend()           | 返回指向第一个元素所在位置前一个位置的反向双向迭代器。       |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| empty()          | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| size()           | 返回当前容器实际包含的元素个数。                             |
| max\_size()      | 返回容器所能包含元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 |
| front()          | 返回第一个元素的引用。                                       |
| back()           | 返回最后一个元素的引用。                                     |
| assign()         | 用新元素替换容器中原有内容。                                 |
| emplace\_front() | 在容器头部生成一个元素。该函数和 push\_front() 的功能相同，但效率更高。 |
| push\_front()    | 在容器头部插入一个元素。                                     |
| pop\_front()     | 删除容器头部的一个元素。                                     |
| emplace\_back()  | 在容器尾部直接生成一个元素。该函数和 push\_back() 的功能相同，但效率更高。 |
| push\_back()     | 在容器尾部插入一个元素。                                     |
| pop\_back()      | 删除容器尾部的一个元素。                                     |
| emplace()        | 在容器中的指定位置插入元素。该函数和 insert() 功能相同，但效率更高。 |
| insert()         | 在容器中的指定位置插入元素。                                 |
| erase()          | 删除容器中一个或某区域内的元素。                             |
| swap()           | 交换两个容器中的元素，必须保证这两个容器中存储的元素类型是相同的。 |
| resize()         | 调整容器的大小。                                             |
| clear()          | 删除容器存储的所有元素。                                     |
| splice()         | 将一个 list 容器中的元素插入到另一个容器的指定位置。         |
| remove(val)      | 删除容器中所有等于 val 的元素。                              |
| remove\_if()     | 删除容器中满足条件的元素。                                   |
| unique()         | 删除容器中相邻的重复元素，只保留一个。                       |
| merge()          | 合并两个事先已排好序的 list 容器，并且合并之后的 list 容器依然是有序的。 |
| sort()           | 通过更改容器中元素的位置，将它们进行排序。                   |
| reverse()        | 反转容器中元素的顺序。                                       |

示例

```cpp
#include <iostream>
#include <list>
using namespace std;
int main()
{
    //创建空的 list 容器
    std::list<double> values;
    //向容器中添加元素
    values.push_back(3.1);
    values.push_back(2.2);
    values.push_back(2.9);
    cout << "values size：" << values.size() << endl;
    //对容器中的元素进行排序
    values.sort();
    //使用迭代器输出list容器中的元素
    for (std::list<double>::iterator it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

#### 2-5 forward\_list（正向链表容器）

forward\_list（正向链表容器）：和 list 容器非常类似，只不过它以单链表的形式组织元素，它内部的元素只能从第一个元素开始访问，是一类比链表容器快、更节省内存的容器。

效率高是选用 forward\_list 而弃用 list 容器最主要的原因，换句话说，只要是 list 容器和 forward\_list 容器都能实现的操作，应优先选择 forward\_list 容器。

```cpp
#include <forward_list>
using namespace std;

```

初始化

```cpp
std::forward_list<int> values;
std::forward_list<int> values(10);
std::forward_list<int> values(10, 5);
std::forward_list<int> value1(values);
```

forward\_list 容器可用的成员函数

| 成员函数         | 功能                                                         |
| :--------------- | :----------------------------------------------------------- |
| before\_begin()  | 返回一个前向迭代器，其指向容器中第一个元素之前的位置。       |
| begin()          | 返回一个前向迭代器，其指向容器中第一个元素的位置。           |
| end()            | 返回一个前向迭代器，其指向容器中最后一个元素之后的位置。     |
| cbefore\_begin() | 和 before\_begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| empty()          | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| max\_size()      | 返回容器所能包含元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 |
| front()          | 返回第一个元素的引用。                                       |
| assign()         | 用新元素替换容器中原有内容。                                 |
| push\_front()    | 在容器头部插入一个元素。                                     |
| emplace\_front() | 在容器头部生成一个元素。该函数和 push\_front() 的功能相同，但效率更高。 |
| pop\_front()     | 删除容器头部的一个元素。                                     |
| emplace\_after() | 在指定位置之后插入一个新元素，并返回一个指向新元素的迭代器。和 insert\_after() 的功能相同，但效率更高。 |
| insert\_after()  | 在指定位置之后插入一个新元素，并返回一个指向新元素的迭代器。 |
| erase\_after()   | 删除容器中某个指定位置或区域内的所有元素。                   |
| swap()           | 交换两个容器中的元素，必须保证这两个容器中存储的元素类型是相同的。 |
| resize()         | 调整容器的大小。                                             |
| clear()          | 删除容器存储的所有元素。                                     |
| splice\_after()  | 将某个 forward\_list 容器中指定位置或区域内的元素插入到另一个容器的指定位置之后。 |
| remove(val)      | 删除容器中所有等于 val 的元素。                              |
| remove\_if()     | 删除容器中满足条件的元素。                                   |
| unique()         | 删除容器中相邻的重复元素，只保留一个。                       |
| merge()          | 合并两个事先已排好序的 forward\_list 容器，并且合并之后的 forward\_list 容器依然是有序的。 |
| sort()           | 通过更改容器中元素的位置，将它们进行排序。                   |
| reverse()        | 反转容器中元素的顺序。                                       |

示例

```cpp
#include <iostream>
#include <forward_list>
using namespace std;
int main()
{
    std::forward_list<int> values{1,2,3};
    values.emplace_front(4);//{4,1,2,3}
    values.emplace_after(values.before_begin(), 5); //{5,4,1,2,3}
    values.reverse();//{3,2,1,4,5}
    for (auto it = values.begin(); it != values.end(); ++it) {
        cout << *it << " ";
    }
    return 0;
}
```

**获取 forward\_list 容器中存储元素的个数**

```cpp
std::forward_list<int> my_words{1,2,3,4};
int count = std::distance(std::begin(my_words), std::end(my_words));
```

**advance() 函数**

```cpp
std::forward_list<int> values{1,2,3,4};
auto it = values.begin();
advance(it, 2);
```

### 3 STL关联式容器

C++ STL关联式容器类别

| 关联式容器名称 | 特点                                                         |
| :------------- | :----------------------------------------------------------- |
| map            | 定义在 头文件中，使用该容器存储的数据，其各个元素的键必须是唯一的（即不能重复），该容器会根据各元素键的大小，默认进行升序排序（调用 std::less）。 |
| set            | 定义在 头文件中，使用该容器存储的数据，各个元素键和值完全相同，且各个元素的值不能重复（保证了各元素键的唯一性）。该容器会自动根据各个元素的键（其实也就是元素值）的大小进行升序排序（调用 std::less）。 |
| multimap       | 定义在 头文件中，和 map 容器唯一的不同在于，multimap 容器中存储元素的键可以重复。 |
| multiset       | 定义在 头文件中，和 set 容器唯一的不同在于，multiset 容器中存储元素的值可以重复（一旦值重复，则意味着键也是重复的）。 |

#### 3-1 pair

pair 类模板定义在头文件中

初始化

```cpp
// #1) 默认构造函数，即创建空的 pair 对象
pair();
// #2) 直接使用 2 个元素初始化成 pair 对象
pair (const first_type& a, const second_type& b);
// #3) 拷贝（复制）构造函数，即借助另一个 pair 对象，创建新的 pair 对象
template<class U, class V> pair (const pair<U,V>& pr);
// #4) 移动构造函数
template<class U, class V> pair (pair<U,V>&& pr);
// #5) 使用右值引用参数，创建 pair 对象
template<class U, class V> pair (U&& a, V&& b);
```

示例

```cpp
#include <iostream>
#include <utility>      // pair
#include <string>       // string
int main() {
	///////////////////////////////////////////////////////////////////////////pair 模版方法示例
    std::pair<int, double> pr1(1, 3.14);
    std::pair<double, double> pr2(pr1);  // 使用构造函数创建新的pair对象

    std::cout << pr2.first << ", " << pr2.second << std::endl;


// 调用构造函数 1，也就是默认构造函数
    std::pair <std::string, double> pair1;
    // 调用第 2 种构造函数
    std::pair <std::string, std::string> pair2("STL教程","std::pair");  
    // 调用拷贝构造函数，将pair2  cp 到 pair3
    std::pair <std::string, std::string> pair3(pair2);

    //调用移动构造函数sq
    //std::make_pair 是一个函数模板，用于创建一个 pair 对象。它的使用非常简单，只需要提供两个参数，分别是键和值，它会自动推导出键值对的类型，并返回一个 pair 对象。

    //////使用 make_pair 可以更加简洁地创建 pair 对象，而无需显式指定类型。

    std::pair <std::string, std::string> pair4(std::make_pair("C++教程", "STL教程"));
    // 调用第 5 种构造函数
    std::pair <std::string, std::string> pair5(std::string("Python教程"), std::string("STL教程"));  
   
    std::cout << "pair1: " << pair1.first << " " << pair1.second << std::endl;
    std::cout << "pair2: " << pair2.first << " " << pair2.second << std::endl;
    std::cout << "pair3: " << pair3.first << " " << pair3.second << std::endl;
    std::cout << "pair4: " << pair4.first << " " << pair4.second << std::endl;
    std::cout << "pair5: " << pair5.first << " " << pair5.second << std::endl;

}
```

#### 3-2 map容器

map 容器定义在 头文件中，并位于 std 命名空间中。是由键值对组成的无序的集合。

`std::map` 是 C++ 标准库提供的一种关联容器，它提供了一种将键和值关联起来的映射关系。`std::map` 容器中的元素按照键的顺序自动排序，并且键是唯一的。

#####  `std::map` 的一些重要特性和用法：

- 元素排序：`std::map` 中的元素默认按照键的升序进行排序，可以使用自定义的比较函数或者通过自定义键类型的重载操作符来改变排序方式。
- 唯一键：`std::map` 中的键是唯一的，如果插入了相同的键，则新值会覆盖旧值。
- 动态操作：`std::map` 支持插入、删除和查找操作。插入操作可以使用插入函数或者使用初始化列表进行批量插入。删除操作可以通过键或迭代器进行删除。查找操作可以使用键进行查找，返回键对应的值或迭代器。
- 迭代器遍历：可以使用迭代器遍历 `std::map` 容器中的元素。迭代器提供了访问键和值的方法，也支持自增运算符实现遍历。
- 范围查找：`std::map` 提供了一系列成员函数，例如 `lower_bound`、`upper_bound` 和 `equal_range`，用于在有序的容器中进行范围查找。
- 键值访问：可以使用下标运算符或 `at()` 函数通过键来访问和修改对应的值。如果键不存在，`std::map` 的下标运算符会在插入一个默认值的情况下返回该值。

使用 `std::map` 

需要包含 `<map>` 头文件，并且使用 `std::map<Key, T>` 模板进行声明，其中 `Key` 是键的类型，`T` 是值的类型。

```cpp
#include <map>
using namespace std;
```

初始化

```cpp
std::map<std::string, int> myMap;
std::map<std::string, int> myMap{ {"C语言教程",10},{"STL教程",20} };
std::map<std::string, int> newMap(myMap);
std::map<std::string, int> newMap(++myMap.begin(), myMap.end());
// 修改 map 容器的排序规则
std::map<std::string, int, std::less<std::string> > myMap{ {"C语言教程",10},{"STL教程",20} };
```

map容器常用成员方法

| 成员方法  | 功能                                                         |      |
| :-------- | :----------------------------------------------------------- | ---- |
| begin()   | 返回指向容器中第一个（注意，是已排好序的第一个）键值对的**双向迭代器**。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向**迭代器**。 |      |
| end()     | 返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的**双向迭代器**，通常和 begin() 结合使用。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |      |
| rbegin()  | 返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |      |
| rend()    | 返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的**反向双向迭代器**。如果 map 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |      |
| cbegin()  | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |      |
| cend()    | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |      |
| crbegin() | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |      |
| crend()   | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |      |
| find(key) | 在 map 容器中查找键为 key 的键值对，如果成功找到，则返回指向该键值对的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |      |
| insert()  | 用于在map中插入一个元素。                                    |      |
|           |                                                              |      |



`std::map`是C++标准库中的一个关联容器，它存储的元素是键值对（key-value pair）。每个键值对都通过一个键（key）来唯一标识。下面是一些`std::map`常用的成员方法及其例子：

##### 1. `insert()`:

 用于在map中插入一个元素。

```c++
std::map<int, std::string> myMap;
myMap.insert(std::pair<int, std::string>(1, "one"));
myMap.insert(std::pair<int, std::string>(2, "two"));
// 或者可以使用简化的语法（C++17 起）
myMap.insert({52,"map_simple_insert_pair_type"});
```

##### 2. `operator[]`: 

   用于访问或修改map中的元素。如果键不存在，该方法会插入一个具有默认值的元素。

```c++
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
std::cout << myMap[1] << std::endl;  // Outputs: onemyMap[3] = "three";
```

##### 3. `at()`: 

用于访问map中指定键的元素。如果键不存在，该方法抛出一个`std::out_of_range`异常。

```c++
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
try {    
    std::cout << myMap.at(1) << std::endl;  // Outputs: one
} catch(const std::out_of_range& e) {    
    std::cout << "Key not found: " << e.what() << std::endl;
}
```

##### 4. `find()`: 

用于查找map中指定键的元素。如果键不存在，该方法返回一个指向map末尾的迭代器。

```c++
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
auto it = myMap.find(2);
if(it != myMap.end()) {    
    std::cout << it->first << ": " << it->second << std::endl;  // Outputs: 2: two
}
```

##### 5. `erase()`:

 用于删除map中的一个元素。

```c++
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
myMap.erase(2);  // Removes the element with key 2
```

##### 6. `clear()`: 

用于删除map中的所有元素。

```c++
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
myMap.clear();  // Removes all elements from the map
```

##### 7. `size()`:

 用于获取map中的元素数量。

```c++
std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
std::cout << myMap.size() << std::endl;  // Outputs: 2
```

##### 8. `empty()`: 

用于检查map是否为空（即没有元素）。

```c++
std::map<int, std::string> myMap;
std::cout << myMap.empty() << std::endl;  // Outputs: 1 (true)
myMap.insert(std::pair<int, std::string>(1, "one"));
std::cout << myMap.empty() << std::endl;  // Outputs: 0 (false)
```

##### 示例

```cpp
#include <iostream>
#include <map>      // map
#include <string>       // string
using namespace std;
int main() {
    //创建空 map 容器，默认根据个键值对中键的值，对键值对做降序排序
    std::map<std::string, std::string, std::greater<std::string>>myMap;
    //调用 emplace() 方法，直接向 myMap 容器中指定位置构造新键值对
    myMap.emplace("C语言教程","http://c.biancheng.net/c/");
    myMap.emplace("Python教程", "http://c.biancheng.net/python/");
    myMap.emplace("STL教程", "http://c.biancheng.net/stl/");
    //输出当前 myMap 容器存储键值对的个数
    cout << "myMap size==" << myMap.size() << endl;
    //判断当前 myMap 容器是否为空
    if (!myMap.empty()) {
        //借助 myMap 容器迭代器，将该容器的键值对逐个输出
        for (auto i = myMap.begin(); i != myMap.end(); ++i) {
            cout << i->first << " " << i->second << endl;
        }
    }  
    return 0;
}

```



输出：

```yaml
Number of apples: 3
apple: 3
banana: 2
grape: 4
```

**lower\_bound(key) 和 upper\_bound(key)**  
lower\_bound(key) 返回的是指向第一个键不小于 key 的键值对的迭代器；  
upper\_bound(key) 返回的是指向第一个键大于 key 的键值对的迭代器；  
lower\_bound(key) 和 upper\_bound(key) 更多用于 multimap 容器，在 map 容器中很少用到。  
**equal\_range(key)**  equal\_range(key) 成员方法可以看做是 lower\_bound(key) 和 upper\_bound(key) 的结合体，该方法会返回一个 pair 对象，其中的 2 个元素都是迭代器类型，其中 pair.first 实际上就是 lower\_bound(key) 的返回值，而 pair.second 则等同于 upper\_bound(key) 的返回值。

#### 3-3 set容器

set 容器定义于头文件，并位于 std 命名空间中。

`std::set` 是 C++ 标准库中的一个容器，它实现了有序的、不重复的元素集合。`std::set` 使用红黑树（Red-Black Tree）作为底层数据结构，因此插入、删除和查找操作的平均时间复杂度都为 O(log n)。

下面是一些 `std::set` 的特点和用法：

1. **有序性**：`std::set` 中的元素按照升序排列，默认使用 `<` 运算符进行比较。你也可以通过提供自定义的比较函数来改变排序方式。
2. **唯一性**：`std::set` 中的元素是唯一的，不会存在重复的元素。当尝试插入已经存在的元素时，插入操作将被忽略。
3. **插入元素**：可以使用 `insert()` 函数向 `std::set` 中插入元素。插入操作会自动调整元素的位置，以保持有序性。
4. **删除元素**：可以使用 `erase()` 函数从 `std::set` 中删除指定元素。删除操作会保持树的平衡。
5. **查找元素**：可以使用 `find()` 函数在 `std::set` 中查找指定元素，如果找到则返回迭代器，否则返回 `end()` 迭代器。
6. **遍历元素**：可以使用迭代器或范围循环来遍历 `std::set` 中的元素。

```cpp
#include <set>
using namespace std;
```

初始化

```cpp
std::set<std::string> myset;
std::set<std::string> myset{"http://c.biancheng.net/java/",
                            "http://c.biancheng.net/stl/",
                            "http://c.biancheng.net/python/"};
std::set<std::string> copyset(myset);                            
```

C++ set 容器常用成员方法

| 成员方法          | 功能                                                         |
| :---------------- | :----------------------------------------------------------- |
| begin()           | 返回指向容器中第一个（注意，是已排好序的第一个）元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| end()             | 返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| rbegin()          | 返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| rend()            | 返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的反向双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| cbegin()          | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| cend()            | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| crbegin()         | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| crend()           | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| find(val)         | 在 set 容器中查找值为 val 的元素，如果成功找到，则返回指向该元素的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| lower\_bound(val) | 返回一个指向当前 set 容器中第一个大于或等于 val 的元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| upper\_bound(val) | 返回一个指向当前 set 容器中第一个大于 val 的元素的迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| equal\_range(val) | 该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower\_bound() 方法的返回值等价，pair.second 和 upper\_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的值为 val 的元素（set 容器中各个元素是唯一的，因此该范围最多包含一个元素）。 |
| empty()           | 若容器为空，则返回 true；否则 false。                        |
| size()            | 返回当前 set 容器中存有元素的个数。                          |
| max\_size()       | 返回 set 容器所能容纳元素的最大个数，不同的操作系统，其返回值亦不相同。 |
| insert()          | 向 set 容器中插入元素。                                      |
| erase()           | 删除 set 容器中存储的元素。                                  |
| swap()            | 交换 2 个 set 容器中存储的所有元素。这意味着，操作的 2 个 set 容器的类型必须相同。 |
| clear()           | 清空 set 容器中所有的元素，即令 set 容器的 size() 为 0。     |
| emplace()         | 在当前 set 容器中的指定位置直接构造新元素。其效果和 insert() 一样，但效率更高。 |
| emplace\_hint()   | 在本质上和 emplace() 在 set 容器中构造新元素的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示新元素生成位置的迭代器，并作为该方法的第一个参数。 |
| count(val)        | 在当前 set 容器中，查找值为 val 的元素的个数，并返回。注意，由于 set 容器中各元素的值是唯一的，因此该函数的返回值最大为 1。 |

示例

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    //创建空set容器
    std::set<std::string> myset;
    //空set容器不存储任何元素
    cout << "1、myset size = " << myset.size() << endl;
    //向myset容器中插入新元素
    myset.insert("http://c.biancheng.net/java/");
    myset.insert("http://c.biancheng.net/stl/");
    myset.insert("http://c.biancheng.net/python/");
    cout << "2、myset size = " << myset.size() << endl;
    //利用双向迭代器，遍历myset
    for (auto iter = myset.begin(); iter != myset.end(); ++iter) {
        cout << *iter << endl;
    }
    return 0;
}
```

#### 3-4 multimap容器

和 map 容器一样，实现 multimap 容器的类模板也定义在头文件，并位于 std 命名空间中。

```cpp
#include <map>
using namespace std;
```

初始化

```cpp
std::multimap<std::string, std::string> mymultimap;
//创建并初始化 multimap 容器
multimap<string, string>mymultimap{ {"C语言教程", "http://c.biancheng.net/c/"},
                                    {"Python教程", "http://c.biancheng.net/python/"},
                                    {"STL教程", "http://c.biancheng.net/stl/"} };
// 修改 multimap 容器内部的排序规则                               
multimap<char, int, std::less<char>>mymultimap{ {'a',1},{'b',2} };
```

multimap 容器常用成员方法

| 成员方法          | 功能                                                         |
| :---------------- | :----------------------------------------------------------- |
| begin()           | 返回指向容器中第一个（注意，是已排好序的第一个）键值对的双向迭代器。如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| end()             | 返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| rbegin()          | 返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| rend()            | 返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的反向双向迭代器。如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| cbegin()          | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| cend()            | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| crbegin()         | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| crend()           | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| find(key)         | 在 multimap 容器中查找首个键为 key 的键值对，如果成功找到，则返回指向该键值对的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| lower\_bound(key) | 返回一个指向当前 multimap 容器中第一个大于或等于 key 的键值对的双向迭代器。如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| upper\_bound(key) | 返回一个指向当前 multimap 容器中第一个大于 key 的键值对的迭代器。如果 multimap 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| equal\_range(key) | 该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower\_bound() 方法的返回值等价，pair.second 和 upper\_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的键为 key 的键值对。 |
| empty()           | 若容器为空，则返回 true；否则 false。                        |
| size()            | 返回当前 multimap 容器中存有键值对的个数。                   |
| max\_size()       | 返回 multimap 容器所能容纳键值对的最大个数，不同的操作系统，其返回值亦不相同。 |
| insert()          | 向 multimap 容器中插入键值对。                               |
| erase()           | 删除 multimap 容器指定位置、指定键（key）值或者指定区域内的键值对。 |
| swap()            | 交换 2 个 multimap 容器中存储的键值对，这意味着，操作的 2 个键值对的类型必须相同。 |
| clear()           | 清空 multimap 容器中所有的键值对，使 multimap 容器的 size() 为 0。 |
| emplace()         | 在当前 multimap 容器中的指定位置处构造新键值对。其效果和插入键值对一样，但效率更高。 |
| emplace\_hint()   | 在本质上和 emplace() 在 multimap 容器中构造新键值对的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示键值对生成位置的迭代器，并作为该方法的第一个参数。 |
| count(key)        | 在当前 multimap 容器中，查找键为 key 的键值对的个数并返回。  |

示例

```cpp
#include <iostream>
#include <map>  //map
using namespace std;   
int main()
{
    //创建并初始化 multimap 容器
    multimap<char, int>mymultimap{ {'a',10},{'b',20},{'b',15}, {'c',30} };
    //输出 mymultimap 容器存储键值对的数量
    cout << mymultimap.size() << endl;
    //输出 mymultimap 容器中存储键为 'b' 的键值对的数量
    cout << mymultimap.count('b') << endl;
    for (auto iter = mymultimap.begin(); iter != mymultimap.end(); ++iter) {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
```

和 map 容器相比，multimap 未提供 at() 成员方法，也没有重载 \[\] 运算符。  
由于 multimap 容器可存储多个具有相同键的键值对，因此 lower\_bound()、upper\_bound()、equal\_range() 以及 count() 成员方法会经常用到。

#### 3-5 multiset容器

multiset 容器和 set 容器唯一的差别在于，multiset 容器允许存储多个值相同的元素，而 set 容器中只能存储互不相同的元素。

和 set 类模板一样，multiset 类模板也定义在头文件，并位于 std 命名空间中。

```cpp
#include <set>
using namespace std;
```

初始化

```cpp
std::multiset<std::string> mymultiset;
std::multiset<std::string> mymultiset{ "http://c.biancheng.net/java/",
                                       "http://c.biancheng.net/stl/",
                                       "http://c.biancheng.net/python/" };
std::multiset<std::string> copymultiset(mymultiset);                                       
```

multiset 容器常用成员方法

| 成员方法          | 功能                                                         |
| :---------------- | :----------------------------------------------------------- |
| begin()           | 返回指向容器中第一个（注意，是已排好序的第一个）元素的双向迭代器。如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| end()             | 返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| rbegin()          | 返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| rend()            | 返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的反向双向迭代器。如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| cbegin()          | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| cend()            | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| crbegin()         | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| crend()           | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| find(val)         | 在 multiset 容器中查找值为 val 的元素，如果成功找到，则返回指向该元素的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| lower\_bound(val) | 返回一个指向当前 multiset 容器中第一个大于或等于 val 的元素的双向迭代器。如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| upper\_bound(val) | 返回一个指向当前 multiset 容器中第一个大于 val 的元素的迭代器。如果 multiset 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| equal\_range(val) | 该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower\_bound() 方法的返回值等价，pair.second 和 upper\_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含所有值为 val 的元素。 |
| empty()           | 若容器为空，则返回 true；否则 false。                        |
| size()            | 返回当前 multiset 容器中存有元素的个数。                     |
| max\_size()       | 返回 multiset 容器所能容纳元素的最大个数，不同的操作系统，其返回值亦不相同。 |
| insert()          | 向 multiset 容器中插入元素。                                 |
| erase()           | 删除 multiset 容器中存储的指定元素。                         |
| swap()            | 交换 2 个 multiset 容器中存储的所有元素。这意味着，操作的 2 个 multiset 容器的类型必须相同。 |
| clear()           | 清空 multiset 容器中所有的元素，即令 multiset 容器的 size() 为 0。 |
| emplace()         | 在当前 multiset 容器中的指定位置直接构造新元素。其效果和 insert() 一样，但效率更高。 |
| emplace\_hint()   | 本质上和 emplace() 在 multiset 容器中构造新元素的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示新元素生成位置的迭代器，并作为该方法的第一个参数。 |
| count(val)        | 在当前 multiset 容器中，查找值为 val 的元素的个数，并返回。  |

示例

```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main() {
    std::multiset<int> mymultiset{1,2,2,2,3,4,5};
    cout << "multiset size = " << mymultiset.size() << endl;
    cout << "multiset count(2) =" << mymultiset.count(2) << endl;
    //向容器中添加元素 8
    mymultiset.insert(8);
    //删除容器中所有值为 2 的元素
    int num = mymultiset.erase(2);
    cout << "删除了 " << num << " 个元素 2" << endl;
    //输出容器中存储的所有元素
    for (auto iter = mymultiset.begin(); iter != mymultiset.end(); ++iter) {
        cout << *iter << " ";
    }
    return 0;
}
```

### 4 STL无序关联式容器

无序关联式容器，又称哈希容器。和关联式容器一样，此类容器存储的也是键值对元素；不同之处在于，关联式容器默认情况下会对存储的元素做升序排序，而无序关联式容器不会。

和其它类容器相比，无序关联式容器擅长通过指定键查找对应的值，而遍历容器中存储元素的效率不如关联式容器。

无序容器种类

| 无序容器            | 功能                                                         |
| :------------------ | :----------------------------------------------------------- |
| unordered\_map      | 存储键值对 <key, value> 类型的元素，其中各个键值对键的值不允许重复，且该容器中存储的键值对是无序的。 |
| unordered\_multimap | 和 unordered\_map 唯一的区别在于，该容器允许存储多个键相同的键值对。 |
| unordered\_set      | 不再以键值对的形式存储数据，而是直接存储数据元素本身（当然也可以理解为，该容器存储的全部都是键 key 和值 value 相等的键值对，正因为它们相等，因此只存储 value 即可）。另外，该容器存储的元素不能重复，且容器内部存储的元素也是无序的。 |
| unordered\_multiset | 和 unordered\_set 唯一的区别在于，该容器允许存储值相同的元素。 |

示例

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main()
{
    //创建并初始化一个 unordered_map 容器，其存储的 <string,string> 类型的键值对
    std::unordered_map<std::string, std::string> my_uMap{
        {"C语言教程","http://c.biancheng.net/c/"},
        {"Python教程","http://c.biancheng.net/python/"},
        {"Java教程","http://c.biancheng.net/java/"} };
    //查找指定键对应的值，效率比关联式容器高
    string str = my_uMap.at("C语言教程");
    cout << "str = " << str << endl;
    //使用迭代器遍历哈希容器，效率不如关联式容器
    for (auto iter = my_uMap.begin(); iter != my_uMap.end(); ++iter)
    {
        //pair 类型键值对分为 2 部分
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
```

### 5 STL容器适配器

容器适配器是一个封装了序列容器的类模板，它在一般序列容器的基础上提供了一些不同的功能。之所以称作适配器类，是因为它可以通过适配容器现有的接口来提供不同的功能。

本章将介绍 3 种容器适配器，分别是 stack、queue、priority\_queue：

+   stack：是一个封装了 deque 容器的适配器类模板，默认实现的是一个后入先出（Last-In-First-Out，LIFO）的压入栈。stack 模板定义在头文件 stack 中。
+   queue：是一个封装了 deque 容器的适配器类模板，默认实现的是一个先入先出（First-In-First-Out，LIFO）的队列。可以为它指定一个符合确定条件的基础容器。queue 模板定义在头文件 queue 中。
+   priority\_queue：是一个封装了 vector 容器的适配器类模板，默认实现的是一个会对元素排序，从而保证最大元素总在队列最前面的队列。priority\_queue 模板定义在头文件 queue 中。

STL 容器适配器及其基础容器

| 容器适配器      | 基础容器筛选条件                                             | 默认使用的基础容器 |
| :-------------- | :----------------------------------------------------------- | :----------------- |
| stack           | 基础容器需包含以下成员函数：empty()，size()，back()，push\_back() ，pop\_back() 满足条件的基础容器有 vector、deque、list。 | deque              |
| queue           | 基础容器需包含以下成员函数：empty()，size()，front()，back()，push\_back()，pop\_front()，满足条件的基础容器有 deque、list。 | deque              |
| priority\_queue | 基础容器需包含以下成员函数：empty()，size()，front()，push\_back()，pop\_back()，满足条件的基础容器有vector、deque。 | vector             |

#### 5-1 stack容器

stack 栈适配器是一种单端开口的容器。由于数据的存和取只能从栈顶处进行操作，因此对于存取数据，stack 适配器有这样的特性，即每次只能访问适配器中位于最顶端的元素，也只有移除 stack 顶部的元素之后，才能访问位于栈中的元素。

stack 适配器以模板类 stack<T,Container=deque>（其中 T 为存储元素的类型，Container 表示底层容器的类型）的形式位于头文件中，并定义在 std 命名空间里。

```cpp
#include <stack>
using namespace std;
```

初始化

```cpp
std::stack<int> values;
std::stack<std::string, std::list<int>> values;
std::list<int> values {1, 2, 3};
std::stack<int,std::list<int>> my_stack (values); 
```

stack容器适配器支持的成员函数

| 成员函数                   | 功能                                                         |
| :------------------------- | :----------------------------------------------------------- |
| empty()                    | 当 stack 栈中没有元素时，该成员函数返回 true；反之，返回 false。 |
| size()                     | 返回 stack 栈中存储元素的个数。                              |
| top()                      | 返回一个栈顶元素的引用，类型为 T&。如果栈为空，程序会报错。  |
| push(const T& val)         | 先复制 val，再将 val 副本压入栈顶。这是通过调用底层容器的 push\_back() 函数完成的。 |
| push(T&& obj)              | 以移动元素的方式将其压入栈顶。这是通过调用底层容器的有右值引用参数的 push\_back() 函数完成的。 |
| pop()                      | 弹出栈顶元素。                                               |
| emplace(arg…)              | arg… 可以是一个参数，也可以是多个参数，但它们都只用于构造一个对象，并在栈顶直接生成该对象，作为新的栈顶元素。 |
| swap(stack & other\_stack) | 将两个 stack 适配器中的元素进行互换，需要注意的是，进行互换的 2 个 stack 适配器中存储的元素类型以及底层采用的基础容器类型，都必须相同。 |

示例

```cpp
#include <iostream>
#include <stack>
#include <list>
using namespace std;
int main()
{
    //构建 stack 容器适配器
    list<int> values{ 1, 2, 3 };
    stack<int, list<int>> my_stack(values);
    //查看 my_stack 存储元素的个数
    cout << "size of my_stack: " << my_stack.size() << endl;
    //将 my_stack 中存储的元素依次弹栈，直到其为空
    while (!my_stack.empty())
    {  
        cout << my_stack.top() << endl;
        //将栈顶元素弹栈
        my_stack.pop();
    }
    return 0;
}
```

#### 5-2 queue容器

queue存储结构最大的特点是，最先进入 queue 的元素，也可以最先从 queue 中出来，即用此容器适配器存储数据具有“先进先出（简称 “FIFO” ）”的特点，因此 queue 又称为队列适配器。

queue 容器适配器以模板类 queue<T,Container=deque>（其中 T 为存储元素的类型，Container 表示底层容器的类型）的形式位于头文件中，并定义在 std 命名空间里。

```cpp
#include <queue>
using namespace std;
```

初始化

```cpp
std::queue<int> values;
std::queue<int, std::list<int>> values;   
std::deque<int> values{1,2,3};
std::queue<int> my_queue(values);                           
```

queue容器适配器支持的成员函数

| 成员函数                  | 功能                                                         |
| :------------------------ | :----------------------------------------------------------- |
| empty()                   | 如果 queue 中没有元素的话，返回 true。                       |
| size()                    | 返回 queue 中元素的个数。                                    |
| front()                   | 返回 queue 中第一个元素的引用。如果 queue 是常量，就返回一个常引用；如果 queue 为空，返回值是未定义的。 |
| back()                    | 返回 queue 中最后一个元素的引用。如果 queue 是常量，就返回一个常引用；如果 queue 为空，返回值是未定义的。 |
| push(const T& obj)        | 在 queue 的尾部添加一个元素的副本。这是通过调用底层容器的成员函数 push\_back() 来完成的。 |
| emplace()                 | 在 queue 的尾部直接添加一个元素。                            |
| push(T&& obj)             | 以移动的方式在 queue 的尾部添加元素。这是通过调用底层容器的具有右值引用参数的成员函数 push\_back() 来完成的。 |
| pop()                     | 删除 queue 中的第一个元素。                                  |
| swap(queue &other\_queue) | 将两个 queue 容器适配器中的元素进行互换，需要注意的是，进行互换的 2 个 queue 容器适配器中存储的元素类型以及底层采用的基础容器类型，都必须相同。 |

示例

```cpp
#include <iostream>
#include <queue>
#include <list>
using namespace std;
int main()
{
    //构建 queue 容器适配器
    std::deque<int> values{ 1,2,3 };
    std::queue<int> my_queue(values);//{1,2,3}
    //查看 my_queue 存储元素的个数
    cout << "size of my_queue: " << my_queue.size() << endl;
    //访问 my_queue 中的元素
    while (!my_queue.empty())
    {
        cout << my_queue.front() << endl;
        //访问过的元素出队列
        my_queue.pop();
    }
    return 0;
}
```

#### 5-3 priority\_queue容器

priority\_queue 容器适配器“First in，Largest out”的特性，和它底层采用堆结构存储数据是分不开的

priority\_queue 容器适配器模板位于头文件中，并定义在 std 命名空间里

```cpp
#include <queue>
using namespace std;
```

初始化

```cpp
std::priority_queue<int> values;
int values[]{4,1,3,2};
std::priority_queue<int>copy_values(values,values+4);//{4,2,3,1} 
// 手动指定 priority_queue 使用的底层容器以及排序规则
int values[]{ 4,1,2,3 };
std::priority_queue<int, std::deque<int>, std::greater<int> >copy_values(values, values+4);//{1,3,2,4}                              
```

priority\_queue 提供的成员函数

| 成员函数                     | 功能                                                         |
| :--------------------------- | :----------------------------------------------------------- |
| empty()                      | 如果 priority\_queue 为空的话，返回 true；反之，返回 false。 |
| size()                       | 返回 priority\_queue 中存储元素的个数。                      |
| top()                        | 返回 priority\_queue 中第一个元素的引用形式。                |
| push(const T& obj)           | 根据既定的排序规则，将元素 obj 的副本存储到 priority\_queue 中适当的位置。 |
| push(T&& obj)                | 根据既定的排序规则，将元素 obj 移动存储到 priority\_queue 中适当的位置。 |
| emplace(Args&&… args)        | Args&&… args 表示构造一个存储类型的元素所需要的数据（对于类对象来说，可能需要多个数据构造出一个对象）。此函数的功能是根据既定的排序规则，在容器适配器适当的位置直接生成该新元素。 |
| pop()                        | 移除 priority\_queue 容器适配器中第一个元素。                |
| swap(priority\_queue& other) | 将两个 priority\_queue 容器适配器中的元素进行互换，需要注意的是，进行互换的 2 个 priority\_queue 容器适配器中存储的元素类型以及底层采用的基础容器类型，都必须相同。 |

示例

```cpp
#include <iostream>
#include <queue>
#include <array>
#include <functional>
using namespace std;
int main()
{
    //创建一个空的priority_queue容器适配器
    std::priority_queue<int>values;
    //使用 push() 成员函数向适配器中添加元素
    values.push(3);//{3}
    values.push(1);//{3,1}
    values.push(4);//{4,1,3}
    values.push(2);//{4,2,3,1}
    //遍历整个容器适配器
    while (!values.empty())
    {
        //输出第一个元素并移除。
        std::cout << values.top()<<" ";
        values.pop();//移除队头元素的同时，将剩余元素中优先级最大的移至队头
    }
    return 0;
}
```

### 6 STL迭代器适配器

反向迭代器适配器、插入型迭代器适配器、流迭代器适配器、流缓冲区迭代器适配器、移动迭代器适配器

C++ STL迭代器适配器种类

| 名称                                                         | 功能                                                         |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| 反向迭代器（reverse\_iterator）                              | 又称“逆向迭代器”，其内部重新定义了递增运算符（++）和递减运算符（–），专门用来实现对容器的逆序遍历。 |
| 安插型迭代器（inserter或者insert\_iterator）                 | 通常用于在容器的任何位置添加新的元素，需要注意的是，此类迭代器不能被运用到元素个数固定的容器（比如 array）上。 |
| 流迭代器（istream\_iterator / ostream\_iterator）            | 输入流迭代器用于从文件或者键盘读取数据；相反，输出流迭代器用于将数据输出到文件或者屏幕上。 |
| 流缓冲区迭代器（istreambuf\_iterator / ostreambuf\_iterator） | 用于从输入缓冲区中逐个读取数据；输出流缓冲区迭代器用于将数据逐个写入输出流缓冲区。 |
| 移动迭代器（move\_iterator）                                 | 此类型迭代器是 C++ 11 标准中新添加的，可以将某个范围的类对象移动到目标范围，而不需要通过拷贝去移动。 |

#### 6-1 反向迭代器适配器（reverse\_iterator）

```cpp
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
int main() {
    //创建并初始化一个 vector 容器
    std::vector<int> myvector{ 1,2,3,4,5,6,7,8 };
    //创建并初始化一个反向迭代器
    std::reverse_iterator<std::vector<int>::iterator> my_reiter(myvector.rbegin());//指向 8
    cout << *my_reiter << endl;// 8
    cout << *(my_reiter + 3) << endl;// 5
    cout << *(++my_reiter) << endl;// 7
    cout << my_reiter[4] << endl;// 3
    return 0;
}
```

#### 6-2 安插型迭代器（inserter或者insert\_iterator）

STL插入迭代器适配器种类

| 迭代器适配器            | 功能                                                         |
| :---------------------- | :----------------------------------------------------------- |
| back\_insert\_iterator  | 在指定容器的尾部插入新元素，但前提必须是提供有 push\_back() 成员方法的容器（包括 vector、deque 和 list）。 |
| front\_insert\_iterator | 在指定容器的头部插入新元素，但前提必须是提供有 push\_front() 成员方法的容器（包括 list、deque 和 forward\_list）。 |
| insert\_iterator        | 在容器的指定位置之前插入新元素，前提是该容器必须提供有 insert() 成员方法。 |

back\_insert\_iterator 迭代器

```cpp
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
int main() {
    //创建一个 vector 容器
    std::vector<int> foo;
    //创建一个可向 foo 容器尾部添加新元素的迭代器
    std::back_insert_iterator< std::vector<int> > back_it(foo);
    //将 5 插入到 foo 的末尾
    back_it = 5;
    //将 4 插入到当前 foo 的末尾
    back_it = 4;
    //输出 foo 容器中的元素
    for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
        std::cout << *it << ' ';
    return 0;
}
```

front\_insert\_iterator 迭代器

```cpp
#include <iostream>
#include <iterator>
#include <forward_list>
using namespace std;
int main() {
    //创建一个 forward_list 容器
    std::forward_list<int> foo;
    //创建一个前插入迭代器
    //std::front_insert_iterator< std::forward_list<int> > front_it(foo);
    std::front_insert_iterator< std::forward_list<int> > front_it = front_inserter(foo);
    //向 foo 容器的头部插入元素
    front_it = 5;
    front_it = 4;
    for (std::forward_list<int>::iterator it = foo.begin(); it != foo.end(); ++it)
        std::cout << *it << ' ';
    return 0;
}
```

insert\_iterator 迭代器

```cpp
#include <iostream>
#include <iterator>
#include <list>
using namespace std;
int main() {
    //初始化为 {5,5}
    std::list<int> foo(2,5);
    //定义一个基础迭代器，用于指定要插入新元素的位置
    std::list<int>::iterator it = ++foo.begin();
    //创建一个 insert_iterator 迭代器
    //std::insert_iterator< std::list<int> > insert_it(foo, it);
    std::insert_iterator< std::list<int> > insert_it = inserter(foo, it);
    //向 foo 容器中插入元素
    insert_it = 1;
    insert_it = 2;
    //输出 foo 容器存储的元素
    for (std::list<int>::iterator it = foo.begin(); it != foo.end(); ++it)
        std::cout << *it << ' ';
    return 0;
}
```

#### 6-3 流迭代器（istream\_iterator / ostream\_iterator）

ostream\_iterator

```cpp
std::ostream_iterator<int> out_it(std::cout,",");
std::copy(v1.begine(),v2.end(),out_it);
```

istream\_iterator

```cpp
std::istream_iterator<double> eos;
std::istream_iterator<double> iit(std::cin);
if(iit!=eos) value1 = *iit;
++iit;
if(iit!=eos) value2 = *iit;
```

#### 6-4 迭代器辅助函数

| 迭代器辅助函数        | 功能                                                         |
| :-------------------- | :----------------------------------------------------------- |
| advance(it, n)        | it 表示某个迭代器，n 为整数。该函数的功能是将 it 迭代器前进或后退 n 个位置。 |
| distance(first, last) | first 和 last 都是迭代器，该函数的功能是计算 first 和 last 之间的距离。 |
| begin(cont)           | cont 表示某个容器，该函数可以返回一个指向 cont 容器中第一个元素的迭代器。 |
| end(cont)             | cont 表示某个容器，该函数可以返回一个指向 cont 容器中最后一个元素之后位置的迭代器。 |
| prev(it)              | it 为指定的迭代器，该函数默认可以返回一个指向上一个位置处的迭代器。注意，it 至少为双向迭代器。 |
| next(it)              | it 为指定的迭代器，该函数默认可以返回一个指向下一个位置处的迭代器。注意，it 最少为前向迭代器。 |

### 7 C++常用算法

#### 7-1 排序函数

| 函数名                                                       | 用法                                                         | 备注                                                 |
| :----------------------------------------------------------- | :----------------------------------------------------------- | :--------------------------------------------------- |
| sort (first, last)                                           | 对容器或普通数组中 \[first, last) 范围内的元素进行排序，默认进行升序排序。 | sort() 只对 array、vector、deque 这 3 个容器提供支持 |
| stable\_sort (first, last)                                   | 和 sort() 函数功能相似，不同之处在于，对于 \[first, last) 范围内值相同的元素，该函数不会改变它们的相对位置。 |                                                      |
| partial\_sort (first, middle, last)                          | 从 \[first,last) 范围内，筛选出 muddle-first 个最小的元素并排序存放在 \[first，middle) 区间中。 |                                                      |
| partial\_sort\_copy (first, last, result\_first, result\_last) | 从 \[first, last) 范围内筛选出 result\_last-result\_first 个元素排序并存储到 \[result\_first, result\_last) 指定的范围中。 |                                                      |
| is\_sorted (first, last)                                     | 检测 \[first, last) 范围内是否已经排好序，默认检测是否按升序排序。 |                                                      |
| is\_sorted\_until (first, last)                              | 和 is\_sorted() 函数功能类似，唯一的区别在于，如果 \[first, last) 范围的元素没有排好序，则该函数会返回一个指向首个不遵循排序规则的元素的迭代器。 |                                                      |
| void nth\_element (first, nth, last)                         | 找到 \[first, last) 范围内按照排序规则（默认按照升序排序）应该位于第 nth 个位置处的元素，并将其放置到此位置。同时使该位置左侧的所有元素都比其存放的元素小，该位置右侧的所有元素都比其存放的元素大。 |                                                      |

sort() 函数

```cpp
#include <algorithm>
//对 [first, last) 区域内的元素做默认的升序排序
void sort (RandomAccessIterator first, RandomAccessIterator last);
//按照指定的 comp 排序规则，对 [first, last) 区域内的元素进行排序
void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

stable\_sort() 函数

```cpp
#include <algorithm>
//对 [first, last) 区域内的元素做默认的升序排序
void stable_sort ( RandomAccessIterator first, RandomAccessIterator last );
//按照指定的 comp 排序规则，对 [first, last) 区域内的元素进行排序
void stable_sort ( RandomAccessIterator first, RandomAccessIterator last, Compare comp );
```

partial\_sort() 函数

```cpp
#include <algorithm>
//按照默认的升序排序规则，对 [first, last) 范围的数据进行筛选并排序
void partial_sort (RandomAccessIterator first,
                   RandomAccessIterator middle,
                   RandomAccessIterator last);
//按照 comp 排序规则，对 [first, last) 范围的数据进行筛选并排序
void partial_sort (RandomAccessIterator first,
                   RandomAccessIterator middle,
                   RandomAccessIterator last,
                   Compare comp);
```

partial\_sort\_copy() 函数

```cpp
#include <algorithm>
//默认以升序规则进行部分排序
RandomAccessIterator partial_sort_copy (
                       InputIterator first,
                       InputIterator last,
                       RandomAccessIterator result_first,
                       RandomAccessIterator result_last);
//以 comp 规则进行部分排序
RandomAccessIterator partial_sort_copy (
                       InputIterator first,
                       InputIterator last,
                       RandomAccessIterator result_first,
                       RandomAccessIterator result_last,
                       Compare comp);
```

nth\_element() 函数

```cpp
#include <algorithm>
//排序规则采用默认的升序排序
void nth_element (RandomAccessIterator first,
                  RandomAccessIterator nth,
                  RandomAccessIterator last);
//排序规则为自定义的 comp 排序规则
void nth_element (RandomAccessIterator first,
                  RandomAccessIterator nth,
                  RandomAccessIterator last,
                  Compare comp);
```

is\_sorted()函数

```cpp
#include <algorithm>
//判断 [first, last) 区域内的数据是否符合 std::less<T> 排序规则，即是否为升序序列
bool is_sorted (ForwardIterator first, ForwardIterator last);
//判断 [first, last) 区域内的数据是否符合 comp 排序规则  
bool is_sorted (ForwardIterator first, ForwardIterator last, Compare comp);
```

is\_sorted\_until()函数

```cpp
#include <algorithm>
//排序规则为默认的升序排序
ForwardIterator is_sorted_until (ForwardIterator first, ForwardIterator last);
//排序规则是自定义的 comp 规则
ForwardIterator is_sorted_until (ForwardIterator first,
                                 ForwardIterator last,
                                 Compare comp);
```

#### 7-2 合并函数

merge()函数  
merge() 函数用于将 2 个有序序列合并为 1 个有序序列，前提是这 2 个有序序列的排序规则相同（要么都是升序，要么都是降序）。并且最终借助该函数获得的新有序序列，其排序规则也和这 2 个有序序列相同。

```cpp
#include <algorithm>
//以默认的升序排序作为排序规则
OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
                      InputIterator2 first2, InputIterator2 last2,
                      OutputIterator result);
//以自定义的 comp 规则作为排序规则
OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
                      InputIterator2 first2, InputIterator2 last2,
                      OutputIterator result, Compare comp);
```

inplace\_merge()函数（推荐使用）

```cpp
#include <algorithm>
//默认采用升序的排序规则
void inplace_merge (BidirectionalIterator first, BidirectionalIterator middle,
                    BidirectionalIterator last);
//采用自定义的 comp 排序规则
void inplace_merge (BidirectionalIterator first, BidirectionalIterator middle,
                    BidirectionalIterator last, Compare comp);
```

示例

```cpp
#include <iostream>     // std::cout
#include <algorithm>    // std::merge
using namespace std;
int main() {
    //该数组中存储有 2 个有序序列
    int first[] = { 5,10,15,20,25,7,17,27,37,47,57 };
    //将 [first,first+5) 和 [first+5,first+11) 合并为 1 个有序序列。
    inplace_merge(first, first + 5,first +11);
    for (int i = 0; i < 11; i++) {
        cout << first[i] << " ";
    }
    return 0;
}
```

#### 7-3 查找函数

find()函数  
该函数会返回一个输入迭代器，当 find() 函数查找成功时，其指向的是在 \[first, last) 区域内查找到的第一个目标元素；如果查找失败，则该迭代器的指向和 last 相同。

```cpp
#include <algorithm>
InputIterator find (InputIterator first, InputIterator last, const T& val);
```

示例

```cpp
#include <iostream>     // std::cout
#include <algorithm>    // std::find
#include <vector>       // std::vector
using namespace std;
int main() {
    //find() 函数作用于普通数组
    char stl[] ="http://c.biancheng.net/stl/";
    //调用 find() 查找第一个字符 'c'
    char * p = find(stl, stl + strlen(stl), 'c');
    //判断是否查找成功
    if (p != stl + strlen(stl)) {
        cout << p << endl;
    }
    //find() 函数作用于容器
    std::vector<int> myvector{ 10,20,30,40,50 };
    std::vector<int>::iterator it;
    it = find(myvector.begin(), myvector.end(), 30);
    if (it != myvector.end())
        cout << "查找成功：" << *it;
    else
        cout << "查找失败";
    return 0;
}
```

find\_if()函数  
和 find() 函数相同，find\_if() 函数也用于在指定区域内执行查找操作。不同的是，前者需要明确指定要查找的元素的值，而后者则允许自定义查找规则。

```cpp
InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
1
```

示例

```cpp
#include <iostream>     // std::cout
#include <algorithm>    // std::find_if
#include <vector>       // std::vector
using namespace std;
//自定义一元谓词函数
bool mycomp(int i) {
    return ((i % 2) == 1);
}
//以函数对象的形式定义一个 find_if() 函数的查找规则
class mycomp2 {
public:
    bool operator()(const int& i) {
        return ((i % 2) == 1);
    }
};
int main() {
    vector<int> myvector{ 4,2,3,1,5 };
    //调用 find_if() 函数，并以 IsOdd() 一元谓词函数作为查找规则
    vector<int>::iterator it = find_if(myvector.begin(), myvector.end(), mycomp2());
    cout << "*it = " << *it;
    return 0;
}
```

find\_if\_not()函数  
find\_if() 函数用于查找符合谓词函数规则的第一个元素，而 find\_if\_not() 函数则用于查找第一个不符合谓词函数规则的元素。

```cpp
InputIterator find_if_not (InputIterator first, InputIterator last, UnaryPredicate pred);
```

find\_end()函数  
常用于在序列 A 中查找序列 B 最后一次出现的位置

```cpp
//查找序列 [first1, last1) 中最后一个子序列 [first2, last2)
ForwardIterator find_end (ForwardIterator first1, ForwardIterator last1,
                          ForwardIterator first2, ForwardIterator last2);
//查找序列 [first2, last2) 中，和 [first2, last2) 序列满足 pred 规则的最后一个子序列
ForwardIterator find_end (ForwardIterator first1, ForwardIterator last1,
                          ForwardIterator first2, ForwardIterator last2,
                          BinaryPredicate pred);
```

find\_first\_of()函数  
在 A 序列中查找和 B 序列中任意元素相匹配的第一个元素

```cpp
//以判断两者相等作为匹配规则
InputIterator find_first_of (InputIterator first1, InputIterator last1,
                             ForwardIterator first2, ForwardIterator last2);
//以 pred 作为匹配规则
InputIterator find_first_of (InputIterator first1, InputIterator last1,
                             ForwardIterator first2, ForwardIterator last2,
                             BinaryPredicate pred);
```

adjacent\_find()函数  
adjacent\_find() 函数用于在指定范围内查找 2 个连续相等的元素。

```cpp
//查找 2 个连续相等的元素
ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last);
//查找 2 个连续满足 pred 规则的元素
ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last,
                               BinaryPredicate pred);
```

search()函数  
在序列 A 中查找序列 B 第一次出现的位置

```cpp
//查找 [first1, last1) 范围内第一个 [first2, last2) 子序列
ForwardIterator search (ForwardIterator first1, ForwardIterator last1,
                        ForwardIterator first2, ForwardIterator last2);
//查找 [first1, last1) 范围内，和 [first2, last2) 序列满足 pred 规则的第一个子序列
ForwardIterator search (ForwardIterator first1, ForwardIterator last1,
                        ForwardIterator first2, ForwardIterator last2,
                        BinaryPredicate pred);
```

search\_n()函数  
用于在指定区域内查找第一个符合要求的子序列。

```cpp
//在 [first, last] 中查找 count 个 val 第一次连续出现的位置
ForwardIterator search_n (ForwardIterator first, ForwardIterator last,
                          Size count, const T& val);
//在 [first, last] 中查找第一个序列，该序列和 count 个 val 满足 pred 匹配规则
ForwardIterator search_n ( ForwardIterator first, ForwardIterator last,
                           Size count, const T& val, BinaryPredicate pred );
```

lower\_bound()函数  
lower\_bound() 函数用于在指定区域内查找不小于目标值的第一个元素。

```cpp
//在 [first, last) 区域内查找不小于 val 的元素
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                             const T& val);
//在 [first, last) 区域内查找第一个不符合 comp 规则的元素
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                             const T& val, Compare comp);
```

upper\_bound()函数  
upper\_bound() 函数用于在指定范围内查找大于目标值的第一个元素。

```cpp
//查找[first, last)区域中第一个大于 val 的元素。
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,
                             const T& val);
//查找[first, last)区域中第一个不符合 comp 规则的元素
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,
                             const T& val, Compare comp);
```

equel\_range()函数  
equel\_range() 函数用于在指定范围内查找等于目标值的所有元素。

```cpp
//找到 [first, last) 范围中所有等于 val 的元素
pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);
//找到 [first, last) 范围内所有等于 val 的元素
pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
```

binary\_search() 函数  
binary\_search() 函数用于查找指定区域内是否包含某个目标元素。

```cpp
//查找 [first, last) 区域内是否包含 val
bool binary_search (ForwardIterator first, ForwardIterator last,
                      const T& val);
//根据 comp 指定的规则，查找 [first, last) 区域内是否包含 val
bool binary_search (ForwardIterator first, ForwardIterator last,
                      const T& val, Compare comp);
```

all\_of() 函数  
all\_of() 算法会返回 true，前提是序列中的所有元素都可以使谓词返回 true。

```cpp
std::all_of(std::begin(ages), std::end(ages),[good_age] (int age) { return age < good_age; })
```

any\_of()函数  
any\_of() 算法会返回 true，前提是序列中的任意一个元素都可以使谓词返回 true。

```cpp
std::any_of(std::begin(ages), std::end(ages),[min_age] (int age) { return age < min_age;})
```

none\_of() 函数  
none\_of() 算法会返回 true，前提是序列中没有元素可以使谓词返回 true。

```cpp
std::none_of(std::begin(ages), std::end(ages),[min_age](int age) { return age < min_age; })
```

equal 函数  
两个序列是否匹配。  
mismatch 函数  
mismatch() 算法判断两个序列是否匹配，如果不匹配，返回不匹配的位置。  
对于 mismatch(iter1，end\_iter1，iter2):

+   返回 pair<end\_iter1，(iter2 + (end\_ter1 - iter1))>，pair 的成员 second 等于 iter2 加上第一个序列的长度。如果第二个序列比第一个序列短，结果是未定义的。

对于 mismatch(iterl, end\_iter1, iter2, end\_iter2)：

+   当第一个序列比第二个序列长时，返回 pair<end\_iter1, (iter2 + (end\_iter1 - iter1))>，所以成员 second 为 iter2 加上第一个序列的长度。
+   当第二个序列比第一个序列长时，返回 pair<(iter1 + (end\_iter2 - iter2)),end\_iter2>， 所以成员 first 等于 iter1 加上第二个序列的长度。
+   当序列的长度相等时，返回 pair<end\_iter1, end\_iter2>。

#### 7-4 分组函数

partition() 函数  
partition() 函数可根据用户自定义的筛选规则，重新排列指定区域内存储的数据，使其分为 2 组，第一组为符合筛选条件的数据，另一组为不符合筛选条件的数据。  
partition() 函数还会返回一个正向迭代器，其指向的是两部分数据的分界位置，更确切地说，指向的是第二组数据中的第 1 个元素。

```cpp
ForwardIterator partition (ForwardIterator first,
                           ForwardIterator last,
                           UnaryPredicate pred);
```

stable\_partition() 函数

```cpp
BidirectionalIterator stable_partition (BidirectionalIterator first,
                                        BidirectionalIterator last,
                                        UnaryPredicate pred);
```

partition\_copy() 函数

```cpp
pair<OutputIterator1,OutputIterator2> partition_copy (
                    InputIterator first, InputIterator last,
                    OutputIterator1 result_true, OutputIterator2 result_false,
                    UnaryPredicate pred);
```

其中，各个参数的含义为：

+   first、last：都为输入迭代器，其组合 \[first, last) 用于指定该函数处理的数据区域；
+   result\_true：为输出迭代器，其用于指定某个存储区域，以存储满足筛选条件的数据；
+   result\_false：为输出迭代器，其用于指定某个存储区域，以存储满足筛选条件的数据；
+   pred：用于指定筛选规则，其本质就是接收一个具有 1 个参数且返回值类型为 bool 的函数。注意，该函数既可以是普通函数，还可以是一个函数对象。

示例

```cpp
#include <iostream>     // std::cout
#include <algorithm>    // std::partition_copy
#include <vector>       // std::vector
using namespace std;
//以普通函数的方式定义筛选规则
bool mycomp(int i) { return (i % 2) == 0; }
//以函数对象的形式定义筛选规则
class mycomp2 {
public:
    bool operator()(const int& i) {
        return (i % 2 == 0);
    }
};
int main() {
    vector<int> myvector{ 1,2,3,4,5,6,7,8,9 };
    int b[10] = { 0 }, c[10] = { 0 };
    //以 mycomp 规则，对 myvector 容器中的数据进行分组，这里的 mycomp 还可以改为 mycomp2()，即以 mycomp2 为筛选规则
    pair<int*, int*> result= partition_copy(myvector.begin(), myvector.end(), b, c, mycomp);
    cout << "b[10]：";
    for (int *p = b; p < result.first; p++) {
        cout << *p << " ";
    }
    cout << "\nc[10]：";
    for (int *p = c; p < result.second; p++) {
        cout << *p << " ";
    }
    return 0;
}
```

partition\_point()函数  
partition\_point()主要用于在已分好组的数据中找到分界位置。

```cpp
ForwardIterator partition_point (ForwardIterator first, ForwardIterator last,
                                 UnaryPredicate pred);
```

#### 7-5 排列函数

next\_permutation 函数  
next\_permutation() 会生成一个序列的重排列，它是所有可能的字典序中的下一个排列，默认使用 < 运算符来做这些事情。它的参数为定义序列的迭代器和一个返回布尔值的函数，这个函数在下一个排列大于上一个排列时返回 true，如果上一个排列是序列中最大的，它返回 false，所以会生成字典序最小的排列。

```cpp
std::vector<string> words {"one","two", "three", "four", "five", "six", "seven", "eight"};
auto words_copy = words; // Copy the original
do {
    std::copy(std::begin(words), std::end(words), std::ostream_iterator<string>{std::cout, " "});
    std::cout << std::endl;
    std::next_permutation(std::begin(words), std::end(words));
}while(words != words_copy); // Continue until back to the original
```

自定义比较函数来代替默认的比较函数。

```cpp
std::vector<string> words { "one", "two", "four", "eight"};
do {
    std::copy(std:rbegin(words), std::end(words), std::ostream_iterator<string> {std::cout, " "});
    std::cout << std::endl;
} while(std::next_permutation(std::begin(words), std::end(words),[](const string& s1, const strings s2) {return s1.back() < s2.back(); }));
```

prev\_permutation 函数  
next\_permutation() 是按照字典升序的方式生成的排列。prev\_permutation()以降序的方式生成排列 。

```cpp
std::vector<double> data {44.5, 22.0, 15.6, 1.5};
do {
    std::copy(std::begin(data), std::end(data), std::ostream_iterator<double> {std::cout, " "});
    std::cout << std::endl;
} while(std::prev_permutation(std::begin(data), std::end(data)));
```

is\_permutation 函数  
is\_permutation() 算法可以用来检查一个序列是不是另一个序列的排列，如果是，会返回 true。

```cpp
std::vector<double> data1{44.5, 22.0, 15.6, 1.5};
std::vector<double> data2{22.5, 44.5, 1.5, 15.6};
std::vector<double> data3{1.5, 44.5, 15.6, 22.0};
auto test = [] (const auto& d1, const auto& d2)
{
    std::copy(std::begin(d1), std::end(d1), std::ostream_iterator<double> {std::cout," "});
    std::cout << (is_permutation (std::begin (d1), std::end(d1), std::begin {d2), std::end(d2))?"is":"is not")>>" a permutation of ";
    std::copy(std::begin(d2), std::end(d2), std::ostream_iterator<double>{std::cout, " "});
    std::cout << std::endl;
};
test(data1, data2);
test(data1, data3);
test(data3, data2);
```

#### 7-6 复制函数

copy\_n函数  
copy\_n() 函数可以从源容器复制指定个数的元素到目的容器中。

```cpp
std::vector<string> names {"A1","Beth", "Carol", "Dan", "Eve","Fred","George" ,"Harry", "Iain", "Joe"};
std::unordered_set<string> more_names {"Janet", "John"};
std::copy_n(std:rbegin(names)+1, 3, std::inserter(more_names, std::begin(more_names)));
```

目的地址是流迭代器：

```cpp
std::copy_n(std::begin(more_names), more_names.size()-1,std::ostream_iterator<string> {std::cout, " "});
```

copy\_if函数  
copy\_if() 函数可以从源序列复制使谓词返回 true 的元素，所以可以把它看作一个过滤器。

```cpp
std::vector<string> names {"A1", "Beth", "Carol", "Dan", "Eve","Fred", "George", "Harry", "Iain", "Joe"};
std::unordered_set<string> more_names {"Jean", "John"};
size_t max_length{4};
std::copy_if(std::begin(names), std::end(names), std::inserter(more_names, std::begin(more_names)), [max_length](const string& s) { return s.length() <= max_length;});
```

copy\_backward函数  
copy\_backward() 会复制前两个迭代器参数指定的序列，但是从最后一个元素开始直到第一个元素，不会逆转序列。

```cpp
std::deque<string> song{ "jingle", "bells"，"jingle", "all", "the", "way"};
song.resize(song.size()+2); // Add 2 elements
std::copy_backward(std::begin(song), std::begin(song)+6, std::end(song));
std::copy(std::begin(song), std::end(song), std::ostream iterator <string> {std::cout, " "});
std::cout << std::endl;
```

reverse\_copy函数  
reverse\_copy() 算法可以将源序列复制到目的序列中，目的序列中的元素是逆序的。

```cpp
std::reverse_copy(std::begin(only_letters), std::end(only_letters), std::back_inserter(reversed));
```

原地逆转可以使用std::reverse

```cpp
string reversed {only_letters};
std::reverse(std::begin(reversed), std::end(reversed));
```

#### 7-7 复制函数

unique函数  
unique() 算法可以在序列中原地移除重复的元素，这就要求被处理的序列必须是正向迭代器所指定的。在移除重复元素后，它会返回一个正向迭代器作为新序列的结束迭代器。

```cpp
std::vector<string> words {"one", "two", "two", "three", "two", "two", "two"};
auto end_iter = std::unique(std::begin(words), std::end(words));
std::copy(std::begin(words), end_iter, std::ostream_iterator<string>{std::cout, " "});
std::cout << std::endl;
```

#### 7-8 填充函数

fill() 会填充整个序列； fill\_n() 则以给定的迭代器为起始位置，为指定个数的元素设置值。

```cpp
std::vector<string> data {12}; // Container has 12 elements
std::fill (std::begin (data), std::end (data), "none"); // Set all elements to "none"
12
```

#### 7-9 准换函数

transform函数  
transform() 可以将函数应用到序列的元素上，并将这个函数返回的值保存到另一个序列中，它返回的迭代器指向输出序列所保存的最后一个元素的下一个位置。

```cpp
std::vector<double> deg_C {21.0, 30.5, 0.0, 3.2, 100.0};
std::vector<double> deg_F(deg_C.size());
std::transform(std::begin(deg_C), std::end(deg_C), std:rbegin(deg_F),[](double temp){ return 32.0 + 9.0*temp/5.0; });
//Result 69.8 86.9 32 37.76 212
1234
```

#### 7-10 取代函数

replace,replace\_if和replace\_copy函数  
replace() 算法会用新的值来替换和给定值相匹配的元素。

```cpp
std::deque<int> data {10, -5, 12, -6, 10, 8, -7, 10, 11};
std::replace(std::begin(data), std::end(data), 10, 99);
// Result: 99 -5 12 -6 99 8 -7 99 11
123
```

replace\_if() 会将使谓词返回 true 的元素替换为新的值。

```cpp
string password { "This is a good choice !"};
std::replace_if(std::begin(password), std::end(password),[](char ch){return std::isspace(ch);}, '_');
//Result:This_is_a_good_choice!
123
```

replace\_copy() 算法和 replace() 做的事是一样的，但它的结果会被保存到另一个序列中，而不会改变原始序列。

```cpp
std::vector<string> words { "one","none", "two", "three", "none", "four"};
std::vector<string> new_words;
std::replace_copy (std::begin (words), std::end(words), std::back_inserter (new_words), string{"none"}, string{"0"});
// Result:"one", "0", "two","three","0","four"
1234
```