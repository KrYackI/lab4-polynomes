#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const extern int lb;
const extern int p;

//x - 0
//y - 1
//z - 2

int rnd(int x)
{
	if (x < lb)
		return lb;
	if (x > lb + p - 1)
		return lb + p - 1;
	return x;
}

struct monom
{
	double mult;
	int pow;
	monom(double m = 1.0, int x = 0, int y = 0, int z = 0)
	{
		mult = m;
		pow = (x - lb) + (y - lb) * p + (z - lb) * p * p;
	}

	int getX() { return pow % p + lb; }
	int getY() { return (pow / p) % p + lb; }
	int getZ() { return pow / p / p + lb; }

	void clear() {
		mult = 1.0; pow = -lb + -lb * p + -lb * p * p;
	}

	monom operator-()
	{
		return monom(-mult, getX(), getY(), getZ());
	}

	monom operator+ (const monom& m)
	{
		if (pow == m.pow)
			return monom(mult + m.mult, getX(), getY(), getZ());
		return monom();
	}

	monom operator- (const monom& m)
	{
		if (pow == m.pow)
			return monom(mult - m.mult, getX(), getY(), getZ());
		return monom();
	}

	monom operator* (monom& m)
	{
		return monom(mult * m.mult, rnd(getX() + m.getX()), rnd(getY() + m.getY()), rnd(getZ() + m.getZ()));
	}

	double calc(double x, double y, double z)
	{
		double res = 0;
		res += mult * exp(getX() * log(x)) * exp(getY() * log(y)) * exp(getZ() * log(z));
		return res;
	}

	//3.14*X^3*Y^6*Z^7

	friend ostream& operator<<(ostream& out, monom& m)
	{
		out << m.mult;
		if (m.mult == 0) return out;
		if (m.getX()) out << "*X^" << m.getX();
		if (m.getY()) out << "*Y^" << m.getY();
		if (m.getZ()) out << "*Z^" << m.getZ();
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, monom& m)
	{
		m.clear();
		string s, tmp = "";
		int st = 0, i = 0, t;
		char c;
		in >> s;
		while (i < s.length())
		{
			c = s[i];
			if (c <= '9' && c >= '0' || c == '.' || c == '-')
			{
				tmp += c;
			}
			else if (c == 'X' || c == 'Y' || c == 'Z')
			{
				if (tmp == "")
					tmp += "1";
				if (!st)
					m.mult = stod(tmp, 0);
				else
				{
					t = stoi(tmp, 0, 10);
					while (st - 1)
					{
						t *= p;
						st--;
					}
					m.pow += t;
				}
				switch (c)
				{
				case 'X': {st = 1; break; }

				case 'Y': {st = 2; break; }

				case 'Z': {st = 3; break; }
				}
				tmp = "";
				i ++;
			}
			i++;
		}
		if (!st)
			m.mult = stod(tmp, 0);
		else
		{
			t = stoi(tmp, 0, 10);
			while (st - 1 > 0)
			{
				t *= p;
				st--;
			}
			m.pow += t;
		}
		return in;
	}
};


struct link
{
	monom val;
	link* next;
	link(monom _v = monom(), link* l = nullptr)
	{
		val = _v;
		next = l;
	}
};
