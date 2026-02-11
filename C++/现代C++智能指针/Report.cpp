#include "Report.h"

Report::Report(std::string title, std::string author)
	:Document(std::move(title)),
	m_Author(std::move(author))
{

}

const std::string& Report::getAuthor() const
{
	return m_Author;
}

