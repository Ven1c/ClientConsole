#include "Common.h"
std::mutex Globals::Locker;
std::mutex Globals::Locker2;
std::queue<Protocol::Message> Globals::assembleLine;
std::vector<string> Globals::HostsList;
std::string Globals::user="";
std::string Globals::dest = "";
int Globals::result = 3;
bool ReadConnectionInfo(const std::string& filename, std::string& ip, std::string& port) {
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            if (key == "ip")
            {
                ip = value;
            }
            else if (key == "port")
            {
                port = value;
            }
        }
    }

    file.close();
    return true;
}