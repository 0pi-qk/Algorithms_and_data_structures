#define ex "Исключение"
#define initial_capacity 1

template<class T>
class list {
protected:
    static list<T>* last_list;//Указатель на последний созданный лист
    int used_el;//Кол-ва использованных элементов
    int capacity, size;//Ёмкость, размер
    T* dynamic_arr;//Динамический массив
public:
    class Iterator;
    class reIterator;

    list();//конструктор по умолчанию
    list(const list&); //конструктор копирования
    void Add_front(const T&);//Добавить новый элемент в начало
    void Add_back(const T&);//Добавить новый элемент в конец
    bool Add_num(const T&, const int&);//Добавление нового значения по номеру
    int Get_pos_by_num(const T&);//Вернуть индекс элемента с заданным значением
    T Get_num_by_pos(const int&);//вернуть значение элемента по индексу
    bool change(const int&, const int&); //изменить значение 
    bool delete_value(const int&);//Удалить элементы с определённым значением
    bool delete_value_one(const int&);//Удалить первый элементы с определённым значением
    bool delete_number(const int&);//Удалить элемент по индексу
    bool check_value_have(const T&); //проверка на наличие заданного значения
    int Get_size();//получить размерность списка
    bool check_for_emptiness();//проверка на пустоту
    void clear_list();//Очистка списка
    int check_used_elements();//количество пройденных элементов
    int get_value_by_index(const int&);//вывод элемента по номеру

    class Iterator {//Итератор
    private:
        list* pointer;//Указатель на элемент списка
        int number_arr;//Номер ячейки динамического массива
    public:
        Iterator(list* some_list);//Конструктор с указателем на конкретный лист
        Iterator();//Конструктор по умолчанию, использует в качестве указателя на элемент списка последний созданный элемент класса
        void operator ++(int);//операция инкремента
        //Операторы сравнивания значений
        bool operator ==(const Iterator&);
        bool operator==(const reIterator&);
        bool operator !=(const Iterator&);
        T& operator*();//операция доступа к текущему значению
        void operator=(const Iterator&);//Приравниваем итераторы
        friend class list<T>;//класс дружественен к классу list
    };

    class reIterator {//обратный итератор
    private:
        list* pointer;//Указатель на элемент списка
        int number_arr;//Номер ячейки динамического массива
    public:
        reIterator(list* some_list);//Конструктор с указателем на конкретный лист
        reIterator();//Конструктор по умолчанию, использует в качестве указателя на элемент списка последний созданный элемент класса
        void operator --(int value);//операция инкремента
        //Операторы сравнивания значений
        bool operator ==(const reIterator& i);
        bool operator ==(const Iterator& i);
        bool operator !=(const reIterator& i);
        T& operator*();//операция доступа к текущему значению
        void operator=(const reIterator& other);//Приравниваем итераторы
        friend class list<T>;//класс дружественен к классу list
    };

    list<T>::Iterator begin();//Запрос прямого итератора
    list<T>::Iterator end();//Запрос неустановленного прямого итератора
    list<T>::reIterator rbegin();//Запрос обратного итератора
    list<T>::reIterator rend();//Запрос неустановленного обратного итератора

    //дополнительные функции
    int Get_capacity();//получить емкость
    void copy_arr(int*, int*, const int&);//Копирование элементов массива
    void capacity_upgrade();//обновить емкость

    ~list();  //деструктор
};

//============================
//функции класса
template<class T>
list<T>* list<T>::last_list = nullptr;


template<class T>
inline list<T>::list() {//конструктор по умолчанию
    this->capacity = initial_capacity;  //установка начальной емкости
    this->size = 0; //установим размер =0
    dynamic_arr = new T[capacity];//выделим память
    last_list = this;
}

template<class T>
inline list<T>::list(const list& other) {//конструктор копирования
    this->capacity = other.capacity;
    this->size = other.size;
    this->dynamic_arr = new T[capacity];
    copy_arr(&other.dynamic_arr[0], &this->dynamic_arr[0], size);
}

