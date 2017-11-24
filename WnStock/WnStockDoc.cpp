
// WnStockDoc.cpp : CWnStockDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "WnStock.h"
#endif

#include "WnStockDoc.h"
#include "WnStockView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWnStockDoc

IMPLEMENT_DYNCREATE(CWnStockDoc, CDocument)

BEGIN_MESSAGE_MAP(CWnStockDoc, CDocument)
END_MESSAGE_MAP()


// CWnStockDoc 构造/析构

CWnStockDoc::CWnStockDoc()
{
	// TODO: 在此添加一次性构造代码

// 	while (1)
// 	{
// 		RealTimeStock* realTimeStock = (RealTimeStock *) malloc(sizeof(RealTimeStock));
// 		StockData stockData;
// 		stockData.GetRealTimeStockData("600016", realTimeStock);
// 		free(realTimeStock);
// 		realTimeStock = NULL;
// 
// 	}

	//GetDayMinData("600016");
	

//  	StockData stockData;
//  	stockData.GetMinStockData("600016");

	ReadMystock();
	GetMytockData();
	KDay = 60;		//默认画60天K线
	KPos = 0;		//默认偏移量
	KBegin = 0;		//开始显示的K线索引	
	
	//GetDayKData("600016");

}

CWnStockDoc::~CWnStockDoc()
{
}

BOOL CWnStockDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CWnStockDoc 序列化

void CWnStockDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CWnStockDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CWnStockDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CWnStockDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWnStockDoc 诊断

#ifdef _DEBUG
void CWnStockDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWnStockDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWnStockDoc 命令


/*************************自定义函数实现***************************/

/*
*	@ 读取My Stock代码
*/
void CWnStockDoc::ReadMystock()
{
	StockData stockData;
	vMystock = stockData.ReadMystockCode();
}

/*
*	@ 保存My Stock代码
*/
void CWnStockDoc::WriteMystock()
{
	
}

void CWnStockDoc::AddMystock(char* stockCode)
{
	vMystock.push_back(stockCode);
}

void CWnStockDoc::DelMystock(char* stockCode)
{
	string strCode = stockCode;
	for (vector<string>::iterator it = vMystock.begin(); it != vMystock.end(); it++)
	{
		string strTemCode = *it;
		if (strTemCode == strCode)
		{
			vMystock.erase(it);
			break;
		}
	}
	
}

void CWnStockDoc::GetMytockData()
{
	//释放realtimeDataGroup内存
	for(vector <RealTimeStock *>::iterator it = vMystockRealTimeData.begin(); it != vMystockRealTimeData.end(); it ++)
	{
		if (NULL != *it) 
		{
			delete *it; 
			*it = NULL;
		}
	}
	vMystockRealTimeData.clear();

	for (int i=0; i<vMystock.size(); i++)
	{
 		StockData stockData;
 		RealTimeStock * realTimeStock = (RealTimeStock*)malloc(sizeof(RealTimeStock));
		memset(realTimeStock, 0, sizeof(RealTimeStock));
 		stockData.GetRealTimeStockData((char*)vMystock[i].c_str(),realTimeStock);
 		vMystockRealTimeData.push_back(realTimeStock);
	}
	return ;
}
<<<<<<< HEAD

