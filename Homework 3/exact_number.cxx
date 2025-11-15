//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Homework 3
// Due Date: November 14, 2025
//
// Description: This program implements the ExactNumber class, 
// which represents rational numbers (fractions) with exact precision, 
// avoiding the rounding errors inherent in floating-point arithmetic.
//
// Acknowledgement:
// 1. Consulted with students in Sunlab
// 2. Utilized copilot to help with assisting with directory to compile and run the exe file 
// 3. Utilized copilot to help with comments
// 4. Utilized copilot to help with indentation
// 5. Utilized stack overflow to understand why it wasnt compiling/creating an exe file
//---------------------------------------------------------------------

#include "exact_number.h"

#include <ostream>
#include <limits>

// Helper to normalize sign so that denominator is non-negative
static inline void normalize_sign(int &n, int &d)
{
	if (d < 0) {
		n = -n;
		d = -d;
	}
}

// Constructors
ExactNumber::ExactNumber() : numer(0), denom(1) {}

ExactNumber::ExactNumber(int n, int d) : numer(n), denom(d)
{
	// Handle division by zero - represent as infinity
	if (denom == 0) {
		if (numer == 0) {
			// 0/0 is indeterminate, treat as 0/1
			numer = 0;
			denom = 1;
		} else {
			// Canonicalize to +/-1/0
			numer = (numer < 0) ? -1 : 1;
			denom = 0;
		}
	} else {
		normalize_sign(numer, denom);
		simplify();
	}
}

ExactNumber::ExactNumber(const ExactNumber& n) : numer(n.numer), denom(n.denom) {}

ExactNumber::~ExactNumber() {}

// Assignment
ExactNumber& ExactNumber::operator=(const ExactNumber& rhs)
{
	if (this != &rhs) {
		numer = rhs.numer;
		denom = rhs.denom;
	}
	return *this;
}

// Arithmetic compound operators
ExactNumber& ExactNumber::operator+=(const ExactNumber& rhs)
{
	// Handle infinities
	if (denom == 0 || rhs.denom == 0) {
		if (denom == 0 && rhs.denom == 0) {
			// inf + inf: if same sign, keep it; if different, undefined -> 0
			if (numer == rhs.numer) {
				return *this;
			} else {
				numer = 0;
				denom = 1;
				return *this;
			}
		}
		// One is infinite
		if (denom == 0) {
			return *this; // inf + finite = inf
		}
		// rhs is infinite
		*this = rhs;
		return *this;
	}

	// a/b + c/d = (ad + bc) / bd
	long long a = numer, b = denom, c = rhs.numer, d = rhs.denom;
	numer = static_cast<int>(a * d + b * c);
	denom = static_cast<int>(b * d);
	simplify();
	normalize_sign(numer, denom);
	return *this;
}

ExactNumber& ExactNumber::operator-=(const ExactNumber& rhs)
{
	// Handle infinities
	if (denom == 0 || rhs.denom == 0) {
		if (denom == 0 && rhs.denom == 0) {
			// inf - inf: if same sign -> 0, if different -> keep current
			if (numer == rhs.numer) {
				numer = 0;
				denom = 1;
				return *this;
			} else {
				return *this;
			}
		}
		if (denom == 0) {
			return *this; // inf - finite = inf
		}
		// finite - inf = -inf (flip sign of rhs)
		numer = -rhs.numer;
		denom = 0;
		return *this;
	}

	// a/b - c/d = (ad - bc) / bd
	long long a = numer, b = denom, c = rhs.numer, d = rhs.denom;
	numer = static_cast<int>(a * d - b * c);
	denom = static_cast<int>(b * d);
	simplify();
	normalize_sign(numer, denom);
	return *this;
}

ExactNumber& ExactNumber::operator*=(const ExactNumber& rhs)
{
	// Handle zero cases first
	if ((denom != 0 && numer == 0) || (rhs.denom != 0 && rhs.numer == 0)) {
		numer = 0;
		denom = 1;
		return *this;
	}

	// inf * 0 or 0 * inf is indeterminate; treat as 0
	if ((denom == 0 && rhs.numer == 0 && rhs.denom != 0) || 
	    (rhs.denom == 0 && numer == 0 && denom != 0)) {
		numer = 0;
		denom = 1;
		return *this;
	}

	// Handle infinities: inf * non-zero -> +/-inf
	if (denom == 0 || rhs.denom == 0) {
		int sign = 1;
		if (numer < 0) sign = -sign;
		if (rhs.numer < 0) sign = -sign;
		numer = (sign > 0) ? 1 : -1;
		denom = 0;
		return *this;
	}

	// Regular multiplication
	long long a = numer, b = denom, c = rhs.numer, d = rhs.denom;
	numer = static_cast<int>(a * c);
	denom = static_cast<int>(b * d);
	simplify();
	normalize_sign(numer, denom);
	return *this;
}

