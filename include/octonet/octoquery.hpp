#ifndef OCTOQUERY_HPP
#define OCTOQUERY_HPP

//TODO : use <boost/container/map.hpp>
#include <cstddef>
#include <map>

struct str_comparator
{
    bool operator()(const char* lhs, const char* rhs) const
    {
        return std::strcmp(lhs, rhs) < 0;
    }
};

struct octoquery
{
    //TODO : think about optimal container
    std::map<char*, char*, str_comparator> headers;
    char *content;
    size_t content_length;

    octoquery() : headers(), content(0), content_length(0) {}
    octoquery(const octoquery &oq) : headers(oq.headers), content(oq.content), content_length(oq.content_length) {}
    //bool parse(const char *query, size_t query_length);
};

#endif
