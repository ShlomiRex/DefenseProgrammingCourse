#include "USocial.h"

int main()
{
	USocial us;

	User* u1 = us.registerUser("Liron");
	try {
		User* u1_second = us.registerUser("Liron"); //Username with that name already exists
	}
	catch (const std::exception& e) {
		std::cout << "error: " << e.what();
	}

	User* u2 = us.registerUser("Yahav");
	User* u3 = us.registerUser("Shachaf");
	User* u4 = us.registerUser("Tsur", true);
	User* u5 = us.registerUser("Elit");




	u1->post("Hello world!");
	u1->post("My name is Liron and this is awesome!", new Video());

	u2->post("I'm having a great time here :)", new Audio());
	u3->post("This is awesome!", new Photo());

	u5->addFriend(u1);
	u5->addFriend(u2);

	try {
		u5->addFriend(u2); //exception, user already in friends list
	}
	catch (const std::exception& e) {
		std::cout << "error: " << e.what();
	}

	u5->viewFriendsPosts(); // should see only u1, u2 s' posts
	u4->sendMessage(u5, new Message("Buy Falafel!"));
	
	u5->viewReceivedMessages();
	try
	{
		u3->sendMessage(u5, new Message("All your base are belong to us"));
	}
	catch (const std::exception& e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
	
	u5->viewReceivedMessages();
	u3->addFriend(u5);
	u3->sendMessage(u5, new Message("All your base are belong to us"));
	u5->viewReceivedMessages();

	User* u = us.getUserById(1); //get user with id 1 (which is user 1).
	//Check same pointer
	if (u == u1) {
		std::cout << "getUserById success" << std::endl;
	}
	else {
		throw std::exception("Expected User* u1 from id 1.");
	}

	us.removeUser(u1);
	us.removeUser(u5);
	//u2,u3,u4 left on heap. Destructor still works.

	us.registerUser("Liron"); //It shouldn't throw exception, because u1 was removed, so the name doesn't exist anymore.
	try {
		us.registerUser("Liron"); //Throw error, liron already registered
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	

	//Note: I made sure no memory leaks were occuring with Visual Studio Heap Profiler. (Diagnosting Tools -> Memory Usage -> Take snapshot at the beginning and end, and diff heap size)
	// "new Message()" or "new Video()" or "new Media()" would create memory leak. (because we create them in main.cpp but never delete them ourselves.)
	//Thats why, when error occurs, and we do 'new Message()' or 'new Post()', then we delete it afterwards because of error to avoid deleting it inside 'main.cpp'.
	//This is my idea for maximum security.
	return 0;
}