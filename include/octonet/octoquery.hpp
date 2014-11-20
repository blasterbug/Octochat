#ifndef OCTOQUERY_HPP
#define OCTOQUERY_HPP

#include <boost/serialization/map.hpp>
#include <map>
#include <string>

struct octoquery
{
	std::map<std::string, std::string> headers_map;
	std::string content_str;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & headers_map;
		ar & content_str;
	}
};

#endif
