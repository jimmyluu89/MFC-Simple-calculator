
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include <sstream>
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "MainLogic.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorDlg dialog


class MainLogic;
CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Display, output);
	DDX_Control(pDX, IDC_Display, m_output);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON1_ADD, &CCalculatorDlg::OnBnClickedButton1Add)
	ON_BN_CLICKED(IDC_BUTTON1_EQUAL, &CCalculatorDlg::OnBnClickedButton1Equal)
	ON_BN_CLICKED(IDC_BUTTON1_SUB, &CCalculatorDlg::OnBnClickedButton1Sub)
	ON_BN_CLICKED(IDC_BUTTON1_TIME, &CCalculatorDlg::OnBnClickedButton1Time)
	ON_BN_CLICKED(IDC_BUTTON1_DIVIDE, &CCalculatorDlg::OnBnClickedButton1Divide)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	SetWindowLong(this->m_hWnd, GWL_STYLE, GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Font.CreateFont(32, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));

	m_output.SetFont(&m_Font);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::outputReset()  //Reset the display to 0 and clear all the value stored.
{
	UpdateData();
	m_logic.Reset();
	output = (L"0");
	firstNum = false;
	opr = false;
	oprPlusUse = false;
	oprSubUse = false;
	oprMulUse = false;
	oprDivUse = false;
	UpdateData(false);
}

void CCalculatorDlg::doInput(std::string digit)
{
		if (output == "0") {   //If the first digit is 0, it will only display 0 and doesn't take anymore input.
			output = digit.c_str();
		}
		else if (opr == true) {  //After any of the operators hit, the output will be clear and display a new input numbers;
			output = digit.c_str();
			
		}
		else {   //taking input and display all the numbers.
			output += digit.c_str();
		}
		opr = false;
	UpdateData(false);   //This to put the values in the variables to the control buttons.
}

