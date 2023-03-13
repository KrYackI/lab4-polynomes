#pragma once


//#include "List.h"
#include "monom.h"

using namespace std;

const extern int lb;
const extern int p;

class polinom
{
protected:
	link* start;
	link* end;
	void addlast(monom _v)
	{
		link* n = new link(_v, start);
		end->next = n;
		end = n;
	}

	void clear()
	{
		while (start->next != start)
		{
			link* d = start->next;
			start->next = start->next->next;
			delete d;
		}
		end = start;
	}

public:
	polinom()
	{
		start = new link();
		start->next = start;
		end = start;
	}

	polinom(const polinom& l)
	{
		start = new link();
		start->next = start;
		end = start;
		link* tmp = l.start->next;
		while (tmp != l.start)
		{
			addlast(tmp->val);
			tmp = tmp->next;
		}
	}

	polinom operator=(const polinom& l)
	{
		if (this == &l)
			return *this;
		clear();
		link* tmp = l.start->next;
		while (tmp != l.start)
		{
			addlast(tmp->val);
			tmp = tmp->next;
		}
		return *this;
	}

	//void add(monom _v)
	//{
	//	link* tmp = start;
	//	while (tmp->next != start)
	//	{
	//		if (tmp->next->val > _v.pow)
	//		{
	//			link* n = new link(_v, tmp->next);
	//			tmp->next = n;
	//			return;
	//		}
	//		tmp = tmp->next;
	//	}
	//	addlast(_v);
	//}

	~polinom()
	{
		while (start->next != start)
		{
			link* d = start->next;
			start->next = start->next->next;
			delete d;
		}
	}

	void add(monom m)
	{
		link* tmp = start;
		while (tmp->next != start)
		{
			if (tmp->next->val.pow == m.pow)
			{
				tmp->next->val.mult += m.mult;
				return;
			}
			if (tmp->next->val.pow > m.pow)
			{
				link* n = new link(m, tmp->next);
				tmp->next = n;
				return;
			}
			tmp = tmp->next;
		}
		addlast(m);
	}

	polinom operator+(const polinom& poly)
	{
		polinom res;
		link* t = start->next;
		link* p = poly.start->next;
		while (t != start && p != poly.start)
		{
			if (t->val.pow == p->val.pow)
			{
				if (t->val.mult + p->val.mult != 0)
					res.addlast(t->val + p->val);
				t = t->next;
				p = p->next;
			}
			else if (t->val.pow < p->val.pow)
			{
				res.addlast(t->val);
				t = t->next;
			}
			else
			{
				res.addlast(p->val);
				p = p->next;
			}
		}
		while (t != start)
		{
			res.addlast(t->val);
			t = t->next;
		}
		while (p != poly.start)
		{
			res.addlast(p->val);
			p = p->next;
		}
		return res;
	}

	polinom operator-(const polinom& poly)
	{
		polinom res;
		link* t = start->next;
		link* p = poly.start->next;
		while (t != start && p != poly.start)
		{
			if (t->val.pow == p->val.pow)
			{
				if (t->val.mult - p->val.mult != 0)
					res.addlast(t->val - p->val);
				t = t->next;
				p = p->next;
			}
			else if (t->val.pow < p->val.pow)
			{
				res.addlast(t->val);
				t = t->next;
			}
			else
			{
				res.addlast(-(p->val));
				p = p->next;
			}
		}
		while (t != start)
		{
			res.addlast(t->val);
			t = t->next;
		}
		while (p != poly.start)
		{
			res.addlast(-(p->val));
			p = p->next;
		}
		return res;
	}

	polinom operator*(const polinom& poly)
	{
		polinom res;
		link* t = start->next;
		link* p = poly.start->next;
		while (t != start)
		{
			while (p != poly.start)
			{
				res.add(t->val * p->val);
				p = p->next;
			}
			t = t->next;
			p = poly.start->next;
		}
		return res;
	}

	double calc(double x = 1.0, double y = 1.0, double z = 1.0)
	{
		double res = 0;
		link* tmp = start->next;
		while (tmp != start)
		{
			res += tmp->val.calc(x, y, z);
			tmp = tmp->next;
		}
		return res;
	}

	friend ostream& operator<<(ostream& out, polinom& poli)
	{
		link* tmp = poli.start->next;
		while (tmp->next != poli.start)
		{
			out << tmp->val << " + ";
			tmp = tmp->next;
		}
		out << tmp->val << " & " << endl;
		return out;
	}

