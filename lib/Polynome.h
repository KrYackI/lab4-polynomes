#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "List.h"

using namespace std;

class polynome : public list
{

public:
	//polynome() : list() {}
	//polynome(const polynome& p)
	//{

	//}

	void add(double m, int p)
	{
		link* tmp = start;
		while (tmp->next != start)
		{
			if (tmp->next->pow == p)
			{
				tmp->next->mult += m;
				return;
			}
			if (tmp->next->pow > p)
			{
				link* n = new link(m, p, tmp->next);
				tmp->next = n;
				return;
			}
			tmp = tmp->next;
		}
		addlast(m, p);
	}

	polynome operator+(const polynome& poly)
	{
		polynome res;
		link* t = start->next;
		link* p = poly.start->next;
		while (t != start && p != poly.start)
		{
			if (t->pow == p->pow)
			{
				if (t->mult + p->mult != 0)
					res.addlast(t->mult + p->mult, t->pow);
				t = t->next;
				p = p->next;
			}
			else if (t->pow < p->pow)
			{
				res.addlast(t->mult, t->pow);
				t = t->next;
			}
			else
			{
				res.addlast(p->mult, p->pow);
				p = p->next;
			}
		}
		while (t != start)
		{
			res.addlast(t->mult, t->pow);
			t = t->next;
		}
		while (p != poly.start)
		{
			res.addlast(p->mult, p->pow);
			p = p->next;
		}
		return res;
	}

	polynome operator-(const polynome& poly)
	{
		polynome res;
		link* t = start->next;
		link* p = poly.start->next;
		while (t != start && p != poly.start)
		{
			if (t->pow == p->pow)
			{
				if (t->mult - p->mult != 0)
					res.addlast(t->mult - p->mult, t->pow);
				t = t->next;
				p = p->next;
			}
			else if (t->pow < p->pow)
			{
				res.addlast(t->mult, t->pow);
				t = t->next;
			}
			else
			{
				res.addlast(-(p->mult), p->pow);
				p = p->next;
			}
		}
		while (t != start)
		{
			res.addlast(t->mult, t->pow);
			t = t->next;
		}
		while (p != poly.start)
		{
			res.addlast(-(p->mult), p->pow);
			p = p->next;
		}
		return res;
	}

	polynome operator*(const polynome& poly)
	{
		polynome res;
		link* t = start->next;
		link* p = poly.start->next;
		while (t != start)
		{
			while (p != poly.start)
			{
				res.add(t->mult * p->mult, t->pow + p->pow);
				p = p->next;
			}
			t = t->next;
			p = poly.start->next;
		}
		return res;
	}

	double calc(double mltplr)
	{
		double res = 0;
		link* tmp = start->next;
		while (tmp != start)
		{
			res += tmp->mult * exp(tmp->pow * log(mltplr));
			tmp = tmp->next;
		}
		return res;
	}

	friend ostream& operator<<(ostream& out, polynome& p)
	{
		link* tmp = p.start->next;
		while (tmp != p.start)
		{
			out << tmp->mult << '^' << tmp->pow << ' ';
			tmp = tmp->next;
		}
		out << "& ";
		return out;
	}

	friend istream& operator>>(istream& in, polynome& poly)
	{
		poly.clear();
		string s;
		string sep = "&";
		string buff;
		double m;
		int p;
		in >> s;
		while (s != sep && s!="")
		{
			buff = "";
			//m = atof(s.substr(0, s.find("^") - 1));
			m = stod(s.substr(0, s.find("^")), 0);
			//p = atoi(s.substr(s.find("^") + 1, s.length()));
			p = stoi(s.substr(s.find("^") + 1, s.length()), 0, 10);
			poly.addlast(m, p);
			in >> s;
		}
		return in;
	}
};
