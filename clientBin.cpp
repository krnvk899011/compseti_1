// clientBIN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

// структура данных запроса клиента
struct Student
{
    char surname[25]; // фамилия студента
    int grade1;       // оценка 1
    int grade2;       // оценка 2
    int grade3;       // оценка 3
    int grade4;       // оценка 4
} A;

struct Answer
{
    bool hasDebt;                // есть ли задолженность
    bool hasIncreasedScholarship; // повышенная стипендия
    bool hasRegularScholarship;   // обычная стипендия
} answer;

int main()
{
    setlocale(LC_ALL, "rus");

    char* nameR = "C:\\REQUEST.bin"; // бинарный файл для запросов клиентов
    char* nameA = "C:\\ANSWER.bin";  // бинарный файл для ответов сервера

    ofstream f_REQ;
    ifstream f_ANS;
    long pred_size;

    while (true)
    {
        // передача данных от клиента серверу
        cout << "Введите данные студента: Фамилия Оценка1 Оценка2 Оценка3 Оценка4" << endl;
        cout << "Пример: Иванов 5 4 5 4" << endl;

        // Ввод данных
        char inputSurname[25];
        cin >> inputSurname >> A.grade1 >> A.grade2 >> A.grade3 >> A.grade4;

        // Копируем фамилию в структуру
        strcpy_s(A.surname, sizeof(A.surname), inputSurname);

        // Проверка введенных оценок
        bool validGrades = true;
        int grades[4] = { A.grade1, A.grade2, A.grade3, A.grade4 };
        for (int i = 0; i < 4; i++) {
            if (grades[i] < 2 || grades[i] > 5) {
                cout << "Ошибка: оценки должны быть от 2 до 5!" << endl;
                validGrades = false;
                break;
            }
        }

        if (!validGrades) {
            continue; // запрашиваем данные заново
        }

        cout << "Отправляемые данные: " << A.surname << " "
            << A.grade1 << " " << A.grade2 << " "
            << A.grade3 << " " << A.grade4 << endl;

        // передача данных от клиента серверу
        f_REQ.open(nameR, ios::app | ios::binary);
        f_REQ.write((char*)&A, sizeof(A));
        f_REQ.close();

        // поступил ответ от сервера?
        f_ANS.open(nameA, ios::binary);
        if (!f_ANS.is_open()) {
            cout << "Ошибка открытия файла ответов!" << endl;
            continue;
        }

        f_ANS.seekg(0, ios::end);
        pred_size = f_ANS.tellg();

        int attempts = 0;
        const int maxAttempts = 50; // максимум 5 секунд ожидания

        while (pred_size >= f_ANS.tellg() && attempts < maxAttempts)
        {
            Sleep(100);
            attempts++;
            f_ANS.seekg(0, ios::end);
        }

        if (attempts >= maxAttempts) {
            cout << "Сервер не ответил. Попробуйте еще раз." << endl;
            f_ANS.close();
            continue;
        }

        // получение ответа от сервера
        f_ANS.seekg(pred_size, ios::beg);
        f_ANS.read((char*)&answer, sizeof(answer));
        f_ANS.close();

        // вывод результата
        cout << "\n=== РЕЗУЛЬТАТ ДЛЯ СТУДЕНТА " << A.surname << " ===" << endl;
        cout << "Оценки: " << A.grade1 << ", " << A.grade2 << ", " << A.grade3 << ", " << A.grade4 << endl;

        if (answer.hasDebt) {
            cout << "Есть задолженности по сессии!" << endl;
            cout << "Стипендия не назначается." << endl;
        }
        else if (answer.hasIncreasedScholarship) {
            cout << "Задолженностей нет" << endl;
            cout << "Назначена ПОВЫШЕННАЯ стипендия!" << endl;
        }
        else if (answer.hasRegularScholarship) {
            cout << "Задолженностей нет" << endl;
            cout << "Назначена ОБЫЧНАЯ стипендия" << endl;
        }
        else {
            cout << "Задолженностей нет" << endl;
            cout << "Стипендия не назначена (есть оценки '3')" << endl;
        }
        cout << "========================================" << endl;

        // Пауза перед следующим запросом
        cout << "\nНажмите Enter для нового запроса...";
        cin.ignore();
        cin.get();
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
