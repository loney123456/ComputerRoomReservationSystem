#include "teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher()
{
	
}

//�вι���
Teacher::Teacher(string empID, string name, string pwd)
{
	//��ʼ����ʦ�����ԣ�������
	this->m_empID = empID;
	this->m_Name = name;
	this->m_Pwd = pwd;

}

// �˵�����
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ:" << this->m_Name << " ��¼" << endl;
	cout << "\t ----------------------------------------" << endl
		<< "\t|                                        |" << endl
		<< "\t|             1.�鿴����ԤԼ             |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               2.���ԤԼ               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               0.�˳���¼               |" << endl
		<< "\t|                                        |" << endl
		<< "\t ----------------------------------------" << endl
		<< "��ѡ�����Ĳ���:";
}

// �鿴�����˵�ԤԼ
void Teacher::showAllOrder()
{
	OrderFile of;

	of.displayOrder();
	system("pause");
	system("cls");
}

// ���ԤԼ
void Teacher::checkOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	vector<int>v;
	int index = 0;
	cout << "����˵�ԤԼ��¼���£�" << endl << endl;;

	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);

			cout << "��" << ++index << "����¼���£�" << endl;
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["weekday"] << " "
				<< "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " "
				<< "ѧ����ţ�" << of.m_orderData[i]["stuId"] << " "
				<< "ѧ��������" << of.m_orderData[i]["stuName"] << " "
				<< "������ţ�" << of.m_orderData[i]["roomId"] << " "
				<< "״̬��" << "�����" << endl << endl;
		}
	}
	
	int select = 0;//�����û�ѡ���ԤԼ��¼
	int ret = 0;//����Ҫ���ĵ�ԤԼ����ļ�¼
	cout << endl<<"������Ҫ��˵�ԤԼ��¼����0��ʾ���أ�";

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)//���������ˣ�ֱ���˳�ѭ���ͷ�����һ����
			{
				break;
			}
			else
			{
				cout << "��������˵Ľ��" << endl
					<< "1.ͨ��" << endl
					<< "2.��ͨ��" << endl;
				cin >> ret;
				if (ret == 1)
				{
					//ͨ�������
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else if (ret == 2)
				{
					//��ͨ�������
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();//����ԤԼ��¼
				cout << "������" << endl;
				break;
			}
		}
		cout << "�����������������룡" << endl;
	}

	system("pause");
	system("cls");
}