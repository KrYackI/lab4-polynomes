#pragma once


const extern int lb; 
const extern int p;


template<typename T>
struct link
{
	T val;
	link* next;
	link(T _v = T(), link* l = nullptr)
	{
		val = _v;
		next = l;
	}
};

template<typename T>
class list
{
protected:
	link<T>* start;
	link<T>* end;
	void addlast(T _v)
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
	list()
	{
		start = new link();
		start->next = start;
		end = start;
	}

	list(const list& l)
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

	list operator=(const list& l)
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

	//iterator* iterator() {
	//	return new literator(first);
	//}

	//void add(T _v)
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

//template<typename T>
//class iterator
//{
//public:
//	virtual bool hasnext() = 0;
//	virtual T next() = 0;
//};
//
//template<typename T>
//class literator : public iterator
//{
//	link<T>* t;
//	link<T>* first;
//public:
//	literator(link<T>* first)
//	{
//		this->first = first;
//		t = first->next;
//	}
//	bool hasnext() { return t != first; }
//	T next()
//	{
//		if (t == first) throw - 1;
//		T val = t->val;
//		t = t->next;
//		return val;
//	}
//};