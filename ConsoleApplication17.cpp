//	Выполнил ст. группы М3О-214Б-19.
/*
	Практическое задание №3 - потоки.

	Есть двумерный массив изображения в градациях серого
	(на предыдущих занятия его оформляли в виде класса и можно воспользоваться
	 данным классом).
1.	Необходимо разработать функцию, которая будет выполнять расчет гистограммы изображения
2.	Необходимо распараллелить вычисление гистограммы на несколько потоков
3.	Выполнить измерение времени вычисления гистограммы изображения.
4.	Построить график зависимости времени вычисления от числа потоков (от 1 до 20)
	Объяснить график.
*/


#include "timer.h"
#include <thread>
#include <iostream>
#include <windows.h>
#include <vector>
#include <mutex>
#include <future>
#include <queue>
#include <chrono>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Image {
private:
	const int rows = 100, cols = 100;
	vector<vector<int>> array;
	int	
		result;
	atomic< unsigned int> Ox[16];
public:
	Image()
	{
		for (int i = 0; i < rows; i++) {
			vector<int> temp;
			for (int j = 0; j < cols; j++)
				temp.push_back(rand() % 16);
			array.push_back(temp);
		}
	}

	void func(int start, int end) {
		for (int start = 0; start < end; start++) {
			for (int i = rows * start / end;
					i < rows * (start + 1) / end;
					i++) {
				for (int j = 0; j < cols; j++) {
					switch (array[i][j]) {
					case 0:
						SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | 0));
						Ox[0]++;
						break;
					case 1:
						SetConsoleTextAttribute(hConsole, (WORD)((Blue << 4) | 0));
						Ox[1]++;
						break;
					case 2:
						SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | 0));
						Ox[2]++;
						break;
					case 3:
						SetConsoleTextAttribute(hConsole, (WORD)((Cyan << 4) | 0));
						Ox[3]++;
						break;
					case 4:
						SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | 0));
						Ox[4]++;
						break;
					case 5:
						SetConsoleTextAttribute(hConsole, (WORD)((Magenta << 4) | 0));
						Ox[5]++;
						break;
					case 6:
						SetConsoleTextAttribute(hConsole, (WORD)((Brown << 4) | 0));
						Ox[6]++;
						break;
					case 7:
						SetConsoleTextAttribute(hConsole, (WORD)((LightGray << 4) | 0));
						Ox[7]++;
						break;
					case 8:
						SetConsoleTextAttribute(hConsole, (WORD)((DarkGray << 4) | 0));
						Ox[8]++;
						break;
					case 9:
						SetConsoleTextAttribute(hConsole, (WORD)((LightBlue << 4) | 0));
						Ox[9]++;
						break;
					case 10:
						SetConsoleTextAttribute(hConsole, (WORD)((LightGreen << 4) | 0));
						Ox[10]++;
						break;
					case 11:
						SetConsoleTextAttribute(hConsole, (WORD)((LightCyan << 4) | 0));
						Ox[11]++;
						break;
					case 12:
						SetConsoleTextAttribute(hConsole, (WORD)((LightMagenta << 4) | 0));
						Ox[12]++;
						break;
					case 13:
						SetConsoleTextAttribute(hConsole, (WORD)((LightRed << 4) | 0));
						Ox[13]++;
						break;
					case 14:
						SetConsoleTextAttribute(hConsole, (WORD)((Yellow << 4) | 0));
						Ox[14]++;
						break;
					case 15:
						SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | 0));
						Ox[15]++;
						break;
					default:
						cout << "\n!!!\t\t" << array[i][j] << endl;
						break;
					}
				}
			}
		}
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	}

	void show_Ox() {
		cout << "\n\t";
		for (int i = 0; i < 16; i++) {
			cout << Ox[i] << ' ';
			result += Ox[i];
		}
		cout << "\t||\t" << result << endl;
	}

	void show_array() {
		cout << endl;
		for (int i = 0; i < rows; i++) {
			cout << "\t||\t";
			for (int j = 0; j < cols; j++) {
				cout << array[i][j] << ' ';
			}
			cout << "\t||" << endl;
		}
	}
};



int main() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	setlocale(LC_ALL, "Russian");

	std::cout << "\n\n\t\tКоличество ядер: "
		<< sysinfo.dwNumberOfProcessors / 2 << "\n\n" << std::endl;
	int n_threads;
	Timer t;
	Image a;

	// генерация потоков здесь
	n_threads = 2;


	vector<thread>th(n_threads);

	t.reset();
	for (int i = 0; i < n_threads; i++) {
		th[i] = std::thread([&a, &i, &n_threads]() {
			a.func(i, n_threads);
		});
	}
	for (int i = 0; i < n_threads; i++) {
		th[i].join();
	}

	a.show_Ox();

	cout << t.elapsed() << endl;
	
	return 0;
}
