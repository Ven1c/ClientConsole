#pragma once
#include "Common.h"

#include <thread>
#ifndef CO_H
#define CO_H
#endif

using namespace std;
class Client
{
public:

    Client() {};
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    ~Client() {
        Disconnect();
    }
public:
    SOCKET connection_socket_;
    /* Ñonfiguration packet with protocol fields.
    * @return NULL on error or wrong data
    */
    char* ProtocolComposition(Protocol::Message message);
    void SetHost(const string& hostname, const string& port) {
        remote_hostname_ = hostname;
        remote_port_ = port;
    }
    int SendMessage(const std::string& message);

    int ReceiveMessage(char* writable_buff);

    int GetStatus() {
        return status;
    }
    
    int Start();

    void Disconnect();
private:
    int NumberDec(const char* mes, int start, int end);
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
    /* Recive packet with protocol fields.
    * @return NULL on error or wrong protocol
    */
    Protocol::Message ProtocolDecomposition(const char* message,int msg_len);
    
    // @return `-1` on error, valid socket on success.
    SOCKET CreateConnectionSocket(addrinfo* conn_addr);

    

    //// Prints the input prompt and flushes stdout afterwards. 
    //void PrintInputPrompt() const;

    ///* Handles user input and message-sending process.
    // * @return `-1` on error, `0` on successful exit.
    //*/
    //int InputHandler();

    /* Main client application loop. Handles incoming data and accepts user input.
     * @return `-1` on error, `0` on successful exit.
    */
    int HandleConnection();

private:
    std::string remote_hostname_, remote_port_;
    
    int status;
    
    time_t mytime;
};

