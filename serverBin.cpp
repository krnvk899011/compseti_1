
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

int main() {
    setlocale(LC_ALL, "Rus");
    long lastSize = 0;

    while (true) {
        ifstream file("C:/Users/rain2/OneDrive/Рабочий стол/CompSeti/Client_bin/client.bin", ios::binary);
        if (!file) {
            // Если файл не существует, ждем и проверяем снова
            this_thread::sleep_for(chrono::milliseconds(500));
            continue;
        }

        file.seekg(0, ios::end);
        long currentSize = file.tellg();
        file.close();

        if (currentSize > lastSize) {
            ifstream in("C:/Users/rain2/OneDrive/Рабочий стол/CompSeti/Client_bin/client.bin", ios::binary);
            in.seekg(lastSize);

            StudentRequest request;
            while (in.read(reinterpret_cast<char*>(&request), sizeof(StudentRequest))) {
                // Обработка запроса
                StudentResponse response;

                // Проверка корректности оценок
                if (request.g1 > 5  request.g1 < 2  request.g2 > 5  request.g2 < 2 
                    request.g3 > 5  request.g3 < 2  request.g4 > 5  request.g4 < 2) {
                    strncpy_s(response.result, "Введите корректные значения от 2 до 5", sizeof(response.result) - 1);
                    response.result[sizeof(response.result) - 1] = '\0';
                }
                // Проверка задолженностей
                else if (request.g1 < 3  request.g2 < 3  request.g3 < 3  request.g4 < 3) {
                    string result_str = string(request.name) + ": Есть задолженности";
                    strncpy_s(response.result, result_str.c_str(), sizeof(response.result) - 1);
                    response.result[sizeof(response.result) - 1] = '\0';
                }
                else {
                    // Расчет стипендии
                    double avg = (request.g1 + request.g2 + request.g3 + request.g4) / 4.0;

                    if (request.g1 < 4  request.g2 < 4  request.g3 < 4 || request.g4 < 4) {
                        string result_str = string(request.name) + ": Нет стипендии, у студента есть отметка 3 (средний балл " + to_string(avg) + ")";
                        strncpy_s(response.result, result_str.c_str(), sizeof(response.result) - 1);
                        response.result[sizeof(response.result) - 1] = '\0';
                    }
                    else if (avg >= 4.5) {
                        string result_str = string(request.name) + ": Повышенная стипендия (средний балл " + to_string(avg) + ")";
                        strncpy_s(response.result, result_str.c_str(), sizeof(response.result) - 1);
                        response.result[sizeof(response.result) - 1] = '\0';
                    }
                    else if (avg >= 4.0) {
                        string result_str = string(request.name) + ": Обычная стипендия (средний балл " + to_string(avg) + ")";
                        strncpy_s(response.result, result_str.c_str(), sizeof(response.result) - 1);
                        response.result[sizeof(response.result) - 1] = '\0';
                    }
                    else {
                        string result_str = string(request.name) + ": Нет стипендии (средний балл " + to_string(avg) + ")";
                        strncpy_s(response.result, result_str.c_str(), sizeof(response.result) - 1);
                        response.result[sizeof(response.result) - 1] = '\0';
                    }
                }

                // Отправка ответа
                ofstream out("C:/Users/rain2/OneDrive/Рабочий стол/CompSeti/Server_bin/server.bin", ios::binary | ios::app);
                if (out) {
                    out.write(reinterpret_cast<char*>(&response), sizeof(StudentResponse));
                    out.close();
                } 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
