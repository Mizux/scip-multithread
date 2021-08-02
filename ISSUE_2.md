# Investigation

Upon crash (in DEBUG an assert is raised)

note: You can control the verbosity of the frame see [.gdbinit](.gdbinit)


```gdb
(gdb) bt
#0  __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:50
#1  0x00007ffff7abe537 in __GI_abort () at abort.c:79
#2  0x00007ffff7abe40f in __assert_fail_base (fmt=0x7ffff7c27128 "%s%s%s:%u: %s%sAssertion `%s' failed.\n%n", assertion=0x555556147030 "idx >= 0 && idx < nconcsolvers", file=0x555556146ce0 "/usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c", line=518, function=<optimized out>) at assert.c:92
#3  0x00007ffff7acd662 in __GI___assert_fail (assertion=0x555556147030 "idx >= 0 && idx < nconcsolvers", file=0x555556146ce0 "/usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c", line=518, function=0x555556147340 <__PRETTY_FUNCTION__.1> "SCIPconcurrentSolve") at assert.c:101
#4  0x0000555555f62d19 in SCIPconcurrentSolve (scip=0x5555561f6eb0) at /usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c:518
#5  0x00005555558fbf28 in SCIPsolveConcurrent (scip=0x5555561f6eb0) at /usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/scip_solve.c:3043
#6  0x0000555555558eed in main () at /usr/local/google/home/corentinl/dev/scip-multithread/Foo/src/main.cpp:120
```

Full back-trace

```gdb
(gdb) bt full
#0  __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:50
        set = {__val = {
            0,
            140737348986476,
            8517419008,
            93825035494240,
            93825035494341,
            93825035494240,
            93825035494240,
            93825035494419,
            93825035494540,
            93825035494240,
            93825035494540,
            0,
            0,
            0,
            0,
            0
          }}
        pid = <optimized out>
        tid = <optimized out>
        ret = <optimized out>
#1  0x00007ffff7abe537 in __GI_abort () at abort.c:79
        save_stage = 1
        act = {__sigaction_handler = {sa_handler = 0x555557e96360, sa_sigaction = 0x555557e96360}, sa_mask = {__val = {
              0,
              93825035494240,
              179,
              0,
              0,
              0,
              21474836480,
              140737488346544,
              140737488346368,
              140737350118352,
              140737350103336,
              0,
              15714818247034364928,
              140737350086616,
              140737354117120,
              140737350103336
            }}, sa_flags = 1444179168, sa_restorer = 0x206}
        sigs = {__val = {
            32,
            0 <repeats 15 times>
          }}
#2  0x00007ffff7abe40f in __assert_fail_base (fmt=0x7ffff7c27128 "%s%s%s:%u: %s%sAssertion `%s' failed.\n%n", assertion=0x555556147030 "idx >= 0 && idx < nconcsolvers", file=0x555556146ce0 "/usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c", line=518, function=<optimized out>) at assert.c:92
        str = 0x555557e96360 ""
        total = 4096
#3  0x00007ffff7acd662 in __GI___assert_fail (assertion=0x555556147030 "idx >= 0 && idx < nconcsolvers", file=0x555556146ce0 "/usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c", line=518, function=0x555556147340 <__PRETTY_FUNCTION__.1> "SCIPconcurrentSolve") at assert.c:101
No locals.
#4  0x0000555555f62d19 in SCIPconcurrentSolve (scip=0x5555561f6eb0) at /usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c:518
        syncstore = 0x55555621ad40
        idx = -1
        jobid = 1
        i = 16
        retcode = SCIP_OKAY
        concsolvers = 0x555558327350
        nconcsolvers = 16
        __PRETTY_FUNCTION__ = "SCIPconcurrentSolve"
#5  0x00005555558fbf28 in SCIPsolveConcurrent (scip=0x5555561f6eb0) at /usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/scip_solve.c:3043
        retcode = 1444922816
        i = 16
        rndgen = 0x0
        minnthreads = 1
        maxnthreads = 16
        __PRETTY_FUNCTION__ = "SCIPsolveConcurrent"
#6  0x0000555555558eed in main () at /usr/local/google/home/corentinl/dev/scip-multithread/Foo/src/main.cpp:120
        scip_ = 0x5555561f6eb0
        x_ = 0x5555563663f8
        y_ = 0x5555563665c8
        z_ = 0x555556366fb8
        constraint_0_ = 0x555556233ec8
        vars_0 = {
          0x5555563665c8,
          0x555556366fb8,
          0x5555563663f8
        }
        vals_0 = {
          7,
          3,
          2
        }
        constraint_1_ = 0x555556233f40
        vars_1 = {
          0x5555563665c8,
          0x555556366fb8,
          0x5555563663f8
        }
        vals_1 = {
          -5,
          7,
          3
        }
        constraint_2_ = 0x555556233fb8
        vars_2 = {
          0x5555563665c8,
          0x555556366fb8,
          0x5555563663f8
        }
        vals_2 = {
          2,
          -6,
          5
        }
        stage = 21845
        scip_status = 1431668704
        solution_number_ = 21845
```

Change frame
```gdb
(gdb) f 4
#4  0x0000555555f62d19 in SCIPconcurrentSolve (scip=0x5555561f6eb0) at /usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c:518
518	   assert(idx >= 0 && idx < nconcsolvers);
```

display frame
```gdb
(gdb) info frame
Stack level 4, frame at 0x7fffffffded0:
 rip = 0x555555f62d19 in SCIPconcurrentSolve (/usr/local/google/home/corentinl/dev/scip-multithread/build/_deps/scip-src/src/scip/concurrent.c:518); saved rip = 0x5555558fbf28
 called by frame at 0x7fffffffdfd0, caller of frame at 0x7fffffffde60
 source language c.
 Arglist at 0x7fffffffdec0, args: scip=0x5555561f6eb0
 Locals at 0x7fffffffdec0, Previous frame's sp is 0x7fffffffded0
 Saved registers:
  rbp at 0x7fffffffdec0, rip at 0x7fffffffdec8
```

display locals
```gdb
gdb) info locals
syncstore = 0x55555621ad40
idx = -1
jobid = 1
i = 16
retcode = SCIP_OKAY
concsolvers = 0x555558327350
nconcsolvers = 16
__PRETTY_FUNCTION__ = "SCIPconcurrentSolve"
```

Once you are on a correct frame, you can dereference pointer object etc...
```gdb
(gdb) p (*syncstore)
$10 = {nuses = 17, mode = SCIP_PARA_DETERMINISTIC, initialized = 1, ninitvars = 3, syncdata = 0x5555587ab5a8, lastsync = 0x0, mainscip = 0x5555561f6eb0, stopped = 0, lock = {__data = {__lock = 0, __count = 0, __owner = 0, __nusers = 0, __kind = 0, __spins = 0, __elision = 0, __list = {__prev = 0x0, __next = 0x0}}, __size = '\000' <repeats 39 times>, __align = 0}, nsyncdata = 16, minsyncdelay = 2.7000000000000002, maxnsyncdelay = 7, syncfreqinit = 10, syncfreqmax = 2.7000000000000002, maxnsols = 3, nsolvers = 16}
(gdb) p (*syncstore->lastsync)
Cannot access memory at address 0x0
(gdb) p (syncstore->lastsync)
$11 = (SCIP_SYNCDATA *) 0x0
```


