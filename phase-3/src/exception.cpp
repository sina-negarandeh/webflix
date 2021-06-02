#include "exception.hpp"

std::string NotFound::what()
{
	return "Not Found\n";
}

std::string BadRequest::what()
{
	return "Bad Request\n";
}

std::string PermissionDenied::what()
{
	return "Permission Denied\n";
}