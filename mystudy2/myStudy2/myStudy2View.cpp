
// myStudy2View.cpp: CmyStudy2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "myStudy2.h"
#endif

#include "myStudy2Doc.h"
#include "myStudy2View.h"
#include <GL/glut.h>
#include"CdialogDuobianxing.h"
#include"CdialogWeight.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define EPS 0.00001
#define LEFT 1;
#define RIGHT 2;
#define BOTTOM 4;
#define TOP 8;
// CmyStudy2View

IMPLEMENT_DYNCREATE(CmyStudy2View, CView)

BEGIN_MESSAGE_MAP(CmyStudy2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmyStudy2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_drawTriangle, &CmyStudy2View::Ondrawtriangle)
	ON_COMMAND(ID_translationAny, &CmyStudy2View::Ontranslationany)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_COMMAND(ID_drawAny, &CmyStudy2View::Ondrawany)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_scaleAny, &CmyStudy2View::Onscaleany)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_rolateAny, &CmyStudy2View::Onrolateany)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Line, &CmyStudy2View::OnLine)
	ON_COMMAND(ID_insJuxing, &CmyStudy2View::Oninsjuxing)
	ON_COMMAND(ID_cut, &CmyStudy2View::Oncut)
	ON_COMMAND(ID_clear, &CmyStudy2View::Onclear)
	ON_COMMAND(ID_directeCut, &CmyStudy2View::Ondirectecut)
	ON_COMMAND(ID_logo, &CmyStudy2View::Onlogo)
	ON_COMMAND(ID_colorSelect, &CmyStudy2View::Oncolorselect)
	ON_COMMAND(ID_LineWeight, &CmyStudy2View::OnLineweight)
	ON_COMMAND(ID_LOGOphoto, &CmyStudy2View::OnLogophoto)
	ON_COMMAND(ID_LOGOfamily, &CmyStudy2View::OnLogofamily)
	ON_COMMAND(ID_LOGOwarning, &CmyStudy2View::OnLogowarning)
	ON_COMMAND(ID_draw3wei, &CmyStudy2View::Ondraw3wei)
	ON_COMMAND(ID_CircleCutRectangle, &CmyStudy2View::OnCirclecutrectangle)
	ON_COMMAND(ID_translation3wei, &CmyStudy2View::Ontranslation3wei)
	ON_COMMAND(ID_makeSeal, &CmyStudy2View::Onmakeseal)
	ON_COMMAND(ID_veandzhucefu, &CmyStudy2View::Onveandzhucefu)
	ON_COMMAND(ID_zidingyi, &CmyStudy2View::Onzidingyi)

	ON_COMMAND(ID_circleCut, &CmyStudy2View::Oncirclecut)
	ON_COMMAND(ID_insCircle, &CmyStudy2View::Oninscircle)
	ON_COMMAND(ID_x, &CmyStudy2View::Onx)
	ON_WM_TIMER()
	ON_COMMAND(ID_y, &CmyStudy2View::Ony)
	ON_COMMAND(ID_z, &CmyStudy2View::Onz)
	ON_COMMAND(ID_scale3wei, &CmyStudy2View::Onscale3wei)
END_MESSAGE_MAP()

// CmyStudy2View 构造/析构

CmyStudy2View::CmyStudy2View() noexcept
{
	// TODO: 在此处添加构造代码

}

CmyStudy2View::~CmyStudy2View()
{
}

BOOL CmyStudy2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


typedef GLfloat Matrix3x3[3][3];
Matrix3x3 ini;
void setIdentity(Matrix3x3 m)
{
	GLint x, y;
	for (x = 0; x < 3; x++)
	{
		for (y = 0; y < 3; y++)
		{
			m[x][y] = (x == y);
		}
	}
}
void multiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint x, y;
	Matrix3x3 temp;
	for (x = 0; x < 3; x++)
	{
		for (y = 0; y < 3; y++)
		{
			temp[x][y] = m1[x][0] * m2[0][y] + m1[x][1] * m2[1][y] + m1[x][2] * m2[2][y];
		}
	}
	for (x = 0; x < 3; x++)
	{
		for (y = 0; y < 3; y++)
		{
			m2[x][y] = temp[x][y];
		}
	}
}
class WcPt2D
{
public:
	GLfloat x, y;
private:

};
WcPt2D verts[3] = { {50,25},{150,25},{100,100} };
void Triangle(WcPt2D *verts)
{
	
	GLint k = 0;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)
	{
		glVertex2f(verts[k].x, verts[k].y);
	}
	glEnd();
}
void transform(GLint n, WcPt2D *verts)
{
	GLint k;
	GLfloat temp;
	for (k = 0; k < n; k++)
	{
		temp = ini[0][0] * verts[k].x + ini[0][1] * verts[k].y + ini[0][2];
		verts[k].y = ini[1][0] * verts[k].x + ini[1][1] * verts[k].y + ini[1][2];
		verts[k].x = temp;
	}
}
void translate(GLfloat dx, GLfloat dy)
{
	Matrix3x3 trans1;
	setIdentity(trans1);
	trans1[0][2] = dx;
	trans1[1][2] = dy;
	multiply(trans1, ini);
}
void scale(GLfloat sx, GLfloat sy, WcPt2D fixedPt)
{
	Matrix3x3 scale1;
	setIdentity(scale1);
	scale1[0][0] = sx;
	scale1[0][2] = (1 - sx)*fixedPt.x;
	scale1[1][1] = sy;
	scale1[1][2] = (1 - sy)*fixedPt.y;
	multiply(scale1, ini);
}
void rotate(WcPt2D fixedPt, GLfloat theta)
{
	Matrix3x3 rotate1;
	setIdentity(rotate1);
	rotate1[0][0] = cos(theta);
	rotate1[0][1] = -sin(theta);
	rotate1[0][2] = fixedPt.x*(1 - cos(theta)) + fixedPt.y*sin(theta);
	rotate1[1][0] = sin(theta);
	rotate1[1][1] = cos(theta);
	rotate1[1][2] = fixedPt.y*(1 - cos(theta)) - fixedPt.x*sin(theta);
	multiply(rotate1, ini);

}
void duichen(int f)
{
	Matrix3x3 chen1;
	setIdentity(chen1);
	if (f == 0)
	{
		chen1[0][0] = -1;
	}
	else if (f == 1)
	{
		chen1[1][1] = -1;
	}
	else if(f==2)
	{
		chen1[0][0] = -1;
		chen1[1][1] = -1;
	}
	multiply(chen1, ini);
}
void CmyStudy2View::Ondrawtriangle()
{

	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	WcPt2D fixedPt = { 100,150 };
	setIdentity(ini);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLineWidth(1.0f);
	glColor3f(1.0, 0.0, 0.0);
	setIdentity(ini);
	Triangle(verts);
	translate(0, 100);
	scale(0.5, 0.5, fixedPt);
	rotate(fixedPt, 3.1415926 / 2);
	transform(3, verts);
	glColor3f(1.0, 1.0, 0.0);
	Triangle(verts);
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);

	// TODO: 在此添加命令处理程序代码
}
//第一个功能over
class WcPt3D
{
public:
	GLfloat x, y,z,c;
private:

};
typedef GLfloat Matrix4x4[4][4];
Matrix4x4 ini3;
void setIdentity3D(Matrix4x4 m)
{
	GLint x, y;
	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			m[x][y] = (x == y);
		}
	}
}
void multiply3D(Matrix4x4 m1, Matrix4x4 m2)
{
	GLint x, y;
	Matrix4x4 temp;
	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			
				temp[x][y] = m1[x][0] * m2[0][y] + m1[x][1] * m2[1][y] + m1[x][2] * m2[2][y]+m1[x][3] * m2[3][y];
			
			
		}
	}
	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			m2[x][y] = temp[x][y];
		}
	}
}

void transform3D(GLint n, WcPt3D *verts)
{
	GLint k;
	GLfloat temp1,temp2,temp3;
	for (k = 0; k < n; k++)
	{
		temp1 = ini3[0][0] * verts[k].x + ini3[0][1] * verts[k].y + ini3[0][2]*verts[k].z+ini3[0][3]* verts[k].c;
		temp2= ini3[2][0] * verts[k].x + ini3[2][1] * verts[k].y + ini3[2][2] * verts[k].z + ini3[2][3]* verts[k].c;
		temp3 = ini3[1][0] * verts[k].x + ini3[1][1] * verts[k].y + ini3[1][2] * verts[k].z + ini3[1][3] * verts[k].c;
		verts[k].y =temp3;
		verts[k].x = temp1;
		verts[k].z = temp2;
	}
	
}
void zhouce3D(GLfloat theta1,GLfloat theta2)
{

	Matrix4x4 zhouce1;
	setIdentity3D(zhouce1);
	zhouce1[0][0] = (float)cos(theta2);
	zhouce1[0][2] = (float)sin(theta2);
	zhouce1[1][0] = -sin(theta1)*sin(theta2);
	zhouce1[1][1] = (float)cos(theta1);
	zhouce1[1][2] = sin(theta1)*cos(theta2);
	zhouce1[2][2] = 0;
	zhouce1[3][3] = 1;
	
	multiply3D(zhouce1, ini3);
}
void translate3D(GLfloat x, GLfloat y, GLfloat z)
{
	Matrix4x4 trans3D;
	setIdentity3D(trans3D);
	trans3D[0][3] = x;
	trans3D[1][3] = y;
	trans3D[2][3] = z;
	multiply3D(trans3D, ini3);

}
void ce3D()
{

	Matrix4x4 ce3D;
	setIdentity3D(ce3D);
	ce3D[0][0] = 0;
	ce3D[1][1] = 1;
	ce3D[2][2] = 1;
	ce3D[3][3] = 1;
	multiply3D(ce3D, ini3);
}
void fu3D()
{

	Matrix4x4 fus3D;
	setIdentity3D(fus3D);
	fus3D[0][0] = 1;
	fus3D[1][1] = 0;
	//zhus3D[1][2] = -1;
	//zhus3D[2][1] = 1;
	fus3D[2][2] = 1;
	multiply3D(fus3D, ini3);
}
void zhu3D()
{

	Matrix4x4 zhus3D;
	setIdentity3D(zhus3D);
	zhus3D[0][0] = 1;
	//zhus3D[0][1] = -1;
	zhus3D[1][1] = 1;
	//zhus3D[2][1] = 0;
	zhus3D[2][2] = 0;
	multiply3D(zhus3D, ini3);
}
void rotate3D(int x,float theta)
{
	Matrix4x4 ro3D;
	setIdentity3D(ro3D);
	if (x == 0)
	{
		ro3D[1][1] = cos(theta);
		ro3D[1][2] = -sin(theta);
		ro3D[2][1] = sin(theta);
		ro3D[2][2] == cos(theta);
	}
	else if (x == 1)
	{
		ro3D[0][0] = cos(theta);
		ro3D[0][2] = sin(theta);
		ro3D[2][0] = -sin(theta);
		ro3D[2][2] = cos(theta);
	}
	else if(x==2)
	{
		ro3D[0][0] = cos(theta);
		ro3D[0][1] = -sin(theta);
		ro3D[1][0] = sin(theta);
		ro3D[1][1] = cos(theta);
	}
	multiply3D(ro3D, ini3);
}
void scale3D(GLfloat sx, GLfloat sy, GLfloat sz)
{
	Matrix4x4 sc3D;
	setIdentity3D(sc3D);
	sc3D[0][0] = sy;
	//zhus3D[0][1] = -1;
	sc3D[1][1] = sy;
	//zhus3D[2][1] = 0;
	sc3D[2][2] = sz;
	multiply3D(sc3D, ini3);

}
// CmyStudy2View 打印


