#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char rankPicture[13][3] = { "2", "3", "4", "5", "6", "7", "8","9", "10", "V", "D", "K", "A" };
int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

int dealerCapacity = 2;
int playerCapacity = 2;
char* dealerPack = new char[dealerCapacity];
char* playersPack = new char[playerCapacity];
int dealerCount = 0;
int playerCount = 0;

void showCart(int cart)
{
    int mast = cart / 13;
    int rank = cart % 13;
    char mastChar = static_cast<char>(mast + 3);
    cout << mastChar << rankPicture[rank];
}

int calculPoint(char* pack, int count)
{
    int sum = 0;
    for (int i = 0; i < count; i++)
    {
        int card = pack[i];
        int rank = card % 13;
        int point = points[rank];
        if (point == 11 && sum > 10) point = 1;
        sum += point;
    }
    return sum;
}

void resizePack(char*& pack, int& capacity)
{
    int newCapacity = capacity * 2;
    char* newPack = new char[newCapacity];
    for (int i = 0; i < capacity; i++)
        newPack[i] = pack[i];
    delete[] pack;
    pack = newPack;
    capacity = newCapacity;
}

void addCard(char*& pack, int& count, int& capacity)
{
    if (count >= capacity)
        resizePack(pack, capacity);
    pack[count++] = rand() % 52;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    cout << "    *******************************************************" << endl;
    cout << "    *           _______                     _______       *" << endl;
    cout << "    *          |8      |                   |8      |      *" << endl;
    cout << "    *          | V   V |                   | V   V |      *" << endl;
    cout << "    *          | V   V |                   | V   V |      *" << endl;
    cout << "    *          | V   V |                   | V   V |      *" << endl;
    cout << "    *          | V   V |      _______      | V   V |      *" << endl;
    cout << "    *          |       |     |9      |     |       |      *" << endl;
    cout << "    *          |______8|     | V V V |     |______8|      *" << endl;
    cout << "    *                        |       |                    *" << endl;
    cout << "    *                        | V V V |                    *" << endl;
    cout << "    *                        |       |                    *" << endl;
    cout << "    *                        | V V V |                    *" << endl;
    cout << "    *                        |______6|                    *" << endl;
    cout << "    *                                                     *" << endl;
    cout << "    *                                                     *" << endl;
    cout << "    *******************************************************" << endl;
    cout << "    *         Добро пожаловать в Blackjack(21)            *" << endl;
    cout << "    *             Правила: тянуть по 1 карте              *" << endl;
    cout << "    *      Главное не взять больше 21 очка в сумме        *" << endl;
    cout << "    *                                                     *" << endl;
    cout << "    *******************************************************" << endl;

    addCard(playersPack, playerCount, playerCapacity);
    addCard(playersPack, playerCount, playerCapacity);
    addCard(dealerPack, dealerCount, dealerCapacity);
    addCard(dealerPack, dealerCount, dealerCapacity);

    while (true)
    {
        cout << "\n************ Ваш ход ************\n";
        cout << "Ваши карты:   ";
        for (int i = 0; i < playerCount; i++)
        {
            showCart(playersPack[i]);
            cout << " ";
        }
        cout << "   У вас в руке: " << calculPoint(playersPack, playerCount) << " Очков\n";

        cout << "Карты дилера: ";
        showCart(dealerPack[0]);
        cout << " **\n";

        if (calculPoint(playersPack, playerCount) > 21)
        {
            cout << "Перебор! Игрок проиграл!\n";
            delete[] dealerPack;
            delete[] playersPack;
            return 0;
        }

        char answer;
        cout << "Взять карту (y / n): ";
        cin >> answer;
        if (answer != 'y' && answer != 'Y') break;

        addCard(playersPack, playerCount, playerCapacity);
    }

    while (true)
    {
        cout << "\n************ Ход дилера ************\n";
        cout << "Ваши карты:      ";
        for (int i = 0; i < playerCount; i++)
        {
            showCart(playersPack[i]);
            cout << " ";
        }
        cout << "   У вас в руке: " << calculPoint(playersPack, playerCount) << " Очков\n";

        cout << "Карты дилера: ";
        for (int i = 0; i < dealerCount; i++)
        {
            showCart(dealerPack[i]);
            cout << " ";
        }
        cout << "   У дилера: " << calculPoint(dealerPack, dealerCount) << " Очков\n";

        if (calculPoint(dealerPack, dealerCount) > 16) break;
        addCard(dealerPack, dealerCount, dealerCapacity);
    }

    int dealers_point = calculPoint(dealerPack, dealerCount);
    int players_point = calculPoint(playersPack, playerCount);

    cout << "\n************ Результат ************\n";
    if (dealers_point == 21)
        cout << "Дилер выиграл\n";
    else if (dealers_point > 21)
        cout << "Игрок выиграл\n";
    else if (dealers_point > players_point)
        cout << "Игрок проиграл\n";
    else if (dealers_point == players_point)
        cout << "Ничья\n";
    else
        cout << "Игрок выиграл\n";
    cout << "**********************************\n";

    delete[] dealerPack;
    delete[] playersPack;
    return 0;
}