#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

#include "BigInteger.h"


BigInteger::BigInteger()
{
	m_sizeReserved = 4;
	m_number = new uint8_t[m_sizeReserved]();
	m_digitCount = 0;
}

BigInteger::BigInteger(int someNumber)
{
	m_digitCount = 0;
	m_sizeReserved = 4;
	m_number = new uint8_t[m_sizeReserved]();

	for (int i = 0; (someNumber % 10) > 0; i++)
	{
		int tempNumber = someNumber % 10;
		setDigit(i, tempNumber);
		someNumber = someNumber / 10;
	}
}

BigInteger::BigInteger(std::string numberString)
{
	m_digitCount = 0;
	m_sizeReserved = 4;
	m_number = new uint8_t[m_sizeReserved];
	uint8_t* myArray = new uint8_t[numberString.size()]();

	for (unsigned int i = 0; i < numberString.size(); i++)
	{
		int value = numberString[numberString.size() - 1 - i] - '0';
		setDigit(i, value);
	}
}

BigInteger::BigInteger(const BigInteger & object)
{
	m_sizeReserved = object.m_sizeReserved;
	m_number = new uint8_t[object.m_sizeReserved]();

	for (unsigned int i = 0; i < m_sizeReserved; i++)
	{
		m_number[i] = object.m_number[i];
	}
	
	m_digitCount = object.m_digitCount;
}

BigInteger::~BigInteger()
{
	delete[]m_number;
	m_number = nullptr;
}

void BigInteger::operator=(const BigInteger & obj)
{
	m_sizeReserved = obj.m_sizeReserved;
	m_number = new uint8_t[obj.m_sizeReserved]();

	for (unsigned int i = 0; i < m_sizeReserved; i++)
	{
		m_number[i] = obj.m_number[i];
	}

	m_digitCount = obj.m_digitCount;
}

BigInteger BigInteger::add(const BigInteger& rhs)
{
	BigInteger result;
	unsigned int length = (this->m_digitCount > rhs.m_digitCount) ? this->m_digitCount : rhs.m_digitCount;

	int carry = 0;
	for (unsigned int digit = 0; digit < length; digit++)
	{
		int v1 = this->getDigit(digit);
		int v2 = rhs.getDigit(digit);
		int sum = v1 + v2 + carry;
		int single = sum % 10;
		carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

		result.setDigit(digit, single);
	}
	if (carry > 0)
	{
		result.setDigit(length, carry);
	}

	return result;
}

BigInteger BigInteger::multiply(const BigInteger& rhs)
{
	BigInteger result;
	const BigInteger& b = (this->m_digitCount < rhs.m_digitCount) ? *this : rhs;
	const BigInteger& t = (this->m_digitCount < rhs.m_digitCount) ? rhs : *this;

	for (unsigned int bDigit = 0; bDigit < b.m_digitCount; bDigit++)
	{
		BigInteger temp(0);
		int v1 = b.getDigit(bDigit);
		int carry = 0;
		for (unsigned int tDigit = 0; tDigit < t.m_digitCount; tDigit++)
		{
			int v2 = t.getDigit(tDigit);
			int sum = v1 * v2 + carry;
			int single = sum % 10;
			carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

			temp.setDigit(bDigit + tDigit, single);
		}
		if (carry > 0)
		{
			temp.setDigit(bDigit + t.m_digitCount, carry);
		}
		BigInteger temp2 = result.add(temp);
		result = temp2;
	}

	return result;
}

void BigInteger::display()
{
	for (unsigned int digit = m_digitCount; digit > 0; digit--)
	{
		std::cout << static_cast<int>(m_number[digit - 1]);
	}
}

// ------------------------------------------------------------------
//
// Returns the digit as the specified positon.  If the position is greater
// that the number representation, a 0 is returned.
//
// ------------------------------------------------------------------
std::uint8_t BigInteger::getDigit(unsigned int position) const
{
	if (position < m_digitCount)
	{
		return m_number[position];
	}

	return 0;
}

void BigInteger::setDigit(unsigned int position, std::uint8_t digit)
{
	if (position >= m_sizeReserved)
	{
		int tempSize = m_sizeReserved;

		while (position >= m_sizeReserved)
		{
			m_sizeReserved = m_sizeReserved * 2;
		}

		uint8_t* tempArray = new uint8_t[m_sizeReserved];

		for (int i = 0; i < tempSize; i++)
		{
			if (i < tempSize)
			{
				tempArray[i] = m_number[i];
			}
			else
			{
				tempArray[i] = 0;
			}
		}

		std::swap(tempArray, m_number);

		delete[]tempArray;
		tempArray = nullptr;
	}

	m_number[position] = digit;

	m_digitCount = position + 1;
}
