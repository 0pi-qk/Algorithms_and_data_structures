#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

int main() {
    system("chcp 65001");
    int menu;
    bool on = false;
    Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>* graph;
    graph = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>();
    Vertex<int, int>* vertex;
    Edge<Vertex<int, int>, int, int>* edge;
    Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::VertexIterator* vIt;
    vIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::VertexIterator(*graph);
    Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::EdgeIterator* eIt;
    eIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::EdgeIterator(*graph);
    Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::OutputEdgeIterator* oIt;
    Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::Euler* eIl;
    bool out = true;
    while (out) {
        system("cls");
        cout << "01| Создать пустой L-граф с нулевым числом вершин и ребер" << endl;
        cout << "02| Создать граф с V вершинами, без ребер, типа D, формы представления F" << endl;
        cout << "03| Создать граф с V вершинами, с E случайными ребрами, типа D , формы F" << endl;
        cout << "04| Выход" << endl;
        cout << endl << "--> ";
        cin >> menu;
        switch (menu) {
            case 1: {
                cout << endl << "1" << endl;
                out = false;
                break;
            };
            case 2: {
                int tmp1, tmp2, tmp3;
                cout << "Введите количество вершин: ";
                cin >> tmp1;
                cout << "Ориентированный ли граф (0 - нет, 1 - да): ";
                cin >> tmp2;
                if (tmp2 == 1) on = true;
                cout << "Форму графа (0 - список, 1 - матрица): ";
                cin >> tmp3;
                graph = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>(tmp1, tmp2, tmp3);
                vIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::VertexIterator(*graph);
                eIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::EdgeIterator(*graph);
                cout << endl << "1" << endl;
                out = false;
                break;
            };
            case 3: {
                int tmp1, tmp2, tmp3, tmp4;
                cout << "Введите количество вершин: ";
                cin >> tmp1;
                cout << "Введите количество ребер: ";
                cin >> tmp2;
                cout << "Ориентированный ли граф (0 - нет, 1 - да): ";
                cin >> tmp3;
                if (tmp3 == 1) on = true;
                cout << "Форму графа (0 - список, 1 - матрица): ";
                cin >> tmp4;
                graph = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>(tmp1, tmp2, tmp3, tmp4);
                vIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::VertexIterator(*graph);
                eIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::EdgeIterator(*graph);
                cout << endl << "1" << endl;
                out = false;
                break;
            };
            case 4: {            //выход
                return 0;
            };
            default: {
                break;
            };
        }
    }
    while (true) {
        system("pause");
        system("cls");
        cout << "00| Распечатать граф" << endl;
        cout << "01| Опрос числа вершин в графе" << endl;
        cout << "02| Опрос числа ребер в графе" << endl;
        cout << "03| Опрос типа графа" << endl;
        cout << "04| Опрос формы представления графа" << endl;
        cout << "05| Опрос коэффициента насыщенности графа" << endl;
        cout << "06| Преобразовать граф к L-форме" << endl;
        cout << "07| Преобразовать граф к M-форме" << endl;
        cout << "08| Добавить вершину к графу" << endl;
        cout << "09| Удалить вершину из графа" << endl;
        cout << "10| Вставить ребро в граф" << endl;
        cout << "11| Удалить ребро из графа" << endl;
        cout << "\tОперации над вершинами:" << endl;
        cout << "12| Прочитать данные о вершине" << endl;
        cout << "13| Записать данные о вершине" << endl;
        cout << "14| Перезаписать имя вершины" << endl;
        cout << "\tОперации над ребрами:" << endl;
        cout << "15| Прочитать вес ребра" << endl;
        cout << "16| Прочитать данные о ребре" << endl;
        cout << "17| Записать данные о ребре" << endl;
        cout << "18| Записать вес ребра" << endl;
        cout << "\tИтератор вершин:" << endl;
        cout << "19| Установить итератор вершин на начальную вершину" << endl;
        cout << "20| Установить итератор вершин на конечную вершину" << endl;
        cout << "21| Переход к следующей позиции" << endl;
        cout << "22| Прочитать вершину по текущей позиции итератора" << endl;
        cout << "23| Прочитать данные вершины по текущей позиции итератора" << endl;
        cout << "24| Записать данные вершины по текущей позиции итератора" << endl;
        cout << "25| Записать имя вершины по текущей позиции итератора" << endl;
        cout << "\tИтератор ребер:" << endl;
        cout << "26| Установить итератор ребер на начальное ребро" << endl;
        cout << "27| Установить итератор ребер на конечное ребро" << endl;
        cout << "28| Переход к следующей позиции" << endl;
        cout << "29| Прочитать вершины ребра и вес по текущей позиции итератора" << endl;
        cout << "30| Прочитать данные ребра по текущей позиции итератора" << endl;
        cout << "31| Записать данные о ребре по текущей позиции итератора" << endl;
        cout << "32| Записать вес ребра по текущей позиции итератора" << endl;
        cout << "\t33| Итератор исходящих ребер" << endl;
        cout << "34| Двух проходной Эйлеров цикл" << endl;
        cout << "35| Выход" << endl;
        cout << endl << "--> ";
        cin >> menu;
        switch (menu) {
            case 0: {
                graph->print_graph();
                break;
            };
            case 1: {
                cout << endl << graph->V() << endl;
                break;
            };
            case 2: {
                cout << endl << graph->E() << endl;
                break;
            };
            case 3: {
                if (graph->Directed() == 0) cout << endl << "0, Hеориентированный" << endl;
                else cout << endl << "1, Oриентированный" << endl;
                break;
            };
            case 4: {
                if (graph->Dense() == 0) cout << endl << "0, L-граф" << endl;
                else cout << endl << "1, M-граф" << endl;
                break;
            };
            case 5: {
                cout << endl << graph->K() << endl;
                break;
            };
            case 6: {
                graph->ToListGraph();
                cout << endl << "1" << endl;
                break;
            };
            case 7: {
                graph->ToMatrixGraph();
                cout << endl << "1" << endl;
                break;
            };
            case 8: {
                if (graph->InsertV()) cout << endl << "1" << endl;
                else cout << endl << "0" << endl;
                break;
            };
            case 9: {
                int v1;
                cout << "Введите удаляемую вершину: ";
                cin >> v1;
                cout << endl << graph->DeleteV1(v1) << endl;
                break;
            }
            case 10: {
                int v1, v2;
                bool tmp;
                cout << "Введите вершину, из которой выходит ребро: ";
                cin >> v1;
                cout << "Введите вершину, в которую входит ребро: ";
                cin >> v2;
                cout << endl << graph->InsertE(v1, v2) << endl;
                break;
            };
            case 11: {
                int v1, v2;
                cout << "Введите вершину, из которой выходит ребро: ";
                cin >> v1;
                cout << "Введите вершину, в которую входит ребро: ";
                cin >> v2;
                cout << endl << graph->DeleteE(v1, v2) << endl;
                break;
            };
            case 12: {
                int tmp;
                int v;
                cout << "Введите имя вершины: ";
                cin >> v;
                tmp = graph->read_data_vertex(v);
                if (tmp != -1) cout << endl << "Данные вершины: " << tmp << endl;
                else cout << endl << "Данные вершины: NULL" << endl;
                break;
            };
            case 13: {
                int tmp;
                int v;
                cout << "Введите имя вершины: ";
                cin >> v;
                cout << "Введите данные: ";
                cin >> tmp;
                cout << endl <<graph->write_data_vertex(v, tmp) << endl;
                break;
            };
            case 14: {
                int v1, v2;
                cout << "Введите старое имя вершины: ";
                cin >> v1;
                cout << "Введите новое имя: ";
                cin >> v2;
                cout << endl << graph->write_name_vertex(v1, v2) << endl;
                break;
            };
            case 15: {
                int tmp;
                int v1, v2;
                cout << "Введите имя исходящей вершины: ";
                cin >> v1;
                cout << "Введите имя входящей вершины: ";
                cin >> v2;
                tmp = graph->read_weight_edge(v1, v2);
                if (tmp != -1) cout << endl << "Вес ребра: " << tmp << endl;
                else cout << endl << "Ребра нет" << endl;
                break;
            };
            case 16: {
                int tmp;
                int v1, v2;
                cout << "Введите имя исходящей вершины: ";
                cin >> v1;
                cout << "Введите имя входящей вершины: ";
                cin >> v2;
                tmp = graph->read_data_edge(v1, v2);
                if (tmp != -1) cout << endl << "Данные ребра: " << tmp << endl;
                else cout << endl << "Данные ребра: NULL" << endl;
                break;
            };
            case 17: {
                int tmp;
                bool tmp1;
                int v1, v2;
                cout << "Введите имя исходящей вершины: ";
                cin >> v1;
                cout << "Введите имя входящей вершины: ";
                cin >> v2;
                cout << "Введите данные: ";
                cin >> tmp;
                tmp1 = graph->write_data_edge(v1, v2, tmp);
                if (tmp1 == true) cout << endl << tmp1 << endl;
                else cout << endl << "Ребра нет" << endl;
                break;
            };
            case 18: {
                int tmp;
                bool tmp1;
                int v1, v2;
                cout << "Введите имя исходящей вершины: ";
                cin >> v1;
                cout << "Введите имя входящей вершины: ";
                cin >> v2;
                cout << "Введите вес: ";
                cin >> tmp;
                tmp1 = graph->write_weight_edge(v1, v2, tmp);
                if (tmp1 == true) cout << endl << tmp1 << endl;
                break;
            };
            case 19: {
                cout << endl << vIt->begin() << endl;
                break;
            };
            case 20: {
                cout << endl << vIt->toend() << endl;
                break;
            };
            case 21: {
                bool tmp;
                tmp = ++ * vIt;
                if (tmp)
                    cout << endl << tmp << endl;
                break;
            };
            case 22: {
                int tmp;
                try {
                    tmp = vIt->read_vertex();
                }
                catch (exception) {
                    cout << endl << "Исключение" << endl;
                    break;
                }
                cout << endl << "Вершина на текущей позиции итератора: " << tmp << endl;
                break;
            };
            case 23: {
                int tmp;
                try {
                    tmp = vIt->read_data_vertex();
                }
                catch (exception) {
                    cout << endl << "Исключение" << endl;
                    break;
                }
                if (tmp != -1) cout << endl << "Данные вершины на текущей позиции итератора: " << tmp << endl;
                break;
            };
            case 24: {
                int tmp;
                bool tmp2;
                cout << "Введите данные: ";
                cin >> tmp;
                tmp2 = vIt->write_data_vertex(tmp);
                if (tmp2)
                    cout << endl << tmp2 << endl;
                break;
            };
            case 25: {
                int cur;
                bool tmp;
                cout << "Введите имя: ";
                cin >> cur;
                tmp = vIt->write_name_vertex(cur);
                if (tmp) cout << endl << tmp << endl;
                break;
            };
            case 26: {
                cout << endl << eIt->begin() << endl;
                break;
            };
            case 27: {
                cout << endl << eIt->toend() << endl;
                break;
            };
            case 28: {
                cout << endl << ++ * eIt << endl;
                break;
            };
            case 29: {
                string tmp;
                try {
                    tmp = eIt->read_edge();
                }
                catch (exception) {
                    cout << endl << "Исключение" << endl;
                    break;
                }
                cout << endl << tmp << endl;
                break;
            };
            case 30: {
                int tmp;
                try {
                    tmp = eIt->read_data_edge();
                }
                catch (exception) {
                    cout << endl << "Исключение" << endl;
                    break;
                }
                cout << endl << "Данные ребра по текущей позиции итератора: " << tmp << endl;
                break;
            };
            case 31: {
                int tmp;
                cout << "Введите данные: ";
                cin >> tmp;
                cout << endl << eIt->write_data_edge(tmp) << endl;
                break;
            };
            case 32: {
                int tmp;
                cout << "Введите вес: ";
                cin >> tmp;
                cout << endl << eIt->write_weight_edge(tmp) << endl;
                break;
            };

                //-------------------------------------------------------
                //Итератор исходящих ребер
            case 33: {
                int tmp, tmp2;        //узел
                cout << endl << "Введите вершину: ";
                cin >> tmp;
                try {
                    oIt = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::OutputEdgeIterator(*graph, *graph->getVertex(tmp));
                }
                catch (exception) {
                    cout << endl << "Исключение" << endl;
                    break;
                };
                out = true;
                while (out) {
                    system("pause");
                    system("cls");
                    cout << "Итератор исходящих ребер:" << endl;
                    cout << "01| Установить итератор исходящих ребер на начальное ребро" << endl;
                    cout << "02| Установить итератор исходящих ребер на конечное ребро" << endl;
                    cout << "03| Переход к следующей позиции" << endl;
                    cout << "04| Прочитать вершины ребра и вес по текущей позиции итератора" << endl;
                    cout << "05| Прочитать данные ребра по текущей позиции итератора" << endl;
                    cout << "06| Записать данные о ребре по текущей позиции итератора" << endl;
                    cout << "07| Записать вес ребра по текущей позиции итератора" << endl;
                    cout << "08| Вернуться в предыдущее меню" << endl;
                    cout << endl << "--> ";
                    cin >> tmp2;
                    switch (tmp2) {
                        case 1: {
                            cout << endl << oIt->begin() << endl;
                            break;
                        };
                        case 2: {
                            cout << endl << oIt->toend() << endl;
                            break;
                        };
                        case 3: {
                            cout << endl << ++ * oIt << endl;
                            break;
                        };
                        case 4: {
                            string tmp;
                            try {
                                tmp = oIt->read_edge();
                            }
                            catch (exception) {
                                cout << endl << "Исключение" << endl;
                                break;
                            };
                            cout << endl << tmp << endl;
                            break;
                        };
                        case 5: {
                            int tmp;
                            try {
                                tmp = oIt->read_data_edge();
                            }
                            catch (exception) {
                                cout << endl << "Исключение" << endl;
                                break;
                            }
                            cout << endl << "Данные ребра по текущей позиции итератора: " << tmp << endl;
                            break;
                        };
                        case 6: {
                            int tmp;
                            cout << "Введите данные: ";
                            cin >> tmp;
                            cout << endl << oIt->write_data_edge(tmp) << endl;
                            break;
                        };
                        case 7: {
                            int tmp;
                            cout << "Введите вес: ";
                            cin >> tmp;
                            cout << endl << oIt->write_weight_edge(tmp) << endl;
                            break;
                        };
                        case 8: {
                            out = false;
                            break;
                        };
                        default: {
                            break;
                        };
                    }
                }
                break;
            }
            case 34: {
                eIl = new Graph<Vertex<int, int>, Edge<Vertex<int, int>, int, int>>::Euler(*graph);
                int* temp = new int;
                int nn;
                bool tmp;
                tmp = eIl->DFS(temp, nn);
                cout << endl;
                if (!tmp) cout << "Эйлеров цикл: " << temp;
                else
                    for (int i = 0; i < nn; i++) {
                        cout << temp[i] << "  ";
                    }
                cout << endl;
                break;
            }
            case 35: {                //выход
                return 0;
            };
                break;
            default: {
                break;
            };
        }
    }
    return 0;
}
