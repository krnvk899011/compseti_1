// serverBIN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Student
{
    char surname[25]; // фамилия студента
    int grade1;       // оценка 1
    int grade2;       // оценка 2
    int grade3;       // оценка 3
    int grade4;       // оценка 4
} S;

struct Answer
{
    bool hasDebt;                // есть ли задолженность
    bool hasIncreasedScholarship; // повышенная стипендия
    bool hasRegularScholarship;   // обычная стипендия
} answer;

long size_pred;

int main()
{
    ifstream fR;
    ofstream fA;
    setlocale(LC_ALL, "rus");

    char* nameR = "C:\\REQUEST.bin"; // бинарный файл запросов клиентов
    char* nameA = "C:\\ANSWER.bin";  // бинарный файл ответов сервера

    cout << "server is working" << endl;

    // начальные установки
    fR.open(nameR, ios::binary);
    if (fR.is_open()) {
        fR.seekg(0, ios::end);
        size_pred = fR.tellg();
        fR.close();
    }
    else {
        size_pred = 0;
    }

    // начало работы сервера
    while (true)
    {
        fR.open(nameR, ios::binary);
        if (!fR.is_open()) {
            Sleep(1000);
            continue;
        }

        fR.seekg(0, ios::end);

        // есть новые запросы от клиентов?
        while (size_pred >= fR.tellg())
        {
            Sleep(100);
            fR.seekg(0, ios::end);
        }

        // получен новый запрос
        fR.seekg(size_pred, ios::beg);
        fR.read((char*)&S, sizeof(S));
        size_pred = fR.tellg();
        fR.close();

        // обработка данных студента
        bool hasDebt = false;
        bool hasIncreasedScholarship = false;
        bool hasRegularScholarship = false;

        // проверка на задолженности и подсчет оценок
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
            else if (satisfactoryCount == 0 && excellentCount + goodCount == 4) {
                // нет троек, только 4 и 5 - обычная стипендия
                hasRegularScholarship = true;
            }
            // если есть тройки - стипендии нет
        }

        // формирование ответа
        answer.hasDebt = hasDebt;
        answer.hasIncreasedScholarship = hasIncreasedScholarship;
        answer.hasRegularScholarship = hasRegularScholarship;

        // передача ответа клиенту
        fA.open(nameA, ios::binary | ios::app);
        fA.write((char*)&answer, sizeof(answer));
        fA.close();

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
