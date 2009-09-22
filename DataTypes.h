#ifndef DATATYPES_H
#define DATATYPES_H

#include "Common.h"

class BaseObject : public gc {
// Base Class for all DataTypes
	public:
		virtual string str() = 0;
};

class None : public BaseObject {
// None object specifies null or void values
	public:
		string str();
};

inline string None::str() {return "None";}

class Cons : public BaseObject {
// Cons object is a pair, a composite data type that can store
// exactly two objects of any type.
	private:
		BaseObject *first;
		BaseObject *second;
	 public:
		Cons();
		Cons(BaseObject*, BaseObject*);
		string str();
		BaseObject *car();
		BaseObject *cdr();
		unsigned long list_length();
};

inline BaseObject *Cons::car() {return first;}  // Returns the first element
inline BaseObject *Cons::cdr() {return second;} // Returns the second element

class Symbol : public BaseObject {
// Symbol Object represents symbols used as identifiers etc.
	private:
		string str_rep;
	public:
		Symbol(string);
		string str();
		bool operator< (Symbol&);
		bool operator== (const char *);
};

class String : public BaseObject {
// String represents variable length strings
	private:
		string str_val;
	public:
		String(string);
		string str();
};

class Integer : public BaseObject {
// Represents a signed long integer
	private:
		long int_val;
	public:
		Integer(long);
		string str();
};

class Boolean : public BaseObject {
	private:
		bool truth_val;
	public:
		Boolean(bool);
		string str();
		bool truth();
		bool operator== (bool);
};
#endif
