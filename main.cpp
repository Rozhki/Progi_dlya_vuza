#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define BOARD_SIZE 10
#define NUM_MINES 5

enum class CellStatus // ������ ������
{
    Hidden,
    Revealed,
};

enum class CellContent // ���������� ������
{
    Empty,
    Mine
};

struct Cell // ������
{
    CellStatus status = CellStatus::Hidden;
    CellContent content = CellContent::Empty;
};

class Minesweeper
{
    public:
        Minesweeper()
        {
            board = vector<vector<Cell>>(BOARD_SIZE, vector<Cell>(BOARD_SIZE)); // �������� ������� ����

            placeMines(); // ������������ ��� �� ����

            calculateAdjacentMines(); // ���������� ���������� ���
        }

        void play() 
        {
            cout << " ����\n\n";
            cout << " �������: \n"
                 << " - ��� �������� ������ ������� ���������� (x, y) ����� ������.\n"
                 << " - ��� ������ �� ���� ������� 'Exit'.\n";
            displayBoard();

            while (!gameOver) 
            {
                string input;
                cout << "������� �������: ";
                getline(cin, input);

                if (input == "Exit")
                {
                    gameOver = true;
                    cout << "���� ��������!";
                    break;
                }
                else
                {
                    int x, y;
                    istringstream iss(input);
                    if (iss >> x >> y)
                    {
                        revealCell(x, y);
                    }
                    else
                    {
                        cout << "�������� ����������. ���������� ��� ���.\n";
                    }
                }
                displayBoard();
                checkGameStatus();
            }
        }

    private:
        vector<vector<Cell>> board;
        bool gameOver = false;

        void placeMines() // ��������� ���
        {
            srand(static_cast<int>(time(0)));
            int count = 0;
            while (count < NUM_MINES) 
            {
                int x = rand() % BOARD_SIZE;
                int y = rand() % BOARD_SIZE;

                if (board[x][y].content != CellContent::Mine) 
                {
                    board[x][y].content = CellContent::Mine;
                    count++;
                }
            }
        }

        void calculateAdjacentMines() // ���������� �������� ���
        {
            for (int x = 0; x < BOARD_SIZE; ++x)
            {
                for (int y = 0; y < BOARD_SIZE; ++y)
                {
                    if (board[x][y].content != CellContent::Mine)
                    {
                        int count = 0;
                        for (int dx = -1; dx <= 1; ++dx)
                        {
                            for (int dy = -1; dy <= 1; ++dy)
                            {
                                int new_x = x + dx;
                                int new_y = y + dy;
                                if ((new_x >= 0 && new_x < BOARD_SIZE) && (new_y >= 0 && new_y < BOARD_SIZE) && (board[new_x][new_y].content == CellContent::Mine))
                                {
                                    count++;
                                }
                            }
                        }
                        if (count > 0)
                        {
                            board[x][y].content = static_cast<CellContent>(count);
                        }
                    }
                }
            }
        }

        void revealCell(int x, int y) // �������� ����� 
        {
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) 
            {
                cout << "�������� ����������. ���������� ��� ���.\n";
                return;
            }

            if (board[x][y].status == CellStatus::Revealed) 
            {
                cout << "��� ������ ��� �������. ���������� ��� ���.\n";
                return;
            }

            board[x][y].status = CellStatus::Revealed;

            if (board[x][y].content == CellContent::Mine) 
            {
                gameOver = true;
                cout << "�� ������ �� ����! ���� ��������\n";
                return;
            }

            if (board[x][y].content == CellContent::Empty) 
            {
                for (int dx = -1; dx <= 1; ++dx) // �������������� �������� �������� ������ �����
                {
                    for (int dy = -1; dy <= 1; ++dy) 
                    {
                        int new_x = x + dx;
                        int new_y = y + dy;
                        if ((new_x >= 0 && new_x < BOARD_SIZE) && (new_y >= 0 && new_y < BOARD_SIZE) && (board[new_x][new_y].status == CellStatus::Hidden) && (board[new_x][new_y].content != CellContent::Mine))
                        {
                            revealCell(new_x, new_y);
                        }
                    }
                }
            }

        }

        void displayBoard() // �����������
        {
            cout << "  ";
            for (int i = 0; i < BOARD_SIZE; ++i) 
            {
                cout << i << " ";
            }
            cout << "\n";

            for (int x = 0; x < BOARD_SIZE; ++x) 
            {
                cout << x << " ";
                for (int y = 0; y < BOARD_SIZE; ++y) 
                {
                    if (board[x][y].status == CellStatus::Hidden) 
                    {
                        cout << "X ";
                    }
                    else if (board[x][y].status == CellStatus::Revealed)
                    {
                        if (board[x][y].content == CellContent::Mine)
                        {
                            cout << "M ";
                        }
                        else if (board[x][y].content == CellContent::Empty)
                        {
                            cout << "- ";
                        }
                        else
                        {
                            cout << static_cast<int>(board[x][y].content) << " ";
                        }
                    }
                    else 
                    {
                        cout << "F ";
                    }
                }
                cout << "\n";
            }
            cout << "\n";
        }
        void checkGameStatus() // �������� ������� ����
        {
            int numHiddenCells = 0;
            for (int x = 0; x < BOARD_SIZE; ++x) 
            {
                for (int y = 0; y < BOARD_SIZE; ++y) 
                {
                    if (board[x][y].status == CellStatus::Hidden) 
                    {
                        numHiddenCells++;
                    }
                }
            }

            if (numHiddenCells == NUM_MINES) 
            {
                gameOver = true;
                cout << "�����������! �� ������� ��� ������. ���, ������!";
            }
        }
};

int main() 
{
    setlocale(LC_ALL, "RU-ru");
    Minesweeper game;
    game.play();
    return 0;
}