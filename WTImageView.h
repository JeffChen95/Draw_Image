
// WTImageView.h : CWTImageView ��Ľӿ�
//

#pragma once


class CWTImageView : public CView
{
protected: // �������л�����
	CWTImageView();
	DECLARE_DYNCREATE(CWTImageView)

// ����
public:
	CWTImageDoc* GetDocument() const;

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
	virtual ~CWTImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // WTImageView.cpp �еĵ��԰汾
inline CWTImageDoc* CWTImageView::GetDocument() const
   { return reinterpret_cast<CWTImageDoc*>(m_pDocument); }
#endif

