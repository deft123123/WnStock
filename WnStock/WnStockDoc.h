
// WnStockDoc.h : CWnStockDoc ��Ľӿ�
//


#pragma once


class CWnStockDoc : public CDocument
{
protected: // �������л�����
	CWnStockDoc();
	DECLARE_DYNCREATE(CWnStockDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CWnStockDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

	
public:
	StockDoc* stockDoc;
	/****************�Զ�������ͺ���******************/
	
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

	void GetDayKData(char* stockCode);				//��ȡK����ʷ���ݣ����浽"WnStockDll.h"�е�vKStockData��
	void GetKPoint();								//���K�ߵ������
	void GetKVolumePoint();							//��óɽ�������
	void GetMaPrice();								//��ȡ���ߵļ۸�
	void GetMaPoint();								//���MA5,MA10,MA20����
	void GetMacd();									//���MACDֵ
	void GetMacdPoint();							//���MACD������ֵ
//��ʱ��
	vector<RealTimeStock*>	vMinData;				//��ʱ�ߵ�����
	vector<POINT>			vMinPoint;				//��ʱ�ߵ�����
	vector<double>			vMinAvgPrice;			//ƽ���۸�
	vector<POINT>			vMinPricePoint;			//�۸�����
	vector<POINT>			vMinAvgPricePoint;			//ƽ���۸�����
	vector<POINT>			vMinVolumePoint;			//�ɽ�������

	void GetDayMinData(char* stockCode);			//��ȡ��ʱ�����ݣ����浽"WnStockDll.h"�е�vMinStockData��
	void GetDayMinPoint();							//��ȡ��ʱ�ߵ���������
	double					fLimitPrice;			//�ü۸�Ϊ���м�����Զ����ͼۻ���߼�

	//��������
	void AddMystock(char* stockCode);				//�Ҽ������������ѡ��ʹ��
	void DelMystock(char* stockCode);				//�Ҽ�������ɾ����ѡ��ʹ��
};
