# Linux



## bash

### 判断语句

```shell
#  $? 变量存储了上一个命令的退出状态码,$? 的值为 0 表示上一个命令成功执行，非零值表示上一个命令执行失败。
if [ $? -eq 0 ]; then    #-eq 用于数值比较 ;= 用于字符串比较
    echo "Command 1 executed successfully"
else
    echo "Command 1 failed"
fi
```

涉及条件测试时

以下是一些示例说明不同情况的常见用法：

1.文件存在性检查：

```shell
# 检查文件是否存在
if [ -e "file.txt" ]; then
    echo "文件 file.txt 存在"
else
    echo "文件 file.txt 不存在"
fi
```

2.目录存在性检查：

```shell
# 检查目录是否存在
if [ -d "directory" ]; then
    echo "目录 directory 存在"
else
    echo "目录 directory 不存在"
fi
```

3.数值比较：

```shell
# 数值比较
a=10
b=20
if [ $a -lt $b ]; then
    echo "$a 小于 $b"
else
    echo "$a 不小于 $b"
fi
```

4.字符串比较：

```bash
# 字符串比较
str1="hello"
str2="world"
if [ "$str1" = "$str2" ]; then     #-eq 用于数值比较 ;= 用于字符串比较
    echo "字符串相等"
else
    echo "字符串不相等"
fi
```

5.逻辑运算：

```shell
# 逻辑运算
num=15
if [ $num -gt 10 ] && [ $num -lt 20 ]; then
    echo "$num 大于10且小于20"
fi

if [ $num -lt 10 ] || [ $num -gt 20 ]; then
    echo "$num 小于10或者大于20"
fi
```

这些示例展示了如何使用条件测试来处理不同情况下的逻辑判断。通过使用条件测试，你可以根据需要在Shell脚本中执行不同的操作。希望这些示例能帮助你更好地理解条件测试的用法。如果有任何疑问，请随时告诉我。



##  systemd 服务单元文件



systemd 服务单元文件是用来配置系统服务的文件，这些服务可以在 Linux 系统启动时自动运行，并在系统运行过程中提供特定功能或服务。这些文件通常存储在 `/etc/systemd/system/` 或 `/lib/systemd/system/` 目录下。

一个标准的 systemd 服务单元文件包含以下几个主要部分：

1. `[Unit]` 部分：这个部分主要用于描述服务单元的基本属性，例如服务的描述、依赖关系等。常见的字段包括：
   - `Description`：服务的描述。
   - `After`：指定服务应该在哪些其他单元之后启动。
2. `[Service]` 部分：这个部分定义了服务的具体行为，例如执行命令、启动类型等。常见的字段包括：
   - `Type`：指定服务的启动类型，如 simple、forking、oneshot 等。
   - `ExecStart`：指定服务启动时要执行的命令或程序。
   - `Restart`：指定服务在意外退出时是否应该重新启动。
3. `[Install]` 部分：这个部分定义了服务在系统启动时如何启用。常见的字段包括：
   - `WantedBy`：指定服务应该由哪个目标单元启用。

以下是一个简单的示例 systemd 服务单元文件的结构：

```plaintext
plaintextCopy Code[Unit]
Description=My Sample Service
After=network.target

[Service]
Type=simple
ExecStart=/usr/bin/my-service
Restart=always

[Install]
WantedBy=multi-user.target
```

在这个示例中，服务的名称是 `My Sample Service`，它依赖于网络的启动（`network.target`）。服务类型为简单（`simple`），启动时执行 `/usr/bin/my-service` 命令，如果服务意外退出，则始终重新启动。最后，该服务应该由多用户目标单元（`multi-user.target`）启用。

创建和管理 systemd 服务单元文件可以让你更方便地配置和控制系统服务的行为。



## SCP 命令

`scp` 是一个用于在Unix和Linux系统之间安全地复制文件和目录的命令行工具。它使用SSH（Secure Shell）协议进行数据传输，因此能够提供加密的连接，确保数据传输的安全性。

基本的 `scp` 命令语法如下：

```bash
 scp [参数] 源文件/目录 目标文件/目录
```

