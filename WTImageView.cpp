
// WTImageView.cpp : CWTImageView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "WTImage.h"
#endif

#include "WTImageDoc.h"
#include "WTImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWTImageView

IMPLEMENT_DYNCREATE(CWTImageView, CView)

BEGIN_MESSAGE_MAP(CWTImageView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWTImageView ����/����

CWTImageView::CWTImageView()
{
	// TODO: �ڴ˴���ӹ������

}

CWTImageView::~CWTImageView()
{
}

BOOL CWTImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CWTImageView ����

void CWTImageView::OnDraw(CDC* /*pDC*/)
{
	CWTImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CWTImageView ��ӡ

BOOL CWTImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CWTImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CWTImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CWTImageView ���

#ifdef _DEBUG
void CWTImageView::AssertValid() const
{
	CView::AssertValid();
}

void CWTImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWTImageDoc* CWTImageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWTImageDoc)));
	return (CWTImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CWTImageView ��Ϣ�������
