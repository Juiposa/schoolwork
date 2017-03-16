include("imageHIST.jl")
using imageHIST
include("imageIO.jl")
using imageIO

println("Image filename to read? (.txt)")
fnameI= chomp(readline(STDIN))

img = imageIO.imreadGray(fnameI)
dx,dy = size(img)
imE = imageHIST.bihistEQ(img)

println("Image filename to write? (.txt)")
fnameO = chomp(readline(STDIN))

imageIO.imwriteGray(fnameO, imE)

