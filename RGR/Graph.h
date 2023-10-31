#include <iostream>
#include <iomanip>
#include <sstream>

#include "GraphForm.h"

using namespace std;

// АТД ПРОСТОЙ ГРАФ----------------------------------------------------------
template <class VertexT, class EdgeT>
class Graph {
protected:
    vector<VertexT*> vertexVector;//Вектор вставленных
    GraphForm<EdgeT>* data;       //Данные графа
    bool directed;                //Направленный граф
    bool dense;                   //М-граф
    int edgeCounter;              //Число рёбер
    int getIndexFromName(int n);//Получение индекса вершины по дескриптору
    int sz;//размер
public:
    Graph(); //Конструктор пустого L-графа
    Graph(int vertexCount, bool directed, bool dense); //Конструктор с заданным числом вершин, заданной ориентированности и заданного типа
    Graph(int vertexCount, int edgeCount, bool directed, bool dense); //Конструктор с заданным числом вершин, случайных рёбер, заданной ориентированности и типа
    Graph(const Graph<VertexT, EdgeT>& G); //Конструктор копирования
    ~Graph(); //Деструктор
    int V();//возвращает число вершин в графе
    int E(); //возвращает число ребер в графе
    bool Dense(); //возвращает форму представления графа
    bool Directed();//возвращает тип графа
    double K(); //возвращает коэффициент насыщенности графа
    void ToListGraph();//преобразует граф к L-графу
    void ToMatrixGraph();//преобразует граф к M-графу
    VertexT* InsertV();//добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    bool DeleteV(int index);//удаляет вершину из графа, заданную адресом дескриптора v
    bool DeleteV(VertexT* v);//удаляет вершину из графа, заданную адресом дескриптора v
    bool DeleteV1(int n);
    bool InsertE(int v1, int v2);//добавляет ребро (v1, v2) к графу, соединяющую вершины, заданные адресами дескрипторов v1 и v2
    EdgeT* InsertE(VertexT* v1, VertexT* v2);
    bool DeleteE(int v1, int v2);//удаляет ребро, соединяющее вершины, заданные адресами дескрипторов v1 и v2
    bool DeleteE(VertexT* v1, VertexT* v2);
    bool deleteVertex(VertexT* v);	//Удаление вершины
    EdgeT* getEdge(VertexT* v1, VertexT* v2);	//Получение ребра
    bool hasEdge(VertexT* v1, VertexT* v2);		//Проверка на существование ребра
    bool hasEdge(int v1, int v2);
    bool write_name_vertex(int v1, int str);//Записать данные о вершине
    bool write_data_vertex(int v1, int d);//Записать данные о вершине
    int read_data_vertex(int v1);//Прочитать данные о вершине
    void print_graph();//Вывод на экран
    int read_weight_edge(int _v1, int _v2);//Прочитать вес ребра
    int read_data_edge(int _v1, int _v2);//Прочитать данные о ребре
    bool write_weight_edge(int _v1, int _v2, int w);//Записать вес ребра
    bool  write_data_edge(int _v1, int _v2, int data);//Записать данные о ребре
    VertexT* getVertexFromName(int n);
    VertexT* getVertex(int index);
    //Число вершин, рёбер, насыщенность
    int getIndex(VertexT* v);
    int getEdgeCount();
    int getVertexCount();

    //------------------------Итератор вершин графа --------------------------------------------------------
    class VertexIterator {
    private:
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф
        bool end;                     //Состояние итератора
        int current;                  //Текущее положение
    public:
        VertexIterator(Graph<VertexT, EdgeT>& g) { graph = &g; }; //Конструктор
        bool begin() {//возвращает итератор, установленный на первую вершину графа
            if (graph->vertexVector.size() == 0) {
                end = true;
                return false;
            }
            current = 0;
            end = false;
            return true;
        }

        bool operator++() {//Переход к следующей позиции
            try {
                if (end) {
                    current = -1;
                    throw bad_exception();
                }
            }
            catch (exception) {
                return false;
            }
            current++;
            if (graph->vertexVector.size() - 1 == current)
                end = true;
            return true;
        }

