#include <iostream>
#include <vector>
#include <string>
// day-2025-7-21
/*
    command模式:
    命令模式是一种行为设计模式，它将请求封装为对象，从而使您可以使用不同的请求、队列或日志请求参数化其他对象。
    命令模式也支持撤销操作。
    命令模式的主要优点是：
        1. 解耦请求发送者和接收者：命令模式将请求发送者和接收者解耦，发送者无需知道接收者的存在，接收者也无需知道发送者的存在。
        2. 支持参数化请求：命令模式允许您将请求参数化，从而使您可以使用不同的参数化请求来调用相同的接收者。
        3. 支持队列请求：命令模式支持将请求排队，从而使您可以按照顺序执行请求。
        4. 支持日志请求：命令模式支持将请求记录在日志中，从而使您可以在需要时重新执行请求。
    命令模式的主要缺点是：
        1. 可能会导致某些系统有过多的具体命令类：命令模式可能会导致某些系统有过多的具体命令类，这会增加系统的复杂性。
    与其他设计模式对比:
        1. 与策略模式对比：命令模式和策略模式都封装了算法，它们的主要区别在于命令模式关注的是请求的发送者和接收者，而策略模式关注的是算法的选择。
        2. 与模板方法模式对比：命令模式和模板方法模式都封装了算法，它们的主要区别在于命令模式关注的是请求的发送者和接收者，而模板方法模式关注的是算法的执行顺序。
*/
// 命令接口：声明执行操作的方法
class Command
{
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual std::string GetName() const = 0;
};

// 接收者类：实现具体业务逻辑
class TextEditor
{
private:
    std::string text_;
    std::string clipboard_; // 剪贴板
    size_t cursor_position_ = 0;

public:
    void TypeText(const std::string &text)
    {
        text_.insert(cursor_position_, text);
        cursor_position_ += text.length();
        std::cout << "Typed text: \"" << text << "\", Current text: \"" << text_ << "\"\n";
    }

    void DeleteText(size_t length)
    {
        if (length > cursor_position_)
            length = cursor_position_;
        if (length > 0)
        {
            std::string deleted = text_.substr(cursor_position_ - length, length);
            text_.erase(cursor_position_ - length, length);
            cursor_position_ -= length;
            std::cout << "Deleted text: \"" << deleted << "\", Current text: \"" << text_ << "\"\n";
        }
    }

    void CopyText(size_t start, size_t length)
    {
        if (start + length <= text_.length())
        {
            clipboard_ = text_.substr(start, length);
            std::cout << "Copied to clipboard: \"" << clipboard_ << "\"\n";
        }
    }

    void PasteText()
    {
        if (!clipboard_.empty())
        {
            text_.insert(cursor_position_, clipboard_);
            cursor_position_ += clipboard_.length();
            std::cout << "Pasted text: \"" << clipboard_ << "\", Current text: \"" << text_ << "\"\n";
        }
    }

    void SetCursorPosition(size_t position)
    {
        if (position <= text_.length())
        {
            cursor_position_ = position;
            std::cout << "Cursor moved to position: " << cursor_position_ << std::endl;
        }
    }

    const std::string &GetText() const { return text_; }
    size_t GetCursorPosition() const { return cursor_position_; }
    const std::string &GetClipboard() const { return clipboard_; }
};

// 具体命令：实现文本输入操作
class TypeCommand : public Command
{
private:
    TextEditor &editor_;
    std::string text_;
    size_t previous_cursor_position_;

public:
    TypeCommand(TextEditor &editor, const std::string &text)
        : editor_(editor), text_(text) {}

    void Execute() override
    {
        previous_cursor_position_ = editor_.GetCursorPosition();
        editor_.TypeText(text_);
    }

    void Undo() override
    {
        editor_.SetCursorPosition(previous_cursor_position_);
        editor_.DeleteText(text_.length());
    }

    std::string GetName() const override
    {
        return "TypeCommand(\"" + text_ + "\")";
    }
};

// 具体命令：实现文本删除操作
class DeleteCommand : public Command
{
private:
    TextEditor &editor_;
    size_t length_;
    std::string deleted_text_;
    size_t previous_cursor_position_;

public:
    DeleteCommand(TextEditor &editor, size_t length)
        : editor_(editor), length_(length) {}

