//Kyle Gomez Assignment 5
//GCC, Visual Studio Windows 10, 

#include<iostream>
#include<fstream>
#include<stdexcept>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<string>
#include<cstring>
#include<typeinfo>
#include "Myhash.h"
#include "Myvector.h"
#include "Mystring.h"
#include "Mylist.h"
#include "list.h"
#include "Myset.h"
#include "DuplicateError.h"

using namespace std;

const string DictionaryFileName = "C:\\Temp\\ass5\\words.txt";
const string DocumentFileName = "C:\\Temp\\ass5\\roosevelt_first_inaugural.txt";

template <typename T> void constructDictionary(const string wordfile, T& Method) {
	const clock_t START = clock();
	Mystring buffer;
	ifstream fin(wordfile.c_str());
	if (!fin) {
		cerr << "Can't find " << wordfile << endl;
		exit(-1);
	}
	while (fin >> buffer) {
		if (buffer[buffer.size() - 1] == '\r')
			buffer.resize(buffer.size() - 1);
		buffer.tolower();
		try {
			Method.insert(buffer);
		}
		catch (const DuplicateError<Mystring> &error) {
		}
	}
	fin.close();
	fin.clear();
	const double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
	cout << "Time to construct Dictionary of type " << typeid(Method).name() << " = " << T_ELAPSED << endl;
}

template <typename T> int spellcheck(const string wordfile, T& Method) {
	const clock_t START = clock();
	unsigned misspelledWords = 0;
	Mystring buffer;
	ifstream fin(wordfile.c_str());
	if (!fin) {
		cerr << "Can't find " << wordfile << endl;
		exit(-1);
	}
	while (fin >> buffer) {
		buffer.tolower();
		buffer.removePunctuation();
		if (!buffer.size() || isdigit(buffer.getMyStr()[0]))
			continue;
		if (!Method.find(buffer)) {
			misspelledWords++;
		}
	}
	fin.seekg(0, ios::beg);
	fin.close();
	fin.clear();
	const double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
	cout << "Spellcheck time using Dictionary type: " << typeid(Method).name() << " = " << T_ELAPSED << endl;
	cout << "Total misspelled words = ";
	return misspelledWords;
}

int main()
{
	Myhash<Mystring, 1500> Dictionary(true); // throw if duplicate words
	Mystring buffer;

	ifstream fin(DictionaryFileName.c_str());
	if (!fin)
	{
		cerr << "Can't find " << DictionaryFileName << endl;
		exit(-1);
	}
	while (fin >> buffer)
	{
		// remove \r if present (this for Mac/Linux)
		if (buffer[buffer.size() - 1] == '\r')
			buffer.resize(buffer.size() - 1);
		buffer.tolower();
		try
		{
			Dictionary.insert(buffer);
		}
		catch (const DuplicateError<Mystring>& error)
		{
			cout << error.what() << buffer.getMyStr() <<endl;
		}
	}

	cout << "Number of words in the dictionary = " << Dictionary.size() << endl;
	cout << "Percent of hash table buckets used = " << setprecision(2) << fixed << 100 * Dictionary.percentOfBucketsUsed() << '%' << endl;
	cout << "Average non-empty bucket size = " << Dictionary.averageNonEmptyBucketSize() << endl;
	cout << "Largest bucket size = " << Dictionary.largestBucketSize() << endl;

	fin.close();
	fin.clear();

	// Spellcheck
	unsigned misspelledWords = 0;

	fin.open(DocumentFileName.c_str());
	if (!fin)
	{
		cerr << "Can't find " << DocumentFileName << endl;
		exit(-1);
	}
	while (fin >> buffer)
	{
		buffer.tolower();
		buffer.removePunctuation();
		if (!buffer.size() || isdigit(buffer.getMyStr()[0]))
			continue;
		if (!Dictionary.find(buffer))
		{
			misspelledWords++;
			cout << "Not found in the dictionary: " << buffer << endl;
		}
	}
	cout << "Total mispelled words = " << misspelledWords << endl;

	cout << endl << "********************  Part 2  **********************" << endl << endl;

	///////////////////////////// Part 2  ///////////////////////////

	Myhash<Mystring>   myhashDictionary;
	Mylist<Mystring>   mylistDictionary;
	Myvector<Mystring> myvectorDictionary;
	Myset<Mystring>    mysetDictionary;

	constructDictionary(DictionaryFileName, myhashDictionary);
	cout << "Total misspelled words = " << spellcheck(DocumentFileName, myhashDictionary) << endl << endl;

	constructDictionary(DictionaryFileName, myvectorDictionary);
	cout << "Total misspelled words = " << spellcheck(DocumentFileName, myvectorDictionary) << endl << endl;

	constructDictionary(DictionaryFileName, mylistDictionary);
	cout << "Total misspelled words = " << spellcheck(DocumentFileName, mylistDictionary) << endl << endl;

	constructDictionary(DictionaryFileName, mysetDictionary);
	cout << "Total misspelled words = " << spellcheck(DocumentFileName, mysetDictionary) << endl << endl;

	cin.get();
}
