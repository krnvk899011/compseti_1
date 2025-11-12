#include <winsock2.h>
#include <stdio.h>
#include <locale.h>
 
#pragma comment(lib, "ws2_32.lib")
 
#define SERVER_IP "127.0.0.1"
#define PORT 5150
 
struct Student {
    char name[50];
    int grade1, grade2, grade3, grade4;
    int has_debt;
    int scholarship;
};
 
int is_valid_grade(int grade) {
    return grade >= 2 && grade <= 5;
}
 
int main() {
    // Установка русской локали
    setlocale(LC_ALL, "rus");
    
    printf("=== TCP КЛИЕНТ ЗАПУЩЕН ===\n");
    
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);
    
    printf("Подключение к серверу %s:%d...\n", SERVER_IP, PORT);
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Успешно подключено!\n");
    
    struct Student student;
    
    // Ввод имени студента
    printf("Введите фамилию студента: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = 0;
    
    // Ввод и проверка 4 оценок
    printf("Введите 4 оценки (только 2,3,4,5 разрешены):\n");
    
    int grades[4];
    int valid_input = 0;
    
    while (!valid_input) {
        printf("Оценка 1: ");
        scanf("%d", &grades[0]);
        printf("Оценка 2: ");
        scanf("%d", &grades[1]);
        printf("Оценка 3: ");
        scanf("%d", &grades[2]);
        printf("Оценка 4: ");
        scanf("%d", &grades[3]);
        
        // Проверка всех оценок
        valid_input = 1;
        for (int i = 0; i < 4; i++) {
            if (!is_valid_grade(grades[i])) {
                printf("Ошибка: Оценка %d должна быть между 2 и 5! Пожалуйста, попробуйте снова.\n\n", grades[i]);
                valid_input = 0;
                break;
            }
        }
    }
    
    // Записываем проверенные оценки
    student.grade1 = grades[0];
    student.grade2 = grades[1];
    student.grade3 = grades[2];
    student.grade4 = grades[3];
    
    // Отправка данных на сервер
    send(client_socket, (char*)&student, sizeof(student), 0);
    printf("Данные отправлены на сервер.\n");
    
    // Получение результата от сервера
    recv(client_socket, (char*)&student, sizeof(student), 0);
    
    // Вывод результата
    printf("\n=== РЕЗУЛЬТАТ ОТ СЕРВЕРА ===\n");
    printf("Студент: %s\n", student.name);
    printf("Оценки: %d, %d, %d, %d\n", student.grade1, student.grade2, 
                                        student.grade3, student.grade4);
    
    if (student.has_debt) {
        printf("Статус: ЕСТЬ ЗАДОЛЖЕННОСТЬ - стипендии нет\n");
    } else if (student.scholarship == 2000) {
        printf("Статус: ОТЛИЧНО - повышенная стипендия %d рублей\n", student.scholarship);
    } else if (student.scholarship == 1500) {
        printf("Статус: ХОРОШО - обычная стипендия %d рублей\n", student.scholarship);
    } else {
        printf("Статус: УДОВЛЕТВОРИТЕЛЬНО - стипендии нет\n");
    }
    
    closesocket(client_socket);
    WSACleanup();
    
    printf("\nНажмите любую клавишу для выхода...");
    getchar(); getchar();
    return 0;
}
