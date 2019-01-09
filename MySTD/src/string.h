#pragma once

#include <iostream>
#include <initializer_list>

#define MAX_STRING_LENGTH 1024

namespace mystd
{
	class string
	{
	public:
		//THIS IS NOT HOW ITERATORS WORK IN STD LIBRARY
		typedef char* iterator;
		typedef const char* const_iterator;
		

		static const size_t npos = -1;

	public:
		/* constructs an empty string with a length of 0.*/
		string();
		/* copies a c-string */
		string(const char* text);
		/* constructs a copy of text */
		string(const string& text);
		/* copies a postion of the string starting at the specified value of pos and spans the specified value of length (or until the end of the string if the string is too short or the length is string::npos.  */
		string(const string& text, size_t pos, size_t length = npos);
		/* copies the number of characters specified in length from the start of the string */
		string(const char* text, size_t length);
		/* copies each of the characters in the specified list */
		string(const std::initializer_list<char> list);
		/* destroys the string */
		~string();

		/* @return The number of characters in the string */
		inline size_t length() const { return m_BufferCount; }
		/* @return whether the string is empty */
		inline bool empty() const { return !m_BufferCount; }
		/* @return a pointer to the string's data */
		inline const char* data() const { return m_Buffer; }
		/* @return a c-string equivalent of the string */
		inline const char* c_str() const { return m_Buffer; }

		/* @return whether the string starts with a specified character */
		bool starts_with(char c) const;
		/* @return whether the string starts with a specified sequence of characters */
		bool starts_with(const string& charSeq) const;
		/* @return whether the string ends with a specified character */
		bool ends_with(char c) const;
		/* @return whether the string ends with a specified sequence of characters */
		bool ends_with(const string& charSeq) const;

		/* @return the position of the first instance of a specified charater starting at the index specified (index is 0 by default) */
		size_t index_of(char c, int index = 0) const;
		/* @return the position of the first instance of a specified sequence of characters starting at the index specified (index is 0 by default) */
		size_t index_of(const string& charSeq, int index = 0) const;
		/* @return the position of the last instance of a specified charater ending at the index specified (index is npos by default) */
		size_t last_index_of(char c, size_t index = mystd::string::npos) const;
		/* @return the position of the last instance of a specified sequence of charaters ending at the index specified (index is npos by default) */
		size_t last_index_of(const string& charSeq, size_t index = mystd::string::npos) const;

		/* @return a newly constructed string with its value being a copy of the characters between pos and length */
		string substr(size_t pos = 0, size_t length = npos) const;
		/* @return a newly constructed copy of the string with all characters in lower case (e.g. "AbCDe123" becomes "abcde123") */
		string to_lower() const;
		/* @return a newly constructed copy of the string with all characters in upper case (e.g. "AbCDe123" becomes "ABCDE123") */
		string to_upper() const;
		/* @return a newly constructed copy of the string where all blank spaces before and after the string are removed (e.g. "    hello world! " becomes "hello world!") */
		string trim() const;
		/* @return a newly constructed copy of the string where all the characters are in reverse order (e.g. "abcde123" becomes "321edcba") */
		string reverse() const;

		/* THIS NEEDS TO BE REDESIGNED, ITERATORS DONT WORK THIS WAY */
		iterator begin();
		/* THIS NEEDS TO BE REDESIGNED, ITERATORS DONT WORK THIS WAY */
		const_iterator begin() const;
		/* THIS NEEDS TO BE REDESIGNED, ITERATORS DONT WORK THIS WAY */
		iterator end();
		/* THIS NEEDS TO BE REDESIGNED, ITERATORS DONT WORK THIS WAY */
		const_iterator end() const;

		/* @return a reference to the character at the specified position in the string */
		char& at(size_t index);
		/* @return a const reference to the character at the specified position in the string */
		const char& at(size_t index) const;
		/* @return a reference to the character at the specified position in the string */
		char& operator[](size_t index);
		/* @return a const reference to the character at the specified position in the string */
		const char& operator[](size_t index) const;

		/* assigns a new value to the string, replacing its current value */
		string& operator=(const string& other);

		/* @return a newly constructed string with its value being a concatination of the two string specified */
		friend string operator+(const string& left, const string& right);
		/* @return whether the first string specified is greater than the second string specified (alphabetically) */
		friend bool operator>(const string& left, const string& right);
		/* @return whether the first string specified is less than the second string specified (alphabetically) */
		friend bool operator<(const string& left, const string& right);
		/* @return whether the first string specified is greater than or equal to the second string specified (alphabetically) */
		friend bool operator>=(const string& left, const string& right);
		/* @return whether the first string specified is less than or equal to the second string specified (alphabetically) */
		friend bool operator<=(const string& left, const string& right);
		/* @return whether the two strings specified have the same contents */
		friend bool operator==(const string& left, const string& right);
		/* @return whether the two strings specified do not have the same contents */
		friend bool operator!=(const string& left, const string& right);
		/* inserts the contents of the string into the ostream */
		friend std::ostream& operator<<(std::ostream& stream, const string& text);
		/* extracts a string from the istream and stores the sequence into the string specified. The extraction stops when a new line character ('\n') has been read. */
		friend std::istream& operator>>(std::istream& stream, string& obj);

	private:
		char* m_Buffer;
		size_t m_BufferCount;
	};
}