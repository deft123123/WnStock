
// WnStockView.h : CWnStockView ��Ľӿ�
//
#include "../WnStockDll/WnStockDll.h"

#pragma once

//�������λ�ã���һ���������ľ���λ�ã����ǹ���������
enum	EMousePos{
	ratioPos,
	dataPos
};		
class CWnStockView : public CScrollView
{
protected: // �������л�����
	CWnStockView();
	DECLARE_DYNCREATE(CWnStockView)

// ����
public:
	CWnStockDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CWnStockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

/*******************�Զ������*****************************/
public:
	//CRect rect;
	bool		bScroll;		//�Ƿ���ʾ������
	CString		m_stockCode;	//��ǰ��Ʊ����
	CString		m_stockName;	//��ǰ��Ʊ����
    
	//��ѡ��UI���ñ���
	int			m_drawStatus;	//0:��Ʊչʾ��1:����ʱ�ߣ�2:��K��
	int			m_selectLine;   //��ʾ��ѡ���е�ǰѡ�е���
	int			m_mouseLine;	//��ʾ��ѡ����������ڵ���
	int			m_totalNum;		//My Stock������
	int			m_width;		//��ѡ����ÿһ����ʾ���ݵ�����
	int			m_height;		//��ѡ����ÿһ����ʾ���ݵ�����
	int			m_posY;			//�������»����붥���߶ȣ��̶���ѡ��������ʹ��
	HCURSOR		m_hHandCursor1; //�������
	EMousePos	eMousePos;

	//K��UI���ñ���
	double		m_interKH;		//K�ߵļ���߶�
	double		m_interKW;		//K�ȵļ�����

	//ʮ�����߱���
	BOOL		bFirstCrossLine;//�Ƿ��һ�λ�ʮ����
	BOOL		bCrossLine;		//�Ƿ񽻲�

	//��ʱ��
	double		m_interMinH;	//��ʱ�߼���߶�
	double		m_interMinW;	//��ʱ�߼�����

/******************�Զ��庯��******************************/
protected:
	//��ѡ��UI���ú���
	void		DrowMyStockUI(CDC* pDc);			//����ѡ�ɲ���
	static UINT ThreadGetMytockData(LPVOID lParam);	//��ȡMy Stock�����߳�
	
	//K��UI���ú���
	void		DrowKLineUI(CDC* pDC);				//��K�߿��
	void		DrawKLine();						//��K��
	void		DrawMaLine();						//��MA��
	void		ShowKData(int i);					//K��չʾ����
	void		DrawMacd(int i);					//��MACD

	//��ʱ��UI���к���
	void		DrowMinLineUI(CDC* pDC);			//����ʱ�߿��
	void		ShowMinData();						//������ʾ
	void		DrowMinLine();						//����ʱ��
	static UINT ThreadGetMinData(LPVOID lParam);	//��ȡ��ʱ�����߳�

public:
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddMystock();
	afx_msg void OnDelMystock();

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // WnStockView.cpp �еĵ��԰汾
inline CWnStockDoc* CWnStockView::GetDocument() const
   { return reinterpret_cast<CWnStockDoc*>(m_pDocument); }
#endif

