#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace ArrayLibrary
{
    public ref class Class1 abstract sealed
    {
    public:
        static void output_mas(array<int>^ mas, int n, int m, DataGridView^ grid);
        static int find_row(array<int>^ mas, int n, int m);
        static int count_multiples(array<int>^ mas, int m, int rowIndex);
        static int set_rezmas(array<int>^ mas, array<int>^ rezmas, int n, int m, int rowIndex, DataGridView^ grid);
    };
}
