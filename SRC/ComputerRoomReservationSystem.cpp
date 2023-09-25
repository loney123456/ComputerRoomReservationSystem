#include <iostream>
#include <fstream>
#include <string>
#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using namespace std;

//����ѧ���Ӳ˵�����
void studentMenu(Identity* &student)
{
	while (true)
	{
		//����ѧ�����Ӳ˵�
		student->operMenu();

		Student* stu = (Student*)student;

		int select = 0;
		cin >> select;//�����û���ѡ��

		switch (select)
		{
		case 1://����ԤԼ
			stu->applyOrder();
			break;

		case 2://�鿴�����ԤԼ
			stu->showMyOrder();
			break;

		case 3://�鿴�����˵�ԤԼ
			stu->showAllOrder();
			break;

		case 4://ȡ��ԤԼ
			stu->cancelOrder();
			break;

		case 0://�˳���¼
			delete student;
			cout << "�˳���¼�ɹ���" << endl;
			system("pause");
			system("cls");
			return;

		default:
			break;
		}
	}
}

//�����ʦ�Ӳ˵��Ľ���
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//�����Ӳ˵��Ľ���
		teacher->operMenu();

		//ǿ������ת��Ϊ�����ָ�룬�����������ĳ�Ա����
		Teacher* tea = (Teacher*)teacher;

		int select = 0;//�����û���ѡ��
		cin >> select;

		if (select == 1)//�鿴���е�ԤԼ
		{
			tea->showAllOrder();
		}
		else if (select == 2)//���ԤԼ
		{
			tea->checkOrder();
		}
		else
		{
			delete teacher;
			cout << "�˳���¼�ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//�������Ա�Ӳ˵�����
void managerMenu(Identity * &manager)
{
	while (true) 
	{
		//���ù���Ա���Ӳ˵�
		manager->operMenu();
	
		//������ָ�� ת��Ϊ����ָ��,������������������ӿ�
		Manager* man = (Manager*)manager;

		int select = 0;
		
		//�����û���ѡ��
		cin >> select;
		
		switch (select)
		{
		case 1://����˺�
			//cout << "����˺�" << endl;
			man->addAccount();
			break;

		case 2://�鿴�˺�
			//cout << "�鿴�˺�" << endl;
			man->showAccount();
			break;

		case 3://�鿴��������Ϣ
			//cout << "�鿴����" << endl;
			man->showComputerRoom();
			break;

		case 4://���ԤԼ��Ϣ
			//cout << "���ԤԼ" << endl;
			man->clearAppointmentRecord();
			break;

		default:
			delete manager;
			cout << "�˳��ɹ�!" << endl;
			system("pause");
			system("cls");
			return;
			break;
		}
	}
}

//ԤԼϵͳ��������ʾ
void MainMenuDisplay()
{
	cout << "-------------------��ӭʹ�û���ԤԼϵͳ-----------------" << endl
		 << endl << "������������ݣ�" << endl
		 << "\t --------------------------------------" << endl
		 << "\t|                                      |" << endl
		 << "\t|             1. ѧ      ��            |" << endl
		 << "\t|                                      |" << endl
		 << "\t|             2. ��      ʦ            |" << endl
		 << "\t|                                      |" << endl
		 << "\t|             3. ��  ��  Ա            |" << endl
		 << "\t|                                      |" << endl
		 << "\t|             0. ��      ��            |" << endl
		 << "\t|                                      |" << endl
		 << "\t---------------------------------------" << endl
		 << "����������ѡ��";

}

//��¼���� ����1 �����ļ��� ����2 �������������
void LoginIn(string fileName, int  type)
{
	//fileName --- �������ļ���  type --- ��¼�����
	// (1-ѧ�� 2-��ʦ 3-����Ա)
	
	//����ָ�� ����ָ���������
	Identity *Person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û��������Ϣ
	string id = "";
	string name = "";
	string pwd = "";

	//�ж����
	if (1 == type)//ѧ�����
	{
		cout << "���������ѧ�ţ�";
		cin >> id;
	}
	else if(2 == type)//ְ�����
	{
		cout << "���������ְ���ţ�";
		cin >> id;
	}

	cout << "�������û�����";
	cin >> name;

	cout << "���������룺"; 
	cin >> pwd;

	if (1 == type)
	{
		//ѧ�������֤
		string fId;//���ļ��ж�ȡ��ID��
		string fName;//���ļ��л�ȡ������
		string fPwd;//���ļ��л�ȡ����

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���жԱ�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����Ϣ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				Person = new Student(id, name, pwd);
			
				//����ѧ����ݵ��Ӳ˵�
				studentMenu(Person);

				return;
			}

		}
	}
	else if (2 == type)
	{
		//��ְ�������֤
		string fId;//���ļ��ж�ȡ��ID��
		string fName;//���ļ��л�ȡ������
		string fPwd;//���ļ��л�ȡ����

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��Ϣ��֤��¼�ɹ�!" << endl;	
				system("pause");
				system("cls");

				Person = new Teacher(id, name, pwd);
				//�����ʦ�Ӳ˵�
				teacherMenu(Person);
				return;
			}
		}

	}
	else if (3 == type)
	{
		//����Ա�����֤
		string fName;
		string fPwd;

		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��Ϣ��֤��¼�ɹ�!" << endl;
				system("pause");
				system("cls");
				Person = new Manager(name, pwd);

				//�������Ա�Ӳ˵�����
				managerMenu(Person);

				return;
			}
		}
	}

	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");

	return;
}
int main(void)
{
	int select = 0;//���ڽ����û���ѡ��
	while (true)
	{
		MainMenuDisplay();

		cin >> select;

		switch (select)
		{
		case 1://ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;

		case 2://��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;

		case 3://����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;

		case 0://�˳�ϵͳ
			cout << "��ӭ�ٴ�ʹ�ã�" << endl;
			return 0;

		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}