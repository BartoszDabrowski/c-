#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <math.h>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <string>


using namespace std;
//  algorytm  //koniec

bool gra = true, surr = false, test = false, trafiony = true, pvp = true;
int win = 0, lose = 0, win1 = 0;
char x1;
int x = 0, y = 0;
int menu;


void legenda();
void gotoxy(int x, int y);
void show(char a);
void set_ship();
void ustawianie();
void ship_g();
void ship_b();
void ship(int x, int y, int z, char a);
void cel();
void baner();
void baner_a();
void stats();
void game(char a);
void check(char a, bool &trafiony, int &win, int &win1);
void player(char a, bool &trafiony, bool &surr, int &win, int &win1);
void bot(bool &trafiony, bool &surr, int &lose);

int g1[10][10];
int p1[10][10];
int g2[10][10];
int p2[10][10];

int main()
{
	ustawianie();
	ship_b();

	int getch(void);
	baner_a();//z animacja;
	cout << endl << "Wci\230nij spacj\251 ,aby kontynuowa\206" << endl;
	while (getch() != ' ') {}

	system("cls");
	baner();
	cout << endl;
	cout << "[1] Zacznij gr\251 vs AI" << endl;
	cout << "[2] Zacznij gr\251 vs Gracz" << endl;
	cout << "[3] Koniec programu" << endl;
	do
	{
		menu = getch();
	} while (!(menu == 49 || menu == 50 || menu == 51));
	if (menu == 51)
	{
		system("pause");
		return 0;
	}
	if (menu == 49)
	{
		pvp = false;
		game(97);
		stats();
		menu--;
	}
	if (menu == 50)game(98);



	system("pause");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void stats()
{
	fstream save;
	fstream load;
	string bufor;
	int wins = 0, loses = 0;

	load.open("staty.txt", ios::in);
	if (!load.good()) exit(1);
	load >> bufor >> wins >> bufor >> loses;
	load.close();
	save.open("staty.txt", ios::out);

	if (surr) loses++;
	if (win == 20) wins++;
	if (lose == 20) loses++;
	save << "Wygrano: " << wins << endl;
	save << "Przegrano: " << loses;
	cout << endl << "Wygrano " << wins << " razy" << endl;
	cout << "Przegrano " << loses << " razy" << endl;
	save.close();
}

void cel() 
{
	bool test = false;
	string y1;
	do
	{
		test = false;
		cin >> x1 >> y1;
		for (int i = 0; i < y1.length(); i++)
		{
			char a = y1[i];
			if ((a<48) || (a>57))
			{
				cout << "Nieprawid\210owe dane" << endl;
				test = true;
				break;
			}
		}
		if (!test)
		{
			istringstream xxx(y1);
			xxx >> y;
			if ((((x1 > 96) && (x1 < 107)) || ((x1 > 64) && (x1 < 75))) && ((y<11) && (y >= 0)))
			{
				if ((x1 > 64) && (x1 < 75)) x1 -= 65;
				else x1 -= 97;
				test = false;
			}
			else
			{
				cout << "Nieprawid\210owe dane" << endl;
				test = true;
			}
			
		}
	} while (test);
	x = int(x1);
	y--;
}

void legenda()
{
	if (!pvp)
	{
		gotoxy(30, 1);
		cout << "Legenda :		Zosta\210o do ustrzelenia: " << 20 - win << "		Twoich przetrwa\210o: " << 20 - lose;
		gotoxy(30, 2);
		cout << char(176) << " - Pole wolne            'a1'- Tak podawaj wsp\242\210rz\251dne";
		gotoxy(30, 3);
		cout << char(254) << " - Statek";
		gotoxy(30, 4);
		cout << char(111) << " - Pud\210o";
		gotoxy(30, 5);
		cout << char(120) << " - Trafiony";
	}
	else
	{
		gotoxy(30, 1);
		cout << "Legenda :		Gracz1: " << win << "		Gracz2: " << win1;
		gotoxy(30, 2);
		cout << char(176) << " - Pole wolne            'a1'- Tak podawaj wsp\242\210rz\251dne";
		gotoxy(30, 3);
		cout << char(254) << " - Statek";
		gotoxy(30, 4);
		cout << char(111) << " - Pud\210o";
		gotoxy(30, 5);
		cout << char(120) << " - Trafiony";
	}

}

void show(char a)
{
	if (a == 97)
	{
		gotoxy(10, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		for (int i = 0; i < 10; i++)
		{

			for (int y = 0; y < 10; y++)
			{
				//cout << g1[y][i] << " ";
				if ((g1[y][i] == 0) || (g1[y][i] == 2) || (g1[y][i] == 3))cout << char(176) << " ";
				else if (g1[y][i] == 4) cout << char(120) << " ";
				else cout << char(254) << " ";
			}
			gotoxy(10, 11 + i);
		}
		gotoxy(15, 8);

		cout << "Twoje statki	Gracz1";
		gotoxy(9, 9);
		for (int i = 0; i < 10; i++) 	cout << " " << char(i + 65);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(7, 10 + i);
			cout << i + 1;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(50, i + 10);
			for (int y = 0; y < 10; y++)
			{
				//cout << g2[y][i]<<" ";
				if ((p1[y][i] == 0) || (p1[y][i] == 2))cout << char(176) << " ";
				else if (p1[y][i] == 3) cout << char(111) << " ";
				else cout << char(120) << " ";
			}
		}
		gotoxy(50, 8);

		cout << "Plansza celownicza";
		gotoxy(49, 9);
		for (int i = 0; i < 10; i++)cout << " " << char(i + 65);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(47, 10 + i);
			cout << i + 1;
		}
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else
	{
		gotoxy(10, 10);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		for (int i = 0; i < 10; i++)
		{

			for (int y = 0; y < 10; y++)
			{
				//cout << g1[y][i] << " ";
				if ((g2[y][i] == 0) || (g2[y][i] == 2) || (g2[y][i] == 3))cout << char(176) << " ";
				else if (g2[y][i] == 4) cout << char(120) << " ";
				else cout << char(254) << " ";
			}
			gotoxy(10, 11 + i);
		}
		gotoxy(15, 8);

		cout << "Twoje statki	Gracz2";
		gotoxy(9, 9);
		for (int i = 0; i < 10; i++) 	cout << " " << char(i + 65);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(7, 10 + i);
			cout << i + 1;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(50, i + 10);
			for (int y = 0; y < 10; y++)
			{
				//cout << g2[y][i]<<" ";
				if ((p2[y][i] == 0) || (p2[y][i] == 2))cout << char(176) << " ";
				else if (p2[y][i] == 3) cout << char(111) << " ";
				else cout << char(120) << " ";
			}
		}
		gotoxy(50, 8);

		cout << "Plansza celownicza";
		gotoxy(49, 9);
		for (int i = 0; i < 10; i++)cout << " " << char(i + 65);
		for (int i = 0; i < 10; i++)
		{
			gotoxy(47, 10 + i);
			cout << i + 1;
		}
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

}

void ship_b()
{
	fstream plik1;
	plik1.open("statki.txt", ios::in);
	if (!(plik1.good())) exit(1);
	srand(time(NULL));
	int los = rand() % 6;
	//int los = 0;
	plik1.seekg(212 * los);
	int x;
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < 10; y++)
		{
			plik1 >> x;
			g2[y][i] = x;
		}
	}
	plik1.close();
}

