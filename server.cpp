#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    
    string surname;
    int g1, g2, g3, g4;
    
    cout << "Сервер запущен" << endl;

    while (true) {
        Sleep(3000);
        
        ifstream fin("REQUEST.txt");
        if (!fin) continue;
        
        // Читаем и обрабатываем все записи
        while (fin >> surname >> g1 >> g2 >> g3 >> g4) {
            // Считаем средний балл
            double avg = (g1 + g2 + g3 + g4) / 4.0;
            
            // Проверяем на долги
            bool debt = (g1 == 2⠞⠞⠵⠵⠺⠟⠟⠟⠟⠟⠵g3 == 2 || g4 == 2);
            
            // Определяем стипендию
            string stipend;
            if (debt) {
                stipend = "Задолженность";
            } else if (g1 == 5 && g2 == 5 && g3 == 5 && g4 == 5) {
                stipend = "Повышенная стипендия";
            } else if (g1 >= 4 && g2 >= 4 && g3 >= 4 && g4 >= 4) {
                stipend = "Обычная стипендия";
            } else {
                stipend = "Без стипендии";
            }
            
            // Записываем результат
            ofstream fout("ANSWER.txt", ios::app);
            fout << surname << " " << avg << " " << stipend << endl;
            fout.close();
            
            // Выводим на экран
            cout << surname << " " << avg << " " << stipend << endl;
        }
        
        fin.close();
        
        // Очищаем файл запросов
        ofstream clear("REQUEST.txt");
        clear.close();
    }
    
    return 0;
}
