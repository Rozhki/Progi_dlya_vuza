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

class DoublyLinkedList // ����������� DoublyLinkedList ��� ������
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

    void addNode(int data) // ���������� ������ ���� � ����� ������
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
        cout << "�� ���� ������ ������ :)";
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
    for (int i = 0; i <= 4; ++i) // ���������� ����� � ������
    {
        list.addNode(i);
    }

    int num_1;
    int num_2;
    cout << "������� ��� ����� ����� ������: ";
    cin >> num_1 >> num_2;
    cout << "0 - ��������" << endl;
    cout << "1 - ���������" << endl;
    cout << "2 - ���������" << endl;
    cout << "3 - �������" << endl;
    cout << "4 - ���������� � �������" << endl;
    cout << "������� ����� �������: ";
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
            cout << "������� �� �������";
            return 0;
    }
    cout << "��� �����: " << otvet;
    return 0;
}
