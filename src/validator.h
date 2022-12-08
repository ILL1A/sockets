#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_ 1
#include <iostream>
#include <string>

using namespace std;

struct Address{
	Address(string host, int port);
	string host_;
	int port_;
};

void raise_error();

Address* get_address(string argv);

#endif // _VALIDATOR_H_