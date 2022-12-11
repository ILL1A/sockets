#include <iostream>
#include <string>
#include "include/validator.h"

using namespace std;

Address::Address(string host, int port) : host_(host), port_(port) {}

void raise_error() {
	cout << "host and/or port is invalid\n";
	exit(0);
}

Address* get_address(string argv) {
	string host = "";
	string s_port = "";
	bool is_host = true;
	for (int i = 0; i < argv.size(); i ++) {
		if (argv[i] == ':' && !is_host) raise_error();
		if (argv[i] == ':') {
			is_host = false;
			continue;
		}
		if (is_host) {
			if ((argv[i] < '0' || argv[i] > '9') && argv[i] != '.') raise_error();
			host += argv[i];
		} else {
			if (argv[i] < '0' || argv[i] > '9') raise_error();
			s_port += argv[i];
		}
	}
	if (s_port.size() > 4 || host.size() < 7) raise_error();
	int port = atoi(s_port.c_str());
	return new Address(host, port);
}