#ifndef OCTOQUERY_HPP
#define OCTOQUERY_HPP

#include <string>
#include <map>
#include <boost/serialization/map.hpp>

struct octoquery
{
	//std::map<const std::string, const std::string> headers_map;
	std::map<std::string, std::string> headers_map;
	//const std::string content_str;
	std::string content_str;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & headers_map;
		ar & content_str;
	}
};

#endif