void CCalculatorDlg::doOperation(char input)
{
	if (input == '+') {
		if (firstNum == false && oprPlusUse == false) {    //If plus operator hit, it will take the first number and store it to the first value in MainLogic class.	
			num1 = _wtof(output);
			m_logic.SetValue(num1);
			curNum = m_logic.GetValue();
			output.Format(_T("%g"),curNum);
			opr = true;
			oprPlusUse = true;
			firstNum = true;        //Check if the first number have been store or not. if not, store the first input number.
		}
		else if (firstNum == true && oprSubUse == true && oprPlusUse == false) {
			num2 = _wtof(output);
			m_logic.SetNewSubValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprPlusUse = true;
			oprSubUse = false;
		}
		else if (firstNum == true && oprMulUse == true && oprPlusUse == false) {
			num2 = _wtof(output);
			m_logic.SetNewMulValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprMulUse = false;
			oprPlusUse = true;

		}
		else if (firstNum == true && oprDivUse == true && oprPlusUse == false) {
			num2 = _wtof(output);
			if (num2 == 0) {
				AfxMessageBox(_T("Error: Can't divide 0."));
				curNum = m_logic.GetValue();
				output.Format(_T("%g"), curNum);
				opr = true;
				oprPlusUse = false;
				oprDivUse = true;
			}
			else {
				m_logic.SetNewDivValue(num2);
				curNum = m_logic.GetResult();
				output.Format(_T("%g"), curNum);
				opr = true;
				oprPlusUse = true;
				oprDivUse = false;
			}
		}
		else if(firstNum == true && oprSubUse == false && oprMulUse == false && oprDivUse == false && oprPlusUse == true) {                      //If first number already input, this is take the next numbers and add them up.
			num2 = _wtof(output);
			m_logic.SetNewAddValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprPlusUse = true;          //Check if the '+' have been use or not.
		}
	}	
	else if (input == '-') {
		if (firstNum == false && oprSubUse == false) {    //If plus operator hit, it will take the first number and store it to the first value in MainLogic class.	
			num1 = _wtof(output);
			m_logic.SetValue(num1);
			curNum = m_logic.GetValue();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprSubUse = true;
			firstNum = true;        //Check if the first number have been store or not. if not, store the first input number.
		}
		else if (firstNum == true && oprPlusUse == true && oprSubUse == false) {
			num2 = _wtof(output);
			m_logic.SetNewAddValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprSubUse = true;
			oprPlusUse = false;
			
		}
		else if (firstNum == true && oprMulUse == true && oprSubUse == false) {
			num2 = _wtof(output);
			m_logic.SetNewSubValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprSubUse = true;
			oprMulUse = false;

		}
		else if (firstNum == true && oprDivUse == true && oprSubUse == false) {
			num2 = _wtof(output);
			if (num2 == 0) {
				AfxMessageBox(_T("Error: Can't divide 0."));
				curNum = m_logic.GetValue();
				output.Format(_T("%g"), curNum);
				opr = true;
				oprSubUse = false;
				oprDivUse = true;
			}
			else {
				m_logic.SetNewDivValue(num2);
				curNum = m_logic.GetResult();
				output.Format(_T("%g"), curNum);
				opr = true;
				oprSubUse = true;
				oprDivUse = false;
			}
		}
		else if(firstNum == true && oprPlusUse == false && oprSubUse == true) {                      //If first number already input, this is take the next numbers and add them up.
			num2 = _wtof(output);
			m_logic.SetNewSubValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprSubUse = true;          //Check if the '+' have been use or not.
		}
	}
	else if (input == '*') {
		if (firstNum == false && oprMulUse == false) {    //If multiply operator hit, it will take the first number and store it to the first value in MainLogic class.	
			num1 = _wtof(output);
			m_logic.SetValue(num1);
			curNum = m_logic.GetValue();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprMulUse = true;
			firstNum = true;        //Check if the first number have been store or not. if not, store the first input number.
		}
		else if (firstNum == true && oprPlusUse == true && oprMulUse == false) {
			num2 = _wtof(output);
			m_logic.SetNewAddValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprMulUse = true;
			oprPlusUse = false;

		}
		else if (firstNum == true && oprSubUse == true && oprMulUse == false) {
			num2 = _wtof(output);
			m_logic.SetNewSubValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprMulUse = true;
			oprSubUse = false;

		}
		else if (firstNum == true && oprDivUse == true && oprMulUse == false) {
			num2 = _wtof(output);
			if (num2 == 0) {
				AfxMessageBox(_T("Error: Can't divide 0."));
				curNum = m_logic.GetValue();
				output.Format(_T("%g"), curNum);
				opr = true;
				oprMulUse = false;
				oprDivUse = true;
			}
			else {
				m_logic.SetNewDivValue(num2);
				curNum = m_logic.GetResult();
				output.Format(_T("%g"), curNum);
				opr = true;
				oprMulUse = true;
				oprDivUse = false;
			}
		}
		else if (firstNum == true && oprPlusUse == false && oprSubUse == false && oprDivUse == false && oprMulUse == true) {                      //If first number already input, this is take the next numbers and multiply them up.
			num2 = _wtof(output);
			m_logic.SetNewMulValue(num2);
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprMulUse = true;          //Check if the '*' have been use or not.
		}
	}
	else if (input == '/') {
	if (firstNum == false && oprDivUse == false) {    //If multiply operator hit, it will take the first number and store it to the first value in MainLogic class.	
		num1 = _wtof(output);
		m_logic.SetValue(num1);
		curNum = m_logic.GetValue();
		output.Format(_T("%g"), curNum);
		opr = true;
		oprDivUse = true;
		firstNum = true;        //Check if the first number have been store or not. if not, store the first input number.
	}
	else if (firstNum == true && oprPlusUse == true && oprDivUse == false) {
		num2 = _wtof(output);
		m_logic.SetNewAddValue(num2);
		curNum = m_logic.GetResult();
		output.Format(_T("%g"), curNum);
		opr = true;
		oprPlusUse = false;
		oprDivUse = true;

	}
	else if (firstNum == true && oprSubUse == true && oprDivUse == false) {
		num2 = _wtof(output);
		m_logic.SetNewSubValue(num2);
		curNum = m_logic.GetResult();
		output.Format(_T("%g"), curNum);
		opr = true;
		oprSubUse = false;
		oprDivUse = true;

	}
	else if (firstNum == true && oprMulUse == true && oprDivUse == false) {
		num2 = _wtof(output);
		m_logic.SetNewMulValue(num2);
		curNum = m_logic.GetResult();
		output.Format(_T("%g"), curNum);
		opr = true;
		oprMulUse = false;
		oprDivUse = true;

	}
	else if (firstNum == true && oprPlusUse == false && oprSubUse == false && oprMulUse == false && oprDivUse == true) {                      //If first number already input, this is take the next numbers and multiply them up.
		num2 = _wtof(output);
		m_logic.SetNewDivValue(num2);
		m_logic.isNumZero();
		if (m_logic.isNumZero() == true) {
			AfxMessageBox(_T("Error: Can't divide 0."));
			curNum = m_logic.GetValue();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprDivUse = true;
		}
		else {
			curNum = m_logic.GetResult();
			output.Format(_T("%g"), curNum);
			opr = true;
			oprDivUse = true;          //Check if the '*' have been use or not.	
		}
	}
	}
	UpdateData(false);
}

