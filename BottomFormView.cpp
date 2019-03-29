// BottomFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WTImage.h"
#include "BottomFormView.h"
#include "MainShape.h"
#include "TopFormView.h"
#include "MainFrm.h"
#include "Graph.h"
#include "SettingDlg.h"
#include "WTImageDoc.h"
#include "MagnifyDlg.h"

// �Ŵ󾵹������õ�
#define  MAGNIFIERSIZE				30 //���δ�С
#define  MAGNIFYINGMULTIPLE			4  //�Ŵ���
#define  OFFSETWIDE					16 //ƫ�����ȵ㣨��
#define  OFFSETHIGH					20 //ƫ�����ȵ㣨�ߣ�


CBottomFormView *pBottomFormView;

// CBottomFormView

IMPLEMENT_DYNCREATE(CBottomFormView, CFormView)

CBottomFormView::CBottomFormView()
	: CFormView(IDD_BOTTOMFORMVIEW)
{
	pBottomFormView = this;
	m_DrawType = 0;
	m_BtisDown = false;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
	m_color = RGB(0, 0, 0);
	m_color_lightpen = RGB(255, 255, 77);
	m_strFontName = "";
	m_pMDC = new CDC();
	m_ptPolyFirst = 0;
	m_ptPolyLast = 0;
	m_PolyCount = 0;
	m_strLine = "";
	m_ptTextOrigin = 0;
	m_flagFullPaint = false;
	m_rectTracker.m_nStyle = CRectTracker::resizeInside | CRectTracker::dottedLine;		//��ʼ����Ƥ����
	m_listPos = 0;
	m_Close = true;		//Ĭ�ϵ�ر�ʱ����λΪ��
}

CBottomFormView::~CBottomFormView()
{
}

void CBottomFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBottomFormView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_COMMAND(ID_DRAW_SAVE, &CBottomFormView::OnFileSave)
END_MESSAGE_MAP()


// CBottomFormView ���

#ifdef _DEBUG
void CBottomFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBottomFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

#endif //_DEBUG


// CBottomFormView ��Ϣ�������

void CBottomFormView::OnInitialUpdate()		//��ͼ������ȫ�������һ������ܵ��õĺ���
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
}


void CBottomFormView::OnDraw(CDC* pDC)
{
	//TODO: �ڴ����ר�ô��� �� ���û���
	CRect rcBottomView(-1,-1, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));		//���°벿��ֽ������ɫ
	pDC->FillRect(&rcBottomView, &CBrush(RGB(255, 255, 255)));

	m_scRollpt = GetScrollPosition();
	
	CClientDC dc(this);		//����dc
	dc.SetViewportOrg(0, 0);
	dc.BitBlt(0, 0, rcBottomView.Width(), rcBottomView.Height(), m_pMDC, m_scRollpt.x, m_scRollpt.y, SRCCOPY);
}

void CBottomFormView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CClientDC dc(this);		//�����豸������
	CBrush D_erase(GetBkColor(dc));		//������Ƥ��
	CBrush D_Brush(m_color);	//����ˢ��
	//CRect cwrect;
	//bool IsInRct = false;
	//CRect Trect;          //������Ƥ���ľ���
	//CRect Prect;         //ͼƬ���ο�
	//CRect AbsRect;
	//int i = 0;

	SetCapture();
	/*��ͼͼ�ε���Ҫ*/
	m_ptOrigin = point;
	m_ptEnd = point;
	m_ptOld = point;
	if (m_PolyCount == 0)
	{
		m_ptPolyFirst = point;
	}

	/*�����ı����������Ҫ*/
	switch (m_DrawType)
	{
	case TTEXTINSERT:
		TEXTMETRIC tm;		//�����ı���Ϣ�ṹ�����
		dc.GetTextMetrics(&tm);		//����豸�������е��ı���Ϣ
		CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);	//���������С���������ʵĲ����
		ShowCaret();
		SetCaretPos(point);
		m_strLine.Empty();
		m_ptTextOrigin = point;
		break;
	case DERASE:		//��Ƥ
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth +3), (point.y + m_nLineWidth +3)), &D_erase);
		break;
	case DBRUSH:		//ˢ��
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_Brush);
		break;
	case DPAINTBUC:		//����Ͱ
		dc.SelectObject(&D_Brush);
		dc.ExtFloodFill(point.x, point.y, dc.GetPixel(point.x, point.y), FLOODFILLSURFACE);
		break;
	case DSELECT:
		//GetClientRect(&cwrect); //��ȡ�����пؼ�������
		////ScreenToClient(&cwrect); //ת��Ϊ��������CRect  
		//if (point.x > cwrect.left && point.y > cwrect.top && point.x)   //ȷ�����µ������ڿؼ�������   
		//{
		//	if (m_rectTracker.HitTest(point) < 0)     //���δ���о���ѡ���,���»�ѡ���
		//	{
		//		m_rectTracker.TrackRubberBand(this, point, TRUE);
		//		m_rectTracker.m_rect.NormalizeRect();   //���滯���Σ��������滯���������н��ܣ�

		//	}
		//	else           //������о���ѡ���
		//	{
		//		m_rectTracker.Track(this, point, TRUE);
		//		m_rectTracker.m_rect.NormalizeRect();   //���滯����
		//		
		//	}
		//	Invalidate();   //ˢ�´�������ʹ��CrectTracker�����ػ浽������
		//	m_rectTracker.Draw(&dc);
		//}
		//SendMessage(WM_RBUTTONUP, NULL, NULL);
		break;
	default:
		break;
	}
	
	m_BtisDown = true;		//����Ѱ���

	CFormView::OnLButtonDown(nFlags, point);
}


