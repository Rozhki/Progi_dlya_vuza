#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) // Ф-ция для создания узла
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node*& root, int data) // Ф-ция для вставки узла
{
    if (root == NULL) 
    {
        root = createNode(data);
        return 0;
    }
    if (data < root->data) 
    {
        insertNode(root->left, data);
    }
    else 
    {
        insertNode(root->right, data);
    }
}

Node* search(Node* root, int data) // Ф-ция для поиска узла
{
    if (root == NULL || root->data == data) 
    {
        return root;
    }
    if (data < root->data) 
    {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}

Node* deleteTree(Node* root) // Ф-ция для удаления дерева
{
    if (root == NULL) 
    {
        return 0;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    return 0;
}

int addingNumbers(int num_1, int num_2) // Сложение
{
    return num_1 + num_2;
}

int subtractingNumbers(int num_1, int num_2) // Вычитание
{
    return num_1 - num_2;
}

int multiplicationNumbers(int num_1, int num_2) // Умножение
{
    return num_1 * num_2;
}

int dividingNumbers(int num_1, int num_2) // Деление
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

int exponentiationNumbers(int num_1, int num_2) // Возведение в степень
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
    
    Node* root = nullptr; // Создание дерева
    for (int i = 0; i <= 4; ++i) 
    {
        insertNode(root, i);
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

    Node* choiceNode = search(root, choiceNumber);
    if (choiceNode != NULL)
    {
        int otvet = 0;
        switch (choiceNode->data) {
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
        }
        cout << "Ваш ответ: " << otvet;
    }
    else
    {
        cout << "Функция не найдена";
    }
    deleteTree(root); // Освобожденпе памяти
    return 0;
}