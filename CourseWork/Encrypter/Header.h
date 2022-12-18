#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

class Common
{
public:
	int ascii = 0, offset = 0, n = 0, steps = 0, pos1 = 0, pos2 = 0;
	string username, password, line, user_pass_str, encryp_pass_str;;
	fstream encryption;
	int user_pass_arr [500];

public:
	void clrscr() {
		system("cls");
	}
};