其中，`[参数]` 可以是一系列用于控制传输行为的选项，比如 `-r` 用于递归复制整个目录，`-P` 用于指定远程主机的端口等。

以下是几个 `scp` 命令的示例：

### 1.从本地系统复制文件到远程系统：

```bash
scp /path/to/local/file username@remotehost:/path/to/remote/location
```

### 2.从远程系统复制文件到本地系统：

```bash
scp username@remotehost:/path/to/remote/file /path/to/local/location
```

### 3.递归复制整个目录：

```bash
scp -r /path/to/local/directory username@remotehost:/path/to/remote/location
```

需要注意的是，`scp` 命令会要求你输入远程系统的密码（或者使用公钥认证），并且需要确保远程系统启用了SSH服务。python



# python装饰器

@装饰器接收函数和函数参数传入，实现在函数运行前和运行后的操作

```python
def my_decorator(func):
    def wrapper(*args, **kwargs):
        print("在函数运行前执行一些处理")
        print(f"传入参数: {args}, {kwargs}")
        result = func(*args, **kwargs)
        print("在函数运行后执行一些处理")
        return result
    return wrapper

@my_decorator
def my_function(x, y):
    print(f"这是我的函数，参数为：{x}, {y}")  

my_function(10, 20)
```

在装饰器中，通常会使用`*args`和`**kwargs`来接收任意数量的位置参数和关键字参数。这样做的好处是可以让装饰器适用于不同数量和类型的参数。

- `*args`表示接受任意数量的位置参数，它会将传入的位置参数打包成一个元组（tuple），并传递给函数内部。在函数内部，你可以通过`args`这个元组来访问和操作这些位置参数。
- `**kwargs`表示接受任意数量的关键字参数，它会将传入的关键字参数打包成一个字典（dictionary），并传递给函数内部。在函数内部，你可以通过`kwargs`这个字典来访问和操作这些关键字参数。

在装饰器函数中，`*args`和`**kwargs`通常用于接收被装饰函数传入的参数，并在内部对这些参数进行处理。当调用被装饰函数时，装饰器会将这些参数传递给被装饰函数，从而实现装饰器对函数行为的扩展或修改。

下面是一个简单的示例，演示了如何在装饰器函数中使用`*args`和`**kwargs`：

```python
def my_decorator(func):
    def wrapper(*args, **kwargs):
        print("装饰器接收到的位置参数：", args)
        print("装饰器接收到的关键字参数：", kwargs)
        result = func(*args, **kwargs)
        return result
    return wrapper

@my_decorator
def example_func(x, y, z=0):
    print(f"被装饰函数执行，参数为：{x}, {y}, {z}")

example_func(1, 2, z=3)
```

## 文件操作

### **遍历文件保存为字典**

```python
import os

def build_directory_structure(folder_path):
    directory_structure = {}
    for root, dirs, files in os.walk(folder_path):  #遍历文件夹下的所有文件夹和文件

        current_dir = directory_structure          
        for dir_name in root.split(os.sep):
            if dir_name:
                current_dir = current_dir.setdefault(dir_name, {})    #层级嵌套

        for file_name in files:
            current_dir[file_name] = None             #文件key值 在上面current_dir 指向 for 循化嵌套最后一个
 
    return directory_structure
```

### **字典路径结构格式化输出**

```python

def print_directory_structure(directory, indent=''):
    for key, value in directory.items():
        if isinstance(value, dict):
            print(f'{indent}└──·{key}')
            print_directory_structure(value, indent + '    ')
        else:
            print(f'{indent}└── {key}')

# 示例目录结构字典
directory_structure = {
    'documents': {
        'work': {
            'report.docx': None,
            'presentation.pptx': None
        },
        'personal': {
            'photos': {
                'summer.jpg':None,
                'winter.png':None
            },
            'diary.txt':None,
            'Path': {}
        }
    }
}
# 输出目录结构
print_directory_structure(directory_structure)

#####################################################
'''输出
└──·documents
    └──·work
        └── report.docx
        └── presentation.pptx
    └──·personal
        └──·photos
            └── summer.jpg
            └── winter.png
        └──·diary.txt
        └──·Path
'''
```

