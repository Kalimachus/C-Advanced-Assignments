#pragma once
#include <set>

template<typename T>
class Myset : public set<T> {
public:
	Myset() : set<T>() {}
	bool find(T item);
};
template<typename T>
bool Myset<T>::find(T item) {
	typename Myset<T>::const_iterator it;
	for (it = Myset<T>::cbegin(); it != Myset<T>::cend(); it++) {
		if (*it == item) return true;
	}
	return false;
}
