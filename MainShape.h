#pragma once
class CMainShape
{
public:
	CMainShape();
	~CMainShape();

public:		//���ó�Ա����
	CPoint m_ptOrigin;		//��ʼ������
	CPoint m_ptEnd;			//�յ�����
	int m_DrawType;			//����ͼ������
};

class CLine : public CMainShape
{

};

class CRectangle : public CMainShape
{

};

class CEllipse : public CMainShape
{

};

