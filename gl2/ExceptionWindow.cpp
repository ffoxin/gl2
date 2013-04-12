#include "ExceptionWindow.h"
#include "StringConstants.h"

const char * ExceptionRegisterWindowClass::what() const throw()
{
	return sRegisterWindowClassError;
}

const char * ExceptionCreateWindow::what() const
{
	return sCreateWindowError;
}

const char * ExceptionCreateDeviceContext::what() const
{
	return sCreateDeviceContextError;
}

const char * ExceptionChoosePixelFormat::what() const
{
	return sChoosePixelFormatError;
}

const char * ExceptionSetPixelFormat::what() const
{
	return sSetPixelFormatError;
}

const char * ExceptionCreateRenderingContext::what() const
{
	return sCreateRenderingContextError;
}

const char * ExceptionActivateRenderingContext::what() const
{
	return sActivateRenderingContextError;
}

const char * ExceptionInitOpenGLWindow::what() const
{
	return sInitOpenGLWindowError;
}
