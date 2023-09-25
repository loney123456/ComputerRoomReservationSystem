#pragma once
#include <iostream>
#include "globalFile.h"
#include <fstream>//�ļ�����ͷ�ļ�
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class OrderFile
{
public:
	//�޲ι��캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();
	
	//��ʾԤԼ��¼
	void displayOrder();

	//��¼ԤԼ������
	int m_Size;

public:
	//��¼����ԤԼ��Ϣ������ 
	//key��ʾ��¼�ĵڼ��� value��ʾ�����¼�ļ�ֵ�Ե���Ϣ
	map<int, unordered_map<string, string>>m_orderData;
};
