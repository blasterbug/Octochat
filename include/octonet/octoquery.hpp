#ifndef OCTOQUERY_HPP
#define OCTOQUERY_HPP

//TODO : use <boost/container/map.hpp>
#include <cstring>
#include <map>

struct str_comparator
{
    bool operator()(const char* lhs, const char* rhs) const
    {
        return std::strcmp(lhs, rhs) < 0;
    }
};

class octoquery
{
private:
    std::map<const char*, const char*, str_comparator> __headers;

public:
    char *content;
    size_t content_length;

    octoquery() : __headers(), content(0), content_length(0) {}

    octoquery(const octoquery &oq) : __headers(oq.__headers), content(oq.content), content_length(oq.content_length) {}

    ~octoquery()
    {
		std::map<const char*, const char*>::const_iterator it;

		for(it=__headers.begin(); it!=__headers.end(); ++it)
		{
			delete[] it->first;
			delete[] it->second;
		}
	}

    std::map<const char*, const char*>::const_iterator begin()
    {
		return __headers.begin();
	}

    std::map<const char*, const char*>::const_iterator end()
    {
		return __headers.end();
	}

    bool set_header(const char *key, const char *value)
    {
		std::size_t key_len = std::strlen(key);
		std::size_t value_len = std::strlen(value);
		char* new_key;
		char* new_value;

		if((key_len>0) && (value_len>0))
		{
			new_value = new char[sizeof(value)];
			std::strcpy(new_value, value);
			std::map<const char*, const char*>::iterator fi = __headers.find(key);
			if(fi != __headers.end())
			{
				delete[] fi->second;
				__headers[fi->first] = new_value;
			}
			else
			{
				new_key = new char[sizeof(key)];
				std::strcpy(new_key, key);
				__headers[new_key] = new_value;
			}
			return true;
		}
		return false;
	}

    bool rem_header(const char *key)
    {
		std::map<const char*, const char*>::const_iterator fi = __headers.find(key);
		const char* old_key;
		const char* old_value;

		if(fi != __headers.end())
		{
			old_key = fi->first;
			old_value = fi->second;
			__headers.erase(fi->first);
			delete[] old_key;
			delete[] old_value;
			return true;
		}
		return false;
	}

    const char* get_header(const char *key) const
    {
		std::map<const char*, const char*>::const_iterator fi = __headers.find(key);

		if(fi != __headers.end())
		{
			return fi->second;
		}
		return 0;
	}
};

#endif
