#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

string extract_first_directory(const std::string &filepath)
{
    // знаходимо позицію першого "\" після диска
    std::size_t start_pos = filepath.find(":");
    if (start_pos != std::string::npos)
    {
        start_pos = filepath.find("\\", start_pos) + 1; // знаходимо початок каталогу
    }
    else
    {
        start_pos = 0; // якщо нема диска, починаємо з початку рядка
    }

    std::size_t end_pos = filepath.find("\\", start_pos); // знаходимо кінець першого каталогу

    if (end_pos == std::string::npos)
    {
        // якщо символ "\" не знайдено, це означає, що файл у кореневому каталозі
        return "\\";
    }
    else
    {
        // повертаємо частину рядка з першого каталогу
        return filepath.substr(start_pos, end_pos - start_pos);
    }
}

bool check_conditions(const std::string &filepath)
{
    // Перевіряємо, чи рядок містить символ "\"
    return filepath.find("\\") != std::string::npos;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Отримуємо шлях до текстового файлу з консолі
    string input_filename, output_filename;
    cout << "Введіть шлях до вхідного текстового файлу: ";
    cin >> input_filename;
    cout << "Введіть шлях до вихідного текстового файлу: ";
    cin >> output_filename;

    // Відкриваємо вхідний текстовий файл для читання
    ifstream input_file(input_filename);
    if (!input_file.is_open())
    {
        cerr << "Помилка: Неможливо відкрити вхідний файл!" << endl;
        return 1;
    }

    // Відкриваємо вихідний текстовий файл для запису
    ofstream output_file(output_filename);
    if (!output_file.is_open())
    {
        cerr << "Помилка: Неможливо відкрити вихідний файл!" << endl;
        return 1;
    }

    string line;
    // Читаємо файл рядок за рядком
    while (getline(input_file, line))
    {
        // Обробляємо кожний рядок
        if (check_conditions(line))
        {
            string result = extract_first_directory(line);
            // Записуємо результат у вихідний файл
            output_file << result << endl;
        }
    }

    // Закриваємо файли
    input_file.close();
    output_file.close();

    cout << "Обробка завершена. Результати записані у файл " << output_filename << endl;

    return 0;
}
