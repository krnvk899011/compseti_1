#include <winsock2.h>
#include <stdio.h>
#include <locale.h>
 
#pragma comment(lib, "ws2_32.lib")
 
#define PORT 5151
 
struct Student {
    char name[50];
    int grade1, grade2, grade3, grade4;
    int has_debt;
    int scholarship;
};
 
int main() {
    // Установка русской локали
    setlocale(LC_ALL, "rus");
    
    printf("=== UDP СЕРВЕР ЗАПУЩЕН ===\n");
    
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    
    SOCKET server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("UDP Сервер готов на порту %d...\n", PORT);
    
    while(1) {
        printf("\nОжидание данных...\n");
        
        struct Student student;
        struct sockaddr_in client_addr;
        int client_size = sizeof(client_addr);
        
        recvfrom(server_socket, (char*)&student, sizeof(student), 0,
                (struct sockaddr*)&client_addr, &client_size);
        
        printf("Получено от клиента: %s, Оценки: %d,%d,%d,%d\n", 
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
        
        sendto(server_socket, (char*)&student, sizeof(student), 0,
              (struct sockaddr*)&client_addr, client_size);
        
        printf("Результат отправлен клиенту.\n");
    }
    
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