        bool toend() {//Установить итератор вершин на конечную вершину
            end = true;
            current = graph->vertexVector.size() - 1;
            if (current < 0)
                return false;
            else
                return true;
        }

        bool onEnd() { return end; }//Проверка на выход
        VertexT* operator*() { //Получение вершины
            if (current >= graph->vertexVector.size() || current == -1)
                throw bad_exception();
            return graph->vertexVector[current];
        }

        int read_vertex() {//Прочитать вершину по текущей позиции итератора
            VertexT* v = NULL;
            try {
                v = operator*();
            }
            catch (exception) {
                throw bad_exception();
            }
            if (v->isNameSet())
                return v->getName();
            else
                throw bad_exception();
        }

        int read_data_vertex() {//Прочитать данные вершины по текущей позиции итератора
            VertexT* v = NULL;
            try {
                v = operator*();
            }
            catch (exception) { throw bad_exception(); } {
                if (v->isDataSet())
                    return v->getData();
                else throw bad_exception();
                return NULL;
            }
        }

        bool write_data_vertex(int d) {//Записать данные о вершины по текущей позиции итератора
            VertexT* v;
            try {
                v = operator*();
            }
            catch (exception) {
                return false;
            }
            v->setData(d);
            return true;
        }

        bool write_name_vertex(int str) {//Записать имя вершины по текущей позиции итератора
            VertexT* v;
            try {
                v = operator*();
            }
            catch (exception) {
                return false;
            }
            v->setName(str);
            return true;
        }
    };

    //------------------------------Итератор рёбер-------------------------------
    class EdgeIterator {
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф
        typename GraphMatrixForm<EdgeT>::EdgeIterator* mIt;
        typename GraphListForm<EdgeT>::EdgeIterator* lIt;
        bool useM;
    public:
        int curV1, curV2;
        string str1, str2, str3, str4;
        bool end;

        EdgeIterator(Graph<VertexT, EdgeT>& g) {
            graph = &g;
            if (graph->Dense()) {
                mIt = new typename GraphMatrixForm<EdgeT>::EdgeIterator(static_cast<GraphMatrixForm<EdgeT>*>(g.data));
                useM = true;
            }
            else {
                lIt = new typename GraphListForm<EdgeT>::EdgeIterator(static_cast<GraphListForm<EdgeT>*>(g.data));
                useM = false;
            }
        }

        bool begin() {//Установка в начало
            if (useM) return
                        mIt->begin();
            else
                return lIt->begin();
        }

        bool operator++() {//Сдвиг на следующий элемент
            if (useM)
                return mIt->next();
            else
                return lIt->next();
        }

        bool onEnd() {//Проверка на выход
            if (useM)
                return mIt->onEnd();
            else
                return lIt->onEnd();
        }

        bool toend() {//Установить итератор рёбер на конечное ребро
            if (useM)
                return mIt->toend();
            else
                return lIt->toend();
        }

        EdgeT* operator*() {//Получение ребра
            if (onEnd())
                throw bad_exception();
            if (useM)
                return mIt->getEdge();
            else
                return lIt->getEdge();
        }

        string read_edge() {//Прочитать вершины ребра и вес по текущей позиции итератора
            EdgeT* e = operator*();
            VertexT* _v1, * _v2;
            _v1 = e->getVertex1();
            _v2 = e->getVertex2();
            if (!(_v1->isNameSet()))
                str1 = "Имя ребра не установлено";
            else
                str1 = to_string(_v1->getName());
            if (!(_v2->isNameSet()))
                str2 = "Данные ребра не установлены";
            else
                str2 = to_string(_v2->getName());
            if (e->isWeightSet() == false)
                str3 = "Вес ребра не установлен";
            else
                str3 = to_string(e->getWeight());
            str4 = "Исходящая вершина: " + str1 + "| Входящая вершина: " + str2 + "| Вес ребра: " + str3;
            return str4;
        }

        int read_data_edge() {//Прочитать данные ребра по текущей позиции итератора
            EdgeT* f = operator*();
            if (f->isDataSet())
                return f->getData();
            else
                throw bad_exception();
        }

