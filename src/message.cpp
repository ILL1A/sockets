#include <iostream>
#include "include/message.h"

using namespace std;
using namespace http_request;

namespace http_request {
	Message::Message(int message_length, string sender_host, int sender_port, string message) : 
		message_length_(message_length), sender_host_(sender_host), sender_port_(sender_port), message_(message) {}
}