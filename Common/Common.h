#pragma once
#include "LeeDateTime.h"

//K�ߵĵ���bar���ݽṹ��
struct BarData {
	CLeeDateTime time;//Bar��ʱ��
	double open;//Bar�Ŀ��̼�
	double high;//Bar����߼�
	double low;//Bar����ͼ�
	double close;//Bar�����̼�
	BarData(const CLeeDateTime& t = CLeeDateTime(), double o = 0.0, double h = 0.0,
		double l = 0.0, double c = 0.0)
		:time(t), open(o), high(h), low(l), close(c) { }//���캯��
};

//�����źŽṹ��
struct TradeSignal {
	string ContractID;//��Լ����
	/*
	order_directionί�з���:
	"Buy" - �࿪
	"Sellshort" - �տ�
	"Sell" - ƽ��
	"Buytocover" - ƽ��
	*/
	string order_direction;
	int order_num;//ί������
	double order_price;//ί�м۸�
	TradeSignal(const string& contract = "", const string& direction = "",
		int num = 0, double price = 0.0)
		:ContractID(contract), order_direction(direction),
		order_num(num), order_price(price) { }//���캯��
};


//�����Զ��������������(ͬһ���߳�������Ч)
class CLock {
public:
	CLock(CRITICAL_SECTION* p) : p_cs(p) {
		EnterCriticalSection(p_cs);//����(�����ٽ��)
	}
	~CLock() {
		LeaveCriticalSection(p_cs);//����(�뿪�ٽ��) 
	}
	CLock(const CLock&) = delete;//��ֹ��������
	CLock& operator= (const CLock&) = delete;//��ֹ��ֵ
private:
	CRITICAL_SECTION* p_cs;//�ٽ��
};

//��ȡ��Լ�е�Ʒ����.�����Ϊstring:"CF801",�򷵻�string:"CF"
inline const string GetCommodityFromContract(const string& contract) {
	size_t index = 0;
	for (; index != contract.size(); ++index) {
		if (isdigit(contract[index])){//index��λ����һ��Ϊ����(0~9)����ĸ����
			break;
		}
	}
	return contract.substr(0, index);//Ʒ����
}

//��ȡ��Լ�е���ݺ��·�.�����Ϊstring:"CF801",�򷵻�string:"801"
inline const string GetYearMonthFromContract(const string& contract) {
	size_t index = 0;
	for (; index != contract.size(); ++index) {
		if (isdigit(contract[index])) {//index��λ����һ��Ϊ����(0~9)����ĸ����
			break;
		}
	}
	return contract.substr(index);
}
