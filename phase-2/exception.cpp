#include "exception.h"

const char* NotFound::what() const noexcept
{
	return "Not Found\n";
}

const char* BadRequest::what() const noexcept
{
	return "Bad Request\n";
}

const char* PermissionDenied::what() const noexcept
{
	return "Permission Denied\n";
}