void CBottomFormView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this); //����dc
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //�������ƵĻ���
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//��������ʱ���Ļ�ˢ
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //��������ʱ���Ļ�ˢ
	}
	CBrush D_erase(GetBkColor(dc)); //������Ƥ��
	CBrush D_Brush(m_color);	//����ˢ��
	dc.SelectObject(&pen); //����ˢ�ͻ���ѡ���豸��������
	dc.SelectObject(pbrush);

	ReleaseCapture();

	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CRect rect;
	CBitmap bitmap;
	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pMDC->SelectObject(&pen); //����ˢ�ͻ���ѡ���豸��������
	m_pMDC->SelectObject(pbrush);
	m_pMDC->SelectObject(&bitmap);
	m_pMDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	if (m_BtisDown != true)
	{
		return;
	}

	switch (m_DrawType)
	{
	case DLINE:		//����
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);		//��ȥ��һ�ε���
		dc.SetROP2(R2_COPYPEN);		//ȱʡ��ͼģʽ������Ϊ������ɫ
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);		//���ƹ̶���
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(m_ptOld);		//���ڴ��б���
		break;
	case DRECT:		//������
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
		dc.SetROP2(R2_COPYPEN);		//ȱʡ��ͼģʽ������Ϊ������ɫ
		dc.Rectangle(CRect(m_ptOrigin, point));
		m_pMDC->Rectangle(CRect(m_ptOrigin, m_ptOld));
		break;
	case DELLI:		//����Բ
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
		dc.SetROP2(R2_COPYPEN);		//ȱʡ��ͼģʽ������Ϊ������ɫ
		dc.Ellipse(CRect(m_ptOrigin, point));
		m_pMDC->Ellipse(CRect(m_ptOrigin, m_ptOld));
		break;
	case DCURVE:	//������
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
		break;
	case DRRECT:	//��Բ�Ǿ���
		dc.RoundRect(CRect(m_ptOrigin, point), CPoint(15, 15));
		m_ptOld = point;
		break;
	case DARC:
		break;
	case DCIRCLE:	//��Բ
		if (((point.x>m_ptOrigin.x) && (point.y>m_ptOrigin.y)) || ((point.x<m_ptOrigin.x) && (point.y<m_ptOrigin.y)))
		{
			point.y = m_ptOrigin.y + (point.x - m_ptOrigin.x);
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		else
		{
			point.y = m_ptOrigin.y - (point.x - m_ptOrigin.x);
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		m_ptOld = point;
		break;
	case DPOLY:		//�������
		m_arrayP[m_PolyCount++] = point;
		m_ptPolyLast = point;
		if (m_PolyCount > 1)	//�㳬��1��ʱ��������
		{
			dc.Polyline(m_arrayP, m_PolyCount);
			m_pMDC->Polyline(m_arrayP, m_PolyCount);
		}
		break;
	case DERASE:	//����Ƥ
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_erase);
		m_pMDC->FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_erase);
		break;
	case DBRUSH:	//��ˢ��
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_Brush);
		m_pMDC->FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_Brush);
		break;

	default:
		break;
	}
	/*CDC *m_NodeDC = new CDC;
	m_NodeDC = m_pMDC;
	m_listDC.AddHead(m_NodeDC);*/

	/*CGraph *pGraph = new CGraph(m_DrawType, m_ptOrigin, point);	//����ûʲô��
	m_ptrArray.Add(pGraph);*/

	m_BtisDown = false;
	//if (m_DrawType >= DLINE && m_DrawType <= DPOLY)
	//{
		
	//}
	
	//CFormView::OnLButtonUp(nFlags, point);
}

