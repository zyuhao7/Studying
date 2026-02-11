#pragma once
#include "Document.h"
class Report : public Document
{
private:
	std::string m_Author;
public:
	Report(std::string title, std::string author);
	const std::string& getAuthor() const;

	void Display() const override
	{
		std::println("<=== [{}] ===> \n{}\nAuthor: {}",  title_, content_, m_Author);

	}

};