void CmyStudy2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmyStudy2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmyStudy2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmyStudy2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CmyStudy2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmyStudy2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CmyStudy2View 诊断

#ifdef _DEBUG
void CmyStudy2View::AssertValid() const
{
	CView::AssertValid();
}

void CmyStudy2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmyStudy2Doc* CmyStudy2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmyStudy2Doc)));
	return (CmyStudy2Doc*)m_pDocument;
}
#endif //_DEBUG


// CmyStudy2View 消息处理程序

//前期工作
int CmyStudy2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int n;
	m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);
	//初始化像素格式
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  //结构大小
		1,
		PFD_DRAW_TO_WINDOW |             //窗口中绘图
		PFD_SUPPORT_OPENGL |             //支持OPENGL
		PFD_DOUBLEBUFFER,               //双缓冲模式
		PFD_TYPE_RGBA,                 //RGBA颜色模式
		24,                           // 24位色彩深度
		0,0,0,0,0,0,                   //无颜色位
		0,                           // 无alpha 缓存
		0,                           //无移位
		0,                           //无加速缓存
		0,0,0,0,                     //无累积位
		32,                          //32位z缓存
		0,                           //无模板缓存
		0,                           //无辅助缓存
		PFD_MAIN_PLANE,              //PFD主平面
		0,                           //保留
		0,0,0                        //忽略主层掩模
		};
	//选择像素格式
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)//渲染描述表是OpenGL输出与Windows设备描述表联系的机制，借助GetSafeHdc()将它转化为Windows的句柄
	{
		MessageBox(L"选择像素格式失败！"); return -1;
	}
	//设置像素格式
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox(L"设置像素格式失败！"); return -1;
	}
	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	m_hglrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	// TODO:  在此添加您专用的创建代码
	return 0;
	}
void CmyStudy2View::OnDestroy()
{
	wglMakeCurrent(NULL, NULL); //将当前绘图情景对象赋空
	   //删除当前绘图情景对象并释放所占内存
	if (m_hglrc) ::wglDeleteContext(m_hglrc);
	if (m_pDC) delete m_pDC;
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
int screeHeight = 0;
int screeWidth = 0;
void CmyStudy2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	screeHeight = cy;
	screeWidth = cx;
	if (m_hglrc) wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else return;
	glViewport(0, 0, cx, cy);//设置视口与窗口大小相同
	glMatrixMode(GL_PROJECTION);//设置变换模式为投影变换
	glLoadIdentity();//初始化投影变换矩阵
	//根据窗口大小设置调整正射投影矩阵,锁定纵横比,让图形不发生变形
	if (cx <= cy)
		glOrtho(-400.0, 400.0, -400.0*(GLfloat)cy / (GLfloat)cx, 400.0*(GLfloat)cy / (GLfloat)cx, -500.0, 500.0);
	else
		glOrtho(-400.0*(GLfloat)cx / (GLfloat)cy, 400.0*(GLfloat)cx / (GLfloat)cy, -400.0, 400.0, -500.0, 500.0);
	glMatrixMode(GL_MODELVIEW);//设置变换模式为变换模型
	glLoadIdentity();//初始化投影变换矩阵
	//gluLookAt(4, 0, 1.5, 0, 0, 0, 1, 1, 0);
	// TODO: 在此处添加消息处理程序代码
}

//bool isTranslate = false, isDraw = false, isScale = false, isRotate = false,isLine=false, isJuxing = false, m_clip=false,m_whole=true;
/*必要的变量设置*/
bool  m_clip = false,m_clip1=false,m_clip2=false,filled=false,isYuan=false,isJuxing=false,isZ=false;
double x = 0, y = 0, sx = 1, sy = 1, angle = 0, xsum = 0, ysum = 0, weight = 1.0f, x33=0, y33=0, z33=0,anglex=0;
int xAngle, yAngle,lcount=0,jcount,nn=6,rad=0;
WcPt2D fixed = { 0,0 },fixed1 = { 0,0 }, mouseRotate = { 0,0 };
CPoint p[20],lpoints[2],jpoints[2],ypoints;
WcPt2D pp[20] = { {0,0},{0,0}, {0,0}, {0,0},{0,0} };
COLORREF color = RGB(255, 0, 0);
int flag = 0;


//绘制任意形状大体over，细节修改，如灵敏度，等
/*绘制画线，旋转，缩放，平移一条龙*/
void CmyStudy2View::draw()
{
	float r = GetRValue(color);
	float g = GetGValue(color);
	float b = GetBValue(color);
	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(weight);
	if (flag==2)
	{
		setIdentity(ini);
		translate(x, y);
		x = 0;
		y = 0;
		transform(nn, pp);
	}
	if (flag==3)
	{
		setIdentity(ini);
		scale(sx, sx, { fixed.x,fixed.y });
		sx = 1;
		transform(nn, pp);
	}
	if (flag==4)
	{
		setIdentity(ini);
		//MessageBox(TEXT("旋转了吗"));
		rotate({ fixed1.x,fixed1.y }, angle);
		angle= 0;
		transform(nn, pp);
	}
	glColor3f(r/255.0,g/255.0,b/255.0); 
	if (filled)
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i < nn; i++)
		{
			glVertex2f(pp[i].x, pp[i].y);
		}
		glEnd();
	}
	if (!filled)
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < nn; i++)
		{
			glVertex2f(pp[i].x, pp[i].y);
		}
		glEnd();
	}
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);
	
	CString m;
	
	CDC *pDC = GetWindowDC();
	for (int i = 0; i < nn; i++)
	{
		m.Format(TEXT("点%d:(%d,%d)"),i+1, int(pp[i].x),int(pp[i].y));
		pDC->TextOut(50, 50+i*20, m);
	}
	m.Format(TEXT("当前缩放基准点:(%d,%d)"), int(fixed.x), int(fixed.y));
	pDC->TextOut(50, 50 + nn * 20, m);
	m.Format(TEXT("当前旋转基准点:(%d,%d)"), int(fixed1.x), int(fixed1.y));
	pDC->TextOut(50, 50 + (nn + 1) * 20, m);
	m.Format(TEXT("当前颜色:(%d,%d,%d)"), int(r), int(g),int(b));
	pDC->TextOut(50, 50 + (nn + 2) * 20, m);
	m.Format(TEXT("当前线宽:(%d)"), int(weight));
	pDC->TextOut(50, 50 + (nn + 3) * 20, m);

	}
	
void CmyStudy2View::Ondrawany()
{
	flag = 1;
	CdialogDuobianxing dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		nn = dlg.nn;
		filled = dlg.filled;
	}
	
	// TODO: 在此添加命令处理程序代码
}
void CmyStudy2View::Ontranslationany()
{
	flag = 2;
}
void CmyStudy2View::Onscaleany()
{
	flag = 3;
	// TODO: 在此添加命令处理程序代码
}
void CmyStudy2View::Onrolateany()
{
	flag = 4;
	//Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}



/*鼠标键盘响应设置一条龙*/
void CmyStudy2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (flag == 11 || flag == 4)
	{
		if (nChar == VK_PRIOR)
		{
			bpageupup = FALSE;
			bpageupdown = TRUE;
			angle = angle + 3.1415926 / 180.0;
			Invalidate(TRUE);
		}
		if (nChar == VK_NEXT)
		{
			bpagedownup = FALSE;
			bpagedowndown = TRUE;
			angle = angle - 3.1415926 / 180.0;
			Invalidate(TRUE);
		}
	}

	if (nChar == VK_UP) {
		bupup = FALSE;
		bupdown = TRUE;
		y++;
		Invalidate(TRUE);
	}
	if (nChar == VK_DOWN) {
		bdownup =FALSE;
		bdowndown = TRUE;
		y--;
		Invalidate(TRUE);
	}
	if (nChar == VK_LEFT) {
		bleftup =FALSE;
		bleftdown = TRUE;
		x--;
		Invalidate(TRUE);
	}
	if (nChar == VK_RIGHT) {
		brightup = FALSE;
		brightdown = TRUE;
		x++;
		Invalidate(TRUE);
	}
	if ((nChar == VK_UP) && (::GetAsyncKeyState(VK_RIGHT)))
	{
		x++;
		y++;
		Invalidate(TRUE);
	//	brightdown = false;
	}
	else if ((nChar == VK_UP) && (::GetAsyncKeyState(VK_LEFT)))
	{
		x--;
		y++;
		Invalidate(TRUE);
	//	bleftdown = false;
	}
	else if ((nChar == VK_DOWN) && (::GetAsyncKeyState(VK_LEFT)))
	{
		x--;
		y--;
		
		Invalidate(TRUE);
	//	bleftdown = false;
	}
	else if ((nChar == VK_DOWN) && (::GetAsyncKeyState(VK_RIGHT)))
	{
		x++;
		y--;
		Invalidate(TRUE);
	//	brightdown = false;
	}
	if (nChar ==65) {
		aup = TRUE;
		adown = FALSE;
		x33--;
	
		Invalidate(TRUE);
	}
	if (nChar == 68) {
		dup = FALSE;
		ddown = TRUE;
		x33++;
		
		Invalidate(TRUE);
	}
	if (nChar == 83) {
		sup = FALSE;
		sdown = TRUE;
		y33--;
		Invalidate(TRUE);
	}
	if (nChar == 87) {
		wup = FALSE;
		wdown = TRUE;
		y33++;
		Invalidate(TRUE);
	}
	if (nChar == 81) {
		qup = FALSE;
		qdown = TRUE;
		isZ = true;
		z33++;
		
		Invalidate(TRUE);
	}
	if (nChar == 69) {
		eup = FALSE;
		edown = TRUE;
		isZ = true;
		z33--;
		Invalidate(TRUE);
	}
	//InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CmyStudy2View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_PRIOR)
	{
		//bpageupup = TRUE;
		//bpageupdown = FALSE;
		//Invalidate(TRUE);
	}
	if (nChar == VK_PRIOR)
	{
		//bpagedownup = TRUE;
		//bpagedowndown = FALSE;
		//Invalidate(TRUE);
	}
	if (nChar == VK_UP) {
		bupup = TRUE;
		bupdown = FALSE;
		Invalidate(TRUE);
	}
	if (nChar == VK_DOWN) {
		bdownup = TRUE;
		bdowndown = FALSE;
		Invalidate(TRUE);
	}
	if (nChar == VK_LEFT) {
		bleftup = TRUE;
		bleftdown = FALSE;
		Invalidate(TRUE);
	}
	if (nChar == VK_RIGHT) {
		brightup = TRUE;
		brightdown = FALSE;
		Invalidate(TRUE);
	}
	if (nChar == 65) {
		aup = TRUE;
		adown = FALSE;
		
		Invalidate(TRUE);
	}
	if (nChar == 68) {
		dup =TRUE;
		ddown = FALSE;
		
		Invalidate(TRUE);
	}
	if (nChar == 53) {
		sup =TRUE;
		sdown = FALSE;
		
		Invalidate(TRUE);
	}
	if (nChar == 57) {
		wup = TRUE;
		wdown = FALSE;
	
		Invalidate(TRUE);
	}
	if (nChar == 81) {
		qup = TRUE;
		qdown = FALSE;
		isZ = false;
		

		Invalidate(TRUE);
	}
	if (nChar == 69) {
		eup = TRUE;
		edown = FALSE;
		isZ = false;
		
		Invalidate(TRUE);
	}
	//InvalidateRect(NULL, FALSE);
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
void CmyStudy2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
					CView::OnChar(nChar, nRepCnt, nFlags);
	
}// CmyStudy2View 绘图
int count = 0,fcount=0;
void CmyStudy2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	GLint    viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat  winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	winX = (float)point.x;
	winY = screeHeight - (float)point.y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	CString str;
	if (flag==5)
	{
		CDC *pDC = GetWindowDC();
		CString str;
		if (jcount == 0) {
			jpoints[0] = point;
			jcount++;
			//wxl = posX;
		//	wyb = posY;
			wxl=jpoints[0].x , wyb=jpoints[0].y;
			//str.Format(TEXT("%d,%d"), wxl,wyb);
			//MessageBox(str);
		}
		else {
			jpoints[1] = point;

			//wxr = posX;
			//wyt = posY;
			wxr = jpoints[1].x, wyt = jpoints[1].y;
			str.Format(TEXT("%d,%d"), wxr,wyt);
			//MessageBox(str);
			Invalidate(TRUE);
			jcount = 0;
		}
	}
	if (flag==6)
	{
		CDC *pDC = GetWindowDC();
		CString str;
		if (lcount == 0) {
			lpoints[0] = point;
			//str.Format(TEXT("%d,%d"), lpoints[0].x, lpoints[0].y);
		//	MessageBox(str);
			lcount++;
		}
		else {
			lpoints[1] = point;
		//	str.Format(TEXT("%d,%d"), lpoints[1].x, lpoints[1].y);
		//	MessageBox(str);
		//	DDALine(pDC, lpoints[0].x, lpoints[0].y, lpoints[1].x, lpoints[1].y, RGB(255, 0, 0));
			Invalidate(TRUE);
			lcount = 0;
		}
		
	}
	if (flag == 7)
	{
		CDC *pDC = GetWindowDC();
		rad = 300;
		ypoints = point;
		Invalidate(TRUE);
		
	}
	if (flag==1)
	{
		switch (count)
		{
		case 0:
			pp[0].x = posX;
			pp[0].y = posY;	
			count++;
			break;
		case 1:
			pp[1].x = posX;
			pp[1].y = posY;
			if (count + 1 == nn)
			{
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break;
			}
			count++;

			break;
		case 2:
			pp[2].x = posX;
			pp[2].y = posY;
			if (count + 1 == nn)
			{
				draw();
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break;
			}
			count++;

			break;
		case 3:
			pp[3].x = posX;
			pp[3].y = posY;
			if (count + 1 == nn)
			{
				draw();
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break; 
			}
			count++;
			break;
		case 4:
			//pp[4] = point;
			pp[4].x = posX;
			pp[4].y = posY;
			if (count + 1 == nn)
			{
				draw();
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break;
			}
			count++;
			break;
		case 5:
		//	pp[5] = point;
			pp[5].x = posX;
			pp[5].y = posY;
			if (count + 1 ==nn)
			{
				draw();
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break;
			}
			count++;
			break;
		case 6:
			//	pp[5] = point;
			pp[6].x = posX;
			pp[6].y = posY;
			if (count + 1 == nn)
			{
				draw();
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break;
			}
			count++;
			break;
		case 7:
			//	pp[5] = point;
			pp[7].x = posX;
			pp[7].y = posY;
			if (count + 1 == nn)
			{
				draw();
				count = 0;
				for (int i = 0; i < 10; i++)
				{
					p[i].x = 0;
					p[i].y = 0;
				}
				break;
			}
			count++;
			break;
		}
	}
	if (flag==3)
	{
		fixed.x = (int)posX;
		fixed.y = (int)posY;
		str.Format(TEXT("%f,%f"), fixed.x, fixed.y);
		//MessageBox(str); 
	}
	if (flag == 4)
	{
		fixed1.x = (int)posX;
		fixed1.y = (int)posY;
		str.Format(TEXT("%f,%f"), fixed1.x, fixed1.y);
		//MessageBox(str);
	}
	
		
	//注意z轴一起缩放 不然坐标不对！20min
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnLButtonDown(nFlags, point);
}
BOOL CmyStudy2View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
		GLint    viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat  winX, winY, winZ;
		GLdouble posX, posY, posZ;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		winX = (float)pt.x;
		winY = screeHeight - (float)pt.y;
		glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
		pt.x = posX;
		pt.y = posY;
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if (sx >= 0)
		{
			sx += 0.05 *zDelta / 120;

		}
		else
		{
			if (zDelta > 0)
			{
				sx += 0.05 *zDelta / 120;
			}
		}
		//MessageBox(TEXT("我在缩放"));
		Invalidate(TRUE);
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
void CmyStudy2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}
void CmyStudy2View::OnMouseMove(UINT nFlags, CPoint point)
{


	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnMouseMove(nFlags, point);
}


