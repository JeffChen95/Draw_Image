// TopFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WTImage.h"
#include "TopFormView.h"
#include "BottomFormView.h"
#include <windows.h>

extern CBottomFormView *pBottomFormView;		//����ָ��CBottom���ָ��

DWORD WINAPI GetImageThread(LPVOID lpParam);

// CTopFormView

IMPLEMENT_DYNCREATE(CTopFormView, CFormView)

CTopFormView::CTopFormView()
	: CFormView(IDD_TOPFORMVIEW)
{
	m_imageW = 120;
	m_imageH = 90;
}

CTopFormView::~CTopFormView()
{
}

void CTopFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTopFormView, CFormView)
	ON_COMMAND(ID_SHOWPIC, &CTopFormView::OnShowpic)
END_MESSAGE_MAP()


// CTopFormView ���

#ifdef _DEBUG
void CTopFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTopFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTopFormView ��Ϣ�������

int CTopFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rect;
	GetClientRect(&rect);
	//��̬����listctrl�ؼ� LVS_AUTOARRANGE���ú�ͼ����洰�ڴ�С�ı仯�Զ�����
	m_listCtrl.Create(LVS_SINGLESEL | LVS_ICON | WS_CHILD | WS_VISIBLE | LVS_SINGLESEL | LVS_AUTOARRANGE, CRect(rect), this, IDD_TOPFORMVIEW);
	InitListCtrl();
	return 0;
}

void CTopFormView::InitListCtrl()//ListCtrl��imagelist�ĳ�ʼ��
{

	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);  //��ʼ��GDI+
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//���õ�ǰ���б���ͼ�ؼ���չ����ʽ
	m_listCtrl.SetIconSpacing(CSize(140, 130));     //����ͼƬ���
													//��������ͼ��С����120 ��90
	m_imageW = 120;
	m_imageH = 90;
	m_imageList.Create(m_imageW, m_imageH, ILC_COLORDDB | ILC_COLOR32, 1, 1);     //wide of picture is 120,height is 90
	m_listCtrl.SetImageList(&m_imageList, LVSIL_NORMAL);     //CImageList associates CListCtrl//LVSIL_NORMAL:��ͼ�귽ʽ����ͼ���б�LVSIL_SMALLΪСͼ�꣬LVSIL_STATE ��ͼ��״̬����ͼ���б�
															 //UpdateImageList();
}

void CTopFormView::OnShowpic()
{
	// TODO: �ڴ���������������
	DWORD  dwID;
	//CreateThread�����̵߳Ļ����ϴ���һ�����̡߳�����ͼƬ�޷�ʵʱ��ʾ
	m_handle = CreateThread(NULL, 0, GetImageThread, this, 0, &dwID);
}


DWORD WINAPI GetImageThread(LPVOID lpParam)
{
	CTopFormView *pPicListDlg = (CTopFormView*)lpParam;
	pPicListDlg->UpdateImageList();
	return 1;
}
void CTopFormView::UpdateImageList()
{
	CString imagename;
	int a = 1, i = 0;
	//while(a<=7)
	while (i<3)
	{
		a = i % 7 + 1;//����ѭ�����ͼ��Ϊ����������˴���image�ļ��´��ͼƬ����1.jpg,2.jpgһֱ��7.jpg������
		imagename.Format(_T("D:\\%d.jpg"), a);
		TCHAR* imagename_t = new TCHAR[50];
		imagename_t = imagename.GetBuffer(imagename.GetLength());//cstring convert to tchar*
		imagename.ReleaseBuffer();
		insertImageItem(imagename_t);
		Sleep(300);
		i++;
	}
}
bool  CTopFormView::insertImageItem(TCHAR* path)
{
	Bitmap bmp(path);                     //����ͼƬ·��

	int sourceWidth = m_imageW;           //���ͼƬ���,���120�ʹ�����120������ͬ��
	int sourceHeight = bmp.GetHeight();   //���ͼƬ���     
	if (sourceHeight>m_imageH)             //��m_ImageList.Create(120��)�кܴ��ϵ�����С����
	{
		sourceHeight = m_imageH;           //���Ŀ�ȣ�ͼƬ���޷���ʾ
	}


	Bitmap* pThumbnail = static_cast<Bitmap*>(bmp.GetThumbnailImage(sourceWidth, sourceHeight, NULL, NULL)); //�趨����ͼ�Ĵ�С
	HBITMAP hBmp = NULL;
	pThumbnail->GetHBITMAP(Color(255, 255, 255), &hBmp);
	CBitmap *pImage = CBitmap::FromHandle(hBmp);         //ת����CBitmap��ʽλͼ
	if (hBmp == NULL)
	{
		AfxMessageBox(L"����Ϊ��");
	}
	/*CBitmap *pImage = new CBitmap;
	pImage->Attach(hBmp);*/


	TCHAR drive[MAX_PATH] = _T("");
	TCHAR dir[MAX_PATH] = _T("");
	TCHAR fname[MAX_PATH] = _T("");
	TCHAR ext[MAX_PATH] = _T("");

	_wsplitpath_s(path, drive, dir, fname, ext);
	drive[MAX_PATH - 1] = '\0';
	dir[MAX_PATH - 1] = '\0';
	fname[MAX_PATH - 1] = '\0';
	ext[MAX_PATH - 1] = '\0';
	CString itemName(fname);
	itemName.Append(ext);

	int index = m_imageList.Add(pImage, RGB(255, 255, 255));
	m_listCtrl.InsertItem(index, itemName, index);               // itemName���ֻ���ʾ��ͼƬ��
	return true;
}