        bool write_data_edge(int d) {
            EdgeT* e;
            try {
                e = operator*();
            }
            catch (exception) {
                return false;
            }
            e->setData(d);
            return true;
        }

        bool write_weight_edge(int w) {
            EdgeT* e;
            try {
                e = operator*();
            }
            catch (exception) {
                return false;
            }
            e->setWeight(w);
            return true;
        }
    };

    //Итератор исходящих рёбер графа---------------------------------------------------------
    class OutputEdgeIterator {
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф
        typename GraphMatrixForm<EdgeT>::OutputEdgeIterator* mIt;
        typename GraphListForm<EdgeT>::OutputEdgeIterator* lIt;
        bool useM;
    public:
        string str1, str2, str3, str4;
        bool end;

        OutputEdgeIterator(Graph<VertexT, EdgeT>& g, VertexT& v) {
            graph = &g;
            mIt = NULL;
            lIt = NULL;
            int curV = graph->getIndex(&v);
            if (graph->Dense()) {
                mIt = new typename GraphMatrixForm<EdgeT>::OutputEdgeIterator(static_cast<GraphMatrixForm<EdgeT>*>(g.data), curV);
                useM = true;
            }
            else {
                lIt = new typename GraphListForm<EdgeT>::OutputEdgeIterator(static_cast<GraphListForm<EdgeT>*>(g.data), curV);
                useM = false;
            }
        }

        ~OutputEdgeIterator() {
            if (mIt != NULL)
                delete mIt;
            if (lIt != NULL)
                delete lIt;
        }

        bool begin() {//Установка в начало
            if (useM)
                return mIt->begin();
            else
                return lIt->begin();
        }

        bool operator++() {//Сдвиг на следующий элемент
            if (useM)
                return mIt->next();
            else
                return lIt->next();
        }

        bool toend() {
            if (useM)
                return mIt->toend();
            else
                return lIt->toend();
        }

        bool onEnd() {//Проверка на выход
            if (useM)
                return mIt->onEnd();
            else
                return lIt->onEnd();
        }

        EdgeT* operator*() {//Получение ребра
            if (onEnd())
                throw bad_exception();
            if (useM)
                return mIt->getEdge();
            else
                return lIt->getEdge();
        }

        string read_edge() {
            EdgeT* e = operator*();
            VertexT* _v1, * _v2;
            _v1 = e->getVertex1();
            _v2 = e->getVertex2();
            if (!(_v1->isNameSet()))
                str1 = "Имя ребра не установлено";
            else
                str1 = to_string(_v1->getName());
            if (!(_v2->isNameSet()))
                str2 = "Данные ребра не установлены";
            else
                str2 = to_string(_v2->getName());
            if (e->isWeightSet() == false)
                str3 = "Вес ребра не установлен";
            else
                str3 = to_string(e->getWeight());
            str4 = "Исходящая вершина: " + str1 + "| Входящая вершина: " + str2 + "| Вес ребра: " + str3;
            return str4;
        }

        int read_data_edge() {
            EdgeT* e;
            e = operator*();
            if (e->isDataSet())
                return e->getData();
            else
                throw bad_exception();
        }

        bool write_data_edge(int d) {
            EdgeT* e;
            try {
                e = operator*();
            }
            catch (exception) {
                return false;
            }
            e->setData(d);
            return true;
        }

        bool write_weight_edge(int w) {
            EdgeT* e;
            try {
                e = operator*();
            }
            catch (exception) {
                return false;
            }
            e->setWeight(w);
            return true;
        }
    };

    // Эйлеров цикл
    class Euler {
        int* color;			//цвет вершины 0-белый, 1-серый, 2-черный
        int* p;				//подграф предшествования
        int** Adj;			//матрица смежных вершин
        int n;				//кол верш в графе
        stack <int> st;
        Graph<VertexT, EdgeT>* graph; //Обрабатываемый граф

    public:
        typename Graph<VertexT, EdgeT>::OutputEdgeIterator* out;

        Euler(Graph<VertexT, EdgeT>& g) {
            graph = &g;
        }
        Euler(const Graph<VertexT, EdgeT>& T) {
            graph = T.graph;
        }

        ~Euler() {
            delete color, p, Adj;
        }

