## 第 11 天：认识 Git 物件的一般参照与符号参照

### 认识物件的参照名称
    参照名称 (ref) 简单来说就是 Git 物件的一个「指标」，或是相对于「绝对名称」的另一个「好记名称」，用一个预先定义或你自行定义的名称来代表某一个 Git 物件。

    我们以｢分支名称｣为例，来说明一下「参照名称」的实体结构为何。以下图为例，我们通过 git branch 取得所有分支名称，你可以看到我们目前有三个分支，然而这三个分支的名称其实就是一个｢参照名称｣，这代表这三个「参照名称」分別对应到 Git 物件仓库中的三个 commit 物件。在下图中你也可以看出这些分支的参照名称其实就是一个文件而已，所有「本地分支」的参照名称皆位于 .git\refs\heads 目录下：
```c++
        $ git branch
        * master
        newbranch1
        newbranch2
        newbranch3

        $ dir .git/refs/heads
        master  newbranch1  newbranch2  newbranch3
```
    接着我再以下图来证明这个文件是如何跟「绝对名称」做连结。我先通过 git branch 取得所有分支名称，并发现目前「工作目录」是指向 newbranch1 这个分支。此时我们通过 git log --pretty=oneline 即可取得该分支的所有版本记录。预设这些分支的「参照名称」会指向分支的「最新版」，我们只要打开 .git\refs\heads\newbranch1 文件的内容，就可以看出这是一个纯文字档而已，而且是指向版本历史记录中的「最新版」。最后再以 git cat-file -p 0bd0 取得该 commit 物件的内容，以及用 git show 0bd0 取得该版本的变更记录，藉此证明这些文件就是「参照名称」的主要用途。

```c++
        $ git branch
        master
        * newbranch1
        newbranch2
        newbranch3

        $ git log --pretty=oneline
        edcb4a0cc586f36e562572a496a7b738c867cfdc (HEAD -> newbranch1) Add b.txt in newbranch1
        2afb5aba0f210448f7ae3e48bc9b20b320987cce a.txt:set 1 as content
        0dedb1d7654d7ff435f74f8cf45ac8ce724fcd
        a9 Initial commit

        $ cat .git/refs/heads/newbranch1
        edcb4a0cc586f36e562572a496a7b738c867cfdc

        $ git cat-file -p edcb
        tree 3a1fdd64de8fc83e5ebd9cfd037b995bb594afa2
        parent 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        author 徐浩 <zyuhao7@yeah.net> 1720103604 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720103604 +0800

        $ git cat-file -p newbranch1
        tree 3a1fdd64de8fc83e5ebd9cfd037b995bb594afa2
        parent 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        author 徐浩 <zyuhao7@yeah.net> 1720103604 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720103604 +0800


        $ git show edcb
        commit edcb4a0cc586f36e562572a496a7b738c867cfdc (HEAD -> newbranch1)
        Author: 徐浩 <zyuhao7@yeah.net>
        Date:   Thu Jul 4 22:33:24 2024 +0800

            Add b.txt in newbranch1

        diff --git a/b.txt b/b.txt
        new file mode 100644
        index 0000000..a3be271
        --- /dev/null
        +++ b/b.txt
        @@ -0,0 +1 @@
        +newbranch1

    在大多数情况下, [参照名称] 通常会指向一个 commit 物件, 但并非必要, 也可以指向其他Git 物件, 比如 blob物件、 tree 物件、 tag 物件等等.
```

### 关于 .git/refs/ 目录

    从上述范例其实已经能看出，所有的「参照名称」都是个文件，而且一律放在 git/refs/ 目录下。而 Git 的参照名称所放置的目录位置，主要有三个：

    * 本地分支：.git/refs/heads/
    * 远端分支：.git/refs/remotes/
    * 标　　签：.git/refs/tags/


    再举个简单例子，如果你建立一个分支名称为 f2e，这时你会知道本地分支的「参照名称」会建立 .git/refs/heads/f2e 文件，如下图示：
