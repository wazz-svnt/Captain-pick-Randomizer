#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Record {
	std::string date;
	double card = 0;
	double cash = 0;
};

void saveRecord(const Record& record, const std::string& filename) {
	std::ofstream file(filename, std::ios::app);
	if (file.is_open()) {
		file << record.date << " " << record.card << " " << record.cash << std::endl;
		file.close();
	}
	else {
		std::cout << "Не удалось открыть файл для записи." << std::endl;
	}
}

void loadRecords(std::vector<Record>& records, const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		Record temp;
		while (file >> temp.date >> temp.card >> temp.cash) {
			records.push_back(temp);
		}
		file.close();
	}
	else {
		std::cout << "Не удалось открыть файл для чтения." << std::endl;
	}
}

void addNewRecord(std::vector<Record>& records, const std::string& filename) {
	Record newRecord;
	bool validDate = false;
	while (!validDate) {
		std::cout << "Введите дату (ГГГГ-ММ-ДД): ";
		std::cin >> newRecord.date;
		std::string strMonth = newRecord.date.substr(5, 2);
		int month = std::stoi(strMonth);
		if (newRecord.date.length() != 10 || month > 12 || month < 1) {
			std::cout << "\nНеверный формат даты. Пожалуйста, введите дату корректно в формате ГГГГ-ММ-ДД\n" << std::endl;
			continue;
		}

		bool dataExists = false;
		for (const auto& record : records) {
			if (record.date == newRecord.date)
				dataExists = true;
		}
		if (dataExists)
			std::cout << "\n*Данные не были записаны, Так как запись на эту дату уже существует*\n" << std::endl;
		else
			validDate = true;
	}
	std::cout << "Доход с карты: ";
	std::cin >> newRecord.card;
	std::cout << "Наличные: ";
	std::cin >> newRecord.cash;

	records.push_back(newRecord);
	saveRecord(newRecord, filename);
	std::cout << "\n*Данные записаны успешно!*\n";
}

void deleteRecord(std::vector<Record>& records, const std::string& filename) {
	int year, month, day;
	std::cout << "Введите год: ";
	std::cin >> year;
	std::cout << "Введите месяц: ";
	std::cin >> month;
	std::cout << "Введите день: ";
	std::cin >> day;
	std::string target = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" + (day < 10 ? "0" : "") + std::to_string(day);

	bool found = false;
	for (auto it = records.begin(); it != records.end(); ++it) {
		if (it->date == target) {
			found = true;
			records.erase(it);
			break;
		}
	}

	if (found) {
		std::ofstream file(filename, std::ios::trunc);
		if (file.is_open()) {
			for (const auto& record : records) {
				file << record.date << " " << record.card << " " << record.cash << std::endl;
			}
			file.close();
			std::cout << "\n* Запись удалена успешно! *" << std::endl;
		}
		else
			std::cout << "\nНе удалось открыть файл для записи." << std::endl;
	}
	else
		std::cout << "\nЗапись с введенной датой не найдена." << std::endl;
}

void printRecords(const std::vector<Record>& records) {
	double totalCard = 0, totalCash = 0;

	if (records.empty()) {
		std::cout << "Контейнер пуст! Нету данных для вывода" << std::endl;
		return;
	}
	for (const auto& record : records) {
		std::cout << "Дата: " << record.date << ", Карта: " << record.card << ", Наличные: " << record.cash << ", Всего: " << (record.card + record.cash) << std::endl;
		totalCard += record.card;
		totalCash += record.cash;
	}
	std::cout << "Общий доход с карты: " << totalCard << ", с наличных: " << totalCash << ", всего: " << (totalCard + totalCash) << std::endl;
}

void printRecordsByMonth(const std::vector<Record>& records) {
	double totalCard = 0, totalCash = 0;
	int year, month;
	std::cout << "Введите год: ";
	std::cin >> year;
	std::cout << "Введите месяц: ";
	std::cin >> month;
	std::string target = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month);
	bool hasRecords = false;

	for (const auto& record : records) {
		if (record.date.substr(0, 7) == target) {
			hasRecords = true;
			std::cout << "Дата: " << record.date << ", Карта: " << record.card << ", Наличные: " << record.cash << ", Всего: " << (record.card + record.cash) << std::endl;
			totalCard += record.card;
			totalCash += record.cash;
		}
	}
	if (hasRecords)
		std::cout << "Общий доход за " << target << " - С карты: " << totalCard << ", Наличные: " << totalCash << ", Всего: " << (totalCard + totalCash) << std::endl;
	else
		std::cout << "\nВведенна неверная дата, или её не существует" << std::endl;
}

std::string getMonthName(const std::string& date) {
	int month = std::stoi(date.substr(5, 2));
	std::string monthName;
	switch (month) {
	case 1: monthName = "Январь"; break;
	case 2: monthName = "Февраль"; break;
	case 3: monthName = "Март"; break;
	case 4: monthName = "Апрель"; break;
	case 5: monthName = "Май"; break;
	case 6: monthName = "Июнь"; break;
	case 7: monthName = "Июль"; break;
	case 8: monthName = "Август"; break;
	case 9: monthName = "Сентябрь"; break;
	case 10: monthName = "Октябрь"; break;
	case 11: monthName = "Ноябрь"; break;
	case 12: monthName = "Декабрь"; break;
	default: monthName = ""; break;
	}
	return monthName;
}

