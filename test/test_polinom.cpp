#include "gtest.h"
#include "polinom.h"

const int lb = -3;
const int p = 10;

TEST(monom, IO)
{
	ifstream in("list.txt");
	monom m;
	in >> m;
	ofstream out("res.txt");
	out << m;
	ASSERT_NO_THROW();
}

TEST(monom, get)
{
	ifstream in("list.txt");
	monom m;
	in >> m;
	int f = m.getX() + m.getY() + m.getZ();
	EXPECT_EQ(f, 13);
}

TEST(monom, math)
{
	ifstream in("list.txt");
	monom m, n, k;
	in >> m; 
	in >> n;
	k = m + n;
	ofstream out("res.txt");
	out << k;
	k = m - n;
	out << k;
	k = m * n;
	out << k;
	ASSERT_NO_THROW();
}

TEST(polinom, p)
{
	polinom l1, l2, l3;
	//l1.add(5, 3);
	//l1.add(2, 7);
	//l1.add(68, 2);
	//l2.add(5, 3);
	//l2.add(6, 3);
	//l2.add(4, 3);
	//l3.add(6, 3);
	//l3.add(4, 3);
	ifstream in("poli.txt");
	string s;
	in >> l1;
	in >> s;
	switch (s[0])
	{
	case '+':
	{
		in >> l2;
		l3 = l1 + l2;
		break;
	}
	case '-':
	{
		in >> l2;
		l3 = l1 - l2;
		break;
	}
	case '*':
	{
		in >> l2;
		l3 = l1 * l2;
		break;
	}
	}
	l3.calc(2, 3, 0.5);
	ofstream out("resp.txt");
	out << l3;
	ASSERT_NO_THROW();
}
