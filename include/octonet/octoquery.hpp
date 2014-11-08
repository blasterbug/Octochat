#ifndef OCTOQUERY_HPP
#define OCTOQUERY_HPP

#include <cstring>
#include <map>

#include "netstring.hpp"

struct str_comparator
{
    bool operator()(const char* lhs_str, const char* rhs_str) const
    {
        return std::strcmp(lhs_str, rhs_str) < 0;
    }
};

class octoquery
{
protected:
    std::map<const char*, const char*, str_comparator> __headers_set;

public:
    const char* content_buf;
    std::size_t content_len;

    octoquery() : __headers_set(), content_buf(0), content_len(0) {}

    octoquery(const octoquery& oq) : __headers_set(oq.__headers_set), content_buf(oq.content_buf), content_len(oq.content_len) {}

    octoquery(const char *query_buf, std::size_t query_len) : __headers_set(), content_buf(0), content_len(0)
    {
		const char* headers_buf;
		std::size_t headers_len;
		std::size_t acc_len;
		const char* key_str;
		std::size_t key_len;
		const char* value_str;
		std::size_t value_len;
		unsigned int i;
		char* end_str;
		
		headers_len = netstring_decode(query_buf, query_len, &headers_buf);
		if(headers_buf == query_buf)
		{
			throw 1;
		}

		acc_len = headers_len;
		key_str = headers_buf;
		while(acc_len > 0)
		{
			key_len = strnlen(key_str, acc_len);
			if((key_len == acc_len) || (key_len < 1))
			{
				throw 3;
			}
			
			value_str = key_str+key_len+1;
			acc_len -= key_len+1;
			value_len = strnlen(value_str, acc_len);
			if((value_len == acc_len) || (value_len < 1))
			{
				throw 4;
			}
			
			set_header(key_str, value_str);
			
			key_str = value_str+value_len+1;
			acc_len -= value_len+1;
		}
		
		value_str = get_header(CONTENT_LENGTH_HEADER);
		for(acc_len=0; (acc_len<query_len) && (query_buf+acc_len!=headers_buf); acc_len++);
		acc_len += headers_len+1;
		if(value_str == 0)
		{
			if(query_len != acc_len)
			{
				throw 6;
			}
		}
		else
		{
			for(i=0; i<std::strlen(value_str); i++)
			{
				if(!std::isdigit(value_str[i]))
				{
					throw 7;
				}
			}
			errno = 0;
			value_len = std::strtoul(value_str, &end_str, 10);
			if((errno != 0 && (value_len == ULONG_MAX || value_len == 0)) || (end_str == value_str))
			{
				throw 8;
			}
			content_len = value_len;
			content_buf = query_buf + acc_len + 1;
		}
	}

    virtual ~octoquery()
    {
		clear_headers();
	}

    virtual void clear_headers()
    {
		__headers_set.clear();
	}

    std::map<const char*, const char*>::const_iterator begin()
    {
		return __headers_set.begin();
	}

    std::map<const char*, const char*>::const_iterator end()
    {
		return __headers_set.end();
	}

    virtual bool set_header(const char* key_str, const char* value_str)
    {
		if((std::strlen(key_str)>0) && (std::strlen(value_str)>0))
		{
			__headers_set[key_str] = value_str;
			return true;
		}
		return false;
	}

    virtual bool rem_header(const char* key_str)
    {
		std::map<const char*, const char*>::const_iterator fi = __headers_set.find(key_str);
		
		if(fi != __headers_set.end())
		{
			__headers_set.erase(fi->first);
			return true;
		}
		return false;
	}

    const char* get_header(const char* key_str) const
    {
		std::map<const char*, const char*>::const_iterator fi = __headers_set.find(key_str);

		if(fi != __headers_set.end())
		{
			return fi->second;
		}
		return 0;
	}
};

/*class octoquery_alloc : public octoquery
{
public:
    virtual void clear_headers()
    {
		std::map<const char*, const char*>::const_iterator it;

		for(it=__headers_set.begin(); it!=__headers_set.end(); ++it)
		{
			delete[] it->first;
			delete[] it->second;
		}
		__headers_set.clear();
	}

    virtual bool set_header(const char *key_str, const char *value_str)
    {
		std::size_t key_len = std::strlen(key_str);
		std::size_t value_len = std::strlen(value_str);
		char* new_key_str;
		char* new_value_str;

		if((key_len>0) && (value_len>0))
		{
			new_value_str = new char[value_len+1];
			std::strcpy(new_value_str, value_str);
			std::map<const char*, const char*>::iterator fi = __headers_set.find(key_str);
			if(fi != __headers_set.end())
			{
				delete[] fi->second;
				__headers_set[fi->first] = new_value_str;
			}
			else
			{
				new_key_str = new char[key_len+1];
				std::strcpy(new_key_str, key_str);
				__headers_set[new_key_str] = new_value_str;
			}
			return true;
		}
		return false;
	}

    virtual bool rem_header(const char *key_str)
    {
		std::map<const char*, const char*>::const_iterator fi = __headers_set.find(key_str);
		const char* old_key_str;
		const char* old_value_str;

		if(fi != __headers_set.end())
		{
			old_key_str = fi->first;
			old_value_str = fi->second;
			__headers_set.erase(fi->first);
			delete[] old_key_str;
			delete[] old_value_str;
			return true;
		}
		return false;
	}
};*/

#endif
