# ludtm
Linux User Dump Test Module

```sh
# echo write_weired_area | ./ludtm
Child PID is 1149461
write_weired_area

ulimit -c unlimited && LD_SHOW_AUXV=1 LD_PRELOAD=/lib/aarch64-linux-gnu/libSegFault.so ./ludtm write_weired_area

AT_SYSINFO_EHDR:      0x7f9274f000
AT_??? (0x33): 0x1270
AT_HWCAP:             887
AT_PAGESZ:            4096
AT_CLKTCK:            100
AT_PHDR:              0x5569b10040
AT_PHENT:             56
AT_PHNUM:             9
AT_BASE:              0x7f9271f000
AT_FLAGS:             0x0
AT_ENTRY:             0x5569b10f24
AT_UID:               0
AT_EUID:              0
AT_GID:               0
AT_EGID:              0
AT_SECURE:            0
AT_RANDOM:            0x7fdf69b8b8
AT_HWCAP2:            0x0
AT_EXECFN:            ./ludtm
AT_PLATFORM:          aarch64
Child PID is 1149464
Do write_weired_area
*** Segmentation fault

Backtrace:
./ludtm(+0x128c)[0x5569b1128c]
./ludtm(+0x11b4)[0x5569b111b4]
./ludtm(+0x19d0)[0x5569b119d0]
/lib/aarch64-linux-gnu/libc.so.6(__libc_start_main+0xe8)[0x7f92573e18]
./ludtm(+0xf58)[0x5569b10f58]

Memory map:

5569b10000-5569b13000 r-xp 00000000 b3:02 5594                           /home/kim/ludtm/ludtm
5569b22000-5569b23000 r--p 00002000 b3:02 5594                           /home/kim/ludtm/ludtm
5569b23000-5569b24000 rw-p 00003000 b3:02 5594                           /home/kim/ludtm/ludtm
55a0d38000-55a0d59000 rw-p 00000000 00:00 0                              [heap]
7f9252f000-7f92542000 r-xp 00000000 b3:02 7269                           /usr/lib/aarch64-linux-gnu/libgcc_s.so.1
7f92542000-7f92551000 ---p 00013000 b3:02 7269                           /usr/lib/aarch64-linux-gnu/libgcc_s.so.1
7f92551000-7f92552000 r--p 00012000 b3:02 7269                           /usr/lib/aarch64-linux-gnu/libgcc_s.so.1
7f92552000-7f92553000 rw-p 00013000 b3:02 7269                           /usr/lib/aarch64-linux-gnu/libgcc_s.so.1
7f92553000-7f926b0000 r-xp 00000000 b3:02 7127                           /usr/lib/aarch64-linux-gnu/libc-2.31.so
7f926b0000-7f926bf000 ---p 0015d000 b3:02 7127                           /usr/lib/aarch64-linux-gnu/libc-2.31.so
7f926bf000-7f926c3000 r--p 0015c000 b3:02 7127                           /usr/lib/aarch64-linux-gnu/libc-2.31.so
7f926c3000-7f926c5000 rw-p 00160000 b3:02 7127                           /usr/lib/aarch64-linux-gnu/libc-2.31.so
7f926c5000-7f926c8000 rw-p 00000000 00:00 0
7f926c8000-7f926e4000 r-xp 00000000 b3:02 7605                           /usr/lib/aarch64-linux-gnu/libpthread-2.31.so
7f926e4000-7f926f3000 ---p 0001c000 b3:02 7605                           /usr/lib/aarch64-linux-gnu/libpthread-2.31.so
7f926f3000-7f926f4000 r--p 0001b000 b3:02 7605                           /usr/lib/aarch64-linux-gnu/libpthread-2.31.so
7f926f4000-7f926f5000 rw-p 0001c000 b3:02 7605                           /usr/lib/aarch64-linux-gnu/libpthread-2.31.so
7f926f5000-7f926f9000 rw-p 00000000 00:00 0
7f9270c000-7f9270e000 r-xp 00000000 b3:02 7021                           /usr/lib/aarch64-linux-gnu/libSegFault.so
7f9270e000-7f9271d000 ---p 00002000 b3:02 7021                           /usr/lib/aarch64-linux-gnu/libSegFault.so
7f9271d000-7f9271e000 r--p 00001000 b3:02 7021                           /usr/lib/aarch64-linux-gnu/libSegFault.so
7f9271e000-7f9271f000 rw-p 00002000 b3:02 7021                           /usr/lib/aarch64-linux-gnu/libSegFault.so
7f9271f000-7f92741000 r-xp 00000000 b3:02 6950                           /usr/lib/aarch64-linux-gnu/ld-2.31.so
7f92749000-7f9274d000 rw-p 00000000 00:00 0
7f9274d000-7f9274f000 r--p 00000000 00:00 0                              [vvar]
7f9274f000-7f92750000 r-xp 00000000 00:00 0                              [vdso]
7f92750000-7f92751000 r--p 00021000 b3:02 6950                           /usr/lib/aarch64-linux-gnu/ld-2.31.so
7f92751000-7f92753000 rw-p 00022000 b3:02 6950                           /usr/lib/aarch64-linux-gnu/ld-2.31.so
7fdf67c000-7fdf69d000 rw-p 00000000 00:00 0                              [stack]
killed by signal 11
AT_SYSINFO_EHDR:      0x7f853fe000
AT_??? (0x33): 0x1270
AT_HWCAP:             887
AT_PAGESZ:            4096
AT_CLKTCK:            100
AT_PHDR:              0x55953c0040
AT_PHENT:             56
AT_PHNUM:             9
AT_BASE:              0x7f853ce000
AT_FLAGS:             0x0
AT_ENTRY:             0x55953c4238
AT_UID:               0
AT_EUID:              0
AT_GID:               0
AT_EGID:              0
AT_SECURE:            0
AT_RANDOM:            0x7ff280eb78
AT_HWCAP2:            0x0
AT_EXECFN:            /bin/sh
AT_PLATFORM:          aarch64
AT_SYSINFO_EHDR:      0x7f9e695000
AT_??? (0x33): 0x1270
AT_HWCAP:             887
AT_PAGESZ:            4096
AT_CLKTCK:            100
AT_PHDR:              0x5573b50040
AT_PHENT:             56
AT_PHNUM:             9
AT_BASE:              0x7f9e665000
AT_FLAGS:             0x0
AT_ENTRY:             0x5573b55780
AT_UID:               0
AT_EUID:              0
AT_GID:               0
AT_EGID:              0
AT_SECURE:            0
AT_RANDOM:            0x7fc16cb368
AT_HWCAP2:            0x0
AT_EXECFN:            /usr/bin/ls
AT_PLATFORM:          aarch64
-rw------- 1 root root 420K  8월  7 01:34 /var/crash/core-ludtm.1149434.raspberrypi.1691339675
```

```
$ gdb ludtm -c /var/crash/core-ludtm.1149434.raspberrypi.1691339675

Core was generated by `./ludtm write_weired_area'.
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x0000005583ca128c in write_weired_area () at ludtm.c:84
84              *(p + 0xffffffff) = 12345678;
(gdb) bt
#0  0x0000005583ca128c in write_weired_area () at ludtm.c:84
#1  0x0000005583ca11b4 in make_coredump (buf=0x7fc2561837 "write_weired_area") at ludtm.c:55
#2  0x0000005583ca19c8 in main (argc=2, argv=0x7fc25613b8) at ludtm.c:297
```
