#include <iostream>
#include <stack>
#include <ctime>
#include <cmath>

#define Ex "Exception!"

typedef unsigned long long INT_64;

using namespace std;

template <typename Key, typename Data>
class Tree {
protected:
    class Node
    {
    public:
        Key key; // Ключ элемента
        Data data; // Значение элемента
        Node* left;	// Указатель на левую ветку
        Node* right;  // Указатель на правую ветку
        Node(Key k = NULL, Data d = Data()) {//конструктор
            this->data = d;
            this->key = k;
            this->left = nullptr;
            this->right = nullptr;
        }
    };
    Node* root; //корневой элемент дерева
    int size; //размер дерева
    int count; //количество пройденных элементов
public:
    class Iterator;
    class reIterator;
    Tree(); // Конструктор
    Tree(const Tree<Key, Data>& obj); // Конструктор копирования
    void copy(Node*); //функция копирования
    ~Tree(); // Деструктор
    int GetSizeTree(); // Опрос размера дерева
    bool ClearTree(); // Очистка дерева
    bool EmptyTree(); //Проверка дерева на пустоту
    Data& GetElemTree(Key); //Чтение данных по ключу
    bool EditElemTree(Key, Data); //Запись данных по ключу
    bool AddElemTree(Key, Data); //Включение данных с заданным ключом
    bool DelElemTree(Key); //Удаление данных с заданным ключом
    void PrintKey(); //Вывод списка ключей
    int SearchNumKey(int); //Поиск количества узлов ключи которых больше заданного значения
    void PrintStructureTree(int); //Вывод структуры дерева
    void PrintStrKey(Node*, int, int); //вывод структуры поэлементно
    int Count();// Опрос количества пройденных узлов
    Node* SearchPredElem(Node*); //Ищем узел с предыдущим по значению ключом
    Node* SearchNextElem(Node*); //Ищем узел со следующим по значению ключом
    Node* SearchMaxKey(Node*);	// Ищем узел с максимальным ключом
    Node* SearchRightParent(Node*, Node*);// Поиск ближайшего правого родителя
    Node* SearchMinKey(Node*);// Ищем узел с минимальным ключом
    Node* SearchLeftParent(Node*, Node*);// Поиск ближайшего левого родителя

    class Iterator { //прямой итератор
        Tree* ptr;
        Node* cur;
    public:
        Iterator(Tree<Key, Data>& tr) { //конструктор
            ptr = &tr;
            cur = NULL;
        }
        Key& begin() { //установка прямого итератора на первый элемент
            if (ptr->root == NULL) throw Ex;
            cur = ptr->root;
            while (cur != NULL && cur->left != NULL) //спускаемся до низа левого дерева
                cur = cur->left;
            return cur->key;
        }
        Key& end() { //установка прямого итератора на первый неопределенный элемент
            if (ptr->root == NULL) throw Ex;
            cur = ptr->root;
            while (cur != NULL && cur->right != NULL) //спускаемся до низа правого дерева
                cur = cur->right;
            Node* temp = cur;
            cur = NULL;
            return temp->key;
        }
        Data& operator*() { //разыменование итератора
            if (ptr->root == NULL) throw Ex;
            if (cur == NULL) throw Ex;
            return cur->data; //возвращаем текущий элемент
        }
        Key& operator++(int) { //операция перехода к следующему
            if (ptr->root == NULL) throw Ex;
            cur = ptr->SearchNextElem(cur); //переходим по дереву вперед
        }
        Key& operator--(int) { //операция перехода к предыдущему
            if (ptr->root == NULL) throw Ex;
            cur = ptr->SearchPredElem(cur);//переходим по дереву назад
        }
        bool operator==(Iterator& it) { //проверка на равенство
            if (ptr->root == NULL) throw Ex;
            return cur == it.cur;
        }
        bool operator!=(Iterator& it) { //проверка на неравенство
            if (ptr->root == NULL) throw Ex;
            return cur != it.cur;
        }
    };