template<class T>
inline void list<T>::Add_back(const T& value) { //Добавить новый элемент в конец
    list<T>old_list(*this);  //сохраняем копию списка
    size++; //увеличиваем количество элементов на 1
    capacity_upgrade();//изменяем емкость, если это необходимо
    if (old_list.capacity != this->capacity)  //если емкость изменилась
        copy_arr(&old_list.dynamic_arr[0], &this->dynamic_arr[0], old_list.size); //то копируем старый массив в новый
    this->dynamic_arr[size - 1] = value;//записываем новое значение
}

template<class T>
inline void list<T>::Add_front(const T& value) { //Добавить новый элемент в начало
    list<T>old_list(*this);  //сохраняем копию списка
    size++; //увеличиваем количество элементов на 1
    capacity_upgrade();//изменяем емкость, если это необходимо
    copy_arr(&old_list.dynamic_arr[0], &this->dynamic_arr[1], old_list.size); //копируем старый массив в новый
    this->dynamic_arr[0] = value; //записываем новое значение
}

template<class T>
inline bool list<T>::Add_num(const T& value, const int& number) {//Добавление нового значения по номеру
    if ((number > size) || (number < 0)) return false;  //проверка выхода за границы списка
    if (number == size) { //если добавляем в конец
        this->Add_back(value);
        return true;
    }
    this->used_el = number + 1; //подсчет количества пройденных элементов
    list<T>old_list(*this);  //создаем копию списка
    size++;//увеличиваем количество элементов на 1
    capacity_upgrade(); //изменяем емкость, если это необходимо
    if (old_list.capacity != this->capacity) //если емкость изменилась
        copy_arr(&old_list.dynamic_arr[0], &this->dynamic_arr[0], number);//то копируем старый массив в новый до позиции
    copy_arr(&old_list.dynamic_arr[number], &this->dynamic_arr[number + 1], old_list.size - number); //после позиции
    this->dynamic_arr[number] = value;  //вставляем число в позицию
    return true;
}

template<class T>
inline int list<T>::Get_pos_by_num(const T& value) {//Вернуть индекс элемента с заданным значением
    for (int i = 0; i < size; i++) { //проходя по всему списку ищем совпадения
        if (dynamic_arr[i] == value)
            return i;  //если совпадения есть – то возвращаем индекс
    }
    return -1;//если нет, то -1
}

template<class T>
inline T list<T>::Get_num_by_pos(const int& number){  //вернуть значение элемента по индексу
    if ((number >= size) || (number < 0)) //если вышли за пределы списка
        throw ex;  //выводим ошибку
    return this->dynamic_arr[number];  //иначе возвращаем необходимое значение
}

template<class T>
inline bool list<T>::change(const int& number, const int& value) {  //изменить значение
    if ((number >= size) || (number < 0)) //если вышли за пределы списка
        return false;//выводим ошибку
    dynamic_arr[number] = value;//меняем значение по номеру
    return true;  //отправляем уведомление об успешном завершении
}

template<class T>
inline bool list<T>::delete_value(const int& value) {//Удалить элементы с определённым значением
    int index_value = this->Get_pos_by_num(value); //узнаем индекс
    if (index_value == -1)  //такого числа нет в списке
        return false;
    if (size == 0) return false; //список пуст
    while (index_value != -1) { //пока не удалили все числа
        this->delete_number(index_value);//удаляем число
        index_value = this->Get_pos_by_num(value);//проверяем есть ли еще такие числа
    }
    return true;//отправляем уведомление об успешном завершении
}

template<class T>
inline bool list<T>::delete_value_one(const int& value) {//Удалить элементы с определённым значением
    int index_value = this->Get_pos_by_num(value); //узнаем индекс
    if (index_value == -1)  //такого числа нет в списке
        return false;
    if (size == 0) return false; //список пуст
    this->delete_number(index_value);
    return true;//отправляем уведомление об успешном завершении
}