void CWnStockDoc::GetDayKData(char* stockCode)
{
	//释放vKData内存
	for(vector<KStock*>::iterator it = vKData.begin(); it != vKData.end(); it ++)
	{
		if (NULL != *it) 
		{
			delete *it; 
			*it = NULL;
		}
	}
	vKData.clear();

	StockData stockData;
	stockData.GetKStockData1(stockCode);
	for (int i=0; i<stockData.vKStockData.size(); i++)
	{
		KStock* kStock = (KStock*)malloc(sizeof(KStock));
		memset(kStock, 0, sizeof(KStock));
		memcpy(kStock->strStockCode,stockData.vKStockData[i]->strStockCode, strlen(stockData.vKStockData[i]->strStockCode));
		memcpy(kStock->strDate,stockData.vKStockData[i]->strDate, strlen(stockData.vKStockData[i]->strDate));
		kStock->fPassClose = stockData.vKStockData[i]->fPassClose;
		kStock->fOpen = stockData.vKStockData[i]->fOpen;
		kStock->fClose = stockData.vKStockData[i]->fClose;
		kStock->fLow = stockData.vKStockData[i]->fLow;
		kStock->fHigh = stockData.vKStockData[i]->fHigh;
		kStock->Volume = stockData.vKStockData[i]->Volume;
		kStock->Amount = stockData.vKStockData[i]->Amount;
		vKData.push_back(kStock);
	}


	//释放vKData内存
	for(vector<KStock*>::iterator it = stockData.vKStockData.begin(); it != stockData.vKStockData.end(); it ++)
	{
		if (NULL != *it) 
		{
			delete *it; 
			*it = NULL;
		}
	}
	stockData.vKStockData.clear();
}

void CWnStockDoc::GetKPoint()
{
	//释放vDayKPoint内存
	for (vector <KPoint *>::iterator it=vKPoint.begin(); it!=vKPoint.end(); it++)
	{
		if (*it!=NULL)
		{
			delete *it;
			*it = NULL;
		}
	}

	vKPoint.clear();

	POINT high, low, open , close;
	POSITION pos = GetFirstViewPosition();
	CWnStockView* pView = (CWnStockView*)GetNextView(pos);

	double ih = pView->m_interKH;//K线的行高

	// 	CRect rect;
	// 	pView->GetClientRect(&rect);
	// 	float ih = (rect.bottom - 67)/16;//K线的行高

	KHighMax = 0;
	KLowMin = 1000;

	double checkKHighMax = KHighMax;
	double checkKLowMin = KLowMin;

	int n = vKData.size();

	if (n==0)
	{
		return;
	}
	int i;

	if (n<KDay)
	{
		KDay = n;
	}
	for(i = n-KDay + KPos;i < n + KPos; i++) //计算最近10的
	{
		if (vKData[i]->fHigh > KHighMax)
			KHighMax = vKData[i]->fHigh;
		if (vKData[i]->fLow < KLowMin)
			KLowMin = vKData[i]->fLow;
	}

	// 	if(checkKHighMax != KHighMax || checkKLowMin != KLowMin)
	// 		pView->Invalidate();

	double KM = KHighMax - KLowMin;		//最大和最小的价格差
	double a = 9 * ih;					//垂直高度
	//float b = rect.right - 200 -62;	//水平高度
	double b = pView->m_interKW;
	double lw = b / KDay;

	for(i = 0 ; i < n ; i++)
	{
		high.x = (int)(lw*9.0/10.0/2.0 + 0.5);
		high.y = (int)(17 + 9.5*ih - (vKData[i]->fHigh - KLowMin) * a / KM /*+0.5*/);

		low.x = (int)(lw*9.0/10.0/2.0 + 0.5);
		low.y = (int)(17 + 9.5*ih - (vKData[i]->fLow - KLowMin) * a / KM);

		open.x =  0;
		open.y = (int)(17 + 9.5*ih - (vKData[i]->fOpen - KLowMin) * a / KM /*+0.5*/);

		close.x = (int)(lw*9.0/10.0 +0.5);
		close.y = (int)(17 + 9.5*ih - (vKData[i]->fClose - KLowMin) * a / KM /*+0.5*/);

		KPoint* pKPoint = (KPoint* )malloc(sizeof(KPoint));
		memset(pKPoint, 0, sizeof(KPoint));

		pKPoint->high = high;
		pKPoint->low = low;
		pKPoint->open = open;
		pKPoint->close = close;

		vKPoint.push_back(pKPoint);
	}
	return;
}

