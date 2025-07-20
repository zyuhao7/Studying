#include <iostream>
#include <vector>
#include <string>
using namespace std;
//
// day-2025-7-13
// �Ž�ģʽ bridge

/*
                ����������������������������������������
                ��  Window�������ࣩ ��<��������������������������
                ����������������������������������������        ��
                         ��                        ��
                ��������������������������������������          ��
                �� DialogWindow����չ ��            ��
                ��������������������������������������          ��
                         ��                        ��
                  has-a����ϣ�                    ��
                         ��                        ��
                ��������������������������������������          ��
                �� WindowImpl �ӿ�  ������������������������������
                ��������������������������������������
                         ��
          �������������������������������੤��������������������������
          ��             ��             ��
     WindowsImpl      LinuxImpl       MacImpl




*/

//  WindowImpl �ӿ�
class WindowImpl
{
public:
    virtual void DrawText(const std::string &text) = 0;
    virtual void DrawRect(int x, int y, int w, int h) = 0;
    virtual ~WindowImpl() {}
};

// ����ʵ��
class WindowsImpl : public WindowImpl
{
public:
    void DrawText(const std::string &text) override
    {
        std::cout << "Windows: Drawing text - " << text << std::endl;
    }

    void DrawRect(int x, int y, int w, int h) override
    {
        std::cout << "Windows: Drawing rectangle at(" << x << "," << y << ") size " << w << " * " << h << std::endl;
    }
};

class LinuxImpl : public WindowImpl
{
public:
    void DrawText(const std::string &text) override
    {
        std::cout << "Linux: Drawing text - " << text << std::endl;
    }

    void DrawRect(int x, int y, int w, int h) override
    {
        std::cout << "Linux: Drawing rectangle at(" << x << "," << y << ") size " << w << " * " << h << std::endl;
    }
};

// Windows ������
class Window
{
protected:
    WindowImpl *impl_;

public:
    Window(WindowImpl *impl)
        : impl_(impl)
    {
    }

    virtual ~Window() {}
    virtual void Draw() = 0;
};

// ��չ�ľ��� Window ��
class DialogWindow : public Window
{
public:
    DialogWindow(WindowImpl *impl)
        : Window(impl) {}
    void Draw() override
    {
        std::cout << "[DialogWindow Drawing Start]" << std::endl;
        impl_->DrawText("this is a dialog");
        impl_->DrawRect(10, 10, 200, 100);
        std::cout << "[DialogWindow Drawing End]" << std::endl;
    }
};

class IconWindow : public Window
{
public:
    IconWindow(WindowImpl *impl)
        : Window(impl)
    {
    }
    void Draw() override
    {
        std::cout << "[IconWindow Drawing Start]" << std::endl;
        impl_->DrawRect(0, 0, 50, 50);
        impl_->DrawText("Icon");
        std::cout << "[IconWindow Drawing End]" << std::endl;
    }
};

// int main()
// {
//    WindowImpl* winImpl = new WindowsImpl();
//    Window* dialogWin = new DialogWindow(winImpl);
//    dialogWin->Draw();

//    WindowImpl* linuxImpl = new LinuxImpl();
//    Window* iconWin = new IconWindow(winImpl);
//    iconWin->Draw();

//    delete dialogWin;
//    delete winImpl;
//    delete linuxImpl;
//    delete iconWin;
// }