void CBottomFormView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	if (pStatus)						//״̬�������ǰ���ָ���λ��
	{
		str.Format(_T("X=%d,Y=%d"), point.x, point.y);
		pStatus->SetWindowTextW(str);
	}

	CClientDC dc(this); //����dc
	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //�������ƵĻ���
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//��������ʱ���Ļ�ˢ
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //��������ʱ���Ļ�ˢ
	}
	dc.SelectObject(&pen); //����ˢ�ͻ���ѡ���豸��������
	CBrush *POldBrush = dc.SelectObject(pbrush);

	CPen D_erase(1, 2*m_nLineWidth+6, GetBkColor(dc)); //������Ƥ��

	CPen D_Brush(1, 2 * m_nLineWidth + 6, m_color); //����ˢ��

	CPen D_LightPen(1, m_nLineWidth + 8, m_color_lightpen/*RGB(255,255,77)*/);	//����ӫ���
	int OldROP = 0;		//�ɵĻ��ģʽ

	CPen D_BallPen(1, m_nLineWidth + 3, m_color);	//����Բ���

	//CPoint mag_pt(0, 0);
	//GetCursorPos(&mag_pt);//��굱ǰ����Ļλ��ʵ�ַŴ�����������ƶ�
	//ScreenToClient(&mag_pt);
	//CPoint ptLeftTop(mag_pt.x + OFFSETWIDE, mag_pt.y + OFFSETHIGH);
	//CRect mag_rt;
	//GetClientRect(&mag_rt);
	//CBitmap m_pBitmap;
	//m_pBitmap.CreateCompatibleBitmap(&dc, mag_rt.Width(), mag_rt.Height());
	//CBitmap *pOldBitmap;
	//CPen mag_pen;
	//CPen *mag_pOldPen;
	//int mag_nWidth;

	if (m_BtisDown != true)
	{
		return;
	}

	switch (m_DrawType)
	{
	case DLINE:
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);		//��ȥ��һ�ε���
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);		//���Ƶ�ǰ����ʱ��
		m_ptOld = point;
		break;
	case DRECT:
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
		dc.Rectangle(CRect(m_ptOrigin, point));
		m_ptOld = point;
		break;
	case DELLI:
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
		dc.Ellipse(CRect(m_ptOrigin, point));
		m_ptOld = point;
		break;
	case DCURVE:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
		break;
	case DRRECT:
		dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
		dc.RoundRect(CRect(m_ptOrigin, m_ptOld), CPoint(15, 15));
		dc.RoundRect(CRect(m_ptOrigin, point), CPoint(15, 15));
		m_ptOld = point;
		break;
	case DARC:
		break;
	case DCIRCLE:
		if (((point.x>m_ptOrigin.x) && (point.y>m_ptOrigin.y)) || ((point.x<m_ptOrigin.x) && (point.y<m_ptOrigin.y)))
		{
			point.y = m_ptOrigin.y + (point.x - m_ptOrigin.x);
			dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
			dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		else
		{
			point.y = m_ptOrigin.y - (point.x - m_ptOrigin.x);
			dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
			dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		m_ptOld = point;
		break;
	case DPOLY:
		if (m_PolyCount != 0)
		{
			dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
			dc.MoveTo(m_ptPolyLast);
			dc.LineTo(point);		//��������Щ���⣬��˸������m_ptOld�����һ����
			dc.MoveTo(m_ptPolyLast);
			dc.LineTo(point);		//���Ƶ�ǰ����ʱ��
		}
		else
		{
			dc.SetROP2(R2_NOTXORPEN);		//��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOld);		//��ȥ��һ�ε���
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);		//���Ƶ�ǰ����ʱ��
		}
		m_ptOld = point;
		break;
	case DERASE:		//��Ƥ��
		dc.SelectObject(&D_erase);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(point);
		m_ptOrigin = point;
		break;
	case DBRUSH:
		dc.SelectObject(&D_Brush);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(point);
		m_ptOrigin = point;
		break;
	case DLIGHTPEN:
		OldROP = dc.SetROP2(R2_MASKPEN);
		dc.SelectObject(&D_LightPen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(point);
		m_ptOrigin = point;
		dc.SetROP2(OldROP);
		break;
	case DPENCIL:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
		break;
	case DBALLPEN:		//Բ���
		dc.SelectObject(&D_BallPen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
	case DMAGNIFY:

		//CXTPWnd *pWnd = new CXTPWnd;
		//m_pMainWnd = pWnd;
		//pWnd->XCreate();
		//return TRUE;

		//ptLeftTop = mag_rt.TopLeft();
		//dc.CreateCompatibleDC(m_pMDC);
		//pOldBitmap = dc.SelectObject(&m_pBitmap);//m_pBitmap����ĵ�ǰ�����λͼû�н��а������ϳɵĿ��Կ���һ��������λ�ȡ�Ļ���Ҳ���Ըĳ�����Ҫ��λͼ	
		//m_pMDC->StretchBlt(ptLeftTop.x, ptLeftTop.y, MAGNIFIERSIZE * MAGNIFYINGMULTIPLE, MAGNIFIERSIZE * MAGNIFYINGMULTIPLE, &dc,	                 
		//	(mag_pt.x  - MAGNIFIERSIZE / 2), (mag_pt.y  - MAGNIFIERSIZE / 2),	                 
		//	MAGNIFIERSIZE,MAGNIFIERSIZE, SRCCOPY);//����ͼƬ�ﵽ�Ŵ��Ч��
		//mag_nWidth = MAGNIFIERSIZE * MAGNIFYINGMULTIPLE;	//���м��ʮ��Begin	
		//
		//mag_pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		//mag_pOldPen = m_pMDC->SelectObject(&mag_pen);
		//m_pMDC->MoveTo(ptLeftTop.x, ptLeftTop.y + mag_nWidth / 2);
		//m_pMDC->LineTo(ptLeftTop.x + mag_nWidth, ptLeftTop.y + mag_nWidth / 2);
		//m_pMDC->MoveTo(ptLeftTop.x + mag_nWidth / 2, ptLeftTop.y);
		//m_pMDC->LineTo(ptLeftTop.x + mag_nWidth / 2, ptLeftTop.y + mag_nWidth);
		//m_pMDC->SelectObject(mag_pOldPen);	//���м��ʮ��End 	//���߿�Begin
		//m_pMDC->SelectStockObject(NULL_BRUSH);
		//m_pMDC->Rectangle(ptLeftTop.x, ptLeftTop.y, ptLeftTop.x + mag_nWidth, ptLeftTop.y + mag_nWidth);	//���߿�End 		
		//
		//dc.SelectObject(pOldBitmap);	
		//dc.DeleteDC();

	default:
		break;
	}
	
	CFormView::OnMouseMove(nFlags, point);
}

void CBottomFormView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this); //����dc
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //�������ƵĻ���
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//��������ʱ���Ļ�ˢ
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //��������ʱ���Ļ�ˢ
	}
	dc.SelectObject(&pen); //����ˢ�ͻ���ѡ���豸��������
	dc.SelectObject(pbrush);
	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CRect rect;
	CBitmap bitmap;
	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pMDC->SelectObject(&pen);		//����ˢ�ͻ���ѡ���ڴ���
	m_pMDC->SelectObject(pbrush);
	m_pMDC->SelectObject(&bitmap);
	m_pMDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	switch (m_DrawType)
	{
	case DPOLY:
		if (m_PolyCount != 0)
		{
			dc.MoveTo(m_ptPolyLast);
			dc.LineTo(point);
			dc.MoveTo(point);
			dc.LineTo(m_ptPolyFirst);
			m_pMDC->MoveTo(m_ptPolyLast);
			m_pMDC->LineTo(point);
			m_pMDC->MoveTo(point);
			m_pMDC->LineTo(m_ptPolyFirst);
			m_PolyCount = 0;
		}
		break;
	default:
		break;
	}

	CFormView::OnRButtonUp(nFlags, point);
}


