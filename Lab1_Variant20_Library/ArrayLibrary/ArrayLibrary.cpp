#include "pch.h"
#include "ArrayLibrary.h"

using namespace System;
using namespace System::Windows::Forms;

namespace ArrayLibrary
{
    static bool is_input_correct(array<int>^ mas, int n, int m)
    {
        return mas != nullptr && n > 0 && m > 0 && mas->Length >= n * m;
    }

    void Class1::output_mas(array<int>^ mas, int n, int m, DataGridView^ grid)
    {
        if (!is_input_correct(mas, n, m) || grid == nullptr)
        {
            return;
        }

        grid->Columns->Clear();
        grid->Rows->Clear();
        grid->ColumnCount = m;
        grid->RowCount = n;
        grid->RowHeadersWidth = 70;

        for (int j = 0; j < m; j++)
        {
            grid->Columns[j]->HeaderText = "j = " + (j + 1).ToString();
        }

        for (int i = 0; i < n; i++)
        {
            grid->Rows[i]->HeaderCell->Value = "i = " + (i + 1).ToString();

            for (int j = 0; j < m; j++)
            {
                grid->Rows[i]->Cells[j]->Value = mas[i * m + j].ToString();
            }
        }
    }

    int Class1::find_row(array<int>^ mas, int n, int m)
    {
        if (!is_input_correct(mas, n, m))
        {
            return -1;
        }

        int bestRow = 0;
        int bestCount = -1;

        for (int i = 0; i < n; i++)
        {
            int currentCount = count_multiples(mas, m, i);

            if (currentCount > bestCount)
            {
                bestCount = currentCount;
                bestRow = i;
            }
        }

        return bestRow;
    }

    int Class1::count_multiples(array<int>^ mas, int m, int rowIndex)
    {
        if (mas == nullptr || m <= 0 || rowIndex < 0)
        {
            return -1;
        }

        int count = 0;

        for (int j = 0; j < m; j++)
        {
            if (mas[rowIndex * m + j] % 3 == 0)
            {
                count++;
            }
        }

        return count;
    }

    int Class1::set_rezmas(array<int>^ mas, array<int>^ rezmas, int n, int m, int rowIndex, DataGridView^ grid)
    {
        if (!is_input_correct(mas, n, m) || rezmas == nullptr || grid == nullptr || rowIndex < 0 || rowIndex >= n)
        {
            return -1;
        }

        int count = 0;

        for (int j = 0; j < m; j++)
        {
            int value = mas[rowIndex * m + j];

            if (value % 3 != 0)
            {
                rezmas[count] = value;
                count++;
            }
        }

        grid->Columns->Clear();
        grid->Rows->Clear();
        grid->RowHeadersVisible = false;

        if (count == 0)
        {
            return 0;
        }

        grid->ColumnCount = count;
        grid->RowCount = 1;

        for (int j = 0; j < count; j++)
        {
            grid->Columns[j]->HeaderText = (j + 1).ToString();
            grid->Rows[0]->Cells[j]->Value = rezmas[j].ToString();
        }

        return count;
    }
}
