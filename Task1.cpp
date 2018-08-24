#include <iostream>
//#include <fstream>	//DEBUG оставил специально для удобной проверки:)

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	//ifstream in("inFile.txt");	//DEBUG

	// натуральное число n
	int n;

	// подсчет строк, содержащих монотонные последовательности
	int count_lines = 0;

	//in >> n;	//DEBUG
	cout << "Введите натуральное число n: ";
	cin >> n;
	
	// целочисленный квадратный массив размера n*n
	int **myArr = new int*[n];

	// выделение памяти для n строк динамического массива
	for (int i = 0; i < n; i++) {
		myArr[i] = new int[n];	 // здесь n - длина ряда
	}

	cout << endl << "Введите массив:" << endl;
	for (int count_row = 0; count_row < n; count_row++) {
		for (int count_column = 0; count_column < n; count_column++) {
			//in >> myArr[count_row][count_column];	// DEBUG
			cin >> myArr[count_row][count_column];
		}
	}

	// текущий элемент в ряду
	int current;

	// логический флаг для подсчета
	bool bool_flag = true;

	// флаг, нужный для правильного вывода строки, состоящей и одинаковых чисел
	bool repeat_flag = true;

	// цикл подсчета количества "монотонных" строк для корректного выделения памяти для динамического массива
	for (int count_row = 0; count_row < n; count_row++) {
		current = myArr[count_row][0];
		repeat_flag = false;	// в начале ряда флаг повторения - false

		for (int count_column = 1; count_column < n; count_column++) {	// цикл для проверки на неубывание
			if (myArr[count_row][count_column] >= current) {
				current = myArr[count_row][count_column];
				bool_flag = true;
			}
			else {
				bool_flag = false;
				break;
			}
		}
		if (bool_flag) {
			count_lines++;
			repeat_flag = true;
		}

		current = myArr[count_row][0];

		for (int count_column = 1; count_column < n; count_column++) {	// цикл для проверки на невозрастание
			if (myArr[count_row][count_column] <= current) {
				current = myArr[count_row][count_column];
				bool_flag = true;
			}
			else {
				bool_flag = false;
				break;
			}
		}

		if (bool_flag && !(repeat_flag)) count_lines++;	// если флаг повторения == false, то увеличить счетчик монотонных строк
	}

	int **outArr = new int*[count_lines];

	// обнуление счетчика "монотонных" строк
	count_lines = 0;

	// временный одномерный массив для хранения текущего ряда
	int *tempArr = new int[n];

	// цикл для вставки "монотонных строк" в выходной массив
	for (int count_row = 0; count_row < n; count_row++) {
		repeat_flag = false;	// в начале ряда флаг повторения - false
		current = myArr[count_row][0];

		for (int count_column = 0; count_column < n; count_column++) {		// цикл для вывода неубывающего ряда
			if (myArr[count_row][count_column] >= current) {
				current = myArr[count_row][count_column];
				tempArr[count_column] = myArr[count_row][count_column];
				bool_flag = true;
			}
			else {
				bool_flag = false;
				break;
			}
		}

		if (bool_flag) {
			count_lines++;
			repeat_flag = true;
			outArr[count_lines - 1] = new int[n];
			for (int i = 0; i < n; i++) {
				outArr[count_lines - 1][i] = tempArr[i];
			}
		}

		current = myArr[count_row][0];

		for (int count_column = 0; count_column < n; count_column++) {		// цикл для вывода невозрастающего ряда
			if (myArr[count_row][count_column] <= current) {
				current = myArr[count_row][count_column];
				tempArr[count_column] = myArr[count_row][count_column];
				bool_flag = true;
			}
			else {
				bool_flag = false;
				break;
			}
		}

		if (bool_flag && !(repeat_flag)) {
			count_lines++;
			outArr[count_lines - 1] = new int[n];
			for (int i = 0; i < n; i++) {
				outArr[count_lines - 1][i] = tempArr[i]; // запись текущего монотонного ряда в выходной массив
			}
		}

	}

	
	cout << endl;
	cout << "Результирующий массив:" << endl;
	for (int count_row = 0; count_row < count_lines; count_row++) {		// DEBUG
		for (int count_column = 0; count_column < n; count_column++) {
			cout << outArr[count_row][count_column] << " ";
		}
		cout << endl;
	}
	

	// освобождение памяти 
	delete[] tempArr;
	for (int i = 0; i < n; i++) {
		delete[] myArr[i];
	}
	for (int i = 0; i < count_lines; i++) {
		delete[] outArr[i];
	}
}
