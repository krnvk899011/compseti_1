// clientBIN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>

using namespace std;

struct StudentRequest {
    char name[50];
    int g1, g2, g3, g4;
};

struct StudentResponse {
    char result[200];
};

void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n') continue;
}

int main() {
    setlocale(LC_ALL, "Rus");
    long lastSize = 0;

    while (true) {
        cout << "Введите фамилию и 4 оценки (через пробел): ";
        string name;
        int g1, g2, g3, g4;

        cin >> name;
        if (cin >> g1 >> g2 >> g3 >> g4) {
            // Успешно считали 5 значений
            clearInputBuffer(); // Очищаем буфер от лишних символов

            // Формируем запрос
            StudentRequest request;
            strncpy_s(request.name, name.c_str(), 49);
            request.name[49] = '\0';
            request.g1 = g1;
            request.g2 = g2;
            request.g3 = g3;
            request.g4 = g4;

            // Отправляем запрос
            ofstream out("C:/Users/rain2/OneDrive/Рабочий стол/CompSeti/Client_bin/client.bin", ios::binary | ios::app);
            if (out) {
                out.write(reinterpret_cast<char*>(&request), sizeof(StudentRequest));
                out.close();
                cout << "Запрос отправлен. Ожидаю ответ...\n";
            }
            else {
                cout << "Ошибка открытия файла!" << endl;
                continue;
            }

            // Ждем ответ
            bool responseReceived = false;
            for (int i = 0; i < 50 && !responseReceived; i++) {
                ifstream in("C:/Users/rain2/OneDrive/Рабочий стол/CompSeti/Server_bin/server.bin", ios::binary);
                if (in) {
                    in.seekg(0, ios::end);
                    long currentSize = in.tellg();
                    in.close();

                    if (currentSize > lastSize) {
                        ifstream respFile("C:/Users/rain2/OneDrive/Рабочий стол/CompSeti/Server_bin/server.bin", ios::binary);
                        if (respFile) {
                            respFile.seekg(lastSize);
                            StudentResponse response;
                            if (respFile.read(reinterpret_cast<char*>(&response), sizeof(StudentResponse))) {
                                cout << "Результат: " << response.result << endl;
                                responseReceived = true;
                                lastSize = currentSize;
                            }
                            respFile.close();
                        }
                    }
                }

                // Пауза 100ms с использованием chrono (кроссплатформенный способ)
                this_thread::sleep_for(chrono::milliseconds(100));
            }

            if (!responseReceived) {
                cout << "Ответ не получен." << endl;
            }

        }
        else {
            cout << "Ошибка ввода! Введите фамилию и 4 числа." << endl;
            clearInputBuffer();
        }
    }

    return 0;
}
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
