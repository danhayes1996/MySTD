#include "string.h"
#include <stdexcept>

namespace mystd {

	string::string()
	{
		m_BufferCount = 0;
		m_Buffer = new char[1];
		m_Buffer[0] = 0;
	}

	string::string(const char* text)
	{
		m_BufferCount = strlen(text);
		m_Buffer = new char[m_BufferCount + 1];
		memcpy(m_Buffer, text, m_BufferCount);
		m_Buffer[m_BufferCount] = 0;
	}

	string::string(const string& text)
		: string(text.m_Buffer)
	{
	}

	string::string(const string& text, size_t pos, size_t length/* = npos*/)
	{
		*this = text.substr(pos, length);
	}

	string::string(const char* text, size_t length)
		: m_Buffer(new char[length + 1]), m_BufferCount(length)
	{
		memcpy(m_Buffer, text, m_BufferCount);
		m_Buffer[m_BufferCount] = 0;
	}

	string::string(const std::initializer_list<char> list)
		: m_Buffer(new char[list.size() + 1]), m_BufferCount(list.size())
	{
		for (unsigned int i = 0; i < list.size(); i++)
			m_Buffer[i] = *(list.begin() + i);
		m_Buffer[m_BufferCount] = 0;
	}

	string::~string()
	{
		delete[] m_Buffer;
	}

	bool string::starts_with(char c) const
	{
		return m_Buffer[0] == c;
	}

	bool string::starts_with(const string& charSeq) const
	{
		for (size_t i = 0; i < charSeq.m_BufferCount; i++)
			if (m_Buffer[i] != charSeq.m_Buffer[i]) return false;
		return true;
	}

	bool string::ends_with(char c) const
	{
		return m_Buffer[m_BufferCount - 1] == c;
	}

	bool string::ends_with(const string& charSeq) const
	{
		for (size_t i = 0; i < charSeq.m_BufferCount; i++)
			if (m_Buffer[m_BufferCount - charSeq.m_BufferCount + i] != charSeq[i]) return false;
		return true;
	}