### **字典嵌套**

dict.setfault( key , { } )  

```python
##############获取键值
my_dict = {'a': 1, 'b': 2}

# 获取键 'a' 的值
value_a = my_dict.setdefault('a', 10)
print(value_a)  # 输出：1

# 获取键 'c' 的值，由于键 'c' 不存在，将其添加到字典中并设置默认值为 20
value_c = my_dict.setdefault('c', 20)
print(value_c)  # 输出：20            因此valu_c，valu_a 都指向my_dict.setdefault 所设置的默认key值，如果dict_name 已经存在key值，则指向已经存在的key 值

print(my_dict)  # 输出：{'a': 1, 'b': 2, 'c': 20}

###########################################################################################
###########字典嵌套
data = {}
key = 'user_info'

# 确保 'key' 总是与一个字典相关联
data.setdefault(key, {}).setdefault('name', 'Unknown')

print(data)  # 输出: {'user_info': {'name': 'Unknown'}}

#在这个例子中，setdefault(key, {}) 确保 key（即 'user_info'）与一个空字典相关联。然后，我们可以继续在这个嵌套字典上调用 setdefault，以确保 'name' 键也存在，并为其设置一个默认值。
```

在这个例子中，current_dir=current_dir.setdefault('one',{})和current_dir.setdefault('TWO',{})之间的区别在于返回的对象。

current_dir=current_dir.setdefault('one',{})：这行代码将在当前目录下创建一个名为 'one' 的子目录，并将 current_dir 更新为新创建的子目录。这意味着 current_dir 现在指向了 'one' 这个子目录的字典对象。

current_dir.setdefault('TWO',{})：这行代码是在当前目录下创建一个名为 'TWO' 的子目录，但它没有更新 current_dir 的指向。因此，current_dir 仍然指向之前创建的 'one' 子目录的字典对象。

以下是你提供的代码的完整示例，包括上面的修改：

```python

# 创建一个空的字典，表示目录结构
directory_structure = {}

# 假设有一个文件路径
file_path = "root/folder1/folder2/file1.txt"

# 将文件路径分割成各级目录名
folders = file_path.split('/')

# 从根目录开始逐级构建嵌套字典
current_dir = directory_structure
for folder in folders:
    if folder:
        current_dir = current_dir.setdefault(folder, {})   #for 循环结束后，current_dir 指向最后一级嵌套目录

# 创建 'one' 子目录并更新 current_dir
current_dir = current_dir.setdefault('one', {})   #在最后一级目录内嵌套 one:{},并将cuuent_dir 指向one:{} 目录下

current_dir.setdefault('TWO', {})    # 在 'one' 子目录下创建 'TWO' 子目录，,但并未改变current_dir 的指向，因此此时根目录仍然指向one:{}

current_dir.setdefault('Three')   # 在 'one' 子目录下创建 'Three' 键

print(directory_structure)
```

# FRP

要配置 FRP 实现广域网远程 SSH，你需要进行以下步骤：

### 1.**安装 FRP：** 

首先，你需要在你的服务器和本地计算机上安装 FRP。你可以从 FRP 的官方 GitHub 仓库（https://github.com/fatedier/frp）下载所需的二进制文件。

### 2.**配置 FRP 服务器端：**

​	在你的服务器上，创建一个配置文件（例如 `frps.ini`），并按照以下示例进行配置：

```ini
[common]
bind_port = 7000
```

这个配置将设置 FRP 服务器监听端口为 7000。你还可以根据需要进行其他更高级的配置，如加密、身份验证等。

### 3.**启动 FRP 服务器：** 

在服务器上运行 FRP 服务器程序，并指定配置文件：

```bash
./frps -c frps.ini
```

### 4.**配置 FRP 客户端：** 

在本地计算机上创建一个客户端配置文件（例如 `frpc.ini`），并按照以下示例进行配置：

```ini
[common]
server_addr = your_server_ip
server_port = 7000

[ssh]
type = tcp
local_ip = 127.0.0.1
local_port = 22
remote_port = 6000
```

