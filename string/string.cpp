#include<iostream>

using namespace std;

int slen(char* s) {
	int i = 0;
	while (*s) {
		i++;
		s++;
	}
	return i;
}


bool is_hex_number(char s) {

	if ((s > 'f') || (s < '0') ||
		((s > '9') && (s < 'A')) ||
		((s > 'F') && (s < 'a'))) {
		return false;
	}
	return true;
}


int macCheck(char* s) {
	int i = 0;
	int symbol = 0;
	while (*s) {
		if (is_hex_number(*s)) {
			i++;
		}
		else if (*s == ':' || *s == '-') {
			if (i == 0 || i / 2 - 1 != symbol)
				break;

			++symbol;
		}
		else {
			symbol = -1;
		}
		s++;
	}

	return (i == 12 && (symbol == 5 || symbol == 0));
}

int ipnum(char* s, int begin, int end) {
	int res = 0;
	for (int i = begin; i < end; i++) {
		res = res * 10 + s[i] - '0';
	}
	return res;
}

bool limit255(char* s) {
	int p = 0;
	int p2 = 0;
	int len = slen(s);
	for (int i = 0; i < slen(s); i++) {
		if (s[i] == '.') {
			p = i;
			break;
		}
	}
	int pa1, pa2, pa3, pa4;
	pa1 = ipnum(s, 0, p);
	for (int i = p + 1; i < slen(s); i++) {
		if (s[i] == '.') {
			p2 = i;
			break;
		}
	}
	pa2 = ipnum(s, p + 1, p2);
	for (int i = p2 + 1; i < slen(s); i++) {
		if (s[i] == '.') {
			p = i;
			break;
		}
	}
	pa3 = ipnum(s, p2 + 1, p);
	pa4 = ipnum(s, p + 1, slen(s));
	if ((pa1 >= 0 && pa1 < 256) && (pa2 >= 0 && pa2 < 256) && (pa3 >= 0 && pa3 < 256) && (pa4 > 0 && pa4 < 256)) {
		return true;
	}
	else
		return false;
}

bool pointip(char* s) {
	int count = 0;
	while (*s) {
		if (*s == '.') {
			count++;
		}
		s++;
	}
	if (count == 3) {
		return true;
	}
	else {
		return false;
	}
}

bool ipCheck(char* s) {
	return (pointip(s) && limit255(s));
}

int main()
{
	char* string = new char[255];

	cout << "Enter MAC address: "; cin.getline(string, 255);
	cout << endl << "Checking whether the string is a MAC address. " << endl << (macCheck(string) ? "[+] this is the MAC address" : "[-] it's not a MAC address") << endl << endl;

	cout << "Enter IP address: "; cin.getline(string, 255);
	cout << endl << "Checks if a string is an IP address." << endl << (ipCheck(string) ? "[+] this line is the IP address" : "[-] this line is not an IP address") << endl;


	delete[] string;
}