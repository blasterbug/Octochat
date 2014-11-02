#ifndef OCTOQUERY_OBSERVER_HPP
#define OCTOQUERY_OBSERVER_HPP

class octoquery_observer
{
    public:
        const char *app_id;
        octoquery_observer(const char *_app_id) : app_id(_app_id) {}
        virtual void update_query(const octoquery &oq);
}

#endif
