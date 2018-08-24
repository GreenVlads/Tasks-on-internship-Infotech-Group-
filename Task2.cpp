#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// возвращает длину наибольшей подстроки в строке, не содержащей цифры
int countSubStr(string);

// возвращает развернутую подстроку в найденной строке
string transformStr(string);

// возвращает перевернутую строку
string invertStr(string);

int main() {
	setlocale(LC_ALL, "Russian");

	// количество элементов в строковом массиве
	int size;
	
	cout << "Введите количество элементов в строковом массиве: ";
	cin >> size;

	// создание динамического массива
	string *myArr = new string[size];
	for (int i = 0; i < size; i++) {
		cin >> myArr[i];
	}
	
	// строка с самой длинной нужной подстрокой
	string res_string;

	// поиск строки res_string
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (countSubStr(myArr[i]) > max) {
			max = countSubStr(myArr[i]);
			res_string = myArr[i];
		}
	}

	res_string = transformStr(res_string);

	cout << "Результирующая строка: ";
	// создание цикла связано с непонятным мне выделением памяти на char*, в переменной res_string остается "хвостик с краказяброй"
	int count_max = 0;
	for (auto current : res_string) {
		if (((current >= 'a') && (current <= 'z')) || ((current >= 'A') && (current <= 'Z'))) { 
			cout << current;
			count_max++;
		}
		if (count_max >= max) break;
	}
	cout << endl;

	// освобождение памяти
	delete[] myArr;
}

int countSubStr(string mystring) {
	// длина наибольшей подстроки
	int maxlenght = 0;
	
	// длина текущей подстроки
	int currentlenght = 0;

	for (int i = 0; i < strlen(mystring.c_str()); i++) {
		if (isdigit(mystring[i]) == 0) {
			currentlenght++;
		}
		else {
			if (currentlenght > maxlenght) {
				maxlenght = currentlenght;
			}
			currentlenght = 0;
		}
		if (i == strlen(mystring.c_str()) - 1) {
			if (currentlenght > maxlenght) {
				maxlenght = currentlenght;
			}
			currentlenght = 0;
		}
	}

	return maxlenght;
}

string invertStr(string mystring) {
	int tempVar = strlen(mystring.c_str());
	char *charArr = new char[strlen(mystring.c_str())];
	for (int i = 0; i < strlen(mystring.c_str()); i++, tempVar--) {
		charArr[i] = mystring[tempVar - 1];
	}
	return string(charArr);
}

string transformStr(string mystring) {
	// длина наибольшей подстроки
	int maxlenght = 0;

	// длина текущей подстроки
	int currentlenght = 0;

	// индекс начала наибольшей подстроки
	int beginIndex = 0;

	for (int i = 0; i < strlen(mystring.c_str()); i++) {
		if (isdigit(mystring[i]) == 0) {
			currentlenght++;
		}
		else {
			if (currentlenght > maxlenght) {
				maxlenght = currentlenght;
				beginIndex = i - (maxlenght - 1);
			}
			currentlenght = 0;
		}
		if (i == strlen(mystring.c_str()) - 1) {
			if (currentlenght > maxlenght) {
				maxlenght = currentlenght;
				beginIndex = i - (maxlenght - 1);
			}
			currentlenght = 0;
		}
	}

	return invertStr(mystring.substr(beginIndex - 1, maxlenght));
}
