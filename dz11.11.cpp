
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <windows.h>

using namespace std;

// Узел списка
struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};


class Stack {
private:
    Node* topNode;

public:
    Stack() {
        topNode = nullptr;
    }

    ~Stack() {
        while (topNode != nullptr) {
            pop();
        }
    }

    // Добавление элемента
    bool push(int value) {
        Node* node = new(nothrow) Node(value);

        if (node == nullptr) {
            return false;
        }

        node->next = topNode;
        topNode = node;

        return true;
    }

    // Удаление верхнего элемента
    bool pop() {
        if (topNode == nullptr) {
            return false;
        }

        Node* temp = topNode;
        topNode = topNode->next;

        delete temp;

        return true;
    }

    // Чтение верхнего элемента без удаления
    bool peek(int& value) const {
        if (topNode == nullptr) {
            return false;
        }

        value = topNode->data;
        return true;
    }

    bool empty() const {
        return topNode == nullptr;
    }
};



class Queue {
private:
    Node* first;
    Node* last;

public:
    Queue() {
        first = nullptr;
        last = nullptr;
    }

    ~Queue() {
        while (first != nullptr) {
            pop();
        }
    }

    // Добавление элемента в конец
    bool push(int value) {
        Node* node = new(nothrow) Node(value);

        if (node == nullptr) {
            return false;
        }

        if (last == nullptr) {
            first = last = node;
        } else {
            last->next = node;
            last = node;
        }

        return true;
    }

    // Удаление первого элемента
    bool pop() {
        if (first == nullptr) {
            return false;
        }

        Node* temp = first;
        first = first->next;

        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;

        return true;
    }

    // Чтение первого элемента без удаления
    bool peek(int& value) const {
        if (first == nullptr) {
            return false;
        }

        value = first->data;
        return true;
    }

    bool empty() const {
        return first == nullptr;
    }
};



int main(int argc, char* argv[]) {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (argc < 2) {
        cerr << "Ошибка: необходимо передать целые числа "
                "через командную строку." << endl;
        return 1;
    }

    Stack stack;
    Queue queue;

    // Получаем числа из аргументов командной строки
    for (int i = 1; i < argc; i++) {
        char* end;
        errno = 0;

        long value = strtol(argv[i], &end, 10);

        if (errno == ERANGE ||
            end == argv[i] ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {

            cerr << "Ошибка: некорректное число: "
                 << argv[i] << endl;

            return 2;
        }

        if (!stack.push(static_cast<int>(value))) {
            cerr << "Ошибка выделения памяти для стека." << endl;
            return 3;
        }

        if (!queue.push(static_cast<int>(value))) {
            cerr << "Ошибка выделения памяти для очереди." << endl;
            return 3;
        }
    }

    // Вывод в прямом порядке
    cout << "Прямой порядок (очередь): ";

    while (!queue.empty()) {
        int value;

        if (queue.peek(value)) {
            cout << value << " ";
            queue.pop();
        }
    }

    cout << endl;

    // Вывод в обратном порядке
    cout << "Обратный порядок (стек): ";

    while (!stack.empty()) {
        int value;

        if (stack.peek(value)) {
            cout << value << " ";
            stack.pop();
        }
    }

    cout << endl;

    return 0;
}

// Второй коммит
