#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

namespace bigNumber
{
	class BadBase : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Numbers Must Have Same Base...\n";
		}
	};

	class DecimalBaseException : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Decimal Base Needed...\n";
		}
	};

	class ZeroDivException : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Can't divide by zero...\n";
		}
	};

	class ZeroModException : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Can't module by zero...\n";
		}
	};

	class WrongSizeException : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Size should be 1...\n";
		}
	};

	class BinaryBaseException : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Binary base needed for this operation...\n";
		}
	};

	class MathException : public exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Math Error...\n";
		}
	};

	enum Base
	{
		Decimal,Binary,Octal,Hexa
	};

	class BigInt
	{
	private:
		vector<short> num;
		string name;
		bool isNegative;
		Base base;

		short getBase()
		{
			switch (base)
			{
			case bigNumber::Decimal:
				return 10;
			case bigNumber::Binary:
				return 2;
			case bigNumber::Octal:
				return 7;
			case bigNumber::Hexa:
				return 16;
			}
		}

		//Turn the char to num
		short toNum(char x)
		{
			if (x == '0') return 0;
			else if (x == '1') return 1;
			else if (x == '2') return 2;
			else if (x == '3') return 3;
			else if (x == '4') return 4;
			else if (x == '5') return 5;
			else if (x == '6') return 6;
			else if (x == '7') return 7;
			else if (x == '8') return 8;
			else if (x == '9') return 9;
			else if (x == 'A') return 10;
			else if (x == 'B') return 11;
			else if (x == 'C') return 12;
			else if (x == 'D') return 13;
			else if (x == 'E') return 14;
			else if (x == 'F') return 15;
			else return -1;
		}

		char toChar(short x)
		{
			if (x == 0) return '0';
			else if (x == 1) return '1';
			else if (x == 2) return '2';
			else if (x == 3) return '3';
			else if (x == 4) return '4';
			else if (x == 5) return '5';
			else if (x == 6) return '6';
			else if (x == 7) return '7';
			else if (x == 8) return '8';
			else if (x == 9) return '9';
			else if (x == 10) return 'A';
			else if (x == 11) return 'B';
			else if (x == 12) return 'C';
			else if (x == 13) return 'D';
			else if (x == 14) return 'E';
			else if (x == 15) return 'F';
			else return '$';
		}

		//Get the devisor for long division
		short getDivisor(BigInt x)
		{
			short z = 0;
			BigInt temp = this->getAbs();
			x = x.getAbs();
			x.optimize();

			while (temp <= x)
			{
				z++;
				temp = temp + *this;
			}

			if (z > getBase()-1)
			{
				cout << "There's Something wrong...\n";
			}

			return z;
		}

		bool isValidNum(char c)
		{
			c = toupper(c);

			switch (base)
			{
			case bigNumber::Decimal:
				return isdigit(c);
			case bigNumber::Binary:
				return c == '0' || c == '1';
			case bigNumber::Octal:
				return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6';
			case bigNumber::Hexa:
				return isdigit(c) || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F';
			}
		}

	public:

		//Empty Number
		BigInt()
		{
			name = "";
			isNegative = false;
			base = Base::Decimal;
		}

		//Constructor of BigInteger from string
		BigInt(string NumberValue , string NumberName = "", Base NumberBase = Base::Decimal)
		{
			name = NumberName;
			isNegative = false;
			base = NumberBase;

			char x = NumberValue[0];

			if (x == '-')
				isNegative = true;
			else if (isValidNum(x))
				num.push_back(toNum(x));
			else
				return;

			for (int i = 1; i < NumberValue.length(); i++)
			{
				x = NumberValue[i];

				if (isValidNum(x))
					num.push_back(toNum(x));
				else
					break;
			}
		}

		//Constructor of BigInteger from Number
		BigInt(int64_t NumberValue, string NumberName = "" , Base NumberBase = Base::Decimal)
		{
			name = NumberName;
			isNegative = false;
			base = NumberBase;
			setNumber(to_string(NumberValue));
		}

		//Set Number Name
		void setName(string NumberName)
		{
			name = NumberName;
		}

		//Set Number Value from string
		void setNumber(string NumberValue)
		{
			num.clear();

			char x = NumberValue[0];

			if (x == '-')
				isNegative = true;
			else if (isValidNum(x))
				num.push_back(toNum(x));
			else
				return;

			for (int i = 1; i < NumberValue.length(); i++)
			{
				x = NumberValue[i];

				if (isValidNum(x))
					num.push_back(toNum(x));
				else
					break;
			}
		}

		//Extend the Number from right side
		void extendWith(string Value)
		{
			char x;

			for (int i = 0; i < Value.length(); i++)
			{
				x = Value[i];

				if (isValidNum(x))
					num.push_back(toNum(x));
				else
					break;
			}
		}

		//Input Operator Overloading
		friend istream& operator>> (istream& in, BigInt& num)
		{
			string s;

			in >> s;

			char x = s[0];

			if (x == '-')
				num.isNegative = true;
			else if (num.isValidNum(x))
				num.num.push_back(num.toNum(x));
			else
				return in;

			for (int i = 1; i < s.length(); i++)
			{
				x = s[i];

				if (num.isValidNum(x))
					num.num.push_back(num.toNum(x));
				else
					break;
			}

			return in;
		}

		//Output Operator Overloading
		friend ostream& operator<< (ostream& out, BigInt x)
		{
			if (!x.name.empty())
				out << x.name << " : " << endl;

			if (x.isNegative && x.num.size() > 0)
				out << '-';

			for (int i = 0; i < x.num.size(); i++)
			{
				out << x.toChar(x.num[i]);
			}

			return out;
		}

		//Get Size of BigInteger In memory
		uint64_t getSizeInMemory()
		{
			return (uint64_t)sizeof(short) * num.size() + sizeof(bool);
		}

		//Get Size of BigInteger
		int getSize()
		{
			return num.size();
		}

		//Overloading of assignment operator from string
		BigInt& operator= (string NumberValue)
		{
			num.clear();

			char x = NumberValue[0];

			if (x == '-')
				isNegative = true;
			else if (isValidNum(x))
				num.push_back(toNum(x));
			else
				return *this;

			for (int i = 1; i < NumberValue.length(); i++)
			{
				x = NumberValue[i];

				if (isValidNum(x))
					num.push_back(toNum(x));
				else
					break;
			}

			return *this;
		}

		//overloading of assignment operator by number
		BigInt& operator= (int64_t x)
		{
			BigInt z(to_string(x));

			this->num = z.num;
			this->isNegative = z.isNegative;

			return *this;
		}

		//Check if equal
		friend bool operator== (BigInt x, BigInt y)
		{
			if (x.getSize() != y.getSize())
				return false;

			for (int i = 0; i < x.getSize(); i++)
			{
				if (x.num[i] != y.num[i])
					return false;
			}

			return true;
		}

		//Check if not equal
		friend bool operator!= (BigInt x, BigInt y)
		{
			if (x.getSize() != y.getSize())
				return true;

			for (int i = 0; i < x.getSize(); i++)
			{
				if (x.num[i] != y.num[i])
					return true;
			}

			return false;
		}

		//Check greater than
		friend bool operator> (BigInt x, BigInt y)
		{
			if (x.isNegative && !y.isNegative)
				return false;

			if (!x.isNegative && y.isNegative)
				return true;

			if (x.getSize() > y.getSize() && x.isNegative)
				return false;

			if (x.getSize() < y.getSize() && x.isNegative)
				return true;

			if (x.getSize() > y.getSize() && !x.isNegative)
				return true;

			if (x.getSize() < y.getSize() && !x.isNegative)
				return false;

			if (x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return false;
					else if (x.num[i] < y.num[i])
						return true;
				}

				//Equal State
				return false;
			}
			else if (!x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return true;
					else if (x.num[i] < y.num[i])
						return false;
				}

				//Equal State
				return false;
			}
		}

		//Check greater than or equal 
		friend bool operator>= (BigInt x, BigInt y)
		{
			if (x.isNegative && !y.isNegative)
				return false;

			if (!x.isNegative && y.isNegative)
				return true;

			if (x.getSize() > y.getSize() && x.isNegative)
				return false;

			if (x.getSize() < y.getSize() && x.isNegative)
				return true;

			if (x.getSize() > y.getSize() && !x.isNegative)
				return true;

			if (x.getSize() < y.getSize() && !x.isNegative)
				return false;

			if (x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return false;
					else if (x.num[i] < y.num[i])
						return true;
				}

				//Equal State
				return true;
			}
			else if (!x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return true;
					else if (x.num[i] < y.num[i])
						return false;
				}

				//Equal State
				return true;
			}
		}

		//Check if less than 
		friend bool operator< (BigInt x, BigInt y)
		{
			if (x.isNegative && !y.isNegative)
				return true;

			if (!x.isNegative && y.isNegative)
				return false;

			if (x.getSize() > y.getSize() && x.isNegative)
				return true;

			if (x.getSize() < y.getSize() && x.isNegative)
				return false;

			if (x.getSize() > y.getSize() && !x.isNegative)
				return false;

			if (x.getSize() < y.getSize() && !x.isNegative)
				return true;

			if (x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return true;
					else if (x.num[i] < y.num[i])
						return false;
				}

				//Equal State
				return false;
			}
			else if (!x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return false;
					else if (x.num[i] < y.num[i])
						return true;
				}

				//Equal State
				return false;
			}
		}

		//check less than or equal
		friend bool operator<= (BigInt x, BigInt y)
		{
			if (x.isNegative && !y.isNegative)
				return true;

			if (!x.isNegative && y.isNegative)
				return false;

			if (x.getSize() > y.getSize() && x.isNegative)
				return true;

			if (x.getSize() < y.getSize() && x.isNegative)
				return false;

			if (x.getSize() > y.getSize() && !x.isNegative)
				return false;

			if (x.getSize() < y.getSize() && !x.isNegative)
				return true;

			if (x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return true;
					else if (x.num[i] < y.num[i])
						return false;
				}

				//Equal State
				return true;
			}
			else if (!x.isNegative)
			{
				for (int i = 0; i < x.getSize(); i++)
				{
					if (x.num[i] > y.num[i])
						return false;
					else if (x.num[i] < y.num[i])
						return true;
				}

				//Equal State
				return true;
			}
		}

		//Turn Integer to BigInteger
		BigInt intToBigInt(int64_t Number)
		{
			return BigInt(to_string(Number));
		}
		
		//Reverse the Number
		void reverse()
		{
			std::reverse(num.begin(), num.end());
		}

		//Negate the BigInteger
		friend BigInt operator- (BigInt x)
		{
			if (x.isNegative)
			{
				x.isNegative = false;
				return x;
			}

			x.isNegative = true;
			return x;
		}

		//Get Max Sized Integer
		friend int maxSize(BigInt x, BigInt y)
		{
			if (x.getSize() > y.getSize())
				return x.getSize();

			return y.getSize();
		}

		//Remove the unused zeros in left side
		void optimize()
		{
			if (num.size() == 0)
				return;

			reverse();


			while (num.size() != 1 && num.back() == 0)
			{
				num.pop_back();
			}

			reverse();
		}

		//Add 2 BigIntegers
		friend BigInt operator+ (BigInt x, BigInt y)
		{
			try
			{
				if (x.base != y.base)
				{
					throw BadBase();
					return 0;
				}
			}
			catch (const BadBase& e)
			{
				cout << e.what();
			}


			BigInt z;
			short carry = 0;

			z.base = x.base;

			if (x.isNegative == y.isNegative)
			{
				if (x.isNegative)
					z.isNegative = true;

				x.reverse();
				y.reverse();

				int size = maxSize(x, y);

				for (int i = 0; i < size; i++)
				{
					if (i < x.getSize())
						carry += x.num[i];

					if (i < y.getSize())
						carry += y.num[i];

					z.num.push_back(carry % z.getBase());
					carry /= z.getBase();
				}

				if (carry != 0)
					z.num.push_back(carry);

				z.reverse();
			}
			else
			{
				if (x.isNegative)
				{
					//X is Negative but Y is Positive
					BigInt temp = -x;
					if (temp >= y)
					{
						x.reverse();
						y.reverse();

						short a, b;

						for (int i = 0; i < y.getSize(); i++)
						{
							a = x.num[i];
							b = y.num[i];

							if (a < b)
							{
								a += z.getBase();
								x.num[i + 1]--;
							}

							z.num.push_back(a - b);
						}

						for (int i = y.getSize(); i < x.getSize(); i++)
						{
							z.num.push_back(x.num[i]);
						}

						z.reverse();
					}
					else
					{
						x.reverse();
						y.reverse();

						z.isNegative = true;

						short a, b;

						for (int i = 0; i < x.getSize(); i++)
						{
							a = y.num[i];
							b = x.num[i];

							if (a < b)
							{
								a += z.getBase();
								y.num[i + 1]--;
							}

							z.num.push_back(a - b);
						}

						for (int i = x.getSize(); i < y.getSize(); i++)
						{
							z.num.push_back(y.num[i]);
						}

						z.reverse();
					}
				}
				else
				{
					x = -x;
					y = -y;

					z = x + y;
				}
			}

			z.optimize();
			return z;
		}

		//Subtract 2 BigIntegers
		friend BigInt operator- (BigInt x, BigInt y)
		{
			y = -y;

			return x + y;
		}
		//Add Biginteger With Number
		friend BigInt operator+ (BigInt x, int64_t y)
		{
			return x + BigInt(y);
		}

		//Subtract Biginteger With Number
		friend BigInt operator- (BigInt x, int64_t y)
		{
			return x - BigInt(y);
		}
		//Prefix increament
		BigInt operator++ ()
		{
			BigInt z = *this;

			z = z + 1;
			this->num = z.num;

			this->optimize();
			return *this;
		}
		//Postfix increament
		BigInt operator++ (int)
		{
			BigInt temp = *this, z = *this;

			z = z + 1;
			this->num = z.num;

			temp.optimize();
			return temp;
		}

		//prefix decreament
		BigInt operator-- ()
		{
			BigInt z = *this;
			z = z - 1;
			this->num = z.num;
			this->isNegative = z.isNegative;

			this->optimize();
			return *this;
		}
		//postfix decreament
		BigInt operator-- (int)
		{
			BigInt z = *this, temp = *this;

			z = z - 1;
			this->num = z.num;

			temp.optimize();
			return temp;
		}

		//Multiply Biginteger by 10 power Number
		BigInt multiply10(int power)
		{

			try
			{
				if (base != Decimal)
				{
					throw DecimalBaseException();
					return *this;
				}
			}
			catch (const DecimalBaseException& e)
			{
				cout << e.what();
			}

			BigInt x = *this;

			for (int i = 0; i < power; i++)
			{
				x.num.push_back(0);
			}

			x.optimize();
			return x;
		}

		//Multiply BigInteger by digit
		friend BigInt digitMult(BigInt x, short y)
		{
			BigInt z;
			short carry = 0;

			z.base = x.base;

			if (y >= x.getBase() || y < 0)
				return 0;

			x.reverse();

			for (int i = 0; i < x.getSize(); i++)
			{
				carry += y * x.num[i];

				z.num.push_back(carry % x.getBase());
				carry /= x.getBase();
			}

			if (carry)
			{
				z.num.push_back(carry);
			}

			z.reverse();

			return z;
		}

		//Mulltply 2 BigIntegers
		friend BigInt operator* (BigInt x, BigInt y)
		{
			
			try
			{
				if (x.base != Base::Decimal)
				{
					throw DecimalBaseException();
					return 0;
				}
				else if (x.base != y.base)
				{
					throw BadBase();
					return 0;
				}
			}
			catch (const DecimalBaseException& e)
			{
				cout << e.what();
			}
			catch (const BadBase& e)
			{
				cout << e.what();
			}

			BigInt z;
			vector<BigInt> sum;
			bool sign = false;
			short carry = 0;
			int size = 0;

			if ((x.isNegative && !y.isNegative) || (y.isNegative && !x.isNegative))
				sign = true;

			x = x.getAbs();

			y = y.getAbs();

			y.reverse();
			for (int i = 0; i < y.getSize(); i++)
			{
				z = digitMult(x, y.num[i]);
				z = z.multiply10(i);
				sum.push_back(z);
			}

			z.num.clear();

			for (int i = 0; i < sum.size(); i++)
			{
				sum[i].reverse();
			}

			if (sum.size() != 0)
				size = sum[sum.size() - 1].getSize();

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < sum.size(); j++)
				{
					if (i < sum[j].getSize())
						carry += sum[j].num[i];
				}
				z.num.push_back(carry % 10);
				carry /= 10;
			}

			if (carry)
				z.num.push_back(carry);

			z.reverse();

			z.isNegative = sign;
			z.optimize();
			return z;
		}

		BigInt getAbs()
		{
			BigInt x = *this;
			x.isNegative = false;
			return x;
		}

		//Division overloading of BigInteger
		friend BigInt operator/ (BigInt x, BigInt y)
		{
			try
			{
				if (x.base != Base::Decimal)
				{
					throw DecimalBaseException();
					return 0;
				}
				else if (x.base != y.base)
				{
					throw BadBase();
					return 0;
				}
				else if (y == 0)
				{
					throw ZeroDivException();
					return 0;
				}
			}
			catch (const DecimalBaseException& e)
			{
				cout << e.what();
			}
			catch (const BadBase& e)
			{
				cout << e.what();
			}
			catch (const ZeroDivException& e)
			{
				cout << e.what();
			}


			bool sign = false;
			BigInt z = 0, m;
			string temp = "";
			short div;


			if ((x.isNegative && !y.isNegative) || (y.isNegative && !x.isNegative))
				sign = true;

			x = x.getAbs();
			y = y.getAbs();

			for (int i = 0; i < x.getSize(); i++)
			{
				temp += to_string(x.num[i]);

				div = y.getDivisor(BigInt(temp));

				z.num.push_back(div);

				if (div == 0)
					continue;

				m = digitMult(y, div);

				m = BigInt(temp) - m;

				temp = m.toString();
			}

			z.optimize();
			z.isNegative = sign;
			return z;
		}

		//Mod overloading of BigInteger
		friend BigInt operator% (BigInt x, BigInt y)
		{
			try
			{
				if (x.base != Base::Decimal)
				{
					throw DecimalBaseException();
					return 0;
				}
				else if (x.base != y.base)
				{
					throw BadBase();
					return 0;
				}
				else if (y == 0)
				{
					throw ZeroModException();
					return 0;
				}
			}
			catch (const DecimalBaseException& e)
			{
				cout << e.what();
			}
			catch (const BadBase& e)
			{
				cout << e.what();
			}
			catch (const ZeroModException& e)
			{
				cout << e.what();
			}

			BigInt z = 0, m;
			string temp = "";
			short div;

			x = x.getAbs();
			y = y.getAbs();


			for (int i = 0; i < x.getSize(); i++)
			{
				temp += to_string(x.num[i]);

				div = y.getDivisor(BigInt(temp));

				if (div == 0)
					continue;

				z.num.push_back(div);

				m = digitMult(y, div);

				m = BigInt(temp) - m;

				temp = m.toString();
			}

			BigInt res(temp);
			res.optimize();
			return res;
		}

		//Overloading operator for Modulus with number
		friend BigInt operator% (BigInt x, int64_t y)
		{
			try
			{
				if (x.base != Base::Decimal)
				{
					throw DecimalBaseException();
					return 0;
				}
				else if (y == 0)
				{
					throw ZeroModException();
					return 0;
				}
			}
			catch (const DecimalBaseException& e)
			{
				cout << e.what();
			}
			catch (const ZeroModException& e)
			{
				cout << e.what();
			}
			

			x = x % BigInt(to_string(y));
			x.optimize();
			return x;
		}

		//left shift operator
		friend BigInt operator<< (BigInt x,int64_t y)
		{
			if (x.base == Decimal)
				x = x.toBinary();

			try
			{
				if (x.base != Base::Binary)
				{
					throw BinaryBaseException();
					return 0;
				}
			}
			catch (const BinaryBaseException& e)
			{
				cout << e.what();
			}

			for (int64_t i = 0; i < y; i++)
			{
				x.num.insert(x.num.end(), 0);
			}
			return x;
		}

		friend BigInt operator>> (BigInt x, int64_t y)
		{
			if (x.base == Decimal)
				x = x.toBinary();

			try
			{
				if (x.base != Base::Binary)
				{
					throw BinaryBaseException();
					return 0;
				}
			}
			catch (const BinaryBaseException& e)
			{
				cout << e.what();
			}

			for (int64_t i = 0; i < y; i++)
			{
				if (x.num.size() > 1)
					x.num.pop_back();
				else
				{
					x = 0;
					break;
				}
			}
			return x;
		}

		//Return a string of the number
		string toString()
		{
			string s = "";

			for (int i = 0; i < num.size(); i++)
			{
				s += to_string(num[i]);
			}

			return s;
		}

		//Power one by another
		friend BigInt pow(BigInt x, BigInt y)
		{
			BigInt res = 1;

			if (y == 0)
				return 1;

			for (BigInt i = 0; i < y; i++)
			{
				res = res * x;
			}

			return res;
		}

		//Get the square root of number as Integer (if x is NOT a perfect square the result will be increased by one)
		friend BigInt sqrt(BigInt x)
		{
			BigInt end = x,mid,sq,start = 0;

			while (start <= end)
			{
				mid = (start + end) / 2;

				sq = mid * mid;

				if (sq == x)
					return mid;

				if (sq < x)
					start = mid + 1;
				else
					end = mid - 1;
			}

			return start;
		}

		BigInt toBinary()
		{
			try
			{
				if (base != Base::Decimal)
				{
					throw DecimalBaseException();
					return 0;
				}
			}
			catch (const DecimalBaseException& e)
			{
				cout << e.what();
				return 0;
			}

			BigInt b , temp = *this;
			short rem , w;
			b.base = Base::Binary;

			while (temp != 0)
			{
				rem = toDigit(temp % 2);
				b.num.push_back(rem);
				temp = temp / 2;
			}

			b.isNegative = temp.isNegative;
			b.reverse();
			return b;
		}

		BigInt toDecimal()
		{
			BigInt x , p;
			x.base = Decimal;
			this->reverse();

			x = 0;
			p = 1;

			for (int i = 0; i < num.size(); i++)
			{
				if (num[i] == 1)
				{
					x = x + pow(BigInt(2), i);
				}
			}

			this->reverse();
			return x;
		}

		friend short toDigit(BigInt x)
		{
			try
			{
				if (x.getSize() != 1)
				{
					throw WrongSizeException();
					return 0;
				}
			}
			catch (const WrongSizeException& e)
			{
				cout << e.what();
			}

			if (x.isNegative)
				return -1 * x.num[0];

			return x.num[0];
		}

		friend BigInt AddMod(BigInt x, BigInt y, BigInt z)
		{
			return (x + y) % z;
		}

		friend BigInt SubMod(BigInt x, BigInt y, BigInt z)
		{
			return (x - y) % z;
		}

		friend BigInt MulltiplyMod(BigInt x, BigInt y, BigInt z)
		{
			return (x * y) % z;
		}

		friend BigInt DivideMod(BigInt x , BigInt y , BigInt z)
		{
			return (x / y) % z;
		}

		friend BigInt powMod(BigInt x, BigInt y, BigInt z)
		{
			if (x.getSize() == 0 || y.getSize() == 0)
			{
				return 0;
			}
			
			BigInt c = 1;
			x = x % z;

			try
			{
				if (x == 0 && y == 0)
				{
					throw MathException();
					return 0;
				}
			}
			catch (const MathException& e)
			{
				cout << e.what();
			}

			if (x == 0)
				return 0;

			if (y == 0)
				return 1;

			while (y > 0)
			{
				if (y % 2 != 0)
					c = (c * x) % z;

				y = y / 2;
				x = (x * x) % z;
			}

			return c;
		}

		void beRandom(uint64_t size)
		{
			if (size == 0)
				return;

			num.clear();

			num.resize(size);

			srand(rand() * time(NULL) * size);

			while (num[0] == 0)
				num[0] = rand() % getBase();

			for (int i = 1; i < size; i++)
				num[i] = rand()*rand() % getBase();
		}

		void bePrime(uint64_t size)
		{
			if (size == 0)
				return;

			srand(rand() * time(NULL));
			BigInt factor;
			BigInt phi;

			this->beRandom(size);
			phi = *this - 1;
			factor = (rand() * rand()) % phi + 2;

			while (powMod(factor,phi,*this) != 1)
			{
				this->beRandom(size);
				phi = *this - 1;
				factor = (rand() * rand()) % phi + 2;
			}
		}
	};
}