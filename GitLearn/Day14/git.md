# 第 14 天： Git for Windows 选项设定

## 关于 Git 指令列工具的选项设定

            $ git config --list
            diff.astextplain.textconv=astextplain
            filter.lfs.clean=git-lfs clean -- %f
            filter.lfs.smudge=git-lfs smudge -- %f
            filter.lfs.process=git-lfs filter-process
            filter.lfs.required=true
            http.sslbackend=openssl
            core.autocrlf=true
            core.fscache=true
            core.symlinks=false
            pull.rebase=false
            credential.helper=manager
            credential.https://dev.azure.com.usehttppath=true
            init.defaultbranch=master
            credential.https://gitee.com.provider=generic
            user.name=徐浩
            user.email=zyuhao7@yeah.net
            filter.lfs.clean=git-lfs clean -- %f
            filter.lfs.smudge=git-lfs smudge -- %f
            filter.lfs.process=git-lfs filter-process
            filter.lfs.required=true
            init.defaultbranch=master

## 储存 Git 选项设定的三个地方
1. 系统层级 ( --system ) (System-level configuration) (设定于整台电脑，适用于本机所有使用者的预设值).

            $ git config --list --system
            diff.astextplain.textconv=astextplain
            filter.lfs.clean=git-lfs clean -- %f
            filter.lfs.smudge=git-lfs smudge -- %f
            filter.lfs.process=git-lfs filter-process
            filter.lfs.required=true
            http.sslbackend=openssl
            http.sslcainfo=C:/Program Files/Git/mingw64/etc/ssl/certs/ca-bundle.crt
            core.autocrlf=true
            core.fscache=true
            core.symlinks=false
            pull.rebase=false
            credential.helper=manager
            credential.https://dev.azure.com.usehttppath=true
            init.defaultbranch=master

**Ps:  若要设定「系统层级」选项，请务必用【以系统管理员身分执行】的方式启用命令提示字元，然后再执行 git config 命令，才能写入正确的文件位置.**

2. 使用者层级 ( --global ) (User-level configuration) (设定于目前登入的使用者)
            $ git config --list --global
            credential.https://gitee.com.provider=generic
            user.name=徐浩
            user.email=zyuhao7@yeah.net
            filter.lfs.clean=git-lfs clean -- %f
            filter.lfs.smudge=git-lfs smudge -- %f
            filter.lfs.process=git-lfs filter-process
            filter.lfs.required=true
            init.defaultbranch=master
            credential.https://gitee.com/xu-haolongq/miscellaneous-notes.git.helper=wincred
            credential.https://gitee.com/xu-haolongq/miscellaneous-notes.git.username=Yoh
            credential.https://gitee.com/xu-haolongq/miscellaneous-notes.git.usehttppath=true
            core.autocrlf=false
            difftool.sourcetree.cmd=''
            mergetool.sourcetree.cmd=''
            mergetool.sourcetree.trustexitcode=true

             # 一般设置这两项.
             git config --global user.name "徐浩"
             git config --global user.email "zyuhao7@yeah.net"

3. 储存区层级 ( --local ) (Repository-level configuration) (设定于工作目录下的 .git\config 设定档中).

            $ git config --list --local
            core.repositoryformatversion=0
            core.filemode=false
            core.bare=false
            core.logallrefupdates=true
            core.symlinks=false
            core.ignorecase=true

## Git 选项设定的套用顺序
            1 先套用系统层级 (优先权最低)
            2 再套用使用者层级
            3 再套用储存区层级 (优先权最高)

            也就是说，你如果在系统层级曾经设定过 core.autocrlf 选项，然后在使用者层级又重新定义过一次，那么最终会套用的 core.autocrlf 选项值将会是「使用者层级」的设定值。

## 选项设定的操作方式
* 取得选项设定清单

                git config --list
                git config --list --system
                git config --list --global
                git config --list --local
                
* 取得特定选项值

              git config [config_section.config_name]

              git config user.name
              git config user.email

* 设定特定选项值
  
             git config [config_section.config_name] [config_value]

             git config user.name "xh"
             git config user.email "zyuhao7@yeah.net"

* 删除特定选项设定

             git config --unset --system [config_section.config_name]
             git config --unset --global [config_section.config_name]
             git config --unset --local  [config_section.config_name]

## 常用选项设定
 * 直接编辑设定档

              git config --edit --system
              git config --edit --global
              git config --edit --local

* 自动订正打错的参数

              git config --global help.autocorrect 1

* 启用消息顏色

             git config --system color.ui auto

* 自订 commit 消息范本
  

              git config --local commit.template "G:\git-commit-template.txt"

**今日小结**

            git config --list
            git config --list --system
            git config --list --global
            git config --list --local
            git config --edit --system
            git config --edit --global
            git config --edit --local
            git config [config_section.config_name]
            git config [config_section.config_name] [config_value]
            git config --unset --system [config_section.config_name]
            git config --unset --global [config_section.config_name]
            git config --unset --local [config_section.config_name]
            git config user.name
            git config user.email
            git config user.name "Will Huang"
            git config user.email "will@example.com"
            git config --global alias.co checkout
            git config --global alias.ci commit
            git config --global alias.st status
            git config --global alias.sts "status -s"
            git config --global alias.br branch
            git config --global alias.re remote
            git config --global alias.di diff
            git config --global alias.type "cat-file -t"
            git config --global alias.dump "cat-file -p"
            git config --global alias.lo "log --oneline"
            git config --global core.editor notepad.exe
            git config --global core.autocrlf true
            git config --global help.autocorrect 1
            git config --system color.ui auto
            git config --local commit.template "G:\git-commit-template.txt"