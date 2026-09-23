#pragma once

#using <ArrayLibrary.dll>

namespace Lab1Variant20
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Windows::Forms;
    using namespace ArrayLibrary;

    public ref class MainForm : public Form
    {
    public:
        MainForm()
        {
            random = gcnew Random();
            InitializeComponent();
            CreateMatrix();
            CreateResult();
            NewExample();
        }
    private:
        literal int Rows = 4;
        literal int Cols = 5;
        System::ComponentModel::Container^ components;
        Random^ random;
        Label^ inputLabel;
        Label^ outputLabel;
        Label^ infoLabel;
        DataGridView^ matrixGrid;
        DataGridView^ resultGrid;
        PictureBox^ taskPicture;
        Button^ exampleButton;
        Button^ solveButton;
        Button^ homeButton;

        String^ AssetPath(String^ name)
        {
            String^ path = Path::Combine(Application::StartupPath, "assets\\" + name);
            if (File::Exists(path)) return path;
            return Path::GetFullPath(Path::Combine(Application::StartupPath, "..\\..\\Lab1Variant20\\assets\\" + name));
        }

        void InitializeComponent()
        {
            components = gcnew System::ComponentModel::Container();
            inputLabel = gcnew Label(); outputLabel = gcnew Label(); infoLabel = gcnew Label();
            matrixGrid = gcnew DataGridView(); resultGrid = gcnew DataGridView(); taskPicture = gcnew PictureBox();
            exampleButton = gcnew Button(); solveButton = gcnew Button(); homeButton = gcnew Button();
            SuspendLayout();
            Text = L"Лабораторная работа № 1. Вариант 20";
            StartPosition = FormStartPosition::CenterScreen;
            ClientSize = Drawing::Size(1000, 650);
            BackColor = Color::FromArgb(245, 245, 245);
            inputLabel->Text = L"Исходная матрица"; inputLabel->AutoSize = true; inputLabel->Location = Point(35, 38);
            matrixGrid->Location = Point(35, 65); matrixGrid->Size = Drawing::Size(410, 185);
            matrixGrid->AllowUserToAddRows = false; matrixGrid->AllowUserToDeleteRows = false;
            matrixGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill; matrixGrid->BackgroundColor = Color::LightGray;
            outputLabel->Text = L"Результирующий массив"; outputLabel->AutoSize = true; outputLabel->Location = Point(35, 300);
            resultGrid->Location = Point(35, 327); resultGrid->Size = Drawing::Size(410, 72);
            resultGrid->AllowUserToAddRows = false; resultGrid->AllowUserToDeleteRows = false; resultGrid->ReadOnly = true;
            resultGrid->RowHeadersVisible = false; resultGrid->ColumnHeadersVisible = false;
            resultGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill; resultGrid->BackgroundColor = Color::LightGray;
            infoLabel->Location = Point(35, 415); infoLabel->Size = Drawing::Size(410, 70);
            infoLabel->Text = L"Нажмите «ОК» для выполнения задания.";
            taskPicture->Location = Point(515, 48); taskPicture->Size = Drawing::Size(445, 255);
            taskPicture->SizeMode = PictureBoxSizeMode::Zoom; taskPicture->BackColor = Color::White;
            String^ task = AssetPath("variant20_task.png");
            if (File::Exists(task)) taskPicture->Image = Image::FromFile(task);
            exampleButton->Text = L"Новый пример"; exampleButton->Location = Point(35, 530); exampleButton->Size = Drawing::Size(145, 45);
            exampleButton->Click += gcnew EventHandler(this, &MainForm::Example_Click);
            solveButton->Text = L"ОК"; solveButton->Location = Point(205, 530); solveButton->Size = Drawing::Size(105, 45);
            solveButton->Click += gcnew EventHandler(this, &MainForm::Solve_Click);
            homeButton->Text = L"На главную форму"; homeButton->Location = Point(690, 530); homeButton->Size = Drawing::Size(190, 45);
            homeButton->Click += gcnew EventHandler(this, &MainForm::Home_Click);
            Controls->Add(inputLabel); Controls->Add(matrixGrid); Controls->Add(outputLabel); Controls->Add(resultGrid);
            Controls->Add(infoLabel); Controls->Add(taskPicture); Controls->Add(exampleButton); Controls->Add(solveButton); Controls->Add(homeButton);
            FormClosed += gcnew FormClosedEventHandler(this, &MainForm::Closed);
            ResumeLayout(false); PerformLayout();
        }

        void CreateMatrix()
        {
            matrixGrid->Columns->Clear(); matrixGrid->Rows->Clear();
            for (int j = 0; j < Cols; j++) matrixGrid->Columns->Add("c" + (j + 1), "j = " + (j + 1));
            matrixGrid->Rows->Add(Rows);
            for (int i = 0; i < Rows; i++) matrixGrid->Rows[i]->HeaderCell->Value = "i = " + (i + 1);
        }

        void CreateResult()
        {
            resultGrid->Columns->Clear(); resultGrid->Rows->Clear();
            resultGrid->Columns->Add("empty", ""); resultGrid->Rows->Add(1);
        }

        void NewExample()
        {
            array<int>^ values = gcnew array<int>(Rows * Cols);
            for (int i = 0; i < values->Length; i++)
            {
                int value = 0;
                while (value == 0) value = random->Next(-30, 31);
                values[i] = value;
            }
            Class1::output_mas(values, Rows, Cols, matrixGrid);
            CreateResult();
            infoLabel->Text = L"Сформирована новая исходная матрица.";
        }

        array<int>^ ReadMatrix()
        {
            array<int>^ values = gcnew array<int>(Rows * Cols);
            for (int i = 0; i < Rows; i++)
                for (int j = 0; j < Cols; j++)
                {
                    int value;
                    Object^ cell = matrixGrid->Rows[i]->Cells[j]->Value;
                    if (cell == nullptr || !Int32::TryParse(cell->ToString(), value))
                        throw gcnew FormatException(String::Format(L"Введите целое число в строке {0}, столбце {1}.", i + 1, j + 1));
                    values[i * Cols + j] = value;
                }
            return values;
        }

        void Example_Click(Object^ sender, EventArgs^ e) { NewExample(); }

        void Solve_Click(Object^ sender, EventArgs^ e)
        {
            try
            {
                array<int>^ values = ReadMatrix();
                int row = Class1::find_row(values, Rows, Cols);
                array<int>^ result = gcnew array<int>(Cols);
                int count = Class1::set_rezmas(values, result, Rows, Cols, row, resultGrid);
                if (row < 0 || count < 0) throw gcnew Exception(L"Ошибка при обработке массива.");
                infoLabel->Text = String::Format(L"Найдена строка: {0}\nЭлементов, кратных 3: {1}\nЭлементов в новом массиве: {2}", row + 1, Class1::count_multiples(values, Cols, row), count);
            }
            catch (Exception^ error)
            {
                MessageBox::Show(error->Message, L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }

        void Home_Click(Object^ sender, EventArgs^ e)
        {
            if (Owner != nullptr) Owner->Show();
            Close();
        }

        void Closed(Object^ sender, FormClosedEventArgs^ e)
        {
            if (Owner == nullptr || !Owner->Visible) Application::Exit();
        }
    };
}
