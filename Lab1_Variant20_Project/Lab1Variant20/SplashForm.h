#pragma once

#include "MainForm.h"

namespace Lab1Variant20
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Windows::Forms;

    public ref class SplashForm : public Form
    {
    public:
        SplashForm() { InitializeComponent(); }
    private:
        System::ComponentModel::Container^ components;
        PictureBox^ titlePicture;
        Button^ startButton;
        Button^ exitButton;

        String^ AssetPath(String^ name)
        {
            String^ path = Path::Combine(Application::StartupPath, "assets\\" + name);
            if (File::Exists(path)) return path;
            return Path::GetFullPath(Path::Combine(Application::StartupPath, "..\\..\\Lab1Variant20\\assets\\" + name));
        }

        void InitializeComponent()
        {
            components = gcnew System::ComponentModel::Container();
            titlePicture = gcnew PictureBox();
            startButton = gcnew Button();
            exitButton = gcnew Button();
            SuspendLayout();
            Text = L"Лабораторная работа № 1";
            StartPosition = FormStartPosition::CenterScreen;
            ClientSize = Drawing::Size(800, 720);
            BackColor = Color::FromArgb(245, 245, 245);
            titlePicture->Location = Point(165, 25);
            titlePicture->Size = Drawing::Size(470, 600);
            titlePicture->SizeMode = PictureBoxSizeMode::Zoom;
            titlePicture->BackColor = Color::White;
            String^ title = AssetPath("title_page.png");
            if (File::Exists(title)) titlePicture->Image = Image::FromFile(title);
            startButton->Text = L"ЛР1";
            startButton->Location = Point(35, 650);
            startButton->Size = Drawing::Size(150, 45);
            startButton->Click += gcnew EventHandler(this, &SplashForm::Start_Click);
            exitButton->Text = L"Выход";
            exitButton->Location = Point(615, 650);
            exitButton->Size = Drawing::Size(150, 45);
            exitButton->Click += gcnew EventHandler(this, &SplashForm::Exit_Click);
            Controls->Add(titlePicture);
            Controls->Add(startButton);
            Controls->Add(exitButton);
            ResumeLayout(false);
        }

        void Start_Click(Object^ sender, EventArgs^ e)
        {
            MainForm^ form = gcnew MainForm();
            form->Owner = this;
            form->Show();
            Hide();
        }

        void Exit_Click(Object^ sender, EventArgs^ e) { Application::Exit(); }
    };
}