```c++
        $ git branch
        master
        * newbranch1
        newbranch2
        newbranch3

        $ ls .git/refs/heads -l
        total 4
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 21:30 master
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 22:33 newbranch1
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 21:38 newbranch2
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 21:58 newbranch3

        $ git branch f2e

        $ ls .git/refs/heads -l
        total 5
        -rw-r--r-- 1 徐浩 197121 41 Jul 10 13:07 f2e
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 21:30 master
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 22:33 newbranch1
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 21:38 newbranch2
        -rw-r--r-- 1 徐浩 197121 41 Jul  4 21:58 newbranch3

```

### 认识物件的符号参照名称 (symref)

    符号参照名称 (symref) 其实也是参照名称 (ref) 的一种，只是内容不同而已。我们从下图应可看出其内容的差异，「符号参照」会指向另一个「参照名称」，并且内容以 ref: 开头：

```c++
        $ cat .git/head
        ref: refs/heads/newbranch1      

        $ cat .git/refs/heads/newbranch1
        edcb4a0cc586f36e562572a496a7b738c867cfdc

        $ git cat-file -p edcb
        tree 3a1fdd64de8fc83e5ebd9cfd037b995bb594afa2
        parent 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        author 徐浩 <zyuhao7@yeah.net> 1720103604 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720103604 +0800
```
    在 Git 工具中，预设会维护一些特别的符号参照，方便我们快速取得常用的 commit 物件，且这些物件预设都会储存在 .git/ 目录下。这些符号参考有以下四个：

```
 HEAD
    永远会指向「工作目录」中所设定的「分支」当中的「最新版」。
    所以当你在这个分支执行 git commit 后，这个 HEAD 符号参照也会更新成该分支最新版的那个 commit 物件。

 ORIG_HEAD
    简单来说就是 HEAD 这个 commit 物件的「前一版」，经常用来复原上一次的版本变更。
    FETCH_HEAD使用远端仓库时，可能会使用 git fetch 指令取回所有远端仓库的物件。
    这个 FETCH_HEAD 符号参考则会记录远端仓库中每个分支的 HEAD (最新版) 的「绝对名称」。

 MERGE_HEAD
    当你执行合并工作时 (关于合并的议题会在日后的文章中会提到)，「合并来源｣的 commit 物件绝对名称会被记录在 MERGE_HEAD 这个符号参照中。
```

### 一般参照与符号参照的使用方式

    我们知道「参照名称」有特殊的目的，通常用于「本地分支」、「远端分支」与「标签」等情境下，但事实上你可以建立任意数量的「自订参照名称」，只要通过 git update-ref 就可以自由建立「一般参照」。

    我企图建立一个名为 InitialCommit 的一般参照，并指向 Git 仓库中的第一个版本，请参见如下图的指令执行顺序，得知一般参照的建立方式：

```c++
        $ git log
        commit edcb4a0cc586f36e562572a496a7b738c867cfdc (HEAD -> newbranch1, f2e)
        Author: 徐浩 <zyuhao7@yeah.net>
        Date:   Thu Jul 4 22:33:24 2024 +0800

            Add b.txt in newbranch1

        commit 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        Author: 徐浩 <zyuhao7@yeah.net>
        Date:   Thu Jul 4 21:23:42 2024 +0800

            a.txt:set 1 as content

        commit 0dedb1d7654d7ff435f74f8cf45ac8ce724fcda9
        Author: 徐浩 <zyuhao7@yeah.net>
        Date:   Thu Jul 4 21:23:21 2024 +0800

            Initial commit

        $ git cat-file -p 0ded
        tree 382279b3d99e24b00b4a9b4822bf3dc11186ad4a
        author 徐浩 <zyuhao7@yeah.net> 1720099401 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720099401 +0800

        Initial commit

        $ git update-ref initialCommit 0ded
        $ cat .git/initialCommit
        0dedb1d7654d7ff435f74f8cf45ac8ce724fcda9    

```
    建立完成后，预设文件会放在 .git 资料夹下，且此时用「绝对名称」与「参照名称」都能存取特定 Git 物件的内容：

