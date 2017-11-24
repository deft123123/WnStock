#ifndef _WNSTOCKDLL_H
#define _WNSTOCKDLL_H

#define WNSTOCKDLL_EXPORTS

#ifdef WNSTOCKDLL_EXPORTS
#define WNSTOCKDLL_API __declspec(dllexport)
#else
#define WNSTOCKDLL_API __declspec(dllimport)
#endif

#include <vector>
#include <string>


using namespace std;



/*
*	@ StockData:��ȡStock������
*	@ woniu201
*	@ 2017/08/03
*/

struct RealTimeStock
{
	char		strStockNum[32];
	char		strStockName[32];
	double		fOpen;
	double		fPassClose;
	double		fNow;
	double		fHigh;  
	double		fLow;
	double		fBuy;
	double		fSale;
	long long	Volume;	
	long long	Amount;

	int			iBuy1;
	double		fBuy1Price;
	int			iBuy2;
	double		fBuy2Price;
	int			iBuy3;
	double		fBuy3Price;
	int			iBuy4;
	double		fBuy4Price;
	int			iBuy5;
	double		fBuy5Price;

	int			iSale1;
	double		fSale1Price;
	int			iSale2;
	double		fSale2Price;
	int			iSale3;
	double		fSale3Price;
	int			iSale4;
	double		fSale4Price;
	int			iSale5;
	double		fSale5Price;

	char		strDate[32];
	char		strTime[32];

	double		fRatio;   
};

struct KStock 
{
	char		strStockCode[32];
	char		strDate[32];
	double		fPassClose; 
	double		fOpen;
	double		fClose;
	double		fLow;
	double		fHigh;
	long long	Volume;
	long long	Amount;
};

struct RealTimeMarket{
	char		marketName[32];//��������
	double		marketIndex;   //����ָ��
	double		marketRose;    //�Ƿ�
	double		marketRatio;   //�Ƿ�����
	long long	Volume;  	 //�ɽ���
	long long	Amount;    //�ɽ���

};

struct 	KPoint	//K�߼۸��Ӧ����ṹ��
{	
	POINT high;
	POINT low;
	POINT open;
	POINT close;
};

struct KVolumePoint     //K�߼۸��Ӧ������ṹ�� 
{
	POINT top;
	POINT bottom;
};


class WNSTOCKDLL_API StockData
{
public:
	vector<string> ReadMystockCode();
	/************My Stock********************/
	bool GetRealTimeStockData(char* stockCode, RealTimeStock* realTimeStock);
	bool GetRealTimeMarketData(char* code, RealTimeMarket* realTimeMarket);
	/*************K�� ����*******************/       
	vector<KStock*>			vKStockData;
	vector<RealTimeStock*>	vMinStockData;
	void					SaveKData(char* stock, char* data, int i);
	bool					GetKStockData(char* stockCode);
	bool					GetKStockData1(char* stockCode);
	bool					GetMinStockData(char* stockCode);
private:
};

/*
*	@ StockTime:��ȡStock����ʱ��
*	@ woniu201
*	@ 2017/08/08
*/
class WNSTOCKDLL_API StockTime
{
public:
	int		CaculateWeekDay(char* pDate);
	int		CaculateDifferenceDay(char* pDate1, char* pDate2);
	BOOL	bSameWeek(char* pDate1, char* pDate2);
	BOOL	bSameMonth(char* pDate1, char* pDate2);
	BOOL	bExchange();
	char*	TimeToSecond(char* time);
};



class WNSTOCKDLL_API StockDoc
{
public:

/******************** K�߲��� ****************************/

	//��ѡ�������������ͺ���
	vector<string>	vMystock;
	void			ReadMystock();					//��ȡ��ѡ�ɹ�Ʊ����
	void			WriteMystock();					//������ѡ�ɵ��������ݿ�(sqlite)
	void			GetMytockData();				//��ȡ������ѡ�ɵ�����
	vector<RealTimeStock*> vMystockRealTimeData;	//��ѡ��ʵʱ��������
	//K�������������ͺ���
	vector<KStock*>		vKData;						//K��ʷ����
	vector <KPoint *>	vKPoint;					//K����������
	vector <KVolumePoint *> vVolumePoint;		    //�ɽ����������� (KDAY,KPOS,KBEGIN������double����Ϊ��Ҫ�͸��������������ǿ��ת��)
	vector <double>		vMa5Price;					//5�վ�������
	vector <double>		vMa10Price;					//10�վ�������
	vector <double>		vMa20Price;					//20�վ�������
	vector <POINT>		vMa5Point;					//MA5����
	vector <POINT>		vMa10Point;					//MA10����
	vector <POINT>		vMa20Point;					//MA20����
	vector <double>		vMacdDif;					//MACD����DIF����
	vector <double>		vMacdDea;					//MACD����DEA����
	vector <double>		vMacd;						//MACD����macd����
	vector <POINT >		vMacdDifPoint;				//MACD����DIF��������
	vector <POINT >		vMacdDeaPoint;				//MACD����DEA��������
	vector <POINT >		vMacdPoint;					//MACD����macd��������

	double				KDay;						//Ҫ��K�ߵ�����
	double				KPos;						//K�������ƶ����õ���ƫ��
	double				KBegin;						//��ʼ��ʾ��K������	
	double				KHighMax;					//��ʾK�߷�Χ�ڵ���߼�
	double				KLowMin;					//��ʾK�߷�Χ�ڵ���ͼ�
	double				KMaxVolume;					//��ʾK�߷�Χ�ڵ����ɽ���
	float maxMACD;            //��ʾ��Χ�����macdֵ
	float minMACD;            //��ʾ��Χ����Сmacdֵ

	void GetDayKData(char* stockCode);						//��ȡK����ʷ���ݣ����浽"WnStockDll.h"�е�vKStockData��
	void GetKPoint(double m_interKH,double m_interKW);		//���K�ߵ������
	void GetKVolumePoint(double m_interKH, double m_interKW);//��óɽ�������
	void GetMaPrice();										//��ȡ���ߵļ۸�
	void GetMaPoint(double m_interKH, double m_interKW);	//���MA5,MA10,MA20����
	void GetMacd();											//���MACDֵ
	void GetMacdPoint(double m_interKH, double m_interKW);	//���MACD������ֵ

/********************* ��ʱ�߲��� **************************/

	vector<RealTimeStock*>	vMinData;						//��ʱ�ߵ�����
	vector<POINT>			vMinPoint;						//��ʱ�ߵ�����
	vector<double>			vMinAvgPrice;					//ƽ���۸�
	vector<POINT>			vMinPricePoint;					//�۸�����
	vector<POINT>			vMinAvgPricePoint;				//ƽ���۸�����
	vector<POINT>			vMinVolumePoint;				//�ɽ�������

	void GetDayMinData(char* stockCode);					//��ȡ��ʱ�����ݣ����浽"WnStockDll.h"�е�vMinStockData��
	void GetDayMinPoint(double m_interMinH, double m_interMinW);//��ȡ��ʱ�ߵ���������
	double					fLimitPrice;					//�ü۸�Ϊ���м�����Զ����ͼۻ���߼�

};


#endif