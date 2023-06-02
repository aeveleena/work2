#include <iostream>
#include <sstream>
#include <chrono>
#include <Windows.h>
using namespace std;

struct List{
    int data;
    List *next;
    List *prev;
};

int checkInput(){
    int input;
    try{
        cin >> input;
        if (cin.fail()) throw 1;
    } catch (int exeption){
        cout << "! ерор ошибка";
        exit(0);
    }
    cin.sync();
    cout << "\n";
    return input;
}

void printList(List * cur){
    cout << "список: ";
    while(cur){
        cout << cur->data << " ";
        cur = cur->next;
    }
}

void printArr(int * arr, int size){
    cout << "массив: ";
    for (int *i = arr; i != arr + size; i++) cout << *i << " ";
}

void deleteList (List * &list){
    List *Next;
    while (list){
        Next = list->next;
        delete list;
        list = Next;
    }
}

List *createListRand(unsigned size){
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *head = nullptr, *tail = nullptr;
    srand(time(NULL));
    for (int i = 0; i < size; i++){
        head = new List;
        head->data = rand() % 100;
        head->next = tail;
        if(tail) tail->prev = head;
        tail = head;
    }
    if(size != 0) head->prev = nullptr;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "\nвремя, потраченное на создание\nсписка: " << end - start << " нс\n";
    return head;
}

int *createArrRand(unsigned size){
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int *arr = new int[size];
    srand(time(NULL));
    for (int i = size - 1; i >= 0; i--) arr[i] = rand() % 100;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "массива: " << end - start << " нс\n";
    return arr;
}

List *createListByHands(string str, int &size){
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *head = nullptr, *tail = nullptr;
    istringstream iss(str);
    int num, count = 0;
    while (iss >> num) {
        head = new List;
        head->data = num;
        head->prev = tail;
        if(tail) tail->next = head;
        tail = head;
        count++;
    }
    size = count;
    if(size > 0) {
        head->next = nullptr;
        while (head->prev) head = head->prev;
        auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "\nвремя, потраченное на создание\nсписка: " << end - start << " нс\n";
        return head;
    }
    else return nullptr;
}

int *createArrByHands(string str, int size){
    if (size == 0) return nullptr;
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int *arr = new int[size];
    istringstream iss(str);
    int num, i = 0;
    while (iss >> num){
        arr[i] = num;
        i++;
    }
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "массива: " << end - start << " нс\n";
    return arr;
}

void getLine(string &stringLine){getline(cin, stringLine);}

void createAll(List * &list, int * &arr, int &size){
    cout << "способ заполнения массива:\n1) случайными значениями\n2) вручную\n\nвыберите: ";
    int inputType = checkInput();
    int sizeList;
    string stringList;
    if (inputType == 1){
        cout << "введите размер: ";
        sizeList = checkInput();
        if (sizeList <= 0){
            cout << "некорректное значение, попробуйте снова\n";
            createAll(list, arr, size);
        }
        size = sizeList;
        list = createListRand(size);
        arr = createArrRand(size);
    }
    else if(inputType == 2){
        cout << "введите значения (через пробел): ";
        getLine(stringList);
        list = createListByHands(stringList, size);
        arr = createArrByHands(stringList, size);
    }
    else{
        cout << "что-то не то ввели, попробуйте снова\n";
        createAll(list, arr, size);
    }
    cout << "\n";
    printList(list);
    cout << "\n";
    printArr(arr, size);
    cout << "\nдлина списка и массива: " << size;
}

List *listItem(List * Beg, unsigned int index){
    int p = 0;
    while(p != index){
        Beg = Beg->next;
        p++;
    }
    return Beg;
}

void addValue(List * &list, int * &arr,  int &size){
    cout << "\nвведите, на место какого индекса вставить значение: ";
    int index = checkInput();
    if (!(index >= 1 && index <= size + 1)){
        cout << "\nнет такого индекса, попробуйте снова: ";
        index = checkInput();
    }
    cout << "\nвведите значение, которое хотите добавить: ";
    int value = checkInput();
    List *addItem = new List;
    addItem->data = value;

    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int *arr1 = new int[size+1];
    for(int i = 0, j = 0; i < size + 1; i++, j++){
        if(i == index - 1){
            arr1[i] = value;
            j--;
        }
        else arr1[i] = arr[j];
    }
    delete []arr;
    arr = arr1;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "время, потраченное на добавление элемента\nв массив: " << end - start << " нс\n";

    start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if(index > size){
        List *item = listItem(list, size-1);
        item->next = addItem;
        addItem->prev = item;
        addItem->next = nullptr;
    }
    else if(index == 1){
        list->prev = addItem;
        addItem->next = list;
        addItem->prev = nullptr;
        list = addItem;
    }
    else{
        List *item = listItem(list, index-1);
        addItem->next = item;
        addItem->prev = item->prev;
        item->prev->next = addItem;
        item->prev = addItem;
    }
    end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "в список: " << end - start << " нс\n";
    size++;
    cout << "\n";
    printArr(arr, size);
    cout << "\n";
    printList(list);
    cout << "\nдлина списка и массива: " << size;
}

