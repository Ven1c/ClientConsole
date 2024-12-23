#include "Client.h"


int Client::Start() {
    std::cerr << "[Info] Starting the client.\n"s;

    // Get server address
    addrinfo* conn_addr = ResolveConnectionAddress();
    if (!conn_addr) {
        return -1;
    }

    // Create connection socket for the client
    connection_socket_ = CreateConnectionSocket(conn_addr);
    if (!IS_VALID_SOCKET(connection_socket_)) {
        return -1;
    }

    std::cerr << "[Info] Connecting to remote host ("s << remote_hostname_ << ":"s << remote_port_ << ")\n"s;
    if (connect(connection_socket_, conn_addr->ai_addr, conn_addr->ai_addrlen) == -1) {
        std::cerr << "[Error] Failed to connect to the remote host: connect(): "s << std::system_category().message(GET_SOCKET_ERRNO()) << std::endl;
        return -1;
    }
    std::cerr << "[Info] Successfully connected to "s << remote_hostname_ << ":"s << remote_port_ << std::endl;
    status = 1;
    freeaddrinfo(conn_addr); // clean up ununsed resources
    
    return HandleConnection();
}

void Client::Disconnect() {
    std::cerr << "[Info] Disconnecting from the remote server.\n"s;
    CLOSE_SOCKET(connection_socket_);
    status = 0;
    std::cerr << "[Info] Disconnected."s << std::endl;
   
};
addrinfo* Client::ResolveConnectionAddress()  {
    std::cerr << "[Debug] Resolving remote server address.\n"s;
    // Create helper and connection data structures for getaddrinfo() call
    addrinfo hints, * connection_address;
    memset(&hints, 0x00, sizeof(hints));
    hints.ai_family = AF_INET; // use IPv4 for connection
    hints.ai_socktype = SOCK_STREAM; // use TCP

    if (getaddrinfo(remote_hostname_.data(), remote_port_.data(), &hints, &connection_address) == -1) {
        std::cerr << "[Error] Failed to resolve remote host address: getaddrinfo(): "s << std::system_category().message(GET_SOCKET_ERRNO()) << std::endl;
        return nullptr;
    }

    return connection_address;
}

