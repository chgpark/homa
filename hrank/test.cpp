#include <bits/stdc++.h>

using namespace std;

int main() {
	vector <string> crossword;
	vector <string> tmp;
	string	s;

	s = "12345";
	crossword.push_back(s);
	crossword.push_back("12424");
	s = crossword.back();
	cout << crossword[0] << endl << s << endl;
//	crossword[0] = "1231234";
//	crossword[1] = "1231234";
	tmp = crossword;
	tmp[0][0] = '5';
	cout << tmp[0] << endl;
	cout << crossword[0] << endl;
}
