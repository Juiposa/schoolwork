include("JuliaIP/colourSPACE.jl")
include("JuliaIP/PGMimages.jl")
using colourSPACE
using PGMimages


function redMask(img, ny, nx)
    newimg = zeros( Int16, ny, nx, 3 )
    for i=1:ny, j=1:nx
        if img[i,j,1] > 200 & img[i,j,1] > img[i,j,2] & img[i,j,2] >  img[i,j,3]
            newimg[i,j,1] = img[i,j,1]
            newimg[i,j,2] = img[i,j,2]
            newimg[i,j,3] = img[i,j,3]
        else
            newimg[i,j,1] = 0
            newimg[i,j,2] = 0
            newimg[i,j,3] = 0
        end
    end
    return newimg
end

function satMask(img, redMask_i, ny, nx)
    H, S, V =  colourSPACE.rgb2hsv(img)
    satMask_i = zeros( Int16, ny, nx, 3 )
    #multiplying pixels by thier saturation value
    #remaining pixels may be fire
    for i=1:ny, j=1:nx
        satMask_i[i,j,1] = floor(redMask_i[i,j,1]*S[i,j])
        satMask_i[i,j,2] = floor(redMask_i[i,j,2]*S[i,j])
        satMask_i[i,j,3] = floor(redMask_i[i,j,3]*S[i,j])
    end
    return satMask_i
end

function valMask(img, redMask_i, ny, nx)
    H, S, V =  colourSPACE.rgb2hsv(img)
    valMask_i = zeros( Int16, ny, nx, 3 )
    pixelCount = 0
    totalIntensity = 0.0
    avg = 0.0

    #getting average intensity value of HSV image
    for i=1:ny, j=1:nx
        pixelCount += 1
        totalIntensity += V[i,j]
    end
    avg = totalIntensity/pixelCount
    #if the intensity is greater than .5 or the average, the pixel might be fire
    for i=1:ny, j=1:nx
        if V[i,j] > 0.5 || V[i,j] > avg
            valMask_i[i,j,1] = redMask_i[i,j,1]
            valMask_i[i,j,2] = redMask_i[i,j,2]
            valMask_i[i,j,3] = redMask_i[i,j,3]
        end
    end
    return valMask_i
end

function colourMask(img, ny, nx)

    #eliminating all pixels that arent fire coloured
    redMask_i = redMask(img, ny, nx)
    PGMimages.writePGMc( "redmask.pnm", redMask_i, ny, nx, 255, "P6" )

    #further wittling down pixels that arent highly saturated
    satMask_i = satMask(img, redMask_i, ny, nx)
    PGMimages.writePGMc( "saturation.pnm", satMask_i, ny, nx, 255, "P6" )

    #removing pixels that have low intensity
    valMask_i = valMask(img, redMask_i, ny, nx)
    PGMimages.writePGMc( "intensity.pnm", valMask_i, ny, nx, 255, "P6" )

    #and multiply the saturation and intensity masks, with a little extra filtering to get rid of grey stuff
    colourMask_i = zeros( Int64, ny, nx, 3 )
    for i=1:ny, j=1:nx
        #my name is Julia and I can't do integer division hurr durr
        colourMask_i[i,j,1] = trunc( convert( Float32, satMask_i[i,j,1] ) * convert( Float32, valMask_i[i,j,1] ) / 255.0 )
        colourMask_i[i,j,2] = trunc( convert( Float32, satMask_i[i,j,2] ) * convert( Float32, valMask_i[i,j,2] ) / 255.0 )
        colourMask_i[i,j,3] = trunc( convert( Float32, satMask_i[i,j,3] ) * convert( Float32, valMask_i[i,j,3] ) / 255.0 )
    end
    PGMimages.writePGMc( "overlap.pnm", colourMask_i, ny, nx, 255, "P6" )
    
    return colourMask_i
end
