#pragma once
#include <windows.h>
#include "database.h"
#define ERR(msg) { throw new std::exception(msg); }
#define EXIT true
#define CONTINUE false
/// <summary>
/// Чтение числа из косноли с обработкой некорректного ввода
/// </summary>
/// <returns>Число</returns>
int GetKey();
std::string Getline();
/// <summary>
/// Вызывает меню для изменения значений строки с Регистрационным номером ID
/// </summary>
bool UpdateMenu(std::string ID, std::string TableName);
///1)Рассчитать данные о количестве происшествий в указанный промежуток времени;
bool MenuCountIncidentsPerTime();
///2)Для указанного лица получить количество происшествий;
bool MenuCountIncidentsForMan();
///3)Добавить/изменить информацию о происшествиях;
bool MenuInsertUpdateIncidents();
///4)Добавить/изменить информацию о лицах, участвующих в происшествиях;
bool MenuInsertUpdateMen();
///5)Получить протокол происшествия;
bool MenuProtocolOfIncident();

bool Menu();