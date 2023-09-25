#pragma once
#include <iostream>
#include "globalFile.h"
#include <fstream>//文件流的头文件
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class OrderFile
{
public:
	//无参构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();
	
	//显示预约记录
	void displayOrder();

	//记录预约的条数
	int m_Size;

public:
	//记录所有预约信息的容器 
	//key表示记录的第几个 value表示具体记录的键值对的信息
	map<int, unordered_map<string, string>>m_orderData;
};
