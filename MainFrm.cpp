
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "WTImage.h"

#include "MainFrm.h"

#include "TopFormView.h"
#include "BottomFormView.h"
#include "SettingDlg.h"
#include "WTImageDoc.h"
#include "MagnifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
extern CBottomFormView *pBottomFormView;		//����ָ��CBottom���ָ��

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DLINE, &CMainFrame::OnDline)
	ON_COMMAND(ID_DCURVE, &CMainFrame::OnDcurve)
	ON_COMMAND(ID_DRECT, &CMainFrame::OnDrect)
	ON_COMMAND(ID_DROUND, &CMainFrame::OnDround)
	ON_COMMAND(ID_DRRECT, &CMainFrame::OnDrrect)
	ON_COMMAND(ID_DARC, &CMainFrame::OnDarc)
	ON_COMMAND(ID_DELLIP, &CMainFrame::OnDellip)
	ON_COMMAND(ID_DPOLY, &CMainFrame::OnDpoly)
	ON_COMMAND(ID_LINE_WIDTH_SETTING, &CMainFrame::OnLineWidthSetting)
	ON_COMMAND(ID_COLOR, &CMainFrame::OnColor)
	ON_COMMAND(IDM_FONT, &CMainFrame::OnFont)
	ON_COMMAND(ID_VIEW_SHAPETOOL, &CMainFrame::OnViewShapetool)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHAPETOOL, &CMainFrame::OnUpdateViewShapetool)
	ON_COMMAND(ID_VIEW_PENSTYLETOOLBAR, &CMainFrame::OnViewPenstyletoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PENSTYLETOOLBAR, &CMainFrame::OnUpdateViewPenstyletoolbar)
	ON_COMMAND(ID_VIEW_SIZE_TYPE_COLOR, &CMainFrame::OnViewSizeTypeColor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZE_TYPE_COLOR, &CMainFrame::OnUpdateViewSizeTypeColor)
	ON_COMMAND(ID_VIEW_PACKET_TOOLBAR, &CMainFrame::OnViewPacketToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PACKET_TOOLBAR, &CMainFrame::OnUpdateViewPacketToolbar)
	ON_COMMAND(IDM_ADD_TEXT, &CMainFrame::OnAddText)
	ON_COMMAND(IDM_EARSER, &CMainFrame::OnEarser)
	ON_COMMAND(IDM_BRUSH, &CMainFrame::OnBrush)
	ON_COMMAND(IDM_FULL_PAINT, &CMainFrame::OnFullPaint)
	ON_COMMAND(IDM_PAINT_BUCKET, &CMainFrame::OnPaintBucket)
	ON_UPDATE_COMMAND_UI(IDM_FULL_PAINT, &CMainFrame::OnUpdateFullPaint)
	ON_UPDATE_COMMAND_UI(ID_DLINE, &CMainFrame::OnUpdateDline)
	ON_UPDATE_COMMAND_UI(ID_DCURVE, &CMainFrame::OnUpdateDcurve)
	ON_UPDATE_COMMAND_UI(ID_DRECT, &CMainFrame::OnUpdateDrect)
	ON_UPDATE_COMMAND_UI(ID_DRRECT, &CMainFrame::OnUpdateDrrect)
	ON_UPDATE_COMMAND_UI(ID_DARC, &CMainFrame::OnUpdateDarc)
	ON_UPDATE_COMMAND_UI(ID_DROUND, &CMainFrame::OnUpdateDround)
	ON_UPDATE_COMMAND_UI(ID_DELLIP, &CMainFrame::OnUpdateDellip)
	ON_UPDATE_COMMAND_UI(ID_DPOLY, &CMainFrame::OnUpdateDpoly)
	ON_UPDATE_COMMAND_UI(IDM_ADD_TEXT, &CMainFrame::OnUpdateAddText)
	ON_UPDATE_COMMAND_UI(IDM_EARSER, &CMainFrame::OnUpdateEarser)
	ON_UPDATE_COMMAND_UI(IDM_BRUSH, &CMainFrame::OnUpdateBrush)
	ON_UPDATE_COMMAND_UI(IDM_PAINT_BUCKET, &CMainFrame::OnUpdatePaintBucket)
	ON_COMMAND(ID_DSELECT, &CMainFrame::OnDselect)
	ON_COMMAND(IDM_MAGNIFY, &CMainFrame::OnMagnify)
	ON_COMMAND(ID_LIGHTPEN, &CMainFrame::OnLightpen)
	ON_COMMAND(ID_PENCIL, &CMainFrame::OnPencil)
	ON_UPDATE_COMMAND_UI(ID_LIGHTPEN, &CMainFrame::OnUpdateLightpen)
	ON_UPDATE_COMMAND_UI(ID_PENCIL, &CMainFrame::OnUpdatePencil)
	ON_COMMAND(ID_BALLPEN, &CMainFrame::OnBallpen)
	ON_COMMAND(ID_BRUSHPEN, &CMainFrame::OnBrushpen)
	ON_UPDATE_COMMAND_UI(ID_BALLPEN, &CMainFrame::OnUpdateBallpen)
	ON_UPDATE_COMMAND_UI(ID_BRUSHPEN, &CMainFrame::OnUpdateBrushpen)
	ON_COMMAND(ID_UNDO, &CMainFrame::OnUndo)
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	//// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_shapeToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_shapeToolBar.LoadToolBar(IDR_SHAPETOOL))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	m_shapeToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_shapeToolBar);
	

	if (!m_penStyleToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_penStyleToolBar.LoadToolBar(IDR_PENSTYLE))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	m_penStyleToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_penStyleToolBar);

	if (!m_lineTypeColorToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_lineTypeColorToolBar.LoadToolBar(IDR_SIZE_TYPE_COLOR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	m_lineTypeColorToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_lineTypeColorToolBar);

	if (!m_packetToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_packetToolBar.LoadToolBar(IDR_PACKET_TOOLBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	m_packetToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_packetToolBar);

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	RecalcLayout();		//���²��֣����´���ʹ���������ͣ����һ�С�
	CRect rect;
	m_wndToolBar.GetWindowRect(rect);
	rect.OffsetRect(1, 0);//ƫ��һ��λ��
	DockControlBar(&m_shapeToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(2, 0);//ƫ��2��λ��
	DockControlBar(&m_penStyleToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(3, 0);//ƫ��3��λ��
	DockControlBar(&m_lineTypeColorToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(4, 0);//ƫ��4��λ��
	DockControlBar(&m_packetToolBar, AFX_IDW_DOCKBAR_TOP, rect);

	//m_wndToolBar.m_pDockBar = NULL;//��ֹ����������
	//m_shapeToolBar.m_pDockBar = NULL;//��ֹ����������
	//m_penStyleToolBar.m_pDockBar = NULL;//��ֹ����������
	//m_lineTypeColorToolBar.m_pDockBar = NULL;//��ֹ����������
	//m_packetToolBar.m_pDockBar = NULL;//��ֹ����������

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	BOOL bFlag = m_splitWnd.CreateStatic(this, 2, 1);
	if (bFlag)
	{
		CSize sz(0, 0);
		m_splitWnd.CreateView(0, 0, RUNTIME_CLASS(CTopFormView), sz, pContext);			//�ϰ벿�ֿ�������ʾ��ͼѡ��������͡��߿���ɫ��
		m_splitWnd.CreateView(1, 0, RUNTIME_CLASS(CBottomFormView), sz, pContext);		//�°벿��������ͼ 
	}
	return bFlag;
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CFrameWnd::OnPaint()
	//DockControlBar(&m_wndToolBar);

	//DockControlBar(&m_shapeToolBar);

	//DockControlBar(&m_penStyleToolBar);

	//DockControlBar(&m_lineTypeColorToolBar);

	//DockControlBar(&m_packetToolBar);

	RecalcLayout();		//���²��֣����´���ʹ���������ͣ����һ�С�
	CRect rect;
	m_wndToolBar.GetWindowRect(rect);
	rect.OffsetRect(256, 0);//ƫ��һ��λ��
	DockControlBar(&m_shapeToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(123, 0);//ƫ��2��λ��
	DockControlBar(&m_penStyleToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(102, 0);//ƫ��3��λ��
	DockControlBar(&m_lineTypeColorToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(77, 0);//ƫ��4��λ��
	DockControlBar(&m_packetToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	//rect.OffsetRect(176, 0);//ƫ��5��λ��
}

void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	int IsSave = MessageBox(_T("�Ƿ񱣴�"), _T("Warning"), MB_YESNOCANCEL);
	if (IsSave == IDCANCEL)
	{
		return;
	}
	if (IsSave == IDYES)
	{
		pBottomFormView->OnFileSave();
	}
	if (IsSave == IDNO || pBottomFormView->m_Close)		//Ϊ�˿����ļ�������е��ȡ��(��ʱm_Close��Ϊfalse)�󲻻�ֱ���˳�����
	{
		CFrameWnd::OnClose();
	}
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

//����OnCmdMsg ʹ�÷ָ���ͼ�У�ÿ��view�ܹ����յ��˵���Ӧ��Ϣ
//�ȵ���ȱʡ�������������û�б�����(ȱʡ��OnCmdMsg����FALSE)�����ȡ��ǰ������ͼָ�룬����ÿ����ͼ��OnCmdMsg����,��������Ϣ���͸�ÿ����ͼ��
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{	if ( CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) )		
		return TRUE;	
	CWTImageDoc* pDoc = (CWTImageDoc* ) GetActiveDocument ();
	POSITION pos = NULL;	
	if ( pDoc != NULL )	
		pos = pDoc->GetFirstViewPosition ();
	while ( pos != NULL )	
	{		
		CView* pNextView = pDoc->GetNextView ( pos );	
		if ( pNextView != GetActiveView() )		
		{			
			if ( pNextView->OnCmdMsg ( nID, nCode, pExtra, pHandlerInfo ) )		
				return TRUE;	
		}	
	} 	
	return FALSE;
}


void CMainFrame::OnDline()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DLINE;		//ͼ�����߶�
}


void CMainFrame::OnDcurve()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DCURVE;		//ͼ��������
}


void CMainFrame::OnDrect()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DRECT;		//ͼ���Ǿ���
}

void CMainFrame::OnDrrect()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DRRECT;		//ͼ����Բ�Ǿ���
}

void CMainFrame::OnDarc()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DARC;		//ͼ����Բ��
}

void CMainFrame::OnDround()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DCIRCLE;		//ͼ����Բ��
}

void CMainFrame::OnDellip()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DELLI;		//ͼ������Բ
}

