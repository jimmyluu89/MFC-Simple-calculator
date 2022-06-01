#include <string>
#include "pch.h"
#include "MainLogic.h"


void MainLogic::SetValue(double value) {   //Taking the first input number and store it here.
	_value = value;
}

double MainLogic::GetValue() {
	return _value;;
}


void MainLogic::SetNewAddValue(double value2) {  //Taking the next input number and store it here. Then add it with the first number.
	m_value = value2;
	Add(m_value);
}

double MainLogic::GetNewAddValue() {
	return m_value;
}


void MainLogic::SetNewSubValue(double value3) {
	m_value = value3;
	Sub(m_value);
}

double MainLogic::GetNewSubValue() {
	return m_value;
}


void MainLogic::SetNewMulValue(double value4) {
	m_value = value4;
	Mul(m_value);
}

double MainLogic::GetNewMulValue() {
	return m_value;
}


void MainLogic::SetNewDivValue(double value5) {
	m_value = value5;
	Div(m_value);
}

double MainLogic::GetNewDivValue() {
	return m_value;
}


void MainLogic::Add(double newValue) {
	equal = _value + newValue;
	_value = equal;          //The result will always become the first number.
}

void MainLogic::Sub(double newValue2) {
	equal = _value - newValue2;
	_value = equal;
}

void MainLogic::Mul(double newValue3) {
	equal = _value * newValue3;
	_value = equal;
}

void MainLogic::Div(double newValue4) {
	equal = _value / newValue4;
	_value = equal;
}


double MainLogic::GetResult() {
	return equal;
}

void MainLogic::Reset() {   //Reset all value back to 0 when the clear button hit.
	_value = 0.0;
	m_value = 0.0;
	equal = 0.0;
}

bool MainLogic::isNumZero() {
	GetNewDivValue();
	if (m_value == 0) {
		return true;
	}
	else {
		return false;
	}
}