    class reIterator {//обратный итератор
        Tree* ptr;
        Node* cur;
    public:
        reIterator(Tree<Key, Data>& rtr) {//конструктор
            ptr = &rtr;
            cur = NULL;
        }
        Key& rbegin() { //установка обратного оператора в начало
            if (ptr->root == NULL) throw Ex;
            cur = ptr->root;
            while (cur != NULL && cur->right != NULL)
                cur = cur->right;
            return cur->key;
        }
        Key& rend() { //установка обратного итератора на первый неустановленный элемент
            if (ptr->root == NULL) throw Ex;
            cur = ptr->root;
            while (cur != NULL && cur->left != NULL)
                cur = cur->left;
            Node* temp = cur;
            cur = NULL;
            return temp->key;
        }
        Data& operator*() { //операция разыменования
            if (ptr->root == NULL) throw Ex;
            return cur->data; //возвращаем текущее значение
        }
        Key& operator++(int) { //операция перехода к следующему
            if (ptr->root == NULL) throw Ex;
            cur = ptr->SearchPredElem(cur); //переходим по дереву вперед
        }
        Key& operator--(int) { //операция перехода к предыдущему
            if (ptr->root == NULL) throw Ex;
            cur = ptr->SearchNextElem(cur);//переходим по дереву назад
        }
        bool operator==(reIterator& rit) {//проверка на равенство
            if (ptr->root == NULL) throw Ex;
            return cur == rit.cur;
        }
        bool operator!=(reIterator& rit) {//проверка на неравенство
            if (ptr->root == NULL) throw Ex;
            return cur != rit.cur;
        }
    };
};

template<typename Key, typename Data>
bool Tree<Key, Data>::AddElemTree(Key key, Data data) { //Добавить новые данные по ключу
    count = 0;  //обнуляем счетчик пройденных элементов
    if (root == nullptr) { //если дерево пусто
        root = new Node(key, data);  //записываем новый элемент как корень
        size++; //увеличиваем размерность
        return true;  //сообщаем об успешном выполнении операции
    }
    Node* tmp = root, * pred = nullptr; //создаем временные элементы
    while (tmp != nullptr) {//пока не пройдем все дерево
        pred = tmp; //запоминаем предыдущий элемент
        count++;   //сделали еще один шаг по дереву
        if (key == (tmp->key))  //если в дереве есть данные с таким ключем
            return false; //возвращаем сообщение об ошибке
        if (key < (tmp->key)) //выбираем по какой ветке идти
            tmp = tmp->left; //спускаемся по левой ветке
        else
            tmp = tmp->right; //спускаемся по правой ветке
    }
    if (key < (pred->key)) //выбираем по какой ветке идти
        pred->left = new Node(key, data); //вставляем значение в конце левой ветки
    else
        pred->right = new Node(key, data);  //вставляем значение в конце правой ветки

    size++; //увеличиваем размерность
    count++; //сделали еще один шаг по дереву
    return true;  //сообщаем об успешном выполнении операции
}

template<typename Key, typename Data>
bool Tree<Key, Data>::EditElemTree(Key key, Data data) { //Изменение данных по ключу
    count = 0;  //обнуляем счетчик пройденных элементов
    if (root == NULL) //если дерево пусто
        return false;  //сообщаем об ошибке
    Node* tmp = root;  //создаем временные элементы
    while (tmp != NULL) {//пока не пройдем все дерево
        count++;   //сделали еще один шаг по дереву
        if (key == (tmp->key)) {  //если в дереве есть данные с таким ключем
            tmp->data = data; //изменяем значение
            return true; //сообщаем об успешном выполнении операции
        }
        if (key < (tmp->key)) //выбираем по какой ветке идти
            tmp = tmp->left; //спускаемся по левой ветке
        else
            tmp = tmp->right; //спускаемся по правой ветке
    }
    return false; //если ключ так и не найден, возвращаем ошибку
}