	friend istream& operator>>(istream& in, polinom& poli)
	{
		string s, sep = "&";
		bool minus = false;
		monom tmp;
		in >> s;
		while (s != sep && s != "")
		{
			if (s == "-")
				minus = true;
			else if (s != "+")
			{
				stringstream ss;
				ss << s;
				ss >> tmp;
				if (minus)
				{
					minus = false;
					tmp.mult = -tmp.mult;
				}
				poli.add(tmp);
			}

			in >> s;
		}
		return in;
	}
};

//class polinom : public list
//{
//
//public:
//	//polinom() : list() {}
//	//polinom(const polinom& p)
//	//{
//
//	//}
//
//	void add(double m, int p)
//	{
//		link* tmp = start;
//		while (tmp->next != start)
//		{
//			if (tmp->next->pow == p)
//			{
//				tmp->next->mult += m;
//				return;
//			}
//			if (tmp->next->pow > p)
//			{
//				link* n = new link(m, p, tmp->next);
//				tmp->next = n;
//				return;
//			}
//			tmp = tmp->next;
//		}
//		addlast(m, p);
//	}
//
//	polinom operator+(const polinom& poly)
//	{
//		polinom res;
//		link* t = start->next;
//		link* p = poly.start->next;
//		while (t != start && p != poly.start)
//		{
//			if (t->pow == p->pow)
//			{
//				if (t->mult + p->mult != 0)
//					res.addlast(t->mult + p->mult, t->pow);
//				t = t->next;
//				p = p->next;
//			}
//			else if (t->pow < p->pow)
//			{
//				res.addlast(t->mult, t->pow);
//				t = t->next;
//			}
//			else
//			{
//				res.addlast(p->mult, p->pow);
//				p = p->next;
//			}
//		}
//		while (t != start)
//		{
//			res.addlast(t->mult, t->pow);
//			t = t->next;
//		}
//		while (p != poly.start)
//		{
//			res.addlast(p->mult, p->pow);
//			p = p->next;
//		}
//		return res;
//	}
//
//	polinom operator-(const polinom& poly)
//	{
//		polinom res;
//		link* t = start->next;
//		link* p = poly.start->next;
//		while (t != start && p != poly.start)
//		{
//			if (t->pow == p->pow)
//			{
//				if (t->mult - p->mult != 0)
//					res.addlast(t->mult - p->mult, t->pow);
//				t = t->next;
//				p = p->next;
//			}
//			else if (t->pow < p->pow)
//			{
//				res.addlast(t->mult, t->pow);
//				t = t->next;
//			}
//			else
//			{
//				res.addlast(-(p->mult), p->pow);
//				p = p->next;
//			}
//		}
//		while (t != start)
//		{
//			res.addlast(t->mult, t->pow);
//			t = t->next;
//		}
//		while (p != poly.start)
//		{
//			res.addlast(-(p->mult), p->pow);
//			p = p->next;
//		}
//		return res;
//	}
//
//	polinom operator*(const polinom& poly)
//	{
//		polinom res;
//		link* t = start->next;
//		link* p = poly.start->next;
//		while (t != start)
//		{
//			while (p != poly.start)
//			{
//				res.add(t->mult * p->mult, t->pow + p->pow);
//				p = p->next;
//			}
//			t = t->next;
//			p = poly.start->next;
//		}
//		return res;
//	}
//
//	double calc(double mltplr)
//	{
//		double res = 0;
//		link* tmp = start->next;
//		while (tmp != start)
//		{
//			res += tmp->mult * exp(tmp->pow * log(mltplr));
//			tmp = tmp->next;
//		}
//		return res;
//	}
//
//	friend ostream& operator<<(ostream& out, polinom& p)
//	{
//		link* tmp = p.start->next;
//		while (tmp != p.start)
//		{
//			out << tmp->mult << '^' << tmp->pow << ' ';
//			tmp = tmp->next;
//		}
//		out << "& ";
//		return out;
//	}
//
//	friend istream& operator>>(istream& in, polinom& poly)
//	{
//		poly.clear();
//		string s;
//		string sep = "&";
//		string buff;
//		double m;
//		int p;
//		in >> s;
//		while (s != sep && s!="")
//		{
//			buff = "";
//			//m = atof(s.substr(0, s.find("^") - 1));
//			m = stod(s.substr(0, s.find("^")), 0);
//			//p = atoi(s.substr(s.find("^") + 1, s.length()));
//			p = stoi(s.substr(s.find("^") + 1, s.length()), 0, 10);
//			poly.addlast(m, p);
//			in >> s;
//		}
//		return in;
//	}
//};
