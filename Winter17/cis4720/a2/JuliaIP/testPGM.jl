include("PGMimages.jl")
using PGMimages

print("image filename? ")
fnameIN = chomp(readline(STDIN))

#img, nr, nc = PGMimages.readPGM(fnameIN)
img, nr, nc = PGMimages.readPGMc(fnameIN)

print("image filename? ")
fnameOUT = chomp(readline(STDIN))

#PGMimages.writePGM(fnameOUT,img,nr,nc,255,"P5")
PGMimages.writePGMc(fnameOUT,img,nr,nc,255,"P6")