void CMainFrame::OnDpoly()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DPOLY;		//ͼ���Ƕ����
}

void CMainFrame::OnLineWidthSetting()
{
	// TODO: �ڴ���������������
	CSettingDlg dlg;
	dlg.m_nLineWidth = pBottomFormView->m_nLineWidth;
	dlg.m_nLineStyle = pBottomFormView->m_nLineStyle;
	if (IDOK == dlg.DoModal())
	{
		pBottomFormView->m_nLineWidth = dlg.m_nLineWidth;
		pBottomFormView->m_nLineStyle = dlg.m_nLineStyle;
	}

}

void CMainFrame::OnColor()
{
	// TODO: �ڴ���������������
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult = pBottomFormView->m_color;
	if (IDOK == dlg.DoModal())
	{
		pBottomFormView->m_color = dlg.m_cc.rgbResult;
	}

}

void CMainFrame::OnFont()
{
	// TODO: �ڴ���������������
	CFontDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		if (pBottomFormView->m_font.m_hObject)
		{
			pBottomFormView->m_font.DeleteObject();
		}
		pBottomFormView->m_font.CreateFontIndirectW(dlg.m_cf.lpLogFont);	//����ѡ�����ʼ��m_font����
		pBottomFormView->m_strFontName = dlg.m_cf.lpLogFont->lfFaceName;	//����������
	}
}

