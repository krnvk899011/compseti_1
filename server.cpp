// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
    ifstream fR;
    ofstream fA;
    setlocale(LC_ALL, "rus");

    string nameR = "C:/Users/USER/Desktop/REQUEST.txt"; // текстовый файл запросов клиентов
    string nameA = "C:/Users/USER/Desktop/ANSWER.txt";  // текстовый файл ответов сервера

    cout << "server is working" << endl;

    // начало работы сервера
    while (true)
    {
        Sleep(1000); // проверяем каждую секунду

        fR.open(nameR);
        if (!fR.is_open()) {
            continue;
        }

        // читаем все запросы
        Student S;
        while (fR >> S.surname >> S.grade1 >> S.grade2 >> S.grade3 >> S.grade4) {
            // обработка данных студента
            bool hasDebt = false;
            bool hasIncreasedScholarship = false; // повышенная стипендия
            bool hasRegularScholarship = false;   // обычная стипендия

            // проверка на задолженности (оценки 2 и 3)
            int grades[4] = { S.grade1, S.grade2, S.grade3, S.grade4 };
            int excellentCount = 0;
            int goodCount = 0;
            int satisfactoryCount = 0;

            for (int i = 0; i < 4; i++) {
                if (grades[i] == 2) {
                    hasDebt = true; // двойка - задолженность
                }
                else if (grades[i] == 3) {
                    satisfactoryCount++; // тройка
                }
                else if (grades[i] == 4) {
                    goodCount++; // четверка
                }
                else if (grades[i] == 5) {
                    excellentCount++; // пятерка
                }
            }

            // расчет стипендии (только если нет задолженностей)
            if (!hasDebt) {
                if (excellentCount == 4) {
                    // все отлично - повышенная стипендия
                    hasIncreasedScholarship = true;
                }
                else if (satisfactoryCount == 0 && excellentCount != 4) {
                    // нет троек, только 4 и 5 - обычная стипендия
                    hasRegularScholarship = true;
                }
                // если есть тройки - стипендии нет
            }

            // запись ответа в файл ответов
            fA.open(nameA, ios::app);
            if (fA.is_open()) {
                fA << S.surname << " "
                    << (hasDebt ? 1 : 0) << " "
                    << (hasIncreasedScholarship ? 1 : 0) << " "
                    << (hasRegularScholarship ? 1 : 0) << endl;
                fA.close();
            }

            cout << "Обработан студент: " << S.surname
                << " Оценки: " << S.grade1 << "," << S.grade2 << "," << S.grade3 << "," << S.grade4
                << " Результат: ";
            if (hasDebt) {
                cout << "Задолженность";
            }
            else if (hasIncreasedScholarship) {
                cout << "Повышенная стипендия";
            }
            else if (hasRegularScholarship) {
                cout << "Обычная стипендия";
            }
            else {
                cout << "Без стипендии";
            }
            cout << endl;
        }
        fR.close();
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