    void Execute() override
    {
        previous_cursor_position_ = editor_.GetCursorPosition();
        size_t start_pos = previous_cursor_position_ > length_ ? previous_cursor_position_ - length_ : 0;
        deleted_text_ = editor_.GetText().substr(start_pos, length_);
        editor_.DeleteText(length_);
    }

    void Undo() override
    {
        editor_.SetCursorPosition(previous_cursor_position_ - length_);
        editor_.TypeText(deleted_text_);
    }

    std::string GetName() const override
    {
        return "DeleteCommand(" + std::to_string(length_) + ")";
    }
};

// 具体命令：实现复制操作
class CopyCommand : public Command
{
private:
    TextEditor &editor_;
    size_t start_;
    size_t length_;
    std::string previous_clipboard_;

public:
    CopyCommand(TextEditor &editor, size_t start, size_t length)
        : editor_(editor), start_(start), length_(length) {}

    void Execute() override
    {
        previous_clipboard_ = editor_.GetClipboard();
        editor_.CopyText(start_, length_);
    }

    void Undo() override
    {
        // 复制操作不修改文档状态，因此撤销操作为空
    }

    std::string GetName() const override
    {
        return "CopyCommand(" + std::to_string(start_) + ", " + std::to_string(length_) + ")";
    }
};

// 具体命令：实现粘贴操作
class PasteCommand : public Command
{
private:
    TextEditor &editor_;
    std::string pasted_text_;
    size_t previous_cursor_position_;

public:
    PasteCommand(TextEditor &editor)
        : editor_(editor) {}

    void Execute() override
    {
        previous_cursor_position_ = editor_.GetCursorPosition();
        pasted_text_ = editor_.GetClipboard();
        editor_.PasteText();
    }

    void Undo() override
    {
        editor_.SetCursorPosition(previous_cursor_position_);
        editor_.DeleteText(pasted_text_.length());
    }

    std::string GetName() const override
    {
        return "PasteCommand()";
    }
};

// 调用者类：负责调用命令执行请求
class Menu
{
private:
    std::vector<Command *> command_history_;
    size_t history_index_ = 0;

public:
    ~Menu()
    {
        // 清理命令历史
        for (auto cmd : command_history_)
        {
            delete cmd;
        }
        command_history_.clear();
    }

    void ExecuteCommand(Command *cmd)
    {
        // 清除历史记录中当前位置之后的命令（用于支持重做）
        while (history_index_ < command_history_.size())
        {
            delete command_history_.back();
            command_history_.pop_back();
        }

        cmd->Execute();
        command_history_.push_back(cmd);
        history_index_ = command_history_.size();
        std::cout << "Executed: " << cmd->GetName() << std::endl;
    }

    bool Undo()
    {
        if (history_index_ > 0)
        {
            history_index_--;
            Command *cmd = command_history_[history_index_];
            cmd->Undo();
            std::cout << "Undid: " << cmd->GetName() << std::endl;
            return true;
        }
        std::cout << "Nothing to undo" << std::endl;
        return false;
    }

    bool Redo()
    {
        if (history_index_ < command_history_.size())
        {
            Command *cmd = command_history_[history_index_];
            cmd->Execute();
            history_index_++;
            std::cout << "Redid: " << cmd->GetName() << std::endl;
            return true;
        }
        std::cout << "Nothing to redo" << std::endl;
        return false;
    }
};

// 客户端代码：演示命令模式的使用
// int main()
// {
//     std::cout << "=== Command Design Pattern Demo ===\n\n";

//     // 创建接收者
//     TextEditor editor;
//     // 创建调用者
//     Menu menu;

//     // 执行一系列命令
//     menu.ExecuteCommand(new TypeCommand(editor, "Hello "));
//     menu.ExecuteCommand(new TypeCommand(editor, "World!"));
//     menu.ExecuteCommand(new CopyCommand(editor, 0, 5)); // 复制 "Hello"
//     menu.ExecuteCommand(new TypeCommand(editor, " \\"));
//     menu.ExecuteCommand(new PasteCommand(editor));     // 粘贴 "Hello"
//     menu.ExecuteCommand(new DeleteCommand(editor, 7)); // 删除 "\Hello!"

//     std::cout << "\nFinal text: \"" << editor.GetText() << "\"\n\n";

//     // 演示撤销操作
//     menu.Undo();
//     menu.Undo();
//     menu.Undo();

//     // 演示重做操作
//     menu.Redo();
//     menu.Redo();

//     return 0;
// }