void changeValues(List * &list, int * &arr, int size){
    cout << "\nвведите индексы, которые нужно поменять местами";
    cout << "\nиндекс 1: ";
    int index1 = checkInput();
    cout << "индекс 2: ";
    int index2 = checkInput();
    if (!((index1 >= 1 && index1 <= size) && (index2 >= 1 && index2 <= size))){
        cout << "\nнет такого индекса, попробуйте снова\n";
        return;
    }
    if (index1 == index2){
        cout << "\n";
        printArr(arr, size);
        cout << "\n";
        printList(list);
        return;
    }
    index1--; index2--;
    if(index1 > index2) swap(index1, index2);

    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    swap(arr[index2], arr[index1]);
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "время, потраченное на обмен элементов\nв массиве: " << end - start << " нс\n";

    start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *item1 = listItem(list, index1);
    List *item2 = listItem(list, index2);
    if (item1->prev != nullptr) item1->prev->next = item2;
    else list = item2;
    if (item1->next != item2) item1->next->prev = item2;
    if (item2->prev != item1) item2->prev->next = item1;
    if (item2->next != nullptr) item2->next->prev = item1;
    if(item1->next == item2){
        item2->prev = item1->prev;
        item1->prev = item2;
        item1->next = item2->next;
        item2->next = item1;
        end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "в списке: " << end - start << " нс\n";
        return;
    }
    List *help = item1->prev;
    item1->prev = item2->prev;
    item2->prev = help;
    help = item1->next;
    item1->next = item2->next;
    item2->next = help;
    end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "в списке: " << end - start << " нс\n";
    cout << "\n";
    printArr(arr, size);
    cout << "\n";
    printList(list);
}

void deleteValue(List * &list, int * &arr, int &size){
    cout << "\nспособ удаления элемента\n1) по значению\n2) по индексу\n\nвыберите: ";
    int type, value, index, count = 0;
    List *cur = list;
    type = checkInput();
    switch (type) {
        case 1:
            cout << "введите значение: ";
            value = checkInput();
            break;
        case 2:
            cout << "введите индекс: ";
            index = checkInput();
            while (!(index >= 1 && index <= size)){
                cout << "\nнет такого индекса, попробуйте снова: ";
                index = checkInput();
            }
            while(cur){
                if(count == index - 1){
                    value = cur->data;
                    break;
                }
                cur = cur->next;
                count++;
            }
            break;
        default:
            cout << "\nчто-то не то ввели, попробуйте снова\n";
            deleteValue(list, arr, size);
    }
    count = 0;
    cur = list;
    List *help = nullptr;
    bool flag = false;
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(cur){
        if (cur->data == value){
            flag = true;
            if (cur->prev == nullptr){
                list = cur->next;
                if(cur->next != nullptr)cur->next->prev = nullptr;
                delete cur;
                cur = list;
            }
            else if(cur->next == nullptr){
                help = cur->next;
                if(cur->prev != nullptr) cur->prev->next = nullptr;
                delete cur;
                cur = help;
            }
            else{
                help = cur->next;
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                delete cur;
                cur = help;
            }
            count++;
            if(type == 2) break;
        }
        else cur = cur->next;
    }
    if(!flag) return;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "время, потраченное на удаление элемента\nв списке: " << end - start << " нс\n";

    start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int *arr1 = new int[size-1];
    flag = true;
    for(int i = 0, j = 0; i < size; i++, j++){
        if(arr[i] == value && flag){
            j--;
            if(type == 2) flag = false;
        }
        else arr1[j] = arr[i];
    }
    delete []arr;
    arr = arr1;
    end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "в массиве: " << end - start << " нс\n";
    size -= count;
    cout << "\n";
    printList(list);
    cout << "\n";
    printArr(arr, size);
    cout << "\nдлина списка и массива: " << size;
}

