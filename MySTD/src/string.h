#pragma once

#include <iostream>

#define MAX_STRING_LENGTH 1024

namespace mystd
{
	class string
	{
	public:
		static const size_t npos = -1;
	
	private:
		char* m_Buffer;
		size_t m_BufferCount;

	public:
		string();
		string(const char* text);
		string(const string& text);
		~string();

		inline size_t length() const { return m_BufferCount; }
		inline bool empty() const { return !m_BufferCount; }
		inline const char* c_str() const { return m_Buffer; }

		bool starts_with(char c) const;
		bool starts_with(const string& charSeq) const;
		bool ends_with(char c) const;
		bool ends_with(const string& charSeq) const;

		size_t index_of(char c, int index = 0) const;
		size_t index_of(const string& charSeq, int index = 0) const;
		size_t last_index_of(char c, size_t index = mystd::string::npos) const;
		size_t last_index_of(const string& charSeq, size_t index = mystd::string::npos) const;

		string substr(size_t pos = 0, size_t length = npos) const;
		string to_lower() const;
		string to_upper() const;
		string trim() const;
		string reverse() const;

		char& at(size_t index);
		const char& at(size_t index) const;
		char& operator[](size_t index);
		const char& operator[](size_t index) const;

		friend string operator+(const string& left, const string& right);
		friend bool operator>(const string& left, const string& right);
		friend bool operator<(const string& left, const string& right);
		friend bool operator>=(const string& left, const string& right);
		friend bool operator<=(const string& left, const string& right);
		friend bool operator==(const string& left, const string& right);
		friend bool operator!=(const string& left, const string& right);
		friend std::ostream& operator<<(std::ostream& stream, const string& text);
		friend std::istream& operator>>(std::istream& stream, string& obj);
	};
}