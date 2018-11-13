// Adapted from C16:TPStash2.h on pg.733 of "Thinking in C++" by Bruce Eckel
/*
Title: TemplateBasics.cpp
Description: Uses the Standard C++ Library vector as an underlying implementation to create 
	     a Set template class that accepts only one of each type of object that is put 
	     into it. Makes a nested iterator class that supports the “end sentinel” 
	     concept. Includes test code in main(), using both the program Set template class 
	     and the Standard C++ Library set template to verify that the behaviour is correct.
Date: March 28th, 2015
Author: Dan Bonham
Version: 1.0
Copyright: 2015 Daniel R. Bonham
*/

// Program written exclusively using information from "Thinking in C++" by Bruce Eckel
#include <vector> // vector used as container in custom set
#include <iostream> // Stream declarations
#include <set> // C++ library set
using namespace std;

template<class T> class Set { // Custom set class
	vector<T> v; // used as underlying container for custom set
public:
	Set() {} // constructor
	~Set() {} // deconstructor
	void insert(T element); // add an element to the set
	bool empty() const; // check whether set is empty
	int size() const; // check size of set
	int find(T element) const; // find where element is in set
	void erase(T element); // erase element from set
	//Nested iterator class
	class iterator; // Declaration required
	friend class iterator; // Make it a friend
	class iterator { // Define Iterator class
		Set& s; // set reference iterator is implemented on
		int index; // current position of iterator
	public:
		iterator(Set& set) : s(set), index(0) {} // constructor
		iterator(Set& set, bool) : s(set), index(s.v.size()) {} // creates end sentinel
		iterator(const iterator& rv) : s(rv.s), index(rv.index) {} // Copy-constructor
		iterator& operator=(const iterator& rv) { // assignment
			s = rv.s;
			index = rv.index;
			return *this;
		}
		iterator& operator++() {
			if(++index <= s.v.size())
				return *this;
		}
		iterator& operator++(int) { return operator++(); } // 
		iterator& operator--() {
			if(--index >= 0)
				return *this;
		}
		iterator& operator--(int) { return operator--(); }
		iterator& operator+=(int amount) {
			if(index + amount < s.v.size() && index + amount >= 0) {
				index += amount;
				return *this;
			}
		}
		iterator& operator-=(int amount) {
			if(index - amount < s.v.size() && index - amount >= 0) {
				index -= amount;
				return *this;
			}
		}
		iterator operator+(int amount) const {
			iterator ret(*this);
			ret += amount; // op+= does bounds check
			return ret;
		}
		T current() const { return s.v.at(index); }
		T operator*() const { return current(); }
		T operator->() const {
			if(s.v.at(index) != 0)
				return current();
		}
		T remove() { return s.v.erase(index); }
		bool operator==(const iterator& rv) const { return index == rv.index; }
		bool operator!=(const iterator& rv) const { return index != rv.index; }
	};
	iterator begin() { return iterator(*this); }
	iterator end() { return iterator(*this, true); }
};
template<class T>
void Set<T>::insert(T element) { // inserts element if not already in set
	bool contained; // used to test whether element already in set
	for(int i = 0; i < v.size(); i++) { // loops through set
		if(element == v.at(i)) { // tests for prior inclusion
			contained = true; // flags boolean if identical element found
		}
	}
	if(contained == false) // if element unique to set, it is added
		v.push_back(element);
	//else
		//cout << "Already in set" << endl;
}
template<class T>
bool Set<T>::empty() const { // tests whether set is empty
	if(v.size() == 0)
		return true;
	else
		return false;
}
template<class T>
int Set<T>::size() const { // returns size of set
	return v.size();
}
template<class T>
int Set<T>::find(T element) const { // returns where in set element resides
	for(int i = 0; i < (v.size()); i++) {
		if(v[i] == element)
			return i;
	}
	return -1;
}
template<class T>
void Set<T>::erase(T element) { // removes specified element from set
	for(int i = 0; i < (v.size()); i++) { // loops through set
		if(v[i] == element) // finds element in set
			v.erase(v.begin()+i); // erases element
	}
}


int main() {
	Set<int> set; // custom set
	std::set<int> libSet; // C++ library set
	cout << "Custom Set Empty: " << set.empty() << endl; // displays result of empty on custom
	cout << "Library Set Empty: " << libSet.empty() << endl; // displays result of empty on library
	cout << "Custom Set Size: " << set.size() << endl; // displays result of size on custom
	cout << "Library Set Size: " << libSet.size() << endl; // displays result of size on library
	for(int i = 0; i < 10; i++) { // adds elements to each set
		set.insert(i); // tests insert
		libSet.insert(i); // compares insert to Library set
	}
	cout << "Custom Set Empty: " << set.empty() << endl; // displays result of empty on custom
	cout << "Library Set Empty: " << libSet.empty() << endl; // displays result of empty on library
	cout << "Custom Set Size: " << set.size() << endl; // displays result of size on custom
	cout << "Library Set Size: " << libSet.size() << endl; // displays result of size on library
	set.insert(8); // tries to insert already existing element to custom
	libSet.insert(8); // tries to insert already existing element to library
	cout << "Custom Set Size (after redundant insert attempt): " << set.size() << endl; // displays result of size on custom
	cout << "Library Set Size (after redundant insert attempt): " << libSet.size() << endl; // displays result of size on library
	set.erase(7); // removes from custom
	libSet.erase(7); // removes from library
	set.erase(10); // tries to remove non-existant object from custom
	libSet.erase(10); // tries to remove non-existant object from library
	// first test of nested iterator and displays identical output of compared sets
	Set<int>::iterator it = set.begin(); // creates iterator at beginning of custom set
	for(it = set.begin(); it != set.end(); it++) // iterates until end sentinel
		cout << "Custom set: " << *it << endl; // displays result
	std::set<int>::iterator libIt = libSet.begin(); // creates iterator at beginning of library set
	for(libIt = libSet.begin(); libIt != libSet.end(); libIt++)
		cout << "Library set: " << *libIt << endl;
	it = set.begin(); // resets iterator to beginning of set
	it += 5; // tests overloaded addition operator (moves iterator up 5 spots in set)
	for(it; it != set.end(); it++) { // displays correct result after operation
		cout << "Custom set: " << *it << endl;
	}
}