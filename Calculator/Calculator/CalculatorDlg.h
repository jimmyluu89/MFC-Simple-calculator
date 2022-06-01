
// CalculatorDlg.h : header file
//

#pragma once
#include "MainLogic.h"

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	MainLogic m_logic;

	CString output;
	char operators;
	double num1, num2, num3;
	double m_result;
	double curNum;

	void doInput(std::string digit);
	void doOperation(char input);
	void outputReset();

	bool opr = false;
	bool oprEqualUse = false;
	bool oprPlusUse = false;
	bool oprSubUse = false;
	bool oprMulUse = false;
	bool oprDivUse = false;
	bool firstNum = false;

	CFont m_Font;
	CEdit m_output;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButton1Add();
	afx_msg void OnBnClickedButton1Equal();
	afx_msg void OnBnClickedButton1Sub();
	afx_msg void OnBnClickedButton1Time();
	afx_msg void OnBnClickedButton1Divide();
};
