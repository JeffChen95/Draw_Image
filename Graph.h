#pragma once
class CGraph
{
public:
	CGraph();
	CGraph(UINT m_nDrawType, CPoint m_ptOrigin, CPoint m_ptEnd);
	~CGraph();

public:		//��Ա����
	UINT m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
};