void CBottomFormView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)		//�����ַ�
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //�������ƵĻ���
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//��������ʱ���Ļ�ˢ
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //��������ʱ���Ļ�ˢ
	}

	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CRect rect;
	CBitmap bitmap;
	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pMDC->SelectObject(&bitmap);
	m_pMDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	CFont *pOldFont = dc.SelectObject(&m_font);
	m_pMDC->SelectObject(&m_font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	dc.SetTextColor(m_color);
	m_pMDC->SetTextColor(m_color);
	if (0x0d == nChar)			//�س���Ϊ0x0d
	{
		m_strLine.Empty();
		m_ptTextOrigin.y += tm.tmHeight;
		/*m_strLine += "\r\n";*/
	}
	else if(0x08 == nChar)		//�˸��Ϊ0x08
	{
		COLORREF clr = dc.SetTextColor(dc.GetBkColor());	//��Ҫɾ�����ַ���ɫ����Ϊ���屳��ɫ,����ԭ����ɫ
		dc.TextOutW(m_ptTextOrigin.x, m_ptTextOrigin.y, m_strLine);
		m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);		//����ָ��ֵ�Ŀ�����ַ���
		dc.SetTextColor(clr);	
	}
	else
	{
		m_strLine += (char)nChar;
	}

	CSize sz = dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.x = m_ptTextOrigin.x + sz.cx;
	pt.y = m_ptTextOrigin.y;
	SetCaretPos(pt);
	dc.TextOutW(m_ptTextOrigin.x, m_ptTextOrigin.y, m_strLine);
	m_pMDC->TextOutW(m_ptTextOrigin.x, m_ptTextOrigin.y, m_strLine);

	dc.SelectObject(pOldFont);

	CFormView::OnChar(nChar, nRepCnt, nFlags);
}

