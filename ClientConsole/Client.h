#pragma once
#include "common.h"
#include <thread>


class Client
{
public:
    Client(const char* hostname, const char* port) : remote_hostname_(hostname), remote_port_(port) {}

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    ~Client() {
        Disconnect();
    }
public:
    int Start();

    void Disconnect();
private:
    void PrependMessageLength(std::string& message) {
        std::string message_size_str = std::to_string(message.size());
        while (message_size_str.size() < 4) {
            message_size_str = "0" + message_size_str;
        }
        message = message_size_str + message;
    }
    /* Creates new `addrinfo` object and fills it with connection information.
     * @return `nullptr` on error, pointer to `addrinfo` object on success.
    */
    addrinfo* ResolveConnectionAddress();

    // @return `-1` on error, valid socket on success.
    SOCKET CreateConnectionSocket(addrinfo* conn_addr);

    int SendMessage(const std::string& message);

    int ReceiveMessage(char* writable_buff);

    // Prints the input prompt and flushes stdout afterwards. 
    void PrintInputPrompt() const;

    /* Handles user input and message-sending process.
     * @return `-1` on error, `0` on successful exit.
    */
    int InputHandler();

    /* Main client application loop. Handles incoming data and accepts user input.
     * @return `-1` on error, `0` on successful exit.
    */
    int HandleConnection();

private:
    const std::string remote_hostname_, remote_port_;
    SOCKET connection_socket_;
};

