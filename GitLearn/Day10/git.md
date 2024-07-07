## day10 认识 Git 物件的绝对名称

```c++
    在 Git 版本控制的过程，每一个版本就代表一个 commit 物件。又因为版控过程中经常会建立分支，最终产出的 commit graph 可能会蛮复杂的，所以如何识別不同的版本，或是快速定位到特定版本以取得信息，就变得很重要.

  物件绝对名称
    $ git log
    commit 5f385e974b2896cb81137285ab5ee76f11f54046 (HEAD -> master)
    Author: 徐浩 <zyuhao7@yeah.net>
    Date:   Wed May 29 21:27:21 2024 +0800

        服务器调制、调试和测试

    commit c5fe9614bd70c031a3f6ec0e66ca0579138420c3 (origin/master)
    Author: 徐浩 <zyuhao7@yeah.net>
    Date:   Fri May 24 11:57:57 2024 +0800

  如果我们想看如上图 commit 物件的内容，可以利用 git cat-file -p commitid 来取得.

    $ git cat-file -p c5fe
    tree 8756ca46085a1b7ade8d7771585dd509801ee7f7
    parent 448911458fc38f6f01cada364b54581b11e67891
    author 徐浩 <zyuhao7@yeah.net> 1716523077 +0800
    committer 徐浩 <zyuhao7@yeah.net> 1716523077 +0800

    a.txt

  物件绝对名称的简短语法
    由于 Git 物件 id 是通过内容进行 SHA1 哈希后的结果，所以很长，在 Git 标示「绝对名称」时，可以用前面几码代替，最少不可低于 4 个字元。也就是说 4 ~ 40 个字元长度的「绝对名称」都是可以用的.

    有时候我们想取得版本记录会使用 git log 命令，同时也会输出每个文件的变更比较结果，结果会十分冗长，这时可以用 git log --pretty=oneline 指令来取得较为精简的历史记录，同时你也可以取得 commit 物件完整的「绝对名称」.

    $ git log --pretty=oneline
    5f385e974b2896cb81137285ab5ee76f11f54046 (HEAD -> master) 服务器调制、调试和测试
    c5fe9614bd70c031a3f6ec0e66ca0579138420c3 (origin/master) a.txt
    448911458fc38f6f01cada364b54581b11e67891 Merge branch 'master' of https://github.com/zyuhao7/Studying
    e81f40bbe08e5f36ace54b62ed7424f51d9d0575 a.txt
    14689121ac8432d5c33eedc98589916072914292 c.txt
    81243f47ec4138dfdd44c3f6d6870f211ad3d322 b.txt
    a58640f3394b74699bc66f80be9adad8168cb7c3 第八章-程序框架
    f03e69baec8fdf6f81950ac9a47a829163ddb112 测试
    3dc47da6113d2e6b91ea5501cb5705fe15e6f1e7 Merge branch 'master' of https://github.com/zyuhao7/Studying

  另外一个常用的技巧则是仅输出部分的「绝对名称」，通过 git log --pretty=oneline --abbrev-commit 指令执行即可.

  $ git log --pretty=oneline --abbrev-commit
    5f385e9 (HEAD -> master) 服务器调制、调试和测试
    c5fe961 (origin/master) a.txt
    4489114 Merge branch 'master' of https://github.com/zyuhao7/Studying
    e81f40b a.txt
    1468912 c.txt
    81243f4 b.txt
    a58640f 第八章-程序框架

今日小结
    git log
    git cat-file -p [object_id]
    git log --pretty=oneline
    git log --pretty=oneline --abbrev-commit

```