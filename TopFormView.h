#pragma once



// CTopFormView ������ͼ

class CTopFormView : public CFormView
{
	DECLARE_DYNCREATE(CTopFormView)

protected:
	CTopFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTopFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOPFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
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

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void InitListCtrl();
private:
	CListCtrl     m_listCtrl;
	CImageList    m_imageList;
	short         m_imageW;
	short         m_imageH;
	HANDLE        m_handle;                        //ѭ������ͼƬ�̵߳ľ��
	GdiplusStartupInput   m_gdiplusStartupInput;   //ֻ��Ҫ�ڳ��������ʼ��ʼ��һ��
	ULONG_PTR             m_gdiplusToken;          //ֻ��Ҫ�ڳ��������ʼ��ʼ��һ��
private:
	bool  insertImageItem(TCHAR* path);
public:
	void UpdateImageList();
	afx_msg void OnShowpic();
};





