#pragma once
#include <cstdlib>
#include <list>

template<typename T>
class Mylist : public list<T> {
public:
	Mylist() : list<T>() {}
	bool find(T targObj);
	void insert(T inObject);
};

template<typename T>
bool Mylist<T>::find(T targObj) {
	typename Mylist<T>::const_iterator it;
	for (it = Mylist<T>::cbegin(); it != Mylist<T>::cend(); it++) {
		if (*it == targObj) return true;
	}
	return false;
}

template<typename T>
void Mylist<T>::insert(T inObject) {
	(*this).push_back(inObject);
}
