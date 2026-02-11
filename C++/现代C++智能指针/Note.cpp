#include "Note.h"
Note::Note(std::string title)
    : Document(std::move(title))
{
}


void Note::AddTag(const std::string& tag)
{
    m_Tags.push_back(tag);
}

const std::vector<std::string>& Note::GetTags() const
{
    return m_Tags;
}