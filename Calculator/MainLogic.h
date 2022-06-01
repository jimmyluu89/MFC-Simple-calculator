#pragma once
#include <list>
#include <string>
#include <iostream>
#include <afxstr.h>

class MainLogic
{
public:
	void SetValue(double value);
	void SetNewAddValue(double value2);
	void SetNewSubValue(double value3);
	void SetNewMulValue(double value4);
	void SetNewDivValue(double value5);

	double GetValue();
	double GetNewAddValue();
	double GetNewSubValue();
	double GetNewMulValue();
	double GetNewDivValue();

	void Add(double newValue);
	void Sub(double newValue2);
	void Mul(double newValue3);
	void Div(double newValue4);

	double GetResult();

	void Reset();
	bool isNumZero();
private:
	double _value = 0.0;
	double m_value = 0.0;
	double equal = 0.0;
};
