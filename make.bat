..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o UnaPack.o UnaPack.s
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o player.o player.s
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o galaxy.o galaxy.c
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -o galaxy.gb UnaPack.o player.o galaxy.o
