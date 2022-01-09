#ifndef MD5_H_INCLUDED
#define MD5_H_INCLUDED
#ifndef MD5_H
#define MD5_H

#include <string>
#include <fstream>

typedef unsigned char byte;
typedef unsigned long ulong;

using std::string;
using std::ifstream;

class MD5 {
public:
	MD5();
	MD5(const void *input, size_t length);
	MD5(const string &str);
	MD5(ifstream &in);
	void update(const void *input, size_t length);
	void update(const string &str);
	void update(ifstream &in);
	const byte* digest();
	string toString();
	void reset();
private:
	void update(const byte *input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const ulong *input, byte *output, size_t length);
	void decode(const byte *input, ulong *output, size_t length);
	string bytesToHexString(const byte *input, size_t length);

	/* class uncopyable */
	MD5(const MD5&);
	MD5& operator=(const MD5&);
private:
    ulong _state[4];	//四个常数（幻数
    ulong _count[2];	//位数
    byte _buffer[64];
    byte _digest[16];
    bool _finished;		//计算完成

    static const byte PADDING[64];	//填充
	static const char HEX[16];
	static const size_t BUFFER_SIZE = 1024;
};

#endif/*MD5_H*/


#endif // MD5_H_INCLUDED
