#pragma once


// CBottomFormView ������ͼ

class CBottomFormView : public CFormView
{
	DECLARE_DYNCREATE(CBottomFormView)

protected:
	CBottomFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBottomFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOTTOMFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:		//˽�г�Ա����
	CPtrArray m_ptrArray;
	


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnDraw(CDC* pDC);		//��дOnDraw()����
	virtual void OnInitialUpdate();

protected:		//�ؼ���س�Ա����

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileSave();

public:		//���ó�Ա����
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

	int m_DrawType;		//��ͼ������
	CPoint m_ptOrigin;		//��ʼ������
	CPoint m_ptEnd;			//�յ�����
	CPoint m_ptOld;			//��һ�εľɵ�
	bool m_BtisDown;		//�����Ƿ���
	CDC *m_pMDC;			//�����ڴ��е��豸��������DC����
	UINT m_nLineWidth;		// �߿������
	int  m_nLineStyle;		//���ͣ�ʵ�ߡ����ߡ�����
	COLORREF m_color;		//ѡ�����ɫ
	COLORREF m_color_lightpen;	//ӫ��ʵ���ɫ
	CFont m_font;			//ѡ�������
	CString m_strFontName;	//��ʾѡ�������
	CPoint m_ptPolyFirst;	//����ͼ�еĵ�һ����
	CPoint m_ptPolyLast;	//����ͼ������
	CPoint m_arrayP[255];	//�洢����ͼ�����е�
	int m_PolyCount;		//���ߵĵ�ļ���
	CString m_strLine;		//�����ַ�ʱ���ַ���
	CPoint m_ptTextOrigin;
	bool m_flagFullPaint;	//��ɫ��䰴ť�İ���̧��״̬��ʶ
	CRectTracker m_rectTracker;		//��Ƥ�������
	CList<CDC*, CDC*&> m_listDC;		//λͼ��������
	int m_listPos;		//�����λ��
	CPoint m_scRollpt;		//����������ͼλ�Ƶ㣩
	bool m_Close;		//�Ƿ�Ҫ�ر��ļ�

};




