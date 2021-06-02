#ifndef EXCEPTION_H

#define EXCEPTION_H

#include <exception>
#include <string>


class NotFound : public std::exception
{
public:
	std::string what();
};

class BadRequest : public std::exception
{
public:
	std::string what();
};

class PermissionDenied : public std::exception
{
public:
	std::string what();
};

#endif
