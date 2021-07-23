#include "USocial.h"

/**
* Return some ID number that has never been returned before.
*/
unsigned long registerId() {
	static unsigned long id_accumulator = 0;
	return ++id_accumulator;
}

USocial::USocial() {
	//On stack. It's ok, destructor handles destruction of the elements of the map from the heap.
	this->users = std::map<unsigned long, User*>();
}

User* USocial::registerUser(std::string name, bool buisnessUser) {

	//Check if user with the same name is already registered
	for (auto const& x : this->users) {
		if (x.second->name == name) {
			std::stringstream ss;
			ss << "User with the name (\"" << name << "\") is already registered.";
			throw std::exception(ss.str().c_str());
		}
	}

	User* user;
	if (buisnessUser) {
		std::cout << "Registering user " << name << "(buisness user)" << std::endl;
		user = new BuisnessUser();
	}
	else {
		std::cout << "Registering user " << name << "(regular user)" << std::endl;
		user = new User();
	}
	user->id = registerId();
	user->name = name;
	user->us = this;
	std::cout << "\t" << "Registered: " << *user << std::endl;
	
	this->users[user->id] = user;

	return user;
}

void USocial::removeUser(User* userToRemove) {
	std::cout << "Removing user: " << *userToRemove << std::endl;
	this->users.erase(userToRemove->id);
	delete userToRemove;
}

USocial::~USocial()
{
	std::cout << "USocial deconstructor called" << std::endl;

	std::cout << "\tRemoving users from the heap" << std::endl;
	for (auto x : this->users) {
		User* user = x.second;
		delete user;
	}
	//Empty list. End of function which means list is destructed because its on the stack of the class.
	this->users.clear();
}

User* USocial::getUserById(unsigned long id) {
	User* user = this->users[id];
	if (user == nullptr)
		std::cerr << "Didn't find user with the id: " << id << ". Returning nullptr." << std::endl;
	return user;
}







User::User() {
	this->id = -1;
	this->name = "";
}

User::~User() {

	std::cout << "\t\t" << *this << " destructor called" << std::endl;

	std::cout << "\t\t\tRemoving posts" << std::endl;
	while (!this->posts.empty()) {
		delete this->posts.back();
		this->posts.pop_back();
	}

	std::cout << "\t\t\tRemoving received messages" << std::endl;
	while (!this->receivedMsgs.empty()) {
		delete this->receivedMsgs.back();
		this->receivedMsgs.pop_back();
	}

	this->posts.clear();
	this->receivedMsgs.clear();
}

void User::post(std::string what) {
	this->post(what, nullptr);
}

void User::post(std::string what, Media* media) {
	//If media is nullptr then it's fine. Constructor is fine.
	Post* post = new Post(what, media);
	this->posts.push_back(post);

	std::cout << *this << " is posting:" << std::endl;
	std::cout << "\t" << *post << std::endl;
}

unsigned long User::getId() const {
	return this->id;
}

std::string User::getName() const {
	return this->name;
}

void User::addFriend(User* my_friend) {
	if (my_friend) {
		std::cout << *this << " is adding friend: " << *my_friend << std::endl;
	}
	else {
		throw std::exception("Can't add null friend");
	}
	//Check if exists
	for (auto x : this->friends) {
		if (x == my_friend->id) {
			std::stringstream ss;
			ss << "Can't add friend " << (*my_friend) << " because hes already in my friend list." << std::endl;
			std::string msg = ss.str();
			throw std::exception(msg.c_str());
		}
	}
	this->friends.push_back(my_friend->id);
}

void User::removeFriend(User* which)
{
	this->friends.remove(which->id);
}

std::list<Post*> User::getPosts() const {
	return this->posts;
}

void User::viewFriendsPosts() const {
	std::cout << *this << " is viewing friend's posts" << std::endl;
	for (auto x : this->friends) {
		User* my_friend = this->us->users[x];
		auto posts = my_friend->getPosts();
		std::cout << "\tViewing " << *my_friend << "'s posts: " << std::endl;
		for (auto post : my_friend->getPosts()) {
			std::cout << "\t\t" << *post << std::endl;
		}
	}
}

/**
* Send message from this user to 'to' user, with content 'msg'.
* Regular user can send message only to his friends.
* Buisness user can message any other user.
* Note: This function is implimented inside User class, NOT BuisnessUser. So it's regular user only.
*/
void User::sendMessageGeneric(User* to, Message* msg, bool buisnessUser) const {
	if (to != nullptr) {
		std::cout << *this << " is trying to send message to " << *to << std::endl;
	}
	else {
		delete msg; //This is optional. Because we create 'new Message()' on main.cpp, we have the option to delete there, or here.
		throw std::exception("Can't send message to null user.");
	}

	//Check not sending to self.
	if (to == this) {
		delete msg; //This is optional. Because we create 'new Message()' on main.cpp, we have the option to delete there, or here.
		throw std::exception("Can't send messages to self.");
	}

	if (buisnessUser) {
		std::cout << "\tMessage sent from " << *this << " (buisness user) to " << *to << std::endl;
		to->receiveMessage(msg);
		return;
	}
	else {
		//Regular user can't send to non-friends
		//Check 'to' in friends list
		for (auto my_friend : this->friends) {
			if (my_friend == to->getId()) {
				//He is in my friend's list
				std::cout << "\tMessage sent from " << *this << " (regular user) to " << *to << std::endl;
				to->receiveMessage(msg);
				return;
			}
		}
		//End for - non-friend
	}


	//'to' is not in friend list. Can't send message to non-friend.
	delete msg; //This is optional. Because we create 'new Message()' on main.cpp, we have the option to delete there, or here.
	throw std::exception("Regular user can't send message to non-friend user.");
}

void User::sendMessage(User* to, Message* msg) const {
	this->sendMessageGeneric(to, msg, false);
}

void User::receiveMessage(Message* msg) {
	std::cout << "\t\t" << *this << " received message: " << *msg << std::endl;
	this->receivedMsgs.push_back(msg);
}

void User::viewReceivedMessages() const {
	std::cout << *this << " is viewing received messages:" << std::endl;

	for (auto msg : this->receivedMsgs) {
		std::cout << "\t" << *msg << std::endl;
	}
}



void BuisnessUser::sendMessage(User* to, Message* msg) const {
	this->sendMessageGeneric(to, msg, true);
}