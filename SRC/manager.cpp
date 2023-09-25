#include "manager.h"
#include <fstream>
#include "globalFile.h"
#include <algorithm>

//Ĭ�Ϲ���
Manager::Manager() 
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա����Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ������  ��ȡ�������ļ��� ѧ������ʦ�������Ϣ
	this->initVector();

	//��ʼ����Ż�����Ϣ����������ȡ���д洢�Ļ�����Ϣ
	this->initComputerRoom();
}

//�˵�����
void Manager::operMenu()
{
	cout << "��ӭ����Ա:" << this->m_Name << " ��¼" << endl;
	cout <<"\t ----------------------------------------" << endl
		<< "\t|                                        |" << endl
		<< "\t|               1.����˺�               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               2.�鿴�˺�               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               3.�鿴����               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               4.���ԤԼ               |" << endl
		<< "\t|                                        |" << endl
		<< "\t|               0.�˳���¼               |" << endl
		<< "\t|                                        |" << endl
		<< "\t ----------------------------------------" << endl
		<< "��ѡ�����Ĳ���:" ;
}

//����˺�
void Manager::addAccount()
{
	//
	cout << "��������ӵ��˺�����" << endl
		 << "1.���ѧ��" << endl
		 << "2.�����ʦ" << endl;

	string fileName;//�����ļ���
	string tip;//��ʾ����������id��
	string errorTip;//�ظ�����id�Ĵ�����ʾ

	ofstream ofs;//�ļ���������

	int select = 0;
	cin >> select;//�����û���ѡ��

	if (select == 1)
	{
		//��ӵ���ѧ��
		fileName = STUDENT_FILE;
		tip = "������ѧ����ѧ�ţ�";
		errorTip = "ѧ���ظ������������룡";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "������ְ���ı��:";
		errorTip = "ְ�����ظ������������룡";
	}
	else
	{
		cout << "ѡ���������������!" << endl;
	}

	//����׷�ӵķ�ʽ����fileName ����д�ļ�
	ofs.open(fileName, ios::out | ios::app);

	if (!ofs.is_open())
	{
		cout << "�ļ��������" << endl;
		return;
	}

	string id;//��idΪ ѧ�Ż�����ְ����
	string name;//����
	string pwd;//����

	while (true)
	{
		cout << tip;
		cin >> id;

		bool ret = this->checkRepeat(id, select);
		if (ret)//���ظ� 
		{
			cout << errorTip << endl;
		}
		else break;
	}

	cout << "������������";
	cin >> name;

	cout << "���������룺";
	cin >> pwd;

	//���ļ���д������
	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�!" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
	//��������ݱ��浽vStu������
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
	cout << "ѧ��ѧ�ţ�" << s.m_ID << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}

void PrintTeacher(const Teacher& t)
{
	cout << "��ʦְ���ţ�" << t.m_empID << " ������" << t.m_Name << " ���룺" << t.m_Pwd << endl;
}

//�鿴�˺�
void Manager::showAccount() 
{
	cout << "��ѡ��Ҫ�鿴������:" << endl
		<< "1���鿴���е�ѧ��" << endl
		<< "2���鿴���е���ʦ" << endl;

	ifstream ifs;
	int select = 0;//�����û���ѡ��
	cin >> select;

	if (select == 1)
	{
		//�鿴ѧ��
		cout <<endl << "����ѧ������Ϣ����;" << endl;

		//����һ  ��ȡ�ļ��������Ϣ
		ifs.open(STUDENT_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "�ļ���ʧ�ܣ�" << endl;
			return;
		}

		string id;
		string name;
		string pwd;

		while (ifs >> id && ifs >> name && ifs >> pwd)
		{
			cout << "ѧ��ѧ�ţ�" << id << " ������" << name << " ���룺" << pwd << endl;
		}

		ifs.close();
		
		//������ ֱ�ӻ�ȡ�����е����� �����Ϣ
		//for (auto it = vStu.begin(); it != vStu.end(); it++)
		//{
		//	cout << "ѧ��ѧ�ţ�" << it->m_ID << " ������" << it->m_Name << " ���룺" << it->m_Pwd << endl;
		//}

		//������ ͨ��for_each�㷨����ȡ��Ϣ�������
		//for_each(vStu.begin(), vStu.end(), PrintStudent);
		
		cout << endl;
	}
	else if (select == 2)
	{
		//�鿴��ʦ
		cout << endl << "������ʦ����Ϣ����;" << endl;
		
		//����һ ��ȡ�ļ��������ص���Ϣ
		ifs.open(TEACHER_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "�ļ���ʧ�ܣ�" << endl;
			return;
		}

		string id;
		string name;
		string pwd;

		while (ifs >> id && ifs >> name && ifs >> pwd)
		{
			cout << "��ʦְ���ţ�" << id << " ������" << name << " ���룺" << pwd << endl;
		}

		ifs.close();

		//������ ֱ�ӻ�ȡ�����е����� �������Ϣ
		//for (auto it = vTea.begin(); it != vTea.end(); it++)
		//{
		//	cout << "ְ���ţ�" << it->m_empID << " ������" << it->m_Name << " ���룺" << it->m_Pwd << endl;
		//}

		//������ ͨ��for_each�㷨��������������ȡ���ݣ��Ӷ������Ϣ
		//for_each(vTea.begin(), vTea.end(), PrintTeacher);
	
		cout << endl;
	}

	system("pause");
	system("cls");
}

//�鿴��������Ϣ
void Manager::showComputerRoom()
{
	cout<<endl << "��������Ϣ���£�" << endl;
	for (auto it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "�����ı�ţ�" << it->m_ComId
			<< " ���������������" << it->m_maxNum << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::clearAppointmentRecord()
{
	cout <<endl << "�Ƿ�Ҫ���ԤԼ��¼��(Y/N)";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		ofstream ofs;
		ofs.open(ORDER_FILE, ios::out | ios::trunc);

		ofs.close();
		cout << "ԤԼ��¼��ճɹ���" << endl;
		system("pause");
		system("cls");
	}
	else return;
	
	return;
}

//��ʼ����������
void Manager::initVector()
{
	//ȷ����������յ�״̬
	vStu.clear();
	vTea.clear();

	//��ȡ�ļ���Ϣ ѧ��
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_ID && ifs >> s.m_Name && ifs >> m_Pwd)
	{
		vStu.push_back(s);
	}

	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	//��ȡ�ļ���Ϣ ��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_empID && ifs >> m_Name && ifs >> m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "��ǰ��ʦ��������" << vTea.size() << endl;
	ifs.close();
}

//����ظ� ����1 ���ѧ��/ְ���� ����2 �������
bool Manager::checkRepeat(string id, int type)
{
	if (type == 1)
	{//���ѧ��
		for (auto it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_ID)
			{
				return true;
			}
		}
	}
	else
	{//�����ʦ
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

//��ʼ��������Ϣ������
void Manager::initComputerRoom()
{
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}

	ComputerRoom com;

	while (ifs >> com.m_ComId && ifs >> com.m_maxNum)
	{
		vCom.push_back(com);
	}

	ifs.close();
	cout << "����������Ϊ��" << vCom.size() << endl;
}
