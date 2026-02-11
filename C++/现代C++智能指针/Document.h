#pragma once
#include <string>
#include <fstream>
#include <print>
class Document {
public:
    friend std::ostream& operator<<(std::ostream& os, const Document& doc)
    {
        return os << doc.content_;
    }

    Document(const std::string title = "Untitled");
    bool IsEmpty() const;
    void setTitle(const std::string& title);
    const std::string& getTitle() const;
    virtual void addContent(const std::string& text);
    void DeleteContent();
    const std::string& getContent() const;
    virtual void Display() const;
    virtual ~Document() = default;

public:
    std::string title_{};
    std::string content_{};
};
