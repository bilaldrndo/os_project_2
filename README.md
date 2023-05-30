## Task 1:
Write a simple C program that runs for a long duration, say, by pausing for user input or by sleeping. While the process is active, use the ps or any other similar command with suitable options, to measure the memory usage of the process. Specifically, measure the virtual memory size (VSZ) of the process, and the resident set size (RSS) of the process (which includes only the physical RAM pages allocated to the process). You should also be able to see the various pieces of the memory image of the process in the Linux proc file system, by accessing a suitable file in the proc filesystem.

### Answers:
- Firstly, we created a file called `long_sleeper.c`, wrote some simple code in it to run infinitely using a `while()` loop with the `sleep()` call.
- After that we compiled the `long_sleeper.c` file and ran it and the program started running normaly.
- After that, we opened another terminal window in the same directory and ran the `ps` command. We got the following output:
```bash
❯ ps
  PID TTY           TIME CMD
15164 ttys000    0:01.03 -zsh
15175 ttys000    0:00.00 -zsh
15278 ttys000    0:00.00 -zsh
15279 ttys000    0:00.00 -zsh
15281 ttys000    0:00.02 /Users/bilaldrndo/.cache/gitstatus/gitstatusd-darwin-arm64 -G v1.5.
 1530 ttys002    1:08.12 /Applications/Xcode.app/Contents/Developer/usr/bin/xcdevice observe
15497 ttys003    0:00.57 /bin/zsh -il
15508 ttys003    0:00.00 /bin/zsh -il
15607 ttys003    0:00.00 /bin/zsh -il
15609 ttys003    0:00.00 /bin/zsh -il
15610 ttys003    0:00.01 /Users/bilaldrndo/.cache/gitstatus/gitstatusd-darwin-arm64 -G v1.5.
15646 ttys003    0:00.00 ./long_sleeper
15662 ttys005    0:00.22 /bin/zsh -il
15673 ttys005    0:00.00 /bin/zsh -il
15770 ttys005    0:00.00 /bin/zsh -il
15772 ttys005    0:00.00 /bin/zsh -il
15773 ttys005    0:00.00 /Users/bilaldrndo/.cache/gitstatus/gitstatusd-darwin-arm64 -G v1.5.
```
- As you can see, on the 12th line, we have a process with id: `15646` with our current command running `./long_sleeper`.
- After this, we are gonna open another terminal file and run the following command: `ps -o vsz,rss -p 15646` to check the virtual memory size (VSZ) and the resident set size (RSS) where we get the following response:
```bash
❯ ps -o vsz,rss -p 15646
     VSZ    RSS
407972896    800
```
- We can see from here that the value of `VSZ` is `407972896 Bytes` or `0.38 Gigabytes` and value of `RSS` is `800 Bytes`.
- After this, we are gonna open a new terminal window to see various pieces of memory image in the proc file system by running the following command in the terminal: `cat /proc/15646/maps`. Since I am using a Mac, 

