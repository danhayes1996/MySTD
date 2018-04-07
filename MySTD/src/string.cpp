#include "string.h"
#include <stdexcept>

mystd::string::string()
	: m_Buffer(nullptr), m_BufferCount(0)
{ }

mystd::string::string(const char* text)
{
	m_BufferCount = strlen(text);
	m_Buffer = new char[m_BufferCount + 1];
	memcpy(m_Buffer, text, m_BufferCount);
	m_Buffer[m_BufferCount] = 0;
}

mystd::string::string(const string& text)
{	
	m_BufferCount = text.length();
	m_Buffer = new char[m_BufferCount + 1];
	memcpy(m_Buffer, text.m_Buffer, m_BufferCount);
	m_Buffer[m_BufferCount] = 0;
}

mystd::string::~string()
{
	delete[] m_Buffer;
}

bool mystd::string::starts_with(char c) const
{
	return m_Buffer[0] == c;
}

bool mystd::string::starts_with(const string& charSeq) const
{
	for (size_t i = 0; i < charSeq.m_BufferCount; i++)
		if (m_Buffer[i] != charSeq.m_Buffer[i]) return false;
	return true;
}

bool mystd::string::ends_with(char c) const
{
	return m_Buffer[m_BufferCount - 1] == c;
}

bool mystd::string::ends_with(const string& charSeq) const
{
	for (size_t i = 0; i < charSeq.m_BufferCount; i++) 
		if (m_Buffer[m_BufferCount - charSeq.m_BufferCount + i] != charSeq[i]) return false;
	return true;
}

size_t mystd::string::index_of(char c, int index/* = 0*/) const
{
	for (size_t i = index; i < m_BufferCount; i++)
		if (m_Buffer[i] == c) return i;
	return npos;
}

size_t mystd::string::index_of(const string& charSeq, int index/* = 0*/) const
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

size_t mystd::string::last_index_of(char c, size_t index/* = npos*/) const
{
	if (index >= m_BufferCount) index = m_BufferCount;
	for (int i = index; i >= 0; i--)
		if (m_Buffer[i] == c) return i;
	return mystd::string::npos;
}

size_t mystd::string::last_index_of(const string& charSeq, size_t index/* = npos*/) const
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


mystd::string mystd::string::substr(size_t pos/* = 0*/, size_t length/* = npos*/) const
{
	if (pos >= m_BufferCount) throw std::out_of_range("pos is greater than the string length");
	if (length >= m_BufferCount) length = m_BufferCount;
	if (pos > length) return string();
	
	char* buffer = new char[length - pos + 1];
	for (size_t i = 0; i < length - pos; i++)
		buffer[i] = m_Buffer[i + pos];
	buffer[length - pos] = 0;

	string res = buffer;
	delete[] buffer;
	return res;
}

mystd::string mystd::string::to_lower() const
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

mystd::string mystd::string::to_upper() const
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

mystd::string mystd::string::trim() const
{
	int start = 0, end = m_BufferCount - 1;
	while (m_Buffer[start] == ' ') start++;
	while (m_Buffer[end] == ' ') end--;
	return substr(start, end + 1);
}

mystd::string mystd::string::reverse() const
{
	char* buffer = new char[m_BufferCount + 1];
	for (size_t i = 0; i < m_BufferCount; i++)
		buffer[i] = m_Buffer[m_BufferCount - i - 1];

	buffer[m_BufferCount] = 0;
	string res = buffer;
	delete[] buffer;
	return res;
}

char& mystd::string::at(size_t index)
{
	if(index >= m_BufferCount) throw std::out_of_range("index is greater than the string length");
	return m_Buffer[index];
}

const char& mystd::string::at(size_t index) const
{
	if (index >= m_BufferCount) throw std::out_of_range("index is greater than the string length");
	return m_Buffer[index];
}

char& mystd::string::operator[](size_t index)
{
	return at(index);
}

const char& mystd::string::operator[](size_t index) const
{
	return at(index);
}

mystd::string mystd::operator+(const mystd::string& left, const mystd::string& right)
{
	char* buffer = new char[left.m_BufferCount + right.m_BufferCount + 1];

	for (size_t i = 0; i < left.m_BufferCount; i++)
		buffer[i] = left.m_Buffer[i];

	for (size_t i = 0; i < right.m_BufferCount; i++)
		buffer[left.m_BufferCount + i] = right.m_Buffer[i];

	buffer[left.m_BufferCount + right.m_BufferCount] = 0;
	string res = mystd::string(buffer);
	delete[] buffer;
	return res;
}

//alphabetical > operator
bool mystd::operator>(const string& left, const string& right)
{
	for (size_t i = 0; i < left.m_BufferCount; i++)
		if (left.m_Buffer[i] > right.m_Buffer[i]) return true;
	return false;
}

bool mystd::operator<(const string& left, const string& right)
{
	for (size_t i = 0; i < left.m_BufferCount; i++)
		if (left.m_Buffer[i] < right.m_Buffer[i]) return true;
	return false;
}

bool mystd::operator>=(const string& left, const string& right)
{
	return !(left < right);
}

bool mystd::operator<=(const string& left, const string& right)
{
	return !(left > right);
}

bool mystd::operator==(const mystd::string& left, const  mystd::string& right)
{
	if (left.m_BufferCount != right.m_BufferCount) return false;
	for (size_t i = 0; i < left.m_BufferCount; i++)
		if (left[i] != right[i]) return false;
	return true;
}

bool mystd::operator!=(const mystd::string& left, const  mystd::string& right)
{
	return !(right == left);
}

std::ostream& mystd::operator<<(std::ostream& stream, const mystd::string& text)
{
	 return stream << text.m_Buffer;
}

std::istream& mystd::operator>>(std::istream& stream, mystd::string& obj)
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