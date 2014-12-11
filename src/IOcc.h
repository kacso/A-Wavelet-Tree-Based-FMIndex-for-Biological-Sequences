#ifndef IOcc_H
#define IOcc_H

class IOcc{
public:
	virtual int getRank(char character, int index) = 0;
	virtual char getChar(int index) = 0;
};
#endif