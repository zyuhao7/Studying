# Linux高性能服务器编程

### 第三篇　高性能服务器优化与监测

#### 第16章 服务器调制、调试和测试

查看用户级文件描述符上限的方法:

```bash
$ ulimit -n
```

修改系统文件描述符的限制， 可使用:

```bash	
$ sysctl -w fs.file-max=max_file_number
```

要永久更改系统级文件描述符限制，则需要在 /etc/sysctl.conf 文件中添加如下一项:

```bash
fs.file-max=max_file_number # 然后执行 sysctl -p 使指令生效
```



```bash
$ sysctl -a # 查看所有内核参数
```



#### gdb调试

##### 1. 用 gdb 调试多进程

如果一个进程通过 fork 系统调用创建了子进程， gdb会继续调试原来的进程， 子进程则正常运行。那么该如何调试子进程呢？常用方法有如下两种。

**① 单独调试子进程**

子进程从本质上说也是一个进程，因此我们可以用通用的 gdb 调试方法来调试它。举例来说，如果要调试代码清单 15-2描述的 CGI进程池服务器的某一个子进程，则我们可以先运行服务器，然后找到目标子进程的 PID，再将其附加(attach)到 gdb 调试器上。

**②使用调试器选项 follow-fork-mode**

gdb 调试器的选项 follow-fork-mode 允许我们选择程序在执行 fork 系统调用后是继续调试父进程还是调试子进程。其用法如下:

```bash
$(gdb)set follow-fork-mode mode
```

```bash
$ gdb ./cgisrv
(gdb)set follow-fork-mode child
(gdb)b processpool.h:264
Breakpoint l at 0x8049787:fle processpool.h, line 264.(gdb)r127.0.0.1 12345
Starting program: /home/shuang/codes/pool process/cgisrv 127.0.0.1 12345INew process 4148]
send request to child 0 
[Switching to process 4148]
Breakpoint 1,processpool<cgi conn>::run child (this=0x804c008) at processpool.h:264
264userslsockfdl.process();Missing separate debuginfos, use: debuginfo install glibc-2.14.90-24.fc16.6.i686

(gdb)bt
#0 processpool<cgi conn>::run child (this=0x804c008) at processpool.h:264
#1 0x08049lfe in processpool<cgi conn>::run (this.0x804c008) at processpool.h
#2 0x08048ef9 in main(argc=3, argv-0xbffff4e4) at main.cpp:138
(gdb)
```

##### 2. 用 gdb调试多线程程序

**gdb 有一组命令可辅助多线程程序的调试**。下面我们仅列举其中常用的一些:

□ **info threads**，显示当前可调试的所有线程。gdb 会为每个线程分配一个ID，我们可以使用这个 ID 来操作对应的线程。 ID 前面有“*”号的线程是当前被调试的线程。

□ **thread ID**，调试目标 ID 指定的线程。
		□**set scheduler-locking[ofon|step]**。调试多线程程序时，默认除了被调试的线程在执行外，其他线程也在继续执行，但有的时候我们希望只让被调试的线程运行。这可以通过这个命令来实现。该命令设置 scheducr-locking的值:**of**表示不锁定任何线程，即所有线程都可以继续执行，这是默认值;**on**表示只有当前被调试的线程会继续执行;**step** 表示在单步执行的时候，只有当前线程会执行。

```bash
$ gdb ./websrv
(gdb)b main.cpp:130 /*设置父线程中的断点 */
Breakpoint lat 0x80498d3:file main.cpp,line 130.
(gdb)b threadpool.h:105 /*设置子线程中的断点 */
Breakpoint 2 at 0x804a10b:file threadpool.h, line 105.
(gdb)r 127.0.0.1 12345
Starting program: /home/webtop/codes/pool thread/websrv 127.0.0.1 12345
[Thread debugging using libthread db enabled]
Using host libthread db library "/lib/libthread db.so,1"
create the 0th thread
[New Thread 0xb7fe1b40)(LWP 5756)]

/*从另一个终端使用 teinet 127.0.0.1 12345 来连接服务器并发送一些数据，调试器就按照我们预期的，在断点处暂停 */
Breakpoint 1,main(argc=3,argv-0xbffff4e4) at main.cpp:130
130 						if(users[sockfd].read())
(gdb)info threads /*查看线程信息。当前被调试的是主线程，其 ID为1 */
Id Target Id  			Frame
2  Thread 0xb7fe1b40   (Lwp 5756)"websrv" 0x00111416 in __kernel_vsyscall ()

*1 Thread 0xb7fe3700   (Lwp 5753)"websrv" main (argc 3, argv-0xbffff4e4) at main.cpp:130
(gdb) set scheduler-locking on /*不执行其他线程，锁定调试对象 */
(gdb)n /*下面的操作都将执行父线程的代码*/
132   			pool->append(users + sockfd);
(gdb)n
103			for(int i = 0; i < number; i++)
(gdb)
94		while(true)
(gdb)
96			int number = epoll_wait( epollfd, eventS, MAX_EVENT_NUMBER, -1 );
(gdb)

Program received signal SIGINT, Interrupt.
0x00111416 in __kernel__vsyscall()
(gdb) thread 2 /*将调试切换到子线程，其ID为2*/
[Switching to thread 2(thread 0xb7felb40(LwP 5756))]
#0 0x00111416 in __kernel__vsyscall()
(gdb) bt /*显示子线程的调用棧 */
#0 0x00111416 in __kernel__vsyscall()
#1 0x44d91c05 in sem_wait@@GLIBc_2.1 () from /lib/libpthread.so.0
#2 0x08049aff in sem::wait(this=0x804e034)at locker.h:24
#3 0x0804a0db in threadpool<http_conn>::run (this 0x804e008) at threadpool.h:98
#4 0x08049f8f in threadpool<http_conn>::worker (arg=0x804e008) at threadpool.h:89
#5 0x44d8bcd3 in start_thread ()from /lib/libpthread.so.0
#6 0x44cc8a2e in clone()from /lib/libc.so.6
(gdb) n /*下面的操作都将执行子线程的代码 */
Single stepping until exit from function __kernel_vsyscal1.
which has no line number information.
0x44d91c05 in sem wait@@GLIBc_2.1 () from /lib/libpthread.so.0
(gdb)
```

关于调试进程池和线程池程序的一个不错的方法，是先将池中的进程个数或线程个数减少至 1，以观察程序的逻辑是否正确，然后逐步增加进程或线程的数量，以调试进程或线程的同步是否正确。

#### 压力测试

压力测试程序有很多种实现方式，比如 I0 复用方式，多线程、多进程并发编程方式以及这些方式的结合使用。不过，单纯的IO复用方式的施压程度是最高的，因为线程和进程的调度本身也是要占用一定 CPU 时间的。因此，我们将使用 **epoll 来实现一个通用的服务器压力测试程序**:

.....等实现完15.6的用线程池实现的web服务器之后测试。