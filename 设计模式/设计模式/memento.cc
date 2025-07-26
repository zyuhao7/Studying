#include <iostream>
#include <string>
#include <vector>
// day-2025-7-26
/*
    备忘录设计模式（Memento Pattern）:
    一、概述
    备忘录模式是一种行为型设计模式，它允许在不暴露对象实现细节的情况下保存和恢复对象的内部状态。
    该模式非常适合需要提供撤销功能的场景，如文本编辑器、图形编辑器等。
    二、结构
    原发器（Originator）：负责创建备忘录对象，记录当前状态。
    备忘录（Memento）：负责存储原发器的状态。
     Caretaker（负责人）：负责保存备忘录对象，不直接操作备忘录。
*/

// 前向声明
class TextEditorMemento;

// 原发器：文本编辑器
class TextEditor
{
private:
    std::string content; // 当前文本内容
    int cursorPosition;  // 光标位置

public:
    TextEditor() : cursorPosition(0) {}

    // 设置内容
    void setContent(const std::string &text)
    {
        content = text;
        cursorPosition = content.length();
    }

    // 追加内容
    void appendContent(const std::string &text)
    {
        content += text;
        cursorPosition = content.length();
    }

    // 创建备忘录
    TextEditorMemento *createMemento();

    // 从备忘录恢复
    void restoreFromMemento(TextEditorMemento *memento);

    // 显示当前状态
    void printStatus() const
    {
        std::cout << "当前内容: " << content << std::endl;
        std::cout << "光标位置: " << cursorPosition << std::endl;
    }
};

// 备忘录类
class TextEditorMemento
{
private:
    // 将原发器声明为友元，使其能访问私有构造函数
    friend class TextEditor;

    std::string content; // 保存的内容
    int cursorPosition;  // 保存的光标位置

    // 私有构造函数，只能由原发器创建
    TextEditorMemento(const std::string &cnt, int pos)
        : content(cnt), cursorPosition(pos) {}

public:
    // 禁止外部修改，只提供获取接口
    std::string getContent() const { return content; }
    int getCursorPosition() const { return cursorPosition; }
};

// 实现原发器的创建备忘录方法
TextEditorMemento *TextEditor::createMemento()
{
    // 创建并返回一个包含当前状态的备忘录
    return new TextEditorMemento(content, cursorPosition);
}

// 实现原发器的恢复方法
void TextEditor::restoreFromMemento(TextEditorMemento *memento)
{
    if (memento)
    {
        content = memento->getContent();
        cursorPosition = memento->getCursorPosition();
    }
}

// 负责人：管理备忘录历史
class HistoryManager
{
private:
    std::vector<TextEditorMemento *> mementos; // 备忘录列表

public:
    ~HistoryManager()
    {
        // 清理所有备忘录
        for (auto m : mementos)
        {
            delete m;
        }
    }

    // 保存备忘录
    void saveMemento(TextEditorMemento *m)
    {
        mementos.push_back(m);
    }

    // 获取上一个备忘录（撤销）
    TextEditorMemento *getPreviousMemento()
    {
        if (mementos.empty())
            return nullptr;

        TextEditorMemento *last = mementos.back();
        mementos.pop_back();
        return last;
    }
};

// 客户端代码
// int main()
// {
//     TextEditor editor;
//     HistoryManager history;

//     // 初始状态
//     editor.setContent("Hello World");
//     std::cout << "=== 初始状态 ===\n";
//     editor.printStatus();

//     // 保存状态
//     history.saveMemento(editor.createMemento());

//     // 修改内容
//     editor.appendContent("! This is a test.");
//     std::cout << "\n=== 修改后 ===\n";
//     editor.printStatus();

//     // 保存状态
//     history.saveMemento(editor.createMemento());

//     // 再次修改
//     editor.appendContent(" More text added.");
//     std::cout << "\n=== 再次修改后 ===\n";
//     editor.printStatus();

//     // 撤销一次
//     TextEditorMemento *prev1 = history.getPreviousMemento();
//     editor.restoreFromMemento(prev1);
//     delete prev1; // 恢复后释放备忘录
//     std::cout << "\n=== 撤销一次后 ===\n";
//     editor.printStatus();

//     // 再次撤销
//     TextEditorMemento *prev2 = history.getPreviousMemento();
//     editor.restoreFromMemento(prev2);
//     delete prev2;
//     std::cout << "\n=== 再次撤销后 ===\n";
//     editor.printStatus();

//     return 0;
// }