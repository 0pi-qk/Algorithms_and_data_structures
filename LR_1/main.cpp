#include <iostream>
#include "list.h"

#define developer true

using namespace std;

int main() {
    system("chcp 65001");
    list<int> list_1;
    list<int>::Iterator itr = list_1.begin();
    list<int>::reIterator r_itr(&list_1);
    r_itr = list_1.rbegin();
    int tmp1, tmp2;
    bool out = true;
    while (out) {
        system("cls");
        if (developer == true) {
            cout << "\t\t\tМеню разработчика:" << endl;
            cout << "Количество элементов: " << list_1.Get_size() << endl;
            cout << "Ёмкость списка: " << list_1.Get_capacity() << endl;
            cout << "Содержимое списка:  ";
            for (int i = 0; i < list_1.Get_size(); i++)
                cout << list_1.get_value_by_index(i) << "  ";
            cout << endl;
            cout << "Текущее положение прямого итератора:  ";
            try
            {
                cout << *itr << endl;
            }
            catch (const char* exs)
            {
                cout << ex << endl;
            }
            cout << "Текущее положение обратного итератора:  ";
            try
            {
                cout << *r_itr << endl;
            }
            catch (const char* exs)
            {
                cout << ex << endl;
            }
            cout << "============================================================" << endl;
        }
        cout << "\t\t\tМеню Списка:" << endl;
        cout << "01| Добавить новое значение в конец" << endl;
        cout << "02| Добавить новое значение в начало" << endl;
        cout << "03| Добавить новое значение в позицию с заданным номером" << endl;
        cout << "04| Получить позицию в списке по значению" << endl;
        cout << "05| Получить значение по позиции в списке" << endl;
        cout << "06| Изменить элемент списка" << endl;
        cout << "07| Удалить заданное значение из всего списка" << endl;
        cout << "08| Удалить заданное значение из списка (первое)" << endl;
        cout << "09| Удалить значение по позиции" << endl;
        cout << "10| Проверить есть ли такое значение" << endl;
        cout << "11| Получить размерность списка" << endl;
        cout << "12| Проверить список на пустоту" << endl;
        cout << "13| Очистить список" << endl;
        cout << "14| Получить число пройденных элементов (для 3, 8, 9)" << endl;
        cout << "15| Вывести весь список" << endl;
        cout << "16| Выйти из меню" << endl;
        cout << "17| Запрос прямого оператора begin()" << endl;
        cout << "18| Запрос 'неустановленного' прямого итератора end()" << endl;
        cout << "19| Запрос прямого оператора rbegin()" << endl;
        cout << "20| Запрос 'неустановленного' прямого итератора rend()" << endl;
        cout << "21| Итератор" << endl;
        cout << endl << "-> ";
        cin >> tmp1;
        switch (tmp1){
            case 1:
                cout << "Введите новое значение: ";
                cin >> tmp2;
                list_1.Add_back(tmp2);
                break;
            case 2:
                cout << "Введите новое значение: ";
                cin >> tmp2;
                list_1.Add_front(tmp2);
                break;
            case 3:
                cout << "Введите новое значение: ";
                cin >> tmp1;
                cout << "Введите номер вставки: ";
                cin >> tmp2;
                cout << list_1.Add_num(tmp1, tmp2) << endl;
                system("pause");
                break;
            case 4:
                cout << "Значение: ";
                cin >> tmp2;
                cout << list_1.Get_pos_by_num(tmp2) << endl;
                system("pause");
                break;
            case 5:
                cout << "Введите номер значения: ";
                cin >> tmp2;
                try {
                    cout << list_1.Get_num_by_pos(tmp2) << endl;
                }
                catch (const char* exs) {
                    cout << ex << endl;
                }
                system("pause");
                break;
            case 6:
                cout << "Введите новое значение: ";
                cin >> tmp1;
                cout << "Введите номер изменяемого значения: ";
                cin >> tmp2;
                cout << list_1.change(tmp2, tmp1) << endl;
                system("pause");
                break;
            case 7:
                cout << "Введите удаляемое значение: ";
                cin >> tmp2;
                cout << list_1.delete_value(tmp2) << endl;
                system("pause");
                break;
            case 8:
                cout << "Введите удаляемое значение: ";
                cin >> tmp2;
                cout << list_1.delete_value_one(tmp2) << endl;
                system("pause");
                break;
            case 9:
                cout << "Введите индекс удаляемого числа: ";
                cin >> tmp2;
                cout << list_1.delete_number(tmp2) << endl;
                system("pause");
                break;
            case 10:
                cout << "Введите проверяемое значение: ";
                cin >> tmp2;
                cout << list_1.check_value_have(tmp2) << endl;
                system("pause");
                break;
            case 11:
                cout << list_1.Get_size() << endl;
                system("pause");
                break;
            case 12:
                cout << list_1.check_for_emptiness() << endl;
                system("pause");
                break;
            case 13:
                list_1.clear_list();
                break;
            case 14:
                cout << list_1.check_used_elements() << endl;
                system("pause");
                break;
            case 15:
                for (int i = 0; i < list_1.Get_size(); i++)
                    cout << list_1.get_value_by_index(i) << "  ";
                cout << endl;
                system("pause");
                break;
            case 16:
                out = false;
                break;
            case 17:
                try
                {
                    itr = list_1.begin();
                }
                catch (const char* exs)
                {
                    cout << ex << endl;
                    system("pause");
                }
                break;
            case 18:
                itr = list_1.end();
                break;
            case 19:
                try
                {
                    r_itr = list_1.rbegin();
                }
                catch (const char* exs)
                {
                    cout << ex << endl;
                    system("pause");
                }
                break;
            case 20:
                r_itr = list_1.rend();
                break;
            case 21:
            {
                bool out_itr = true;
                while (out_itr) {
                    system("cls");
                    if (developer == true) {
                        cout << "\t\t\tМеню разработчика:" << endl;
                        cout << "Количество элементов: " << list_1.Get_size() << endl;
                        cout << "Ёмкость списка: " << list_1.Get_capacity() << endl;
                        cout << "Содержимое списка:  ";
                        for (int i = 0; i < list_1.Get_size(); i++)
                            cout << list_1.get_value_by_index(i) << "  ";
                        cout << endl;
                        cout << "Текущее положение прямого итератора:  ";
                        try
                        {
                            cout << *itr << endl;
                        }
                        catch (const char* exs)
                        {
                            cout << ex << endl;
                        }
                        cout << "Текущее положение обратного итератора:  ";
                        try
                        {
                            cout << *r_itr << endl;
                        }
                        catch (const char* exs)
                        {
                            cout << ex << endl;
                        }
                        cout << "============================================================" << endl;
                    }
                    cout << "\t\t\tМеню итератор:" << endl;
                    cout << "ПРЯМОЙ ИТЕРАТОР" << endl;
                    cout << "\t22| Выполнить операцию инкремента" << endl;
                    cout << "\t23| Изменить текущее значение" << endl;
                    cout << "\t24| Получить текущее значение" << endl;
                    cout << "\t25| Является ли текущее положение конечным в списке" << endl;
                    cout << "\t26| Не является ли текущее положение начальным в списке" << endl;

                    cout << endl << "ОБРАТНЫЙ ИТЕРАТОР" << endl;
                    cout << "\t27| Выполнить операцию инкремента" << endl;
                    cout << "\t28| Изменить текущее значение" << endl;
                    cout << "\t29| Получить текущее значение" << endl;
                    cout << "\t30| Является ли текущее положение конечным в списке" << endl;
                    cout << "\t31| Не является ли текущее положение начальным в списке" << endl;
                    cout << endl << "\t32| Находятся ли прямой и обратный итератор в одной позиции" << endl;
                    cout << endl << "\t33| Выйти" << endl;
                    cout << endl << "-> ";
                    cin >> tmp1;
                    switch (tmp1)
                    {
                        case 22:
                            try
                            {
                                itr++;
                            }
                            catch (const char* exs)
                            {
                                cout << ex << endl;
                                system("pause");
                            }
                            break;
                        case 23:
                            cout << "Введите новое значение: ";
                            cin >> tmp1;
                            try
                            {
                                *itr = tmp1;
                            }
                            catch (const char* exs)
                            {
                                cout << ex << endl;
                                system("pause");
                            }
                            break;
                        case 24:
                            try
                            {
                                cout << *itr << endl;
                                system("pause");
                            }
                            catch (const char* exs)
                            {
                                cout << ex << endl;
                                system("pause");
                            }
                            break;
                        case 25:
                            cout << (itr == list_1.end()) << endl;
                            system("pause");
                            break;
                        case 26:
                            cout << (itr != list_1.begin()) << endl;
                            system("pause");
                            break;
                        case 27:
                            try
                            {
                                r_itr--;
                            }
                            catch (const char* exs)
                            {
                                cout << ex << endl;
                                system("pause");
                            }
                            break;
                        case 28:
                            cout << "Введите новое значение: ";
                            cin >> tmp1;
                            try
                            {
                                *r_itr = tmp1;
                            }
                            catch (const char* exs)
                            {
                                cout << ex << endl;
                                system("pause");
                            }
                            break;
                        case 29:
                            try
                            {
                                cout << *r_itr << endl;
                                system("pause");
                            }
                            catch (const char* exs)
                            {
                                cout << ex << endl;
                                system("pause");
                            }
                            break;
                        case 30:
                            cout << (r_itr == list_1.rend()) << endl;
                            system("pause");
                            break;
                        case 31:
                            cout << (r_itr != list_1.rbegin()) << endl;
                            system("pause");
                            break;
                        case 32:
                            cout << (itr == r_itr) << endl;
                            system("pause");
                            break;
                        case 33:
                            out_itr = false;
                            break;
                        default:
                            break;
                    }
                }
            }
                break;
            default:
                break;
        }
    }
    return 0;
}