void CMainFrame::OnAddText()
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = TTEXTINSERT;	//�ı������
}

void CMainFrame::OnEarser()		//��Ƥ��
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DERASE;
}

void CMainFrame::OnBrush()		//ˢ��
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DBRUSH;
}

void CMainFrame::OnLightpen()		//ӫ���
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DLIGHTPEN;
}

void CMainFrame::OnPencil()		//Ǧ��
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DPENCIL;
}

void CMainFrame::OnBallpen()	//Բ���
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DBALLPEN;
}


void CMainFrame::OnBrushpen()	//ë��
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DBRUSHPEN;
}



void CMainFrame::OnPaintBucket()	//����Ͱ
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DPAINTBUC;
}

void CMainFrame::OnFullPaint()		//��ɫ���
{
	// TODO: �ڴ���������������
	if (pBottomFormView->m_flagFullPaint == false)
	{
		pBottomFormView->m_flagFullPaint = true;		//��ť����״̬�����������״̬
	}
	else
	{
		pBottomFormView->m_flagFullPaint = false;
	}
}


void CMainFrame::OnDselect()	//ѡ���
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DSELECT;
}

void CMainFrame::OnMagnify()	//�Ŵ�
{
	// TODO: �ڴ���������������
	pBottomFormView->m_DrawType = DMAGNIFY;
	CMagnifyDlg magDlg;
	magDlg.DoModal();
	//CWnd *pChWnd = new CWnd;
	//pChWnd->CreateEx(0,//WS_EX_TOPMOST,
	//	AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
	//	(LPCTSTR)"Magnify",
	//	WS_POPUP,//|WS_BORDER,//WS_OVERLAPPEDWINDOW,
	//	0, 0, 300, 180,
	//	m_splitWnd,
	//	NULL,
	//	NULL);
	//pChWnd->CenterWindow();
	//pChWnd->ShowWindow(SW_SHOW);
}





