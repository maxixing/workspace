https://baijiahao.baidu.com/s?id=1692060766841452736&wfr=spider&for=pc

#get import module by vendor
go version -m go_binary_filename


#get import module by self
#//////////////////////////////////////////////////////////////////
root@debian:/work# readelf -h natapp_x86
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x80ae540
  Start of program headers:          52 (bytes into file)
  Start of section headers:          276 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         7
  Size of section headers:           40 (bytes)
  Number of section headers:         14
  Section header string table index: 3
#//////////////////////////////////////////////////////////////////
root@debian:/work# readelf -l natapp_x86

Elf file type is EXEC (Executable file)
Entry point 0x80ae540
There are 7 program headers, starting at offset 52

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  PHDR           0x000034 0x08048034 0x08048034 0x000e0 0x000e0 R   0x1000
  NOTE           0x000f9c 0x08048f9c 0x08048f9c 0x00064 0x00064 R   0x4
  LOAD           0x000000 0x08048000 0x08048000 0x355b1f 0x355b1f R E 0x1000
  LOAD           0x356000 0x0839e000 0x0839e000 0x31cac4 0x31cac4 R   0x1000
  LOAD           0x673000 0x086bb000 0x086bb000 0x47620 0x60e60 RW  0x1000
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RW  0x4
  LOOS+0x5041580 0x000000 0x00000000 0x00000000 0x00000 0x00000     0x4

 Section to Segment mapping:
  Segment Sections...
   00 
   01     .note.go.buildid 
   02     .text .note.go.buildid 
   03     .rodata .typelink .itablink .gosymtab .gopclntab 
   04     .go.buildinfo .noptrdata .data .bss .noptrbss 
   05 
   06 
#//////////////////////////////////////////////////////////////////
root@debian:/work# readelf -S natapp_x86
There are 14 section headers, starting at offset 0x114:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        08049000 001000 354b1f 00  AX  0   0 16
  [ 2] .rodata           PROGBITS        0839e000 356000 15c0b0 00   A  0   0 32
  [ 3] .shstrtab         STRTAB          00000000 4b20c0 0000a5 00      0   0  1
  [ 4] .typelink         PROGBITS        084fa180 4b2180 002b78 00   A  0   0 32
  [ 5] .itablink         PROGBITS        084fcd00 4b4d00 0006f4 00   A  0   0 32
  [ 6] .gosymtab         PROGBITS        084fd3f4 4b53f4 000000 00   A  0   0  1
  [ 7] .gopclntab        PROGBITS        084fd400 4b5400 1bd6c4 00   A  0   0 32
  [ 8] .go.buildinfo     PROGBITS        086bb000 673000 000020 00  WA  0   0 16
  [ 9] .noptrdata        PROGBITS        086bb020 673020 03e560 00  WA  0   0 32
  [10] .data             PROGBITS        086f9580 6b1580 009088 00  WA  0   0 32
  [11] .bss              NOBITS          08702620 6ba620 0140dc 00  WA  0   0 32
  [12] .noptrbss         NOBITS          08716700 6ce700 005760 00  WA  0   0 32
  [13] .note.go.buildid  NOTE            08048f9c 000f9c 000064 00   A  0   0  4
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  p (processor specific)
#//////////////////////////////////////////////////////////////////
root@debian:/work# objdump -s -j .go.buildinfo natapp_x86

natapp_x86:     file format elf32-i386

Contents of section .go.buildinfo:
 86bb000 ff20476f 20627569 6c64696e 663a0400  . Go buildinf:..
 86bb010 889b6f08 a89b6f08 00000000 00000000  ..o...o.........
#//////////////////////////////////////////////////////////////////
root@debian:/work# objdump -s --start-address 0x86f9b88 --stop-address 0x86f9b98 natapp_x86

natapp_x86:     file format elf32-i386

Contents of section .data:
 86f9b88 c8214408 06000000 f0764e08 489b6f08  .!D......vN.H.o.
#//////////////////////////////////////////////////////////////////
root@debian:/work# objdump -s --start-address 0x84421c8 --stop-address 0x84421ce natapp_x86

natapp_x86:     file format elf32-i386

Contents of section .rodata:
 84421c8 676f312e 3136                        go1.16 
#//////////////////////////////////////////////////////////////////
root@debian:/work# objdump -s --start-address 0x86f9ba8 --stop-address 0x86f9bb8 natapp_x86

natapp_x86:     file format elf32-i386

Contents of section .data:
 86f9ba8 50114608 6c040000 f0764e08 509b6f08  P.F.l....vN.P.o.
#//////////////////////////////////////////////////////////////////
root@debian:/work# objdump -s --start-address 0x8461150 --stop-address 0x84615bc natapp_x86

natapp_x86:     file format elf32-i386

Contents of section .rodata:
 8461150 3077af0c 92740802 41e1c107 e6d618e6  0w...t..A.......
 8461160 70617468 096e6174 6170702f 7372632f  path.natapp/src/
 8461170 6d61696e 2f6e6174 6170700a 6d6f6409  main/natapp.mod.
 8461180 6e617461 70700928 64657665 6c29090a  natapp.(devel)..
 8461190 64657009 67697468 75622e63 6f6d2f67  dep.github.com/g
 84611a0 6f72696c 6c612f77 6562736f 636b6574  orilla/websocket
 84611b0 0976312e 342e3009 68313a57 44466a78  .v1.4.0.h1:WDFjx
 84611c0 2f544d7a 56677939 56644d4d 5169324b  /TMzVgy9VdMMQi2K
 84611d0 32456d74 77693251 63555173 7a745a2f  2Emtwi2QcUQsztZ/
 84611e0 7a4c6148 2f513d0a 64657009 67697468  zLaH/Q=.dep.gith
 84611f0 75622e63 6f6d2f69 6e636f6e 73687265  ub.com/inconshre
 8461200 76656162 6c652f6d 6f757365 74726170  veable/mousetrap
 8461210 0976312e 302e3009 68313a5a 38747535  .v1.0.0.h1:Z8tu5
 8461220 7372614c 58435849 63415278 42702f38  sraLXCXIcARxBp/8
 8461230 6362766c 77566137 5a314e48 67395845  cbvlwVa7Z1NHg9XE
 8461240 4b687453 764d3d0a 64657009 67697468  KhtSvM=.dep.gith
 8461250 75622e63 6f6d2f6b 61726469 616e6f73  ub.com/kardianos
 8461260 2f6f7365 78740976 302e302e 302d3230  /osext.v0.0.0-20
 8461270 31393032 32323137 33333236 2d326263  190222173326-2bc
 8461280 31663335 63646463 30096831 3a695154  1f35cddc0.h1:iQT
 8461290 772f3846 57547563 37756961 53657058  w/8FWTuc7uiaSepX
