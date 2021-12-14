#include "Menu.h"
using namespace std;
int main()
{
	system("chcp 1251&&cls");
	DB::start();
	while (1)
	{
		try
		{
			if (Menu()) break;
		}
		catch (const std::exception& e)
		{
			cout << "Îøèáêà: " << e.what() << endl;
			system("pause");
		}
	}
	DB::stop();
	return 0;
}