	bool string::is_alpha() const
	{
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] < 'A'
				|| (m_Buffer[i] > 'Z' && m_Buffer[i] < 'a')
				|| m_Buffer[i] > 'z')
				return false;
		}
		return true;
	}

	bool string::is_numeric() const
	{
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] < '0' || m_Buffer[i] > '9')
				return false;
		}
		return true;
	}

	bool string::is_alphanumeric() const
	{
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] < '0'
				|| (m_Buffer[i] > '9' && m_Buffer[i] < 'A')
				|| (m_Buffer[i] > 'Z' && m_Buffer[i] < 'a')
				|| m_Buffer[i] > 'z')
				return false;
		}
		return true;
	}

	size_t string::index_of(char c, int index/* = 0*/) const
	{
		for (size_t i = index; i < m_BufferCount; i++)
			if (m_Buffer[i] == c) return i;
		return npos;
	}

	size_t string::index_of(const string& charSeq, int index/* = 0*/) const
	{
		for (size_t i = index; i < m_BufferCount; i++)
		{
			bool found = true;
			for (size_t j = 0; j < charSeq.m_BufferCount; j++)
			{
				if (m_Buffer[i + j] != charSeq.m_Buffer[j])
				{
					found = false;
					break;
				}
			}
			if (found) return i;
		}
		return npos;
	}

	size_t string::last_index_of(char c, size_t index/* = npos*/) const
	{
		if (index >= m_BufferCount) index = m_BufferCount;
		for (int i = index; i >= 0; i--)
			if (m_Buffer[i] == c) return i;
		return string::npos;
	}

	size_t string::last_index_of(const string& charSeq, size_t index/* = npos*/) const
	{
		if (index >= m_BufferCount) index = m_BufferCount;
		for (int i = index - charSeq.m_BufferCount; i >= 0; i--)
		{
			bool found = true;
			for (size_t j = 0; j < charSeq.m_BufferCount; j++)
			{
				if (m_Buffer[i + j] != charSeq.m_Buffer[j])
				{
					found = false;
					break;
				}
			}
			if (found) return i;
		}
		return npos;
	}

	size_t string::occurrences(char c, size_t index/* = 0*/) const
	{
		size_t cnt = 0;
		for (size_t i = index; i < m_BufferCount; i++)
			if (m_Buffer[i] == c) cnt++;
		return cnt;
	}

	size_t string::occurrences(const string& charSeq, size_t index/* = 0*/) const
	{
		if (charSeq.m_BufferCount == 0
			|| m_BufferCount == 0
			|| m_BufferCount < charSeq.m_BufferCount)
			return 0;

		size_t cnt = 0;
		for (size_t i = index; i < m_BufferCount - charSeq.m_BufferCount; i++)
		{
			bool found = true;
			for (size_t j = 0; j < charSeq.m_BufferCount; j++)
			{
				if (m_Buffer[i + j] != charSeq.m_Buffer[j])
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				cnt++;
				i += charSeq.m_BufferCount - 1; //extra 1 gets added at the start of the next loop
			}
		}
		return cnt;
	}

	string string::substr(size_t pos/* = 0*/, size_t length/* = npos*/) const
	{
		if (pos >= m_BufferCount) throw std::out_of_range("pos is greater than the string length");
		if (length >= m_BufferCount) length = m_BufferCount - pos;
		if (length == 0) return string();

		char* buffer = new char[length + 1];
		for (size_t i = 0; i < length; i++)
			buffer[i] = m_Buffer[pos + i];
		buffer[length] = 0;

		string res = buffer;
		delete[] buffer;
		return res;
	}

	string string::to_lower() const
	{
		char* buffer = new char[m_BufferCount + 1];
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] >= 'A' && m_Buffer[i] <= 'Z') buffer[i] = m_Buffer[i] + 32;
			else buffer[i] = m_Buffer[i];
		}

		buffer[m_BufferCount] = 0;
		string res = buffer;
		delete[] buffer;
		return res;
	}

	string string::to_upper() const
	{
		char* buffer = new char[m_BufferCount + 1];
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] >= 'a' && m_Buffer[i] <= 'z') buffer[i] = m_Buffer[i] - 32;
			else buffer[i] = m_Buffer[i];
		}

		buffer[m_BufferCount] = 0;
		string res = buffer;
		delete[] buffer;
		return res;
	}

	string string::to_proper() const
	{
		char* buffer = new char[m_BufferCount + 1];
		bool prevIsSpace = true;
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] == ' ')
			{
				prevIsSpace = true;
				buffer[i] = m_Buffer[i];
			}
			else if (m_Buffer[i] >= 'a' && m_Buffer[i] <= 'z' && prevIsSpace)
			{
				buffer[i] = m_Buffer[i] - 32;
				prevIsSpace = false;
			}
			else
			{
				buffer[i] = m_Buffer[i];
				prevIsSpace = false; //for cases where the first character in a word isnt a letter (e.g. "123abc")
			}
		}

		buffer[m_BufferCount] = 0;
		string res = buffer;
		delete[] buffer;
		return res;
	}

	string string::reverse() const
	{
		char* buffer = new char[m_BufferCount + 1];
		for (size_t i = 0; i < m_BufferCount; i++)
			buffer[i] = m_Buffer[m_BufferCount - i - 1];

		buffer[m_BufferCount] = 0;
		string res = buffer;
		delete[] buffer;
		return res;
	}

	string string::trim() const
	{
		int start = 0, end = m_BufferCount - 1;
		while (m_Buffer[start] == ' ') start++;
		while (m_Buffer[end] == ' ') end--;
		return substr(start, end + 1);
	}

	string string::unique(bool keepSpaces /*= true*/) const
	{
		char* str = new char[m_BufferCount + 1];
		size_t index = 0; //keep track of index of str (str[index])
		
		for (int i = 0; i < (int)m_BufferCount; i++)
		{
			bool isDuplicate = false;
			if ((keepSpaces && m_Buffer[i] != ' ') || !keepSpaces)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					if (m_Buffer[i] == m_Buffer[j])
					{
						isDuplicate = true;
						break;
					}
				}
			}
			if (!isDuplicate) str[index++] = m_Buffer[i];
		}

		str[index] = 0;
		string res = str;
		delete[] str;
		return res;
	}

	void string::clear()
	{
		delete[] m_Buffer;
		m_Buffer = new char[1];
		m_Buffer[0] = 0;
		m_BufferCount = 0;
	}

	size_t string::words() const
	{
		size_t cnt = 0;
		bool prevIsSpace = true;
		for (size_t i = 0; i < m_BufferCount; i++)
		{
			if (m_Buffer[i] == ' ')
			{
				prevIsSpace = true;
			}
			else if (m_Buffer[i] != ' ' && prevIsSpace)
			{
				cnt++;
				prevIsSpace = false;
			}
		}
		return cnt;
	}

	arraylist<string> string::split(char c /*= ' '*/) const
	{
		arraylist<string> list(occurrences(c));
		size_t from = 0;
		size_t to = index_of(c);
		do
		{
			if (m_Buffer[from] != c) list.push_back(substr(from, to - from));
			from = to + 1;
			to = index_of(c, from);
		} while (to != -1);
		//add the rest of the string to the list if the last character isnt the same as c.
		if (m_Buffer[m_BufferCount - 1] != c) list.push_back(substr(last_index_of(c) + 1));
		return list;
	}

	string string::hex() const
	{
		//credit for this function goes to fredoverflow for their answer here: https://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa
		static const char* hex_vals = "0123456789ABCDEF";
		char* buffer = new char[m_BufferCount * 3]; //each character will have 2 characters (from hex_vals) followed by a space (last space will be replaced with null)
		size_t index = 0; //current index in the buffer above

		for (size_t i = 0; i < m_BufferCount; i++)
		{
			char c = m_Buffer[i];
			buffer[index++] = hex_vals[c >> 4];
			buffer[index++] = hex_vals[c & 15];
			buffer[index++] = ' ';
		}
		buffer[m_BufferCount * 3 - 1] = 0;
		string res = buffer;
		delete[] buffer;
		return res;
	}

	string string::binary() const
	{
		char* buffer = new char[m_BufferCount * 9]; //each character will have 8 numbers (1 or 0) followed by a space (last space will be replaced with null)
		string temp = m_Buffer;	//edit a copy of this string instead of the actual one
		size_t index = 0;       //current index in the buffer above

		for (size_t i = 0; i < m_BufferCount; i++)
		{
			for (int b = 128; b > 0; b /= 2)
			{
				if (temp.m_Buffer[i] - b >= 0)
				{
					buffer[index++] = '1';
					temp.m_Buffer[i] -= b;
				}
				else
				{
					buffer[index++] = '0';
				}
			}
			buffer[index++] = ' ';
		}
		buffer[m_BufferCount * 9 - 1] = 0;
		string res = buffer;
		delete[] buffer;
		return res;
	}

	string::iterator string::begin()
	{
		return &m_Buffer[0];
	}

	string::const_iterator string::begin() const
	{
		return &m_Buffer[0];
	}

	string::const_iterator string::cbegin() const
	{
		return &m_Buffer[0];
	}

	string::reverse_iterator string::rbegin()
	{
		return &m_Buffer[m_BufferCount - 1];
	}

	string::const_reverse_iterator string::crbegin() const
	{
		return &m_Buffer[m_BufferCount - 1];
	}

	string::iterator string::end()
	{
		return &m_Buffer[m_BufferCount];
	}

	string::const_iterator string::end() const
	{
		return &m_Buffer[m_BufferCount];
	}

	string::const_iterator string::cend() const
	{
		return &m_Buffer[m_BufferCount];
	}

	string::reverse_iterator string::rend()
	{
		return &m_Buffer[-1];
	}

	string::const_reverse_iterator string::crend() const
	{
		return &m_Buffer[-1];
	}

	char& string::at(size_t index)
	{
		if (index >= m_BufferCount) throw std::out_of_range("index is greater than the string length");
		return m_Buffer[index];
	}

	const char& string::at(size_t index) const
	{
		if (index >= m_BufferCount) throw std::out_of_range("index is greater than the string length");
		return m_Buffer[index];
	}

	char& string::operator[](size_t index)
	{
		return at(index);
	}

	const char& string::operator[](size_t index) const
	{
		return at(index);
	}

	string& string::operator=(const string& other)
	{
		delete[] m_Buffer;

		m_BufferCount = other.m_BufferCount;
		m_Buffer = new char[m_BufferCount + 1];
		memcpy(m_Buffer, other.m_Buffer, m_BufferCount);
		m_Buffer[m_BufferCount] = 0;

		return *this;
	}

	string operator+(const string& left, const string& right)
	{
		char* buffer = new char[left.m_BufferCount + right.m_BufferCount + 1];

		for (size_t i = 0; i < left.m_BufferCount; i++)
			buffer[i] = left.m_Buffer[i];

		for (size_t i = 0; i < right.m_BufferCount; i++)
			buffer[left.m_BufferCount + i] = right.m_Buffer[i];

		buffer[left.m_BufferCount + right.m_BufferCount] = 0;
		string res = string(buffer);
		delete[] buffer;
		return res;
	}

	//alphabetical > operator
	bool operator>(const string& left, const string& right)
	{
		for (size_t i = 0; i < left.m_BufferCount; i++)
			if (left.m_Buffer[i] > right.m_Buffer[i]) return true;
		return false;
	}

	bool operator<(const string& left, const string& right)
	{
		for (size_t i = 0; i < left.m_BufferCount; i++)
			if (left.m_Buffer[i] < right.m_Buffer[i]) return true;
		return false;
	}

	bool operator>=(const string& left, const string& right)
	{
		return !(left < right);
	}

	bool operator<=(const string& left, const string& right)
	{
		return !(left > right);
	}

	bool operator==(const string& left, const  string& right)
	{
		if (left.m_BufferCount != right.m_BufferCount) return false;
		for (size_t i = 0; i < left.m_BufferCount; i++)
			if (left[i] != right[i]) return false;
		return true;
	}

	bool operator!=(const string& left, const  string& right)
	{
		return !(right == left);
	}

	std::ostream& operator<<(std::ostream& stream, const string& text)
	{
		return stream << text.m_Buffer;
	}

	std::istream& operator>>(std::istream& stream, string& obj)
	{
		char* buffer = new char[MAX_STRING_LENGTH];
		stream.getline(buffer, MAX_STRING_LENGTH, '\n');

		//set obj data
		obj.m_BufferCount = strlen(buffer);
		obj.m_Buffer = new char[obj.m_BufferCount + 1];
		memcpy(obj.m_Buffer, buffer, obj.m_BufferCount);
		obj.m_Buffer[obj.m_BufferCount] = 0;

		delete[] buffer;
		return stream;
	}
}