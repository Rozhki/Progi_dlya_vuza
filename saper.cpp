#include <iostream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define BOARD_SIZE 10
#define NUM_MINES 5

enum class CellStatus // Статус ячейки
{
    Hidden,
    Revealed,
};

enum class CellContent // Содержимое ячейки
{
    Empty,
    Mine
};

struct Cell // Ячейка
{
    CellStatus status = CellStatus::Hidden;
    CellContent content = CellContent::Empty;
};

class Minesweeper
{
    public:
        Minesweeper()
        {
            board = vector<vector<Cell>>(BOARD_SIZE, vector<Cell>(BOARD_SIZE)); // Создание пустого поля

            placeMines(); // Расставление мин на поле

            calculateAdjacentMines(); // Вычисление количества мин
        }

        void play() 
        {
            cout << " Сапёр\n\n";
            cout << " Команды: \n"
                 << " - Для открытия клетки введите координаты (x, y) через пробел.\n"
                 << " - Для выхода из игры введите 'Exit'.\n";
            displayBoard();

            while (!gameOver) 
            {
                string input;
                cout << "Введите команду: ";
                getline(cin, input);

                if (input == "Exit")
                {
                    gameOver = true;
                    cout << "Игра окончена!";
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
                        cout << "Неверные координаты. Попробуйте ещё раз.\n";
                    }
                }
                displayBoard();
                checkGameStatus();
            }
        }

    private:
        vector<vector<Cell>> board;
        bool gameOver = false;

        void placeMines() // Генератор мин
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

        void calculateAdjacentMines() // Вычисление соседних мин
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

        void revealCell(int x, int y) // Открытие ячеек 
        {
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) 
            {
                cout << "Неверные координаты. Попробуйте ещё раз.\n";
                return;
            }

            if (board[x][y].status == CellStatus::Revealed) 
            {
                cout << "Эта клетка уже открыта. Попробуйте ещё раз.\n";
                return;
            }

            board[x][y].status = CellStatus::Revealed;

            if (board[x][y].content == CellContent::Mine) 
            {
                gameOver = true;
                cout << "Вы попали на мину! Игра окончена\n";
                return;
            }

            if (board[x][y].content == CellContent::Empty) 
            {
                for (int dx = -1; dx <= 1; ++dx) // Автоматическое открытие соседних пустых ячеек
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

        void displayBoard() // Отображение
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
        void checkGameStatus() // Проверка статуса игры
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
                cout << "Поздравляем! Вы открыли все клетки. Ура, победа!";
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
