#pragma once
#include "identity.h"
#include "orderFile.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//��ʦ������
class Teacher :public Identity
{
public:	
	//Ĭ�Ϲ���
	Teacher(); 

	//�вι���
	Teacher(string empID, string name, string pwd);
	
	// �˵�����
	virtual void operMenu();

	// �鿴�����˵�ԤԼ
	void showAllOrder();

	// ���ԤԼ
	void checkOrder();

	//ְ�����
	string m_empID;
};