在这个配置中，`your_server_ip` 是你的 FRP 服务器的 IP 地址。`local_ip` 和 `local_port` 是你本地计算机上 SSH 服务的 IP 地址和端口号。`remote_port` 是你在 FRP 配置中将要映射的远程端口号。

### 5.**启动 FRP 客户端：** 

在本地计算机上运行 FRP 客户端程序，并指定配置文件：

```bash
./frpc -c frpc.ini
```

### 6.**测试连接：**

 现在，你可以使用 SSH 客户端连接到你的服务器上的远程端口。使用以下命令：

```bash
ssh user@your_server_ip -p 6000
#这里的 `user` 是你的服务器上的用户名，`your_server_ip` 是你的服务器的 IP 地址，`6000` 是你在 FRP 配置中指定的远程端口号。
```

通过这些步骤，你应该能够成功配置 FRP 实现广域网远程 SSH 连接。请确保你的服务器和本地计算机都有稳定的网络连接，并且防火墙已经正确配置以允许 FRP 数据流经过。



# Rust



## 结构体



在 Rust 中，关联函数（associated functions）是定义在 `impl` 块中的函数，不是对象实例的方法，而是与结构体或枚举类型相关联的函数。通过关联函数，我们可以在创建实例时执行一些额外的处理或逻辑。下面我将举一个简单的例子来说明如何在关联函数中执行额外的处理：

假设我们有一个 `Rectangle` 结构体，并希望在创建 `Rectangle` 实例时，检查宽度和高度是否合法（例如都大于 0），如果不合法则给出相应的提示信息。这时候就可以使用关联函数来实现这个逻辑。

```rust
rustCopy Code#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    //通过Option<Rectangle> 枚举类型存储返回值some或者None
    fn create(width: u32, height: u32) -> Option<Rectangle> {
        if width > 0 && height > 0 {
            Some(Rectangle { width, height })
        } else {
            println!("Error: Width and height must be greater than 0.");
            None
        }
    }
}

fn main() {
    // 创建一个合法的 Rectangle 实例
    let rect1 = Rectangle::create(30, 50);
    println!("{:?}", rect1);

    // 创建一个不合法的 Rectangle 实例
    let rect2 = Rectangle::create(0, 20);
    // 注意：此时 rect2 是一个 Option<Rectangle> 类型
    if let Some(rectangle) = rect2 {
        println!("{:?}", rectangle);
    }
}
```

在上面的代码中，`Rectangle` 结构体的关联函数 `create` 返回 `Option<Rectangle>` 类型，允许返回一个合法的 `Rectangle` 实例或者 `None`。在 `create` 函数中，我们首先检查传入的宽度和高度是否大于 0，如果是，则返回一个包含初始化后的 `Rectangle` 实例的 `Some`；如果不合法，则打印错误信息并返回 `None`。

在 `main` 函数中，我们演示了如何使用 `Rectangle::create` 关联函数来创建合法和不合法的 `Rectangle` 实例，并根据返回的 `Option<Rectangle>` 进行处理。

这是一个简单的例子，展示了如何在关联函数中执行额外的处理或逻辑。实际应用中，你可以根据具体需求在关联函数中实现更复杂的逻辑，以确保创建实例时满足特定条件或进行特定操作。





## rust库编写

### 库文件结构

一个库文件的源码结构通常包括以下组成部分：

1. **`src/` 目录**：包含库的源代码文件。这些文件通常以 Rust 代码（`.rs` 文件）的形式存在，定义了库中的各种函数、结构体、trait 等。
2. **`Cargo.toml` 文件**：这是 Rust 项目的配置文件，用于指定项目的元数据、依赖关系和构建选项。
3. **`tests/` 目录**：包含用于测试库功能的测试代码。这些代码通常涵盖库中各个模块的不同功能，以确保库的正确性。
4. **`examples/` 目录**：包含示例代码，用于展示如何使用库中的功能。这些示例代码可以帮助其他开发者更快地上手并了解如何使用该库。

举例来说，假设有一个名为 `my_library` 的 Rust 库，其源码结构可能如下所示：