void ship_g()
{
	fstream  plik2;
	plik2.open("statki_.txt", ios::in);
	if (!(plik2.good())) exit(2);
	srand(time(NULL));
	int los = rand() % 2;
	plik2.seekg(210 * los);
	int x;
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < 10; y++)
		{
			plik2 >> x;
			g1[y][i] = x;
		}
	}
	plik2.close();
}

void set_ship()
{
	int getch(void);
	int mmenu;
	int a = 1, b = 2, c = 3, d = 4;
	while (a || b || c || d)
	{
		system("cls");
		cout << "- - - -Pozosta\210e statki : - - -                      'a1'- Tak podawaj wsp\242\210rz\251dne" << endl;
		if (a)cout << "[1] " << a << " x 4pola" << endl;
		if (b)cout << "[2] " << b << " x 3pola" << endl;
		if (c)cout << "[3] " << c << " x 2pola" << endl;
		if (d)cout << "[4] " << d << " x 1pola" << endl;
		show(97);
		cout << "Kt\242ry statek chcesz umie\230ci\206?" << endl;
		switch (getch())
		{
		case 49:
			if (a)
			{
				cout << "Ustawiasz statek o rozmiarze 4 p\242l " << endl;
				cout << "[1] Pionowo " << endl;
				cout << "[2] Poziomo " << endl;
				do
				{
					mmenu = getch();
				} while (mmenu != 49 && mmenu != 50);
				switch (mmenu)
				{
				case 49:
					cout << "Podaj wsp\242\210rz\251dne g\242rnego punktu" << endl;
					do
					{
						cel();
						if ((g1[x][y] != 0) || (g1[x][y + 1] != 0) || (g1[x][y + 2] != 0) || (y>6))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
					} while ((g1[x][y] != 0) || (g1[x][y + 1] != 0) || (g1[x][y + 2] != 0) || (y>6));
					ship(x, y, 4, 97);
					break;
				case 50:
					cout << "Podaj wsp\242\210rz\251dne lewego punktu" << endl;
					do
					{
						cel();
						if ((g1[x][y] != 0) || (g1[x + 1][y] != 0) || (g1[x + 2][y] != 0) || (g1[x + 3][y] != 0) || (x>6))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
					} while ((g1[x][y] != 0) || (g1[x + 1][y] != 0) || (g1[x + 2][y] != 0) || (g1[x + 3][y] != 0) || (x>6));
					ship(x, y, 4, b);
					break;
				default:
					break;
				}
				a--;
			}
			break;
		case 50:
			if (b)
			{
				cout << "Ustawiasz statek o rozmiarze 3 p\242l " << endl;
				cout << "[1] Pionowo " << endl;
				cout << "[2] Poziomo " << endl;
				do
				{
					mmenu = getch();
				} while (mmenu != 49 && mmenu != 50);
				switch (mmenu)
				{
				case 49:
					cout << "Podaj wsp\242\210rz\251dne g\242rnego punktu" << endl;
					do
					{
						cel();
						if ((g1[x][y] != 0) || (g1[x][y + 1] != 0) || (g1[x][y + 2] != 0) || (y>7))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
					} while ((g1[x][y] != 0) || (g1[x][y + 1] != 0) || (g1[x][y + 2] != 0) || (y>7));
					ship(x, y, 3, 97);
					break;
				case 50:
					cout << "Podaj wsp\242\210rz\251dne lewego punktu" << endl;
					do
					{
						cel();
						if ((g1[x][y] != 0) || (g1[x + 1][y] != 0) || (g1[x + 2][y] != 0) || (x>7))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
					} while ((g1[x][y] != 0) || (g1[x + 1][y] != 0) || (g1[x + 2][y] != 0) || (x>7));
					ship(x, y, 3, b);
					break;
				default:
					break;
				}
				b--;
			}
			break;
		case 51:
			if (c)
			{
				cout << "Ustawiasz statek o rozmiarze 2 p\242l " << endl;
				cout << "[1] Pionowo " << endl;
				cout << "[2] Poziomo " << endl;
				do
				{
					mmenu = getch();
				} while (mmenu != 49 && mmenu != 50);
				switch (mmenu)
				{
				case 49:
					cout << "Podaj wsp\242\210rz\251dne g\242rnego punktu" << endl;
					do
					{
						cel();
						if ((g1[x][y] != 0) || (g1[x][y + 1] != 0) || (y>8))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
					} while ((g1[x][y] != 0) || (g1[x][y + 1] != 0) || (y>8));
					ship(x, y, 2, 97);
					break;
				case 50:
					cout << "Podaj wsp\242\210rz\251dne lewego punktu" << endl;
					do
					{
						cel();
						if ((g1[x][y] != 0) || (g1[x + 1][y] != 0) || (x>8))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
					} while ((g1[x][y] != 0) || (g1[x + 1][y] != 0) || (x>8));
					ship(x, y, 2, b);
					break;
				default:
					break;
				}
				c--;
			}
			break;
		case 52:
			if (d)
			{
				cout << "Ustawiasz statek o rozmiarze 1 pola " << endl;
				cout << "Podaj wsp\242\210rz\251dne punktu" << endl;
				do
				{
					cel();
					if ((g1[x][y] != 0))cout << "Nie mo\276esz w tym miejscu umie\230ci\206 statku" << endl;
				} while (g1[x][y] != 0);
				ship(x, y, 1, 97);
				d--;
			}
			break;
		default:
			break;

		}
	}
}

