#include <queue>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <exception>

using namespace std;

//форма представления графа
template <class EdgeT> class GraphForm {
public:
    //Вставка и удаление вершин и рёбер
    virtual bool InsertV(int index) = 0;
    virtual bool DeleteV(int index) = 0;
    virtual bool InsertE(int v1, int v2, EdgeT* t) = 0;
    virtual bool DeleteE(int v1, int v2) = 0;
    //Удалить входящие и исходящие из вершины рёбра
    virtual int DeleteEsFromVertex(int index, bool directed) = 0;
    //Проверка и получение
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual EdgeT* getEdge(int v1, int v2) = 0;
};

//форма представления матричная
template <class EdgeT> class GraphMatrixForm : public GraphForm < EdgeT > {
    friend class EdgeIterator;
    bool directed;
public:
    vector<vector<EdgeT*>> matrix;	//Матрица смежности
    vector<vector<EdgeT*>> matrix_tmp1;  //temp Матрица смежности
    vector<vector<EdgeT*>> matrix_tmp2;  //temp Матрица смежности

    GraphMatrixForm(bool directed) : directed(directed) {}

    //Вставка и удаление вершин и рёбер
    bool InsertV(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index > size) return false;
        //Создаём новую пустую строку
        vector<EdgeT*> newLine;
        newLine.assign(size, NULL);
        //Вставляем новую строку:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;
        //Вставляем новый столбец:
        for (int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, (EdgeT*)NULL);
        return true;
    }

    bool DeleteV(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return false;
        //Удаляем строку:
        matrix.erase(matrix.begin() + index);
        --size;
        //Удаляем столбец:
        for (int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);
        return true;
    }

    bool InsertE(int v1, int v2, EdgeT* t) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Петля или ребро уже есть
        if (v1 == v2 || matrix[v1][v2] != NULL) return false;
        //Вставляем ребро
        matrix[v1][v2] = t;
        return true;
    }

    bool DeleteE(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Ребра нет
        if (v1 == v2 || matrix[v1][v2] == NULL) return false;
        matrix[v1][v2] = NULL;
        return true;
    }

    //Удалить входящие и исходящие из вершины рёбра
    int DeleteEsFromVertex(int index, bool directed) {
        int size = matrix.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size) return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; i++) {
            if (matrix[i][index] != NULL) {
                delete matrix[i][index];
                matrix[i][index] = NULL;
                ++deleted;
                //Стираем симметричное ребро, если граф неориентированный
                if (directed == false)
                    matrix[index][i] = NULL;
            }
            if (matrix[index][i] != NULL) {
                delete matrix[index][i];
                matrix[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;
    }

    //Проверка и получение
    bool hasEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        if (v1 == v2) //Петля
            return false;
        if (matrix[v1][v2] != NULL)
            return true;
        return false;
    }

    EdgeT* getEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw bad_exception();
        if (v1 == v2 || matrix[v1][v2] == NULL)//Петля
            throw bad_exception();
        return matrix[v1][v2];
    }

    //Итератор рёбер
    class EdgeIterator {
        bool end;
        GraphMatrixForm* f;
    public:
        int curI, curJ;
        EdgeIterator(GraphMatrixForm* f) {
            this->f = f;
            begin();
        }
        bool begin() {
            for (int i = 0; i < f->matrix.size(); ++i)
                for (int j = 0; j < f->matrix.size(); ++j)
                    if (f->matrix[i][j]) {
                        curI = i;
                        curJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }
        bool onEnd() { return end; }
        bool toend() {
            for (int i = f->matrix.size() - 1; i >= 0; --i)
                for (int j = f->matrix.size() - 1; j >= 0; --j)
                    if (f->matrix[i][j]) {
                        curI = i;
                        curJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curI < f->matrix.size()) {
                while (curJ < f->matrix.size()) {
                    if (f->matrix[curI][curJ])
                        return true;
                    ++curJ;
                }
                ++curI;
                curJ = (f->directed ? 0 : curI + 1);
            }
            end = true;
            return false;
        }

        EdgeT* getEdge() {
            if (end)
                throw bad_exception();
            if (!(f->matrix[curI][curJ]))
                throw bad_exception();
            return f->matrix[curI][curJ];
        }
    };

    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        int curI, curJ;
        bool end;
        GraphMatrixForm* f;
    public:
        OutputEdgeIterator(GraphMatrixForm* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }

        bool begin() {
            for (curJ = 0; curJ < f->matrix.size(); curJ++)
                if (f->matrix[curI][curJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool toend() {
            for (curJ = f->matrix.size() - 1; curJ >= 0; --curJ)
                if (f->matrix[curI][curJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curJ < f->matrix.size()) {
                if (f->matrix[curI][curJ])
                    return true;
                ++curJ;
            }
            end = true;
            return false;
        }

        EdgeT* getEdge() {
            if (end)
                throw bad_exception();
            return f->matrix[curI][curJ];
        }
    };
};

//форма представления список---------------------------------------------------
template <class EdgeT> class GraphListForm : public GraphForm < EdgeT > {
    //Элемент списка
    class Node {
    public:
        EdgeT* edge; //Само ребро
        int v2;      //Вторая вершина, которую ребро соединяет
    };

    bool directed;
    vector<list<GraphListForm<EdgeT>::Node>> edgeList; //Списки смежности
public:
    GraphListForm(bool directed) : directed(directed) {}

    //Вставка и удаление вершин и рёбер
    bool InsertV(int index) {
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index > size) //Неверный номер вершины
            return false;
        //Создаём новый список смежности
        list<GraphListForm<EdgeT>::Node> newList;
        //Вставляем
        edgeList.insert(edgeList.begin() + index, newList);
        ++size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                    ++((*j).v2);//то увеличиваем этот номер
        return true;
    }

    bool DeleteV(int index) {
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index >= size)  //Неверный номер вершины
            return false;
        //Удаляем из списков записи о рёбрах
        for (int i = 0; i < size; ++i)
            for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    edgeList[i].erase(j);
                    break;
                }
        //Удаляем список смежности
        edgeList.erase(edgeList.begin() + index);
        --size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)//
                if ((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,//
                    --((*j).v2);//то уменьшить этот номер//
        return true;
    }

    bool InsertE(int v1, int v2, EdgeT* t) {
        int size = edgeList.size(); //Число вершин
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//Неверный номер вершины
            return false;
        if (v1 == v2 || hasEdge(v1, v2))  //Петля или ребро уже есть
            return false;
        //Вставляем ребро
        Node node;
        node.edge = t;
        node.v2 = v2;
        edgeList[v1].push_front(node);
        return true;
    }

    bool DeleteE(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Ребра нет
        if (v1 == v2 || hasEdge(v1, v2) == false)
            return false;
        //Удаляем ребро
        for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }

    //Удалить входящие и исходящие из вершины рёбра
    int DeleteEsFromVertex(int index, bool directed) {
        int size = edgeList.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; ++i)
            for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    //Стираем симметричное ребро
                    if (!directed)
                        for (typename list<GraphListForm<EdgeT>::Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                            if ((*k).v2 == i) {
                                edgeList[index].erase(k);
                                break;
                            }
                    delete (*j).edge;
                    edgeList[i].erase(j);
                    ++deleted;
                    break;
                }
        return deleted;
    }

    //Проверка и получение
    bool hasEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Петля
        if (v1 == v2)
            return false;
        for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }

    EdgeT* getEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw bad_exception();
        //Петля
        if (v1 == v2)
            throw bad_exception();
        for (typename list<GraphListForm<EdgeT>::Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw bad_exception();
    }

    //Итератор рёбер
    class EdgeIterator {
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        EdgeIterator(GraphListForm* f) {
            this->f = f;
        }

        //Установить итератор рёбер на начальное ребро
        bool begin() {
            for (curI = 0; curI < f->edgeList.size(); ++curI)
                for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                    if ((*curJ).edge) {
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        //Установить итератор рёбер на конечное ребро
        bool toend() {
            typename list<typename GraphListForm<EdgeT>::Node>::iterator prev_curJ;
            for (curI = 0; curI < f->edgeList.size(); ++curI) {
                for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ) {
                    if ((*curJ).edge)
                        prev_curJ = curJ;
                    if (!(*prev_curJ).edge) {
                        end = true;
                        return false;
                    }
                    else {
                        end = false;
                        curJ = prev_curJ;
                        return true;
                    }
                }
            }
        }

        //Переход к следующей позиции
        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curI < f->edgeList.size()) {
                while (curJ != f->edgeList[curI].end()) {
                    if ((*curJ).edge && (f->directed || !f->directed && (*curJ).v2 > curI))
                        return true;
                    ++curJ;
                }
                ++curI;
                if (curI < f->edgeList.size())
                    curJ = f->edgeList[curI].begin();
            }
            end = true;
            return true;
        }

        EdgeT* getEdge() {
            if (end)
                throw bad_exception();
            return (*curJ).edge;
        }
    };

    //Итератор исходящих рёбер
    class OutputEdgeIterator {
    private:
        int curI;
        typename list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm* f;
    public:
        OutputEdgeIterator(GraphListForm* f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }

        bool begin() {
            for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if ((*curJ).edge) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        bool toend() {
            typename list<typename GraphListForm<EdgeT>::Node>::iterator prev_curJ;
            for (curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if ((*curJ).edge)
                    prev_curJ = curJ;
            if (!(*prev_curJ).edge) {
                end = true;
                return false;
            }
            else {
                end = false;
                curJ = prev_curJ;
                return true;
            }
        }

        bool next() {
            if (end)
                return false;
            ++curJ;
            while (curJ != f->edgeList[curI].end()) {
                if ((*curJ).edge)
                    return true;
                ++curJ;
            }
            end = true;
            return true;
        }

        EdgeT* getEdge() {
            if (end)
                throw bad_exception();
            return (*curJ).edge;
        }
    };
};