        bool DFS(int* temp, int &st_size) {
            if (graph->directed) {
                return false;
            }
            n = graph->V();
            color = new int[n];
            p = new int[n];

            Adj = new int* [n];
            for (int i = 0; i < n; i++) {
                Adj[i] = new int[n];
            }

            for (int u = 0; u < n; u++) {
                color[u] = 0;
                p[u] = -1;
            }
            search();

            for (int u = 0; u < n; u++) {
                if (color[u] == 0) {
                    DFS_Visit(u);
                }
            }
            st_size = st.size();
            for (int i = (st_size - 1); i > -1; i--) {
                temp[i] = st.top();
                st.pop();
            }
            return true;
        }
        void DFS_Visit(int u) {
            color[u] = 1;
            for (int i = 0; i < n; i++) {
                if (Adj[u][i] == INT_MAX) {
                    break;
                }
                if (color[Adj[u][i]] == 0) {
                    st.push(u);
                    st.push(Adj[u][i]);
                    p[Adj[u][i]] = u;
                    DFS_Visit(Adj[u][i]);
                    st.push(Adj[u][i]);
                    st.push(u);
                }
                else if (color[Adj[u][i]] == 1) {
                    if (p[u] != Adj[u][i]) {
                        st.push(u);
                        st.push(Adj[u][i]);
                        st.push(Adj[u][i]);
                        st.push(u);
                    }
                }
                color[u] = 2;
            }
        }
        void search() {
            int vv1, vv2;
            for (int u = 0; u < n; u++) {
                try {
                    out = new  typename  Graph<VertexT, EdgeT>::OutputEdgeIterator(*graph, *graph->getVertex(u));
                }
                catch (exception) {
                    continue;
                }
                if (!out->begin()) {
                    continue;
                }
                for (int j = 0; j < n; j++) {
                    try {
                        out->read_edge();
                    }
                    catch (exception) {
                        Adj[u][j] = INT_MAX;
                        break;
                    }
                    stringstream stream1(out->str1);
                    stream1 >> vv1;
                    stringstream stream2(out->str2);
                    stream2 >> vv2;
                    if (u == vv2) {
                        Adj[u][j] = vv1;
                    }
                    else {
                        Adj[u][j] = vv2;
                    }
                    try {
                        ++* out;
                    }
                    catch (exception) {
                        break;
                    }
                }
            }
        }
    };

    friend class VertexIterator;  //дружественный класс
    friend class EdgeIterator;
    friend class OutputEdgeIterator;

};

//Получение индекса вершины по дескриптору
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::getIndexFromName(int n) {
    int index = 0;
    for (int i = 0; i < vertexVector.size(); i++) {
        if (vertexVector[index]->getName() == n)
            break;
        ++index;
    }
    if (index == vertexVector.size())
        throw bad_exception();
    return index;
}

//Создать пустой L-граф с нулевым числом вершин и рёбер
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::Graph() {
    sz = 0;
    data = new GraphListForm<EdgeT>(false);
    directed = false;
    dense = false;
    edgeCounter = 0;
}

//Создать граф с V вершинами, без ребер, типа D, формы представления F
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::Graph(int vertexCount, bool directed, bool dense) {
    sz = 0;
    if (dense)
        data = new GraphMatrixForm<EdgeT>(directed);
    else
        data = new GraphListForm<EdgeT>(directed);
    //Создаём вершины и помещаем в структуру
    for (int i = 0; i < vertexCount; i++)
        data->InsertV(i);
    for (int i = 0; i < vertexCount; i++) {
        VertexT* v = new VertexT();
        v->setName(sz);
        sz++;
        vertexVector.push_back(v);
        data->InsertV(i);
    }
    this->directed = directed;
    this->dense = dense;
    edgeCounter = 0;
}