void ustawianie()
{
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; i < 10; i++)
		{
			g1[y][i] = 0;
			p1[y][i] = 0;
			g2[y][i] = 0;
			p2[y][i] = 0;
		}

	}
}

void ship(int x, int y, int z, char a)
{
	if (a == 97)
	{
		for (int i = 0; i < z; i++)
		{
			if ((x <= 8) && (y <= 8))g1[x + 1][y + i] = 2;
			g1[x][y + i] = 1;
			if ((x != 0) && (y <= 8))g1[x - 1][y + i] = 2;

		}
		if ((y - 1) >= 0)g1[x][y - 1] = 2;
		if ((y + z)<10)g1[x][y + z] = 2;
	}
	else
	{
		for (int i = 0; i < z; i++)
		{
			if ((x <= 8) && (y <= 8))g1[x + i][y + 1] = 2;
			g1[x + i][y] = 1;
			if ((y != 0) && (x <= 8))g1[x + i][y - 1] = 2;

		}
		if (x - 1 >= 0)g1[x - 1][y] = 2;
		if (x + z< 10)g1[x + z][y] = 2;
	}

}

void baner()
{
	fstream plik3;
	string bufor;
	int i = 4;

	plik3.open("baner.txt", ios::in);
	if (!(plik3.good())) exit(1);

	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -STATKI - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	while (getline(plik3, bufor))
	{
		gotoxy(20, i);
		cout << bufor;
		i++;
	}
	//plik3.seekg(0);
	plik3.close();
}