void CWnStockDoc::GetMaPrice()
{
	//释放内存
	vMa5Price.clear();
	vMa10Price.clear();
	vMa20Price.clear();
	vector<double >(vMa5Price).swap(vMa5Price);
	vector<double >(vMa10Price).swap(vMa10Price);
	vector<double >(vMa20Price).swap(vMa20Price);


	int n = vKData.size();
	if (n ==0)
	{
		return;
	}

	if (n<=5) //不存在MA5
	{
		return;
	}
	int i,j;
	//前面补4个数据保证ma5Group数据和kDataGroup数据长度一样
	for (int i=0; i<4; i++)
	{
		vMa5Price.push_back(0);
	}
	for (i = 4;i < n;i++)
	{
		double sumPrice = 0;
		for (j = i;j>=i-4; j--)
		{
			sumPrice += vKData[j]->fClose;
		}
		vMa5Price.push_back(sumPrice/5);
	}

	if (n<=10)//不存在MA10
	{
		return;
	}
	//前面补9个数据保证ma10Group数据和kDataGroup数据长度一样
	for (int i=0; i<9; i++)
	{
		vMa10Price.push_back(0);
	}

	for (i = 9;i < n;i++)
	{
		double sumPrice = 0;
		for (j = i;j>=i-9; j--)
		{
			sumPrice += vKData[j]->fClose;
		}
		vMa10Price.push_back(sumPrice/10);
	}

	if (n<=20)//不存在MA20
	{
		return;
	}

	//前面补19个数据保证ma20Group数据和kDataGroup数据长度一样
	for (int i=0; i<19; i++)
	{
		vMa20Price.push_back(0);
	}

	for (i = 19;i < n;i++)
	{
		double sumPrice = 0;
		for (j = i;j>=i-19; j--)
		{
			sumPrice += vKData[j]->fClose;
		}
		vMa20Price.push_back(sumPrice/20);
	}
	return;
}

void CWnStockDoc::GetMaPoint()
{
	//释放内存
	vMa5Point.clear();
	vMa10Point.clear();
	vMa20Point.clear();
	vector<POINT >(vMa5Point).swap(vMa5Point);
	vector<POINT >(vMa10Point).swap(vMa10Point);
	vector<POINT >(vMa20Point).swap(vMa20Point);

	int n = vMa5Price.size();
	if (n<=5)
	{
		return;
	}

	POSITION pos = GetFirstViewPosition();
	CWnStockView* pView = (CWnStockView*)GetNextView(pos);

	double kmPrice = KHighMax - KLowMin; //kDay内最大值最小值差


	double a = pView->m_interKH*9;     //垂直高度
	double b = pView->m_interKW;       //水平宽度
	double lw = b/KDay; 


	POINT point;
	//ma5的坐标 
	for (int i = 0 + KPos; i<KDay+KPos; i++)
	{
		point.x = (int)(62+(i-KPos)*lw+0.5*lw);
		point.y = (int)(17 + pView->m_interKH*9.5 -(vMa5Price[n-KDay+i]-KLowMin)*a/kmPrice);
		vMa5Point.push_back(point);
	}

	//ma10坐标
	n = vMa10Price.size();
	if(n==0)
		return;
	for (int i = 0 + KPos; i<KDay+KPos; i++)
	{
		point.x = (int)(62+(i-KPos)*lw+0.5*lw);
		point.y = (int)(17 + pView->m_interKH*9.5 -(vMa10Price[n-KDay+i]-KLowMin)*a/kmPrice);
		vMa10Point.push_back(point);
	}

	//ma20坐标
	n = vMa20Price.size();
	if (n==0)
		return;
	for (int i = 0 + KPos; i<KDay+KPos; i++)
	{
		point.x = (int)(62+(i-KPos)*lw+0.5*lw);
		point.y = (int)(17 + pView->m_interKH*9.5 -(vMa20Price[n-KDay+i]-KLowMin)*a/kmPrice);
		vMa20Point.push_back(point);
	}
	return;
}

