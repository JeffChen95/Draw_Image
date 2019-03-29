
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);//�ָ���ͼ��Ӧ�˵���Ϣ

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	

public:
	CStatusBar        m_wndStatusBar;
	CToolBar          m_wndToolBar;
	CToolBar          m_shapeToolBar;		//����ͼ�εĹ�����
	CToolBar          m_penStyleToolBar;	//ʹ�õı���
	CToolBar		  m_lineTypeColorToolBar;	//�߹�����ɫ
	CToolBar		  m_packetToolBar;		//ʹ�õĹ��߰�����������Ŵ󾵵�
	CSplitterWnd      m_splitWnd;

	enum SBID { prompt, xName, xVal, yName, yVal };
	enum DTYPE		//��ͼ������
	{
		DLINE,		//����
		DCURVE,		//������
		DRECT,		//������
		DRRECT,		//��Բ�Ǿ���
		DARC,		//��Բ��
		DELLI,		//����Բ
		DCIRCLE,	//��Բ
		DPOLY,		//�������
		TTEXTINSERT,	//�ı������
		DERASE,		//��ͼ����Ƥ��
		DBRUSH,		//��ͼ��ˢ��
		DPAINTBUC,		//��ͼ������Ͱ
		DSELECT,	//ѡ���
		DMAGNIFY,	//�Ŵ�
		DLIGHTPEN,	//ӫ���
		DPENCIL,	//Ǧ��
		DBALLPEN,	//Բ���
		DBRUSHPEN,	//ë��
	};

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDline();
	afx_msg void OnDcurve();
	afx_msg void OnDrect();
	afx_msg void OnDround();
	afx_msg void OnDrrect();
	afx_msg void OnDarc();
	afx_msg void OnDellip();
	afx_msg void OnDpoly();
	afx_msg void OnLineWidthSetting();
	afx_msg void OnColor();
	afx_msg void OnFont();
	afx_msg void OnViewShapetool();
	afx_msg void OnUpdateViewShapetool(CCmdUI *pCmdUI);
	afx_msg void OnViewPenstyletoolbar();
	afx_msg void OnUpdateViewPenstyletoolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewSizeTypeColor();
	afx_msg void OnUpdateViewSizeTypeColor(CCmdUI *pCmdUI);
	afx_msg void OnViewPacketToolbar();
	afx_msg void OnUpdateViewPacketToolbar(CCmdUI *pCmdUI);
	afx_msg void OnAddText();
	afx_msg void OnEarser();
	afx_msg void OnBrush();
	afx_msg void OnFullPaint();
	afx_msg void OnPaintBucket();
	afx_msg void OnUpdateFullPaint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDline(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDcurve(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrrect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDarc(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDround(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDellip(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDpoly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAddText(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEarser(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrush(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePaintBucket(CCmdUI *pCmdUI);
	afx_msg void OnDselect();
	afx_msg void OnMagnify();
	afx_msg void OnLightpen();
	afx_msg void OnPencil();
	afx_msg void OnUpdateLightpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePencil(CCmdUI *pCmdUI);
	afx_msg void OnBallpen();
	afx_msg void OnBrushpen();
	afx_msg void OnUpdateBallpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushpen(CCmdUI *pCmdUI);


	afx_msg void OnUndo();
	afx_msg void OnPaint();
	afx_msg void OnClose();
};




