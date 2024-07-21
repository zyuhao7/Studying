# 第 15 天：标签 - 标记版本控制过程中的重要事件

## 关于标签 (Tag) 的基本概念
        基本上，标签的用途就是用来标记某一个「版本」或称为「commit 物件」，以一个「好记的名称」来帮助我们记忆【某个】版本。
        Git 标签 (Tag) 拥有两种型态，这两种类型分別是：

            轻量标签 (lightweight tag)
            标示标签 (annotated tag)


## 了解轻量标签 (lightweight tag) 的使用方式
        $ git log -1
        commit 95cb1da7bb878a08406b6e35efad16b70aa38b8b (HEAD -> master)
        Author: 徐浩 <zyuhao7@yeah.net>
        Date:   Thu Jul 4 21:30:58 2024 +0800

            Create b.txt with content master in the master branch

        $ git tag
        $ git tag 1.0.0-alpha
        
        $ dir .git/refs/tags
        1.0.0-alpha

        $ cat .git/refs/tags/1.0.0-alpha
        95cb1da7bb878a08406b6e35efad16b70aa38b8b

**Ps：所有在 .git\refs\ 下的文件都是个「参考名称」.**

    大致的使用说明如下:
        列出所有标签：git tag
        建立轻量标签：git tag [tagname]
        删除轻量标签：git tag [tagname] -d

    如果我们想看这个「轻量标签」的内容，我们可以通过 git cat-file -p [tagname] 取得。如果我们想看这个「轻量标签」的物件类型，可以通过 git cat-file -t [tagname] 取得.

        $ git cat-file -p 1.0.0-alpha
        tree 5bd5c169e4ac245d128d71460648c61fca825b6c
        parent 2afb5aba0f210448f7ae3e48bc9b20b320987cce
        author 徐浩 <zyuhao7@yeah.net> 1720099858 +0800
        committer 徐浩 <zyuhao7@yeah.net> 1720099858 +0800

        Create b.txt with content master in the master branch

        $ git cat-file -t 1.0.0-alpha
        commit

---
**Ps: 轻量标签不是个 Git 物件，所以我们从上图可以看出，该 Tag 名称取得的是 commit 物件的内容，而且该名称所查出的物件类型是 commit 物件.**

## 了解标示标签 (annotated tag) 的使用方式
        $ git log -1
        commit 95cb1da7bb878a08406b6e35efad16b70aa38b8b (HEAD -> master)
        Author: 徐浩 <zyuhao7@yeah.net>
        Date:   Thu Jul 4 21:30:58 2024 +0800

            Create b.txt with content master in the master branch
        
        $ git tag
        1.0.0-alpha

        $ git tag 1.0.0-beta -a -m "Beta Version"

        $ git tag
        1.0.0-alpha
        1.0.0-beta

        $ git cat-file -p 1.0.0-beta
        object 95cb1da7bb878a08406b6e35efad16b70aa38b8b
        type commit
        tag 1.0.0-beta
        tagger 徐浩 <zyuhao7@yeah.net> 1721563756 +0800

        Beta Version

        $ git cat-file -t 1.0.0-beta
        tag
---
这里跟「轻量标签」有些不一样的地方：
        
    1. 当我们执行 git tag 列出所有标签时, 所有标签都会混在一起, 看不出标签的类型.
    2. 建立 [标示标签] 要加上 -a 参数.
    3. 建立 [标示标签] 一定要加上 [版本信息], 跟执行 git commit 一样有 -m 参数可用.
    4. 但我们执行 git cat-file -p 1.0.0-beta时, 可以看出这个物件内容跟 commit物件稍有不同.
    5. 但我们执行 git cat-file -p 1.0.0-beta时, 可以从 type 看出上一行 object 的物件类型,这代表你可以把任何 Git 物件建立成一个标签物件.
    6. 当我们执行 git cat-file -t 1.0.0-beta时, 得到的是 tag 物件类型.


**预设 git tag [tagname] -a 会将当前的 HEAD 版本建立成 [标签物件], 如果要将其他特定物件建立为标签的用法为 git tag [tagname] [object_id].**


### 今日小结
        git tag
        git tag [tagname]
        git tag [tagname] -a
        git tag [tagname] -d







