#include "comment.h"

Comment::Comment(std::string InputComment, int InputCommentID, int InputUserID)
{
	Content = InputComment;
	CommentID = InputCommentID;
	UserID = InputUserID;
}

int Comment::GetCommentID()
{
	return CommentID;
}

std::string Comment::GetContent()
{
	return Content;
}

std::vector<std::string>* Comment::GetListOfReplies()
{
	return &ListOfReplies;
}

int Comment::GetUserID()
{
	return UserID;
}

void Comment::ShowReplies()
{
	for (int Counter = 0; Counter < ListOfReplies.size(); Counter++)
		std::cout << CommentID << "." << (Counter + 1) << ". " << ListOfReplies[Counter] << std::endl;
}

bool Comment::IsAvailable()
{
	return Available;
}

void Comment::Delete()
{
	Available = false;
}