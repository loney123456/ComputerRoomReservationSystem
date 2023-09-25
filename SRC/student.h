#pragma once
#include "identity.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "globalFile.h"
#include "computerRoom.h"
#include "orderFile.h"
#include <cstdlib>

using namespace std;

//���ѧ����
class Student :public Identity
{
public:
	//������
	//Ĭ�Ϲ���
	Student();
	
	//�вι��� ������ѧ�š��û���������
	Student(string id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴�Լ���ԤԼ
	
	void showMyOrder();

	//�鿴���е�ԤԼ
	
	void showAllOrder();

	//ȡ��ԤԼ

	void cancelOrder();

	//����:
	
	//ѧ��ѧ��
	string m_ID;

	//����洢������Ϣ������
	vector<ComputerRoom>vCom;
};
