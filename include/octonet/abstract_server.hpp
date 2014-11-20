#ifndef ABSTRACT_SERVER_HPP
#define ABSTRACT_SERVER_HPP

class abstract_server
{
public:
    virtual ~abstract_server(void) {}
    virtual void run(void) = 0;
    virtual unsigned short port(void) = 0;
};

#endif
