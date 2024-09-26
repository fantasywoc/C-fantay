# linux

## Modify user

```
sudo chown -R  root:root
```

##  Kill

###   Kill -9 

  使用 `pgrep` 命令（如果已安装）或 `ps` 命令配合 `grep` 来实现这一点。例如：

```Bash
pgrep dgs  
# 或者  
ps aux | grep dgs

#杀死进程
kill -9 <PID>     
```

### pgrep -f dgs | xargs kill -9 

一个常用的方法是使用 `pgrep` 命令结合 `-f` 选项来搜索完整的命令行，然后使用 `xargs` 或循环来将这些 PID 传递给 `kill` 命令。

例如，使用 `pgrep` 和 `xargs`：

杀死含有xxx字符串的进程

```Bash
pgrep -f dgs | xargs kill -9
```

或者，可以使用 `while` 循环和 `read` 命令：

```Bash
pgrep -f dgs | while read -r pid; do  
    kill -9 "$pid"  
done
```

## Bash 前缀名称修改

```
sudo vi /etc/debian_chroot`修改为`-^
source .bashrc
```

## nfs文件共享/挂载

 安装：`nfs-kernel-server`

 **编辑** **NFS** **导出配置**：在 NFS 服务器上，编辑 `/etc/exports` 文件：

 `sudo vim /etc/exports `

 **修改导出配置**：将导出行修改为允许所有主机读写，添加下面这行：

 `/home/kf/Documents/nfs_point *(rw,sync,no_subtree_check,insecure)`这里的 `rw` 选项允许读写，`sync` 确保数据同步，`no_subtree_check` 防止子目录检查，`insecure` 允许使用非特权端口的客户端访问。

 不加`insecure`windows挂载会出现 网络错误 -53

 **重新导出文件系统**：保存更改后，重新导出 NFS 共享以应用更改，更新配置：

 `sudo exportfs -ra`

 **检查防火墙设置**：确保 NFS 服务器的防火墙允许 NFS 流量。

 **重新启动** **NFS** **服务**（如果需要）：

 `sudo systemctl restart nfs-kernel-server.service`

 Linux  mount：`mount  ip:/share/path   /local/mont/path`

 Windows mount: `mount  ip:/share/path  F: `  F：未使用的盘符 ，CMD 执行

## cmake

源码包3.21.7



链接：https://www.zhihu.com/question/592372765/answer/2967956773

**（1）卸载已经安装的旧版的CMake（非必需）。**

```Plain
sudo apt-get autoremove cmake
```

**（2）下载CMake压缩包：根据需要下载对应的按照包，示例中下载的是3.21.3版本。**

```Plain
wget https://cmake.org/files/v3.21/cmake-3.21.3-linux-x86_64.tar.gz
```

**（3）解压压缩包：**

```Plain
tar zxvf cmake-3.21.3-linux-x86_64.tar.gz
```

查看解压后目录:

```Plain
cmake-3.21.3-linux-x86_64
├── bin
│   ├── ccmake
│   ├── cmake
│   ├── cmake-gui
│   ├── cpack
│   └── ctest
├── doc
│   └── cmake
├── man
│   ├── man1
│   └── man7
└── share
    ├── aclocal
    ├── applications
    ├── bash-completion
    ├── cmake-3.21
    ├── emacs
    ├── icons
    ├── mime
    └── vim
15 directories, 5 files
```

bin下面有各种cmake家族的产品程序。

**（4）创建软链接**

注意，文件路径是可以指定的, 一般选择在/opt 或 /usr 路径下, 这里选择/opt 。

```Plain
sudo mv cmake-3.21.3-Linux-x86_64 /opt/cmake-3.21.3
sudo ln -sf /opt/cmake-3.21.3/bin/*  /usr/bin/
```

检查版本号：