//Создать граф с V вершинами, с E случайными ребрами, типа D, формы F
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::Graph(int vertexCount, int edgeCount, bool directed, bool dense) {
    sz = 0;
    if (dense)
        data = new GraphMatrixForm<EdgeT>(directed);
    else
        data = new GraphListForm<EdgeT>(directed);
    //Создаём вершины и помещаем в структуру
    for (int i = 0; i < vertexCount; i++)
        data->InsertV(i);
    for (int i = 0; i < vertexCount; i++) {
        VertexT* v = new VertexT();
        v->setName(sz);
        sz++;
        vertexVector.push_back(v);
        data->InsertV(i);
    }
    this->directed = directed;
    this->dense = dense;
    edgeCounter = 0;

    //Вставляем рёбра
    if (edgeCount <= 0) return;
    //Корректируем число рёбер, чтобы не превышало максимумы
    if (directed) {
        if (edgeCount > vertexCount * (vertexCount - 1))
            edgeCount = vertexCount * (vertexCount - 1);
        srand((unsigned)time(NULL));
    }
    else {
        if (edgeCount > (vertexCount * (vertexCount - 1)) / 2)
            edgeCount = (vertexCount * (vertexCount - 1)) / 2;
    }
    //Вставляем
    for (int v1, v2; edgeCounter < edgeCount;) {
        v1 = rand() % vertexCount;
        v2 = rand() % vertexCount;
        if (v1 == v2)
            continue;
        if (data->hasEdge(v1, v2))
            continue;

        EdgeT* t = new EdgeT(vertexVector[v1], vertexVector[v2]);
        data->InsertE(v1, v2, t);
        t->setWeight((rand() % 9) + 1);
        if (directed == false)
            data->InsertE(v2, v1, t);
        edgeCounter++;
    }
}

//конструктор копирования
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::Graph(const Graph<VertexT, EdgeT>& G) {
    sz = 0;
    delete data;
    if (G.Dense())
        data = new GraphMatrixForm<EdgeT>(*(G.data));
    else
        data = new GraphListForm<EdgeT>(*(G.data));
    directed = G.directed;
    dense = G.dense;
}

//деструктор
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::~Graph() {
    while (vertexVector.size() != 0)
        DeleteV(0);
    delete data;
}

//Информация о графе
//Число вершин, рёбер, насыщенность
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::getVertexCount() {
    return vertexVector.size();
}

template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::getEdgeCount() {
    return edgeCounter;
}

//возвращает число вершин в графе
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::V() {
    return vertexVector.size();
}

//возвращает число ребер в графе
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::E() {
    return edgeCounter;
}

//возвращает тип графа
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::Directed() {
    return directed;
}

//возвращает форму представления графа
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::Dense() {
    return dense;
}

//возвращает коэффициент насыщенности графа
template <class VertexT, class EdgeT> double Graph<VertexT, EdgeT>::K() {
    int max = vertexVector.size() * (vertexVector.size() - 1);
    if (!directed)
        max /= 2;
    if (max == 0)
        return -1;
    else
        return (double)edgeCounter / (double)max;
}

//преобразует граф к L-графу
template <class VertexT, class EdgeT> void Graph<VertexT, EdgeT>::ToListGraph() {
    //Создаём структуру хранения L-графа
    GraphForm<EdgeT>* newData = new GraphListForm<EdgeT>(this->directed);
    //Создаём вершины
    for (int i = 0; i < vertexVector.size(); i++)
        newData->InsertV(i);
    //Переносим рёбра
    for (int i = 0; i < vertexVector.size(); i++)
        for (int j = 0; j < vertexVector.size(); j++)
            if (data->hasEdge(i, j))
                newData->InsertE(i, j, data->getEdge(i, j));
    delete data;
    data = newData;
    dense = false;
}

//преобразует граф к M-графу
template <class VertexT, class EdgeT> void Graph<VertexT, EdgeT>::ToMatrixGraph() {
    //Создаём структуру хранения М-графа
    GraphForm<EdgeT>* newData = new GraphMatrixForm<EdgeT>(this->directed);
    //Создаём вершины
    for (int i = 0; i < vertexVector.size(); i++)
        newData->InsertV(i);
    //Переносим рёбра
    for (int i = 0; i < vertexVector.size(); i++)
        for (int j = 0; j < vertexVector.size(); j++)
            if (data->hasEdge(i, j))
                newData->InsertE(i, j, data->getEdge(i, j));
    delete data;
    data = newData;
    dense = true;
}

//добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
template <class VertexT, class EdgeT> VertexT* Graph<VertexT, EdgeT>::InsertV() {
    VertexT* v = new VertexT;
    if (data->InsertV(vertexVector.size()) == false)
        throw bad_exception();
    v->setName(sz);
    sz++;
    vertexVector.push_back(v);
    return v;
}

//удаляет вершину из графа, заданную адресом дескриптора v
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::DeleteV(VertexT* v) {
    int index = getIndex(v);
    edgeCounter -= data->DeleteEsFromVertex(index, directed);
    if (data->DeleteV(index)) {
        vertexVector.erase(vertexVector.begin() + index);//
        return true;
    }
    return false;
}

template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::DeleteV(int index) {
    edgeCounter -= data->DeleteEsFromVertex(index, directed);
    if (data->DeleteV(index)) {
        vertexVector.erase(vertexVector.begin() + index);//
        return true;
    }
    return false;
}

template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::DeleteV1(int n) {
    VertexT* v = NULL;
    try {
        v = getVertexFromName(n);
    }
    catch (exception) {
        return false;
    }
    return DeleteV(v);
}

template <class VertexT, class EdgeT> VertexT* Graph<VertexT, EdgeT>::getVertex(int index) {
    if (index < 0 || index >= vertexVector.size())
        throw bad_exception();
    return vertexVector[index];
}

template <class VertexT, class EdgeT> VertexT* Graph<VertexT, EdgeT>::getVertexFromName(int n) {
    for (int i = 0; i < vertexVector.size(); i++)
        if (vertexVector[i]->getName() == n)
            return vertexVector[i];
    throw bad_exception();
}

template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::getIndex(VertexT* v) {
    int index = 0;
    for (int i = 0; i < vertexVector.size(); ++i) {
        if (vertexVector[index] == v)
            break;
        index++;
    }
    if (index == vertexVector.size())
        throw bad_exception();;
    return index;
}

//добавляет ребро (v1, v2) к графу, соединяющую вершины, заданные адресами дескрипторов v1 и v2
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::InsertE(int v1, int v2) {
    VertexT* _v1 = new VertexT;
    VertexT* _v2 = new VertexT;
    try {
        _v1 = getVertexFromName(v1);
        _v2 = getVertexFromName(v2);
        InsertE(_v1, _v2);
    }
    catch (exception) {
        return false;
    }
    return true;
}

template <class VertexT, class EdgeT> EdgeT* Graph<VertexT, EdgeT>::InsertE(VertexT* v1, VertexT* v2) {
    EdgeT* e = new EdgeT(v1, v2);
    if (!data->InsertE(getIndex(v1), getIndex(v2), e)) throw bad_exception();
    if (directed == false)
        data->InsertE(getIndex(v2), getIndex(v1), e);
    edgeCounter++;
    return e;
}

//удаляет ребро, соединяющее вершины, заданные адресами дескрипторов v1 и v2
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::DeleteE(int v1, int v2) {
    VertexT* _v1 = new VertexT;
    VertexT* _v2 = new VertexT;
    try {
        _v1 = getVertexFromName(v1);
        _v2 = getVertexFromName(v2);
    }
    catch (exception) {
        return false;
    }
    if (!DeleteE(_v1, _v2)) return false;
    else return true;
}

template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::DeleteE(VertexT* v1, VertexT* v2) {
    if (data->DeleteE(getIndex(v1), getIndex(v2))) {
        edgeCounter--;
        if (directed == false)
            data->DeleteE(getIndex(v2), getIndex(v1));
        return true;
    }
    else
        return false;
}

template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::hasEdge(VertexT* v1, VertexT* v2) {
    int ind1, ind2;
    try {
        ind1 = getIndex(v1);
        ind2 = getIndex(v2);
    }
    catch (int& a) {
        return false;
    }
    return data->hasEdge(getIndex(v1), getIndex(v2));
}

template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::hasEdge(int v1, int v2) {
    if (v1 < 0 || v1 >= vertexVector.size())
        return false;
    if (v2 < 0 || v2 >= vertexVector.size())
        return false;
    return data->hasEdge(v1, v2);
}

