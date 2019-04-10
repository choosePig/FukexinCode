
// myStudy2View.h: CmyStudy2View 类的接口
//
#include <GL/glut.h>

#pragma once


class CmyStudy2View : public CView
{
private:
	bool bupdown = false, bupup = false, bdownup = false, bdowndown = false, bleftup = false, bleftdown = false, brightup = false, brightdown = false, bpageupup = false, bpageupdown = false,
		bpagedownup = false, bpagedowndown = false, aup = false, adown = false, wup = false, wdown = false, sup = false, sdown = false, dup = false,ddown=false,qup=false,qdown=false,edown=false,
		eup=false;

protected: // 仅从序列化创建
	CmyStudy2View() noexcept;
	DECLARE_DYNCREATE(CmyStudy2View)

// 特性
public:
	CmyStudy2Doc* GetDocument() const;
	CClientDC *m_pDC;
	HGLRC m_hglrc;
	CPoint p[20];
	CPtrArray m_save;
	unsigned int RC, RC0, RC1;//变量
	int wxl = 0, wxr = 0,wyt = 0, wyb =0;
	float x1, y1, x0, y0;//起止点坐标

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CmyStudy2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void Ondrawtriangle();

	void draw();
	 void Ontranslationany();
	 afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	 afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	 afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	 afx_msg void Ondrawany();
	 afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	 afx_msg void Onscaleany();
	 afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	 afx_msg void Onrolateany();
	 afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	 afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	 afx_msg
	void DDALine(CDC * pDC, int x0, int y0, int x1, int y1, int color);
	 void OnLine();
	 void juxing();	
	 afx_msg void Oninsjuxing();
	 int enCode(float xx, float yy);
	 void LineClip();
	 afx_msg void Oncut();
	 afx_msg void Onclear();
	 void DirectLineClip();
	 afx_msg void Ondirectecut();
	 afx_msg void Onlogo();
	 afx_msg void Oncolorselect();
	 afx_msg void OnLineweight();
	 afx_msg void OnLogophoto();
	 afx_msg void OnLogofamily();
	 afx_msg void OnLogowarning();
	 afx_msg
		 void draw3weiFunction();
	// void draw3();
	 
	

	 void draw3();

	 void Ondraw3wei();
	 afx_msg void OnCirclecutrectangle();
	 afx_msg void Ontranslation3wei();
	 afx_msg void Onmakeseal();
	 afx_msg void Onveandzhucefu();
	 afx_msg void Onzidingyi();
	 afx_msg
	
	 void ClipPolygonSuthHodg();
	 afx_msg
	 void yuanxing(CDC * pDC, int x0, int y0, double r, int color);
	 void Oncirclecut();
	 afx_msg void Oninscircle();
	 void CircleCut();
	 bool LineInterCircle(CPoint ptStart, CPoint ptEnd, CPoint ptCenter, double Radius2);
	
	 afx_msg void Onx();
	 afx_msg void OnTimer(UINT_PTR nIDEvent);
	 afx_msg void Ony();
	 afx_msg void Onz();
	 afx_msg void Onscale3wei();
};

#ifndef _DEBUG  // myStudy2View.cpp 中的调试版本
inline CmyStudy2Doc* CmyStudy2View::GetDocument() const
   { return reinterpret_cast<CmyStudy2Doc*>(m_pDocument); }
#endif