template<typename Key, typename Data>
Data& Tree<Key, Data>::GetElemTree(Key key) { //получить значение по ключу
    if (root == nullptr) throw Ex; //если древо пусто, выводим исключение
    count = 0;  //обнуляем счетчик пройденных элементов
    Node* tmp = root;//создаем временные элементы
    while (tmp != nullptr && key != (tmp->key)) {
        if (key < (tmp->key)) //выбираем по какой ветке идти
            tmp = tmp->left; //спускаемся по левой ветке
        else
            tmp = tmp->right; //спускаемся по правой ветке
        count++;   //сделали еще один шаг по дереву
    }
    if (tmp == nullptr) throw Ex; //если не найдены данные с заданным ключем, то выводим исключение
    return tmp->data; //возвращаем данные
}

template<typename Key, typename Data>
bool Tree<Key, Data>::DelElemTree(Key key) { //удалить данные по ключу
    if (root == nullptr) //если дерево пусто
        return false;  //сообщаем об ошибке
    Node* tmp = root, * pred = nullptr, * next = nullptr, * tmp_0 = nullptr; //создаем временные элементы
    count = 0; //обнуляем счетчик пройденных элементов
    while (tmp != nullptr && tmp->key != key) { //пока не пройдем все дерево и текущий ключ не равен искомому
        pred = tmp;//запоминаем предыдущий элемент
        if (key < tmp->key)//выбираем по какой ветке идти
            tmp = tmp->left;//спускаемся по левой ветке
        else
            tmp = tmp->right;//спускаемся по правой ветке
        count++;//сделали еще один шаг по дереву
    }
    if (tmp == nullptr) //если такого элемента в дереве нет
        return false; //сообщаем об ошибке
    if (tmp->left != nullptr && tmp->right != nullptr) { //если удаление из середины
        tmp_0 = tmp;
        pred = tmp;
        tmp = tmp->right; //идем по правой ветке
        while (tmp->left != nullptr) { //пока не достигнем конца левой ветки
            count++; //сделали еще один шаг по дереву
            pred = tmp; //запомнили предыдущий элемент
            tmp = tmp->left; //прошли дальше по левой ветке
        }
        //запоминаем во временных параметрах
        tmp_0->key = tmp->key;
        tmp_0->data = tmp->data;
        next = tmp->right;
    }
    else { //удаляем из конца
        if (tmp->left == nullptr && tmp->right == nullptr) //удаляем последний элемент ветки
            next = nullptr;
        else {
            if (tmp->left == nullptr)
                next = tmp->right; //запоминаем следующий элемент удаляемого значения правой ветки
            else if (tmp->right == nullptr)
                next = tmp->left; //запоминаем следующий элемент удаляемого значения левой ветки
        }
    }
    if (pred == nullptr)//если остается один элемент
        root = next; //корневому элементу присваиваем последний оставшийся
    else
    if (tmp->key < pred->key)//выберем по какой ветке идти
        pred->left = next; //вставляем значение в левую ветку
    else
        pred->right = next; //вставляем значение в правую ветку
    delete tmp; //очищаем память
    size--; //уменьшаем размерность
    return true;  //сообщаем об успешном выполнении операции
}

template<typename Key, typename Data>
int Tree<Key, Data>::GetSizeTree() { //узнать размерность
    return size; //возвращаем размерность
}

template<typename Key, typename Data>
bool Tree<Key, Data>::EmptyTree() { //проверка на пустоту
    if (size)
        return false; //0 если дерево пусто
    return true; //1 если есть элементы
}

template<typename Key, typename Data>
void Tree<Key, Data>::PrintKey() { //получить список ключей
    if (root == NULL) throw Ex; //если древо пусто, выводим исключение
    stack<Node*> stack1; //создаем стек
    Node* tmp; //создаем временные элементы
    stack1.push(root); //вставить корневой элемент в стек
    while (!stack1.empty()) { //пока стек не пуст
        tmp = stack1.top(); //переход к следующему элементу
        cout << tmp->key << " "; //выводим все элементы
        stack1.pop(); //удалить верхний уровень
        if (tmp->right != NULL) //если ветка не закончилась
            stack1.push(tmp->right); //вставляем следующий элемент по правой ветке в стек
        if (tmp->left != NULL) //если ветка не закончилась
            stack1.push(tmp->left); //вставляем следующий элемент по левой ветке в стек
    }
}

