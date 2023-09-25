#include "student.h"

//默认构造
Student::Student()
{
	
}
//有参构造 参数：学号、用户名、密码
Student::Student(string id, string name, string pwd)
{
	//初始化属性
	this->m_ID = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房的信息
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_maxNum)
	{
		//将读取到的信息放到容器中
		vCom.push_back(com);
	}

	ifs.close();

}
//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生:" << this->m_Name << " 登录" << endl;
	cout << "\t ----------------------------------------" << endl
		<< "\t|                                        |" << endl
		<< "\t|               1.申请预约               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|             2.查看我的预约             |" << endl
		<< "\t|                                        |" << endl
		<< "\t|             3.查看所有预约             |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               4.取消预约               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               0.退出登录               |" << endl
		<< "\t|                                        |" << endl
		<< "\t ----------------------------------------" << endl
		<< "请选择您的操作:";

}

//申请预约(预约的状态有：审核中 预约成功 预约失败 取消的预约)
void Student::applyOrder()//申请预约
{
	cout << "机房开放时间：周一到周五" << endl
		<<endl<< "请输入申请预约的时间" << endl
		<< "  1.周一" << endl
		<< "  2.周二" << endl
		<< "  3.周三" << endl
		<< "  4.周四" << endl
		<< "  5.周五" << endl;

	int weekday = 0; //日期 周一到周五
	int interval = 0;//时间段 time interval 时间段
	int room = 0;//机房编号

	while (true)
	{
		cin >> weekday;
		if (weekday >= 1 && weekday <= 5)
		{
			break;
		}
		cout << "日期输入有误，请重新输入！" << endl;
	}

	cout <<endl<< "请输入申请预约的时间段：" << endl
		 << "  1.上午" << endl
		 << "  2.下午" << endl;
	
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "时间段输入有误，请重新输入！" << endl;
	}

	cout<<endl << "请选择机房：" << endl;
	//range base for形式的for循环
	for (const auto& com : vCom)
	{
		cout << com.m_ComId << "号机房的容量为：" << com.m_maxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room >= 1 && room < vCom.size())
		{
			break;
		}
		cout << "机房号输入有误，请重新输入！" << endl;
	}

	cout << "预约成功，审核中！" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);//app - append追加 追加的方式向文件中写入数据

	if (!ofs.is_open())
	{
		cout << "预约机房的信息文件打开失败！" << endl;
		return;
	}

	ofs << "weekday:" << weekday << " "
		<< "interval:" << interval << " "
		<< "stuId:" << m_ID << " "
		<< "stuName:" << m_Name << " "
		<< "roomId:" << room << " "
		<< "status:" << 1 << endl;
	ofs.close();

	system("pause");
	system("cls");

}
//查看自己的预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	int cnt = 0;//记录自身预约的个数
	for (int i = 0; i < of.m_Size; i++)
	{
		//string 转为 int
		//string利用.c_str()转为C风格的字符串const char *
		//利用 atoi (const char *)函数转换为int类型
		if (this->m_ID == of.m_orderData[i]["stuId"])
		{
			cnt++;
			cout << "第" << cnt << "条预约的信息如下：" << endl;
			cout << "预约时间：周" << of.m_orderData[i]["weekday"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房编号：" << of.m_orderData[i]["roomId"];
			
			string status = " 状态：";
			//1.审核中 2.已预约 -1 预约失败 0 已取消
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "预约审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败，审核未通过！";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "预约已取消";
			}
			cout << status << endl << endl;
		}
	}

	if (cnt == 0) cout << "无自身预约记录" << endl;
	system("pause");
	system("cls");
}
//查看所有的预约
void Student::showAllOrder()
{
	OrderFile of;
	of.displayOrder();

	system("pause");
	system("cls");
}
//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入要取消预约的记录号" << endl;
	
	vector<int>v;//存放在最大的map容器中的下标编号
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断是自身的学号
		if (of.m_orderData[i]["stuId"] == this->m_ID)
		{
			//再筛选自身 预约状态为“已预约”或者“预约成功”的预约记录
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << "第" << index++ << "条记录：" << endl;
				cout << "  预约日期：周" << of.m_orderData[i]["weekday"] << " "
					 << "  时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " "
					 << "  机房编号：" << of.m_orderData[i]["roomId"] << " ";
				string status = " 状态：";
				if(of.m_orderData[i]["status"]=="1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;

			}
		}
	}
	cout << "请输入取消的记录(0表示返回)：";
	int select = 0;
	while (true) 
	{
		cin >> select;

		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//cout << "记录所在大map容器中的位置：" << v[select - 1] << endl;
				
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				
				cout << "取消预约成功！" << endl;
				break;
			}
		}

		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}