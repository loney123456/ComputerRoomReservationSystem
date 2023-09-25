#include "teacher.h"

//默认构造
Teacher::Teacher()
{
	
}

//有参构造
Teacher::Teacher(string empID, string name, string pwd)
{
	//初始化教师的属性（参数）
	this->m_empID = empID;
	this->m_Name = name;
	this->m_Pwd = pwd;

}

// 菜单界面
void Teacher::operMenu()
{
	cout << "欢迎老师:" << this->m_Name << " 登录" << endl;
	cout << "\t ----------------------------------------" << endl
		<< "\t|                                        |" << endl
		<< "\t|             1.查看所有预约             |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               2.审核预约               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               0.退出登录               |" << endl
		<< "\t|                                        |" << endl
		<< "\t ----------------------------------------" << endl
		<< "请选择您的操作:";
}

// 查看所有人的预约
void Teacher::showAllOrder()
{
	OrderFile of;

	of.displayOrder();
	system("pause");
	system("cls");
}

// 审核预约
void Teacher::checkOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	vector<int>v;
	int index = 0;
	cout << "待审核的预约记录如下：" << endl << endl;;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);

			cout << "第" << ++index << "条记录如下：" << endl;
			cout << "预约日期：周" << of.m_orderData[i]["weekday"] << " "
				<< "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " "
				<< "学生编号：" << of.m_orderData[i]["stuId"] << " "
				<< "学生姓名：" << of.m_orderData[i]["stuName"] << " "
				<< "机房编号：" << of.m_orderData[i]["roomId"] << " "
				<< "状态：" << "审核中" << endl << endl;
		}
	}
	
	int select = 0;//接收用户选择的预约记录
	int ret = 0;//接收要更改的预约结果的记录
	cout << endl<<"请输入要审核的预约记录：（0表示返回）";

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)//如果不想审核，直接退出循环就返回上一界面
			{
				break;
			}
			else
			{
				cout << "请输入审核的结果" << endl
					<< "1.通过" << endl
					<< "2.不通过" << endl;
				cin >> ret;
				if (ret == 1)
				{
					//通过的情况
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else if (ret == 2)
				{
					//不通过的情况
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();//更新预约记录
				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	system("pause");
	system("cls");
}