ExactNumber& ExactNumber::operator/=(const ExactNumber& rhs)
{
	// Division by zero (rhs == 0) -> infinity with proper sign
	if (rhs.denom != 0 && rhs.numer == 0) {
		if (numer == 0 && denom != 0) {
			// 0/0 is indeterminate
			numer = 0;
			denom = 1;
		} else {
			// n/0 -> +/- infinity
			int sign = (numer < 0) ? -1 : 1;
			numer = sign;
			denom = 0;
		}
		return *this;
	}

	// inf / finite non-zero -> inf with adjusted sign
	if (denom == 0 && rhs.denom != 0 && rhs.numer != 0) {
		int sign = (rhs.numer < 0) ? -1 : 1;
		numer = (numer * sign > 0) ? 1 : -1;
		denom = 0;
		return *this;
	}

	// finite / inf -> 0
	if (rhs.denom == 0) {
		numer = 0;
		denom = 1;
		return *this;
	}

	// inf / inf is indeterminate
	if (denom == 0 && rhs.denom == 0) 
    {
		numer = 0;
		denom = 1;
		return *this;
	}

	// a/b ÷ c/d = a/b * d/c = ad / bc
	long long a = numer, b = denom, c = rhs.numer, d = rhs.denom;
	numer = static_cast<int>(a * d);
	denom = static_cast<int>(b * c);

	if (denom == 0) 
    {
		// Result is infinity
		if (numer == 0) 
        {
			numer = 0;
			denom = 1;
		} else {
			numer = (numer < 0) ? -1 : 1;
		}
		return *this;
	}

	simplify();
	normalize_sign(numer, denom);
	return *this;
}

// Non-member arithmetic operators
ExactNumber operator+(const ExactNumber& lhs, const ExactNumber& rhs)
{
	ExactNumber tmp(lhs);
	tmp += rhs;
	return tmp;
}

ExactNumber operator-(const ExactNumber& lhs, const ExactNumber& rhs)
{
	ExactNumber tmp(lhs);
	tmp -= rhs;
	return tmp;
}

ExactNumber operator*(const ExactNumber& lhs, const ExactNumber& rhs)
{
	ExactNumber tmp(lhs);
	tmp *= rhs;
	return tmp;
}

ExactNumber operator/(const ExactNumber& lhs, const ExactNumber& rhs)
{
	ExactNumber tmp(lhs);
	tmp /= rhs;
	return tmp;
}

// Equality / inequality
bool ExactNumber::operator==(const ExactNumber& rhs) const
{
	return numer == rhs.numer && denom == rhs.denom;
}

bool ExactNumber::operator!=(const ExactNumber& rhs) const
{
	return !(*this == rhs);
}

// Relational operators
bool ExactNumber::operator<(const ExactNumber& rhs) const
{
	// Handle infinities
	if (denom == 0 || rhs.denom == 0) 
    {
		if (denom == 0 && rhs.denom == 0) {
			// Both infinite: -inf < +inf
			return numer < rhs.numer;
		}
		if (denom == 0) {
			// this is infinite: -inf < anything, +inf < nothing
			return numer < 0;
		}
		// rhs is infinite: anything < +inf, nothing < -inf
		return rhs.numer > 0;
	}

	// Both finite: compare a/b < c/d -> ad < bc (assuming b,d > 0)
	long long left = static_cast<long long>(numer) * rhs.denom;
	long long right = static_cast<long long>(rhs.numer) * denom;
	return left < right;
}

bool ExactNumber::operator>(const ExactNumber& rhs) const
{
	return rhs < *this;
}

bool ExactNumber::operator<=(const ExactNumber& rhs) const
{
	return !(*this > rhs);
}

bool ExactNumber::operator>=(const ExactNumber& rhs) const
{
	return !(*this < rhs);
}

// Stream insertion
ostream& operator<<(ostream& os, const ExactNumber& n)
{
	os << "(" << n.numer << "/" << n.denom << ")";
	return os;
}