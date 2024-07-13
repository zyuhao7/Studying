## 第 13 天：暂存工作目录与索引的变更状态
### 认识 git stash 指令
```c++
day-2024-7-13

    我们知道使用 Git 版控的时候，有区分「工作目录」与「索引」。
    工作目录里面会有你改到一半还没改完的文件 (尚未加入索引)，也有新增文件但还没加入的文件 (尚未加入索引)。
    而放在索引的资料，则是你打算通过 git commit 建立版本 (建立 commit 物件) 的内容.

    在 Git 里有个 git stash 指令，可以自动帮你把改写到一半的那些文件建立一个「特殊的版本」(也是一个 commit 物件)，
    我们称这些版本为 stash 版本，或你可以直接称他为「暂存版」.

    建立暂存版本
        我们手边改到一半的文件，可能会有以下状态：
        新增文件 (尚未列入追踪的文件) (untracked files)
        新增文件 (已经加入索引的文件) (tracked/staged files)
        修改文件 (尚未加入索引的文件) (tracked/unstaged files)
        修改文件 (已经加入索引的文件) (tracked/staged files)
        删除文件 (尚未加入索引的文件) (tracked/unstaged files)
        删除文件 (已经加入索引的文件) (tracked/staged files)
    
    若要将这些开发到一半的文件建立一个「暂存版」，你有两个选择：
        git stash 会将所有已列入追踪 (tracked) 的文件建立暂存版.
        git stash -u　会包括所有已追踪或未追踪的文件，全部都建立成暂存版.
    
ps:git stash 也可以写成 git stash save，两个指令的结果是一样的，只是 save 参数可以忽略不打而已。


    我们来看看一个简单的例子。我们先通过以下指令快速建立一个拥有两个版本的 Git 仓库与工作目录：
    mkdir git-stash-demo
    cd git-stash-demo   
    git init

    echo . > a.txt
    git add .
    git commit -m "Initial commit"

    echo 1 > a.txt
    git add .
    git commit -m "a.txt: set 1 as content"

    目前的「工作目录」是干净的，没有任何更新到一半的文件：
    $ git log
    commit 911a1d4f4bda4fb44fd91a08576b13a5d8d476e3 (HEAD -> master)
    Author: 徐浩 <zyuhao7@yeah.net>
    Date:   Sat Jul 13 21:30:22 2024 +0800

        a.txt: set 1 as content

    commit d6458e93b257bc81cfd004f89fe306237d77e616
    Author: 徐浩 <zyuhao7@yeah.net>
    Date:   Sat Jul 13 21:30:00 2024 +0800

        Inititial commit
    
    $ git status
    On branch master
    nothing to commit, working tree clean

    $ ls -l
    total 1
    -rw-r--r-- 1 徐浩 197121 1 Jul 13 21:30 a.txt

    接着我新增一个 b.txt，再将 a.txt 的内容改成 2，如下：
    $ cat a.txt
    1

    $ echo 2 > a.txt
    $ cat a.txt
    2

    $ echo TEST > b.txt

    $ dir
    a.txt  b.txt

    $ git status
    On branch master
    Changes not staged for commit:
    (use "git add <file>..." to update what will be committed)
    (use "git restore <file>..." to discard changes in working directory)
            modified:   a.txt

    Untracked files:
    (use "git add <file>..." to include in what will be committed)
            b.txt

    no changes added to commit (use "git add" and/or "git commit -a")

    现在我们用 git status 得出我们有两个文件有变更，一个是 a.txt 处于 "not staged" 状态，而 b.txt 则是 "untracked" 状态.

    这时，我们利用 git stash -u 即可将目前这些变更全部储存起来 (包含 untracked 文件),
    储存完毕后，这些变更全部都会被重置，新增的文件会被删除、修改的文件会被还原、删除的文件会被加回去，
    让我们目前在工作目录中所做的变更全部回复到 HEAD 状态。这就是 Stash 帮我们做的事。如下所示：

    $ git stash -u
    Saved working directory and index state WIP on master: 911a1d4 a.txt: set 1 as content

    $ git status
    On branch master
    nothing to commit, working tree clean

    在建立完成｢暂存版｣之后，Git 会顺便帮我们建立一个暂存版的「参考名称」，而且是「一般参考」,
    在 .git\refs\stash 储存的是一个 commit 物件的「绝对名称」:
    $ ls .git/refs -l
    total 1
    drwxr-xr-x 1 徐浩 197121  0 Jul 13 21:40 heads/
    -rw-r--r-- 1 徐浩 197121 41 Jul 13 21:40 stash
    drwxr-xr-x 1 徐浩 197121  0 Jul 13 21:29 tags/


    我们用 git cat-file -p stash 即可查出该物件的内容,
    这时你可以发现它其实就是个具有三个 parent (上层 commit 物件) 的 commit 物件：

        $ git cat-file -p stash
        tree 7b1ecdb76a31a8576acb22a8a35bbc773a9ec7cd
        parent 911a1d4f4bda4fb44fd91a08576b13a5d8d476e3
        parent 6d7311cc7f80df14e29f373a1f1bf8600eaac5e6
        parent c713a822c65149dbcf3735552ca78a43041097fa
        author 徐浩 <zyuhao7@yeah.net> 1720878012 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720878012 +0800

        WIP on master: 911a1d4 a.txt: set 1 as content

  有三个 parent commit 物件的意义就在于，这个特殊的暂存版是从另外三个版本合并进来的，然而这三个版本的内容,
  我们一样可以通过相同的指令显示其内容：

        $ git cat-file -p 911a
        tree 21a3711d5b4d4186d1d485ee2256f633c985eb73
        parent d6458e93b257bc81cfd004f89fe306237d77e616
        author 徐浩 <zyuhao7@yeah.net> 1720877422 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720877422 +0800

        a.txt: set 1 as content

        $ git cat-file -p 6d73
        tree 21a3711d5b4d4186d1d485ee2256f633c985eb73
        parent 911a1d4f4bda4fb44fd91a08576b13a5d8d476e3
        author 徐浩 <zyuhao7@yeah.net> 1720878012 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720878012 +0800

        index on master: 911a1d4 a.txt: set 1 as content

        $ git cat-file -p c713
        tree 48a4018b5178b9ce12d2dfe2dc07325c006d685b
        author 徐浩 <zyuhao7@yeah.net> 1720878012 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720878012 +0800

        untracked files on master: 911a1d4 a.txt: set 1 as content


   从上述执行结果你应该可以从「消息记录」的地方清楚看出这三个版本分別代表那些内容：
   1.原本工作目录的 HEAD 版本
   2.原本工作目录里所有追踪中的内容 (在索引中的内容)
   3.原本工作目录里所有未追踪的内容 (不在索引中的内容)

    也就是说，他把「原本工作目录的 HEAD 版本」先建立两个暂时的分支，这两个分支分別就是「原本工作目录里所有追踪中的内容」
    与「原本工作目录里所有未追踪的内容」之用，并在个別分支建立了一个版本以产生 commit 物件并且给予预设的 log 内容。
    最后把这三个分支，合并到一个「参照名称」为 stash 的版本（这也是个 commit 物件)。
    不仅如此，他还把整个「工作目录」强迫重置为 HEAD 版本，把这些变更与新增的文件都给还原，多的文件也会被移除。

    取回暂存版本
       由于「工作目录」已经被重置，所以变更都储存到 stash 这里，哪天如果你想要把这个暂存文件取回，
       就可以通过 git stash pop 重新「合并」回来。如下所示：

        $ git status
        On branch master
        nothing to commit, working tree clean

        $ git stash pop
        On branch master
        Changes not staged for commit:
        (use "git add <file>..." to update what will be committed)
        (use "git restore <file>..." to discard changes in working directory)
                modified:   a.txt

        Untracked files:
        (use "git add <file>..." to include in what will be committed)
                b.txt

        no changes added to commit (use "git add" and/or "git commit -a")
        Dropped refs/stash@{0} (613e3577034de65d37c018e76e1e39799edd5020)

    执行完毕后，所有当初的工作目录状态与索引状态都会被还原。事实上 Git 骨子里是通过「合并」的功能把这个名为 stash 的版本给合并回目前分支而已。
    最后，它还会自动将这个 stash 分支给删除，所以称它为【暂存版】非常贴切！

    建立多重暂存版
      Git 的 stash 暂存版可以不只一份，你也可以建立多份暂存档，以供后续使用。
      不过，在正常的开发情境下，通常不会有太多暂存版才对，会有这种情況发生，主要有两种可能：

      1.你的开发习惯太差，导致累积一堆可能用不到的暂存版。
      2.你老板或客戶「插单」的问题十分严重，经常改到一半就被迫插单。(这就是身为 IT 人的 BI 啊~~~XD) 
      (BI = Business Intelligence 或另一层意思... Well, you know....)

我们延续上一个例子，目前工作目录的状态应该是有两个文件有变化，我们用 git status -s 取得工作目录的状态 (其中 -s 代表显示精简版的状态)：
        
        $ git status -s
        M a.txt
        ?? b.txt

    现在，我们先建立第一个 stash 暂存版：

        $ git stash save -u
        Saved working directory and index state WIP on master: 911a1d4 a.txt: set 1 as content

    然后通过 git stash list 列出目前所有的 stash 清单，目前仅一份暂存版：

        $ git stash list
        stash@{0}: WIP on master: 911a1d4 a.txt: set 1 as content

  而且你可以看到建立暂存版之后，工作目录是干净的。此时我们在建立另一个 new.txt 文件，并且再次建立暂存版：

        $ git status -s
        $ echo 1 > new.txt

        $ git status -s
        ?? new.txt

        $ git stash save -u
        Saved working directory and index state WIP on master: 911a1d4 a.txt: set 1 as content

    我们在再一次 git stash list 就可以看到目前有两个版本：

        $ git stash list
        stash@{0}: WIP on master: 911a1d4 a.txt: set 1 as content
        stash@{1}: WIP on master: 911a1d4 a.txt: set 1 as content

    你应该会很纳闷，都没有自订的注解，过了几天不就忘记这两个暂存档各自的修改项目吗？
    没错，所以你可以自订「暂存版」的记录消息。我们通过 git stash save -u <message> 指令，就可自订暂存版的注解：

        $ git stash -h

        $ git stash pop
        Already up to date.
        On branch master
        Untracked files:
        (use "git add <file>..." to include in what will be committed)
                new.txt

        nothing added to commit but untracked files present (use "git add" to track)
        Dropped refs/stash@{0} (b9d551f386c0b9f62f9ab4d9ff0e3275477f43a2)

        $ git stash save -u "新增 new.txt 文件"
        Saved working directory and index state On master: 新增 new.txt 文件

        $ git stash list
        stash@{0}: On master: 新增 new.txt 文件
        stash@{1}: WIP on master: 911a1d4 a.txt: set 1 as content

  这时，如果你直接执行 git stash pop 的话，他会取回最近的一笔暂存版，也就是上述例子的 stash@{0} 这一项，并且把这一笔删除。
  另一种取回暂存版的方法是通过 git stash apply 指令，唯一差別则是取回该版本 (其实是执行合并动作) 后，该暂存版还会留在 stash 清单上。

  如果你想取回「特定一个暂存版」，你就必须在最后指名 stash id，例如 stash@{1} 这样的格式。
  例如如下范例，我使用 git stash apply "stash@{1}" 取回前一个暂存版，但保留这版在 stash 清单里：

        $ git stash list
        stash@{0}: On master: 新增 new.txt 文件
        stash@{1}: WIP on master: 911a1d4 a.txt: set 1 as content

        $ git stash apply "stash@{1}"
        On branch master
        Changes not staged for commit:
        (use "git add <file>..." to update what will be committed)
        (use "git restore <file>..." to discard changes in working directory)
                modified:   a.txt

        Untracked files:
        (use "git add <file>..." to include in what will be committed)
                b.txt

        no changes added to commit (use "git add" and/or "git commit -a")

        $ git stash list
        stash@{0}: On master: 新增 new.txt 文件
        stash@{1}: WIP on master: 911a1d4 a.txt: set 1 as content

  如果确定合并正确，你想删除 stash@{1} 的话，可以通过 git stash drop "stash@{1}" 将特定暂存版删除。

        $ git stash drop "stash@{1}"
        Dropped stash@{1} (035fdcd322c317809efb880b94bcf64db9270127)

        $ git stash list
        stash@{0}: On master: 新增 new.txt 文件

  如果想清理掉所有的暂存版, 直接下达 git stash clear 即可.
        
        $ git stash clear


今日小结:
    git stash
    git stash -u
    git stash save
    git stash save -u
    git stash list
    git stash pop
    git stash apply
    git stash pop "stash@{id}"
    git stash apply "stash@{id}"
    git stash drop "stash@{id}"
    git stash clear

```