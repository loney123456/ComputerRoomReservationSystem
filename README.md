# ComputerRoomReservationSystem
高校机房预约系统

编译运行环境：VS2019 IDE、Window10

（SRC文件夹中是源代码，Release文件夹中是编译好的可以直接运行的可执行文件）

主要涉及的技术点：map容器、vector容器、文件读写操作、C++中封装、继承、多态的特性


此项目主要是依据C++的相关知识来制作的，


主要包含了C++的综合知识、面向对象的编程思想、


泛型的编程思想、STL中容器和算法的使用、文件的读写等。


源代码文件分类窗口如下：

![image](https://github.com/loney123456/ComputerRoomReservationSystem/assets/35869270/d8b2fdcf-8fe9-45dc-9a0f-2da0eae0bbd4)

系统的整体实现思路：

![20210618175454157](https://github.com/loney123456/ComputerRoomReservationSystem/assets/35869270/16228587-502f-4bc4-b5e4-bf3b7712a9e5)

系统介绍

身份简介
本系统分别有三种身份使用该软件：

1.学生：主要申请使用机房

2.教师：主要审核学生的预约申请

3.管理员：给学生、管理员来创建账号


机房简介
机房一共有三个


1.一号机房：最大容量50人


2.二号机房：最大容量50人


3.三号机房：最大容量100人

申请简介：
申请的预约记录是每周由管理员来负责清空的
学生可以预约未来一周之内的机房的使用，预约的日期为每周的周一到周五，预约时需要选择预约时间段（上午、下午）
教师可以审核学生的预约信息，可以根据具体情况来审核预约通过或不通过

使用介绍
首先进入系统的登录界面，可选的登录的身份有：
1.学生


2.老师


3.管理员


每个身份都需要进行验证，验证通过之后才可以进入子菜单

学生身份需要输入：学号、姓名、登录密码


老师身份需要输入：职工号、姓名、登录密码


管理员身份需要输入：管理员姓名、登录密码


学生具体的功能
1.申请预约


2.查看自身的预约


3.查看所有的预约


4.取消预约


5.退出登录


教师的具体功能：


1.查看学生的所有预约


2.审核学生的预约信息


3.退出登录


管理员的具体功能：

1.添加账号


2.查看所有账号


3.查看机房信息


4.清空预约记录


5.退出登录


软件的运行效果

①系统主界面

![image](https://github.com/loney123456/ComputerRoomReservationSystem/assets/35869270/082c97be-78cd-41ee-a266-9d0ec7947ca1)

②系统子界面-学生

![image](https://github.com/loney123456/ComputerRoomReservationSystem/assets/35869270/51e41a0e-cecf-4ede-82da-060c62bb4ef1)

③系统子界面-老师

![image](https://github.com/loney123456/ComputerRoomReservationSystem/assets/35869270/f75171a0-6e73-4282-a561-e77290d05eda)

③系统子界面-管理员

![image](https://github.com/loney123456/ComputerRoomReservationSystem/assets/35869270/abe4be76-c597-4d7e-b671-b2bca66c69ac)


未来的可优化方向：

①增加图形化界面（通过MFC或QT来进行实现）。


②增加数据库（在云端服务器上搭载数据库），学生信息、老师信息、管理员信息还有预约信息全部放在数据库中，可以方便显示和查询。


③管理员可以更改机房的相关信息，可以修改机房的机房号、机房的容量。


④完善学生和老师的个人信息，学生和老师可以自己修改自己的个人信息，同时管理员也可以修改学生或者老师的个人信息。


⑤学生身份和老师身份添加注销账号的功能，用户可根据自身的实际情况，清空账号信息。


⑥在机房管理系统中新建一个数组用于维护机房是否被预约的状态，在教师审核时，需要与数组信息对比，
在学生申请时，也需要和数组信息对比，已有审核通过的预约，无法再次申请，提示学生更换时间段，系统也会提示教师不通过审核。

