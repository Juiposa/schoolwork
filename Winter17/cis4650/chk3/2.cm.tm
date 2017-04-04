* START: Prelude
  0:  LD 6, 0(0) load max address
  1:  LDA 5, 0(6) copy to reg(5)
  2:  ST 0, 0(0) clear daddr(0)
* START: IO routines
* input
  4:  ST 0, -1(5) store return loc
  5:  IN 0, 0, 0 in
  6:  LD 7, -1(5) return
* output
  7:  ST 0, -1(5) store return loc
  8:  LD 0, -2(5) load output value
  9:  OUT 0, 0, 0 out
  10:  LD 7, -1(5) return
  3:  LDA 7, 7(7) jump past i/o
* END: IO routines
* END: Prelude
* START: Finale
  11:  ST 5, -1(5) push frame pointer
  12:  LDA 5, -1(5) push frame
  13:  LDA 0, 1(7) load reg(0) with return pointer
  14:  LDA 7, -35(7) jump to main
  15:  LD 5, 0(5) pop frame
  16:  HALT 0, 0, 0 
* END: Finale