template<typename Key, typename Data>
bool Tree<Key, Data>::ClearTree() { //очистка дерева
    if (root == nullptr) //если дерево пусто
        return false;  //сообщаем об ошибке
    stack<Node*> stack1, stack2; //создаем стеки
    Node* tmp; //создаем временные элементы
    stack1.push(root); //вставить корневой элемент в стек
    while (!stack1.empty()) {//пока стек не пуст
        tmp = stack1.top();//переход к следующему элементу
        stack1.pop();//удалить верхний уровень
        stack2.push(tmp);//вставляем следующий элемент tmp в стек
        if (tmp->left != nullptr)//если ветка не закончилась
            stack1.push(tmp->left);//вставляем следующий элемент по левой ветке в стек
        if (tmp->right != nullptr)//если ветка не закончилась
            stack1.push(tmp->right); //вставляем следующий элемент по правой ветке в стек
        while (!stack2.empty()) {//пока стек не пуст
            tmp = stack2.top();//переход к следующему элементу
            stack2.pop();//удалить верхний уровень
            delete tmp;//очищаем память
            size--; //уменьшаем размерность
        }
    }
    root = nullptr; //ставим метку в корне дерева
    return true;//сообщаем об успешном выполнении операции
}

template<typename Key, typename Data>
void Tree<Key, Data>::PrintStructureTree(int num) { //вывод структуры дерева
    if (root == NULL) throw Ex; //если древо пусто, выводим исключение
    PrintStrKey(root, 0, num); //вызываем рекурсивную функцию вывода дерева
}

template<typename Key, typename Data>
inline void Tree<Key, Data>::PrintStrKey(Node* r, int level, int num) { //функция вывода дерева поэлементно
    if (r == NULL) return; //если прошли дерево, возвращаемся
    PrintStrKey(r->right, level + num, num); //проходим по правой ветке
    if (r->key == root->key) cout << endl;
    for (int i = 0; i < 3 * level; i++) cout << " ";
    if (num == 2) //выводим только ключи
        cout << r->key << endl;
    else
        cout << r->key << "[" << r->data << "]" << endl; //выводим ключи со значениями
    if (r->key == root->key) cout << endl;
    PrintStrKey(r->left, level + num, num); //проходим по левой ветке
}

template<typename Key, typename Data>
int Tree<Key, Data>::SearchNumKey(int num) {//поиск количества узлов с ключами больше заданного числа
    if (root == nullptr) throw Ex; //если древо пусто, выводим исключение
    count = 0; //обнуляем счетчик пройденных элементов
    stack<Node*> stack1;//создаем стек
    Node* tmp;//создаем временные элементы
    stack1.push(root);//вставить корневой элемент в стек
    while (!stack1.empty()) {//пока стек не пуст
        tmp = stack1.top();//переход к следующему элементу
        if (tmp->key > num) count++; //если данный ключ удовлетворяет условию, то увеличиваем на 1 счетчик
        stack1.pop();//удалить верхний уровень
        if (tmp->right != nullptr)//если ветка не закончилась
            stack1.push(tmp->right);//вставляем следующий элемент по правой ветке в стек
        if (tmp->left != nullptr)//если ветка не закончилась
            stack1.push(tmp->left);//вставляем следующий элемент по левой ветке в стек
    }
    return count; //возвращаем количество подходящих по условию ключей
}

template <class K, class tmp>
int Tree<K, tmp>::Count() { //количество пройденных элементов
    int temp = count; //запоминаем
    count = 0; //обнуляем
    return temp; //возвращаем количество пройденных элементов
}

template<typename Key, typename Data>
Tree<Key, Data>::Tree() { //конструктор
    root = nullptr; //задаем параметры по умолчанию
    count = 0;
}

template<typename Key, typename Data>
Tree<Key, Data>::Tree(const Tree<Key, Data>& obj) { //конструктор копирования
    root = NULL;
    size = 0;
    copy(obj.root);
}