```Plain
$ cmake --version
cmake version 3.21.3
CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

至此，Linux按照CMake完成。

## Git

`git` 是一个强大的版本控制系统，广泛用于软件开发中。以下是 `git` 的一些常用命令及其基本描述：

### 初始化

- `git init`：初始化一个新的 Git 仓库在当前目录下。

### 克隆

- `git clone [url]`：从 URL 克隆一个 Git 仓库到本地。

### 配置

- `git config --global user.name "[name]"`：设置全局的用户名。
- `git config --global user.email "[email]"`：设置全局的用户邮箱。

### 状态

- `git status`：查看工作区和暂存区的状态。

### 添加

- `git add [file|folder]`：将文件或文件夹添加到暂存区。
- `git add .`：将当前目录下的所有文件添加到暂存区。

### 提交

- `git commit -m "[message]"`：将暂存区的修改提交到本地仓库，并附带一条消息。
- 青鸾提交Cpp `git commit -m "noScan. ``message``"`
- `git` 提交删除改变
- `rm -rf folder_name` 删除文件
- 如果你只想添加被删除的文件夹的改变，可以使用：`git add -u`

### 查看提交历史

- `git log`：查看提交历史。
- `git log --pretty=oneline`：以一行的方式查看提交历史。

### 分支

- `git branch`：查看当前仓库的所有分支。
- `git branch [branch-name]`：创建一个新分支。
- `git checkout [branch-name]`：切换到指定分支。
- `git checkout -b [branch-name]`：创建并切换到新分支。
- `git merge [branch-name]`：将指定分支合并到当前分支。
- `git branch -d [branch-name]`：删除一个分支。

### 远程仓库

- `git remote add [remote-name] [url]`：添加一个新的远程仓库。
- `git remote -v`：查看已添加的远程仓库信息。
- `git push [remote-name] [branch-name]`：将本地分支推送到远程仓库。
- `git pull [remote-name] [branch-name]`：从远程仓库拉取分支到本地。

### 标签

- `git tag [tag-name]`：创建一个标签。
- `git tag -a [tag-name] -m "[message]"`：创建一个带有消息的标签。
- `git show [tag-name]`：查看标签信息。
- `git tag -d [tag-name]`：删除一个标签。

### 撤销操作

- `git reset --hard [commit-id]`：将本地仓库重置到某个提交，工作区和暂存区都会被改变。
- `git revert [commit-id]`：创建一个新的提交来撤销某个提交。

### 清理

- `git clean -fd`：清理未跟踪的文件和目录。

### 忽略文件

- 创建一个 `.gitignore` 文件，并在其中列出要忽略的文件或文件夹的模式。

### 其他

- `git help [command]`：查看指定命令的帮助信息。
- `git diff`：查看工作区与暂存区、暂存区与最新提交之间的差异。

这些命令只是 `git` 的一小部分，但涵盖了大部分常用的操作。随着对 `git` 的深入了解，您会发现更多高级功能和命令。

## ubuntu 右键添加快捷方式

将Sublime Text添加到Ubuntu的右键菜单中，可以通过以下步骤完成：

步骤 1：安装Sublime Text

确保你已经在Ubuntu中安装了Sublime Text。如果还没有安装，可以通过以下步骤进行安装：

​    从Sublime Text的官方网站下载对应Ubuntu版本的.deb安装包。

​    打开终端，进入下载文件所在的目录。

​    使用sudo dpkg -i sublime-text.deb命令来安装Sublime Text。

步骤 2：创建自定义脚本

在Ubuntu中，我们需要在.gnome2/nautilus-scripts目录下创建一个自定义脚本来处理右键点击事件。由于较新的Ubuntu版本可能已经更改了相关路径或配置方式，我们将按照较为通用的方法进行操作：

1. ​    打开终端。
2. ​    使用mkdir -p ~/.local/share/nautilus/scripts命令（如果目录不存在则创建它）来确保脚本目录存在。
3. ​    进入该目录：cd ~/.local/share/nautilus/scripts。
4. ​    使用文本编辑器（如nano、vim或gedit）创建一个新的脚本文件，例如命名为OpenWithSublimeText：

对于`nano：nano OpenWithSublimeText`

​    在脚本文件中，输入以下内容（确保将<Sublime_Full_Path>替换为Sublime Text的实际安装路径）：

```Bash
#!/bin/bash  
<Sublime_Full_Path> 可以通过在终端输入 "whereis subl" 或 "which subl" 找到

    /usr/bin/subl "$NAUTILUS_SCRIPT_SELECTED_FILE_PATHS"

    保存并关闭文件。
