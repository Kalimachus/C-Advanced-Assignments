#pragma once
#ifndef LIST_H_
#define LIST_H_

#include <cstddef> //for NULL
#include<iostream>
#include <assert.h>

using namespace std;

template <class listdata> //list stores generic listdata, not any specific C++ type

class List {
private:
	struct Node {
		listdata data;
		Node* nextnode;
		Node* previousnode;
		Node(listdata newdata) : data(newdata), nextnode(NULL), previousnode(NULL) {}
	};
	typedef struct Node* NodePtr;

	NodePtr begin;
	NodePtr iterator;
	NodePtr end;
	int length;

	bool isSorted(const NodePtr& node) const;
	//Helper function for the public isSorted() function
	//Recursively determines whether a List is sorted in ascending order

	int binarySearch(int& low, int& high, const listdata&);
	//Recursively search the list by dividing the search space in half
	//Returns the index of the element, if it is found in the List
	//Returns -1 if the element is not in the List

	void reverse(const NodePtr& node) const;
	//Helper function for the public printReverse() function.
	//Recursively prints the data in a List in reverse.

public:

	/**Constructors and Destructors*/

	//Default constructor; initializes and empty list
	//Postcondition:List is initialized with it's members: begin(NULL), end(NULL),
	//and list length as 0.
	List();

	//Copy Constructor; copies a list into another one;
	List(const List<listdata>& obj);

	//Destructor. Frees memory allocated to the list
	//Postcondition: The list will be deleted as it leaves scope
	// via traversing the list in a loop that individually deletes the nodes
	// until the next node and after nodes are NULL
	~List();

	/**Manipulation Procedures*/

	void deleteBegin();
	//Removes the value of the first element in the list
	//Precondition: List should not be empty
	//Postcondition: First item should be deleted with
	// head pointer reassigned to next item in list

	void deleteEnd();
	//Removes the value of the last element in the list
	//Precondition: List should not be empty
	//Postcondition: Last item in list is deleted and next item
	// in list is pointing to null

	void insertBegin(const listdata& val);
	//Inserts a new element at the start of the list
	//If the list is empty, the new element becomes both first and last
	//Postcondition: head pointer points to inserted node, inserted node's next
	//pointer is pointing to null if no other item exists in list or the address of
	// the next item in list.

	void insertEnd(const listdata& val);
	//Inserts a new element at the end of the list
	//If the list is empty, the new element becomes both first and last
	//Postcondition: node is inserted at the end of list with previous item in list
	// pointing to newly inserted item's location and the new item's next pointer
	// is pointed to NULL

	void beginIterator();
	//postcondition: moves the iterator to the start of the list
	//precondition: list must not be empty

	void deleteIterator();
	//Postcondition: removes the element currently pointed to by the iterator. Iterator then points to NULL.
	//Precondition: list must not be empty, nor offEnd

	void insertIterator(const listdata&val);
	//Postcondition: inserts an element after the node currently pointed to by the iterator
	//Precondition: iterator must not be pointing to null, nor offEnd

	void advanceIterator();
	//Postcondition: iterator moved up by one node
	//Precondition: iterator must not be pointing to null, nor offEnd

	void reverseIterator();
	//Postcondition: iterator moved down by one node
	//Precondition: iterator must not be pointing to null, nor offEnd

	void advanceToIndex(const int&indexnum);
	//Moves the iterator to the node whose index number is specified in the parameter
	//Pre: length != 0
	//Pre: index <= length

	/**Accessors*/

	listdata getBegin() const;
	//Returns the first element in the list
	//Precondition: list should not be empty when called

	listdata getEnd() const;
	//Returns the last element in the list
	//Precondition: list should not be empty when called

	bool empty() const;
	//Determines whether a list is empty.

	int getLength() const;
	//Returns the size of the list

	listdata getIterator() const;
	//Post: returns the element currently pointed at by the iterator
	//Pre: iterator should not be empty, nor offEnd

	bool offEnd() const;
	//Post: returns whether the iterator is off the end of the list (if iterator is Null)

	bool isSorted() const;
	//Wrapper function that calls the isSorted helper function to determine whether
	//a list is sorted in ascending order.
	//We will consider that a list is trivially sorted if it is empty.
	//Therefore, no precondition is needed for this function

	int getIndex() const;
	//Indicates the index of the Node where the iterator is currently pointing
	//Nodes are numbered from 1 to size of the list
	//Pre: length != 0
	//Pre: !offEnd()

