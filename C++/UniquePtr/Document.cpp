#include "Document.h"

Document::Document(const std::string& title)
{
	m_Title = title;
}

void Document::SetTitle(const std::string& title)
{
	m_Title = title;
}

const std::string& Document::GetTitle() const
{
	return m_Title;
}

void Document::AddContent(const std::string& content)
{
	m_Content += content;
}

void Document::DeleteContent()
{
	m_Content.clear();
}

const std::string& Document::GetContent() const
{
	// TODO: 在此处插入 return 语句
	return m_Content;
}

bool Document::IsEmpty() const
{
	return m_Content.empty(); 
}