```

步骤 3：设置脚本为可执行

在终端中，使用chmod +x ~/.local/share/nautilus/scripts/OpenWithSublimeText命令将脚本设置为可执行。

步骤 4：测试右键菜单

现在，当你在文件管理器中右键点击一个文件或目录时，你应该会在弹出的菜单中看到一个名为“Scripts”的子菜单（或在类似位置，这取决于你的系统配置和使用的文件管理器版本）。在这个子菜单中，你应该能看到“OpenWithSublimeText”选项。点击它，Sublime Text应该会打开并加载你选择的文件或目录。

## 跨主机键鼠共享

```bash
wget  http://archive.ubuntu.com/ubuntu/pool/universe/s/synergy/synergy_1.8.8-stable+dfsg.1-1build1_amd64.deb
sudo dpkg -i synergy_1.8.8-stable+dfsg.1-1build1_amd64.deb
```

中间会提示缺少依赖，如果直接使用 sudo apt-get -f -y install ，直接提示卸载了synergy，而不是下载依赖。

因为20.04换成了qt5，所以这里需要添加qt4的ppa源。

```bash
sudo add-apt-repository ppa:rock-core/qt4
sudo apt-get update
sudo apt-get install libcanberra-gtk-module
sudo dpkg -i synergy_1.8.8-stable+dfsg.1-1build1_amd64.deb
sudo apt-get -f install
```

反正大概就这样差不多就装好了。

- 共享键鼠的作为server，被共享的主机作为client
- 服务端设置client的hostname
- 如果报了链接失败的错误；将/home/用户/.config/Synergy/Synergy.conf : `cryptoEnabled=false `#将true改为false ,杀掉进程重启。即可

参考链接：https://blog.csdn.net/u010586698/article/details/122686546       

​                  https://blog.csdn.net/guojingyue123/article/details/120013254

## ubuntu wifi 驱动

一、新装Ubuntu20.04后发现wifi连不上，提示网络激活失败，经一番研究发现是网卡驱动问题。解决办法如下：

点击左下角“显示应用程序”按钮，找到“软件和更新”双击打开，单击“附加驱动”选项卡，选择使用Broa*****“”这行等自动处理完后关闭。

如果“附加驱动”里没有相关驱动，打开终端输入下面命令安装，然后重启电脑。

```bash
    sudo apt update
    sudo apt-get install bcmwl-kernel-source
```

二、wifi经常在使用一段时间后自动无法上网，很可能是电源管理模块关闭了wifi硬件，通过修改硬件配置信息可以解决，方法如下：

打开终端输入命令：

```bash
    sudo iwconfig
    #查看到网卡名称后，输入命令关闭电源管理。我的网卡名称wlp5s0
    sudo iwconfig wlp5s0 power off
