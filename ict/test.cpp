#include <string.h>
#include <iostream>

using namespace std;

int		main(int ac, char **av)
{
	string		str;
	string		str_a;

	str = av[1];
	str_a = str.c_str();
	cout << str_a << endl;
	return 0;
}
