#include "Window.h"
#include "LoginForm.h"
#include "Client.h"
#include "Common.h"
#include <thread>
#include <iostream>
#include <format>
#include <functional>
using namespace std;
using namespace Vis;

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
void SideSocketProcces(const string& a, const string& b);
int consts = 0;
Client clie;

[STAThread]
int WINAPI WinMain
(
    HINSTANCE hInstance,	// указатель на текущий экземпляр
    HINSTANCE hPrevInstance,	// указатель на предыдущйи запушенный экземпляр
    LPSTR lpCmdLine,		// командная строка
    int nCmdShow		// тип отображения окна программы
){
#ifdef _WIN32
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        std::cerr << "[Error] Failed to initialize WinSockAPI: "s << std::system_category().message(GET_SOCKET_ERRNO()) << std::endl;
        return 1;
    }
#endif
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Window^ win = gcnew Window;
    LoginForm^ auth = gcnew LoginForm;
    auth->win = &win;
    
    auth->Show();
    string ip;
    string port;
    ReadConnectionInfo("Config.txt", ip, port);
    thread  socke(SideSocketProcces, ip, port);
    socke.detach();
   
   

    
    Application::Run(win);

}


void SideSocketProcces(const string &a, const string &b) {

    
    cout << a << ":" << b << endl;
    clie.SetHost(a, b);
    clie.Start();
    
}

System::Void Window::button2_Click(System::Object^ sender, System::EventArgs^ e) {
    

    char* msg_buff = (char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text);
    std::string message_str(msg_buff);
    Protocol::Message mes;
    time_t mytime = time(NULL);
    mes.time = *localtime(&mytime);
    mes.commandL = STRDMES;
    mes.destName = Globals::dest;
    mes.senderName = Globals::user;
    mes.mail = message_str;
    //std::cerr << "[Info] MAIL SODERJ."s << mes.mail << std::endl;
    Globals::Locker.lock();
    Globals::assembleLine.push(mes);
    Globals::Locker.unlock();
    char* somemes = clie.ProtocolComposition(mes);
    if (clie.SendMessage(somemes) == -1) {
        std::exit(1);
    }
    if (fileName != " " || fileName!=nullptr) {
        std::string file= string((char*)(void*)Marshal::StringToHGlobalAnsi(fileName));
        std::ifstream inputFile(file, std::ios::binary);
        char a[3];
        char* buffer = new char[CHUNK_SIZE];
        bool fl = false;
        int j = 0;
        if (!inputFile.is_open()) {
            std::cerr << "Не удалось открыть входной файл: " << string((char*)(void*)Marshal::StringToHGlobalAnsi(fileName)) << std::endl;
        }
        
        for (int i = 0; i < file.size(); i++) {
            if (fl) {
                a[j] = file.c_str()[i];
            }
            if (file.c_str()[i] == '.') {
                fl = true;
            }
        }
        
        const auto begin = inputFile.tellg();
        inputFile.seekg(0, ios::end);
        const auto end = inputFile.tellg();
        const auto fsize = (end - begin);
        int cycles = (fsize / CHUNK_SIZE)+1;
        int readed = 0;
        for (int i = 0; i < cycles; i++) {
            Protocol::Message mes;
            time_t mytime = time(NULL);
            mes.time = *localtime(&mytime);
            mes.commandL = FILE;
            inputFile.seekg(readed);
            inputFile.read(buffer, CHUNK_SIZE);
            std::streamsize bytesRead = inputFile.gcount();
            readed += bytesRead;
            mes.mail = string(buffer);
            mes.extenshion = string(a);
            clie.SendMessage(clie.ProtocolComposition(mes));
        }
        
    }
}
System::Void Window::UpdateChat(Protocol::Message assembled) {
        
    char buf[150];
    sprintf_s(buf, 150, "[%d:%d] %s: %s\r\n", assembled.time.tm_hour, assembled.time.tm_min, assembled.senderName.c_str(), assembled.mail.c_str());
    System::String^ sys;
    sys = gcnew String(buf);
    AppendTextSafe(sys);
   
}
System::Void LoginForm::LoginForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

  
    
}
System::Void LoginForm::Sign_In(System::Object^ sender, System::EventArgs^ e) {
    if (clie.GetStatus() == 1) {
        Protocol::User us;
        us.name = string((char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text));
        us.password = string((char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text));
        //шифрование сюда
        Protocol::Message mes;
        mes.authData = us;
        mes.commandL = AUTH;
        Globals::result = 0;
        clie.SendMessage(clie.ProtocolComposition(mes));
        for (int i = 0; i < 10; i++) {
            if (Globals::result == 1) {
                Globals::user = us.name;
                this->IsAutorised = true;
                (*this->win)->Opacity = 1;
                (*this->win)->ShowInTaskbar = true;
                (*this->win)->backgroundWorker1->RunWorkerAsync();
                
                break;
            }
            else {
                cout << "wrong auth data" << endl;
            }
            Sleep(100);
        }
        this->Close();
    }
}
System::Void LoginForm::Register(System::Object^ sender, System::EventArgs^ e) {

        Protocol::User us;
        us.name = string((char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text));
        us.password = string((char*)(void*)Marshal::StringToHGlobalAnsi(textBox2->Text));
        //шифрование сюда
        Protocol::Message mes;
        mes.authData = us;
        mes.commandL = REG;
        clie.SendMessage(clie.ProtocolComposition(mes));
    
}
System::Void LoginForm::UpdateStatusWi() {
    if (clie.GetStatus() == 1) {
        UpdateLabel("Подключено");
    }
    else {
        UpdateLabel("Отключено");

    }
}
System::Void LoginForm::Recon(System::Object^ sender, System::EventArgs^ e) {
    if (clie.GetStatus() == 0) {
        clie.Start();
    }
}