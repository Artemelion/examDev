#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Названия карт по индексам (0..12)
char rankPicture[13][3] = { "2", "3", "4", "5", "6", "7", "8","9", "10", "V", "D", "K", "A" };
// Очки карт по тем же индексам
int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

// Отображение карты по её номеру (0..51)
void showCart(int cart) {
    int mast = cart / 13; // масть
    int rank = cart % 13; // ранг
    char mastChar = static_cast<char>(mast + 3); // символ масти
    cout << mastChar << rankPicture[rank];
}

// Подсчёт очков в руке (с учётом туза как 11 или 1)
int calculPoint(char* pack, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        int card = pack[i];
        int rank = card % 13;
        int point = points[rank];
        if (point == 11 && sum > 10) point = 1; // если туз и перебор — считать как 1
        sum += point;
    }
    return sum;
}

// Увеличение массива карт в 2 раза при необходимости
void resizePack(char*& pack, int& capacity) {
    int newCapacity = capacity * 2;
    char* newPack = new char[newCapacity];
    for (int i = 0; i < capacity; i++)
        newPack[i] = pack[i];
    delete[] pack;
    pack = newPack;
    capacity = newCapacity;
}

// Добавление новой случайной карты в массив
void addCard(char*& pack, int& count, int& capacity) {
    if (count >= capacity)
        resizePack(pack, capacity);
    pack[count++] = rand() % 52;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL)); // инициализация генератора случайных чисел

    // Приветствие и ASCII-графика
    cout << "    *******************************************************" << endl;
    cout << "    *           _______                     _______       *" << endl;
    cout << "    *          |8      |                   |8      |      *" << endl;
    cout << "    *          | V   V |                   | V   V |      *" << endl;
    cout << "    *          | V   V |                   | V   V |      *" << endl;
    cout << "    *          | V   V |                   | V   V |      *" << endl;
    cout << "    *          |       |      _______      |       |      *" << endl;
    cout << "    *          |______8|     |9      |     |______8|      *" << endl;
    cout << "    *                        | V V V |                    *" << endl;
    cout << "    *                        |       |                    *" << endl;
    cout << "    *                        | V V V |                    *" << endl;
    cout << "    *                        |       |                    *" << endl;
    cout << "    *                        | V V V |                    *" << endl;
    cout << "    *                        |______6|                    *" << endl;
    cout << "    *                                                     *" << endl;
    cout << "    *         Добро пожаловать в Blackjack(21)            *" << endl;
    cout << "    *             Правила: тянуть по 1 карте              *" << endl;
    cout << "    *      Главное не взять больше 21 очка в сумме        *" << endl;
    cout << "    *******************************************************" << endl;

    // Главный игровой цикл
    while (true) {
        // Инициализация руки игрока и дилера
        int dealerCapacity = 2;
        int playerCapacity = 2;
        char* dealerPack = new char[dealerCapacity];
        char* playersPack = new char[playerCapacity];
        int dealerCount = 0;
        int playerCount = 0;

        // Начальная раздача
        addCard(playersPack, playerCount, playerCapacity);
        addCard(playersPack, playerCount, playerCapacity);
        addCard(dealerPack, dealerCount, dealerCapacity);
        addCard(dealerPack, dealerCount, dealerCapacity);

        // Ход игрока
        while (true) {
            cout << "\n************ Ваш ход ************\n";
            cout << "Ваши карты:   ";
            for (int i = 0; i < playerCount; i++) {
                showCart(playersPack[i]);
                cout << " ";
            }
            cout << "   У вас в руке: " << calculPoint(playersPack, playerCount) << " Очков\n";

            cout << "Карты дилера: ";
            showCart(dealerPack[0]); // первая карта дилера видна
            cout << " **\n"; // вторая скрыта

            if (calculPoint(playersPack, playerCount) > 21) {
                cout << "Перебор! Игрок проиграл!\n";
                break;
            }

            char answer;
            cout << "Взять карту (y / n): ";
            cin >> answer;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Неверный ввод. Повторите: ";
                cin >> answer;
            }

            if (answer != 'y' && answer != 'Y') break;
            addCard(playersPack, playerCount, playerCapacity);
        }

        // Ход дилера, пока у него <= 16 очков
        while (calculPoint(playersPack, playerCount) <= 21 && calculPoint(dealerPack, dealerCount) <= 16) {
            addCard(dealerPack, dealerCount, dealerCapacity);
        }

        // Подсчёт очков
        int dealers_point = calculPoint(dealerPack, dealerCount);
        int players_point = calculPoint(playersPack, playerCount);

        // Вывод результата
        cout << "\n************ Результат ************\n";
        cout << "Ваши карты: ";
        for (int i = 0; i < playerCount; i++) {
            showCart(playersPack[i]);
            cout << " ";
        }
        cout << " -> " << players_point << " очков\n";

        cout << "Карты дилера: ";
        for (int i = 0; i < dealerCount; i++) {
            showCart(dealerPack[i]);
            cout << " ";
        }
        cout << " -> " << dealers_point << " очков\n";

        // Определение победителя
        if (players_point > 21)
            cout << "Игрок проиграл\n";
        else if (dealers_point > 21 || players_point > dealers_point)
            cout << "Игрок выиграл\n";
        else if (players_point < dealers_point)
            cout << "Игрок проиграл\n";
        else
            cout << "Ничья\n";

        cout << "**********************************\n";

        // Освобождение памяти
        delete[] dealerPack;
        delete[] playersPack;

        // Запрос на продолжение игры
        char playAgain;
        cout << "Сыграть ещё раз? (y / n): ";
        cin >> playAgain;
        if (playAgain != 'y' && playAgain != 'Y') break;
    }

    return 0;
}