```tree
my_library/
    ├── Cargo.toml
    ├── src/
    │   ├── lib.rs
    │   ├── module1.rs
    │   └── module2.rs
    ├── tests/
    │   └── test_module1.rs
    ├── examples/
    │   └── example1.rs
    └── README.md
```

在这个例子中，`src/` 目录包含了库的主要代码，`tests/` 目录包含了测试代码，`examples/` 目录包含了示例代码。`Cargo.toml` 文件用于配置项目，`README.md` 则可以提供关于该库的说明文档。

### pub(crate)控制代码的可见性

假设你有一个 Rust 项目，包含两个模块：`module1.rs` 和 `module2.rs`，它们都属于同一个 crate。在这种情况下，你可以使用 `pub(crate)` 来控制项的可见性范围。

下面是一个简单的示例：

 module1.rs

```rust
// module1.rs
mod module2;

pub(crate) struct MyStruct {
    pub name: String,
}

impl MyStruct {
    pub(crate) fn new(name: String) -> MyStruct {
        MyStruct { name }
    }

    pub fn get_name(&self) -> &str {
        &self.name
    }
}

```

 module2.rs

```rust

// module2.rs
use super::MyStruct;

pub fn print_name(my_struct: &MyStruct) {
    println!("Name: {}", my_struct.get_name());
}
在 Rust 中，use super::MyStruct; 这行代码用于在一个模块中引入其父模块中定义的 MyStruct 结构体。让我解释一下这行代码的含义：
super 关键字表示当前模块的父模块。如果一个模块位于另一个模块内部，那么使用 super 可以引用父模块。
:: 用于访问父模块中的项（比如结构体、函数等）。
MyStruct 是要引入的结构体的名称。
因此，use super::MyStruct; 表示从当前模块的父模块中引入名为 MyStruct 的项，使得在当前模块中可以直接使用 MyStruct 而无需指定完整的路径。

这个语法在 Rust 中非常有用，特别是在模块嵌套结构较深的情况下，可以简化对父模块中定义的项的引用，提高代码的可读性和易用性。
```



在这个示例中：

- `MyStruct` 结构体和其构造函数 `new` 被标记为 `pub(crate)`，这意味着它们可以在当前 crate 的任何地方访问，但对 crate 外部的其他 crate 则是不可见的。
- `get_name` 方法被标记为 `pub`，表示它是公共的，可以在整个 crate 内外访问。
- 在 `module2.rs` 中，我们导入了 `MyStruct` 结构体，并定义了一个函数 `print_name`，该函数可以访问 `MyStruct` 的公共方法 `get_name`。

通过使用 `pub(crate)`，我们可以确保 `MyStruct` 结构体只能在当前 crate 中使用，同时允许其内部的模块共享对该结构体的访问权限。这有助于控制代码的可见性，同时保持模块之间的良好封装性。



### 库例子

1.创建一个简单的 Rust 库，包含一个公共函数用于计算两个整数的和：

`src/lib.rs` 文件内容如下：

```rust
// 引入 module1 模块
mod module1;

// 在 lib.rs 中重新导出 module1 模块的内容
pub use module1::add_numbers;
```

2.创建一个存放具体函数实现的模块文件 `module1.rs`：

`src/module1.rs` 文件内容如下：

```rust
// 定义一个函数 add_numbers，用于计算两个整数的和
pub fn add_numbers(a: i32, b: i32) -> i32 {
    a + b
}
```

3.创建一个示例程序来使用这个库：

`examples/example1.rs` 文件内容如下：

```rust
// 引入我们创建的库
extern crate my_library;

use my_library::add_numbers;

fn main() {
    let result = add_numbers(5, 10);
    println!("The sum is: {}", result);
}
```

在这个例子中，`lib.rs` 作为库的入口文件，通过 `mod module1;` 引入了一个名为 `module1` 的模块，然后通过 `pub use module1::add_numbers;` 将 `module1` 模块中的 `add_numbers` 函数重新导出，使其成为库的公共接口之一。

`module1.rs` 则是一个模块文件，包含了具体的 `add_numbers` 函数的实现。

最后，`examples/example1.rs` 文件演示了如何引入这个库并使用其中的函数。

