void CWnStockDoc::GetKVolumePoint()
{
	//释放kPointGroup内存
	for (vector <KVolumePoint *>::iterator it=vVolumePoint.begin(); it!=vVolumePoint.end(); it++)
	{
		if (*it!=NULL)
		{
			delete *it;
			*it = NULL;
		}
	}
	vVolumePoint.clear();


	POSITION pos = GetFirstViewPosition();
	CWnStockView* pView = (CWnStockView*)GetNextView(pos);

	POINT top, bottom;
	double ih = pView->m_interKH;

	double a = 2 * ih;               //垂直高度
	double b = pView->m_interKW;       //水平宽度
	double lw = b / KDay;

	KMaxVolume = 0;

	int n = vKData.size();
	if (n == 0)
	{
		return;
	}
	int i;
	for(i =  n-KDay + KPos; i <  n + KPos; i++)
	{
		if(vKData[i]->Volume >= KMaxVolume)
		{
			KMaxVolume = vKData[i]->Volume;
		}
	}

	for(i = 0; i < n; i++)
	{
		top.x =0;
		//top.y = pView->rect.bottom - 50 - 4*ih - ((double)vKData[i]->Volume) * a / KMaxVolume; //这种方法有误差不准确
		top.y = pView->m_interKH*12+17 - ((double)vKData[i]->Volume) * a / KMaxVolume;
		bottom.x = (double)(lw*9.0/10.0 +0.5);
		//bottom.y = pView->rect.bottom - 50 - 4*ih;
		bottom.y = pView->m_interKH*12+17;

		KVolumePoint* pKVolumePoint = (KVolumePoint*)malloc(sizeof(KVolumePoint));
		memset(pKVolumePoint, 0, sizeof(KVolumePoint));
		pKVolumePoint->top = top;
		pKVolumePoint->bottom =bottom;

		vVolumePoint.push_back(pKVolumePoint); 
	}   

	return;
}

void CWnStockDoc::GetMacd()
{
	//释放内存
	vMacdDif.clear();
	vMacdDea.clear();
	vMacd.clear();
	vector<double>(vMacdDif).swap(vMacdDif);
	vector<double>(vMacdDea).swap(vMacdDea);
	vector<double>(vMacd).swap(vMacd);


	//选用MACD参数为MACD(12,26,9)
	int n = vKData.size();	
	if (n==0)
	{
		return;
	}
	double EMA12 = 0;
	double YesDayEMA12 = 0;
	double EMA26 = 0;
	double YesDayEMA26 = 0;

	//计算离差值DIF
	for (int i=0; i<n; i++)
	{
		if (i == 0)
		{
			EMA12 = vKData[i]->fClose;
			YesDayEMA12 = EMA12;
			EMA26 = vKData[i]->fClose;
			YesDayEMA26 = EMA26;
		}
		else
		{
			EMA12 = vKData[i]->fClose*2/13 + YesDayEMA12*11/13;
			YesDayEMA12 = EMA12;
			EMA26 = vKData[i]->fClose*2/27 + YesDayEMA26*25/27;
			YesDayEMA26 = EMA26;
		}
		vMacdDif.push_back(EMA12 - EMA26);
	}

	//计算DEA
	double DEA = 0;
	double YesDayDEA = 0;
	for (int i=0; i<n; i++)
	{
		if(i == 0)
		{
			DEA = 0;
			YesDayDEA = DEA;
		}
		else
		{
			DEA = vMacdDif[i]*2/10 + YesDayDEA*8/10;
			YesDayDEA = DEA;
		}
		vMacdDea.push_back(DEA);
	}

	//计算MACD
	for (int i=0; i<n; i++)
	{
		double fMacd = 0;
		fMacd = 2*(vMacdDif[i] - vMacdDea[i]);
		vMacd.push_back(fMacd);
	}
	return;
}

