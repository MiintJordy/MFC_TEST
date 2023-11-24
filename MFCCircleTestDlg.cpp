
// MFCCircleTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCCircleTest.h"
#include "MFCCircleTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCircleTestDlg 대화 상자



CMFCCircleTestDlg::CMFCCircleTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIRCLETEST_DIALOG, pParent)
	, m_nRadius(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCircleTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RAD, m_nRadius);
}

BEGIN_MESSAGE_MAP(CMFCCircleTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCCircleTestDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_FIND, &CMFCCircleTestDlg::OnBnClickedBtnFind)
	ON_BN_CLICKED(IDC_BTN_BORDER, &CMFCCircleTestDlg::OnBnClickedBtnBorder)
END_MESSAGE_MAP()


// CMFCCircleTestDlg 메시지 처리기

BOOL CMFCCircleTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 난수표 무작위로 고르게 초기화
	srand((unsigned int)(time(NULL)));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCCircleTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCCircleTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCCircleTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// C++ 입출력 라이브러리
#include <iostream>
// rand()를 사용하기 위한 라이브러리
#include <math.h>
// 콘솔 창
// #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
// 생성 클릭 시, 입력한 숫자를 반지름으로 한 랜덤 X, Y 좌표의 원 생성
void CMFCCircleTestDlg::OnBnClickedBtnDraw()
{
	m_image.Destroy();

	const int nWidth = 780;
	const int nHeight = 520;
	const int nBpp = 8;
	UpdateData(TRUE);
	// std::cout << m_nRadius << std::endl;
	UpdateData(false);
	if (1 < m_nRadius && m_nRadius <= 250) {
		DrawBackGround(nWidth, nHeight, nBpp);
		DrawCircle(nWidth, nHeight);
	}
	else {
		AfxMessageBox(_T("2 ~ 250 사이의 값을 입력해주세요."));
	}
}

// 생성된 원에 대한 X, Y 좌표 중심값 찾기
void CMFCCircleTestDlg::OnBnClickedBtnFind()
{
	if (m_nCheck == 1) 
	{
		const int nWidth = 780;
		const int nHeight = 520;
		int nPitch = m_image.GetPitch();

		int nSum_X = 0;
		int nSum_Y = 0;
		int nCount = 0;

		for (int j = 0; j <= nHeight; j++) {
			for (int i = 0; i <= nWidth; i++) {
				if (m_fm[j * nPitch + i] == m_nGray) {
					nSum_X += i;
					nSum_Y += j;
					nCount++;
				}
			}
		}
		int Center_X = (int)nSum_X / nCount;
		int Center_Y = (int)nSum_Y / nCount;

		m_nCenter_X = Center_X;
		m_nCenter_Y = Center_Y;

		std::cout << "Center_X :" << Center_X << std::endl;
		std::cout << "Center_Y :" << Center_Y << std::endl;

		CString X_Result, Y_Result;
		X_Result.Format(_T("%d"), Center_X);
		Y_Result.Format(_T("%d"), Center_Y);

		CEdit* X_Edit = (CEdit*)GetDlgItem(IDC_EDIT_CirCleX);
		CEdit* Y_Edit = (CEdit*)GetDlgItem(IDC_EDIT_CircleY);

		X_Edit->SetWindowText(X_Result);
		Y_Edit->SetWindowText(Y_Result);

		CClientDC dc(this);

		for (int i = Center_X - m_nRadius / 2; i <= Center_X + m_nRadius / 2; i++) {
			m_fm[Center_Y * nPitch + i] = 0;
		}

		for (int j = Center_Y - m_nRadius / 2; j <= Center_Y + m_nRadius / 2; j++) {
			m_fm[j * nPitch + Center_X] = 0;
		}

		m_image.Draw(dc, 0, 0);

		m_nCheck = 2;
		m_nCheck_Border = 0;
	}
	else if (m_nCheck == 2) {
		AfxMessageBox(_T("이미 중심이 표시되었습니다."));
	}
	else {
		AfxMessageBox(_T("원을 생성해주세요."));
	}

}