template<typename Key, typename Data>
void Tree<Key, Data>::copy(typename Tree<Key, Data>::Node* r) { //функция копирования
    if (r == NULL) //если закончилась ветка
        return;
    AddElemTree(r->key, r->data); //добавляем элемент
    copy(r->left); //проверяем левую ветку
    copy(r->right); //проверяем правую ветку
}

template<typename Key, typename Data>
Tree<Key, Data>::~Tree() { //деструктор
    ClearTree(); //вызываем функцию очистки дерева
}

template<typename Key, typename Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::SearchPredElem(Node* x) {//Ищем узел с предыдущим по значению ключом
    if (x->left != NULL) return SearchMaxKey(x->left); //если следующий элемент не является конечным, то предыдущий элемент является максимальным ключем
    else return SearchRightParent(root, x); //иначе ищем правого родителя
}

template<typename Key, typename Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::SearchNextElem(Node* x) {//Ищем узел со следующим по значению ключом
    if (x->right != NULL) return SearchMinKey(x->right); //если следующий элемент не является конечным, то предыдущий элемент является минимальным ключем
    else return SearchLeftParent(root, x);//иначе ищем левого родителя
}

template<typename Key, typename Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::SearchMaxKey(Node* tmp) { //поиск максимального ключа
    if (tmp == NULL) return NULL; //если закончилось дерево
    while (tmp->right != NULL) tmp = tmp->right; //проходим по правой ветви
    return tmp; //возвращаем максимальный ключ
}

template<typename Key, typename Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::SearchMinKey(Node* tmp) { //поиск минимального ключа
    if (tmp == NULL) return NULL; //если дерево закончилось
    while (tmp->left != NULL) tmp = tmp->left; //проходим по левой ветви
    return tmp; //возвращаем минимальный ключ
}

template<typename Key, typename Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::SearchRightParent(Node* tmp, Node* x) {//Поиск ближайшего правого родителя
    if (tmp == x) return NULL; //если дерево закончилось
    if (x->key > tmp->key) { //сравниваем ключи
        Node* rp = SearchRightParent(tmp->right, x); //ищем правого родителя
        if (rp != NULL) return rp; //если родитель найден, то возвращаем его
        else return tmp;
    }
    else return SearchRightParent(tmp->left, x);
}

template<typename Key, typename Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::SearchLeftParent(Node* tmp, Node* x) {//Поиск ближайшего левого родителя
    if (tmp == x) return NULL;//если дерево закончилось
    if (x->key < tmp->key) {//сравниваем ключи
        Node* lp = SearchLeftParent(tmp->left, x); //ищем левого родителя
        if (lp != NULL) return lp;//если родитель найден, то возвращаем его
        else return tmp;
    }
    else return SearchLeftParent(tmp->right, x);
}

//==========================================Тестировщик===============================================

//переменная и константы генератора
static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

//функция установки первого случайного числа от часов компьютера
void sRand() { srand(time(0)); RRand = (INT_64)rand(); }

//функция генерации случайного числа линейный конгруэнтный генератор Xi+1=(a*Xi+c)%m
INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