void CWnStockDoc::GetMacdPoint()
{
	//释放内存
	vMacdPoint.clear();
	vMacdDifPoint.clear();
	vMacdDeaPoint.clear();
	vector<POINT >(vMacdPoint).swap(vMacdPoint);
	vector<POINT >(vMacdDifPoint).swap(vMacdDifPoint);
	vector<POINT >(vMacdDeaPoint).swap(vMacdDeaPoint);


	POSITION pos = GetFirstViewPosition();
	CWnStockView* pView = (CWnStockView*)GetNextView(pos);

	int n = vMacd.size();
	if (n==0)
	{
		return;
	}
	CRect rect;
	pView->GetClientRect(&rect);

	double a = pView->m_interKH;
	double b = pView->m_interKW;
	double lw = b/KDay;

	maxMACD = -100;
	minMACD = 100;
	double maxDIF = -100;
	double minDIF = 100;
	double maxDEA = -100;
	double minDEA = 100;

	//计算显示区间内MACD点的坐标
	for (int i = n-KDay+KPos; i < n+KPos; i++)
	{
		if (vMacd[i] > maxMACD)
		{
			maxMACD = vMacd[i];
		}
		if (vMacd[i] < minMACD)
		{
			minMACD = vMacd[i];
		}
	}
	POINT macdPoint;
	for (int i = n-KDay+KPos; i< (n+KPos); i++)
	{
		if (vMacd[i] >= 0)
		{
			macdPoint.x = 62+(i-n+KDay-KPos)*lw+0.5*lw;
			macdPoint.y = (a - a* vMacd[i]/maxMACD) + 13*a +17;
		}
		else
		{
			macdPoint.x = 62+(i -n+KDay-KPos)*lw+0.5*lw;
			macdPoint.y = a * (vMacd[i]) / minMACD + 14*a + 17;
		}

		//保存MACD点坐标
		vMacdPoint.push_back(macdPoint);
	}


	//计算显示区间内DIF坐标
	a = pView->m_interKH*2;
	for (int i = n-KDay+KPos; i < n+KPos; i++)
	{
		if (vMacdDif[i] >= maxDIF)
		{
			maxDIF = vMacdDif[i];
		}
		if (vMacdDif[i] < minDIF)
		{
			minDIF = vMacdDif[i];
		}
	}
	POINT difPoint;
	for (int i = n-KDay+KPos; i< (n+KPos); i++)
	{
		if (vMacdDif[i] >= 0)
		{
			difPoint.x = 62+(i-n+KDay-KPos)*lw+0.5*lw;
			difPoint.y = (a -a * vMacdDif[i] / maxDIF) + 12*(pView->m_interKH) +17;
		}
		else
		{
			difPoint.x = 62+(i-n +KDay-KPos)*lw+0.5*lw;
			difPoint.y = a * (vMacdDif[i]) / minDIF + 14*(pView->m_interKH) + 17;
		}
		//保存DIF点坐标
		vMacdDifPoint.push_back(difPoint);
	}


	//计算显示区间内DEA坐标
	a = pView->m_interKH*2;
	for (int i= n- KDay + KPos; i < n + KPos; i++)
	{
		if (vMacdDea[i] >= maxDEA)
		{
			maxDEA = vMacdDea[i];
		}
		if (vMacdDea[i] < minDEA)
		{
			minDEA = vMacdDea[i];
		}
	}
	POINT deaPoint;
	for (int i = n - KDay + KPos; i< (n + KPos); i++)
	{
		if (vMacdDea[i] >= 0)
		{
			deaPoint.x = 62+(i -n + KDay - KPos)*lw+0.5*lw;
			deaPoint.y = (a -a * vMacdDea[i] / maxDEA) + 12*(pView->m_interKH) +17;
		}
		else
		{
			deaPoint.x = 62+(i -n + KDay - KPos)*lw+0.5*lw;
			deaPoint.y = a * (vMacdDea[i]) / minDEA + 14*(pView->m_interKH) + 17;
		}
		//保存DIF点坐标
		vMacdDeaPoint.push_back(deaPoint);
	}
	return;
}

