
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    
    string surname;
    int g1, g2, g3, g4;
    
    cout << "Введите данные студентов (фамилия и 4 оценки)" << endl;
    cout << "Для выхода введите 'end' вместо фамилии" << endl;

    while (true) {
        cout << "Фамилия: ";
        cin >> surname;
        
        if (surname == "end") break;
        
        cout << "4 оценки: ";
        cin >> g1 >> g2 >> g3 >> g4;
        
        // Записываем в файл
        ofstream fout("REQUEST.txt", ios::app);
        fout << surname << " " << g1 << " " << g2 << " " << g3 << " " << g4 << endl;
        fout.close();
        
        cout << "Данные отправлены на обработку" << endl;
    }
    
    return 0;
}


        

         
