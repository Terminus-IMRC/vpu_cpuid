# vpu_cpuid

Prints the cpuid of the VideoCore IV **VPU** on Raspberry Pi.

See http://imrc.noip.me/blog/vc4/VPUID/ for the results.

## Requirements
You need [librpimemmgr](https://github.com/Idein/librpimemmgr) and
[mailbox](https://github.com/Terminus-IMRC/mailbox).

## How to run
```
$ git clone https://github.com/Terminus-IMRC/vpu_cpuid.git
$ cd vpu_cpuid/
$ cmake .
$ make
$ ./vpuid
```
