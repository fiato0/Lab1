#include "SplashForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Lab1Variant20::SplashForm^ splashForm = gcnew Lab1Variant20::SplashForm();
    Application::Run(splashForm);

    return 0;
}