template<class T>
inline bool list<T>::delete_number(const int& number) {//Удалить элемент по индексу
    if (size == 0) //список пуст
        return false; //выводим ошибку
    if ((number >= size) or (number < 0)) //если вышли за пределы списка
        return false;//выводим ошибку
    this->used_el = number + 1; //подсчет количества пройденных элементов
    list<T>old_list(*this);//сохраняем копию списка
    size--; //уменьшаем размерность
    capacity_upgrade();//изменяем емкость
    if (old_list.capacity != this->capacity) //если емкость изменилась
        copy_arr(&old_list.dynamic_arr[0], &this->dynamic_arr[0], number);//то копируем старый массив в новый до позиции
    copy_arr(&old_list.dynamic_arr[number + 1], &this->dynamic_arr[number], size - number);//после позиции
    dynamic_arr[size] = 0;
    return true;//отправляем уведомление об успешном завершении
}

template<class T>
inline bool list<T>::check_value_have(const T& value){ //проверка на наличие заданного значения
    used_el = 0; //задаем количество шагов равным нулю
    for (int i = 0; i < size; i++) {
        used_el++;  //увеличиваем количество пройденных шагов на 1
        if (dynamic_arr[i] == value) // если такое значение есть
            return true; //выводим успех
    }
    return false; //выводи !успех
}

template<class T>
inline int list<T>::Get_size() {//получить размерность списка
    return this->size;//возвращаем размерность
}

template<class T>
inline bool list<T>::check_for_emptiness() {//проверка на пустоту
    return (size == 0); //если список пуст, то 1
}

template<class T>
inline void list<T>::clear_list(){//очистить список
    this->size = 0;//размерность 0
    capacity = initial_capacity;//емкость
    delete[] dynamic_arr;//очищаем память
    dynamic_arr = new int[capacity];//заново выделяем память
}

template<class T>
inline int list<T>::check_used_elements() {//количество пройденных элементов
    return this->used_el;
}

template<class T>
inline int list<T>::get_value_by_index(const int& number){//вывод элемента по номеру
    return dynamic_arr[number];//возвращаем элемент
}


template<class T>
inline typename list<T>::Iterator list<T>::begin() {//Запрос прямого итератора
    //if (size == 0) throw ex; //если размерность нулевая, выводим ошибку
    list<T>::Iterator itr(this);//создаем
    return itr;//возвращаем
}

template<class T>
inline typename list<T>::Iterator list<T>::end() {//Запрос неустановленного прямого итератора
    list<T>::Iterator itr(this);//создаем
    itr.number_arr = size;//устанавливаем на неустановленный
    return itr;//возвращаем
}

template<class T>
inline typename list<T>::reIterator list<T>::rbegin() {//Запрос обратного итератора
    //if (size == 0) throw ex; //если размерность нулевая, выводим ошибку
    list<T>::reIterator i(this);//создаем
    i.number_arr = size - 1;//устанавливаем на начало
    return i;//возвращаем
}

template<class T>
inline typename list<T>::reIterator list<T>::rend() {//Запрос неустановленного обратного итератора
    list<T>::reIterator i(this);//создаем
    i.number_arr = -1;//устанавливаем на неустановленный
    return i;//возвращаем
}


template<class T>
inline list<T>::~list() {//деструктор
    delete[] this->dynamic_arr; //очищаем динамическую память
}

//============================
//Итератор прямой

template<class T>
inline list<T>::Iterator::Iterator() { //Конструктор по умолчанию, использует в качестве указателя на элемент списка последний созданный элемент класса
    if (last_list != nullptr) this->pointer = last_list;
    this->number_arr = 0;
}

template<class T>
inline list<T>::Iterator::Iterator(list* some_list) { //Конструктор с указателем на конкретный лист
    //if (some_list->size == 0) throw ex;
    this->pointer = some_list;
    this->number_arr = 0;
}

template<class T>
inline T& list<T>::Iterator::operator*() {//операция доступа к текущему значению
    if ((pointer == nullptr) || (pointer->size == 0) || (*this == pointer->end())) throw ex;
    return pointer->dynamic_arr[number_arr];
}