// 생성된 원에 대한 테두리 표시
void CMFCCircleTestDlg::OnBnClickedBtnBorder()
{
	if (m_nCheck == 2 && m_nCheck_Border == 0) {
		CClientDC dc(this);
		if (m_image) {
			CPen pen(PS_SOLID, 5, RGB(0, 255, 0));
			CPen* pOldPen = dc.SelectObject(&pen);

			int nRadiusBorder = m_nRadius;

			CRect rectBorder;
			rectBorder.SetRect(m_nCenter_X - nRadiusBorder, m_nCenter_Y - nRadiusBorder, m_nCenter_X + nRadiusBorder, m_nCenter_Y + nRadiusBorder);
			dc.Ellipse(rectBorder);

			dc.SelectObject(pOldPen);
			
			CBrush brush(RGB(m_nGray, m_nGray, m_nGray));
			CBrush* pOldBrush = dc.SelectObject(&brush);

			CRect rect;
			rect.SetRect(m_nCenter_X - m_nRadius, m_nCenter_Y - m_nRadius, m_nCenter_X + m_nRadius, m_nCenter_Y + m_nRadius);
			dc.SelectObject(GetStockObject(NULL_PEN));
			dc.Ellipse(rect);
			
			dc.SelectObject(pOldBrush);
			
			DrawCenterLine(&dc);
		}
		m_nCheck = 1;
		m_nCheck_Border = 1;
	}
	else if (m_nCheck_Border == 1) {
		AfxMessageBox(_T("이미 테두리가 생성되었습니다."));
	}
	else {
		AfxMessageBox(_T("중심을 찾아주세요."));
	}
}


// 원이 생성될 공간의 배경을 하얀색으로 지정
void CMFCCircleTestDlg::DrawBackGround(int nWidth, int nHeight, int nBpp)
{
	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	m_fm = (unsigned char*)m_image.GetBits();

	memset(m_fm, 0xff, nWidth*nHeight);

	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CMFCCircleTestDlg::DrawCircle(int nWidth, int nHeight)
{
	UpdateData(TRUE);
	// std::cout << m_nRadius << std::endl;
	UpdateData(false);

	// 반지름 크기는 X 좌표 최소값
	int nStart_X = m_nRadius;
	// nWidth - 반지름 크기 = X좌표 최대값
	int nEnd_X = nWidth - m_nRadius;
	// 반지름 크기는 Y좌표 최소값
	int nStart_Y = m_nRadius;
	// nHeight - 반지름 크기 = Y좌표 최대값
	int nEnd_Y = nHeight - m_nRadius;

	// 중심이 될 X, Y 좌표 생성
	int nRandom_X = (rand() % (nEnd_X - nStart_X + 1)) + nStart_X;
	int nRandom_Y = (rand() % (nEnd_Y - nStart_Y + 1)) + nStart_Y;

	std::cout << "nRandom_X :" << nRandom_X << std::endl;
	std::cout << "nRandom_Y :" << nRandom_Y << std::endl;

	int nPitch = m_image.GetPitch();

	for (int j = nRandom_Y - m_nRadius; j <= nRandom_Y + m_nRadius; j++) {
		for (int i = nRandom_X - m_nRadius; i <= nRandom_X + m_nRadius; i++) {
			if (InCircle(i, j, nRandom_X, nRandom_Y)) {
				m_fm[j * nPitch + i] = m_nGray;
			}
		}
	}

	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

	m_nCheck = 1;
}

bool CMFCCircleTestDlg::InCircle(int i, int j, int nRandom_X, int nRandom_Y)
{
	bool bRet = false;

	double dX = i - nRandom_X;
	double dY = j - nRandom_Y;
	double dDist = dX * dX + dY * dY;

	if (dDist < m_nRadius * m_nRadius) {
		bRet = true;
	}
	return bRet;
}

void CMFCCircleTestDlg::DrawCenterLine(CClientDC* CDC)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = CDC -> SelectObject(&pen);

	CPoint nStart_X(m_nCenter_X - m_nRadius / 2, m_nCenter_Y);
	CPoint nEnd_X(m_nCenter_X + m_nRadius / 2, m_nCenter_Y);
	CPoint nStart_Y(m_nCenter_X, m_nCenter_Y - m_nRadius / 2);
	CPoint nEnd_Y(m_nCenter_X, m_nCenter_Y + m_nRadius / 2);

	CDC -> MoveTo(nStart_X);
	CDC -> LineTo(nEnd_X);
	CDC -> MoveTo(nStart_Y);
	CDC -> LineTo(nEnd_Y);

	CDC -> SelectObject(pOldPen);
}