```c++
        $ git cat-file -p 0ded
        tree 382279b3d99e24b00b4a9b4822bf3dc11186ad4a
        author 徐浩 <zyuhao7@yeah.net> 1720099401 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720099401 +0800

        Initial commit

        $ git cat-file -p initialcommit
        tree 382279b3d99e24b00b4a9b4822bf3dc11186ad4a
        author 徐浩 <zyuhao7@yeah.net> 1720099401 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720099401 +0800

        Initial commit
    
PS: 参照名称可以指向任意 Git 物件，并没有限定非要 commit 物件不可。
```

    若要建立较为正式的参照名称，最好加上 refs/ 开头，例如：git update-ref refs/InitialCommit [object_id]。
    若要删除一般参照，则可以使用 -d 选项。如下图示：
```c++
        $ git update-ref -d initialcommit
            error: refusing to update ref with bad name 'initialcommit'

```

    显示所有参数的方式, 可以使用`git show-ref` 指令, 如下:
```c++
        $ git show-ref
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/heads/f2e
        95cb1da7bb878a08406b6e35efad16b70aa38b8b refs/heads/master
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/heads/newbranch1
        9c1a5ed2d064d25dae181b0163b01a63694c0dbf refs/heads/newbranch2
        9c1a5ed2d064d25dae181b0163b01a63694c0dbf refs/heads/newbranch3

        $ git update-ref refs/initialCommit 0ded

        $ git show-ref
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/heads/f2e
        95cb1da7bb878a08406b6e35efad16b70aa38b8b refs/heads/master
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/heads/newbranch1
        9c1a5ed2d064d25dae181b0163b01a63694c0dbf refs/heads/newbranch2
        9c1a5ed2d064d25dae181b0163b01a63694c0dbf refs/heads/newbranch3
        0dedb1d7654d7ff435f74f8cf45ac8ce724fcda9 refs/initialCommit
```
    若要建立与删除「符号参照」，可以参考如下图 git symbolic-ref 的用法。请自行看图说故事，理解之后，你真的会发现 Git 对于参照的用法非常灵活且强大。还有，执行 git show-ref 只会显示在 .git\refs 目录下的那些参照，而且不管是「一般参照」或「符号参照」都一样：

```c++
        $ git branch
        f2e
        master
        * newbranch1
        newbranch2
        newbranch3

        $ git cat-file -p f2e
        tree 3a1fdd64de8fc83e5ebd9cfd037b995bb594afa2
        parent 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        author 徐浩 <zyuhao7@yeah.net> 1720103604 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720103604 +0800

        Add b.txt in newbranch1

        $ git cat-file -p refs/heads/f2e
        tree 3a1fdd64de8fc83e5ebd9cfd037b995bb594afa2
        parent 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        author 徐浩 <zyuhao7@yeah.net> 1720103604 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720103604 +0800

        Add b.txt in newbranch1

        $ git symbolic-ref f2e-init2 refs/heads/f2e

       $ cat .git/refs/f2-init2
        ref: refs/heads/f2e 

        $ git show-ref
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/f2-init2
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/heads/f2e
        95cb1da7bb878a08406b6e35efad16b70aa38b8b refs/heads/master
        edcb4a0cc586f36e562572a496a7b738c867cfdc refs/heads/newbranch1
        9c1a5ed2d064d25dae181b0163b01a63694c0dbf refs/heads/newbranch2
        9c1a5ed2d064d25dae181b0163b01a63694c0dbf refs/heads/newbranch3
        0dedb1d7654d7ff435f74f8cf45ac8ce724fcda9 refs/initialCommit
```

### 今日小结
    git branch
    git log --pretty=oneline
    git log --oneline
    git cat-file -p [ref or object_id]
    git show [ref or object_id]
    git update-ref
    git symbolic-ref
    git show-ref