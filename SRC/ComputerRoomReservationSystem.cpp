#include <iostream>
#include <fstream>
#include <string>
#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using namespace std;

//进入学生子菜单界面
void studentMenu(Identity* &student)
{
	while (true)
	{
		//调用学生的子菜单
		student->operMenu();

		Student* stu = (Student*)student;

		int select = 0;
		cin >> select;//接收用户的选择

		switch (select)
		{
		case 1://申请预约
			stu->applyOrder();
			break;

		case 2://查看自身的预约
			stu->showMyOrder();
			break;

		case 3://查看所有人的预约
			stu->showAllOrder();
			break;

		case 4://取消预约
			stu->cancelOrder();
			break;

		case 0://退出登录
			delete student;
			cout << "退出登录成功！" << endl;
			system("pause");
			system("cls");
			return;

		default:
			break;
		}
	}
}

//进入教师子菜单的界面
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//调用子菜单的界面
		teacher->operMenu();

		//强制类型转换为子类的指针，方便调用子类的成员函数
		Teacher* tea = (Teacher*)teacher;

		int select = 0;//接收用户的选择
		cin >> select;

		if (select == 1)//查看所有的预约
		{
			tea->showAllOrder();
		}
		else if (select == 2)//审核预约
		{
			tea->checkOrder();
		}
		else
		{
			delete teacher;
			cout << "退出登录成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入管理员子菜单界面
void managerMenu(Identity * &manager)
{
	while (true) 
	{
		//调用管理员的子菜单
		manager->operMenu();
	
		//将父类指针 转换为子类指针,调用子类里面的其他接口
		Manager* man = (Manager*)manager;

		int select = 0;
		
		//接收用户的选择
		cin >> select;
		
		switch (select)
		{
		case 1://添加账号
			//cout << "添加账号" << endl;
			man->addAccount();
			break;

		case 2://查看账号
			//cout << "查看账号" << endl;
			man->showAccount();
			break;

		case 3://查看机房的信息
			//cout << "查看机房" << endl;
			man->showComputerRoom();
			break;

		case 4://清空预约信息
			//cout << "清空预约" << endl;
			man->clearAppointmentRecord();
			break;

		default:
			delete manager;
			cout << "退出成功!" << endl;
			system("pause");
			system("cls");
			return;
			break;
		}
	}
}

//预约系统主界面显示
void MainMenuDisplay()
{
	cout << "-------------------欢迎使用机房预约系统-----------------" << endl
		 << endl << "请输入您的身份：" << endl
		 << "\t --------------------------------------" << endl
		 << "\t|                                      |" << endl
		 << "\t|             1. 学      生            |" << endl
		 << "\t|                                      |" << endl
		 << "\t|             2. 老      师            |" << endl
		 << "\t|                                      |" << endl
		 << "\t|             3. 管  理  员            |" << endl
		 << "\t|                                      |" << endl
		 << "\t|             0. 退      出            |" << endl
		 << "\t|                                      |" << endl
		 << "\t---------------------------------------" << endl
		 << "请输入您的选择：";

}

//登录功能 参数1 操作文件名 参数2 操作的身份类型
void LoginIn(string fileName, int  type)
{
	//fileName --- 操作的文件名  type --- 登录的身份
	// (1-学生 2-老师 3-管理员)
	
	//父类指针 用于指向子类对象
	Identity *Person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接收用户输入的信息
	string id = "";
	string name = "";
	string pwd = "";

	//判断身份
	if (1 == type)//学生身份
	{
		cout << "请输入你的学号：";
		cin >> id;
	}
	else if(2 == type)//职工身份
	{
		cout << "请输入你的职工号：";
		cin >> id;
	}

	cout << "请输入用户名：";
	cin >> name;

	cout << "请输入密码："; 
	cin >> pwd;

	if (1 == type)
	{
		//学生身份验证
		string fId;//从文件中读取的ID号
		string fName;//从文件中获取的姓名
		string fPwd;//从文件中获取密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息进行对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生信息验证登录成功！" << endl;
				system("pause");
				system("cls");
				Person = new Student(id, name, pwd);
			
				//进入学生身份的子菜单
				studentMenu(Person);

				return;
			}

		}
	}
	else if (2 == type)
	{
		//教职工身份验证
		string fId;//从文件中读取的ID号
		string fName;//从文件中获取的姓名
		string fPwd;//从文件中获取密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "老师信息验证登录成功!" << endl;	
				system("pause");
				system("cls");

				Person = new Teacher(id, name, pwd);
				//进入教师子菜单
				teacherMenu(Person);
				return;
			}
		}

	}
	else if (3 == type)
	{
		//管理员身份验证
		string fName;
		string fPwd;

		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员信息验证登录成功!" << endl;
				system("pause");
				system("cls");
				Person = new Manager(name, pwd);

				//进入管理员子菜单界面
				managerMenu(Person);

				return;
			}
		}
	}

	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");

	return;
}
int main(void)
{
	int select = 0;//用于接收用户的选择
	while (true)
	{
		MainMenuDisplay();

		cin >> select;

		switch (select)
		{
		case 1://学生身份
			LoginIn(STUDENT_FILE, 1);
			break;

		case 2://老师身份
			LoginIn(TEACHER_FILE, 2);
			break;

		case 3://管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;

		case 0://退出系统
			cout << "欢迎再次使用！" << endl;
			return 0;

		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}