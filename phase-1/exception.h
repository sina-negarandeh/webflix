#ifndef EXCEPTION_H

#define EXCEPTION_H

#include <exception>


class NotFound : public std::exception
{
public:
	const char* what() const noexcept;
};

class BadRequest : public std::exception
{
public:
	const char* what() const noexcept;
};

class PermissionDenied : public std::exception
{
public:
	const char* what() const noexcept;
};

#endif
