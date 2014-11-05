#ifndef OCTOQUERY_OBSERVER_HPP
#define OCTOQUERY_OBSERVER_HPP

#include "octoquery.hpp"

class octoquery_observer
{
    public:
        virtual void update_query(const octoquery &oq) = 0;
        virtual const char* get_app() const = 0;
};

#endif