void CMainFrame::OnViewShapetool()
{
	// TODO: �ڴ���������������
	if (m_shapeToolBar.IsWindowVisible())
	{
		m_shapeToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_shapeToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_shapeToolBar);
}


void CMainFrame::OnUpdateViewShapetool(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_shapeToolBar.IsWindowVisible());
}


void CMainFrame::OnViewPenstyletoolbar()
{
	// TODO: �ڴ���������������
	if (m_penStyleToolBar.IsWindowVisible())
	{
		m_penStyleToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_penStyleToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_penStyleToolBar);
}


void CMainFrame::OnUpdateViewPenstyletoolbar(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_penStyleToolBar.IsWindowVisible());
}


void CMainFrame::OnViewSizeTypeColor()		//���������߿���ɫ�Ĺ�����������ͼ��ѡ����ʾ����ʾ
{
	// TODO: �ڴ���������������
	if (m_lineTypeColorToolBar.IsWindowVisible())
	{
		m_lineTypeColorToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_lineTypeColorToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_lineTypeColorToolBar);
}


void CMainFrame::OnUpdateViewSizeTypeColor(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_lineTypeColorToolBar.IsWindowVisible());
}

void CMainFrame::OnViewPacketToolbar()
{
	// TODO: �ڴ���������������
	if (m_packetToolBar.IsWindowVisible())
	{
		m_packetToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_packetToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_packetToolBar);
}

void CMainFrame::OnUpdateViewPacketToolbar(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_packetToolBar.IsWindowVisible());
}


void CMainFrame::OnUpdateFullPaint(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DRECT || pBottomFormView->m_DrawType == DELLI ||
		pBottomFormView->m_DrawType == DRRECT || pBottomFormView->m_DrawType == DCIRCLE ||
		pBottomFormView->m_DrawType == DPOLY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}

	if (pBottomFormView->m_flagFullPaint == false)		//��ť����̧��״̬
	{
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetCheck(TRUE);
	}
}


void CMainFrame::OnUpdateDline(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DLINE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateDcurve(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DCURVE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDrect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DRECT)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDrrect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DRRECT)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDarc(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DARC)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDround(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DCIRCLE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDellip(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DELLI)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDpoly(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DPOLY)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateAddText(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == TTEXTINSERT)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateEarser(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DERASE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateBrush(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DBRUSH)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdatePaintBucket(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DPAINTBUC)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateLightpen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DLIGHTPEN)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdatePencil(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DPENCIL)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateBallpen(CCmdUI *pCmdUI)	//Բ��ʵİ���̧��״̬
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DBALLPEN)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateBrushpen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (pBottomFormView->m_DrawType == DBRUSHPEN)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}



void CMainFrame::OnUndo()
{
	// TODO: �ڴ���������������
	
	if (pBottomFormView->m_listPos != 0)
	{
		pBottomFormView->m_pMDC = pBottomFormView->m_listDC.GetAt(pBottomFormView->m_listDC.FindIndex(2));
		pBottomFormView->m_listPos++;
	}
	Invalidate();
}
