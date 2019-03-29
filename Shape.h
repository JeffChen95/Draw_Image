// Shape.h: interface for the Shape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__C6FCF805_15B4_4F8A_911B_4D2EBDB86094__INCLUDED_)
#define AFX_SHAPE_H__C6FCF805_15B4_4F8A_911B_4D2EBDB86094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum DRAWSORT{dsNULL,dsLine,dsCircle,dsPolyGon,dsQuLine,dsBezier,dsStroke,dsText};//��ͼ����
enum DRAWLINESORT{DlsNull,DlsDDA,DlsBresenham};//��ֱ�߷�ʽ:DDA����Bresenham

/*
*����ͼ����
*/
class Shape  
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw(CDC* pDC)=0;//����ͼ�η���,�������ʵ��
	void SetPenColor(long lColor);
protected:

	long	m_lPenColor;//������ɫ
};

/*
*ֱ����
*/
class Line : public Shape
{
public:
	Line(POINT start,POINT end);
	Line(const Line& other);
	Line();
	~Line();

	void Draw(CDC *pDC);//ֱ����Ļ��Ʒ���

	bool operator==(const Line& other)const;
	bool operator!=(const Line& other)const;
	void SetStartPoint(POINT tmp);
	void SetEndPoint(POINT tmp);
	void SetDrawLineSort(DRAWLINESORT tmp);
	POINT GetStartPoint();
	POINT GetEndPoint();
	//void SetPenColor(long lColor);
	friend double Distance(POINT pStart,POINT pEnd);//���������ľ���
	
private:
	POINT pStart;//���
	POINT pEnd;//�յ�
	//long	m_lPenColor;//������ɫ
	DRAWLINESORT dlsDrawSort;
	void Draw_DDA(CDC* pDC);
	void Draw_Bresenham(CDC *pDC);

};

/*
* Բ
*/
class Circle : public Shape
{
public:
	Circle(POINT pt,double r):pMid(pt),radis(r){};
	Circle(const Circle& other);
	Circle();
	~Circle(){};
	void Draw(CDC* pDC);
	void SetRadis(double r);
	void SetMidPoint(POINT pt);
	double GetRadis()const;
	void SetPenColor(long lColor);
	friend void CirclePoints(int x,int y,long color,CDC *pDC);
private:
	POINT pMid;//Բ��
	double radis;//�뾶
	long	m_lPenColor;//������ɫ
};


#endif // !defined(AFX_SHAPE_H__C6FCF805_15B4_4F8A_911B_4D2EBDB86094__INCLUDED_)
