#include <octonet/octonet_manager.hpp>

int main(void)
{
    octonet_manager on(1234, 4321);
    on.run();
    std::string s;
    std::getline(std::cin, s);
    return 0;
}
