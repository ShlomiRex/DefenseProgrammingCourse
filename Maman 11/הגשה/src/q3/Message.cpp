#include "Message.h"

Message::Message(std::string msg) {
	this->text = msg;
}

std::string Message::getText() const {
	return this->text;
}

Message::~Message() {
	//this->text is on stack
}