#pragma once
#include <string>
#include <cstdlib>
#include <stdexcept>

using namespace std;

template<typename T>
class DuplicateError : public logic_error {
private:
	T object;
public:
	DuplicateError(const string& msg, T ob) : logic_error(msg.c_str()), object(ob) {
	}
	T print() const { return object; }
	virtual ~DuplicateError() noexcept {}
};
