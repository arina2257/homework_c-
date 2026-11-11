
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <new>
#include <windows.h>
using namespace std;

// Стек
int* stackArr;
int stackTop = 0;
int stackSize;

// Очередь
int* queueArr;
int queueStart = 0;
int queueEnd = 0;
int queueSize;

// Добавление в стек
bool stackPush(int value) {
    if (stackTop >= stackSize) return false;

    stackArr[stackTop] = value;
    stackTop++;
    return true;
}

// Удаление из стека
bool stackPop(int& value) {
    if (stackTop == 0) return false;

    stackTop--;
    value = stackArr[stackTop];
    return true;
}

// Чтение верхнего элемента
bool stackPeek(int& value) {
    if (stackTop == 0) return false;

    value = stackArr[stackTop - 1];
    return true;
}

// Добавление в очередь
bool queuePush(int value) {
    if (queueEnd >= queueSize) return false;

    queueArr[queueEnd] = value;
    queueEnd++;
    return true;
}

// Удаление из очереди
bool queuePop(int& value) {
    if (queueStart >= queueEnd) return false;

    value = queueArr[queueStart];
    queueStart++;
    return true;
}

// Чтение первого элемента
bool queuePeek(int& value) {
    if (queueStart >= queueEnd) return false;

    value = queueArr[queueStart];
    return true;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (argc == 1) {
        cout << "Ошибка: числа не переданы." << endl;
        return 1;
    }

    int count = argc - 1;

    stackSize = count;
    queueSize = count;

    // Выделение динамической памяти
    stackArr = new (nothrow) int[stackSize];
    queueArr = new (nothrow) int[queueSize];

    if (stackArr == nullptr || queueArr == nullptr) {
        cout << "Ошибка выделения памяти." << endl;
        delete[] stackArr;
        delete[] queueArr;
        return 1;
    }

    // Получение и проверка чисел
    for (int i = 1; i < argc; i++) {
        char* end;
        errno = 0;
        long number = strtol(argv[i], &end, 10);

        if (errno == ERANGE || end == argv[i] ||
            *end != '\0' || number < INT_MIN || number > INT_MAX) {
            cout << "Ошибка: неверное целое число: " << argv[i] << endl;
            delete[] stackArr;
            delete[] queueArr;
            return 1;
        }

        if (!stackPush((int)number) || !queuePush((int)number)) {
            cout << "Ошибка добавления элемента." << endl;
            delete[] stackArr;
            delete[] queueArr;
            return 1;
        }
    }

    int value;

    cout << "Прямой порядок: ";

    while (queuePop(value)) {
        cout << value << " ";
    }

    cout << endl;

    cout << "Обратный порядок: ";

    while (stackPop(value)) {
        cout << value << " ";
    }

    cout << endl;

    // Освобождение памяти
    delete[] stackArr;
    delete[] queueArr;

    return 0;
}