/*印章*/
WcPt2D box[4] = { {-350,100},{-350,350},{-600,350},{-600,100} };
WcPt2D k1[4] = { {-370,340},{-370,330},{-455,330},{-455,340} };
WcPt2D k2[4] = { {-380,330},{-390,330},{-390,250},{-380,250} };
WcPt2D k3[4] = { {-380,250},{-410,250},{-410,240},{-380,240} };
WcPt2D k4[4] = { {-425,290},{-425,300},{-415,300},{-415,290} };
WcPt2D k5[4] = { {-405,280},{-435,280},{-435,310},{-405,310} };

WcPt2D f1[4] = { {-500,310},{-500,300},{-555,300},{-555,310} };
WcPt2D f2[4] = { {-510,330},{-520,330},{-520,250},{-510,250} };
WcPt2D f3[4] = { {-510,240},{-540,240},{-540,250},{-510,250} };
WcPt2D f4[4] = { {-535,275},{-530,280},{-535,285},{-540,280} };
WcPt2D f5[4] = { {-570,310},{-570,240},{-580,240},{-580,300} };
WcPt2D f6[4] = { {-550,330},{-560,335},{-595,300},{-585,295} };

WcPt2D xx1[4] = { {-590,180},{-580,180},{-580,210},{-590,210} };
WcPt2D x2[4] = { {-505,160},{-495,160},{-495,120},{-505,120} };
WcPt2D x3[4] = { {-540,180},{-530,180},{-530,150},{-540,150} };
WcPt2D x4[4] = { {-490,170},{-480,170},{-480,140},{-490,140} };
WcPt2D x5[4] = { {-570,195},{-560,195},{-560,120},{-570,120} };
WcPt2D x6[4] = { {-560,130},{-505,130},{-505,120},{-560,120} };



