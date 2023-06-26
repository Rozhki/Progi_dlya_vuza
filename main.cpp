#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
using namespace sf;

// Размеры окна
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Размеры игрового поля
const int BOARD_SIZE = 5;
const int CELL_SIZE = WINDOW_WIDTH / BOARD_SIZE;

// Количество мин на поле
const int NUM_MINES = 1;

enum class CellStatus
{
    Hidden,
    Revealed,
    Flagged
};

struct Cell
{
    CellStatus status = CellStatus::Hidden;
    int content = 0;
};

class Minesweeper
{
public:
    Minesweeper()
    {
        board = vector<vector<Cell>>(BOARD_SIZE, vector<Cell>(BOARD_SIZE));
        font.loadFromFile("D:\\Для проги\\Saper\\Saper\\ArialRegular.ttf");
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(Color::Black);
        generateMines();
        calculateAdjacentMines();
    }

    void play()
    {
        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Minesweeper");

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                else if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        int x = event.mouseButton.x / CELL_SIZE;
                        int y = event.mouseButton.y / CELL_SIZE;
                        revealCell(x, y);
                    }
                    else if (event.mouseButton.button == Mouse::Right)
                    {
                        int x = event.mouseButton.x / CELL_SIZE;
                        int y = event.mouseButton.y / CELL_SIZE;
                        toggleFlag(x, y);
                    }
                }
            }

            window.clear(Color::White);
            drawBoard(window);
            window.display();
        }
    }

private:
    vector<vector<Cell>> board;
    Font font;
    Text text;
    bool gameOver = false;

    void generateMines()
    {
        srand(time(nullptr));
        int count = 0;
        while (count < NUM_MINES)
        {
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;

            if (board[x][y].content != -1)
            {
                board[x][y].content = -1;
                count++;
            }
        }
    }

    void calculateAdjacentMines()
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
        {
            for (int y = 0; y < BOARD_SIZE; ++y)
            {
                if (board[x][y].content != -1)
                {
                    int count = 0;
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        for (int dy = -1; dy <= 1; ++dy)
                        {
                            int new_x = x + dx;
                            int new_y = y + dy;
                            if (isValidCell(new_x, new_y) && board[new_x][new_y].content == -1)
                            {
                                count++;
                            }
                        }
                    }
                    if (count > 0)
                    {
                        board[x][y].content = count;
                    }
                }
            }
        }
    }

    bool isValidCell(int x, int y)
    {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }

    void revealCell(int x, int y)
    {
        if (!isValidCell(x, y) || board[x][y].status == CellStatus::Revealed)
        {
            return;
        }

        board[x][y].status = CellStatus::Revealed;

        if (board[x][y].content == -1)
        {
            gameOver = true;
            text.setString("Game over, because you hit mine");
            text.setPosition(10.0f, 10.0f);
            return;
        }

        if (board[x][y].content == 0)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (isValidCell(new_x, new_y) && board[new_x][new_y].status != CellStatus::Revealed && board[new_x][new_y].content != -1)
                    {
                        revealCell(new_x, new_y);
                    }
                }
            }
        }
    }

    void toggleFlag(int x, int y)
    {
        if (!isValidCell(x, y))
        {
            return;
        }

        if (board[x][y].status == CellStatus::Revealed)
        {
            return;
        }

        if (board[x][y].status == CellStatus::Hidden)
        {
            board[x][y].status = CellStatus::Flagged;
        }
        else if (board[x][y].status == CellStatus::Flagged)
        {
            board[x][y].status = CellStatus::Hidden;
        }
    }

    void drawBoard(RenderWindow& window)
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
        {
            for (int y = 0; y < BOARD_SIZE; ++y)
            {
                RectangleShape cellShape(Vector2f(CELL_SIZE, CELL_SIZE));
                cellShape.setPosition(x * CELL_SIZE, y * CELL_SIZE);

                if (board[x][y].status == CellStatus::Hidden)
                {
                    cellShape.setFillColor(Color(128, 128, 128)); // Серый цвет
                    cellShape.setOutlineColor(Color::Black);
                    cellShape.setOutlineThickness(1.0f);
                }
                else if (board[x][y].status == CellStatus::Revealed)
                {
                    if (board[x][y].content == -1)
                    {
                        cellShape.setFillColor(Color::Red);
                    }
                    else if (board[x][y].content == 0)
                    {
                        cellShape.setFillColor(Color::White);
                    }
                    else
                    {
                        cellShape.setFillColor(Color::Green);
                    }
                    cellShape.setOutlineColor(Color::Black);
                    cellShape.setOutlineThickness(1.0f);
                }
                else if (board[x][y].status == CellStatus::Flagged)
                {
                    cellShape.setFillColor(Color::Yellow);
                    cellShape.setOutlineColor(Color::Black);
                    cellShape.setOutlineThickness(1.0f);
                }
                window.draw(cellShape);

                if (board[x][y].status == CellStatus::Revealed && board[x][y].content > 0)
                {
                    int adjacentMines = board[x][y].content;

                    Text cellText;
                    cellText.setFont(font);
                    cellText.setCharacterSize(24);
                    cellText.setFillColor(Color::Black);
                    cellText.setString(std::to_string(adjacentMines));
                    cellText.setPosition(x * CELL_SIZE + 0.35f * CELL_SIZE, y * CELL_SIZE + 0.25f * CELL_SIZE);
                    window.draw(cellText);
                }
            }
        }
        if (gameOver)
        {
            window.draw(text);
        }
    }
};

int main()
{
    Minesweeper game;
    game.play();

    return 0;
}
