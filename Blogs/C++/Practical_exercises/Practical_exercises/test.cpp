#include<iostream>

using namespace std;



#if 0

int main()
{
    //                      重载++的时钟.

    class Time
    {
    public:
        Time(int h = 0, int m = 0, int s = 0)
            :hour(h),
            minute(m),
            second(s)
        {}
        Time operator++();
        Time operator++(int);
        void operator()(int h, int m, int s) {
            hour = h;
            minute = m;
            second = s;
        }
        void ShowTime()
        {
            cout << "当前时间为: " << hour << ":" << minute << ":" << second << endl;
        }

    private:
        int hour, minute, second;

    };

    Time Time::operator++()
    {
        ++second;
        if (second == 60)
        {
            ++minute;
            second = 0;
            if (minute == 60)
            {
                minute = 0;
                ++hour;
                if (hour == 24)
                    hour = 0;
            }
        }
        return *this;
    }

    Time Time::operator++(int n)
    {
        Time tmp(*this);
        ++(*this);
        return tmp;
    }


    Time t(23, 59, 59);
    t.ShowTime();
    ++t;
    (t++).ShowTime();
    t.ShowTime();


int i = 1;
void other(void)
{
    static int a = 2;
    static int b;
    int c = 10;
    a = a + 2;
    i = i + 32;
    c = c + 5;
    cout << "--- Other ---\n";
    cout << "i = " << i << " a = " << a << " b = " << b << " c = " << c << endl;
    b = a;
}



static int a;
int b = -10;
int c = 0;
cout << "--- Main ---\n";
cout << "i = " << i << " a = " << a << " b = " << b << " c = " << c << endl;//1 0 -10 0
c = c + 8;
other();   //33 4 0 15

cout << "--- Main ---\n";
cout << "i = " << i << " a = " << a << " b = " << b << " c = " << c << endl;//33 0 -10 8 
i = i + 10;
other(); // 75 6 4 15
other(); // 107 8 6 15


    struct student {
        int num;       // 4
        char name[20]; //20
        char gender;   //28
    };

    student s = { 10, "asd", 'M' };
    cout << s.num << endl;            //10
    cout << sizeof(s.num) << endl;    // 4
    cout << sizeof(s.name) << endl;   //20
    cout << sizeof(s.gender) << endl; //1
    cout << sizeof(s) << endl;        //28


            递归2
            int f(int n, int k)
            {
                if (n == 0 || k == 0) return 1;
                else return f(n - 1, k - 1) + f(n - 1, k);
            }

            cout << "请输入n与k:";
            int n, k;
            cin >> n >> k;
            cout << f(n, k) << endl;

                递归1

                int f(int n)
            {
                if (n == 0) return 1;
                else return n * f(n - 1);
            }

            cout << "input x: ";
            int x;
            cin >> x;
            cout << f(x) << endl;


x的n次方
    double power(double x, int n) {
    double val = 1.0;
    while (n--) {
        val *= x;
    }
    return val;
}


    int x;
cin >> x;
int wei = 0;
int sum = 0;
int each, chu;
for (int i = 0; i < 8; i++) {
    each = x % 10;
    chu = x / 10;
    sum += each * power(2, wei);
    x = chu;
    wei++;
}
cout << sum << endl;

                    汉诺塔
    void move(char A, char B);
    void hanoi(int n, char A, char B, char C);
    void move(char A, char B) { cout << A << "->" << B << endl; }

    void hanoi(int n, char A, char B, char C) {
        if (n == 1) {
            move(A, C);
        }
        else {
            hanoi(n - 1, A, C, B);
            move(A, C);
            hanoi(n - 1, B, A, C);
        }
    }

    cout << "请输入盘子数量：";
    int disks;
    cin >> disks;
    hanoi(disks, 'A', 'B', 'C');

    enum weekday { s, m, t, w, thu, f, s1 }; // 0 1 2 3 4 5 6 7

    union myun {
        struct {
            int x;
            int y;
            int z;
        } u;
        int k;
    } a;

    a.u.x = 4;
    a.u.y = 5;
    a.u.z = 6;
    a.k = 0; //覆盖掉第一个int空间值
    printf("%d %d %d %d\n", a.u.x, a.u.y, a.u.z, a.k); // 0 5 6 0


    int i, j, k, f;
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 30; j++)
            cout << " ";
        for (k = 1; k <= 8 - 2 * i; k++)
            cout << " ";
        for (f = 1; f <= 2 * i; f++)
            cout << '*';
        cout << endl;
    }
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 30; j++)
            cout << " ";
        for (f = 1; f <= 7 - 2 * i; f++)
            cout << '*';
        cout << endl;
    }


	return 0;
}
#endif