template<class T>
inline void list<T>::Iterator::operator++(int value) {//операция инкремента
    if ((pointer == nullptr) || (number_arr == pointer->size)) throw ex;
    number_arr++;
}

//Операторы сравнивания значений
template<class T>
inline bool list<T>::Iterator::operator==(const Iterator& i) {
    return ((pointer == i.pointer) && (number_arr == i.number_arr));
}

template<class T>
inline bool list<T>::Iterator::operator==(const reIterator& i) {
    return ((pointer == i.pointer) && (number_arr == i.number_arr));
}

template<class T>
inline bool list<T>::Iterator::operator!=(const Iterator& i) {
    return ((pointer != i.pointer) || (number_arr != i.number_arr));
}

template<class T>
inline void list<T>::Iterator::operator=(const Iterator& other) { //Приравниваем итераторы
    if (other.pointer == nullptr) throw ex;
    this->pointer = other.pointer;
    this->number_arr = other.number_arr;
}

//============================
//итератор обратный

template<class T>
inline list<T>::reIterator::reIterator(){ //Конструктор по умолчанию, использует в качестве указателя на элемент списка последний созданный элемент класса
    if (last_list != nullptr) this->pointer = last_list;
    this->number_arr = pointer->size - 1;
}

template<class T>
inline list<T>::reIterator::reIterator(list* some_list){ //Конструктор с указателем на конкретный лист
    // if (some_list->size == 0) throw ex;
    this->pointer = some_list;
    this->number_arr = pointer->size - 1;
}

template<class T>
inline T& list<T>::reIterator::operator*() { //операция доступа к текущему значению
    if ((pointer == nullptr) || (pointer->size == 0) || (*this == pointer->rend())) throw ex;
    return pointer->dynamic_arr[number_arr];
}

template<class T>
inline void list<T>::reIterator::operator--(int value){ //операция инкремента
    if ((pointer == nullptr) || (number_arr == -1)) throw ex;
    number_arr--;
}

//Операторы сравнивания значений
template<class T>
inline bool list<T>::reIterator::operator==(const reIterator& i){
    return ((pointer == i.pointer) && (number_arr == i.number_arr));
}

template<class T>
inline bool list<T>::reIterator::operator==(const Iterator& i){
    return ((pointer == i.pointer) && (number_arr == i.number_arr));
}

template<class T>
inline bool list<T>::reIterator::operator!=(const reIterator& i){
    return ((pointer != i.pointer) || (number_arr != i.number_arr));
}

template<class T>
inline void list<T>::reIterator::operator=(const reIterator& other){  //Приравниваем итераторы
    if (other.pointer == nullptr) throw ex;
    this->pointer = other.pointer;
    this->number_arr = other.number_arr;
}

//============================
//дополнительные функции

template<class T>
inline int list<T>::Get_capacity() {//получить емкость списка
    return this->capacity;
}

template<class T>
inline void list<T>::copy_arr(int* mas_sourcer, int* mas_receiver, const int& size) {//копируем массива
    for (int i = 0; i < size; i++) {//проходя по всему массиву копируем из одного, в другой
        *(mas_receiver + i) = *(mas_sourcer + i);
    }
}

template<class T>
inline void list<T>::capacity_upgrade() {//обновить емкость
    if (size == capacity) {//если текущий размер = емкости
        capacity *= 2;//увеличиваем емкость по экспоненциальному закону
        delete[] dynamic_arr; //удаляем прошлы дин массив
        dynamic_arr = new int[capacity];  //выделяем память новому
        return;
    }
    else if (size < initial_capacity) {
        capacity = initial_capacity;
        return;
    }
    else if (size <= (capacity / 2)) {  //если выделено больше емкости чем необходимо для данных
        if (size == (capacity / 2))
            capacity = size + initial_capacity; //сокращаем емкость
        else
            capacity /= 2;
        delete[] dynamic_arr;//удаляем прошлы дин массив
        dynamic_arr = new int[capacity];//выделяем память новому
        return;
    }
}