void duplicateFile(const std::vector<Record>& records, const std::string& desktopPath, const std::string& newFilename) {
	std::string fullPath = desktopPath + "/" + newFilename;
	std::ofstream file(fullPath);
	if (!file.is_open()) {
		std::cout << "Не удалось открыть файл для записи: " << fullPath << std::endl;
		return;
	}
	if (records.empty()) {
		std::cout << "Контейнер пуст! Данные для отчета отсутствуют!" << std::endl;
		return;
	}

	std::string target;
	int year, month;
	int choice;
	double totalCard = 0, totalCash = 0;
	double monthTotalCard = 0, monthTotalCash = 0;
	bool filterByMonth = false, hasRecords = false;
	std::cout << "Выберите вариант записи отчета:" << std::endl;
	std::cout << "1. За все время" << std::endl;
	std::cout << "2. За конкретный месяц" << std::endl;
	std::cin >> choice;
	if (choice > 2 || choice < 1) {
		std::cout << "\nНеобходимо ввести 1 или 2" << std::endl;
		return;
	}

	if (choice == 2) {
		filterByMonth = true;
		std::cout << "\nВведите год: ";
		std::cin >> year;
		std::cout << "Введите месяц: ";
		std::cin >> month;
		target = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month);
	}

	std::string currentMonth = "";
	for (const auto& record : records) {
		if (filterByMonth && record.date.substr(0, 7) != target)
			continue;

		std::string recordMonth = record.date.substr(0, 7);
		if (currentMonth != recordMonth) {
			if (!currentMonth.empty()) {
				file << "Общий доход: " << "С карты: " << monthTotalCard << ", С наличных: " << monthTotalCash << ", Всего: " << (monthTotalCard + monthTotalCash) << std::endl;
				monthTotalCard = 0, monthTotalCash = 0;
			}
			currentMonth = recordMonth;
			std::string monthName = getMonthName(currentMonth);
			file << "\n" << monthName << std::endl;
		}

		hasRecords = true;
		file << "Дата: " << record.date << ", Карта: " << record.card << ", Наличные: " << record.cash << ", Всего: " << (record.card + record.cash) << std::endl;
		totalCard += record.card;
		totalCash += record.cash;
		monthTotalCard += record.card;
		monthTotalCash += record.cash;
	}
	if (!currentMonth.empty())
		file << "Общий доход: " << "С карты: " << monthTotalCard << ", С наличных: " << monthTotalCash << ", Всего: " << (monthTotalCard + monthTotalCash) << std::endl;

	if (hasRecords) {
		if (choice == 1) {
			file << "\nДоход за все время: " << "С карты: " << totalCard << ", С наличных: " << totalCash << ", Всего: " << (totalCard + totalCash) << std::endl;
		}
		std::cout << "\nОтчет успешно сохранен на рабочий стол: " << newFilename << std::endl;
	}
	else
		std::cout << "\nВведенна неверная дата, или она не существует" << std::endl;
}

std::string getDesktopPath() {
	setlocale(LC_ALL, "RU");
	std::string path = getenv("USERPROFILE");
	if (!path.empty()) {
		return path + "\\Desktop";
	}
	else {
		std::cout << "Не удалось определить путь к рабочему столу пользователя." << std::endl;
		return "";
	}
}

void clearContainer(std::vector<Record>& records, const std::string& filename) {
	char choice;
	std::cout << "Вы уверены? Все данные будут безвозвратно удалены! (Y/N): ";
	std::cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		records.clear();
		std::ofstream file(filename, std::ios::trunc);
		if (file.is_open()) {
			file.close();
			std::cout << "\n* Контейнер успешно очищен *" << std::endl;
		}
		else
			std::cout << "\nНе удалось открыть контейнер для очистки" << std::endl;
	}
	else if (choice == 'n' || choice == 'N')
		std::cout << "\n* Операция отменена. *" << std::endl;
	else
		std::cout << "\nНеобходимо ввести значение y или n! \n      * Операция отменена *" << std::endl;
}

int main() {
	setlocale(LC_ALL, "RU");
	std::vector<Record> records;
	std::string filename = "Finance Container.txt";

	loadRecords(records, filename);

	int choice;
	do {
		std::cout << "\n********* | Меню | *********\n"
			<< "\n1. Ввести новую запись\n"
			<< "2. Удалить запись\n"
			<< "3. Показать все записи\n"
			<< "4. Показать записи за месяц\n"
			<< "5. Создать отчет для печати\n"
			<< "6. Очистить контейнер\n\n"
			<< "7. Выход\n\n"
			<< "****************************\n\n"
			<< "Выбор: ";
		std::cin >> choice;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ошибка ввода. Пожалуйста, Введите число\n" << "Выбор: ";
			std::cin >> choice;
		}
		std::cout << "\n";

		switch (choice) {
		case 1:
			addNewRecord(records, filename);
			break;
		case 2:
			deleteRecord(records, filename);
			break;
		case 3:
			printRecords(records);
			break;
		case 4: {
			printRecordsByMonth(records);
			break;
		}
		case 5: {
			std::string desktopPath = getDesktopPath();
			std::string newFilename = "printable_finances.txt";
			duplicateFile(records, desktopPath, newFilename);
			break;
		}
		case 6:
			clearContainer(records, filename);
			break;
		case 7:
			std::cout << "Выход из программы." << std::endl;
			break;
		default:
			std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
		}
	} while (choice != 7);

	return 0;
}
