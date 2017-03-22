#takes image to detect fire in as a argument

include("include.jl")
include("masking.jl")

filename = ARGS[1]

image, ny, nx = PGMimages.readPGMc(filename)

colourMask_i = colourMask(image, ny, nx)

PGMimages.writePGMc( "output.pnm", colourMask_i, ny, nx, 255, "P6" )
