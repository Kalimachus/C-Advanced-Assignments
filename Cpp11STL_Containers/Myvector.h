#include <vector>

template<typename T>
class Myvector : public vector<T> {
public:
	Myvector() : vector<T>() {}
	bool find(T item);
	void insert(T item);
};

template<typename T>
bool Myvector<T>::find(T item) {
	typename Myvector<T>::const_iterator it;
	for (it = Myvector<T>::cbegin(); it != Myvector<T>::cend(); it++) {
		if (*it == item) return true;
	}
	return false;
}

template<typename T>
void Myvector<T>::insert(T item) {
	(*this).push_back(item);
}