Protocol::Message Client::ProtocolDecomposition(const char* message,int msg_len)
{

    Protocol::Message assembled;
    assembled.size = msg_len;
    std::ofstream file;
    std::ifstream test;
    char buf1[255] = { 0 };
    char buf2[255] = { 0 };
    char* buf3;
    int sizeSend;
    int sizeDest;
    int k = 0;
    int j = 0;
    string strbuf;
    std::string filepath;
    int hosts = 0;
    assembled.time.tm_hour = NumberDec(message, 0, 1);
    assembled.time.tm_min = NumberDec(message, 2, 3);
    assembled.time.tm_sec = NumberDec(message, 4, 5);
    assembled.commandL = NumberDec(message, 6, 7);
    switch (assembled.commandL)
    {
    case HISTORY:
    case STRDMES:
        for (int i = 0; i < 10; i++) {
            sizeSend = i;
            if (message[8 + i] == '/') {
                break;
            }
            buf1[i] = message[8 + i];

        }
        sizeSend++;
        assembled.senderName = std::string(buf1);
        for (int i = 0; i < 10; i++) {
            sizeDest = i;
            if (message[8 + sizeSend + i] == '/') {
                break;
            }
            buf2[i] = message[8 + sizeSend + i];
        }
        assembled.destName = std::string(buf2);
        sizeDest++;

        buf3 = new char[msg_len - (8 + sizeSend + sizeDest)];
        for (int i = 0; i < msg_len - (8 + sizeSend + sizeDest); i++) {
            buf3[i] = 0;
        }
        while (8 + sizeSend + sizeDest + j < msg_len) {
            if (message[8 + sizeSend + sizeDest + j] == '/') {
                break;
            }
            buf3[j] = message[8 + sizeSend + sizeDest + j];
            j++;
        }

        assembled.mail = std::string(buf3);
        break;
    case HOSTS:
        hosts = NumberDec(message, 8, 9);
        Globals::Locker2.lock();
        Globals::HostsList.clear();
        for (int i = 0; i < hosts; i++) {
            memset(&buf1[0], 0, sizeof(buf1));
            strbuf.clear();
            j = 0;
            while (message[k+10] != '/') {
                buf1[j] = message[10 + k];
                j++;
                k++;
            }
            k++;
            
            strbuf.assign(buf1);
            
            std::cerr << "[Error] from client.cpp lock" << endl;
            Globals::HostsList.push_back(strbuf);
            
        }
        Globals::Locker2.unlock();
        break;
    case HOSTS_OFLINE:
        hosts = NumberDec(message, 8, 9);
        Globals::Locker2.lock();
        Globals::UserList.clear();
        for (int i = 0; i < hosts; i++) {
            memset(&buf1[0], 0, sizeof(buf1));
            strbuf.clear();
            j = 0;
            while (message[k + 10] != '/') {
                buf1[j] = message[10 + k];
                j++;
                k++;
            }
            k++;

            strbuf.assign(buf1);
            std::cerr << "[Error] from client.cpp lock" << endl;
            Globals::UserList.push_back(strbuf);

        }
        Globals::Locker2.unlock();
        break;
    case ACK:
        //idk now
    case AUTH_ACK:
        buf1[0] = message[8];
        assembled.result = atoi(buf1);
        break;
    case FILE:
        buf3 = new char[1024];
        for (int i = 0; i < 10; i++) {
            sizeSend = i;
            if (message[8 + i] == '/') {
                break;
            }
            buf1[i] = message[8 + i];

        }
        sizeSend++;
        assembled.senderName = std::string(buf1);
        for (int i = 0; i < 10; i++) {
            sizeDest = i;
            if (message[8 + sizeSend + i] == '/') {
                break;
            }
            buf2[i] = message[8 + sizeSend + i];
        }
        assembled.destName = std::string(buf2);
        sizeDest++;
        j = sizeDest + sizeSend;
        memset(&buf1[0], 0, sizeof(buf1));
        for (int i = 0; i < 60; i++) {
            sizeSend = i;
            if (message[8 + i + j] == '/') {
                break;
            }
            buf1[i] = message[8 + j+ i];

        }
        assembled.extenshion = std::string(buf1);
        sizeSend++;
        j += sizeSend;
        j += 8;
        memset(&buf1[0], 0, sizeof(buf1));
        for (int i = 0; i < assembled.size-j; i++) {
             buf1[i]= message[i+j];
        }
       
        test.open(assembled.extenshion);
        if (test.is_open()) {
            test.close();
            file.open(assembled.extenshion, ios::binary | ios::app);
        }
        else {
            file.open(assembled.extenshion, ios::binary | ios::out);
        }
        memset(&buf3[0], 0, sizeof(buf3));
        recv(connection_socket_,buf3 , stoi(string(buf1)), NULL);
        for (int i = 0; i < stoi(string(buf1)); i++) {
            file << buf3[i];
        }
        
            
        file.close();
        break;
    default:
        cout << "undefined protocol" << endl;
        break;
    }
    return assembled;
}
int Client::NumberDec(const char* mes, int start, int end) {
    char buf[2];
    int j = 0;
    for (int i = start; i < end+1; i++) {
        buf[j] = mes[i];
        j++;
    }
    return stoi(buf);
}
char* Client::ProtocolComposition(Protocol::Message message)
{

    mytime = time(NULL);
    message.time = *localtime(&mytime);
    int msg_len;
    char* mes;
    switch (message.commandL)
    {
    case HISTORY:
    case STRDMES:
        msg_len = 12 + message.senderName.size() + message.destName.size() + message.mail.size();
        mes = new char[msg_len];
        cout << message.mail << endl;
        sprintf_s(mes, msg_len, "%2d%2d%2d%2d%s/%s/%s/", message.time.tm_hour, message.time.tm_min, message.time.tm_sec, message.commandL, message.senderName.c_str(), message.destName.c_str(), message.mail.c_str());
        cout << mes << endl;
        break;

  //case HOSTS: для хостов не применима отправка с клиента
    case AUTH:
        msg_len = 11 + message.authData.name.size() + message.authData.password.size();
        mes = new char[msg_len];
        sprintf_s(mes, msg_len, "%2d%2d%2d%2d%s/%s/", message.time.tm_hour, message.time.tm_min, message.time.tm_sec, message.commandL, message.authData.name.c_str(), message.authData.password.c_str());
        break;
    case REG:
        msg_len = 11 + message.authData.name.size() + message.authData.password.size();
        mes = new char[msg_len];
        sprintf_s(mes, msg_len, "%2d%2d%2d%2d%s/%s/", message.time.tm_hour, message.time.tm_min, message.time.tm_sec, message.commandL, message.authData.name.c_str(), message.authData.password.c_str());
        break;
    case FILE:
        msg_len = 12 + message.senderName.size() + message.destName.size() +message.extenshion.size()+message.mail.size();
        mes = new char[msg_len];
        sprintf_s(mes, msg_len, "%2d%2d%2d%2d%s/%s/%s/%s", message.time.tm_hour, message.time.tm_min, message.time.tm_sec, message.commandL, message.senderName.c_str(), message.destName.c_str(),message.extenshion.c_str(),message.mail.c_str());
        break;
    default:
        break;
    }
    return mes;
    
    
}
// @return `-1` on error, valid socket on success....