void game(char a)
{
	int getch(void);
	if (a == 97)  //wersja vs ai
	{
		system("cls");
		baner();
		cout << endl;
		cout << "[1] Sam ustawiam statki" << endl;
		cout << "[2] Ustaw za mnie" << endl;
		do
		{
			menu = getch();
		} while (!(menu == 49 || menu == 50));
		if (menu == 49) set_ship();
		else ship_g();

		do
		{
			trafiony = true, test = false;
			player(97, trafiony, surr, win, win1);

			if (win == 20)	break;
			if (surr) break;
			trafiony = true;

			bot(trafiony, surr, lose);

			if (lose == 20) gra = false;
		} while (gra);

		system("cls");
		show(97);
		if (win == 20) cout << "Wygra\210e\230" << endl;
		if (lose == 20) cout << "Przegra\210e\230" << endl;
	}
	else
	{
		system("cls"); //wersja vs gracz
		ship_g();
		do
		{

			trafiony = true, test = false;

			player(97, trafiony, surr, win, win1);
			if (win == 20) gra = false;
			if ((!surr || win != 20) && gra == true)
			{
				for (int i = 5; i > 0; i--)
				{
					system("cls");
					gotoxy(20, 4);
					cout << "ZMIANA GRACZA ZA :" << i;
					Sleep(1000);
				}
			}

			if (win == 20)	break;
			if (surr) break;
			trafiony = true;
			player(98, trafiony, surr, win, win1);

			if (win1 == 20) gra = false;
			if ((!surr || win1 != 20) && gra == true)
			{
				for (int i = 5; i > 0; i--)
				{
					system("cls");
					gotoxy(20, 4);
					cout << "ZMIANA GRACZA ZA :" << i;
					Sleep(1000);
				}
			}

		} while (gra);

		if (win == 20)
		{
			system("cls");
			show(97);
			cout << endl << "Wygra\210 gracz 1" << endl;
		}
		if (win1 == 20)
		{
			system("cls");
			show(98);
			cout << endl << "Wygra\210 gracz 2" << endl;
		}
	}

}

