#include "student.h"

//Ĭ�Ϲ���
Student::Student()
{
	
}
//�вι��� ������ѧ�š��û���������
Student::Student(string id, string name, string pwd)
{
	//��ʼ������
	this->m_ID = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ����������Ϣ
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_maxNum)
	{
		//����ȡ������Ϣ�ŵ�������
		vCom.push_back(com);
	}

	ifs.close();

}
//�˵�����
void Student::operMenu()
{
	cout << "��ӭѧ��:" << this->m_Name << " ��¼" << endl;
	cout << "\t ----------------------------------------" << endl
		<< "\t|                                        |" << endl
		<< "\t|               1.����ԤԼ               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|             2.�鿴�ҵ�ԤԼ             |" << endl
		<< "\t|                                        |" << endl
		<< "\t|             3.�鿴����ԤԼ             |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               4.ȡ��ԤԼ               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               0.�˳���¼               |" << endl
		<< "\t|                                        |" << endl
		<< "\t ----------------------------------------" << endl
		<< "��ѡ�����Ĳ���:";

}

//����ԤԼ(ԤԼ��״̬�У������ ԤԼ�ɹ� ԤԼʧ�� ȡ����ԤԼ)
void Student::applyOrder()//����ԤԼ
{
	cout << "��������ʱ�䣺��һ������" << endl
		<<endl<< "����������ԤԼ��ʱ��" << endl
		<< "  1.��һ" << endl
		<< "  2.�ܶ�" << endl
		<< "  3.����" << endl
		<< "  4.����" << endl
		<< "  5.����" << endl;

	int weekday = 0; //���� ��һ������
	int interval = 0;//ʱ��� time interval ʱ���
	int room = 0;//�������

	while (true)
	{
		cin >> weekday;
		if (weekday >= 1 && weekday <= 5)
		{
			break;
		}
		cout << "���������������������룡" << endl;
	}

	cout <<endl<< "����������ԤԼ��ʱ��Σ�" << endl
		 << "  1.����" << endl
		 << "  2.����" << endl;
	
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "ʱ��������������������룡" << endl;
	}

	cout<<endl << "��ѡ�������" << endl;
	//range base for��ʽ��forѭ��
	for (const auto& com : vCom)
	{
		cout << com.m_ComId << "�Ż���������Ϊ��" << com.m_maxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room >= 1 && room < vCom.size())
		{
			break;
		}
		cout << "�����������������������룡" << endl;
	}

	cout << "ԤԼ�ɹ�������У�" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);//app - append׷�� ׷�ӵķ�ʽ���ļ���д������

	if (!ofs.is_open())
	{
		cout << "ԤԼ��������Ϣ�ļ���ʧ�ܣ�" << endl;
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
//�鿴�Լ���ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	int cnt = 0;//��¼����ԤԼ�ĸ���
	for (int i = 0; i < of.m_Size; i++)
	{
		//string תΪ int
		//string����.c_str()תΪC�����ַ���const char *
		//���� atoi (const char *)����ת��Ϊint����
		if (this->m_ID == of.m_orderData[i]["stuId"])
		{
			cnt++;
			cout << "��" << cnt << "��ԤԼ����Ϣ���£�" << endl;
			cout << "ԤԼʱ�䣺��" << of.m_orderData[i]["weekday"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������ţ�" << of.m_orderData[i]["roomId"];
			
			string status = " ״̬��";
			//1.����� 2.��ԤԼ -1 ԤԼʧ�� 0 ��ȡ��
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "ԤԼ�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ����";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl << endl;
		}
	}

	if (cnt == 0) cout << "������ԤԼ��¼" << endl;
	system("pause");
	system("cls");
}
//�鿴���е�ԤԼ
void Student::showAllOrder()
{
	OrderFile of;
	of.displayOrder();

	system("pause");
	system("cls");
}
//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������Ҫȡ��ԤԼ�ļ�¼��" << endl;
	
	vector<int>v;//���������map�����е��±���
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//���ж��������ѧ��
		if (of.m_orderData[i]["stuId"] == this->m_ID)
		{
			//��ɸѡ���� ԤԼ״̬Ϊ����ԤԼ�����ߡ�ԤԼ�ɹ�����ԤԼ��¼
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << "��" << index++ << "����¼��" << endl;
				cout << "  ԤԼ���ڣ���" << of.m_orderData[i]["weekday"] << " "
					 << "  ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " "
					 << "  ������ţ�" << of.m_orderData[i]["roomId"] << " ";
				string status = " ״̬��";
				if(of.m_orderData[i]["status"]=="1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;

			}
		}
	}
	cout << "������ȡ���ļ�¼(0��ʾ����)��";
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
				//cout << "��¼���ڴ�map�����е�λ�ã�" << v[select - 1] << endl;
				
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				
				cout << "ȡ��ԤԼ�ɹ���" << endl;
				break;
			}
		}

		cout << "�����������������룡" << endl;
	}
	system("pause");
	system("cls");
}