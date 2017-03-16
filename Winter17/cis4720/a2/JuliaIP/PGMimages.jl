module PGMimages

# Module to read and write PGM images.
#
# ---------------------------------
# PGM I/O
# ---------------------------------
# readPGMHeader()         - Read the PGM header
# readPGM()               - Read a PGM image (grayscale)
# writePGM()              - Write a PGM image (grayscale)
# readPGMc()              - Read a PGM image (colour)
# writePGMc()             - Write a PGM image (colour)


# Read and parse a PGM image file header
# Returns the number of columns, number of rows,
#         maximum pixel value
#         and type = P2 or P5
# Unsuccessful parse returns -1

function readPGMHeader(fid)

# First line contains ID string:
# "P1" = ascii bitmap, "P2" = ascii greymap, "P3" = ascii pixmap
# "P4" = raw bitmap,   "P5" = raw greymap,   "P6" = raw pixmap

    x = readline(fid)

    pgmType = x[1:2]

    if (pgmType != "P2" && pgmType != "P5")
        println("PGM file must be of type P2 or P5")
        return -1
    end

    comment = readline(fid)
    sizeIM = readline(fid)
    sizeR = split(sizeIM)
    nrow = parse(Int16,sizeR[2])
    ncol = parse(Int16,sizeR[1])
    maxVal = readline(fid)

    return pgmType, nrow, ncol, maxVal


end

# Function to read in type P2/P5 PGM images (grayscale)

function readPGM(fname)

    f = open(fname,"r")

    # Read header information
    pgmType, nrows, ncols, maxVal = readPGMHeader(f)
    println(nrows, " rows  x ", ncols, " columns")

    img = zeros(Int16, nrows, ncols)

    if (pgmType == "P2")
        img = readdlm(f, UInt8)
    elseif (pgmType == "P5")
        for i=1:nrows, j=1:ncols
            img[i,j] = read(f,UInt8)
        end
    end

    close(f)

    return img, nrows, ncols

end

# Function to write type P2/P5 PGM images (grayscale)

function writePGM(fname,img,nrows,ncols,maxVal,pgmType)

    imgN = zeros(UInt8, nrows, ncols)

    # Convert to 8-bit image before writing to file
    for i=1:nrows, j=1:ncols
        imgN[i,j] = convert(UInt8, img[i,j])
    end

    # Write header information
    f = open(fname,"w")
    @printf(f,"%s\n", pgmType)
    @printf(f,"#Grayscale image (8-bit)\n")
    @printf(f,"%d %d\n", ncols, nrows)
    @printf(f,"%d\n", maxVal)

    # Write data
    if (pgmType == "P2")
        writedlm(f,img)
    elseif (pgmType == "P5")
        for i=1:nrows, j=1:ncols
            write(f,imgN[i,j])
        end
    end

    close(f)

end

# Function to read in type P3/P6 PGM images (colour)

function readPGMc(fname)

    f = open(fname,"r")

    x = readline(f)

    pgmType = x[1:2]

    # Read header information
    if (pgmType != "P3" && pgmType != "P6")
        println("PGM file must be of type P3 or P6")
        return -1
    end

    comment = readline(f)
    sizeIM = readline(f)
    sizeR = split(sizeIM)
    nrow = parse(Int16,sizeR[2])
    ncol = parse(Int16,sizeR[1])
    maxVal = readline(f)

    img = zeros(Int16, nrow, ncol, 3)

    if (pgmType == "P3")
        # NOT yet implemented
    elseif (pgmType == "P6")
        for i=1:nrow, j=1:ncol
            for k=1:3
                img[i,j,k] = read(f,UInt8)
            end
        end
    end

    close(f)

    return img, nrow, ncol

end

# Function to write type P2/P5 PGM images (colour)

function writePGMc(fname,img,nrows,ncols,maxVal,pgmType)

    imgN = zeros(UInt8, nrows, ncols, 3)

    # Convert to 8-bit image before writing to file
    for k = 1:3
        for i=1:nrows, j=1:ncols
            imgN[i,j,k] = convert(UInt8, img[i,j,k])
        end
    end

    # Write header information
    f = open(fname,"w")
    @printf(f,"%s\n", pgmType)
    @printf(f,"#Colour image\n")
    @printf(f,"%d %d\n", ncols, nrows)
    @printf(f,"%d\n", maxVal)

    # Write data
    if (pgmType == "P3")
        # NOT yet implemented
    elseif (pgmType == "P6")
        for i=1:nrows, j=1:ncols
            for k=1:3
                write(f, imgN[i,j,k])
            end
        end
    end

    close(f)

end

end