WcPt2D yy1[4] = { {-410,195},{-400,195},{-400,120},{-410,120} };
WcPt2D y2[4] = { {-420,205},{-465,205},{-465,195},{-420,195} };
WcPt2D y3[4] = { {-455,185},{-455,175},{-420,175},{-420,185} };
WcPt2D y4[4] = { {-465,165},{-465,155},{-420,155},{-420,165} };
WcPt2D y5[4] = { {-410,205},{-410,195},{-360,195},{-360,205} };
WcPt2D y6[4] = { {-360,150},{-370,150},{-370,195},{-360,195} };
WcPt2D y7[4] = { {-360,150},{-385,150},{-385,140},{-360,140} };
WcPt2D y8[4] = { {-465,195},{-465,165},{-455,165},{-455,195} };
WcPt2D y9[4] = { {-465,165},{-465,155},{-420,155},{-420,165} };
void drawyinzhang()
{

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(box[i].x, box[i].y);
	}
	glEnd();

	glColor3f(1.0, 1.0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(f1[i].x, f1[i].y);
	}
	glEnd();
	
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(f2[i].x, f2[i].y);
	}
	glEnd();


	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(f3[i].x, f3[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(f4[i].x, f4[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(f5[i].x, f5[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(f6[i].x, f6[i].y);
	}
	glEnd();
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(k1[i].x, k1[i].y);
	}
	//可
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(k2[i].x, k2[i].y);
	}
	//可
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(k3[i].x, k3[i].y);
	}
	//可
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(k5[i].x, k5[i].y);
	}
	//可
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(k4[i].x, k4[i].y);
	}
	//可
	glEnd();
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(xx1[i].x, xx1[i].y);
	}
	//心
	glEnd();

	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(x2[i].x, x2[i].y);
	}
	//心
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(x3[i].x, x3[i].y);
	}
	//心
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(x4[i].x, x4[i].y);
	}
	//心
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(x5[i].x, x5[i].y);
	}
	//心
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(x6[i].x, x6[i].y);
	}
	//心
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(yy1[i].x, yy1[i].y);
	}
	//印
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y2[i].x, y2[i].y);
	}
	//印
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y3[i].x, y3[i].y);
	}
	//印
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y4[i].x, y4[i].y);
	}
	//印
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y5[i].x, y5[i].y);
	}
	//印
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y6[i].x, y6[i].y);
	}
	//印
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y7[i].x, y7[i].y);
	}
	//印
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y8[i].x, y8[i].y);
	}
	//印
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(y9[i].x, y9[i].y);
	}
	//印
	glEnd();
}
void duichenyinzhang(int x)
{
	setIdentity(ini);
	duichen(x);
	transform(4, box);

	setIdentity(ini);
	duichen(x);
	transform(4, k1);

	setIdentity(ini);
	duichen(x);
	transform(4, k2);

	setIdentity(ini);
	duichen(x);
	transform(4, k3);

	setIdentity(ini);
	duichen(x);
	transform(4, k4);

	setIdentity(ini);
	duichen(x);
	transform(4, k5);

	setIdentity(ini);
	duichen(x);
	transform(4, xx1);

	setIdentity(ini);
	duichen(x);
	transform(4, x2);

	setIdentity(ini);
	duichen(x);
	transform(4, x3);

	setIdentity(ini);
	duichen(x);
	transform(4, x4);
	setIdentity(ini);
	duichen(x);
	transform(4, x5);
	setIdentity(ini);
	duichen(x);
	transform(4, x6);


	setIdentity(ini);
	duichen(x);
	transform(4, yy1);

	setIdentity(ini);
	duichen(x);
	transform(4, y2);

	setIdentity(ini);
	duichen(x);
	transform(4, y3);

	setIdentity(ini);
	duichen(x);
	transform(4, y4);
	setIdentity(ini);
	duichen(x);
	transform(4, y5);
	setIdentity(ini);
	duichen(x);
	transform(4, y6);
	setIdentity(ini);
	duichen(x);
	transform(4, y7);
	setIdentity(ini);
	duichen(x);
	transform(4, y8);
	setIdentity(ini);
	duichen(x);
	transform(4, y9);
	setIdentity(ini);
	duichen(x);
	transform(4, f1);

	setIdentity(ini);
	duichen(x);
	transform(4, f2);

	setIdentity(ini);
	duichen(x);
	transform(4, f3);

	setIdentity(ini);
	duichen(x);
	transform(4, f4);
	setIdentity(ini);
	duichen(x);
	transform(4, f5);
	setIdentity(ini);
	duichen(x);
	transform(4, f6);

}
void CmyStudy2View::Onmakeseal()
{


	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(8.0f);
	glColor3f(0.0, 0.0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 400);
	glVertex2f(0, -400);
	glVertex2f(-950, 0);
	glVertex2f(950, 0);
	glEnd();
	glLineWidth(3.0f);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
/*	glVertex2f(-475, 350);
	glVertex2f(-475, 100);
	glVertex2f(-350, 225);
	glVertex2f(-600, 225);
	glEnd();*/
	drawyinzhang();
	duichenyinzhang(1);
	drawyinzhang();
	duichenyinzhang(0);
	drawyinzhang();
	duichenyinzhang(1);
	drawyinzhang();
	
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);
	// TODO: 在此添加命令处理程序代码
}
/*裁剪一条龙*/
/*画线，生成窗口*/
void CmyStudy2View::DDALine(CDC *pDC, int x0, int y0, int x1, int y1, int color)
{

	int dm = 0;
	if (abs(x1 - x0) >= abs(y1 - y0))
	{
		dm = abs(x1 - x0);
	}
	else
	{
		dm = abs(y1 - y0);
	}
	float dx, dy, x, y, b;
	dx = (float)(x1 - x0) / dm;
	dy = (float)(y1 - y0) / dm;
	x = x0 + 0.5;
	y = y0 + 0.5;
	for (int i = 0; i < dm; i++)
	{

		pDC->SetPixel((int)x, int(y), color);
		x += dx;
		y += dy;
	}

}
void CmyStudy2View::OnLine()
{
	flag = 6;
	// TODO: 在此添加命令处理程序代码
}
void CmyStudy2View::Oninscircle()
{
	flag = 7;

	isYuan = true;
	isJuxing = false;
	x0 = 0; y0 = 0;  x1 = 0; y1 = 0;
	lpoints[0].x = 0; lpoints[0].y = 0; lpoints[1].x = 0; lpoints[1].y = 0;
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}
void CmyStudy2View::juxing()
{
	CPen m_pen;
	m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	CDC *pDC = GetWindowDC();
	CPen *oldPen = pDC->SelectObject(&m_pen);
	CRect rect(wxl, wyb, wxr, wyt);
	pDC->Rectangle(&rect);

}
void CmyStudy2View::Oninsjuxing()
{
	flag = 5;
	isYuan = false;
	isJuxing = true;
	x0 = 0; y0 = 0;  x1 = 0; y1 = 0;
	lpoints[0].x = 0; lpoints[0].y = 0; lpoints[1].x = 0; lpoints[1].y = 0;
	Invalidate(TRUE);
}
void Cirpot(CDC *pDC, int x0, int y0, int x, int y, int color)
{
	pDC->SetPixel((x0 + x), (y0 + y), color);
	pDC->SetPixel((x0 + y), (y0 + x), color);
	pDC->SetPixel((x0 + y), (y0 - x), color);
	pDC->SetPixel((x0 + x), (y0 - y), color);
	pDC->SetPixel((x0 - x), (y0 - y), color);
	pDC->SetPixel((x0 - y), (y0 - x), color);
	pDC->SetPixel((x0 - y), (y0 + x), color);
	pDC->SetPixel((x0 - x), (y0 + y), color);


}//整圆
void CmyStudy2View::yuanxing(CDC *pDC, int x0, int y0, double r, int color)
{
	int x, y, d;
	x = 0;
	y = (int)r;
	d = int(3 - 2 * r);
	while (x < y)
	{
		Cirpot(pDC, x0, y0, x, y, color);
		if (d < 0)
		{
			d += 4 * x + 6;
		}
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	if (x == y)
	{
		Cirpot(pDC, x0, y0, x, y, color);
	}

}

/*编码裁剪法*/
int CmyStudy2View::enCode(float xx, float yy)
{
	RC = 0;

	if (xx < wxl)
		RC = RC | LEFT;

	if (xx > wxr)
		RC = RC | RIGHT;

	if (yy < wyb)
		RC = RC | BOTTOM;

	if (yy > wyt)
		RC = RC | TOP;

	return RC;

}
void CmyStudy2View::LineClip()
{	
	
	float k;
	x0 = lpoints[0].x; y0 = lpoints[0].y;
	x1 = lpoints[1].x; y1 = lpoints[1].y;
	//MessageBox(TEXT("1111"));
	while (TRUE)
	{
		RC0 = enCode(x0,y0);
		RC1 = enCode(x1, y1);
		//	m.Format(TEXT("%f,%f,%f,%f"), x0,y0, x1, y1);
	//	MessageBox(m);
		//MessageBox(TEXT("1111"));
		if ((RC0 | RC1) == 0)
		{
		
			return;
		}
		else if ((RC0&RC1) != 0)
		{
			x1 = x0; y1 = y0;
			return;
		}
		else 
		{
			if (RC0 == 0)
			{
				unsigned int t;
				t = RC0; RC0 = RC1; RC1 = t;

				int tmp;
				tmp = x0; x0 = x1; x1 = tmp;
				tmp = y0; y0 = y1; y1 = tmp;
			}
		
			if (x1 - x0 == 0)
			{
				if ((RC0&1) || (RC0&2))
				{
					y0 = y1;
					return;
				}
				else
				{
					if (RC1 == 0)
					{
						if (RC0&4)
							y0 = wyb;
						else if (RC0&8)
							y0 = wyt;
					}
					else 
					{
						y0 = wyb;
						y1 = wyt;
					}
					return;
				}
			}
			k = (y0 - y1) / (x0 - x1);
			if (RC0&1)	
			{
				x0 = wxl;	
				y0 = y1 + k * (x0 - x1);
			}

			else if (RC0&2)
			{
				x0 = wxr;	
				y0 = y1 + k * (x0 - x1);
			}
			else if (RC0&4)
			{
				y0 = wyb;	
				x0 = x1 + (y0 - y1) / k;
			}
			else if (RC0&8)
			{
				y0 = wyt;	
				x0 = x1 + (y0 - y1) / k;
			}
		}


	}

}
void CmyStudy2View::Oncut()
{
	
	LineClip();
	m_clip = true;
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}
/*直接裁剪法*/
int  clipTest(float p, float q, float *u1, float *u2)
{
	float r;
	int retVal = 1;
	if (p < 0)
	{
		r = q / p;
		if (r > *u2)
		{
			retVal = 0;
		}
		else if (r > *u1)
		{
			*u1 = r;
		}
	}
	else if (p > 0)
	{
		r = q / p;
		if (r < *u1)
		{
			retVal = 0;
		}
		else if (r < *u2)
		{
			*u2 = r;
		}
	}
	else if (q < 0)
	{
		retVal = 0;
	}
	return retVal;
}
void CmyStudy2View::DirectLineClip()
{
	//CString m;
	x0 = lpoints[0].x; y0 = lpoints[0].y;
	x1 = lpoints[1].x; y1 = lpoints[1].y;
	//m.Format(TEXT("%f,%f,%f,%f"), x0, y0, x1, y1);
	//MessageBox(m);
	//wxl = 0, wxr = 0, wyt = 0, wyb = 00;
	float u1 = 0, u2 = 1, dx = x1 - x0, dy;
	if (clipTest(-dx, x0 - wxl, &u1, &u2))
	{
		if (clipTest(dx, wxr - x0, &u1, &u2))
		{
			dy = y1 - y0;
			if (clipTest(-dy, y0 - wyb, &u1, &u2))
			{
				if (clipTest(dy, wyt - y0, &u1, &u2))
				{
					if (u2 < 1)
					{
						x1 = x0 + u2 * dx;
						y1 = y0 + u2 * dy;
					}
					if (u1 > 0)
					{
						x0 = x0 + u1 * dx;
						y0 = y0 + u1 * dy;
					}

				}
			}
		}
	}
	else
	{
		//MessageBox(TEXT("111"));
		x0 = 0; y0 = 0;  x1 = 0; y1 = 0;
	}
	//	m.Format(TEXT("%f,%f,%f,%f"), x0,y0, x1, y1);
	//	MessageBox(m);
}
void CmyStudy2View::Ondirectecut()
{
	DirectLineClip();
	m_clip1 = true;
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}
/*多边形裁剪法*/
typedef enum
{
	Left, Right, Bottom, Top
}Boundary;
int Inside(WcPt2D p, Boundary b, WcPt2D wMin, WcPt2D wMax)
{
	switch (b)
	{
	case Left:
		if (p.x < wMin.x) return (false);
		break;
	case Right:
		if (p.x > wMax.x) return (false);
		break;
	case Bottom:
		if (p.y < wMin.y) return (false);
		break;
	case Top:
		if (p.y > wMax.y) return (false);
		break;
	}
	return true;
}
/*int Cross(WcPt2D p1, WcPt2D p2, Boundary b, WcPt2D wMin, WcPt2D wMax)
{
	if (Inside(p1, b, wMin, wMax) == Inside(p2, b, wMin, wMax))
		return (false);
	else
		return true;
}*/
WcPt2D Intersect(WcPt2D p1, WcPt2D p2, Boundary b, WcPt2D	wMin, WcPt2D wMax)
{
	WcPt2D iPt;
	float m;
	if (p1.x != p2.x) m = (p2.y - p1.y) / (p2.x - p1.x);
	switch (b) {
	case Left:
		iPt.x = wMin.x;
		iPt.y = p2.y + (wMin.x - p2.x)*m;
		break;
	case Right:
		iPt.x = wMax.x;
		iPt.y = p2.y + (wMax.x - p2.x)*m;
		break;
	case Bottom:
		iPt.y = wMin.y;
		if (p1.x != p2.x)iPt.x = p2.x + (wMin.y - p2.y) / m;
		else iPt.x = p2.x;
		break;
	case Top:
		iPt.y = wMax.y;
		if (p1.x != p2.x) iPt.x = p2.x + (wMax.y - p2.y) / m;
		else iPt.x = p2.x;
		break;
	}
	return iPt;
}
int edgeCliper(Boundary b, WcPt2D wMin, WcPt2D wMax, WcPt2D *pIn, int cnt, WcPt2D *pOut)
{
	WcPt2D s;
	int i, Outcnt = 0;
	s = pIn[0];
	for (i = 1; i <= cnt; i++)
	{
		if (!Inside(s, b, wMin, wMax) && Inside(pIn[i], b, wMin, wMax))
		{
			pOut[Outcnt] = Intersect(s, pIn[i], b, wMin, wMax);
			Outcnt++;
			pOut[Outcnt] = pIn[i];
			Outcnt++;
		}
		else if (Inside(s, b, wMin, wMax) && Inside(pIn[i], b, wMin, wMax))
		{
			pOut[Outcnt] = pIn[i];
			Outcnt++;
		}
		else if (Inside(s, b, wMin, wMax) && (!Inside(pIn[i], b, wMin, wMax)))
		{
			pOut[Outcnt] = Intersect(s, pIn[i], b, wMin, wMax);
			Outcnt++;
		}
		s = pIn[i];
	}
	return (Outcnt);
}
void  CmyStudy2View::ClipPolygonSuthHodg()
{


	WcPt2D wMin = { -200,0 }, wMax = { 50,200 };
	WcPt2D pOut[50 * 4], pIn[50 * 4];
	WcPt2D ppp[50] = { {0,0 } };
	int cnt = 49;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	int i, Outcnt, b;
	int R = 80, n = 50;
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(wMin.x, wMin.y);
	glVertex2f(wMin.x, wMax.y);
	glVertex2f(wMax.x, wMax.y);
	glVertex2f(wMax.x, wMin.y);
	glEnd();
	for (int i = 0; i < n; i++)
	{
		ppp[i] = { (float)(R*cos(2 * 3.1415926*i / n)), (float)(R*sin(2 * 3.1415926*i / n)) };
	}
	for (int i = 0; i < 4 * cnt; i++)
	{
		pIn[i].x = 0.0;
		pIn[i].y = 0.0;
		pOut[i].x = 0.0;
		pOut[i].y = 0.0;
	}
	for (int i = 0; i < n; i++)
	{
		pIn[i] = ppp[i];
	}
	glLineWidth(2.0);
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < cnt; i++)
		glVertex2f(pIn[i].x, pIn[i].y);
	glEnd();
	glLineWidth(2.0);
	for (int b = 0; b < 4; b++)
	{
		int Outcnt = edgeCliper(Boundary(b), wMin, wMax, pIn, cnt, pOut);
		for (int i = 0; i < Outcnt; i++)
			pIn[i] = pOut[i];
		pIn[Outcnt] = pOut[0];
		cnt = Outcnt;
	}
	glColor3f(0.0, 0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < cnt; i++)
		glVertex2f(pOut[i].x, pOut[i].y);
	glEnd();
	cnt = 49;
	for (int i = 0; i < n; i++)
	{
		ppp[i] = { (float)(R*cos(2 * 3.1415926*i / n)-150), (float)(R*sin(2 * 3.1415926*i / n)+100) };
	}
	for (int i = 0; i < 4 * cnt; i++)
	{
		pIn[i].x = 0.0;
		pIn[i].y = 0.0;
		pOut[i].x = 0.0;
		pOut[i].y = 0.0;
	}
	for (int i = 0; i < n; i++)
	{
		pIn[i] = ppp[i];
	}
	glLineWidth(2.0);
	glColor3f(1.0, 1.0, 0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < cnt; i++)
		glVertex2f(pIn[i].x, pIn[i].y);
	glEnd();
	glLineWidth(2.0);
	for (int b = 0; b < 4; b++)
	{
		int Outcnt = edgeCliper(Boundary(b), wMin, wMax, pIn, cnt, pOut);
		for (int i = 0; i < Outcnt; i++)
			pIn[i] = pOut[i];
		pIn[Outcnt] = pOut[0];
		cnt = Outcnt;
	}
	glColor3f(1.0, 0.6, 1.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < cnt; i++)
		glVertex2f(pOut[i].x, pOut[i].y);
	glEnd();

	glFlush();
	//MessageBox(TEXT("aaa"));
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);
}
/*圆形窗口裁剪直线*/
double PointToPoint(CPoint p1, CPoint p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
double PointToSegDist(CPoint P,CPoint A,CPoint B)
{
/*	double cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
	double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
	double r = cross / d2;
	double px = x1 + (x2 - x1) * r;
	double py = y1 + (y2 - y1) * r;
	return sqrt((x - px) * (x - px) + (py - y1) * (py - y1));*/
	double r = ((P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y)) / PointToPoint(A, B);
	if (r <= 0) return sqrt(PointToPoint(A, P));  //第一种情况, 返回AP的长
	else if (r >= 1) return sqrt(PointToPoint(B, P)); //第二种情况, 返回BP的长度
	else                           //第三种情况, 返回PC的长度
	{
		double AC = r * sqrt(PointToPoint(A, B));  //先求AC的长度,(AC=r*|AB|)
		return sqrt(PointToPoint(A, P) - AC * AC); //再勾股定理返回PC的长度
	}

}

CPoint ptInter1;
CPoint ptInter2;
void CmyStudy2View::CircleCut()
{
	x0 = lpoints[0].x; y0 = lpoints[0].y;
	x1 = lpoints[1].x; y1 = lpoints[1].y;
	CString m;
	CPoint pt;
	double dis = PointToSegDist(ypoints, lpoints[0], lpoints[1]);
	m.Format(TEXT("%f"), dis);
	//MessageBox(m);
	if (dis>=rad)
	{
		x0 = 0; y0 = 0;x1 = 0; y1 = 0;
		return ;
	}
	else
	{
		double d1 = PointToPoint(lpoints[0], ypoints);
		double d2 = PointToPoint(lpoints[1], ypoints);
		m.Format(TEXT("%f,%f"), d1,d2);
	//	MessageBox(m);
		if ( d1<= rad && d2<= rad)
		{
			return;
		}
		else 
		{
			if (d1 > rad && d2 > rad)
			{
				//求交点。赋新值；
				LineInterCircle(lpoints[0], lpoints[1], ypoints, 90000);
				x0 = ptInter1.x;
				y0 = ptInter1.y;
				x1 = ptInter2.x;
				y1 = ptInter2.y;
				
			//	m.Format(TEXT("%f,%f,%f,%f"), x0, y0, x1,y1);
				m.Format(TEXT("%f,%f,%f,%f"), ptInter1.x, ptInter1.y, ptInter2.x, ptInter2.y);
			//	MessageBox(m);
			//	lpoints[0] = ptInter1;
				//lpoints[1] = ptInter2;
				return;
			}
			else
			{
				LineInterCircle(lpoints[0], lpoints[1], ypoints, 90000);
				pt = ptInter1.x < ptInter2.x ? ptInter1 : ptInter2;
				if (d1 < d2)
				{
				//	lpoints[1] = pt;
					x0 = lpoints[0].x;
					y0 = lpoints[0].y;
					x1 = pt.x;
					y1 = pt.y;
					//p2=p3;p1=p1
				}
				else
				{
				//	lpoints[1] = pt;
					x1 = lpoints[1].x;
					y1 = lpoints[1].y;
					x0 = pt.x;
					y0 = pt.y;
					//lpoints[0] = pt;
					//p1=p3;p2=p2;
				}
			}
		}
	}
}
bool CmyStudy2View::LineInterCircle(CPoint ptStart, CPoint ptEnd, CPoint ptCenter, double Radius2)
	{

	// MessageBox(TEXT("执行我了么"));
	 ptInter1.x = ptInter2.x = 255360.0f;
	 ptInter1.y = ptInter2.y = 255360.0f;
		float fDis = sqrt((ptEnd.x - ptStart.x) * (ptEnd.x - ptStart.x) + (ptEnd.y - ptStart.y) * (ptEnd.y - ptStart.y));
		WcPt2D d;
		d.x = (ptEnd.x - ptStart.x) / fDis;
		d.y = (ptEnd.y - ptStart.y) / fDis;
		CPoint E;
		E.x = ptCenter.x - ptStart.x;
		E.y = ptCenter.y- ptStart.y;
		float a = E.x * d.x + E.y * d.y;
		float a2 = a * a;
		float e2 = E.x * E.x + E.y * E.y;

		if ((Radius2 - e2 + a2) < 0)

		{
			return false;

		}
		else
		{
			float f = (float)sqrt(Radius2 - e2 + a2);
			float t = a - f;
			if (((t - 0.0) > -EPS) && (t - fDis) < EPS)
			{
				ptInter1.x = ptStart.x + t * d.x;
				ptInter1.y = ptStart.y + t * d.y;
			}
			t = a + f;
			if (((t - 0.0) > -EPS) && (t - fDis) < EPS)
			{
				ptInter2.x = ptStart.x + t * d.x;
				ptInter2.y = ptStart.y + t * d.y;
			}
			return true;
		}

	}
void CmyStudy2View::Oncirclecut()
{

	CircleCut();
	m_clip2 = true;
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}



void CmyStudy2View::OnDraw(CDC* /*pDC*/)
{
	CmyStudy2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CDC *pDC = GetWindowDC();

	if (flag != 0)
	{
		//                                                                                                                                                raw3();
		
		if (flag != 5 && flag != 6&&flag!=7&&flag!=10&&flag!=11 && flag != 11 && flag != 12 && flag != 13 && flag != 14 && flag != 9)
		{
			draw();
		}
		if (flag != 5 && flag != 6 && flag != 7 && flag != 1&&flag!=2 && flag != 3 && flag != 4)
		{
			draw3();
		}
		

		if ((flag == 5 || flag == 6)&&isJuxing==true)
		{
			juxing();
			
		}
		if ((flag == 6  || flag == 7)&&isYuan==true)
		{
			yuanxing(pDC, ypoints.x, ypoints.y, rad, RGB(0, 0, 255));
			//MessageBox(TEXT("执行我了"));
		}
		if (!m_clip&&!m_clip1&&!m_clip2&&flag!=1&&flag!=2&&flag!=3&&flag!=4&&flag!=10 && flag != 11 && flag != 12 && flag != 13&&flag!=14)
		{
			DDALine(pDC, lpoints[0].x, lpoints[0].y, lpoints[1].x, lpoints[1].y, RGB(255, 0, 0));
			//MessageBox(TEXT("执行我了"));
		}
		if ((m_clip||m_clip1||m_clip2) && flag != 1 && flag != 2 && flag != 3 && flag != 4 && flag != 10 && flag != 11 && flag != 12 && flag != 13&&flag!=14)
		{
			DDALine(pDC, x0, y0, x1, y1, RGB(255, 0, 0));
			m_clip = false;
			m_clip1 = false;
			m_clip2 = false;
		}

	}
	//DDALine(pDC, 800, 500, 200, 100, RGB(255, 0, 0));
}
void CmyStudy2View::Onclear()
{
	flag = 0;
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}



void CmyStudy2View::OnCirclecutrectangle()
{
	ClipPolygonSuthHodg();
	
	//Invalidate(TRUE);
}


void CmyStudy2View::Onlogo()
{
	
}
/*设置一条龙*/
void CmyStudy2View::Oncolorselect()
{
	CColorDialog  colordlg(color);
	if (colordlg.DoModal() == IDOK)
	{
		color = colordlg.GetColor();
	}
	
	// TODO: 在此添加命令处理程序代码
}

void CmyStudy2View::OnLineweight()
{
	CdialogWeight dlg;
	if (dlg.DoModal() == IDOK)
	{

		weight = dlg.weight;
	}
	
	// TODO: 在此添加命令处理程序代码
}


/*logo一条龙*/
void CmyStudy2View::OnLogophoto()
{
	WcPt2D ppp[300];

	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1.0f);
	glColor4f(0.0, 0.0, 1.0, 0.6); //画笔梅红色
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);

	int R = 80, n = 50;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n / 2; i++)
	{
		ppp[i] = { (float)(R*cos(2 * 3.1415926*i / n)), (float)(R*sin(2 * 3.1415926*i / n)) };
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		ppp[i] = { (float)(R*cos(2 * 3.1415926*i / n)), (float)(R*sin(2 * 3.1415926*i / n) - 100) };
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(0.196, 0.804, 0.196, 0.6);


	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(0.804, 0.804, 0.0, 0.6);
	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(1.0, 1.0, 0.0, 0.6);
	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(1.0, 0.5, 0.0, 0.6);
	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(1.0, 0.0, 0.0, 0.6);
	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(0.627, 0.4, 0.827, 0.6);
	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	setIdentity(ini);
	rotate({ 0,100 }, 3.1415926 / 4.0);
	transform(50, ppp);
	glColor4f(0.627, 0.125, 0.941, 0.6);

	for (int i = 0; i < n / 2; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	for (int i = n / 2; i < n; i++)
	{
		glVertex2f(ppp[i].x, ppp[i].y);
	}
	glEnd();
	glDisable(GL_BLEND);
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);

	CBitmap bitmap;			//位图类对象
	bitmap.LoadBitmap(IDB_BITMAP1); //从资源中装载入位图
	CDC *pDC = GetWindowDC();
	CDC dcComp;			//创建CDC对象
	dcComp.CreateCompatibleDC(pDC);		//创建设备环境
	dcComp.SelectObject(&bitmap);			//选择位图对象

	BITMAP bmInfo;
	bitmap.GetObject(sizeof(bmInfo), &bmInfo);	//获取位图信息
	//将位图显示到视图中
	pDC->BitBlt(0, 0, bmInfo.bmWidth+200, bmInfo.bmHeight+200, &dcComp, 0, 0, SRCCOPY);
	

	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
}
void CmyStudy2View::OnLogofamily()
{
	WcPt2D pppp[5] = { {0,100},{-173.2,0},{-173.2,-200},{173.2,-200},{173.2,0} };
	WcPt2D ppppp[11] = { {0,125},{ 130 * 1.732,-5},{ 115 * 1.732,-5},
	{ 115 * 1.732,-225},{ -115 * 1.732,-225},{ -115 * 1.732,-5},{ -130 * 1.732,-5} };
	WcPt2D pppppp[4] = { { 100 * 1.732, 25}, { 100 * 1.732,80 }, { 115 * 1.732,80 }, { 115 * 1.732,10 } };
	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1.0f);
	glColor4f(238/255.0, 173/255.0, 14/255.0, 0.6); //画笔梅红色
	glBegin(GL_POLYGON);
	for (int i = 0; i < 11; i++)
	{

		glVertex2f(ppppp[i].x, ppppp[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{

		glVertex2f(pppppp[i].x, pppppp[i].y);
	}
	glEnd();
	glColor4f(1.0, 193 / 255.0, 37 / 255.0, 0.6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 5 ; i++)
	{
		
		glVertex2f(pppp[i].x, pppp[i].y);
	}
	glEnd();
	glColor4f(1.0, 215 / 255.0, 0.0, 0.6);
	glBegin(GL_POLYGON);
	setIdentity(ini);
	scale(0.8,0.8 , { 0,-100 });
	transform(5, pppp);
	for (int i = 0; i < 5; i++)
	{

		glVertex2f(pppp[i].x, pppp[i].y);
	}
	glEnd();
	glColor4f(1.0, 215 / 255.0, 0.0, 0.6);
	glBegin(GL_POLYGON);
	setIdentity(ini);
	scale(0.8, 0.8, { 0,-100 });
	transform(5, pppp);
	for (int i = 0; i < 5; i++)
	{

		glVertex2f(pppp[i].x, pppp[i].y);
	}
	glEnd();
	glColor4f(238/255.0, 225/255.0, 130/255.0, 0.6);

	glBegin(GL_POLYGON);
	setIdentity(ini);
	scale(0.95, 0.95, { 0,-100 });
	transform(5, pppp);
	for (int i = 0; i < 5; i++)
	{

		glVertex2f(pppp[i].x, pppp[i].y);
	}
	glEnd();
	glColor4f(1.0,236/255.0, 139/ 255.0, 0.6);
	glBegin(GL_POLYGON);
	setIdentity(ini);
	scale(0.8, 0.8, { 0,-100 });
	transform(5, pppp);
	for (int i = 0; i < 5; i++)
	{

		glVertex2f(pppp[i].x, pppp[i].y);
	}
	glEnd();
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);

	CBitmap bitmap;			//位图类对象
	bitmap.LoadBitmap(IDB_BITMAP2); //从资源中装载入位图
	CDC *pDC = GetWindowDC();
	CDC dcComp;			//创建CDC对象
	dcComp.CreateCompatibleDC(pDC);		//创建设备环境
	dcComp.SelectObject(&bitmap);			//选择位图对象

	BITMAP bmInfo;
	bitmap.GetObject(sizeof(bmInfo), &bmInfo);	//获取位图信息
	//将位图显示到视图中
	pDC->BitBlt(0, 0, bmInfo.bmWidth + 200, bmInfo.bmHeight + 200, &dcComp, 0, 0, SRCCOPY);
	// TODO: 在此添加命令处理程序代码
}       
void  CmyStudy2View::OnLogowarning()
{
	WcPt2D w[100];
	WcPt2D ww[100];
	WcPt2D www[100];
	WcPt2D l[2] = { {100,300},{1800,300} };
	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1.0f);
	int R = 50,R1=60,R2=70,n = 100;
	glBegin(GL_POLYGON);
	glColor4f(0.0, 0.749, 1.0, 0.0);
	for (int i = 0; i < n; i++)
	{
		www[i] = { (float)(R2*cos(2 * 3.1415926*i / n)), (float)(R2*sin(2 * 3.1415926*i / n)) };
		glVertex2f(www[i].x, www[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	for (int i = 0; i < n; i++)
	{
		ww[i] = { (float)(R1*cos(2 * 3.1415926*i / n)), (float)(R1*sin(2 * 3.1415926*i / n)) };
		glVertex2f(ww[i].x, ww[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor4f(0.0, 0.749, 1.0, 0.0);
	for (int i = 0; i < n ; i++)
	{
		w[i] = { (float)(R*cos(2 * 3.1415926*i / n)), (float)(R*sin(2 * 3.1415926*i / n)) };
		glVertex2f(w[i].x, w[i].y);
	}
	glEnd();
	setIdentity(ini);
	translate(0, 200);
	transform(100, w);
	transform(100, ww);
	transform(100, www);
	glBegin(GL_POLYGON);
	glColor4f(1.0, 0.756, 0.145, 0.0);
	for (int i = 0; i < n; i++)
	{
		
		glVertex2f(www[i].x, www[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	for (int i = 0; i < n; i++)
	{
		
		glVertex2f(ww[i].x, ww[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor4f(1.0, 0.756, 0.145, 0.0);
	for (int i = 0; i < n; i++)
	{
		
		glVertex2f(w[i].x, w[i].y);
	}
	glEnd();
	setIdentity(ini);
	translate(0,-400);
	transform(100, w);
	transform(100, ww);
	transform(100, www);
	glBegin(GL_POLYGON);
	glColor4f(0.462, 0.933, 0.0, 0.0);
	for (int i = 0; i < n; i++)
	{

		glVertex2f(www[i].x, www[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	for (int i = 0; i < n; i++)
	{

		glVertex2f(ww[i].x, ww[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor4f(0.462, 0.933, 0.0, 0.0);
	for (int i = 0; i < n; i++)
	{

		glVertex2f(w[i].x, w[i].y);
	}
	glEnd();
	glColor4f(0.745, 0.745, 0.745, 0.0); //画笔梅红色
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex2f(l[0].x,l[0].y);
	glVertex2f(l[1].x, l[1].y);
	glEnd();
	setIdentity(ini);
	translate(0, -200);
	transform(2, l);
	glBegin(GL_LINES);
	glVertex2f(l[0].x, l[0].y);
	glVertex2f(l[1].x, l[1].y);
	glEnd();
	setIdentity(ini);
	translate(0, -200);
	transform(2, l);
	glBegin(GL_LINES);
	glVertex2f(l[0].x, l[0].y);
	glVertex2f(l[1].x, l[1].y);
	glEnd();
	setIdentity(ini);
	translate(0, -200);
	transform(2, l);
	glBegin(GL_LINES);
	glVertex2f(l[0].x, l[0].y);
	glVertex2f(l[1].x, l[1].y);
	glEnd();
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);


	CBitmap bitmap;			//位图类对象
	bitmap.LoadBitmap(IDB_BITMAP3); //从资源中装载入位图
	CDC *pDC = GetWindowDC();
	CDC dcComp;			//创建CDC对象
	dcComp.CreateCompatibleDC(pDC);		//创建设备环境
	dcComp.SelectObject(&bitmap);			//选择位图对象

	BITMAP bmInfo;
	bitmap.GetObject(sizeof(bmInfo), &bmInfo);	//获取位图信息
	//将位图显示到视图中
	pDC->BitBlt(0, 0, bmInfo.bmWidth + 200, bmInfo.bmHeight + 200, &dcComp, 0, 0, SRCCOPY);
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
}

/*轴测图及其三视图*/
void  CmyStudy2View::draw3weiFunction()
{
	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0f);
	glColor3f(1.0, 0.0, 0.0);
	WcPt3D m3D[12] = { {0,0,0,1},{45 * 4,0,0,1},{45 * 4,37 * 4,0,1},{0,37 * 4,0,1},{0,37 * 4,45 * 4,1},{0,0,45 * 4,1},
	{12 * 4,0,45 * 4,1}, {30 * 4,0,14 * 4,1},{45 * 4,0,14 * 4,1},{45 * 4,37 * 4,14 * 4,1},{30 * 4,37 * 4,14 * 4,1},{12 * 4,37 * 4,45 * 4,1} };
	WcPt3D m3D1[12];
	WcPt3D m3D2[12];
	WcPt3D m3D3[12];

	for (int i = 0; i < 12; i++)
	{
		m3D1[i] = m3D[i];
		m3D2[i] = m3D[i];
		m3D3[i] = m3D[i];
	}
	setIdentity3D(ini3);
	zhu3D();
	transform3D(12, m3D);
	setIdentity3D(ini3);
	translate3D(250, 100, 0);
	transform3D(12, m3D);
	glBegin(GL_LINES);
	glVertex2f(m3D[0].x, m3D[0].y);
	glVertex2f(m3D[1].x, m3D[1].y);
	glVertex2f(m3D[1].x, m3D[1].y);
	glVertex2f(m3D[2].x, m3D[2].y);
	glVertex2f(m3D[2].x, m3D[2].y);
	glVertex2f(m3D[3].x, m3D[3].y);
	glVertex2f(m3D[3].x, m3D[3].y);
	glVertex2f(m3D[4].x, m3D[4].y);
	glVertex2f(m3D[4].x, m3D[4].y);
	glVertex2f(m3D[5].x, m3D[5].y);
	glVertex2f(m3D[5].x, m3D[5].y);
	glVertex2f(m3D[6].x, m3D[6].y);
	glVertex2f(m3D[6].x, m3D[6].y);
	glVertex2f(m3D[7].x, m3D[7].y);
	glVertex2f(m3D[7].x, m3D[7].y);
	glVertex2f(m3D[8].x, m3D[8].y);

	glVertex2f(m3D[8].x, m3D[8].y);
	glVertex2f(m3D[9].x, m3D[9].y);
	glVertex2f(m3D[9].x, m3D[9].y);
	glVertex2f(m3D[10].x, m3D[10].y);
	glVertex2f(m3D[10].x, m3D[10].y);
	glVertex2f(m3D[11].x, m3D[11].y);
	glVertex2f(m3D[11].x, m3D[11].y);
	glVertex2f(m3D[6].x, m3D[6].y);
	glVertex2f(m3D[2].x, m3D[2].y);
	glVertex2f(m3D[9].x, m3D[9].y);
	glVertex2f(m3D[1].x, m3D[1].y);
	glVertex2f(m3D[8].x, m3D[8].y);
	glVertex2f(m3D[4].x, m3D[4].y);
	glVertex2f(m3D[11].x, m3D[11].y);
	glVertex2f(m3D[0].x, m3D[0].y);
	glVertex2f(m3D[5].x, m3D[5].y);
	glVertex2f(m3D[0].x, m3D[0].y);
	glVertex2f(m3D[3].x, m3D[3].y);
	glVertex2f(m3D[7].x, m3D[7].y);
	glVertex2f(m3D[10].x, m3D[10].y);
	glEnd();

	setIdentity3D(ini3);
	ce3D();
	transform3D(12, m3D2);
	setIdentity3D(ini3);
	rotate3D(1, 3.1415926 / 2.0);
	transform3D(12, m3D2);
	setIdentity3D(ini3);
	translate3D(-550, -250, 0);
	transform3D(12, m3D2);
	glBegin(GL_LINES);
	glVertex2f(m3D2[0].x, m3D2[0].y);
	glVertex2f(m3D2[1].x, m3D2[1].y);
	glVertex2f(m3D2[1].x, m3D2[1].y);
	glVertex2f(m3D2[2].x, m3D2[2].y);
	glVertex2f(m3D2[2].x, m3D2[2].y);
	glVertex2f(m3D2[3].x, m3D2[3].y);
	glVertex2f(m3D2[3].x, m3D2[3].y);
	glVertex2f(m3D2[4].x, m3D2[4].y);
	glVertex2f(m3D2[4].x, m3D2[4].y);
	glVertex2f(m3D2[5].x, m3D2[5].y);
	glVertex2f(m3D2[5].x, m3D2[5].y);
	glVertex2f(m3D2[6].x, m3D2[6].y);
	glVertex2f(m3D2[6].x, m3D2[6].y);
	glVertex2f(m3D2[7].x, m3D2[7].y);
	glVertex2f(m3D2[7].x, m3D2[7].y);
	glVertex2f(m3D2[8].x, m3D2[8].y);

	glVertex2f(m3D2[8].x, m3D2[8].y);
	glVertex2f(m3D2[9].x, m3D2[9].y);
	glVertex2f(m3D2[9].x, m3D2[9].y);
	glVertex2f(m3D2[10].x, m3D2[10].y);
	glVertex2f(m3D2[10].x, m3D2[10].y);
	glVertex2f(m3D2[11].x, m3D2[11].y);
	glVertex2f(m3D2[11].x, m3D2[11].y);
	glVertex2f(m3D2[6].x, m3D2[6].y);
	glVertex2f(m3D2[2].x, m3D2[2].y);
	glVertex2f(m3D2[9].x, m3D2[9].y);
	glVertex2f(m3D2[1].x, m3D2[1].y);
	glVertex2f(m3D2[8].x, m3D2[8].y);
	glVertex2f(m3D2[4].x, m3D2[4].y);
	glVertex2f(m3D2[11].x, m3D2[11].y);
	glVertex2f(m3D2[0].x, m3D2[0].y);
	glVertex2f(m3D2[5].x, m3D2[5].y);
	glVertex2f(m3D2[0].x, m3D2[0].y);
	glVertex2f(m3D2[3].x, m3D2[3].y);
	glVertex2f(m3D2[7].x, m3D2[7].y);
	glVertex2f(m3D2[10].x, m3D2[10].y);
	glEnd();


	setIdentity3D(ini3);
	fu3D();
	transform3D(12, m3D3);
	setIdentity3D(ini3);
	rotate3D(0, 3.1415926 / 2.0);
	transform3D(12, m3D3);
	setIdentity3D(ini3);
	translate3D(250, -100, 0);
	transform3D(12, m3D3);
	glBegin(GL_LINES);
	glVertex2f(m3D3[0].x, m3D3[0].y);
	glVertex2f(m3D3[1].x, m3D3[1].y);
	glVertex2f(m3D3[1].x, m3D3[1].y);
	glVertex2f(m3D3[2].x, m3D3[2].y);
	glVertex2f(m3D3[2].x, m3D3[2].y);
	glVertex2f(m3D3[3].x, m3D3[3].y);
	glVertex2f(m3D3[3].x, m3D3[3].y);
	glVertex2f(m3D3[4].x, m3D3[4].y);
	glVertex2f(m3D3[4].x, m3D3[4].y);
	glVertex2f(m3D3[5].x, m3D3[5].y);
	glVertex2f(m3D3[5].x, m3D3[5].y);
	glVertex2f(m3D3[6].x, m3D3[6].y);
	glVertex2f(m3D3[6].x, m3D3[6].y);
	glVertex2f(m3D3[7].x, m3D3[7].y);
	glVertex2f(m3D3[7].x, m3D3[7].y);
	glVertex2f(m3D3[8].x, m3D3[8].y);

	glVertex2f(m3D3[8].x, m3D3[8].y);
	glVertex2f(m3D3[9].x, m3D3[9].y);
	glVertex2f(m3D3[9].x, m3D3[9].y);
	glVertex2f(m3D3[10].x, m3D3[10].y);
	glVertex2f(m3D3[10].x, m3D3[10].y);
	glVertex2f(m3D3[11].x, m3D3[11].y);
	glVertex2f(m3D3[11].x, m3D3[11].y);
	glVertex2f(m3D3[6].x, m3D3[6].y);
	glVertex2f(m3D3[2].x, m3D3[2].y);
	glVertex2f(m3D3[9].x, m3D3[9].y);
	glVertex2f(m3D3[1].x, m3D3[1].y);
	glVertex2f(m3D3[8].x, m3D3[8].y);
	glVertex2f(m3D3[4].x, m3D3[4].y);
	glVertex2f(m3D3[11].x, m3D3[11].y);
	glVertex2f(m3D3[0].x, m3D3[0].y);
	glVertex2f(m3D3[5].x, m3D3[5].y);
	glVertex2f(m3D3[0].x, m3D3[0].y);
	glVertex2f(m3D3[3].x, m3D3[3].y);
	glVertex2f(m3D3[7].x, m3D3[7].y);
	glVertex2f(m3D3[10].x, m3D3[10].y);
	glEnd();

	setIdentity3D(ini3);
	zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
	transform3D(12, m3D1);

	setIdentity3D(ini3);
	translate3D(-450, 200, 0);
	transform3D(12, m3D1);
	glLineStipple(2, 0x5555);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);


	glVertex2f(m3D1[0].x, m3D1[0].y);
	glVertex2f(m3D1[1].x, m3D1[1].y);
	glVertex2f(m3D1[0].x, m3D1[0].y);
	glVertex2f(m3D1[5].x, m3D1[5].y);

	glVertex2f(m3D1[0].x, m3D1[0].y);
	glVertex2f(m3D1[3].x, m3D1[3].y);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(m3D1[1].x, m3D1[1].y);
	glVertex2f(m3D1[2].x, m3D1[2].y);
	glVertex2f(m3D1[2].x, m3D1[2].y);
	glVertex2f(m3D1[3].x, m3D1[3].y);
	glVertex2f(m3D1[3].x, m3D1[3].y);
	glVertex2f(m3D1[4].x, m3D1[4].y);
	glVertex2f(m3D1[4].x, m3D1[4].y);
	glVertex2f(m3D1[5].x, m3D1[5].y);
	glVertex2f(m3D1[5].x, m3D1[5].y);
	glVertex2f(m3D1[6].x, m3D1[6].y);
	glVertex2f(m3D1[6].x, m3D1[6].y);
	glVertex2f(m3D1[7].x, m3D1[7].y);
	glVertex2f(m3D1[7].x, m3D1[7].y);
	glVertex2f(m3D1[8].x, m3D1[8].y);

	glVertex2f(m3D1[8].x, m3D1[8].y);
	glVertex2f(m3D1[9].x, m3D1[9].y);
	glVertex2f(m3D1[9].x, m3D1[9].y);
	glVertex2f(m3D1[10].x, m3D1[10].y);
	glVertex2f(m3D1[10].x, m3D1[10].y);
	glVertex2f(m3D1[11].x, m3D1[11].y);
	glVertex2f(m3D1[11].x, m3D1[11].y);
	glVertex2f(m3D1[6].x, m3D1[6].y);
	glVertex2f(m3D1[2].x, m3D1[2].y);
	glVertex2f(m3D1[9].x, m3D1[9].y);
	glVertex2f(m3D1[1].x, m3D1[1].y);
	glVertex2f(m3D1[8].x, m3D1[8].y);
	glVertex2f(m3D1[4].x, m3D1[4].y);
	glVertex2f(m3D1[11].x, m3D1[11].y);


	glVertex2f(m3D1[7].x, m3D1[7].y);
	glVertex2f(m3D1[10].x, m3D1[10].y);
	glEnd();
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);
}
void CmyStudy2View::Onveandzhucefu()
{

	draw3weiFunction();
	CDC *pDC = GetWindowDC();
	pDC->TextOut(100, 200, TEXT("轴测图"));
	pDC->TextOut(1000, 200, TEXT("主视图"));
	pDC->TextOut(1000, 600, TEXT("俯视图"));
	pDC->TextOut(100, 600, TEXT("侧视图"));
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
}

/*三维物体绘制，变换*/
bool test = true;
int caozuox = 0,caozuoy=0,caozuoz=10;
WcPt3D m3D1[12] = { {0,0,0,1},{45 * 4,0,0,1},{45 * 4,37 * 4,0,1},{0,37 * 4,0,1},{0,37 * 4,45 * 4,1},{0,0,45 * 4,1},
{12 * 4,0,45 * 4,1}, {30 * 4,0,14 * 4,1},{45 * 4,0,14 * 4,1},{45 * 4,37 * 4,14 * 4,1},{30 * 4,37 * 4,14 * 4,1},{12 * 4,37 * 4,45 * 4,1} };
WcPt3D m3D2[12]= { {0,0,0,1},{45 * 4,0,0,1},{45 * 4,37 * 4,0,1},{0,37 * 4,0,1},{0,37 * 4,45 * 4,1},{0,0,45 * 4,1},
{12 * 4,0,45 * 4,1}, {30 * 4,0,14 * 4,1},{45 * 4,0,14 * 4,1},{45 * 4,37 * 4,14 * 4,1},{30 * 4,37 * 4,14 * 4,1},{12 * 4,37 * 4,45 * 4,1} };
WcPt3D MX1[2] = { {1000,0,0,1},{-1000,0,0,1} };
WcPt3D MY1[2] = { {0,1000,0,1},{0,-1000,0,1} };
WcPt3D MZ1[2] = { {0,0,1000,1},{0,0,-1000,1} };
WcPt3D MX2[2] = { {1000,0,0,1},{-1000,0,0,1} };
WcPt3D MY2[2] = { {0,1000,0,1},{0,-1000,0,1} };
WcPt3D MZ2[2] = { {0,0,1000,1},{0,0,-1000,1} };
void CmyStudy2View::draw3()
{
	

	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2.0f);
	
	/*setIdentity3D(ini3);
	scale3D(2,2, 2);
	transform3D(12, m3D1);*/
	//MessageBox(TEXT(">.."));
	/*if (x == 1 || x == 2 || x == 0)
	{
		if (x == 0)
		{
			setIdentity3D(ini3);
			rotate3D(0, 3.1415926 / 2.0);
			transform3D(12, m3D1);
			caozuox++;
		}
		if (x == 1)
		{
			setIdentity3D(ini3);
			rotate3D(1, 3.1415926 / 2.0);
			transform3D(12, m3D1);
			caozuox++;
		}
		if (x == 2)
		{
			setIdentity3D(ini3);
			rotate3D(2, 3.1415926 / 2.0);
			transform3D(12, m3D1);
			caozuox++;
		}
	}*/
//	gluLookAt(0, 0,1 , 0, 0, 0, 1, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(5.0f);

	if (flag == 9)
	{
		setIdentity3D(ini3);
		translate3D(x, y, z33);
		x = 0;
		y = 0;
		z33 = 0;
		transform3D(12, m3D1);
		caozuox++;
	}
	if (flag == 11)
	{
		setIdentity3D(ini3);
		rotate3D(0, 3.1415956 / 2.0);
		transform3D(12, m3D1);
		caozuox++;
	}
	if (flag == 12)
	{
		setIdentity3D(ini3);
		rotate3D(1, 3.1415956 / 2.0);
		transform3D(12, m3D1);
		caozuox++;
	}
	if (flag == 13)
	{
		setIdentity3D(ini3);
		rotate3D(2, 3.1415956 / 2.0);
		transform3D(12, m3D1);
		caozuox++;
	}
	if (flag == 14)
	{
		setIdentity3D(ini3);
		scale3D(sx, sx, sx);
		sx = 1;
		transform3D(12, m3D1);
		caozuox++;
	}
	/*if (x == 3&&caozuoy<=5)
	{
	//	MessageBox(TEXT("."));
		setIdentity3D(ini3);
		scale3D(1.1, 1.1, 1.1);
		transform3D(12, m3D1);
		caozuox++;
		caozuoy++;
		if (caozuoy == 5)
		{
			caozuoy = 10;
		}
	}
	if (x == 3 && caozuoy >5)
	{
		setIdentity3D(ini3);
		scale3D(0.9, 0.9, 0.9);
		transform3D(12, m3D1);
		caozuox++;
		caozuoy--;
		if (caozuoy == 6)
		{
			caozuoy = 0;
		}
	}*/
	if (caozuox % 2 == 1)
	{
		for (int i = 0; i < 12; i++)
		{
			m3D2[i] = m3D1[i];
			
		}
		for (int i = 0; i < 2; i++)
		{
			MX2[i] = MX1[i];
			MY2[i] = MY1[i];
			MZ2[i] = MZ1[i];

		}
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0f);
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(2, MX1);
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(2, MY1);
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(2, MZ1);
	
	//	pDC->TextOut(1000, 200, TEXT("主视图"));
	//	pDC->TextOut(1000, 600, TEXT("俯视图"));
	//	pDC->TextOut(100, 600, TEXT("侧视图"));
		glBegin(GL_LINES);
		glVertex2f(MX1[0].x, MX1[0].y);
		glVertex2f(MX1[1].x, MX1[1].y);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(MY1[0].x, MY1[0].y);
		glVertex2f(MY1[1].x, MY1[1].y);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(MZ1[0].x, MZ1[0].y);
		glVertex2f(MZ1[1].x, MZ1[1].y);
		glEnd();
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(12, m3D1);
		//绘图
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(15 / 255.0, 126 / 255.0, 186 / 255.0,0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[2].x, m3D1[2].y, m3D1[2].z);
		glVertex3f(m3D1[3].x, m3D1[3].y, m3D1[3].z);
		glVertex3f(m3D1[4].x, m3D1[4].y, m3D1[4].z);
		glVertex3f(m3D1[11].x, m3D1[11].y, m3D1[11].z);
		glVertex3f(m3D1[10].x, m3D1[10].y, m3D1[10].z);
		glVertex3f(m3D1[9].x, m3D1[9].y, m3D1[9].z);
		glEnd();
		glColor4f(1, 140.0 / 255, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[1].x, m3D1[1].y, m3D1[1].z);
		glVertex3f(m3D1[0].x, m3D1[0].y, m3D1[0].z);
		glVertex3f(m3D1[5].x, m3D1[5].y, m3D1[5].z);
		glVertex3f(m3D1[6].x, m3D1[6].y, m3D1[6].z);
		glVertex3f(m3D1[7].x, m3D1[7].y, m3D1[7].z);
		glVertex3f(m3D1[8].x, m3D1[8].y, m3D1[8].z);
		glEnd();

		glColor4f(1.0, 1.0, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[0].x, m3D1[0].y, m3D1[0].z);
		glVertex3f(m3D1[1].x, m3D1[1].y, m3D1[1].z);
		glVertex3f(m3D1[2].x, m3D1[2].y, m3D1[2].z);
		glVertex3f(m3D1[3].x, m3D1[3].y, m3D1[3].z);
		glEnd();
		glColor4f(1.0, 0.0, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[0].x, m3D1[0].y, m3D1[0].z);
		glVertex3f(m3D1[3].x, m3D1[3].y, m3D1[3].z);
		glVertex3f(m3D1[4].x, m3D1[4].y, m3D1[4].z);
		glVertex3f(m3D1[5].x, m3D1[5].y, m3D1[5].z);
		glEnd();
		glColor4f(0.0, 1.0, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[4].x, m3D1[4].y, m3D1[4].z);
		glVertex3f(m3D1[5].x, m3D1[5].y, m3D1[5].z);
		glVertex3f(m3D1[6].x, m3D1[6].y, m3D1[6].z);
		glVertex3f(m3D1[11].x, m3D1[11].y, m3D1[11].z);
		glEnd();
		glColor4f(0.0, 0.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[6].x, m3D1[6].y, m3D1[6].z);
		glVertex3f(m3D1[7].x, m3D1[7].y, m3D1[7].z);
		glVertex3f(m3D1[10].x, m3D1[10].y, m3D1[10].z);
		glVertex3f(m3D1[11].x, m3D1[11].y, m3D1[11].z);
		glEnd();
		glColor4f(1.0, 0.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[7].x, m3D1[7].y, m3D1[7].z);
		glVertex3f(m3D1[8].x, m3D1[8].y, m3D1[8].z);
		glVertex3f(m3D1[9].x, m3D1[9].y, m3D1[9].z);
		glVertex3f(m3D1[10].x, m3D1[10].y, m3D1[10].z);
		glEnd();
		glColor4f(0.0, 1.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D1[1].x, m3D1[1].y, m3D1[1].z);
		glVertex3f(m3D1[2].x, m3D1[2].y, m3D1[2].z);
		glVertex3f(m3D1[9].x, m3D1[9].y, m3D1[9].z);
		glVertex3f(m3D1[8].x, m3D1[8].y, m3D1[8].z);
		glEnd();
		glDisable(GL_BLEND);
	}
	else
	{
//	MessageBox(TEXT("11"));
		for (int i = 0; i < 12; i++)
		{
			m3D1[i] = m3D2[i];
	
		}
		for (int i = 0; i < 2; i++)
		{
			MX1[i] = MX2[i];
			MY1[i] = MY2[i];
			MZ1[i] = MZ2[i];
		}
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(12, m3D2);

		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0f);
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(2, MX2);
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(2, MY2);
		setIdentity3D(ini3);
		zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
		transform3D(2, MZ2);
		glBegin(GL_LINES);
		glVertex2f(MX2[0].x, MX2[0].y);
		glVertex2f(MX2[1].x, MX2[1].y);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(MY2[0].x, MY2[0].y);
		glVertex2f(MY2[1].x, MY2[1].y);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(MZ2[0].x, MZ2[0].y);
		glVertex2f(MZ2[1].x, MZ2[1].y);
		glEnd();
		//绘图
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glColor4f(1.0, 1.0, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[0].x, m3D2[0].y, m3D2[0].z);
		glVertex3f(m3D2[1].x, m3D2[1].y, m3D2[1].z);
		glVertex3f(m3D2[2].x, m3D2[2].y, m3D2[2].z);
		glVertex3f(m3D2[3].x, m3D2[3].y, m3D2[3].z);
		glEnd();
		glColor4f(1.0, 0.0, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[0].x, m3D2[0].y, m3D2[0].z);
		glVertex3f(m3D2[3].x, m3D2[3].y, m3D2[3].z);
		glVertex3f(m3D2[4].x, m3D2[4].y, m3D2[4].z);
		glVertex3f(m3D2[5].x, m3D2[5].y, m3D2[5].z);
		glEnd();
		glColor4f(0.0, 1.0, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[4].x, m3D2[4].y, m3D2[4].z);
		glVertex3f(m3D2[5].x, m3D2[5].y, m3D2[5].z);
		glVertex3f(m3D2[6].x, m3D2[6].y, m3D2[6].z);
		glVertex3f(m3D2[11].x, m3D2[11].y, m3D2[11].z);
		glEnd();
		glColor4f(0.0, 0.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[6].x, m3D2[6].y, m3D2[6].z);
		glVertex3f(m3D2[7].x, m3D2[7].y, m3D2[7].z);
		glVertex3f(m3D2[10].x, m3D2[10].y, m3D2[10].z);
		glVertex3f(m3D2[11].x, m3D2[11].y, m3D2[11].z);
		glEnd();
		glColor4f(1.0, 0.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[7].x, m3D2[7].y, m3D2[7].z);
		glVertex3f(m3D2[8].x, m3D2[8].y, m3D2[8].z);
		glVertex3f(m3D2[9].x, m3D2[9].y, m3D2[9].z);
		glVertex3f(m3D2[10].x, m3D2[10].y, m3D2[10].z);
		glEnd();
		glColor4f(0.0, 1.0, 1.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[1].x, m3D2[1].y, m3D2[1].z);
		glVertex3f(m3D2[2].x, m3D2[2].y, m3D2[2].z);
		glVertex3f(m3D2[9].x, m3D2[9].y, m3D2[9].z);
		glVertex3f(m3D2[8].x, m3D2[8].y, m3D2[8].z);
		glEnd();
		glColor4f(15/255.0, 126/255.0, 186/255.0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[2].x, m3D2[2].y, m3D2[2].z);
		glVertex3f(m3D2[3].x, m3D2[3].y, m3D2[3].z);
		glVertex3f(m3D2[4].x, m3D2[4].y, m3D2[4].z);
		glVertex3f(m3D2[11].x, m3D2[11].y, m3D2[11].z);
		glVertex3f(m3D2[10].x, m3D2[10].y, m3D2[10].z);
		glVertex3f(m3D2[9].x, m3D2[9].y, m3D2[9].z);
		glEnd();
		glColor4f(1, 140.0 / 255, 0, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(m3D2[1].x, m3D2[1].y, m3D2[1].z);
		glVertex3f(m3D2[0].x, m3D2[0].y, m3D2[0].z);
		glVertex3f(m3D2[5].x, m3D2[5].y, m3D2[5].z);
		glVertex3f(m3D2[6].x, m3D2[6].y, m3D2[6].z);
		glVertex3f(m3D2[7].x, m3D2[7].y, m3D2[7].z);
		glVertex3f(m3D2[8].x, m3D2[8].y, m3D2[8].z);
		glEnd();
		glDisable(GL_BLEND);
		
	}

	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);


}
void CmyStudy2View::Ondraw3wei()
{
	flag = 10;
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}

void CmyStudy2View::Ontranslation3wei()
{
	flag = 9;
	//Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}

void CmyStudy2View::Onzidingyi()
{
	WcPt3D mid[8] = { {0,0,0,1}, {150, 0, 0,1},{150,0,200,1}, {0,0,200,1},{0,300,0,1},{0,300,200,1},{150,300,200,1},{150,300,0,1} };

	glDrawBuffer(GL_BACK);//指定在后台缓存中绘制
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0f);

	glColor3f(1.0, 0.0, 0.0);
	

	setIdentity3D(ini3);
	zhouce3D(-3.1415926 / 4.0, -3.1415925 / 4.0);
	transform3D(8, mid);
	
	setIdentity3D(ini3);
	translate3D(x33, y33, 0);
	x33 = 0;
	y33 = 0;
	transform3D(8, mid);
	CString m;
	m.Format(TEXT("%f"), mid[1].x);
	MessageBox(m);
	glBegin(GL_LINES);
	glVertex3f(mid[0].x, mid[0].y, mid[0].z);
	glVertex3f(mid[1].x, mid[1].y, mid[1].z);
	glVertex3f(mid[1].x, mid[1].y, mid[1].z);
	glVertex3f(mid[2].x, mid[2].y, mid[2].z);
	glVertex3f(mid[2].x, mid[2].y, mid[2].z);
	glVertex3f(mid[3].x, mid[3].y, mid[3].z);
	glVertex3f(mid[3].x, mid[3].y, mid[3].z);
	glVertex3f(mid[0].x, mid[0].y, mid[0].z);

	glVertex3f(mid[4].x, mid[4].y, mid[4].z);
	glVertex3f(mid[5].x, mid[5].y, mid[5].z);

	glVertex3f(mid[5].x, mid[5].y, mid[5].z);
	glVertex3f(mid[6].x, mid[6].y, mid[6].z);
	glVertex3f(mid[6].x, mid[6].y, mid[6].z);
	glVertex3f(mid[7].x, mid[7].y, mid[7].z);
	glVertex3f(mid[7].x, mid[7].y, mid[7].z);
	glVertex3f(mid[4].x, mid[4].y, mid[4].z);

	glVertex3f(mid[0].x, mid[0].y, mid[0].z);
	glVertex3f(mid[4].x, mid[4].y, mid[4].z);
	glVertex3f(mid[5].x, mid[5].y, mid[5].z);
	glVertex3f(mid[3].x, mid[3].y, mid[3].z);
	glVertex3f(mid[6].x, mid[6].y, mid[6].z);
	glVertex3f(mid[2].x, mid[2].y, mid[2].z);
	glVertex3f(mid[7].x, mid[7].y, mid[7].z);
	glVertex3f(mid[1].x, mid[1].y, mid[1].z);
	glEnd();
	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	SwapBuffers(wglGetCurrentDC());//交换前后缓存
	glDrawBuffer(GL_FRONT);
	// TODO: 在此添加命令处理程序代码
}




void CmyStudy2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnTimer(nIDEvent);
}


void CmyStudy2View::Onx()
{
	flag = 11;

	
}
void CmyStudy2View::Ony()
{
	flag = 12;

	
}
void CmyStudy2View::Onz()
{
	flag = 13;

}


void CmyStudy2View::Onscale3wei()
{
	flag = 14;
	
	// TODO: 在此添加命令处理程序代码
}
