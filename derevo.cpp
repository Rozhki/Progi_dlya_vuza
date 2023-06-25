#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) // �-��� ��� �������� ����
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node*& root, int data) // �-��� ��� ������� ����
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

Node* search(Node* root, int data) // �-��� ��� ������ ����
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

Node* deleteTree(Node* root) // �-��� ��� �������� ������
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

int addingNumbers(int num_1, int num_2) // ��������
{
    return num_1 + num_2;
}

int subtractingNumbers(int num_1, int num_2) // ���������
{
    return num_1 - num_2;
}

int multiplicationNumbers(int num_1, int num_2) // ���������
{
    return num_1 * num_2;
}

int dividingNumbers(int num_1, int num_2) // �������
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

int exponentiationNumbers(int num_1, int num_2) // ���������� � �������
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
    
    Node* root = nullptr; // �������� ������
    for (int i = 0; i <= 4; ++i) 
    {
        insertNode(root, i);
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
        cout << "��� �����: " << otvet;
    }
    else
    {
        cout << "������� �� �������";
    }
    deleteTree(root); // ������������ ������
    return 0;
}