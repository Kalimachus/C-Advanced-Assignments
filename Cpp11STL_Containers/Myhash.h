#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "list.h"
#include "DuplicateError.h"

using namespace std;

template<typename T, unsigned buckets = 1500>
class Myhash {
private:
	List<T> Table[buckets];
	int filled;
	int maxSize;
public:
	//Myhash(bool b = true) : filled(0), array(new List<T>*[buckets]), filledBuckets(0) {
	//	for (auto i = 0u; i < buckets; i++) {
	//		array[i] = nullptr;
	//	}
	//}
	Myhash(bool b = true) : filled(0), maxSize(buckets) {
	}
	~Myhash() {
		/*
		for (auto i = 0u; i < buckets; i++) {
			if (array[i]) {
				delete array[i];
			}
		}
		delete[] array;
		array = nullptr;
		*/
	}
	void insert(T object);
	unsigned hash(string key);
	int countBucket(int index);
	bool find(T target);
	int size() { return filled; }
	float percentOfBucketsUsed() { return float(countBuckets()) / float(buckets); }
	float averageNonEmptyBucketSize() {
		return float(filled) / float (countBuckets());
	}
	int countBuckets() const {
		int filledBuckets = 0;
		for (int i = 0; i < buckets; i++)
		{
			if (!Table[i].empty())
			{
				filledBuckets++;
			}
		}
		return filledBuckets;
	}
	int largestBucketSize() {
		int largest = 0;
		int max = 0;
		for (int i = 0; i < buckets; i++) {
			max = Table[i].getLength();
			//max = array[i]->getLength();
			if (max >= largest) {
				largest = max;
			}
		}
		return largest;
	}
};

inline unsigned hash(unsigned key, unsigned size) {
	int c2 = 0x27d4eb2d;
	key = (key ^ 61) ^ (key >> 16);
	key = key + (key << 3);
	key = key ^ (key >> 4);
	key = key * c2;
	key = key ^ (key >> 15);
	return key % size;
}

template<typename T, unsigned buckets>
int Myhash<T, buckets>::countBucket(int index)
{
	assert(index >= 0);
	assert(index < buckets);
	return Table[index].getLength();
}
/*
template<typename T, unsigned buckets>
bool Myhash<T, buckets>::find(T target) {
	for (int i = 0; i < buckets; i++)
	{
		if (!Table[i].empty())
		{
			Table[i].beginIterator();
			for (int j = 0; j < countBucket(i); j++)
			{
				if (target == Table[i].getIterator())
					return true;
				if (j < (Table[i].getLength() - 1))
					Table[i].advanceIterator();
			}
		}
	}
	return false;
}
*/

template<typename T, unsigned buckets>
bool Myhash<T, buckets>::find(T target) {
	unsigned i = target;
	auto index = ::hash(i, buckets);
	if (!Table[index].empty()) {
		Table[index].beginIterator();
		for (int j = 0; j < Table[index].getLength(); j++)
		{
			if (target == Table[index].getIterator())
				return true;
			if (j < (Table[index].getLength() - 1))
				Table[index].advanceIterator();
		}
	}
	return false;
}


template<typename T, unsigned buckets>
void Myhash<T, buckets>::insert(T object) {
	if(find(object)){
		throw (DuplicateError<T>(string("Duplicate Mystring: "), object));
	}
	else {
		unsigned i = object;
		auto index = ::hash(i, buckets);
		Table[index].insertEnd(object);
		filled++;
	}
}
