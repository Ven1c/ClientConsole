#pragma once

#include "Common.h"
#include <format>
#include <functional>
namespace Vis {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Сводка для Window
	/// </summary>
	public ref class Window : public System::Windows::Forms::Form
	{
	public:
		Window(void)
		{
			InitializeComponent();
			this->Opacity = 0;
			this->ShowInTaskbar = false;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}



	private:System::Windows::Forms::TextBox^ textBox1;
	private:System::Windows::Forms::TextBox^ textBox2;



	public: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	public:


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Window::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(405, 23);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(552, 236);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(405, 263);
			this->textBox2->Margin = System::Windows::Forms::Padding(2);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(426, 29);
			this->textBox2->TabIndex = 4;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Window::backgroundWorker1_DoWork);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(835, 263);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(122, 29);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Отправить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Window::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(30, 55);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(236, 21);
			this->comboBox1->TabIndex = 9;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Window::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(43, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(205, 20);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Доступные пользователи";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(279, 263);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(121, 29);
			this->button1->TabIndex = 12;
			this->button1->Text = L"Прикрепить файл";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Window::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"\" \"";
			this->openFileDialog1->Filter = L"All files (*.*)|*.*";
			this->openFileDialog1->InitialDirectory = L"C:\\\\";
			this->openFileDialog1->Title = L"Выбор файла";
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(974, 514);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Name = L"Window";
			this->Text = L"SpiritMessenger";
			this->Load += gcnew System::EventHandler(this, &Window::Window_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion




private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	
	while (true) {
		
		
		Globals::Locker.lock();
		if (!Globals::assembleLine.empty()) {
			UpdateChat(Globals::assembleLine.front());
			Globals::assembleLine.pop();
		}
		Globals::Locker.unlock();

		Globals::Locker2.lock();
		if (!Globals::HostsList.empty()) {
			ClearBox();
			AddItemSafe("ВСЕМ");
			for (const auto& x : Globals::HostsList) {
				AddItemSafe(gcnew String(x.c_str()));
			}
			Globals::HostsList.clear();
		}
		Globals::Locker2.unlock();
		Sleep(5);
	}
}
	   String^ fileName;;
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (comboBox1->SelectedIndex == 0) {
		Globals::dest = "TO_ALL";
	}
	else {
		Globals::dest = string((char*)(void*)Marshal::StringToHGlobalAnsi(comboBox1->SelectedItem->ToString()));
	}
}
private: System::Void UpdateChat(Protocol::Message);	  
private: System::Void Window_Load(System::Object^ sender, System::EventArgs^ e) {

	comboBox1->Items->Add("ВСЕМ");

}
void AppendTextSafe(String^ text)
{
	if (textBox1->InvokeRequired)
	{
		// Если вызов сделан не из UI-потока, используем Invoke
		textBox1->Invoke(gcnew Action<String^>(this,&Window::AppendTextSafe), text);
	}
	else
	{
		// Если вызов сделан из UI-потока, добавляем текст
		textBox1->AppendText(text);
	}
}
void AddItemSafe(String^ item)
{
	if (comboBox1->InvokeRequired)
	{
		// Если вызов происходит из другого потока, используем Invoke
		comboBox1->Invoke(gcnew Action< String^>(this,&Window::AddItemSafe), item);
	}
	else
	{
		// Если вызов происходит из UI-потока, добавляем элемент напрямую
		
		comboBox1->Items->Add(item);
	}
}
void ClearBox()
{
	if (comboBox1->InvokeRequired)
	{
		// Если вызов происходит из другого потока, используем Invoke
		comboBox1->Invoke(gcnew Action(this, &Window::ClearBox));
	}
	else
	{
		comboBox1->Items->Clear();
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		fileName = openFileDialog1->FileName;
	}

}
	   
};
}