void CBottomFormView::OnFileSave()		//�����ļ�
{
	// TODO: �ڴ���������������
	m_Close = true;	//��ʾҪ�ر�
	CClientDC dc(this);
	CRect rect;
	BOOL  showMsgTag;                  //�Ƿ�Ҫ������ͼ�񱣴�ɹ��Ի���"     
	GetClientRect(&rect);                  //��ȡ������С    
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.Width(), rect.Height());       //��������λͼ  

	HDC hdc = CreateCompatibleDC(dc);      //��������DC���Ա㽫ͼ�񱣴�Ϊ��ͬ�ĸ�ʽ    
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);  //��λͼѡ��DC�������淵��ֵ   

	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);        //����ĻDC��ͼ���Ƶ��ڴ�DC��    

	CImage image;
	image.Attach(hbitmap);                //��λͼת��Ϊһ��ͼ��     

	showMsgTag = TRUE;
	CString  strFilter = _T("λͼ�ļ�(*.bmp)|*.bmp|JPEG ͼ���ļ�|*.jpg|GIFͼ���ļ� | *.gif | PNGͼ���ļ� | *.png | ������ʽ*.*) | *.* || ");  

	CFileDialog dlg(FALSE, _T("bmp"), _T("test.bmp"), NULL, strFilter);

	if (dlg.DoModal() != IDOK)
	{
		m_Close = false;		//��ʾ���ر�
		return;
	}
	CString strFileName;          //����û�û��ָ���ļ���չ������Ϊ�����һ��  

	CString strExtension;

	strFileName = dlg.m_ofn.lpstrFile;

	if (dlg.m_ofn.nFileExtension = 0)               //��չ����ĿΪ0    
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
			case 1:
				strExtension = "bmp"; break;
			case 2:
				strExtension = "jpg"; break;
			case 3:
				strExtension = "gif"; break;
			case 4:
				strExtension = "png"; break;
			default:
				break;
		}
		strFileName = strFileName + "." + strExtension;
	}
	HRESULT hResult = image.Save(strFileName);     //����ͼ��    
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"), strFileName);
	}
	else
	{
		if (showMsgTag)
			MessageBox(_T("�ļ�����ɹ���"), strFileName);
	}
	image.Detach();
	SelectObject(hdc, hOldMap);
}