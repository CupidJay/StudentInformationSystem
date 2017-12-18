# 学生信息管理系统

## 介绍

这是一款Qt实现的简单的学生信息管理系统，它的功能包括：

1. 学生信息的增加
2. 学生信息的修改
3. 学生信息的删除
4. 用文件保存学生信息
5. 从文件读取学生信息
6. 可按学号或姓名排序显示学生信息



## 编译与安装

1. 安装Qt Creator。[[下载地址]](https://www1.qt.io/download/)

   ​

2. 获取源码

   ```Bash
   git clone https://github.com/CupidJay/StudentInformationSystem.git
   ```



3. 用Qt Creator打开management.pro文件即可

   ​

## 程序功能

#### 程序主界面

![](https://github.com/CupidJay/hello-world/blob/master/main.png)



![](https://github.com/CupidJay/hello-world/blob/master/main2.png)



#### 程序工具栏

程序工具栏包括四个按钮：

- 添加按钮，弹出对话框输入界面实现学生信息的添加。
- 删除按钮，删除一个学生信息，删除前会弹出警示框以防误删。
- 编辑按钮，弹出对话框实现学生信息的修改，此外双击学生所在行也可以实现修改。
- 排序按钮，弹出对话框选择排序方式进行学生信息排序。



#### 程序菜单栏

- 文件菜单栏包括新建选项，保存选项和打开选项。
- 编辑菜单栏提供的功能同程序工具栏。
- 帮助菜单栏有这个软件的介绍。