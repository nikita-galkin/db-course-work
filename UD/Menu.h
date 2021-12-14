#pragma once
#include <windows.h>
#include "database.h"
#define ERR(msg) { throw new std::exception(msg); }
#define EXIT true
#define CONTINUE false
/// <summary>
/// ������ ����� �� ������� � ���������� ������������� �����
/// </summary>
/// <returns>�����</returns>
int GetKey();
std::string Getline();
/// <summary>
/// �������� ���� ��� ��������� �������� ������ � ��������������� ������� ID
/// </summary>
bool UpdateMenu(std::string ID, std::string TableName);
///1)���������� ������ � ���������� ������������ � ��������� ���������� �������;
bool MenuCountIncidentsPerTime();
///2)��� ���������� ���� �������� ���������� ������������;
bool MenuCountIncidentsForMan();
///3)��������/�������� ���������� � �������������;
bool MenuInsertUpdateIncidents();
///4)��������/�������� ���������� � �����, ����������� � �������������;
bool MenuInsertUpdateMen();
///5)�������� �������� ������������;
bool MenuProtocolOfIncident();

bool Menu();