void CWnStockDoc::GetDayMinData(char* stockCode)
{
	//释放vKData内存
	for(vector<RealTimeStock*>::iterator it = vMinData.begin(); it != vMinData.end(); it ++)
	{
		if (NULL != *it) 
		{
			delete *it; 
			*it = NULL;
		}
	}
	vMinData.clear();

	StockData stockData;
	stockData.GetMinStockData(stockCode);
	int n = stockData.vMinStockData.size();
	for (int i=0; i<n; i++)
	{
		RealTimeStock* realTimeStock = (RealTimeStock*)malloc(sizeof(RealTimeStock));
		memset(realTimeStock, 0, sizeof(RealTimeStock));

		realTimeStock->fOpen = stockData.vMinStockData[i]->fOpen;
		realTimeStock->fPassClose = stockData.vMinStockData[i]->fPassClose;
		realTimeStock->fNow = stockData.vMinStockData[i]->fNow;
		realTimeStock->fHigh = stockData.vMinStockData[i]->fHigh;
		realTimeStock->fLow = stockData.vMinStockData[i]->fLow;
		realTimeStock->fBuy = stockData.vMinStockData[i]->fBuy;
		realTimeStock->fSale = stockData.vMinStockData[i]->fSale;
		realTimeStock->Volume = stockData.vMinStockData[i]->Volume;
		realTimeStock->Amount = stockData.vMinStockData[i]->Amount;

		realTimeStock->iBuy1 = stockData.vMinStockData[i]->iBuy1;
		realTimeStock->fBuy1Price = stockData.vMinStockData[i]->fBuy1Price;
		realTimeStock->iBuy2 = stockData.vMinStockData[i]->iBuy2;
		realTimeStock->fBuy2Price = stockData.vMinStockData[i]->fBuy2Price;
		realTimeStock->iBuy3 = stockData.vMinStockData[i]->iBuy3;
		realTimeStock->fBuy3Price = stockData.vMinStockData[i]->fBuy3Price;
		realTimeStock->iBuy4 = stockData.vMinStockData[i]->iBuy4;
		realTimeStock->fBuy4Price = stockData.vMinStockData[i]->fBuy4Price;
		realTimeStock->iBuy5 = stockData.vMinStockData[i]->iBuy5;
		realTimeStock->fBuy5Price = stockData.vMinStockData[i]->fBuy5Price;

		realTimeStock->iSale1 = stockData.vMinStockData[i]->iSale1;
		realTimeStock->fSale1Price = stockData.vMinStockData[i]->fSale1Price;
		realTimeStock->iSale2 = stockData.vMinStockData[i]->iSale2;
		realTimeStock->fSale2Price = stockData.vMinStockData[i]->fSale2Price;
		realTimeStock->iSale3 = stockData.vMinStockData[i]->iSale3;
		realTimeStock->fSale3Price = stockData.vMinStockData[i]->fSale3Price;
		realTimeStock->iSale4 = stockData.vMinStockData[i]->iSale4;
		realTimeStock->fSale4Price = stockData.vMinStockData[i]->fSale4Price;
		realTimeStock->iSale5 = stockData.vMinStockData[i]->iSale5;
		realTimeStock->fSale5Price = stockData.vMinStockData[i]->fSale5Price;

		memcpy(realTimeStock->strDate, stockData.vMinStockData[i]->strDate, strlen(stockData.vMinStockData[i]->strDate));
		memcpy(realTimeStock->strTime, stockData.vMinStockData[i]->strTime, strlen(stockData.vMinStockData[i]->strTime));
		vMinData.push_back(realTimeStock);
	}


	//释放vKData内存
	for(vector<RealTimeStock*>::iterator it = stockData.vMinStockData.begin(); it != stockData.vMinStockData.end(); it ++)
	{
		if (NULL != *it) 
		{
			delete *it; 
			*it = NULL;
		}
	}
	stockData.vMinStockData.clear();
}

