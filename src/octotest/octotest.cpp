#include <boost/log/utility/setup/file.hpp>

#include <octonet/octonet.hpp>

void init(void)
{
    //boost::log::add_file_log("octotest.log");
}

int main(void)
{
    init();
    octonet on;
    on.run();
    std::string s;
    std::getline(std::cin, s);
    return 0;
}
