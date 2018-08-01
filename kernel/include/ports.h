#ifndef PORTS_H
#define PORTS_H

//Reads byte from a specified port
unsigned char readBytePort(unsigned short port);
//Writes a byte to a specified port
void writeBytePort(unsigned short port, unsigned char data);
//Reads word from a specified port
unsigned short readWordPort(unsigned short port);
//Writes a word to a specified port
void writeWordPort(unsigned short port, unsigned short data);

#endif