template <class VertexT, class EdgeT> EdgeT* Graph<VertexT, EdgeT>::getEdge(VertexT* v1, VertexT* v2) {
    EdgeT* e;
    try {
        e = data->getEdge(getIndex(v1), getIndex(v2));
    }
    catch (exception) {
        throw bad_exception();;
    }
    return e;
}
//Записать данные о ребре
template <class VertexT, class EdgeT> bool  Graph<VertexT, EdgeT>::write_data_edge(int _v1, int _v2, int data) {
    EdgeT* e;
    VertexT* v1, * v2;
    try {
        v1 = getVertexFromName(_v1);
        v2 = getVertexFromName(_v2);
        e = getEdge(v1, v2);
        e->setData(data);
    }
    catch (exception) {
        return false;
    }
    return true;
}

//Записать вес ребра
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::write_weight_edge(int _v1, int _v2, int w) {
    EdgeT* e;
    VertexT* v1, * v2;
    try {
        v1 = getVertexFromName(_v1);
        v2 = getVertexFromName(_v2);
        e = getEdge(v1, v2);
        e->setWeight(w);
    }
    catch (exception) {
        return false;
    }
    return true;
}

//Прочитать данные о ребре
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::read_data_edge(int _v1, int _v2) {
    EdgeT* e;
    VertexT* v1, * v2;
    try {
        v1 = getVertexFromName(_v1);
        v2 = getVertexFromName(_v2);
        e = getEdge(v1, v2);
        if (e->isDataSet())
            return e->getData();
        else
            throw bad_exception();;
    }
    catch (exception) {
        return -1;
    }
}

//Прочитать вес ребра
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::read_weight_edge(int _v1, int _v2) {
    EdgeT* e;
    VertexT* v1, * v2;
    try {
        v1 = getVertexFromName(_v1);
        v2 = getVertexFromName(_v2);
        e = getEdge(v1, v2);
        if (e->isWeightSet())
            return e->getWeight();
        else
            throw bad_exception();;
    }
    catch (exception) {
        return -1;
    }
}

//Вывод на экран
template <class VertexT, class EdgeT> void Graph<VertexT, EdgeT>::print_graph() {
    int i, j;
    VertexT* v;
    EdgeT* e;
    if (Dense()) {
        cout << setw(5) << "  ";
        for (i = 0; i < V(); i++) {
            v = getVertex(i);
            cout << setw(4) << v->getName();
        }
        cout << endl;
        for (i = 0; i < 5 * V() + 4; i++)
            cout << "_";
        cout << endl;
        for (i = 0; i < V(); i++) {
            v = getVertex(i);
            cout << setw(4) << v->getName() << "|";
            for (j = 0; j < V(); j++)
                if (hasEdge(i, j)) {
                    e = getEdge(getVertex(i), getVertex(j));
                    cout << setw(4) << "1"; // есть ли связь или нет
                }
                else
                    cout << setw(4) << "0";
            cout << endl;
        }
    }
    else {
        for (i = 0; i < V(); i++) {
            v = getVertex(i);
            cout << v->getName() << ": ";
            OutputEdgeIterator out(*this, *v);
            while (!out.onEnd()) {	// исходящие рёбра
                cout << (*out)->getVertex2()->getName() << "; ";
                ++out;
            }
            cout << endl;
        }
    }
};

//Прочитать данные о вершине
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::read_data_vertex(int v1) {
    VertexT* v;
    try {
        v = getVertexFromName(v1);
        int d;
        d = v->getData();
        if (v->isDataSet())
            return d;
        else
            throw bad_exception();
    }
    catch (exception) {
        return -1;
    }
}

//Записать данные о вершине
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::write_data_vertex(int v1, int d) {
    VertexT* v;
    try {
        v = getVertexFromName(v1);
    }
    catch (exception) {
        return false;
    };
    v->setData(d);
    return true;
}

//Записать данные о вершине
template <class VertexT, class EdgeT> bool Graph<VertexT, EdgeT>::write_name_vertex(int v1, int str) {
    VertexT* v;
    try {
        v = getVertexFromName(v1);
    }
    catch (exception) {
        return false;
    };
    v->setName(str);
    return true;
}