void CCalculatorDlg::OnBnClickedButton1Add()
{
	// TODO: Add your control notification handler code here
	operators = '+';
	doOperation(operators);
}

void CCalculatorDlg::OnBnClickedButton1Sub()
{
	// TODO: Add your control notification handler code here
	operators = '-';
	doOperation(operators);
}

void CCalculatorDlg::OnBnClickedButton1Time()
{
	// TODO: Add your control notification handler code here
	operators = '*';
	doOperation(operators);
}

void CCalculatorDlg::OnBnClickedButton1Divide()
{
	// TODO: Add your control notification handler code here
	operators = '/';
	doOperation(operators);
}

void CCalculatorDlg::OnBnClickedButton1Equal()
{
	// TODO: Add your control notification handler code here
	if (operators == '+') {               //If the + operator hit, the equal will calculate the sum.
		if (firstNum == false) {   //If there are no operators hit or haven't take first number, the equal do nothing.
			return;
		}
		else{                     //calculate the sum of the last input number with the first number.
			num3 = _wtof(output);
			m_logic.Add(num3);
			m_result = m_logic.GetResult();
			output.Format(_T("%.f"), m_result);
			firstNum = false;     //Reset the first number after equal. So now, the result will be store as first number if user hit '+'
			oprEqualUse = true;   //Check if the '=' have been use or not.
			oprPlusUse = false;
			opr = true;
		}
	}
	else if (operators == '-') {               //If the + operator hit, the equal will calculate the sum.
		if (firstNum == false) {   //If there are no operators hit or haven't take first number, the equal do nothing.
			return;
		}
		else {                     //calculate the sum of the last input number with the first number.
			num3 = _wtof(output);
			m_logic.Sub(num3);
			m_result = m_logic.GetResult();
			output.Format(_T("%.f"), m_result);
			firstNum = false;     //Reset the first number after equal. So now, the result will be store as first number if user hit '+'
			oprEqualUse = true;   //Check if the '=' have been use or not.
			oprSubUse = false;
			opr = true;
		}
	}
	else if (operators == '*') {               //If the + operator hit, the equal will calculate the sum.
		if (firstNum == false) {   //If there are no operators hit or haven't take first number, the equal do nothing.
			return;
		}
		else {                     //calculate the sum of the last input number with the first number.
			num3 = _wtof(output);
			m_logic.Mul(num3);
			m_result = m_logic.GetResult();
			output.Format(_T("%.f"), m_result);
			firstNum = false;     //Reset the first number after equal. So now, the result will be store as first number if user hit '+'
			oprEqualUse = true;   //Check if the '=' have been use or not.
			oprMulUse = false;
			opr = true;
		}
	}
	else if (operators == '/') {               //If the + operator hit, the equal will calculate the sum.
		if (firstNum == false) {   //If there are no operators hit or haven't take first number, the equal do nothing.
			return;
		}
		else {                     //calculate the sum of the last input number with the first number.
			num3 = _wtof(output);
			if (num3 == 0) {
				AfxMessageBox(_T("Error: Can't divide 0."));
				outputReset();
			}
			else {
				m_logic.Div(num3);
				m_result = m_logic.GetResult();
				output.Format(_T("%g"), m_result);
				firstNum = false;     //Reset the first number after equal. So now, the result will be store as first number if user hit '+'
				oprEqualUse = true;   //Check if the '=' have been use or not.
				oprDivUse = false;
				opr = true;
			}
		}
	}
	UpdateData(false);
}

void CCalculatorDlg::OnBnClickedButton0()
{
	// TODO: Add your control notification handler code here
	doInput("0");
}

void CCalculatorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	doInput("1");
}


void CCalculatorDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	doInput("2");
}


void CCalculatorDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	doInput("3");
}


void CCalculatorDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	doInput("4");
}


void CCalculatorDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	doInput("5");
}


void CCalculatorDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	doInput("6");
}


void CCalculatorDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	doInput("7");
}


void CCalculatorDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	doInput("8");
}


void CCalculatorDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	doInput("9");
}


void CCalculatorDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	outputReset();
}
