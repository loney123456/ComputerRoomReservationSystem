#pragma once
#include "identity.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "globalFile.h"
#include "computerRoom.h"
#include "orderFile.h"
#include <cstdlib>

using namespace std;

//设计学生类
class Student :public Identity
{
public:
	//操作：
	//默认构造
	Student();
	
	//有参构造 参数：学号、用户名、密码
	Student(string id, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//申请预约
	void applyOrder();

	//查看自己的预约
	
	void showMyOrder();

	//查看所有的预约
	
	void showAllOrder();

	//取消预约

	void cancelOrder();

	//属性:
	
	//学生学号
	string m_ID;

	//定义存储机房信息的容器
	vector<ComputerRoom>vCom;
};
