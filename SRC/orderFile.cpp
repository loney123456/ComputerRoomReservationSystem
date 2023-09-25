#include "orderFile.h"

void readOrderInfo(string& orderData, unordered_map<string, string>&m)
{
	string key;//��
	string value;//ֵ

	int pos = orderData.find(":");

	if (pos != -1)
	{
		key = orderData.substr(0, pos);
		value = orderData.substr(pos + 1, orderData.size() - pos);

		m.insert(make_pair(key, value));
	}
}

//�޲ι��캯��
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�����ʧ�ܣ�" << endl;
		return;
	}

	string weekday; //ԤԼ�����ڣ���һ�������е���һ�죩
	string interval;//ԤԼ��ʱ���
	string stuId;//ԤԼ��ѧ�����
	string stuName;//ԤԼ��ѧ������
	string computerRoomID;//ԤԼ�Ļ������
	string status;//ԤԼ��Ϣ��״̬

	this->m_Size = 0;//ԤԼ��¼������


	while (ifs >> weekday && ifs >> interval && ifs >> stuId &&
		ifs >> stuName && ifs >> computerRoomID && ifs >> status)
	{
		unordered_map<string, string> m;

		readOrderInfo(weekday, m);//��ȡ�ܼ�
		readOrderInfo(interval, m);//��ȡ���
		readOrderInfo(stuId, m);//��ȡѧ�����
		readOrderInfo(stuName, m);//��ȡѧ������
		readOrderInfo(computerRoomID, m);//��ȡ�������
		readOrderInfo(status, m);//��ȡԤԼ��״̬

		//��Сmap�����ŵ����map������
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}

	ifs.close();

	////��������map����
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

//����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;//ԤԼ��¼0����ֱ��return
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
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < this->m_Size; i++)
	{
		cout << endl;
		cout << "��" << i + 1 << "����¼��" << endl;
		cout << "ԤԼ���ڣ���" << this->m_orderData[i]["weekday"] << " "
			<< "ʱ��Σ�" << (this->m_orderData[i]["interval"] == "1" ? "����" : "����") << " "
			<< "ѧ����ţ�" << this->m_orderData[i]["stuId"] << " "
			<< "ѧ��������" << this->m_orderData[i]["stuName"] << " "
			<< "������ţ�" << this->m_orderData[i]["roomId"] << " ";
		string status = " ״̬��";

		//1.����� 2.��ԤԼ -1.ԤԼʧ�� 0.ȡ��ԤԼ
		if (this->m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (this->m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (this->m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else if (this->m_orderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
}