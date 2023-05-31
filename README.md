### Disclaimer: I am using Kali Linux as my primary operating system for this project

## Task 1:
Write a simple C program that runs for a long duration, say, by pausing for user input or by sleeping. While the process is active, use the ps or any other similar command with suitable options, to measure the memory usage of the process. Specifically, measure the virtual memory size (VSZ) of the process, and the resident set size (RSS) of the process (which includes only the physical RAM pages allocated to the process). You should also be able to see the various pieces of the memory image of the process in the Linux proc file system, by accessing a suitable file in the proc filesystem.

### Answers:
- Firstly, we created a file called `long_sleeper.c`, wrote some simple code in it to run infinitely using a `while()` loop with the `sleep()` call.
- After that we compiled the `long_sleeper.c` file and ran it and the program started running normaly.
- After that, we opened another terminal window in the same directory and ran the `ps -e` command. We got the following output:
```bash
┌──(bilaldrndo㉿kali)-[~/Desktop/OS/os_project_2]
└─$ ps -e
   PID TTY          TIME CMD
      1 ?        00:00:00 systemd
      2 ?        00:00:00 kthreadd
      3 ?        00:00:00 rcu_gp
      .
      .
   7617 pts/0    00:00:00 long_sleeper

      .
      .
   7651 pts/1    00:00:00 zsh
   7759 ?        00:00:00 kworker/1:0-mm_percpu_wq
   8549 pts/1    00:00:00 ps
```
- As you can see, on the 12th line, we have a process with id: `7617` with our current command running `long_sleeper`.
- After this, we are gonna open another terminal file and run the following command: `ps -o vsz,rss -p 7617` to check the virtual memory size (VSZ) and the resident set size (RSS) where we get the following response:
```bash
┌──(bilaldrndo㉿kali)-[~/Desktop/OS/os_project_2]
└─$ ps -o vsz,rss -p 7617
   VSZ   RSS
  2192   752
```
- We can see from here that the value of `VSZ` is `2192 Bytes` and value of `RSS` is `752 Bytes`.
- After this, we are gonna open a new terminal window to see various pieces of memory image in the proc file system by running the following command in the terminal: `cat /proc/7617/maps` and will get the following output:
```bash
┌──(bilaldrndo㉿kali)-[~/Desktop/OS/os_project_2]
└─$ cat /proc/7617/maps
aaaab8020000-aaaab8021000 r-xp 00000000 fe:02 1439002                    /home/bilaldrndo/Desktop/OS/os_project_2/long_sleeper
aaaab803f000-aaaab8040000 r--p 0000f000 fe:02 1439002                    /home/bilaldrndo/Desktop/OS/os_project_2/long_sleeper
aaaab8040000-aaaab8041000 rw-p 00010000 fe:02 1439002                    /home/bilaldrndo/Desktop/OS/os_project_2/long_sleeper
aaaae0f5b000-aaaae0f7c000 rw-p 00000000 00:00 0                          [heap]
ffff88530000-ffff886b8000 r-xp 00000000 fe:02 1569814                    /usr/lib/aarch64-linux-gnu/libc.so.6
ffff886b8000-ffff886cc000 ---p 00188000 fe:02 1569814                    /usr/lib/aarch64-linux-gnu/libc.so.6
ffff886cc000-ffff886d0000 r--p 0018c000 fe:02 1569814                    /usr/lib/aarch64-linux-gnu/libc.so.6
ffff886d0000-ffff886d2000 rw-p 00190000 fe:02 1569814                    /usr/lib/aarch64-linux-gnu/libc.so.6
ffff886d2000-ffff886df000 rw-p 00000000 00:00 0 
ffff886fa000-ffff88721000 r-xp 00000000 fe:02 1569810                    /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
ffff88733000-ffff88735000 rw-p 00000000 00:00 0 
ffff88735000-ffff88737000 r--p 00000000 00:00 0                          [vvar]
ffff88737000-ffff88738000 r-xp 00000000 00:00 0                          [vdso]
ffff88738000-ffff8873a000 r--p 0002e000 fe:02 1569810                    /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
ffff8873a000-ffff8873c000 rw-p 00030000 fe:02 1569810                    /usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1
ffffc2ec2000-ffffc2ee3000 rw-p 00000000 00:00 0                          [stack]
```

## Task 2:
Now, add code to your simple program to memory map an empty page from the OS. For this program, it makes sense to ask the OS for an anonymous page (since it is not backed by any file on disk) and in private mode (since you are not sharing this page with other processes). Do not do anything else with the memory mapped page. Now, pause your program again and measure the virtual and physical memory consumed by your process. What has changed, and how do you explain it?

- Firstly, we are gonna copy the code from `long_sleeper.c` and create a new file called `memory_map_variation_1.c` 