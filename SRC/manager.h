#pragma once
#include "identity.h"
#include <iostream>
#include <vector>
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

using namespace std;

class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//添加账号
	void addAccount();

	//查看账号
	void showAccount();

	//查看机房的信息
	void showComputerRoom();

	//修改机房的信息

	//清空预约记录
	void clearAppointmentRecord();

	//初始化容器
	void initVector();

	//初始化机房的相关信息
	void initComputerRoom();

	//检测重复 参数1 检测学号/职工号 参数2 检测类型
	bool checkRepeat(string id, int type);

private:
	//学生容器
	vector<Student> vStu;

	//老师容器
	vector<Teacher> vTea;

	//机房信息的容器
	vector<ComputerRoom>vCom;

};