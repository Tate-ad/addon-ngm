/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * String.cpp
 * 描述：从std::string继承过来的字符串类，主要是添加一些std::string没有的功能
 *
 * 版本：1.0
 * 创建时间: Apr 28, 2015
 * 作者: ubuntukylin
 */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "String.h"

void String::trim(char pattern)
{
	std::string::size_type pos = find_last_not_of(pattern);
	if (pos != std::string::npos)
	{
		erase(pos + 1);
		pos = find_first_not_of(pattern);
		if (pos != std::string::npos)
			erase(0, pos);
	}
	else
	{
		erase(begin(), end());
	}
}

void String::ltrim(const String& pattern)
{
	std::string::size_type nIndex = std::string::npos;

	for (std::string::size_type i=0; i<this->size(); i++)
	{
		if (std::string::npos == pattern.find(this->at(i)))
		{
			break;
		}

		nIndex = i + 1;
	}

	if (std::string::npos != nIndex)
		this->erase(0, nIndex);
}

void String::rtrim(const String& pattern)
{
	long nIndex = -1;

	for (long i=this->size() - 1; i>=0; i--)
	{
		if (std::string::npos == pattern.find(this->at((std::string::size_type)i)))
		{
			break;
		}

		nIndex = i;
	}

	if (-1 != nIndex)
		this->erase(nIndex);
}

void String::trim(const String &pattern)
{
	ltrim(pattern);
	rtrim(pattern);
}

std::vector<String> String::split(const String &pattern, bool merge) const
{
	std::string::size_type pos;
	std::vector<String> result;
	std::string::size_type size = 0;
	String sSub;
	String sSrc = *this + pattern;//扩展字符串以方便操作

	size = sSrc.size();

	for (std::string::size_type i = 0; i < size; i++)
	{
		pos = sSrc.find(pattern, i);
		if (pos < size)
		{
			sSub = sSrc.substr(i, pos - i);
			sSub.trim(' ');

			if (!merge || (merge && !sSub.empty()))
				result.push_back(sSub);

			i = pos + pattern.size() - 1;
		}
	}

	return result;
}

bool String::compareNoCase(const String &other, int len) const
{
	std::string::const_iterator i1 = this->begin();
	std::string::const_iterator i2 = other.begin();
	int nIndex = 0;

	//遍历对比每个字符
	while (i1 != this->end() && i2 != other.end() && toupper(*i1) == toupper(*i2))
	{
		if (-1 != len)
		{
			nIndex ++;
			if (nIndex == len)
				return true;
		}

		++ i1;
		++ i2;
	}
	//如果str1到结尾，str2也到结尾则相等
	if (i1 == this->end() && i2 == other.end() && -1 == len)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::rcompareNoCase(const String& other, int len) const
{
	std::string::const_reverse_iterator i1 = this->rbegin();
	std::string::const_reverse_iterator i2 = other.rbegin();
	int nIndex = 0;

	//遍历对比每个字符
	while (i1 != this->rend() && i2 != other.rend() && toupper(*i1) == toupper(*i2))
	{
		if (-1 != len)
		{
			nIndex ++;
			if (nIndex == len)
				return true;
		}

		++ i1;
		++ i2;
	}
	//如果str1到结尾，str2也到结尾则相等
	if (i1 == this->rend() && i2 == other.rend() && -1 == len)
	{
		return true;
	}
	else
	{
		return false;
	}
}

String String::right(int size) const
{
	if (-1 == size)
		return this->substr(0, size);
	else
		return this->substr(this->length() - size, size);
}

String& String::toUpper()
{
	std::string::iterator i = this->begin();
	for (; i!=this->end(); ++i)
		if (isalpha(*i) && islower(*i))
			*i = toupper(*i);

	return *this;
}

String& String::toLower()
{
	std::string::iterator i = this->begin();
	for (; i!=this->end(); ++i)
		if (isalpha(*i) && isupper(*i))
			*i = tolower(*i);

	return *this;
}

std::wstring String::toWString() const
{
	std::wstring value;
	size_t wslen = 0;

	wslen = mbstowcs(0, this->c_str(), 0);

	if (wslen == (size_t)(-1))
		return value;

	value.resize(wslen);
	mbstowcs(&value[0], this->c_str(), wslen);

	return value;
}

String& String::fromWString(const std::wstring &value)
{
	size_t slen = 0;

	this->clear();

	slen = wcstombs(0, value.c_str(), 0);
	//slen = wcslen(value.c_str()) * sizeof(wchar_t);
	if (slen == (size_t)(-1))
		return *this;

	this->resize(slen);

	wcstombs(&(*this)[0], value.c_str(), slen);

	return *this;
}

String& String::format(const char *format, ...)
{
	int nSize = 100;
	char *sBuffer = 0;
    int nLen = -1;

    *this = "";

    if (0 == format)
    	return *this;

    va_list ap;
    try
    {
    	do
    	{
    	    va_start(ap, format);

    		nSize *= 2;
    		delete[] sBuffer;
    		sBuffer = new char[nSize];
    		memset(sBuffer, '\0', nSize);

        	nLen = vsnprintf(sBuffer, nSize - 1, format, ap);

            va_end(ap);

        	if (-1 == nLen)
        		break;
    	} while (nLen >= nSize - 1);
    }
    catch (...)
    {
    	nLen = -1;
        //std::cout << "ERROR: format the string failed..." << std::endl;
    }

    if (nLen != -1)
    	*this = sBuffer;

    delete[] sBuffer;

    return *this;
}

String& String::appendFormat(const char *format, ...)
{
	int nSize = 100;
	char *sBuffer = 0;
    int nLen = -1;

    if (0 == format)
    	return *this;

    va_list ap;
    try
    {
    	do
    	{
    	    va_start(ap, format);

    		nSize *= 2;
    		delete[] sBuffer;
    		sBuffer = new char[nSize];
    		memset(sBuffer, 0x00, nSize);

        	nLen = vsnprintf(sBuffer, nSize - 1, format, ap);

            va_end(ap);

            if (-1 == nLen)
            	break;

    	} while (nLen >= nSize - 1);
    }
    catch (...)
    {
    	nLen = -1;
        //std::cout << "ERROR: format the string failed..." << std::endl;
    }

    if (nLen != -1)
    	*this += sBuffer;

    delete[] sBuffer;

    return *this;
}

String& String::replace(const String &src, const String &dst)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = src.size();
	std::string::size_type dstlen = dst.size();

	while ((pos = this->std::string::find(src.toStdStr(), pos)) != std::string::npos)
	{
		this->std::string::replace(pos, srclen, dst);
		pos += dstlen;
	}

	return *this;
}

bool String::isDigit() const
{
	std::string::const_iterator i = this->begin();
	for (; i!=this->end(); ++i)
	{
		if (!isdigit(*i))
			return false;
	}

	return true;
}

bool String::isDigit2() const
{
	std::string::const_iterator i = this->begin();
	for (; i!=this->end(); ++i)
	{
		if (!isdigit(*i) && *i != '-' && *i != '+' && *i != 'e' && *i != 'E' && *i != '.')
			return false;
	}

	return true;
}
