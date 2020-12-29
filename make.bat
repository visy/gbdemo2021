set CART_SIZE=16
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o UnaPack.o UnaPack.s
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o player.o player.s
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o galaxy.o galaxy.c
..\gbdk\bin\lcc -Wl-yo16 -Wa-l -Wl-m -Wl-j -Wl-yt27 -Wl-ya4 -Wl-yp0x143=0x80 -o galaxy.gb UnaPack.o player.o galaxy.o
