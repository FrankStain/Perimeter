#ifndef __XBUFFER_H
#define __XBUFFER_H

#include <string>
#include <cstring>

#ifndef NULL
#define NULL	0L
#endif

#define XB_CONV_BUFFER_LEN	63

#define XB_DEFSIZE	256

#define XB_BEG		0
#define XB_CUR		1
#define XB_END		2

#define XB_FORWARD	0
#define XB_BACKWARD	1
#define XB_GLOBAL	2

#define XB_CASEON	0
#define XB_CASEOFF	1

#define XB_DEFDIGITS	8

struct XBuffer
{
	char* buf;
	unsigned int size;
	unsigned int offset;
	int digits;
	int MakeFree;
	int automatic_realloc;

	XBuffer(unsigned int sz = XB_DEFSIZE, int automatic_realloc_ = 0);
	XBuffer(void* p,int sz);
	~XBuffer(void){ free(); }

	void SetDigits(int d) { digits = d; }

	void alloc(unsigned int sz);
	void free(void);
	void fill(char fc = '\0');
	void set(int off,int mode = XB_BEG);
	void init(void){ offset = 0; *buf = 0; }
	int search(char* what,int mode = XB_FORWARD,int cs = XB_CASEON);
	int end() const { return (offset > size); }

	unsigned int tell(void) const { return offset; }
	unsigned int length(void) const { return size; }
	char* address(){ return buf; }

	unsigned int read(void* s, unsigned int len);
	unsigned int write(const void* s, unsigned int len, int bin_flag = 1);
	void handleOutOfSize();
	
	XBuffer& operator< (const char* v);
	XBuffer& operator< (char v) { return write(v); }
	XBuffer& operator< (unsigned char v) { return write(v); }
	XBuffer& operator< (short v) { return write(v); }
	XBuffer& operator< (unsigned short v) { return write(v); }
	XBuffer& operator< (int v ) { return write(v); }
	XBuffer& operator< (unsigned int v) { return write(v); }
	XBuffer& operator< (long v) { return write(v); }
	XBuffer& operator< (unsigned long v) { return write(v); }
    XBuffer& operator< (unsigned long long v) { return write(v); }
	XBuffer& operator< (float v) { return write(v); }
	XBuffer& operator< (double v) { return write(v); }
    XBuffer& operator< (long double v) { return write(v); }

	XBuffer& operator> (char* v);
	XBuffer& operator> (char& v) { return read(v); }
	XBuffer& operator> (unsigned char& v) { return read(v); }
	XBuffer& operator> (short& v) { return read(v); }
	XBuffer& operator> (unsigned short& v) { return read(v); }
	XBuffer& operator> (int& v) { return read(v); }
	XBuffer& operator> (unsigned int& v) { return read(v); }
	XBuffer& operator> (long& v) { return read(v); }
	XBuffer& operator> (unsigned long& v) { return read(v); }
    XBuffer& operator> (unsigned long long& v) { return read(v); }
	XBuffer& operator> (float& v) { return read(v); }
	XBuffer& operator> (double& v) { return read(v); }
    XBuffer& operator> (long double& v) { return read(v); }

    template<typename T>
    XBuffer& operator<= (T var) {
        std::string str = std::to_string(var);
        write(str.c_str(), str.length(), 0);
        return *this;
    }
	XBuffer& operator<= (float);
	XBuffer& operator<= (double);
	XBuffer& operator<= (long double);

	XBuffer& operator>= (char&);
	XBuffer& operator>= (unsigned char&);
	XBuffer& operator>= (short&);
	XBuffer& operator>= (unsigned short&);
	XBuffer& operator>= (int&);
	XBuffer& operator>= (unsigned int&);
	XBuffer& operator>= (long&);
	XBuffer& operator>= (unsigned long&);
    XBuffer& operator>= (unsigned long long&);
	XBuffer& operator>= (float&);
	XBuffer& operator>= (double&);
    XBuffer& operator>= (long double&);

	operator const char* () const { return buf; }
	const char* operator ()(int offs){ return buf + offs; }
	XBuffer& operator++(){ offset++; return *this; }
	XBuffer& operator--(){ offset--; return *this; }
	XBuffer& operator+= (int v){ offset+=v; return *this; }
	XBuffer& operator-= (int v){ offset-=v; return *this; }

	const char& operator[](int ind) const { return buf[ind]; }
	const char& operator()() const { return buf[offset]; }

	char& operator[](int ind){ return buf[ind]; }
	char& operator()(){ return buf[offset]; }

	template<typename T> XBuffer& write(const T& v){ while(offset + sizeof(T) >= size) handleOutOfSize(); memcpy(&buf[offset], &v, sizeof(T)); offset += sizeof(T); return *this; }
	template<typename T> XBuffer& read(T& v){ memcpy(&v, &buf[offset], sizeof(T)); offset += sizeof(T); return *this; }

private:
	char convBuf[XB_CONV_BUFFER_LEN + 1];
};


#endif /* __XBUFFER_H */

