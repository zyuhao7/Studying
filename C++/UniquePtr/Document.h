#pragma once
#include <string>
class Document
{
	std::string m_Title{};
	std::string m_Content{};

public:
	Document(const std::string& title = "Untitled");
	void SetTitle(const std::string& title);
	const std::string& GetTitle() const;
	void AddContent(const std::string& content);
	void DeleteContent();
	const std::string& GetContent() const;
	bool IsEmpty() const;
};

