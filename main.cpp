#include <iostream>
using namespace std;

class Node 
{
    public:
        int data;
        Node* prev;
        Node* next;
        Node(int data) 
        {
            this->data = data;
            prev = NULL;
            next = NULL;
        }
};

class DoublyLinkedList // Определение DoublyLinkedList для списка
{
    private:
        Node* head;
        Node* tail;

    public:
        DoublyLinkedList() 
        {
            head = NULL;
            tail = NULL;
        }

    void addNode(int data) // Добавление нового узла в конец списка
    {
        Node* newNode = new Node(data);
        if (head == NULL) 
        {
            head = newNode;
            tail = newNode;
        }
        else 
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
};

int addingNumbers(int num_1, int num_2)
{
    return num_1 + num_2;
}

int subtractingNumbers(int num_1, int num_2)
{
    return num_1 - num_2;
}

int multiplicationNumbers(int num_1, int num_2)
{
    return num_1 * num_2;
}

int dividingNumbers(int num_1, int num_2)
{
    if (num_2 != 0)
    {
        return num_1 / num_2;
    }
    else 
    {
        cout << "На ноль делить нельзя :)";
        return 0;
    }
}

int exponentiationNumbers(int num_1, int num_2)
{
    int a = 1;
    for (int i = 0; i < num_2; i++) 
    {
        a *= num_1;
    }
    return a;
}

int main() 
{
    setlocale(LC_ALL, "RU-ru");

    DoublyLinkedList list;
    for (int i = 0; i <= 4; ++i) // Добавление узлов в список
    {
        list.addNode(i);
    }

    int num_1;
    int num_2;
    cout << "Введите два числа через пробел: ";
    cin >> num_1 >> num_2;
    cout << "0 - Сложение" << endl;
    cout << "1 - Вычитание" << endl;
    cout << "2 - Умножение" << endl;
    cout << "3 - Деление" << endl;
    cout << "4 - Возведение в степень" << endl;
    cout << "Введите номер функции: ";
    int choiceNumber;
    cin >> choiceNumber;
    int otvet = 0;
    switch (choiceNumber)
    {
        case 0:
            otvet = addingNumbers(num_1, num_2);
            break;
        case 1:
            otvet = subtractingNumbers(num_1, num_2);
            break;
        case 2:
            otvet = multiplicationNumbers(num_1, num_2);
            break;
        case 3:
            otvet = dividingNumbers(num_1, num_2);
            break;
        case 4:
            otvet = exponentiationNumbers(num_1, num_2);
            break;
        default:
            cout << "Функция не найдена";
            return 0;
    }
    cout << "Ваш ответ: " << otvet;
    return 0;
}