	int linearSearch(const listdata& data);
	//Searchs the list, element by element, from the start of the List to the end of the List
	//Returns the index of the element, if it is found in the List
	//Calls the above indexing functions in its implementation
	//Returns -1 if the element is not in the List
	//Pre: length != 0

	int binarySearch(const listdata&data);
	//Returns the index where data is located in the List
	//Calls the private helper function binarySearch to perform the search
	//Pre: length != 0
	//Pre: List is sorted (must test on a sorted list)

	/**Additional List Operations*/

	void print() const;
	//Prints to the console the value of each element in the list sequentially
	//and separated by a blank space
	//Prints nothing if the list is empty

	void printNumberedList() const;
	//Prints the contents of the linked list to the screen
	//in the format #. <element> followed by a newline

	bool operator==(const List<listdata> &obj) const;
	//Post: returns a true if all items in the list are the same.
	//Pre: list should be exact lengths

	void printReverse() const;
	//Wrapper function that calls the reverse helper function to print a list in reverse
	//prints nothing if the List is empty
};
/**Constructors and Destructors*/

//Default constructor; initializes and empty list
//Postcondition:List is initialized with it's members: begin(NULL), end(NULL),
//and list length as 0.
template <class listdata>
List<listdata>::List() : begin(NULL), iterator(NULL), end(NULL), length(0) {}

//Copy constructor
//Postcondition: a list will be created exactly like the one passed into the constructor
template <class listdata>
List<listdata>::List(const List & obj) {

	if (obj.begin == NULL)
	{
		begin = end = iterator = NULL;
	}
	else
	{
		begin = new Node(obj.begin->data);
		NodePtr temp = obj.begin;
		iterator = begin;

		while (temp->nextnode != NULL)
		{
			//get data of next item of list passed in
			temp = temp->nextnode;
			//create a new node with a name to assign its members
			NodePtr N = new Node(temp->data);
			//N's previous node will be assigned to the node that iterator is at
			N->previousnode = iterator;
			//iterator will assign current node's next to the new node (N)
			iterator->nextnode = N;
			//advance the iterator
			iterator = N;
		}
		end = iterator;
		iterator = NULL;
	}
	length = obj.length;
}

//Destructor. Frees memory allocated to the list
//Postcondition: The list will be deleted as it leaves scope
// via traversing the list in a loop that individually deletes the nodes
// until the next node and after nodes are NULL
template <class listdata>
List<listdata>::~List() {
	NodePtr after = begin;
	NodePtr before;
	while (after != NULL) {
		before = after->nextnode;
		delete after;
		after = before;
	}
}

/**Accessors*/

//Returns the first element in the list
//Precondition: List should not be empty when called. Returns begin.
// If empty when called, function returns -1.
template <class listdata>
listdata List<listdata>::getBegin() const {
	assert(begin != NULL);
	return begin->data;
}

//Returns the last element in the list
//Precondition: List should not be empty when called. Returns end.
// If empty when called, halt occurs
template <class listdata>
listdata List<listdata>::getEnd() const {
	assert(end != NULL);
	return end->data;
}

//Determines whether a list is empty.
template <class listdata>
bool List<listdata>::empty() const {
	return length == 0;
}

//Returns the size of the list
template <class listdata>
int List<listdata>::getLength() const {
	return length;
}

//Returns data element pointed by iterator
//Pre: do not call if iterator is pointing to NULL
template <class listdata>
listdata List<listdata>::getIterator() const {
	assert(iterator != NULL);
	return iterator->data;
}

//Returns true/false depending if the iterator is pointing at nothing or something
template <class listdata>
bool List<listdata>::offEnd()const {
	return iterator == NULL;
}

//Wrapper function that calls the isSorted helper function to determine whether
//a list is sorted in ascending order.
//We will consider that a list is trivially sorted if it is empty.
//Therefore, no precondition is needed for this function
template <class listdata>
bool List<listdata>::isSorted()const {
	return isSorted(begin);
}
//Corresponding Function in Private:
//Helper function for the public isSorted() function
//Recursively determines whether a List is sorted in ascending order
template <class listdata>
bool List<listdata>::isSorted(const NodePtr& current) const
{
	if (current->nextnode == NULL)//base case
		return true;
	else if (current->data > current->nextnode->data)//second base case
		return false;
	else
	{
		isSorted(current->nextnode);
		return true;
	}
}//O-time:O(n)

 //Indicates the index of the Node where the iterator is currently pointing
 //Nodes are numbered from 1 to size of the list
 //Pre: length != 0
 //Pre: !offEnd()
