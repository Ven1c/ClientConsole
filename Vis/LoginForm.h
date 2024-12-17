#pragma once
#include "Window.h"


namespace Vis {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для LoginForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button2;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(59, 141);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Войти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LoginForm::Sign_In);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(206, 81);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(164, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Enter += gcnew System::EventHandler(this, &LoginForm::textBox1_Enter);
			this->textBox1->Leave += gcnew System::EventHandler(this, &LoginForm::textBox1_Leave);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(206, 141);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(164, 20);
			this->textBox2->TabIndex = 2;
			this->textBox2->Enter += gcnew System::EventHandler(this, &LoginForm::textBox2_Enter);
			this->textBox2->Leave += gcnew System::EventHandler(this, &LoginForm::textBox2_Leave);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(37, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Отключено";
			this->label1->Click += gcnew System::EventHandler(this, &LoginForm::Recon);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 81);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(122, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Зарегистироваться";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &LoginForm::Register);
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(478, 312);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"LoginForm";
			this->Text = L"Авторизация";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &LoginForm::LoginForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &LoginForm::LoginForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void LoginForm_Load(System::Object^ sender, System::EventArgs^ e) {
	textBox1->ForeColor= Color::Gray;
	textBox1->Text = "Введите ваш логин";
	textBox2->ForeColor = Color::Gray;
	textBox2->Text = "Введите ваш пароль";
	textBox2->UseSystemPasswordChar = false;
	UpdateStatusWi();

}
private: System::Void textBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
	if (textBox2->Text == "Введите ваш пароль" && textBox2->ForeColor == Color::Gray)
	{
		textBox2->Text = ""; // Очистить поле
		textBox2->ForeColor = Color::Black; // Установить цвет текста
		textBox2->UseSystemPasswordChar = true;
	}
	UpdateStatusWi();
}
private: System::Void textBox2_Leave(System::Object^ sender, System::EventArgs^ e) {
	if (String::IsNullOrWhiteSpace(textBox2->Text))
	{
		textBox2->ForeColor = Color::Gray;
		textBox2->Text = "Введите ваш пароль";
		textBox2->UseSystemPasswordChar = false;
	}
}
private: System::Void textBox1_Leave(System::Object^ sender, System::EventArgs^ e) {
	if (String::IsNullOrWhiteSpace(textBox1->Text))
	{
		textBox1->ForeColor = Color::Gray;
		textBox1->Text = "Введите ваш логин";
	}
}
private: System::Void textBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	if (textBox1->Text == "Введите ваш логин" && textBox1->ForeColor == Color::Gray)
	{
		textBox1->Text = ""; // Очистить поле
		textBox1->ForeColor = Color::Black; // Установить цвет текста

	}
	UpdateStatusWi();
}
private: System::Void Register(System::Object^ sender, System::EventArgs^ e);
private: System::Void Sign_In(System::Object^ sender, System::EventArgs^ e);
void UpdateLabel(System::String^ text)
{

	if (!this->IsDisposed) {
		if (text == "Подключено") {
			label1->ForeColor = System::Drawing::Color::ForestGreen;
		}
		else {
			label1->ForeColor = System::Drawing::Color::Crimson;
		}
		label1->Text = text;
	}

}
public:System::Void LoginForm::UpdateStatusWi();
	  public: bool IsAutorised;
	  public: Vis::Window^ *win;
private: System::Void LoginForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);

private: System::Void Recon(System::Object^ sender, System::EventArgs^ e);
};
}
