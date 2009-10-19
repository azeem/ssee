#ifndef DATATYPES_H
#define DATATYPES_H

#include "Common.h"
#include <typeinfo>

//! CannotConvertToInt exceptions if thrown when an object
//! cannot be converted to an integer for some operation
class CannotConvertToInt: public BaseException {};

//! BaseObject is the base class for all DataTypes
class BaseObject : public gc {
	public:
		virtual string str() = 0;
		virtual bool is_callable();
		virtual long to_int();
};
inline bool BaseObject::is_callable() {return false;}
inline long BaseObject::to_int() {throw CannotConvertToInt();}

//! None object specifies null or void values
class None : public BaseObject {
	public:
		string str();
};
inline string None::str() {return "None";}

//! Cons object is a pair, a composite data type that can store
//! exactly two objects of any type.
class Cons : public BaseObject {
	private:
		BaseObject *first;
		BaseObject *second;
	 public:
		Cons();
		Cons(BaseObject *first, BaseObject *second) : first(first), second(second) {}
		string str();
		BaseObject *car();
		BaseObject *cdr();
		unsigned long list_length();
};
inline BaseObject *Cons::car() {return first;}  // Returns the first element
inline BaseObject *Cons::cdr() {return second;} // Returns the second element

//! Symbol Object represents symbols used as identifiers etc.
class Symbol : public BaseObject {
	private:
		string str_rep;
	public:
		Symbol(string str_rep) : str_rep(str_rep) {}
		string str();
		bool operator< (Symbol&);
		bool operator== (const char *);
};
inline string Symbol::str() {return str_rep;}

//! String represents variable length strings
class String : public BaseObject {
	private:
		string str_val;
	public:
		String(string str_val) : str_val(str_val) {}
		string get_string();
		string str();
};
inline string String::get_string() {return str_val;}

//! Integer Represents a signed long integer
class Integer : public BaseObject {
	private:
		long int_val;
	public:
		Integer(long int_val) : int_val(int_val) {}
		string str();
		long to_int();
};
inline long Integer::to_int() {return int_val;}

//! Boolean objects store a truth value ie. either true or false
class Boolean : public BaseObject {
	private:
		bool truth_val;
	public:
		Boolean(bool truth_val) : truth_val(truth_val) {}
		string str();
		bool truth();
		bool operator== (bool);
};
inline bool Boolean::truth() {return truth_val;}
#endif
