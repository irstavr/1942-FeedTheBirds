#include "..\..\include\Utilities\Utilities.h"

unsigned int Utilities::getCurrTime() {
	SYSTEMTIME st;
	GetSystemTime(&st);
	return st.wMilliseconds + st.wSecond * 1000 +
		st.wMinute * 60 * 1000 +
		st.wHour * 3600 * 1000 +
		st.wDay * 24 * 3600 * 1000;
}