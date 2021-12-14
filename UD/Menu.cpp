#include "Menu.h"

bool UpdateMenu(std::string ID, std::string TableName)
{
	system("cls");
	DB::PrintAnswer(DB::sendReq("SELECT * FROM " + TableName + " WHERE `��������������� �����`=" + ID));
	std::cout << "������� �������� ������� ��� ��������\n";
	std::string column = Getline();
	std::cout << "������� ����� �������� ����:\n";
	if (DB::GetColumnType(TableName, column) == "int")
		DB::sendReq("UPDATE `" + TableName + "` SET `" + column + "`=" + Getline() + " WHERE `��������������� �����`=" + ID);
	else DB::sendReq("UPDATE `" + TableName + "` SET `" + column + "`='" + Getline() + "' WHERE `��������������� �����`=" + ID);
	return EXIT;
}
bool MenuCountIncidentsPerTime()
{
	system("cls");
	std::cout << 
"1)���������� ������ � ���������� ������������ � ��������� ���������� �������; \n\
������� ��������� ����������\n\
(������ ����� ��������� ����������� ����� Enter YYYY-MM-DD HH:MM:SS)\n";
	std::string first = Getline(), second = Getline();
	MYSQL_RES* res = DB::sendReq("SELECT COUNT(*) FROM ������������ WHERE `���� �����������` BETWEEN STR_TO_DATE('" + first + "', '%Y-%m-%d %H:%i:%s') AND STR_TO_DATE('" + second + "', '%Y-%m-%d %H:%i:%s')");
	DB::PrintAnswer(res);
	return EXIT;
}
bool MenuCountIncidentsForMan()
{
	system("cls");
	std::cout << "2)��� ���������� ���� �������� ���������� ������������;\n";
	DB::PrintAnswer(DB::sendReq("SELECT ��� FROM ����"));
	std::cout << "������� ���, ��� �������� ������� �������� ���������� ������������, � ������� Enter:\n";
	MYSQL_RES* res = DB::sendReq(
"SELECT COUNT(������������) FROM ��������� WHERE ���������.���� = (\
SELECT `��������������� �����` FROM ���� WHERE ��� = '" + Getline() + "')");
	DB::PrintAnswer(res);
	return EXIT;
}
bool MenuInsertUpdateIncidents()
{
	system("cls");
	std::cout << "3)��������/�������� ���������� � �������������;\n\
������������ ������ ������� \"������������\":\n";
	DB::PrintAnswer(DB::sendReq("SELECT * FROM ������������"));
	std::cout <<
"0 - �����\n\
1 - ��������\n\
2 - ��������\n\
������� ����������� ��� ��������: ";
	switch (GetKey())
	{
	case 0: return EXIT;
	case 1:
	{
		std::cout << "������� ����� Enter:\n\
����� ����������� ������������ (� ������� YYYY-MM-DD HH:MM:SS),\n\
��� ������������\n\
������� (�����: 1-�������� � ����������� ����; 2-������������� ����������� � ����������� ���������� ����;\n\
3-���������� �� ���������������� ��������)\n";
		DB::sendReq("INSERT INTO ������������ (`�������`, `��� ������������`, `���� �����������`) VALUES (" + Getline() + ", '" + Getline() + "', '" + Getline() + "')");
	}
	break;
	case 2:
	{
		std::cout << "������� ��������������� ����� ������������ ��� ���������\n";
		while(!UpdateMenu(Getline(), "������������"));
	}
	break;
	default: std::cout << "������ �����\n"; break;
	}
	return CONTINUE;
}
bool MenuInsertUpdateMen()
{
	system("cls");
	std::cout << "4) ��������/�������� ���������� � �����, ����������� � �������������;\n\
������������ ������ ������� \"����\":\n";
	DB::PrintAnswer(DB::sendReq("SELECT * FROM ����"));
	std::cout <<
"0 - �����\n\
1 - ��������\n\
2 - ��������\n\
������� ����������� ��� ��������: ";
	switch (GetKey())
	{
	case 0: return EXIT;
	case 1: {
		std::cout << 
"������� ����� Enter: \n\
��� (������ ������: ������� ��� ��������)\n\
���������� ���������� (����������� ����� ��� 0)\n\
����� (������ ������: �����, �����-����� ����)\n";
		DB::sendReq("INSERT INTO ���� (`�����`, `���������`, `���`) VALUES ('" + Getline() + "', " + Getline() + ", '" + Getline() + "')");
	} break;
	case 2:
	{
		std::cout << "������� ��������������� ����� ���� ��� ���������\n";
		while (!UpdateMenu(Getline(), "����"));
	} break;
	default: std::cout << "������ �����\n"; break;
	}
	return CONTINUE;
}
bool MenuProtocolOfIncident()
{
	system("cls");
	std::cout << "5)�������� �������� ������������;\n";
	DB::PrintAnswer(DB::sendReq("SELECT `��������������� �����`,`��� ������������` FROM ������������"));
	std::cout << "������� ��������������� ����� ������������, ��� �������� �� ������ �������� �������� � ������� Enter:\n";
	MYSQL_RES* res = DB::sendReq(
"SELECT `��� ������������`, �������.�������, ����.���, ����.�����, ����.��������� \
FROM ������������ JOIN ������� ON ������������.�������=�������.ID JOIN ��������� ON ���������.������������=������������.`��������������� �����` JOIN ���� ON ����.`��������������� �����`=���������.���� \
WHERE ������������.`��������������� �����`='" + Getline()+ "'");
	DB::PrintAnswer(res);
	return EXIT;
}
bool Menu()
{
	std::cout <<
"������� ��������, ������� ������ ������� � ����� ������, ����� ���� ������� Enter:\n\
0)����� �� ���������;\n\
1)���������� ������ � ���������� ������������ � ��������� ���������� �������;\n\
2)��� ���������� ���� �������� ���������� ������������;\n\
3)��������/�������� ���������� � �������������;\n\
4)��������/�������� ���������� � �����, ����������� � �������������;\n\
5)�������� �������� ������������;\n";
	switch (GetKey()) {
	case 0: return EXIT;
	case 1: while(!MenuCountIncidentsPerTime()); break;
	case 2: while(!MenuCountIncidentsForMan()); break;
	case 3: while(!MenuInsertUpdateIncidents()); break;
	case 4: while (!MenuInsertUpdateMen()); break;
	case 5: while (!MenuProtocolOfIncident()); break;
	default: std::cout << "��� ������ ������ � ����!\n"; break;
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