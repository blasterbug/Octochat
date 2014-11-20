#ifndef OCTOQUERY_OBSERVER_HPP
#define OCTOQUERY_OBSERVER_HPP

#include <string>

#include "octoquery.hpp"

class octoquery_observer
{
    public:
		virtual ~octoquery_observer(void) {}
        virtual void update_query(const octoquery& _query) = 0;
        virtual std::string app() const = 0;
};

#endif
