//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCTOQUERY_HPP
#define OCTOQUERY_HPP

#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <map>
#include <string>

/*!
 * \struct octoquery
 * \brief Structure octoquery, correspond à une requête.
 */
struct octoquery
{
	std::map<std::string, std::string> headers_map;
	std::string content_str;

	/*!
	 * \brief Sérialise une requête.
	 */
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & headers_map;
		ar & content_str;
	}
};

#endif
