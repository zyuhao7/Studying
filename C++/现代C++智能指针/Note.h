#pragma once
#include <vector>
#include <print>
#include <iostream>
#include "Document.h"
class Note : public Document
{
private:
    std::vector<std::string> m_Tags;
    std::string m_Content;
public:
    explicit Note(std::string title);
    void addContent(const std::string& content) override
    {
        m_Content += "* "+ content + "\n";
    }
    void AddTag(const std::string& tag);
    const std::vector<std::string>& GetTags() const;

    void Display() const override
    {
        std::println("<=== [{}] ===>\n{}", title_, m_Content);

        for (const auto& tag : m_Tags)
            std::cout << "#" << tag << " ";
        std::cout << '\n';

    }

};

