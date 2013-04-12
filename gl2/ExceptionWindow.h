#ifndef EXCEPTIONWINDOW_H
#define EXCEPTIONWINDOW_H

#include <exception>

class ExceptionRegisterWindowClass : public std::exception
{
	virtual const char * what() const;
};

class ExceptionCreateWindow : public std::exception
{
	virtual const char * what() const;
};

class ExceptionCreateDeviceContext : public std::exception
{
	virtual const char * what() const;
};

class ExceptionChoosePixelFormat : public std::exception
{
	virtual const char * what() const;
};

class ExceptionSetPixelFormat : public std::exception
{
	virtual const char * what() const;
};

class ExceptionCreateRenderingContext : public std::exception
{
	virtual const char * what() const;
};

class ExceptionActivateRenderingContext : public std::exception
{
	virtual const char * what() const;
};

class ExceptionInitOpenGLWindow : public std::exception
{
	virtual const char * what() const;
};


#endif // EXCEPTIONWINDOW_H
