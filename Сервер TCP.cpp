#include <winsock2.h>
#include <stdio.h>
#include <locale.h>
 
#pragma comment(lib, "ws2_32.lib")
 
#define PORT 5150
 
struct Student {
    char name[50];
    int grade1, grade2, grade3, grade4;
    int has_debt;
    int scholarship;
};
 
int main() {
    // Установка русской локали
    setlocale(LC_ALL, "rus");
    
    printf("=== TCP СЕРВЕР ЗАПУЩЕН ===\n");
    
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("Сервер слушает порт %d...\n", PORT);
    
    while(1) {
        printf("\nОжидание подключения клиента...\n");
        
        struct sockaddr_in client_addr;
        int client_size = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_size);
        
        printf("Клиент подключен!\n");
        
        struct Student student;
        recv(client_socket, (char*)&student, sizeof(student), 0);
        
        printf("Получены данные: %s, Оценки: %d,%d,%d,%d\n", 
               student.name, student.grade1, student.grade2, 
               student.grade3, student.grade4);
        
        // Логика расчета
        student.has_debt = 0;
        student.scholarship = 0;
        
        if(student.grade1 <= 2 || student.grade2 <= 2 || 
           student.grade3 <= 2 || student.grade4 <= 2) {
            student.has_debt = 1;
            student.scholarship = 0;
        }
        else if(student.grade1 == 3 || student.grade2 == 3 || 
                student.grade3 == 3 || student.grade4 == 3) {
            student.has_debt = 0;
            student.scholarship = 0;
        }
        else if(student.grade1 == 4 || student.grade2 == 4 || 
                student.grade3 == 4 || student.grade4 == 4) {
            student.has_debt = 0;
            student.scholarship = 1500;
        }
        else {
            student.has_debt = 0;
            student.scholarship = 2000;
        }
        
        send(client_socket, (char*)&student, sizeof(student), 0);
        printf("Результат отправлен клиенту.\n");
        
        // Вывод результата на сервере
        if (student.has_debt) {
            printf("Результат для %s: ЕСТЬ ЗАДОЛЖЕННОСТЬ\n", student.name);
        } else if (student.scholarship == 2000) {
            printf("Результат для %s: ОТЛИЧНО - стипендия %d руб\n", student.name, student.scholarship);
        } else if (student.scholarship == 1500) {
            printf("Результат для %s: ХОРОШО - стипендия %d руб\n", student.name, student.scholarship);
        } else {
            printf("Результат для %s: УДОВЛЕТВОРИТЕЛЬНО - стипендии нет\n", student.name);
        }
        
        closesocket(client_socket);
        printf("Клиент отключен.\n");
    }
    
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
