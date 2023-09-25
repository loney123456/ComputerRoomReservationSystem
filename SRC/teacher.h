#pragma once
#include "identity.h"
#include "orderFile.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//教师类的设计
class Teacher :public Identity
{
public:	
	//默认构造
	Teacher(); 

	//有参构造
	Teacher(string empID, string name, string pwd);
	
	// 菜单界面
	virtual void operMenu();

	// 查看所有人的预约
	void showAllOrder();

	// 审核预约
	void checkOrder();

	//职工编号
	string m_empID;
};