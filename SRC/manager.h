#pragma once
#include "identity.h"
#include <iostream>
#include <vector>
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

using namespace std;

class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����˺�
	void addAccount();

	//�鿴�˺�
	void showAccount();

	//�鿴��������Ϣ
	void showComputerRoom();

	//�޸Ļ�������Ϣ

	//���ԤԼ��¼
	void clearAppointmentRecord();

	//��ʼ������
	void initVector();

	//��ʼ�������������Ϣ
	void initComputerRoom();

	//����ظ� ����1 ���ѧ��/ְ���� ����2 �������
	bool checkRepeat(string id, int type);

private:
	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//������Ϣ������
	vector<ComputerRoom>vCom;

};