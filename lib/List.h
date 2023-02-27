#pragma once

struct link
{
	double mult;
	int pow;
	link* next;
	link(double m, int p, link* l = nullptr)
	{
		mult = m;
		pow = p;
		next = l;
	}
};

class list
{
protected:
	link* start;
	link* end;
	void addlast(double m, int p)
	{
		link* n = new link(m, p, start);
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
	list()
	{
		start = new link(0, 0);
		start->next = start;
		end = start;
	}

	list(const list& l)
	{
		start = new link(0, 0);
		start->next = start;
		end = start;
		link* tmp = l.start->next;
		while (tmp != l.start)
		{
			addlast(tmp->mult, tmp->pow);
			tmp = tmp->next;
		}
	}

	list operator=(const list& l)
	{
		if (this == &l)
			return *this;
		clear();
		link* tmp = l.start->next;
		while (tmp != l.start)
		{
			addlast(tmp->mult, tmp->pow);
			tmp = tmp->next;
		}
		return *this;
	}

	//void add(double m, int p)
	//{
	//	link* tmp = start;
	//	while (tmp->next != start)
	//	{
	//		if (tmp->next->pow > p)
	//		{
	//			link* n = new link(m, p, tmp->next);
	//			tmp->next = n;
	//			return;
	//		}
	//		tmp = tmp->next;
	//	}
	//	addlast(m, p);
	//}

	~list()
	{
		while (start->next != start)
		{
			link* d = start->next;
			start->next = start->next->next;
			delete d;
		}
	}
};