```

这样wifi就不会掉线了。

## 绕过加密软件

 python3 ENCODING.py path

## 依赖问题

要创建一个可以被正常挂载的 ISO 文件，需要按照 ISO 9660 文件系统的规范来构建。ISO 9660 是一种标准的光盘文件系统，用于光盘镜像文件，包括 ISO 文件。

下面是创建一个可以被正常挂载的空 ISO 文件的步骤：

1. **创建空的** **ISO** **文件**： 使用 `dd` 命令结合 `genisoimage` 或 `mkisofs` 工具来生成一个 ISO 文件，并确保填充正确的文件系统和目录结构。

```bash
dd if=/dev/zero of=empty.iso bs=1M count=100
```

这将创建一个大小为 100MB 的空 ISO 文件 `empty.iso`。

1. **使用** **`genisoimage`** **创建** **ISO** **文件结构**： `genisoimage` 是一个创建 ISO 文件系统镜像的工具，它能够将文件和目录组织成符合 ISO 9660 标准的格式。

```bash
genisoimage -o empty.iso -V VOLUME_NAME -r -J -l -iso-level 3 path/to/directory
```

如果你只需要一个空的 ISO 文件，可以跳过指定目录路径的步骤，只需确保 `-o`、`-V` 和其他参数正确设置。

1. **挂载** **ISO** **文件**： 确保你有足够的权限，并使用 `mount` 命令挂载 ISO 文件到一个目录。

```bash
sudo mount -o loop empty.iso /mnt/iso
```

`/mnt/iso` 是你预先创建好的挂载点。

1.可以尝试用下面方法处理依赖问题，紧跟前一条安装命令后面输入下面命令，然后再执行安装命令：

```bash
sudo apt-get install -f
```

2.在安装软件之前，或者遇到依赖问题之时，可以尝试安装build-essential解决问题，它聚合了一些常用的依赖：

```bash
sudo apt-get install build-essential
```

 3.用aptitude来代替apt-get，aptitude也是一个包管理工具，它在处理依赖问题时比apt-get更优秀

```bash
sudo aptitude install 需要安装的软件名
```

## Sudoer 文件损坏

 **`neousys ALL=(ALL:ALL) NOPASSWD:ALL`**

https://zhuanlan.zhihu.com/p/148889634

## Cmake 

mkdir -p build  &&   cd build  &&  cmake ..  cmake -DCMAKE_INSTALL_PREFIX=/you/install/path/  &&  make 





## adb  command

```bash 
#capture device screen and pull it locally
filename="$(date +%Y%m%d_%H%M%S).png"  
adb shell screencap -p /sdcard/temp_screenshot.png  
adb pull /sdcard/temp_screenshot.png "$filename"  
adb shell rm /sdcard/temp_screenshot.png
```

### Capture screen

```Bash
#!/bin/bash  
  
# 执行adb devices命令并捕获其输出  
adb_output=$(adb devices)  
# 检查输出中是否包含"device"（忽略大小写）  
if echo "$adb_output" | grep -qi 'device'; then  
    echo "ADB 已成功连接到设备。"  
    # 输出设备型号  
    echo "设备型号: $(adb shell getprop ro.product.model)"  
    # 输出Android版本  
    echo "Android版本: $(adb shell getprop ro.build.version.release)" 
    adb shell "df /data | grep /data" 
else  
    echo "ADB 未连接到任何设备。"  
fi
filename="$(date +%Y%m%d_%H%M%S).png"  
adb shell screencap -p /sdcard/temp_screenshot.png  
adb pull /sdcard/temp_screenshot.png ~/Desktop/screen_$filename
adb shell rm /sdcard/temp_screenshot.png
echo "Capture screen  saved as ~/Desktop/screenrecord_$current_time.mp4"
```

### Screen record

```Bash
#!/bin/bash  
  
# 执行adb devices命令并捕获其输出  
adb_output=$(adb devices)  
  
# 检查输出中是否包含"device"（忽略大小写）  
if echo "$adb_output" | grep -qi 'device'; then  
    echo "ADB 已成功连接到设备。"  
    # 输出设备型号  
    echo "设备型号: $(adb shell getprop ro.product.model)"  
    # 输出Android版本  
    echo "Android版本: $(adb shell getprop ro.build.version.release)" 
    adb shell "df /data | grep /data" 
else  
    echo "ADB 未连接到任何设备。"  
fi
# 录制屏幕三分钟  
adb shell screenrecord /sdcard/screenrecord_3min.mp4 --time-limit 180  
sleep 5  
# 获取当前时间  
current_time=$(date +%Y%m%d_%H%M%S)  
# 拉取文件并重命名  
adb pull /sdcard/screenrecord_3min.mp4 ~/Desktop/screenrecord_$current_time.mp4  
# 删除设备上的源文件  
adb shell rm /sdcard/screenrecord_3min.mp4  
echo "Screen recording saved as ~/Desktop/screenrecord_$current_time.mp4"
```

