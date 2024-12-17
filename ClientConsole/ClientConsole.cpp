#include "Common.h"
#include "Client.h"
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "[Usage] client <remote_address> <remote_port>"s << std::endl;
        return 1;
    }
#ifdef _WIN32
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        std::cerr << "[Error] Failed to initialize WinSockAPI: "s << std::system_category().message(GET_SOCKET_ERRNO()) << std::endl;
        return 1;
    }
#endif

    Client client(argv[1], argv[2]);
    if (client.Start() == -1) {
        return 1;
    }
}