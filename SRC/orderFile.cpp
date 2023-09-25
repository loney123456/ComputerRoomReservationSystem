#include "orderFile.h"

void readOrderInfo(string& orderData, unordered_map<string, string>&m)
{
	string key;//键
	string value;//值

	int pos = orderData.find(":");

	if (pos != -1)
	{
		key = orderData.substr(0, pos);
		value = orderData.substr(pos + 1, orderData.size() - pos);

		m.insert(make_pair(key, value));
	}
}

//无参构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读入失败！" << endl;
		return;
	}

	string weekday; //预约的日期（周一到周五中的哪一天）
	string interval;//预约的时间段
	string stuId;//预约的学生编号
	string stuName;//预约的学生姓名
	string computerRoomID;//预约的机房编号
	string status;//预约信息的状态

	this->m_Size = 0;//预约记录的条数


	while (ifs >> weekday && ifs >> interval && ifs >> stuId &&
		ifs >> stuName && ifs >> computerRoomID && ifs >> status)
	{
		unordered_map<string, string> m;

		readOrderInfo(weekday, m);//截取周几
		readOrderInfo(interval, m);//截取间隔
		readOrderInfo(stuId, m);//截取学生编号
		readOrderInfo(stuName, m);//截取学生姓名
		readOrderInfo(computerRoomID, m);//截取机房编号
		readOrderInfo(status, m);//截取预约的状态

		//将小map容器放到大的map容器中
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}

	ifs.close();

	////测试最大的map容器
	//for (const auto& orderData : m_orderData)
	//{
	//	cout << "No : " << orderData.first << " Actual value : " << endl << endl;
	//	for (const auto& orderInfo : orderData.second)
	//	{
	//		cout << "  key = " << orderInfo.first << " value = " << orderInfo.second << endl;
	//	}
	//	cout << endl;
	//}

}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;//预约记录0条，直接return
	}

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);

	for (int i = 0; i < m_Size; i++)
	{
		ofs << "weekday:" << this->m_orderData[i]["weekday"] << " "
			<< "interval:" << this->m_orderData[i]["interval"] << " "
			<< "stuId:" << this->m_orderData[i]["stuId"] << " "
			<< "stuName:" << this->m_orderData[i]["stuName"] << " "
			<< "roomId:" << this->m_orderData[i]["roomId"] << " "
			<< "status:" << this->m_orderData[i]["status"] << endl;
	}

	ofs.close();
}

void OrderFile::displayOrder()
{
	if (this->m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < this->m_Size; i++)
	{
		cout << endl;
		cout << "第" << i + 1 << "条记录：" << endl;
		cout << "预约日期：周" << this->m_orderData[i]["weekday"] << " "
			<< "时间段：" << (this->m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " "
			<< "学生编号：" << this->m_orderData[i]["stuId"] << " "
			<< "学生姓名：" << this->m_orderData[i]["stuName"] << " "
			<< "机房编号：" << this->m_orderData[i]["roomId"] << " ";
		string status = " 状态：";

		//1.审核中 2.已预约 -1.预约失败 0.取消预约
		if (this->m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (this->m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (this->m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else if (this->m_orderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
}