template <class listdata>
int List<listdata>::getIndex() const {
	assert(length != 0);
	assert(!offEnd());
	int count = 1;
	NodePtr curr = begin;//start left
	while (curr != iterator)//go until it meets iterator
	{
		curr = curr->nextnode;//go right
		count++;
	}
	return count;
}

//Returns the index where data is located in the List
//Calls the private helper function binarySearch to perform the search
//Pre: length != 0
//Pre: List is sorted (must test on a sorted list)
template <class listdata>
int List<listdata>::binarySearch(const listdata&data) {

	assert(length != 0);
	assert(isSorted());
	int low = 0;
	int high = length;
	return binarySearch(low, high, data);
}

//Corresponding Function in Private:
//Recursively search the list by dividing the search space in half
//Returns the index of the element, if it is found in the List
//Returns -1 if the element is not in the List
template <class listdata>
int List<listdata>::binarySearch(int& low, int& high, const listdata& data)
{
	if (high < low)//base case
		return -1;

	int mid = ((high - low) / 2) + low;
	advanceToIndex(mid);

	if (data == getIterator())
		return getIndex();
	else if (data < getIterator()) //search the left half
	{
		--mid;
		return binarySearch(low, mid, data);
	}
	else //search the right half
	{
		++mid;
		return binarySearch(mid, high, data); //step down
	}
} //O-time: worst,average: O(log(base2)n)

  //Searchs the list, element by element, from the start of the List to the end of the List
  //Returns the index of the element, if it is found in the List
  //Calls the above indexing functions in its implementation
  //Returns -1 if the element is not in the List
  //Pre: length != 0
template <class listdata>
int List<listdata>::linearSearch(const listdata& data) {

	beginIterator();//checks precondition
	for (int i = 1; i < length; i++)//offeset for begin function
	{
		if (getIterator() == data)
			return getIndex();
		advanceIterator();
	}
	return -1;
} //O-time: worst,average: O(n)

  /**Manipulation Procedures*/

  //Removes the value of the first element in the list
  //Precondition: List should not be empty
  //Postcondition: First item should be deleted with
  // head pointer reassigned to next item in list
template <class listdata>
void List<listdata>::deleteBegin() {
	assert(begin != NULL);
	if (length == 1) {
		delete begin;
		begin = end = NULL;
	}
	else {
		NodePtr previous = begin; //store this location so we don't lose access to it
		begin = begin->nextnode; //advance the pointer
		begin->previousnode = NULL;
		delete previous; //free the memory for the original begin node
	}
	length--;
}

//Removes the value of the last element in the list
//Precondition: List should not be empty
//Postcondition: Last item in list is deleted and next item
// in list is pointing to null
template <class listdata>
void List<listdata>::deleteEnd() {
	assert(end != NULL);
	if (length == 1) {
		delete end;
		begin = end = NULL;
	}
	else {
		NodePtr previous = end->previousnode;
		delete end; //free the memory for the original last node
		end = previous; //set the new end node
		end->nextnode = NULL; //so last->next is not pointing at freed memory
	}
	length--;
}

//Inserts a new element at the start of the list
//If the list is empty, the new element becomes both first and last
//Postcondition: head pointer points to inserted node. Inserted node's next
//pointer is pointing to null if no other item exists in list. If there other
// items the newly inserted item's next pointer is the address of
// the next item in list.
template <class listdata>
void List<listdata>::insertBegin(const listdata& val) {
	if (length == 0)//why is this necessary
	{
		begin = end = new Node(val);
	}
	else {
		NodePtr N = new Node(val);
		N->nextnode = begin;
		begin->previousnode = N;
		begin = N;
	}
	length++;
}

//Inserts a new element at the end of the list
//If the list is empty, the new element becomes both first and last
//Postcondition: node is inserted at the end of list with previous item in list
// pointing to newly inserted item's location and the new item's next pointer
// is pointed to NULL
template <class listdata>
void List<listdata>::insertEnd(const listdata& val) {
	if (length == 0) {
		begin = end = new Node(val);
	}
	else {
		NodePtr N = new Node(val);
		end->nextnode = N;
		N->previousnode = end;
		end = N;
	}
	length++;
}

