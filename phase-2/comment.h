#ifndef COMMENT_H

#define COMMENT_H

#include <iostream>
#include <vector>
#include <string>

class Comment
{
public:
	Comment(std::string Content, int CommentID, int UserID);
	int GetCommentID();
	std::string GetContent();
	std::vector<std::string>* GetListOfReplies();
	int GetUserID();
	void ShowReplies();
	bool IsAvailable();
	void Delete();
private:
	int CommentID;
	std::string Content;
	std::vector<std::string> ListOfReplies;
	int UserID;
	bool Available = true;
};

#endif
