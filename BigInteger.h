#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <cstdint>
#include <iostream>
#include <string>

class TestCases;

class BigInteger
{
public:
	BigInteger();
	BigInteger(int someNumber);
	BigInteger(std::string numberString);
	BigInteger(const BigInteger& object);
	~BigInteger();

	void BigInteger::operator=(const BigInteger& obj);

	BigInteger add(const BigInteger& rhs);
	BigInteger multiply(const BigInteger& rhs);
	void display();

	friend TestCases; // TODO Have students do this first thing

private:
	std::uint8_t* m_number;		// Internal representation of the number.
	unsigned int m_sizeReserved;	// Total size of the allocated space used to internally store the number
	unsigned int m_digitCount;	// How many digits are in the number.

	std::uint8_t getDigit(unsigned int position) const;
	void setDigit(unsigned int position, std::uint8_t digit);
};

#endif
