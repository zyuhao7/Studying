```bash
# 查看用户级别文件描述符限制的方法
$ ulimit -n

#可以通过如下方式将用户级别文件描述符设置为 max-file-num(临时)
$ ulimit -SHn max-file-number

# 内核模块和驱动程序, 都在 /proc/sys 文件系统下.
$sysctl -a               #查看所有这些内核参数.

/proc/sys/fs/epoll/max_user_watches  #一个用户能够往epoll内核事件中注册的事件的总量

#内核中网络模块的相关参数都位于 /proc/sys/net 目录下
```

### gdb 调试 ······
