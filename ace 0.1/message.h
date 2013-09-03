#pragma once
template <class T> class message
{
public:
	message(void);
	message(T text): _text(text)
	{
	}
/*	void send();
	void receive();//*/
private:
	T _text;
};

