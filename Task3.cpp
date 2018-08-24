#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <iostream> // DEBUG

using namespace std;

// входной поток данных
ifstream in("inFile.txt");

// выходной поток данных
ofstream out("outFile.txt");

// мьютекс, неоходимый для синхронизации потоков
std::mutex threadLock;

// функция главного потока
void inputThreadFunction(queue<string>&, vector<vector<string>>&);

// функция побочного потока
void outputThreadFunction(vector<vector<string>>&);

// функция, разделяющая строку на вектор слов по входному символу
vector<string> split(string str, string token);

int main() {
	setlocale(LC_ALL, "rus");

	// дверовидная структура, воплощенная в контейнере vector
	vector<vector<string>> dataBase;	// в качестве древовидной структуры был использован
										// динамический двумерный массив, т.к. по заданию было
										// непонятно, каким именно образом помещать данные в n-арное дерево
	// здесь 1 уровень вектора - начальство (директора)
	// 2 уровень вектора - менеджеры
	// 3 уровень вектора - рабочие

	// очередь входных данных
	queue<string> inputData;

	// главный поток
	thread inputThread(inputThreadFunction, ref(inputData), ref(dataBase));
	inputThread.join();

	// побочный поток
	thread outputThread(outputThreadFunction , ref(dataBase));
	outputThread.join();

	out.close();
	return 0;
}

void inputThreadFunction(queue<string> &inputData, vector<vector<string>> &dataBase) {
	threadLock.lock();

	// буфер для считывания данных в очередь
	string tempStr;

	// считывание данных из входного файла в очередь
	while (getline(in, tempStr)) {
		inputData.push(tempStr);
	}

	// помещение данных в структуру
	for (int i = 0; i < 3; i++) {	// выделение памяти для "уровней" структуры
		dataBase.push_back(vector<string>());
	}
	while (!inputData.empty()) {
		if ((split(inputData.front(), ",")[1] == "директор") || (split(inputData.front(), ",")[1] == "Директор")) {
			dataBase[0].push_back(split(inputData.front(), ",")[0] + "," + split(inputData.front(), ",")[2]);
			inputData.pop();
		}
		else if ((split(inputData.front(), ",")[1] == "менеджер") || (split(inputData.front(), ",")[1] == "Менеджер")) {
			dataBase[1].push_back(split(inputData.front(), ",")[0] + "," + split(inputData.front(), ",")[2]);
			inputData.pop();
		}
		else if ((split(inputData.front(), ",")[1] == "рядовой работник") || (split(inputData.front(), ",")[1] == "Рядовой работник")) {
			dataBase[2].push_back(split(inputData.front(), ",")[0] + "," + split(inputData.front(), ",")[2]);
			inputData.pop();
		}
		else {
			inputData.pop();	// если строка не содержит нужной информации, также извлекаем её из стека
		}
	}

	threadLock.unlock();
}

void outputThreadFunction(vector<vector<string>>& dataBase) {
	threadLock.lock();
	for (int i = 0; i < 3; i++) {
		for (auto current : dataBase[i]) {
			if (i == 0) {
				out << current + "," + "директор" << endl;
			}
			else if (i == 1) {
				out << current + "," + "менеджер" << endl;
			}
			else if (i == 2) {
				out << current + "," + "рядовой работник" << endl;
			}
		}
	}
	threadLock.unlock();
}

vector<string> split(string str, string token) {
	vector<string> result;
	while (str.size()) {
		int index = str.find(token);
		if (index != string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0) { 
				result.push_back(str); 
			}
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}