void check(char a, bool &trafiony, int &win, int &win1)
{
	if (a == 97)
	{
		if (g2[x][y] == 1)
		{
			p1[x][y] = 4;
			g2[x][y] = 4;
			cout << "Trafiony" << endl;
			trafiony = true;
			win++;
		}
		else
		{
			p1[x][y] = 3;
			cout << "Pud\210o" << endl;
			trafiony = false;
		}
	}
	else
	{
		if (g1[x][y] == 1)
		{
			p2[x][y] = 4;
			g1[x][y] = 4;
			cout << "Trafiony" << endl;
			trafiony = true;
			win1++;
		}
		else
		{
			p2[x][y] = 3;
			cout << "Pud\210o" << endl;
			trafiony = false;
		}
	}
}

void player(char a, bool &trafiony, bool &surr, int &win, int &win1)
{
	int getch(void);
	while (trafiony) //ruch gracza
	{
		int menu1;

		system("cls");
		legenda();
		if (a == 97)show(97);
		else show(98);
		cout << "[1] Podaj wsp\242\210rz\251dne celu" << endl;
		cout << "[2] Poddaj si\251" << endl;
		do
		{
			menu1 = getch();
		} while (!(menu1 == 49 || menu1 == 50));
		if (menu1 == 50)
		{
			int menus;
			cout << "Na pewno? [y/n]" << endl;
			do
			{
				menus = getch();
			} while (!(menus == 121 || menus == 110));
			if (menus==121)
			{
				if (a == 97)
				{
					surr = true;
					win1 = 20;
				}
				else
				{
					surr = true;
					win = 20;
				}
			}
			else continue;
		}
		if (surr) break;
		cout << "Podaj wsp\242\210rz\251dne celu" << endl;
		cel();
		if (a == 97)
		{
			if (p1[x][y] != 0)
			{
				cout << "Tu ju\276 celowa\210es" << endl;
				Sleep(1500);
				continue;
			}
		}
		else
		{
			if (p2[x][y] != 0)
			{
				cout << "Tu ju\276 celowa\210es" << endl;
				Sleep(1500);
				continue;
			}
		}
		if (a == 97)check(97, trafiony, win, win1);
		else check(98, trafiony, win, win1);

		if (win == 20)	break;
		if (win1 == 20)	break;
		Sleep(1500);
	}
	if (surr) gra = false;
}

void bot(bool &trafiony, bool &surr, int &lose)
{
	while (trafiony)
	{
		srand(time(NULL));
		system("cls");
		gotoxy(20, 1);
		cout << "RUCH AI";
		do
		{
			x = rand() % 10;
			y = rand() % 10;
		} while (g1[x][y] == 3 || g1[x][y] == 4);
		x1 = char(x + 65);
		show(97);
		cout << "Celuj\251 w: ";
		Sleep(500);
		cout << x1 << y + 1;
		if (g1[x][y] == 1)
		{
			g1[x][y] = 4;
			cout << " Trafiony" << endl;
		}
		else
		{
			g1[x][y] = 3;
			cout << " Pud\210o" << endl;
			trafiony = false;
		}
		Sleep(1500);
		lose = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (g1[i][y] == 4) lose++;
			}
		}
		if (lose == 20) break;
	}
}

void baner_a()
{
	fstream plik3;
	string bufor[14];
	int i = 0;

	plik3.open("animated.txt", ios::in);
	if (!(plik3.good())) exit(1);

	for (int y = 0; y < 23; y++)
	{
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -STATKI - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for  (i = 0; i < 14; i++)
		{	
			getline(plik3, bufor[i]);
			cout << bufor[i] << endl;

		} 
		Sleep(100);
		system("cls");
	}
	for (i = 1; i < 21; i++)
	{
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -STATKI - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		for (int y = 0; y < 14; y++)
		{
			gotoxy(i , y+4);
			cout << bufor[y];

		}
		Sleep(100);
		if (i != 20)system("cls");
	}
	
	
	//system("cls");
		
	
	Sleep(200);
	plik3.close();
}