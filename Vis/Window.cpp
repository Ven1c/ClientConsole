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
std::ifstream inputFile;
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
    if (fileName != " " &&  fileName!=nullptr) {
      
        std::string file= string((char*)(void*)Marshal::StringToHGlobalAnsi(fileName));
        
        char a[3];
        char* buffer = new char[CHUNK_SIZE];
        memset(&buffer[0], 0, sizeof(buffer));
        bool fl = false;
        int j = 0;
        int h;
        inputFile.open(file, std::ios::binary);
        if (!inputFile.is_open()) {
            h = errno;
            std::cerr << "Не удалось открыть входной файл: " << string((char*)(void*)Marshal::StringToHGlobalAnsi(fileName)) << std::endl;
        }
        std::size_t found = file.find_last_of("/\\");
        while ( !inputFile.eof()) {
            inputFile.read(buffer, CHUNK_SIZE);
            std::size_t bytesRead = inputFile.gcount();
            buffer[bytesRead] = '\0';
            Protocol::Message mes;
            time_t mytime = time(NULL);
            mes.time = *localtime(&mytime);
            mes.commandL = FILE;
            mes.file = buffer;
            mes.extenshion = string(file.substr(found + 1));
            mes.destName = Globals::dest;
            mes.senderName = Globals::user;
            clie.SendMessage(clie.ProtocolComposition(mes));
            memset(&buffer[0], 0, sizeof(buffer));
        }
        
        inputFile.close();
        inputFile.clear();
        inputFile.seekg(0, ios::beg);

        fileName = nullptr;
    }
}
System::Void Window::UpdateChat(Protocol::Message assembled) {
        
    char buf[150];
    sprintf_s(buf, 150, "[%02d:%02d] %s: %s\r\n", assembled.time.tm_hour, assembled.time.tm_min, assembled.senderName.c_str(), assembled.mail.c_str());
    System::String^ sys;
    sys = gcnew String(buf);
    AppendTextSafe(sys);
   
}
System::Void LoginForm::LoginForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
    if (!this->IsAutorised){
        (*this->win)->Close();
}
    
}
System::Void Window::Window_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
    clie.Disconnect();
}
System::Void Window::comboBox1_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
 
    bool fl = false;
    string g = string((char*)(void*)Marshal::StringToHGlobalAnsi(comboBox1->SelectedItem->ToString()));
    g.erase(std::remove(g.begin(), g.end(), ' '), g.end());
    for (auto& i : Globals::HostsList) {
        if (i ==  g ) {
            fl = true;
        }
    }
    if (fl)
    {
        label2->Text = "В Сети";
        label2->ForeColor = System::Drawing::Color::ForestGreen;
    }
    else {
        label2->Text = "Не в Сети";
        label2->ForeColor = System::Drawing::Color::Crimson;
    }
    if (comboBox1->SelectedIndex == 0) {
        Globals::dest = "TO_ALL";
    }
    else {
        Globals::dest = g;
    }
    textBox1->Clear();
    Protocol::Message mes;
    mes.commandL = HISTORY;
    mes.destName = Globals::dest;
    mes.senderName = Globals::user;
    time_t mytime = time(NULL);
    mes.time = *localtime(&mytime);
    mes.mail = "/";
    clie.SendMessage(clie.ProtocolComposition(mes));
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
                this->Close();
                (*this->win)->ShowInTaskbar = true;
                (*this->win)->backgroundWorker1->RunWorkerAsync();
                
                break;
            }
            else {
                cout << "wrong auth data" << endl;
            }
            Sleep(100);
        }
                
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