/*
 * Copyright (c) 2015（年）,北京蓝威技术有限公司
 * All rights reserved.
 * String.h
 * 描述：从std::string继承过来的字符串类，主要是添加一些std::string没有的功能
 *
 * 版本：1.0
 * 创建时间: Apr 28, 2015
 * 作者: ubuntukylin
 */

#ifndef LANWEI_STRING_H_
#define LANWEI_STRING_H_

#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <limits>

class String : public std::string
{
public:
	String() : std::string() {}
	virtual ~String() {}
	String(const String& other) : std::string(other) {}
	String(const std::string &str) : std::string(str) {}
	String(const char *str) : std::string() { if (str) this->assign(str); }
	String(const char ch) : std::string() { this->assign(1, ch); }
	String& operator=(const String& other) { this->assign(other); return *this; }
	String& operator=(const std::string& str) { this->assign(str); return *this; }
	String& operator=(const char* str) { if (str) this->assign(str); else this->clear(); return *this; }
	String& operator=(const char ch) { this->assign(1, ch); return *this; }

	//去除字符串左右两边的指定字符
	void trim(char pattern = ' ');
	//去除字符串左边指定字符串中的字符
	void ltrim(const String &pattern);
	//去除字符串右边指定字符串中的字符
	void rtrim(const String &pattern);
	//去除字符串左右两边指定字符串中的字符
	void trim(const String &pattern);
	//字符串分割函数
	std::vector<String> split(const String &pattern, bool merge = false) const;
	//不区分大小写的比较函数
	bool compareNoCase(const String &other, int len = -1) const;
	bool rcompareNoCase(const String &other, int len = -1) const;
	//字符串转浮点型atoi，atol，strtod，strtol，strtoul
	double toDouble() const { return atof(this->c_str()); }
	float toFloat() const { return (float)atof(this->c_str()); }
	//字符串转整形
	int toInt() const { return atoi(this->c_str()); }
	long int toLong() const { return atol(this->c_str()); }
	const char* toStdStr() const { return this->c_str(); }
	//转大小写
	String& toUpper();
	String& toLower();
	//多字节字符串转宽字节字符串
	std::wstring toWString() const;
	String& fromWString(const std::wstring &value);
	//获取子串
	String mid(int pos = 0, int size = -1) const { return this->substr(pos, size); }
	String left(int size = -1) const { return this->substr(0, size); }
	String right(int size = -1) const;
	//格式化函数(注：该函数对于long double类型的数据无效)
	String& format(const char *format, ...);
	String& appendFormat(const char *format, ...);
	//字符串替换函数
	String& replace(const String &src, const String &dst);
	//清空
	//void empty() { this->clear(); }
	//bool isEmpty() { return this->std::string::empty(); }
	//判断是否是数字
	bool isDigit() const;
	//判断是否是数字（包括小数点和科学计数）
	bool isDigit2() const;
	//基本数据类型数据值转字符串
	template<typename T>
	String& fromValue(T value);
};

template<typename T>
inline String& String::fromValue(T value)
{
	std::ostringstream out;
	out.precision(std::numeric_limits<T>::digits10);
	out<<value;
	*this = out.str();
	return *this;
}

#endif /* LANWEI_STRING_H_ */