void getValue(List * &list, int * &arr,  int size){
    cout << "\nспособ получения элемента\n1) по значению\n2) по индексу\n\nвыберите: ";
    int type, value, index, count = 0;
    bool flag = false;
    List *cur = list;
    type = checkInput();
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    switch (type) {
        case 1: {
            cout << "введите значение: ";
            value = checkInput();
            bool bebra = false;
            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            for (int i = 0; i < size; i++){
                if (arr[i] == value) {
                    bebra = true;
                    cout << "элемент " << value << " найден, его индекс: " << i + 1 << "\n";
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << "время, потраченное на нахождение элемента в массиве: " << end - start << " нс\n";
                }
            }
            if (!bebra){
                auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                cout << "массив не содержит элемент " << value << "\n";
                cout << "время, потраченное на нахождение элемента в массиве: " << end - start << " нс\n";
            }

            start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            while (cur){
                if (cur->data == value){
                    flag = true;
                    index = count;
                    cout << "\nэлемент " << value << " найден, его индекс: " << index + 1 << "\n";
                    end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << "время, потраченное на нахождение элемента в списке: " << end - start << " нс\n";
                }
                cur = cur->next;
                count++;
            }
            if (!flag) {
                end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                cout << "список не содержит элемент " << value << "\n";
                cout << "время, потраченное на нахождение элемента в списке: " << end - start << " нс\n";
            }
            break;
        }
        case 2: {
            cout << "введите индекс: ";
            index = checkInput();
            while (!(index >= 1 && index <= size)) {
                cout << "нет такого индекса, попробуйте снова: ";
                index = checkInput();
            }

            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            cout << "элемент с индексом " << index << " найден, его значение: " << arr[index - 1] << "\n";
            auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            cout << "время, потраченное на поиск элемента в массиве: " << end - start << " нс\n";

            start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            cur = listItem(list, index - 1);
            cout << "\nэлемент с индексом " << index << " найден, его значение: " << cur->data << "\n";
            end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            cout << "время, потраченное на поиск элемента в списке: " << end - start << " нс\n";
            break;
        }
            default: {
                cout << "что-то не то ввели, попробуйте снова\n";
                getValue(list, arr, size);
                break;
            }
    }
    cout << "\n";
    printArr(arr, size);
    cout << "\n";
    printList(list);
}

void idz(List * &list, int * &arr, int &size){
    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int count = 0;
    for(int i = 0; i < size; i++) if (arr[i] % 2 != 0) count++;
    int *arr1 = new int[size - count];
    for(int i = 0, j = 0; i < size; i++, j++){
        if(arr[i] % 2 != 0) j--;
        else arr1[j] = arr[i];
    }
    size -= count;
    delete []arr;
    arr = arr1;
    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "\nвремя, потраченное на удаление нечетных элементов в массиве: " << end - start << " нс\n";
    printArr(arr, size);
    start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    List *cur = list, *help = nullptr;
    while(cur){
        if (cur->data % 2 != 0){
            if (cur->prev == nullptr){
                list = cur->next;
                if(cur->next != nullptr)cur->next->prev = nullptr;
                delete cur;
                cur = list;
            }
            else if(cur->next == nullptr){
                help = cur->next;
                if(cur->prev != nullptr) cur->prev->next = nullptr;
                delete cur;
                cur = help;
            }
            else{
                help = cur->next;
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                delete cur;
                cur = help;
            }
        }
        else cur = cur->next;
    }
    end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout << "\nвремя, потраченное на удаление нечетных элементов в списке: " << end - start << " нс\n";
    printList(list);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int kek(1), command;
    int size;
    int *arr = nullptr;
    List *list = nullptr;
    createAll(list, arr, size);
    cout << "\n\n\tменю:\n1. идз\n2. вставить элемент в список\n3. поменять элементы местами\n4. удалить элемент списка\n5. найти элемент в списке\n";
    while (kek) {
        cout << "\nвведите номер пункта: ";
        cin >> command;
        switch(command) {
            case 1:{
                idz(list, arr, size);
            }break;

            case 2:{
                addValue(list, arr, size);
            }break;

            case 3:{
                changeValues(list, arr, size);
            }break;

            case 4:{
                deleteValue(list, arr, size);
            }break;

            case 5:{
                getValue(list, arr, size);
            }break;
        }

        cout << "\n\nпродолжить выполнение? (1 - да, 0 - нет)" << endl;
        cin >> kek;
    }
    delete []arr;
    deleteList(list);
    return 0;
}
