#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
using namespace std;

template <typename T>
struct Element 
{
	T value;
	weak_ptr<Element<T>> prev;
	shared_ptr<Element<T>> next{ nullptr };
	Element();
	Element(T);
};



template <typename T>
class MojaLista
{
private:
	shared_ptr<Element<T>> first{ nullptr };
	shared_ptr<Element<T>> last{ nullptr };
	int size{0};
public:
	void push_back(T);
	void move_back(T&&);
	void push_front(T);
	shared_ptr<Element<T>>find(T);
	bool erase(T);
	void displaySize();
	void low_to_high();
	void high_to_low();
	vector<T> to_vec();
	int get_size();
	const shared_ptr<Element<T>> get_first();
	const shared_ptr<Element<T>> get_last();
	MojaLista();
	MojaLista(const MojaLista&);
	MojaLista(MojaLista&&);
	~MojaLista();
	MojaLista& operator=(const MojaLista& source)
	{
		this->first = nullptr;
		this->last = nullptr;
		this->size = 0;

		if (source.first)
		{
			this->push_back(source.first->value);
			auto curr = source.first;
			while (curr->next)
			{
				this->push_back(curr->next->value);
				curr = curr->next;
			}
			this->size = source.size;
		}
	};
	MojaLista& operator=(MojaLista&& source)
	{
		this->first = nullptr;
		this->last = nullptr;
		this->size = 0;

		auto curr = source.first;
		if (source.first)
		{
			this->move_back(std::move(source.first->value));

			while (curr->next)
			{
				this->move_back(std::move(curr->next->value));
				curr = curr->next;
			}
		}
		this->size = source.size;
		source.size = 0;
	};
	void displayBack()
	{
		if (last)
		{
			auto e = last;
			cout << e->value << endl;
			while (!e->prev.expired())
			{
				cout << e->prev.lock()->value << endl;
				e = e->prev.lock();
			}
		}
		else
		{
			cout << "list is empty" << endl;
		}
	};
	void displayFront()
	{
		if (first)
		
		{
			auto e = first;
			cout << e->value << endl;
			while (e->next)
			{
				cout << e->next->value << endl;
				e = e->next;
			}
		}
		else
		{
			cout << "list is empty" << endl;
		}
	}
};

template<typename T>
inline void MojaLista<T>::push_back(T v)
{
	auto newElement = std::make_shared<Element<T>>(v);
	
	if (first==nullptr)
	{
		first = newElement;
		last = newElement;
		this->size++;
	}
	else
	{	
		last->next = newElement;
		newElement->prev = last;
		last = newElement;
		this->size++;
	}
}
template<typename T>
inline void MojaLista<T>::move_back(T &&v)
{
	auto newElement = std::make_shared<Element<T>>(v);

	if (first == nullptr)
	{
		first = newElement;
		last = newElement;
		this->size++;
	}
	else
	{
		last->next = newElement;
		newElement->prev = last;
		last = newElement;
		this->size++;
	}
}

template<typename T>
inline void MojaLista<T>::push_front(T v)
{
	auto newElement = std::make_shared<Element<T>>(v);
	if (first == nullptr)
	{
		first = newElement;
		last = newElement;
		this->size++;
	}
	else
	{
		first->prev = newElement;
		newElement->next = first;
		first = newElement;
		this->size++;
	}
}

template<typename T>
inline shared_ptr<Element<T>> MojaLista<T>::find(T v)
{
	auto tmp = this->first;
	while (tmp!=nullptr)
	{
		if (tmp->value == v)
		{
			//cout << "Element with the value " << v << " is found." << endl;
			return tmp;
		}
		else
		{
			tmp = tmp->next;
			//cout << "still searching..." << endl;
		}
	}
	return nullptr;
}


template<typename T>
inline bool MojaLista<T>::erase(T val)
{
	auto tmp = this->find(val);
	if (tmp == nullptr)
	{
		return false;
	}

	if (!tmp->prev.expired() && tmp->next != nullptr)
	{
		tmp->prev.lock()->next = tmp->next;
		tmp->next->prev = tmp->prev;
		//cout << "Element with the value " << val << " has been deleted." << endl;
		this->size--;
		return true;
	}
	//first element case
	else if(tmp->prev.expired())
	{
		//only one element case
		if (tmp->next == nullptr)
		{
			first = nullptr;
			last = nullptr;
			this->size--;
			return true;
		}
		else
		{
			first = tmp->next;
			//cout << "Element with the value " << val << " has been deleted." << endl;
			this->size--;
			return true;
		}
	}

	//last element case
	else if (tmp->next == nullptr)
	{
		tmp->prev.lock()->next = nullptr;
		last = tmp->prev.lock();
		//cout << "Element with the value " << val << " has been deleted." << endl;
		this->size--;
		return true;
	}
}
template<typename T>
inline int MojaLista<T>::get_size()
{
	return this->size;
}

template<typename T>
inline void MojaLista<T>::displaySize()
{
	cout << this->size << endl;
}


template<typename T>
inline void MojaLista<T>::low_to_high()
{
	if (first == nullptr)
		return;
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			auto ptr = first;
			while (ptr->next)
			{
				if (ptr->value > ptr->next->value)
				{
					swap(ptr->value, ptr->next->value);
				}
				ptr = ptr->next;
			}
		}
	}
}

template<typename T>
inline void MojaLista<T>::high_to_low()
{
	if (first == nullptr)
		return;
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			auto ptr = first;
			while (ptr->next)
			{
				if (ptr->value < ptr->next->value)
				{
					swap(ptr->value, ptr->next->value);
				}
				ptr = ptr->next;
			}
		}
	}
}

template<typename T>
inline vector<T> MojaLista<T>::to_vec()
{
	vector<T> vec{};
	auto tmp = this->first;
	if (tmp == nullptr)
	{
		return vec;
	}
	vec.push_back(tmp->value);
	while (tmp->next)
	{
		vec.push_back(tmp->next->value);
		tmp = tmp->next;
	}

	return vec;
}

template<typename T>
inline MojaLista<T>::MojaLista()
{
	this->first = nullptr;
	this->last = nullptr;
	this->size = 0;
}

template<typename T>
inline MojaLista<T>::MojaLista(const MojaLista& source)
{
		if (source.first)
		{
			this->push_back(source.first->value);
			auto curr = source.first;
			while (curr->next)
			{
				this->push_back(curr->next->value);
				curr = curr->next;
			}
			this->size = source.size;
		}
}

template<typename T>
inline MojaLista<T>::MojaLista(MojaLista&& source)
{
	auto curr = source.first;
	if (source.first)
	{this->move_back(std::move(source.first->value));
	
		while (curr->next)
		{
			this->move_back(std::move(curr->next->value));
			curr = curr->next;
		}
	}

	this->size = source.size;
	source.size = 0;
}

template<typename T>
inline MojaLista<T>::~MojaLista()
{
}

template<typename T>
inline Element<T>::Element()
{
	this->value = 0;
}

template<typename T>
inline Element<T>::Element(T value)
{
	this->value = value;
}
template<typename T>
inline const shared_ptr<Element<T>> MojaLista<T>::get_first()
{
	return this->first;
}
template<typename T>
inline const shared_ptr<Element<T>> MojaLista<T>::get_last()
{
	return this->last;
}