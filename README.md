# Operating Systems - Project 2: Memory

## Basic Infomation:

### Members:
- Bilal Drndo
- Dželila Tinjak

### Files:
```
    .
    ├── long_sleeper.c         
    ├── memory_map_variation_1.c               
    ├── memory_map_variation_2.c
    └── README.md
```

*Note: Kali Linux will be used as the primary Operating System for all of the tasks*

### Outline:
In this project, we have created three c files that demonstrate the process of memory mapping and showed how memory acts upon different challenges that are brought upon it.

### Instructions for Compiling:
1. Make sure that You have installed a C compiler on Your Computer. If not, You can download it by following [this](https://itsourcecode.com/c-tuts/environment-setup-in-c-programming-language/) tutorial.
2. Open a new Terminal Window and change Your working directory to this project. Example: `cd /path/to/this/directory/`.
3. Compile the first program by typing in `gcc -o long_sleeper long_sleeper.c`.
4. Compile the second program by typing in `gcc -o memory_map_variation_1 memory_map_variation_1.c`.
5. Compile the second program by typing in `gcc -o memory_map_variation_2 memory_map_variation_2.c`.
4. Run the programs by typing in `./long_sleeper` & `./memory_map_variation_1` & `./memory_map_variation_2`.
5. Have Fun!

### Sources/Tutorials that we have used:
- https://linux.die.net/man/2/munmap
- https://www.tutorialspoint.com/unix_system_calls/mmap.htm
- https://www.baeldung.com/linux/process-memory-management
- https://dannyda.com/2021/01/31/how-to-use-ps-command-to-monitor-process-information-details-in-linux-debian-ubuntu-kali-linux-rhel-centos-etc/
- https://www.geeksforgeeks.org/proc-file-system-linux/

---

## Answers to Questions:

## Task 1:
***Write a simple C program that runs for a long duration, say, by pausing for user input or by sleeping. While the process is active, use the ps or any other similar command with suitable options, to measure the memory usage of the process. Specifically, measure the virtual memory size (VSZ) of the process, and the resident set size (RSS) of the process (which includes only the physical RAM pages allocated to the process). You should also be able to see the various pieces of the memory image of the process in the Linux proc file system, by accessing a suitable file in the proc filesystem.***

### Answer:
- Firstly, we created a file called `long_sleeper.c`, wrote a simple code script that runs infinitely using a `while()` loop with the `sleep()` call.
- After that we compiled the `long_sleeper.c` file and ran it.
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
- We saw that we have a process with id: `7617` with our current command running `long_sleeper`.
- After this, we opened another terminal file and run the following command: `ps -o vsz,rss -p 7617` to check the `virtual memory size (VSZ)` and the `resident set size (RSS)` where we get the following response:
```bash
┌──(bilaldrndo㉿kali)-[~/Desktop/OS/os_project_2]
└─$ ps -o vsz,rss -p 7617
        VSZ   RSS
  407972896   800
```
- We saw that the value of `VSZ` is `407972896 Bytes` and value of `RSS` is `800 Bytes`.
- After this, we opened a new terminal window to check out various pieces of memory image of this process id in the proc file system by running the following command in the terminal: `cat /proc/7617/maps` after we got the following output:
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
***Now, add code to your simple program to memory map an empty page from the OS. For this program, it makes sense to ask the OS for an anonymous page (since it is not backed by any file on disk) and in private mode (since you are not sharing this page with other processes). Do not do anything else with the memory mapped page. Now, pause your program again and measure the virtual and physical memory consumed by your process. What has changed, and how do you explain it?***

### Answer:
- Firstly, we copied the code from `long_sleeper.c` and created a new file called `memory_map_variation_1.c` where we pasted the code and added also some extra code into the `while()` loop that memory maps an empty page. 
- We compiled and ran the program. After that ran the command `ps -e o comm,vsz,rss` to get a list of all processes, their names as well their `VSZ` and `RSS` values just to save some time.
- We saw that the `memory_map_variation_1` process had a `VSZ` value of `407973120 Bytes` and an `RSS` value of `800 Bytes`. 
- The `VSZ` value has changed but not by a major margin but the RSS value has stayed the same. After doing some research  and digging through documentation, we concluded that the `RSS` value hasn't changed because the new program is nearly the same as the old one since, in the "eyes" of the computer, it memory maps an empty page.

## Task 3:
***Finally, write some data into your memory mapped page and measure the virtual and physical memory usage again. Explain what you find.***

### Answer:
- We copied the code from `memory_map_variation_1.c` and create a new file called `memory_map_variation_2.c` where we pasted the code and added one extra line of code near the end of `while()` loop that inserts dummy "Hello World" data into our memory maped page.
- We compiled and ran the program. We ran the `ps -e o comm,vsz,rss` command to get a list of all processes again.
- We saw that the `memory_map_variation_2` process has a `VSZ` value of `407972992 Bytes` and an `RSS` value of `1344 Bytes`. 
- Again, the `VSZ` value hasn't been changed by a major margin but the `RSS` value has been changed because we have added one more extra part to our code and we are writing some dummy data in our memory which requires from our system to allocate more memory.

## Extra:
- Just out of curiosity we wanted to run all of the 3 programs silmontaneously and measure their `RSS` values. 
- After we ran the programs and the `ps` command with the process IDs, we got this response:
```bash
┌──(bilaldrndo㉿kali)-[~/Desktop/OS/os_project_2]
└─$ ps -o pid,%mem,vsz,rss,comm -p 4202,4206,4222
  PID %MEM      VSZ    RSS COMM
 4202  0.0 407972896   1248 ./long_sleeper
 4206  0.0 407973024   1248 ./memory_map_variation_1
 4222  0.0 407973024   1376 ./memory_map_variation_2
``` 
- Based on the terminal repose, we saw that the `RSS` values of `./long_sleeper` and `./memory_map_variation_1` stayed the same but the `RSS` value of `./memory_map_variation_2` showed up to be a bit bigger than the other ones. We ran the `ps` command a few more times, we saw that the `RSS` value of `.memory_map_variation_2` constantly kept increasing. Why? Because the program constanlty writes extra data into memory every few seconds and that is why more memory is needed to be allocated on each new `while()` loop iteration.