void CWnStockDoc::GetDayMinPoint()
{
	int n = vMinData.size();
	if (n == 0)
		return;

//*******获得价格坐标
	POINT pricePoint;
	pricePoint.x=0;
	pricePoint.y=0;
	POINT avgPricePoint;
	avgPricePoint.x=0;
	avgPricePoint.y=0;
	POINT volumePoint;
	volumePoint.x=0;
	volumePoint.y=0;


	double fPass = vMinData[0]->fPassClose;
	double minMaxPrice = 0;
	double minMinPrice = 1000;
	double minMaxAvgPrice = 0;
	double minMinAvgPrice = 1000;

	int maxVolume = 0;
	fLimitPrice = 0;
	double fLimitAvgPrice = 0;
	
	//找价格最大值和最小值
	for(int i = 0; i<n; i++)
	{
		if(vMinData[i]->fNow > minMaxPrice)
			minMaxPrice = vMinData[i]->fNow;
		if(vMinData[i]->fNow < minMinPrice)
			minMinPrice = vMinData[i]->fNow;
	}

	//求平均价格保存到avgPriceGroup
	vMinAvgPrice.clear();
	for (int i=0; i<n; i++)
	{
		double avgPrice = 0;
		double sumPrice = 0;

		for (int j=0; j<=i; j++)
		{
			sumPrice += vMinData[j]->fNow;
		}
		avgPrice = sumPrice/(i+1);
		vMinAvgPrice.push_back(avgPrice);
	}
	for (int i=0; i<n; i++)
	{
		float avg = vMinAvgPrice[i];
		CString str;
		str.Format("%5.2f\n", vMinAvgPrice[i]);
		OutputDebugString(str);
	}
	//找平均价格的最大值和最小值
	for(int i = 0; i<n; i++) //计算最近10的
	{
		if(vMinAvgPrice[i] > minMaxAvgPrice)
			minMaxAvgPrice = vMinAvgPrice[i];
		if(vMinAvgPrice[i] < minMinAvgPrice)
			minMinAvgPrice = vMinAvgPrice[i];
	}
	//找出成交量的最大值
	for (int i=0; i<n; i++)
	{
		if (vMinData[i]->Volume >= maxVolume)
			maxVolume = vMinData[i]->Volume;
	}

	//求峰值价格
	if (minMinPrice >= fPass)
	{
		fLimitPrice = minMaxPrice;
	}
	if (minMaxPrice <= fPass)
	{
		fLimitPrice = minMinPrice;
	}
	if ((minMinPrice<fPass) && (minMaxPrice>fPass))
	{
		if ((minMaxPrice-fPass) > (fPass-minMinPrice))
		{
			fLimitPrice = minMaxPrice;
		}
		else
		{
			fLimitPrice = minMinPrice;
		}
	}


	//求平均价格的峰值
	if (minMinAvgPrice >= fPass)
	{
		fLimitAvgPrice = minMaxAvgPrice;
	}
	if (minMaxAvgPrice <= fPass)
	{
		fLimitAvgPrice = minMinAvgPrice;
	}
	if ((minMinAvgPrice<fPass) && (minMaxAvgPrice>fPass))
	{
		if ((minMaxAvgPrice-fPass) > (fPass-minMinAvgPrice))
		{
			fLimitAvgPrice = minMaxAvgPrice;
		}
		else
		{
			fLimitAvgPrice = minMinAvgPrice;
		}
	}


	//峰值在上对应的纵坐标Y=(6*ih)*(fLimitPrice-fnow)/(fLimitPrice-fpass)+35;
	//峰值在下对应的纵坐标Y=(6*ih)*(fpass-fnow)/(fpass-fLimitPrice)+6*ih+35;

	POSITION pos = GetFirstViewPosition();
	CWnStockView* pView = (CWnStockView*)GetNextView(pos);
	
	float ih = pView->m_interMinH;   //分时线的行高

	CRect rect;
	pView->GetClientRect(&rect);

	vMinPricePoint.clear();
	vMinAvgPricePoint.clear();
	vMinVolumePoint.clear();
	for (int i=0; i<n; i++)
	{
// 		//时间转化为秒
// 		char time[128] = {0};
// 		strcpy(time, vMinData[i]->strTime);
// 		int nowS = timeToSecond(time); //直接传递minDataGroup[i]->strTime相当于引用会改变该地址值
	
		int nowS = atoi(vMinData[i]->strTime);
		//价格坐标坐标
		if (fLimitPrice>fPass) //峰值在上
		{
			if (nowS<= 11*3600+30*60)
			{
				int startS = 9*3600 +30*60;
				pricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;
				pricePoint.y = (6*ih)*(fLimitPrice-vMinData[i]->fNow)/(fLimitPrice-fPass)+35;
			}
			else
			{
				int startS = 13*3600;
				pricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
				pricePoint.y = (6*ih)*(fLimitPrice-vMinData[i]->fNow)/(fLimitPrice-fPass)+35;
			}
		}
		else//峰值在下
		{
			if (nowS<= 11*3600+30*60)
			{
				int startS = 9*3600 +30*60;
				pricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;
				pricePoint.y = (6*ih)*(fPass-vMinData[i]->fNow)/(fPass-fLimitPrice)+6*ih+35;
			}
			else
			{
				int startS = 13*3600;
				pricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
				pricePoint.y = (6*ih)*(fPass-vMinData[i]->fNow)/(fPass-fLimitPrice)+6*ih+35;
			}
		}
		
		//均价坐标
		if (vMinAvgPrice[i]>fPass)//均价在上
		{
			if (nowS<= 11*3600+30*60)
			{
				int startS = 9*3600 +30*60;
				if (fLimitPrice>fPass)//价格峰值在上
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;;
				    avgPricePoint.y = (6*ih)*(fLimitPrice-vMinAvgPrice[i])/(fLimitPrice-fPass)+35;
				}
				else
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;;
					//avgPricePoint.y = -(6*ih)*(fLimitPrice-avgPriceGroup[i])/(fLimitPrice-fPass)+35;
					avgPricePoint.y = (6*ih)*(2*fPass-fLimitPrice-vMinAvgPrice[i])/(fPass-fLimitPrice)+35;

				}
			}
			else
			{
				int startS = 13*3600;
				if (fLimitPrice>fPass)//价格峰值在上
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
					avgPricePoint.y = (6*ih)*(fLimitPrice-vMinAvgPrice[i])/(fLimitPrice-fPass)+35;
				}
				else
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
					//avgPricePoint.y = -(6*ih)*(fLimitPrice-avgPriceGroup[i])/(fLimitPrice-fPass)+35;
					avgPricePoint.y = (6*ih)*(2*fPass-fLimitPrice-vMinAvgPrice[i])/(fPass-fLimitPrice)+35;
				}
			}
		}
		else
		{
			if (nowS<= 11*3600+30*60)
			{
				int startS = 9*3600 +30*60;
				if (fLimitPrice>fPass)//价格峰值在上
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;
					avgPricePoint.y = (6*ih)*(fPass-vMinAvgPrice[i])/(fLimitPrice - fPass)+6*ih+35;
				}
				else
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;
					avgPricePoint.y = (6*ih)*(fPass-vMinAvgPrice[i])/(fPass - fLimitPrice)+6*ih+35;
				}

			}
			else
			{
				int startS = 13*3600;
				if (fLimitPrice>fPass)//价格峰值在上
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
					avgPricePoint.y = (6*ih)*(fPass-vMinAvgPrice[i])/(fLimitPrice - fPass)+6*ih+35;
				}
				else
				{
					avgPricePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
					avgPricePoint.y = (6*ih)*(fPass-vMinAvgPrice[i])/(fPass - fLimitPrice)+6*ih+35;
				}
			}
		}
		//成交量坐标 公式：Y=6*interMinH*(maxVolume-nowVolume)/maxVolume+6*interMinH+35;
		if (nowS<= 11*3600+30*60)
		{
			int startS = 9*3600 +30*60;
			volumePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62;
			volumePoint.y = 6*ih*(maxVolume-vMinData[i]->Volume)/maxVolume+12*ih+35;
		}
		else
		{
			int startS = 13*3600;
			volumePoint.x = ((nowS-startS)*(pView->m_interMinW))/3600 + 62 + 2*pView->m_interMinW;
		    volumePoint.y = 6*ih*(maxVolume-vMinData[i]->Volume)/maxVolume+12*ih+35;
	
	    }
		vMinPricePoint.push_back(pricePoint);
		vMinAvgPricePoint.push_back(avgPricePoint);
		vMinVolumePoint.push_back(volumePoint);
	}
	return;
}