#include "manager.h"
#include <fstream>
#include "globalFile.h"
#include <algorithm>

//默认构造
Manager::Manager() 
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员的信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器  获取到所有文件中 学生、老师的相关信息
	this->initVector();

	//初始化存放机房信息的容器，获取所有存储的机房信息
	this->initComputerRoom();
}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员:" << this->m_Name << " 登录" << endl;
	cout <<"\t ----------------------------------------" << endl
		<< "\t|                                        |" << endl
		<< "\t|               1.添加账号               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               2.查看账号               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               3.查看机房               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               4.清空预约               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               0.退出登录               |" << endl
		<< "\t|                                        |" << endl
		<< "\t ----------------------------------------" << endl
		<< "请选择您的操作:" ;
}

//添加账号
void Manager::addAccount()
{
	//
	cout << "请输入添加的账号类型" << endl
		 << "1.添加学生" << endl
		 << "2.添加老师" << endl;

	string fileName;//操作文件名
	string tip;//提示输入怎样的id号
	string errorTip;//重复输入id的错误提示

	ofstream ofs;//文件操作对象

	int select = 0;
	cin >> select;//接收用户的选项

	if (select == 1)
	{
		//添加的是学生
		fileName = STUDENT_FILE;
		tip = "请输入学生的学号：";
		errorTip = "学号重复，请重新输入！";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工的编号:";
		errorTip = "职工号重复，请重新输入！";
	}
	else
	{
		cout << "选择错误，请重新输入!" << endl;
	}

	//利用追加的方式来向fileName 进行写文件
	ofs.open(fileName, ios::out | ios::app);

	if (!ofs.is_open())
	{
		cout << "文件不可输出" << endl;
		return;
	}

	string id;//此id为 学号或者是职工号
	string name;//姓名
	string pwd;//密码

	while (true)
	{
		cout << tip;
		cin >> id;

		bool ret = this->checkRepeat(id, select);
		if (ret)//有重复 
		{
			cout << errorTip << endl;
		}
		else break;
	}

	cout << "请输入姓名：";
	cin >> name;

	cout << "请输入密码：";
	cin >> pwd;

	//向文件中写入数据
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功!" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//调用初始化容器接口，重新获取文件中的数据
	//将这个数据保存到vStu向量中
	this->initVector();

	//if(select == 1)
	//{
	//	vStu.push_back(Student(id, name, pwd));
	//}
	//else if (select == 2)
	//{
	//	vTea.push_back(Teacher(id, name, pwd));
	//}
}

void PrintStudent(const Student& s)
{
	cout << "学生学号：" << s.m_ID << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}

void PrintTeacher(const Teacher& t)
{
	cout << "教师职工号：" << t.m_empID << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}

//查看账号
void Manager::showAccount() 
{
	cout << "请选择要查看的内容:" << endl
		<< "1、查看所有的学生" << endl
		<< "2、查看所有的老师" << endl;

	ifstream ifs;
	int select = 0;//接收用户的选择
	cin >> select;

	if (select == 1)
	{
		//查看学生
		cout <<endl << "所有学生的信息如下;" << endl;

		//方法一  读取文件来输出信息
		ifs.open(STUDENT_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "文件打开失败！" << endl;
			return;
		}

		string id;
		string name;
		string pwd;

		while (ifs >> id && ifs >> name && ifs >> pwd)
		{
			cout << "学生学号：" << id << " 姓名：" << name << " 密码：" << pwd << endl;
		}

		ifs.close();
		
		//方法二 直接获取向量中的数据 输出信息
		//for (auto it = vStu.begin(); it != vStu.end(); it++)
		//{
		//	cout << "学生学号：" << it->m_ID << " 姓名：" << it->m_Name << " 密码：" << it->m_Pwd << endl;
		//}

		//方法三 通过for_each算法来获取信息进行输出
		//for_each(vStu.begin(), vStu.end(), PrintStudent);
		
		cout << endl;
	}
	else if (select == 2)
	{
		//查看老师
		cout << endl << "所有老师的信息如下;" << endl;
		
		//方法一 读取文件来输出相关的信息
		ifs.open(TEACHER_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "文件打开失败！" << endl;
			return;
		}

		string id;
		string name;
		string pwd;

		while (ifs >> id && ifs >> name && ifs >> pwd)
		{
			cout << "教师职工号：" << id << " 姓名：" << name << " 密码：" << pwd << endl;
		}

		ifs.close();

		//方法二 直接获取向量中的数据 来输出信息
		//for (auto it = vTea.begin(); it != vTea.end(); it++)
		//{
		//	cout << "职工号：" << it->m_empID << " 姓名：" << it->m_Name << " 密码：" << it->m_Pwd << endl;
		//}

		//方法三 通过for_each算法来遍历向量来获取数据，从而输出信息
		//for_each(vTea.begin(), vTea.end(), PrintTeacher);
	
		cout << endl;
	}

	system("pause");
	system("cls");
}

//查看机房的信息
void Manager::showComputerRoom()
{
	cout<<endl << "机房的信息如下：" << endl;
	for (auto it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房的编号：" << it->m_ComId
			<< " 机房的最大容量：" << it->m_maxNum << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
}

//清空预约记录
void Manager::clearAppointmentRecord()
{
	cout <<endl << "是否要清空预约记录？(Y/N)";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		ofstream ofs;
		ofs.open(ORDER_FILE, ios::out | ios::trunc);

		ofs.close();
		cout << "预约记录清空成功！" << endl;
		system("pause");
		system("cls");
	}
	else return;
	
	return;
}

//初始化容器函数
void Manager::initVector()
{
	//确保容器是清空的状态
	vStu.clear();
	vTea.clear();

	//读取文件信息 学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_ID && ifs >> s.m_Name && ifs >> m_Pwd)
	{
		vStu.push_back(s);
	}

	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	//读取文件信息 老师
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_empID && ifs >> m_Name && ifs >> m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "当前老师的数量：" << vTea.size() << endl;
	ifs.close();
}

//检测重复 参数1 检测学号/职工号 参数2 检测类型
bool Manager::checkRepeat(string id, int type)
{
	if (type == 1)
	{//检测学生
		for (auto it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_ID)
			{
				return true;
			}
		}
	}
	else
	{//检测老师
		for (auto it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_empID)
			{
				return true;
			}
		}
	}
	return false;
}

//初始化机房信息的容器
void Manager::initComputerRoom()
{
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}

	ComputerRoom com;

	while (ifs >> com.m_ComId && ifs >> com.m_maxNum)
	{
		vCom.push_back(com);
	}

	ifs.close();
	cout << "机房的数量为：" << vCom.size() << endl;
}
