
// MFCCircleTestDlg.h: 헤더 파일
//

#pragma once


// CMFCCircleTestDlg 대화 상자
class CMFCCircleTestDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;
	
public:
	CMFCCircleTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIRCLETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Edit에 입력한 반지름 값(기본 값 10)
	int m_nRadius;
	// 픽셀 주소
	unsigned char* m_fm;
	// 원 색상
	const int m_nGray = 150;
    // 원의 중심 위치
	int m_nCenter_X = 0;
	int m_nCenter_Y = 0;
	// 기능 중복 실행 확인
	int m_nCheck = 0;
	// 테두리 그리기 실행 확인
	int m_nCheck_Border = 0;
	// 배경 + 원 그리기 함수
	afx_msg void OnBnClickedBtnDraw();
	// 그린 원의 중심을 출력
	afx_msg void OnBnClickedBtnFind();
	// 그린 원의 테두리를 표시
	afx_msg void OnBnClickedBtnBorder();
	// 원을 그려질 공간의 배경을 하얗게 변경
	void DrawBackGround(int nWidth, int nHeight, int nBpp);
	// 원 중심 그리기
	void DrawCircle(int nWidth, int nHeight);
	// 원 안에 속하는 경우
	bool InCircle(int i, int j, int nRandom_X, int nRandom_Y);
	// 중심선 그리기
	void DrawCenterLine(CClientDC *CDC);
};