//postcondition: moves the iterator to the start of the list
//precondition: list must not be NULL
template <class listdata>
void List<listdata>::beginIterator() {
	assert(length != 0);
	iterator = begin;
}

//Postcondition: removes the element currently pointed to by the iterator. Iterator then points to NULL.
//Precondition: list must not be empty, nor offEnd
template <class listdata>
void List<listdata>::deleteIterator() {
	assert(iterator != NULL);
	if (iterator == begin)
		deleteBegin();
	else if (iterator == end)
		deleteEnd();
	else
	{
		NodePtr Current = iterator;
		NodePtr Prev = iterator->previousnode;//GL
		NodePtr Nxt = iterator->nextnode;//GR
		iterator = Prev->nextnode = Nxt;//ASL,ASR,ASI
		Nxt->previousnode = Prev;//ANP
		delete Current;
		length--;
	}

}

//Postcondition: inserts an element after the node currently pointed to by the iterator
//Precondition: iterator must not be pointing to null, nor offEnd
template <class listdata>
void List<listdata>::insertIterator(const listdata& val) {
	assert(!offEnd());
	if (iterator == begin)
		insertBegin(val);
	else if (iterator == end)
		insertEnd(val);
	else
	{
		NodePtr N = new Node(val);
		N->previousnode = iterator;
		N->nextnode = iterator->nextnode;
		iterator->nextnode->previousnode = N;
		iterator->nextnode = N;
		length++;
	}
}

//Postcondition: iterator moved up by one node
//Precondition: iterator must not be pointing to null
template <class listdata>
void List<listdata>::advanceIterator() {

	assert(iterator != NULL);
	iterator = iterator->nextnode;
}

//Postcondition: iterator moved down by one node
//Precondition: iterator must not be pointing to null
template <class listdata>
void List<listdata>::reverseIterator() {
	assert(iterator != NULL);
	iterator = iterator->previousnode;
}

//Moves the iterator to the node whose index number is specified in the parameter
//Pre: length != 0
//Pre: index <= length
template <class listdata>
void List<listdata>::advanceToIndex(const int&indexnum) {
	assert(length != 0);
	assert(indexnum <= length);
	beginIterator();
	for (int i = 1; i < indexnum; i++)
		advanceIterator();
}


/**Additional List Operations*/

//Prints to the console the value of each element in the list sequentially
//and separated by a blank space
//Prints nothing if the list is empty
template <class listdata>
void List<listdata>::print() const
{
	NodePtr temp = begin; //create a temporary iterator
	while (temp != NULL) {

		//Add two lines of code here
		cout << temp->data << " ";
		temp = temp->nextnode;
		//Hint: One statement should contain a cout
	}
	cout << endl;
}

//Prints the contents of the linked list to the screen
//in the format #. <element> followed by a newline
template <class listdata>
void List<listdata>::printNumberedList() const
{
	NodePtr temp = begin; //create a temporary iterator
	int itemnum = 1;
	while (temp != NULL) {
		cout << itemnum << ". " << temp->data << endl;
		temp = temp->nextnode;
		itemnum++;
	}
	cout << endl;
}

//Post: returns a true if all items in the list are the same.
//Pre: list should be exact lengths
template <class listdata>
bool List<listdata>::operator==(const List<listdata> &obj) const {

	if (obj.length != length || end->data != obj.end->data || begin->data != obj.begin->data)
		return false;
	else//check contents
	{
		NodePtr temp = begin; //create a temporary iterator
		NodePtr temp2 = obj.begin;
		while (temp != NULL) {
			if (temp->data != temp2->data)
				return false;
			temp = temp->nextnode;
			temp2 = temp2->nextnode;
		}
		return true;
	}
}

//Wrapper function that calls the reverse helper function to print a list in reverse
//prints nothing if the List is empty
template <class listdata>
void List<listdata>::printReverse() const
{
	if (length == 0)
		cout << endl;
	else
	{
		reverse(begin);
		cout << endl;
	}
}

//Corresponding Function in Private:
//Helper function for the public printReverse() function.
//Recursively prints the data in a List in reverse.
template <class listdata>
void List<listdata>::reverse(const NodePtr& node) const
{
	if (node->nextnode == NULL)//last node to print
		cout << node->data << ' ';
	else
	{
		reverse(node->nextnode);//add to stack frame
		cout << node->data << ' '; //prints as the frame numbers collapse
	}
}

#endif /* LIST_H_ */