void TestRandom(int n) { //Тест трудоёмкости случайного дерева
    Tree< INT_64, int > Rtree;//создание дерева для 64 – разрядных ключей типа INT_64
    INT_64* m = new INT_64[n];//массив для ключей, которые присутствуют в дереве
    sRand();//установка первого случайного числа
    for (int i = 0; i < n; i++) {//заполнение дерева и массива элементами со случайными ключами
        m[i] = LineRand();
        Rtree.AddElemTree(m[i], 1);
    }
    cout << "Размер дерева до теста: " << Rtree.GetSizeTree() << endl;
    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    double CN = 0;
    //генерация потока операций, 10% - промахи операций
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) {		//10% промахов
            Rtree.DelElemTree(LineRand());//подсчет трудоёмкости удаления
            D += Rtree.Count();
            Rtree.AddElemTree(m[rand() % n], 1);//подсчет трудоёмкости вставки
            I += Rtree.Count();
            Rtree.SearchNumKey(LineRand());//подсчет трудоёмкости поиска
            CN += Rtree.Count();
            try
            {
                Rtree.GetElemTree(LineRand()); //подсчет трудоёмкости поиска
                S += Rtree.Count();
            }
            catch (...) { S += Rtree.Count(); }
        }
        else  //90% успешных операций
        {
            int ind = rand() % n;
            INT_64 key = LineRand();
            Rtree.DelElemTree(m[ind]);//подсчет трудоёмкости удаления
            D += Rtree.Count();
            Rtree.AddElemTree(key, 1);
            I += Rtree.Count();//подсчет трудоёмкости вставки
            m[ind] = key;
            try {
                Rtree.GetElemTree(m[rand() % n]);//подсчет трудоёмкости поиска
                S += Rtree.Count();
            }
            catch (...) { S += Rtree.Count(); }
        }
    cout << "Размер дерева после теста:" << Rtree.GetSizeTree() << endl;
    cout << "Теоретическая оценка трудоёмкости операций 1.39*log2(n)= " << 1.39 * (log((double)n) / log(2.0)) << endl;
    cout << "Экспериментальная оценка трудоёмкости вставки: " << I / (n / 2) << endl;
    cout << "Экспериментальная оценка трудоёмкости удаления: " << D / (n / 2) << endl;
    cout << "Экспериментальная оценка трудоёмкости поиска: " << S / (n / 2) << endl;
    Rtree.ClearTree(); //очищаем дерево
    delete[] m; //очищаем массив
}

void test_ord(int n) { //Тест трудоёмкости вырожденного дерева
    Tree< INT_64, int > Otree;//создание дерева для 64 – разрядных ключей типа INT_64
    INT_64* m = new INT_64[n];//массив для ключей, которые присутствуют в дереве
    for (int i = 0; i < n; i++) {//Заполнение дерева и массива элементами с возрастающими чётными //ключами на интервале [0, 10000, 20000, ... ,10000*n]
        m[i] = i * 10000;
        Otree.AddElemTree(m[i], 1);
    }
    cout << "Размер дерева до теста: " << Otree.GetSizeTree() << endl;
    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    double CN = 0;
    sRand();//установка первого случайного числа
    for (int i = 0; i < n / 2; i++) {//генерация потока операций, 10% - промахи операций
        if (i % 10 == 0)		//10% промахов
        {
            INT_64 k = LineRand() % (10000 * n);
            k = k + !(k % 2);	//случайный нечётный ключ
            Otree.DelElemTree(k);//подсчет трудоёмкости удаления
            D += Otree.Count();
            Otree.AddElemTree(m[rand() % n], 1);//подсчет трудоёмкости вставки
            I += Otree.Count();
            Otree.SearchNumKey(k);//подсчет трудоёмкости поиска
            CN += Otree.Count();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2);	// случайный нечётный ключ
            try {
                Otree.GetElemTree(k);//подсчет трудоёмкости поиска
                S += Otree.Count();
            }
            catch (...) { S += Otree.Count(); }
        }
        else {  //90% успешных операций
            int ind = rand() % n;
            Otree.DelElemTree(m[ind]);//подсчет трудоёмкости удаления
            D += Otree.Count();
            int k = LineRand() % (10000 * n);
            k = k + k % 2;		// случайный чётный ключ
            Otree.AddElemTree(k, 1);//подсчет трудоёмкости вставки
            I += Otree.Count();
            m[ind] = k;
            try {
                Otree.GetElemTree(m[rand() % n]);//подсчет трудоёмкости поиска
                S += Otree.Count();
            }
                //обработка исключения при ошибке операции поиска
            catch (int) { S += Otree.Count(); }
        }
    }
    //вывод результатов:
    cout << "Размер дерева после теста: " << Otree.GetSizeTree() << endl;
    cout << "Теоретическая оценка трудоёмкости операций n/2 = " << n / 2 << endl;
    cout << "Экспериментальная оценка трудоёмкости вставки: " << I / (n / 2) << endl;
    cout << "Экспериментальная оценка трудоёмкости удаления: " << D / (n / 2) << endl;
    cout << "Экспериментальная оценка трудоёмкости поиска: " << S / (n / 2) << endl;
    Otree.ClearTree(); //очищаем дерево
    delete[] m; //очищаем массив
}
