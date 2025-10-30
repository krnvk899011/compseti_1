// client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

struct Student
{
    string surname; // фамилия студента
    int grade1;     // оценка 1
    int grade2;     // оценка 2
    int grade3;     // оценка 3
    int grade4;     // оценка 4
};

int main()
{
    setlocale(LC_ALL, "rus");

    string nameR = "C:/Users/USER/Desktop/REQUEST.txt"; // текстовый файл для запросов клиентов
    string nameA = "C:/Users/USER/Desktop/ANSWER.txt";  // текстовый файл для ответов сервера

    while (true)
    {
        Student A;
        cout << "Введите данные студента: Фамилия Оценка1 Оценка2 Оценка3 Оценка4" << endl;
        cin >> A.surname >> A.grade1 >> A.grade2 >> A.grade3 >> A.grade4;

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

        // отправка запроса
        ofstream f_REQ(nameR, ios::app);
        f_REQ << A.surname << " " << A.grade1 << " " << A.grade2
            << " " << A.grade3 << " " << A.grade4 << endl;
        f_REQ.close();

        // ожидание ответа
        cout << "Ожидание ответа от сервера..." << endl;
        bool found = false;
        int attempts = 0;
        const int maxAttempts = 10;

        while (!found && attempts < maxAttempts) {
            Sleep(2000); // ждем 2 секунды
            attempts++;

            ifstream f_ANS(nameA);
            if (!f_ANS.is_open()) {
                continue;
            }

            string answerSurname;
            int hasDebt, hasIncreasedScholarship, hasRegularScholarship;

            while (f_ANS >> answerSurname >> hasDebt >> hasIncreasedScholarship >> hasRegularScholarship) {
                if (answerSurname == A.surname) {
                    cout << "\n=== РЕЗУЛЬТАТ ДЛЯ СТУДЕНТА " << A.surname << " ===" << endl;
                    cout << "Оценки: " << A.grade1 << ", " << A.grade2 << ", " << A.grade3 << ", " << A.grade4 << endl;

                    if (hasDebt) {
                        cout << "Есть задолженности по сессии!" << endl;
                        cout << "Стипендия не назначается." << endl;
                    }
                    else if (hasIncreasedScholarship) {
                        cout << " Задолженностей нет" << endl;
                        cout << " Назначена ПОВЫШЕННАЯ стипендия!" << endl;
                    }
                    else if (hasRegularScholarship) {
                        cout << " Задолженностей нет" << endl;
                        cout << " Назначена ОБЫЧНАЯ стипендия" << endl;
                    }
                    else {
                        cout << " Задолженностей нет" << endl;
                        cout << " Стипендия не назначена (есть оценки '3')" << endl;
                    }
                    cout << "========================================" << endl;
                    found = true;
                    break;
                }
            }
            f_ANS.close();

            if (!found && attempts == maxAttempts) {
                cout << " Сервер не ответил. Попробуйте еще раз." << endl;
            }
        }

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
