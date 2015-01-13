#ifndef IOcc_H
#define IOcc_H

class IOcc{
public:
	virtual unsigned getRank(char character, unsigned index) = 0;
	virtual char getChar(unsigned index) = 0;
	virtual unsigned indexOf(char character, unsigned rank) = 0;
	virtual unsigned length() = 0;
	virtual unsigned getAlphabet(char *&arr) = 0;
};
#endif