SOCKET Client::CreateConnectionSocket(addrinfo* conn_addr) {
    if (!conn_addr) {
        std::cerr << "[Error] CreateConnectionSocket(): conn_addr is NULL."s << std::endl;
        return -1;
    }

    std::cerr << "[Debug] Creating new connection socket.\n"s;
    SOCKET new_conn_socket = socket(conn_addr->ai_family, conn_addr->ai_socktype, conn_addr->ai_protocol);
    if (!IS_VALID_SOCKET(new_conn_socket)) {
        std::cerr << "[Error] Failed to create a new connection socket: socket(): "s <<WSAGetLastError()<< std::endl;
        return -1;
    }
    return new_conn_socket;
}
int Client::SendMessage(const std::string& message) {
    std::string assembled_msg(message);
    PrependMessageLength(assembled_msg);
    int total_bytes = assembled_msg.size();
    int sent_bytes = 0;
    int sent_n;
    std::cerr << "[Debug] Sending message: '"s << assembled_msg << "'\n"s;
    while (total_bytes > sent_bytes) {
        sent_n = send(connection_socket_, assembled_msg.data() + sent_bytes, total_bytes - sent_bytes, 0);
        if (sent_n == -1) {
            std::cerr << "[Error] Failed to send data to the remote host: send(): "s << std::system_category().message(GET_SOCKET_ERRNO()) << std::endl;
            return sent_n;
        }
        sent_bytes += sent_n;
        std::cerr << "[Debug] Sending "s << sent_n << " bytes to the remote host\n"s;
    }


    return sent_bytes;
}

int Client::ReceiveMessage(char* writable_buff) {

    // Receive packet length (first 4 bytes)
    char msg_len_str[5]; // 4 bytes + 1 byte for the null-terminating character
    memset(msg_len_str, 0x00, sizeof(msg_len_str));
    msg_len_str[4] = '\0';

    int recv_bytes = recv(connection_socket_, msg_len_str, sizeof(msg_len_str) - 1, 0);
    if (recv_bytes <= 0) { // either client disconnect or an error
        return recv_bytes;
    }
    std::cerr << "[Debug] Received "s << recv_bytes << " bytes (packet length): '"s << msg_len_str << "\n"s;
    // Check if the message conforms to the protocol
    for (const char c : std::string(msg_len_str)) {
        if (!std::isdigit(c)) {
            std::cerr << "[Error] Failed to read data from the remote host: invalid protocol format.\n"s;
            return -1;
        }
    }

    int packet_length = std::atoi(msg_len_str);
    recv_bytes = recv(connection_socket_, writable_buff, packet_length, 0);
    if (recv_bytes <= 0) { // Check for errors
        return recv_bytes;
    }
    std::cerr << "[Debug] Received "s << recv_bytes << " bytes (actual packet)\n"s << writable_buff << "\n"s;
    Protocol::Message regular = ProtocolDecomposition(writable_buff,packet_length);
    switch (regular.commandL) {
    case HISTORY:
    case STRDMES:
            std::cerr << "[Debug] ["s << regular.time.tm_hour << ":" << regular.time.tm_min << "] " << regular.mail << "\n"s;
            Globals::Locker.lock();
            Globals::assembleLine.push(regular);
            Globals::Locker.unlock();
            break;
    case HOSTS:
            std::cerr << "[Debug] ["s << regular.time.tm_hour << ":" << regular.time.tm_min << "] ";
            Globals::Locker2.lock();

            for (string i : Globals::HostsList) {
                std::cerr << i;
            }
            Globals::Locker2.unlock();
            std::cerr << "\n"s;
            break;
    case AUTH_ACK:
        Globals::result = regular.result;
        std::cerr << "[Debug] ["s << regular.result << "]"s << endl;
        break;
    default:
        
        break;
    }
  
    return recv_bytes;
}
//void Client::PrintInputPrompt() const {
//    std::cin.clear();
//    std::cout << " >>> "s;
//    std::cout.flush();
//}

//int Client::InputHandler() {
//    while (true) {
//        char msg_buff[MAX_DATA_BUFFER_SIZE];
//        PrintInputPrompt();
//        
//        std::fgets(msg_buff, MAX_DATA_BUFFER_SIZE, stdin);
//        std::string message_str(msg_buff);
//        message_str.pop_back(); // fgets() adds \n char to the end of the string
//        Protocol::Message mes;
//        mes.commandL = 0;
//        mes.destName = "SOME/";
//
//        mes.senderName = "inner/";
//        mes.mail = message_str;
//        std::cerr << "[Info] MAIL SODERJ."s <<mes.mail<< std::endl;
//        char* somemes = ProtocolComposition(mes);
//        if (SendMessage(somemes) == -1) {
//            std::exit(1);
//        }
//        memset(msg_buff, 0x00, MAX_DATA_BUFFER_SIZE);
//    }
//}

int Client::HandleConnection()  {
    //std::thread input_worker_thread(&Client::InputHandler, this); // Create a new thread for reading user input
    //input_worker_thread.detach();
    while (true) {
        char msg_buff[MAX_DATA_BUFFER_SIZE];
        memset(msg_buff, 0x00, sizeof(msg_buff));
        memset(msg_buff, 0x00, sizeof(msg_buff));

        int recv_bytes = ReceiveMessage(msg_buff);
        if (recv_bytes <= 0) {
            if (recv_bytes == 0) {
                std::cerr << "[Info] Remote host has closed the connection."s << std::endl;
                std::exit(1);
            }
            else {
                std::cerr << "[Error] Failed to receive data from the remote host: recv(): "s << std::system_category().message(GET_SOCKET_ERRNO()) << std::endl;
                std::exit(1);
            }
        }
        std::cout << msg_buff << '\n';

        /*PrintInputPrompt();*/
    }
}