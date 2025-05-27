﻿#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Functions.h"


using namespace std;

//Назначение символам карты (0–12)
char rankPicture[13][3] = { "2", "3", "4", "5", "6", "7", "8","9", "10", "V", "D", "K", "A" };
//Ценность карт
int points[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

// Максимум 12 карт в руке — физически невозможно набрать больше
const int MAX_CARDS = 12;
char dealerPack[MAX_CARDS];
char playersPack[MAX_CARDS];
int dealerCount = 0;
int playerCount = 0;

// Показывает карту
void showCart(int cart)
{

}

// Подсчёт очков
int calculPoint(char pack[], int count)
{
	int sum = 0;
	return sum;
}

// Добавляет карту в руку
void addCard(char pack[], int& count)
{

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

	// Раздача карт
	addCard(playersPack, playerCount);
	addCard(playersPack, playerCount);
	addCard(dealerPack, dealerCount);
	addCard(dealerPack, dealerCount);
	while (true)
	{
		cout << "************ Ваш ход ************\n";
		cout << "Ваши карты:      ";
		for (int i = 0; i < playerCount; i++)
		{
			showCart(playersPack[i]);
			cout << " ";
		}
		cout << "   У вас в руке: " << calculPoint(playersPack, playerCount) << " Очков\n";

		cout << "Карты компютера: ";
		showCart(dealerPack[0]);
		cout << " **\n";

		if (calculPoint(playersPack, playerCount) > 21)
		{
			cout << "Перебор! Игрок проиграл!\n";
			return 0;
		}

		char answer;
		cout << "Взять карту (y / n): ";
		cin >> answer;
		if (answer != 'y' && answer != 'Y') break;

		addCard(playersPack, playerCount);
		cout << "\n";
	}

	while (true)
	{
		cout << "************ Ход дилера ************\n";
		cout << "Ваши карты:      ";
		for (int i = 0; i < playerCount; i++)
		{
			showCart(playersPack[i]);
			cout << " ";
		}
		cout << "   У вас в руке: " << calculPoint(playersPack, playerCount) << " Очков\n";

		cout << "Карты компютера: ";
		for (int i = 0; i < dealerCount; i++)
		{
			showCart(dealerPack[i]);
			cout << " ";
		}
		cout << "   У диллера: " << calculPoint(dealerPack, dealerCount) << " Очков\n";

		if (calculPoint(dealerPack, dealerCount) > 16) break;
		addCard(dealerPack, dealerCount);
	}

	// Определяем победителя
	int dealers_point = calculPoint(dealerPack, dealerCount);
	int players_point = calculPoint(playersPack, playerCount);

}

