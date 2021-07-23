#pragma once

#include <iostream>

class Media
{
public:
	virtual void display() const {
		std::cout << "Media()";
	}

	friend std::ostream& operator << (std::ostream& os, const Media& media)
	{
		if (&media == 0) {
			os << "Media(nullptr)";
		}
		else {
			media.display();
		}
		return os;
	};
};

class Photo : public Media {
public:
	void display() const {
		std::cout << "Photo()";
	}
};

class Audio : public Media {
	void display() const {
		std::cout << "Audio()";
	}
};

class Video : public Media {
	void display() const {
		std::cout << "Video()";
	}
};