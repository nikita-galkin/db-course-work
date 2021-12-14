#include "Menu.h"

bool UpdateMenu(std::string ID, std::string TableName)
{
	system("cls");
	DB::PrintAnswer(DB::sendReq("SELECT * FROM " + TableName + " WHERE `Регистрационный номер`=" + ID));
	std::cout << "Введите название столбца для изменния\n";
	std::string column = Getline();
	std::cout << "Введите новое значение поля:\n";
	if (DB::GetColumnType(TableName, column) == "int")
		DB::sendReq("UPDATE `" + TableName + "` SET `" + column + "`=" + Getline() + " WHERE `Регистрационный номер`=" + ID);
	else DB::sendReq("UPDATE `" + TableName + "` SET `" + column + "`='" + Getline() + "' WHERE `Регистрационный номер`=" + ID);
	return EXIT;
}
bool MenuCountIncidentsPerTime()
{
	system("cls");
	std::cout << 
"1)Рассчитать данные о количестве происшествий в указанный промежуток времени; \n\
Введите временные промежутки\n\
(Формат ввода временных промежутков через Enter YYYY-MM-DD HH:MM:SS)\n";
	std::string first = Getline(), second = Getline();
	MYSQL_RES* res = DB::sendReq("SELECT COUNT(*) FROM происшествие WHERE `Дата регистрации` BETWEEN STR_TO_DATE('" + first + "', '%Y-%m-%d %H:%i:%s') AND STR_TO_DATE('" + second + "', '%Y-%m-%d %H:%i:%s')");
	DB::PrintAnswer(res);
	return EXIT;
}
bool MenuCountIncidentsForMan()
{
	system("cls");
	std::cout << "2)Для указанного лица получить количество происшествий;\n";
	DB::PrintAnswer(DB::sendReq("SELECT ФИО FROM лица"));
	std::cout << "Введите ФИО, для которого желаете получить количество происшествий, и нажмите Enter:\n";
	MYSQL_RES* res = DB::sendReq(
"SELECT COUNT(Происшествие) FROM участники WHERE участники.Лицо = (\
SELECT `Регистрационный номер` FROM лица WHERE ФИО = '" + Getline() + "')");
	DB::PrintAnswer(res);
	return EXIT;
}
bool MenuInsertUpdateIncidents()
{
	system("cls");
	std::cout << "3)Добавить/изменить информацию о происшествиях;\n\
Существующие записи таблицы \"происшествие\":\n";
	DB::PrintAnswer(DB::sendReq("SELECT * FROM происшествие"));
	std::cout <<
"0 - Выйти\n\
1 - Добавить\n\
2 - Обновить\n\
Введите необходимое Вам значение: ";
	switch (GetKey())
	{
	case 0: return EXIT;
	case 1:
	{
		std::cout << "Введите через Enter:\n\
время регистрации происшествия (в формате YYYY-MM-DD HH:MM:SS),\n\
тип происшествия\n\
решение (число: 1-отказано в возбуждении дела; 2-удовлетворено ходатайство о возбуждении уголовного дела;\n\
3-отправлено по территориальному признаку)\n";
		DB::sendReq("INSERT INTO происшествие (`Решение`, `Тип происшествия`, `Дата регистрации`) VALUES (" + Getline() + ", '" + Getline() + "', '" + Getline() + "')");
	}
	break;
	case 2:
	{
		std::cout << "Введите Регистрационный номер происшествия для изменения\n";
		while(!UpdateMenu(Getline(), "происшествие"));
	}
	break;
	default: std::cout << "Ошибка ввода\n"; break;
	}
	return CONTINUE;
}
bool MenuInsertUpdateMen()
{
	system("cls");
	std::cout << "4) Добавить/изменить информацию о лицах, участвующих в происшествиях;\n\
Существующие записи таблицы \"лица\":\n";
	DB::PrintAnswer(DB::sendReq("SELECT * FROM лица"));
	std::cout <<
"0 - Выйти\n\
1 - Добавить\n\
2 - Обновить\n\
Введите необходимое Вам значение: ";
	switch (GetKey())
	{
	case 0: return EXIT;
	case 1: {
		std::cout << 
"Введите через Enter: \n\
ФИО (формат записи: Фамилия Имя Отчество)\n\
количество судимостей (натуральное число или 0)\n\
адрес (формат записи: Улица, число-номер дома)\n";
		DB::sendReq("INSERT INTO лица (`Адрес`, `Судимости`, `ФИО`) VALUES ('" + Getline() + "', " + Getline() + ", '" + Getline() + "')");
	} break;
	case 2:
	{
		std::cout << "Введите Регистрационный номер лица для изменения\n";
		while (!UpdateMenu(Getline(), "лица"));
	} break;
	default: std::cout << "Ошибка ввода\n"; break;
	}
	return CONTINUE;
}
bool MenuProtocolOfIncident()
{
	system("cls");
	std::cout << "5)Получить протокол происшествия;\n";
	DB::PrintAnswer(DB::sendReq("SELECT `Регистрационный номер`,`Тип происшествия` FROM происшествие"));
	std::cout << "Введите Регистрационный номер происшествия, для которого вы хотите получить протокол и нажмите Enter:\n";
	MYSQL_RES* res = DB::sendReq(
"SELECT `Тип происшествия`, решения.Решение, лица.ФИО, лица.Адрес, лица.Судимости \
FROM происшествие JOIN решения ON происшествие.Решение=решения.ID JOIN участники ON участники.Происшествие=происшествие.`Регистрационный номер` JOIN лица ON лица.`Регистрационный номер`=участники.Лицо \
WHERE происшествие.`Регистрационный номер`='" + Getline()+ "'");
	DB::PrintAnswer(res);
	return EXIT;
}
bool Menu()
{
	std::cout <<
"Введите действие, которое хотите сделать с базой данных, после чего нажмите Enter:\n\
0)Выход из программы;\n\
1)Рассчитать данные о количестве происшествий в указанный промежуток времени;\n\
2)Для указанного лица получить количество происшествий;\n\
3)Добавить/изменить информацию о происшествиях;\n\
4)Добавить/изменить информацию о лицах, участвующих в происшествиях;\n\
5)Получить протокол происшествия;\n";
	switch (GetKey()) {
	case 0: return EXIT;
	case 1: while(!MenuCountIncidentsPerTime()); break;
	case 2: while(!MenuCountIncidentsForMan()); break;
	case 3: while(!MenuInsertUpdateIncidents()); break;
	case 4: while (!MenuInsertUpdateMen()); break;
	case 5: while (!MenuProtocolOfIncident()); break;
	default: std::cout << "Нет такого пункта в меню!\n"; break;
	}
	system("pause&&cls");
	return false;
}
int GetKey()
{
	int key = 0;
	std::cin >> key;
	std::cin.ignore();
	return key;
}
std::string Getline()
{
	std::string str;
	std::getline(std::cin, str);
	return str;
}