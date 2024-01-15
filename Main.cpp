#include <iostream>
#include <fstream>
#include <string>

bool file_insert(std::string path, int pos, std::string str);

int main() {
	setlocale(LC_ALL, "ru");

	const std::string path = "file.txt";


	// Класс fstream для чтения и записи
	
	std::fstream fs;

	fs.open(path,std::ios::in | std::ios::app); // открытие файла в нескольких режимах с помощью перегрузки операции битового ИЛИ

	if (fs.is_open()) {
		std::cout << "File open!\n";
		
		//ввод данных в файл
		
		std::cout << "Enter string -> ";
		std::string str;
		std::getline(std::cin, str);
		fs << str << '\n';
		
		// seekp - seek put pointer = (переместить курсор записи)
		// seekg - seek get pointer = (переместить курсор считывания)
		fs.seekg(0, std::ios::beg); // перемещение курсора считывания в начало файла

		// tellg - аналогично, но для получения положения курсора
		// tellp
				 
		
		// чтение данных из файла
		std::cout << "File contents:\n";
		char sym;
		while (fs.get(sym))
			std::cout << sym;
		std::cout << std::endl;
	}
	else {
		std::cout << "Error open!\n";
	}
	fs.close();
	


	// Задача 1
	
	if (file_insert(path, 3, "%%%"))
		std::cout << "Строка вставлена успешно.\n\n";
	else
		std::cout << "Ошибка выполнения функции!\n\n";
	

	//Задача 2. Парсинг даты из файла
	std::cout << "Задача 1.\nДата: ";
	std::ifstream in;
	in.open("date.txt");
	if (in.is_open()) {
		std::string date;
		in >> date;
		std::cout << date << std::endl;

		int day = std::stoi(date);
		int month = std::stoi(date.substr(date.find('.') + 1));
		int year = std::stoi(date.substr(date.rfind('.') + 1));

		std::cout << "День: " << day << std::endl;
		std::cout << "Месяц: " << month << std::endl;
		std::cout << "Год: " << year << std::endl;
	}
	in.close();






	return 0;
}

bool file_insert(std::string path, int pos, std::string str) {
	static std::fstream fs;  // объект класса fstream в статической области видимости
	fs.open(path,std::ios::in); // открываем файл в режиме чтения

	if (!fs.is_open()) // проверка на открытия
		return false;
	
	std::string file,line;  //создаем строку для содержимого файла и строку для построчного считывания
	while (std::getline(fs, line))
		file += line + '\n';
	fs.close();   // закрываем

	file.insert(pos, str);  // вставляем на позицию нужную строку
	
	fs.open(path, std::ios::out); // открывает в режиме out
	if (!fs.is_open()) // проверяем на открытия
		return false;
	fs << file; // вставляем новую строку в файл
	fs.close(); // закрываем
	return true;// выполнено!

}