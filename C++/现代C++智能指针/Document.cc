#include "Document.h"


Document::Document(std::string title)
    : title_(std::move(title)) {
}

bool Document::IsEmpty() const
{
    return content_.empty();
}

// 设置标题
void Document::setTitle(const std::string& title) {
    title_ = title;
}
const std::string& Document::getTitle() const
{
    return title_;
}

// 添加一段内容
void Document::addContent(const std::string& text) {
    content_ += text;
}

void Document::DeleteContent()
{
    content_ = "";
}

const std::string& Document::getContent() const { return content_; }

void Document::Display() const
{
    std::println("<=== [{}] ===>\n{}", title_, content_);
}