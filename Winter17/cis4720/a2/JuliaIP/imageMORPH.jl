include("imageSET.jl")
using imageSET

module imageMORPH

# ---------------------------------
# Image Morphology
# ---------------------------------
# padarray()
# makeSE()        - Build a structuring element
# dilate()        - Function to perform binary dilation
# erode()         - Function to perform binary erosion
# open()          - Function to perform binary opening
# close()         - Function to perform binary closing
# dilateG()       - Function to perform grayscale dilation
# erodeG()        - Function to perform grayscale erosion
# openG()         - Function to perform grayscale opening
# closeG()        - Function to perform grayscale closing
# sharpen()
# toggleCE()
# tophat()        - Function to perform top-hat filter
# bothat()        - Function to perform bottom-hat filter
# morphCE()       - Function to perform morphological contrast enhancement
# morphASF()      - Function to perform alternating-sequential-filter
# condDilate()     - Conditional dilation

function padarray(img, padsize, padtype="value", padvalue=0)

    dx,dy = size(img)
    imP = zeros(UInt8,dx+padsize,dy+padsize)
    w = div(padsize,2)
    
    if padtype == "value"
        imP[:,:] = padvalue
    elseif padtype == "replicate"
        imP[1:w,:] = imP[w+1:w+w]
        imP[end-w:end,:] = imP[w+1:w+w]
    else
        println("Unknown border condition")
    end

end

#---------------------------------------------------------------------------------
# CORE BINARY MORPHOLOGY
#---------------------------------------------------------------------------------

# A function which returns a flat structuring element.
# A structuring element is simply a binary image (or mask) that 
# allows us to define arbitrary neighborhood structures.
# The types of shape include a disk, vertical and horizontal
# lines, a cross and a square

function makeSE(shape="disk", size=5)

    mask = zeros(UInt8,size,size)
    radius = div(size,2)
    centre = radius + 1
        
    if shape == "disk"
        for x=1:size, y=1:size
            dist = sqrt((centre - x)^2 + (centre - y)^2)
            if dist <= radius+0.5
                mask[x,y] = 1
            end
        end
    elseif shape == "lineH"
        mid = div(size,2)
        mask[mid+1,:] = 1
    elseif shape == "lineV"
        mid = div(size,2)
        mask[:,mid+1] = 1   
    elseif shape == "cross"
        mid = div(size,2)
        mask[mid+1,:] = 1
        mask[:,mid+1] = 1     
    elseif shape == "square"
        mask[:,:] = 1 
    end
    return mask
end

# Function to perform binary dilation (dilation of white pixels)
#
# Syntax:
# im2 = dilate(img,se)
# This function dilates a binary image img, returning the dilated image, im2. 
# The argument se is a structuring element 

function dilate(img, se)

    dx,dy = size(img)
    sx,sy = size(se)
    w = div(sx,2)
    
    # Pad zeroes on all sides
    #imP = zeros(UInt8,dx+w+w,dy+w+w)
    #imP[w+1:w+dx,w+1:w+dy] = img[:,:]
    # Initialize a matrix of size img with zeros
    imB = zeros(UInt8,dx,dy)
    
    for i=w+1:dx-w, j=w+1:dy-w
        #map = img[i-w:i+w,j-w:j+w] | se
        #imB[i-w:i+w,j-w:j+w] = map
        zx = i-w-1
        zy = j-w-1
        if img[i,j] == 1
            for x=i-w:i+w, y=j-w:j+w
                if se[x-zx,y-zy] == 1 || img[x,y] == 1
                    imB[x,y] = 1
                end
            end
        end
    end
    
    #for i=w+1:w+dx, j=w+1:dy+w
    #    intS = sum(imP[i-w:i+w,j-w:j+w] & se)
    #    println(imP[i-w:i+w,j-w:j+w])
    #    println(se)
    #    println(intS)
    #    if intS == sumSE
    #        imB[i-w,j-w] = 1
    #    end
    #end
    return imB
end

# Function to perform binary erosion (erosion of white pixels)
#
# Syntax:
# im2 = erode(img,SE)
# This function erodes a binary image img, returning the eroded image, im2. 
# The argument SE is a structuring element 

function erode(img, se)

    dx,dy = size(img)
    sx,sy = size(se)
    w = div(sx,2)
    sumSE = sum(se)
    
    imB = zeros(UInt8,dx,dy)
    
    # Perform the erosion by retaining only those pixels where the SE 
    # fits on the image
    for i=w+1:dx-w, j=w+1:dy-w
        sum1 = sum(img[i-w:i+w,j-w:j+w] & se)
        if sum1 == sumSE
            imB[i,j] = 1
        end       
    end

    return imB
end

# Function to perform binary opening (erosion of img by se, followed by dilation)
function open(img, se)

    imgE = erode(img,se)
    imgO = dilate(imgE,se)
    return imgO
    
end

# Function to perform binary opening (dilation of img by se, followed by erosion)
function close(img, se)

    imgD = dilate(img,se)
    imgC = erode(imD,se)
    return imgC
    
end

#---------------------------------------------------------------------------------
# CORE GRAYSCALE MORPHOLOGY
#---------------------------------------------------------------------------------

function dilateG(img, se)

    dx,dy = size(img)
    sx,sy = size(se)
    w = div(sx,2)

    imG = copy(img)
    
    seL = vec(reshape(se,1,sx*sy))
    seZ = find(seL)
    
    for i=w+1:dx-w, j=w+1:dy-w
        block = img[i-w:i+w,j-w:j+w]
        block = vec(reshape(block,1,sx*sy))
        maxG = maximum(block[seZ])
        imG[i,j] = maxG
    end
    
    return imG
end

function erodeG(img, se)

    dx,dy = size(img)
    sx,sy = size(se)
    w = div(sx,2)

    imG = copy(img)
    
    seL = vec(reshape(se,1,sx*sy))
    seZ = find(seL)
    
    for i=w+1:dx-w, j=w+1:dy-w
        block = img[i-w:i+w,j-w:j+w]
        block = vec(reshape(block,1,sx*sy))
        minG = minimum(block[seZ])
        imG[i,j] = minG
    end
    
    return imG
end

# Function to perform grayscale opening (erosion of img by se, followed by dilation)
function openG(img, se)

    imgE = erodeG(img,se)
    imgO = dilateG(imgE,se)
    return imgO
    
end

# Function to perform grayscale opening (dilation of img by se, followed by erosion)
function closeG(img, se)

    imgD = dilateG(img,se)
    imgC = erodeG(imgD,se)
    return imgC
    
end

#---------------------------------------------------------------------------------
# IMAGE ENHANCEMENT ALGORITHMS
#---------------------------------------------------------------------------------

# Function to perform morphological sharpening similar in concept to
# morphological toggles for contrast enhancement.
#
# Syntax:
# imS = sharpen(img,SE,iter)
# This function performs a form of morphological sharpening on the image img. 
# The argument SE is a structuring element, the argument iter, the number of
# iterations of sharpening to be performed.
#
# References:
#   Schavemaker, J.G.M. , Reinders, M.J.T., Gerbrands, J.J.,
#    Backer, E.E., "Image sharpening by morphological filtering",
#    Pattern Recognition, 2000, Vol.33, pp.997-1012.

function sharpen(img,SE,iter=1)

    dx,dy = size(img)
    sx,sy = size(SE)
    w = div(sx,2)
    
    imgT = copy(img)
    imgS = zeros(UInt8,dx,dy)

    for x = 1:iter

        imgS[:,:] = 0
    
        imgD = dilateG(img,SE)
        imgE = erodeG(img,SE)
                
        for i=1:dx, j=1:dy
            if (imgD[i,j] - imgT[i,j]) < (imgT[i,j] - imgE[i,j])
                imgS[i,j] = imgD[i,j]
            elseif (imgD[i,j] - imgT[i,j]) > (imgT[i,j] - imgE[i,j])    
                imgS[i,j] = imgE[i,j]
            else
                imgS[i,j] = imgT[i,j]
            end
        end

        imgT = copy(imgS)
    end

    return imgT
end

# Function to perform morphological toggle contrast enhancement.
#
# Syntax:
# imS = sharpen(img,SE)
# This function performs a form of morphological sharpening on the image img. 
# The argument SE is a structuring element.
#
# References:
#   Meyer & Serra

function toggleCE(img,SE,iter=1)

    dx,dy = size(img)
    sx,sy = size(SE)
    w = div(sx,2)
    
    imgS = zeros(UInt8,dx,dy)
    
    imgD = dilateG(img,SE)
    imgE = erodeG(img,SE)
                
    for i=1:dx, j=1:dy
        if (imgD[i,j] - img[i,j]) < (img[i,j] - imgE[i,j])
            imgS[i,j] = imgD[i,j]
        else   
            imgS[i,j] = imgE[i,j]
        end
    end
    return imgS
end

# Function to perform morphological top-hat of grayscale images.
# Top-hat filtering computes the morphological opening of the image and then subtracts 
# the result from the original image. Sometimes known as the white top-hat, or
# top-hat-by-opening.
#
# The resulting image contains those "objects" or "elements" of an input image that:
# are "smaller" than the structuring element (i.e., places where the structuring element 
# does not fit in), and are brighter than their surroundings.
#
# Syntax:
# imS = tophat(img,SE)
# This function performs top-hat filtering of the grayscale image img. 
# The argument SE is a structuring element.
#
function tophat(img, SE)

    imgO = openG(img,SE)
    imgTH = img .- imgO
    
    return imgTH

end

# Function to perform morphological top-hat of grayscale images.
# Top-hat filtering computes the morphological closing of the image and then subtracts 
# the original image from it. Sometimes known as the black top-hat, or 
# top-hat-by-closing.
#
# The resulting image contains those "objects" or "elements" of an input image that:
# are "smaller" than the structuring element, and are darker than their surroundings.
#
# Syntax:
#     imS = bothat(img,SE)
# This function performs bottom-hat filtering of the grayscale image img. 
# The argument SE is a structuring element.
#
function bothat(img, SE)

    imgC = closeG(img,SE)
    imgBH = imgC .- img
    
    return imgBH

end

# Function to perform morphological contrast enhancement.
#
# Syntax:
#     imS = morphCE(img,SE)
# This function performs morphological contrast enhancement of the grayscale image img. 
# The argument SE is a structuring element.
#
function morphCE(img, SE)

    imgTH = tophat(img,SE)
    imgBH = bothat(img,SE)
    
    # Contrast enhancement
    imgCE = img .+ imgTH .- imgBH
    
    return imgCE
end

# Function to perform Alternating Sequential filter
# Creates the image Iasf by filtering the image img by n iterations of the close and open 
# alternating sequential filter characterized by the structuring element SE. The sequence 
# of opening and closing is controlled by the parameter SEQ. 'oc' performs opening after 
# closing, 'co' performs closing after opening, 'oco' performs opening after closing after 
# opening, and 'coc' performs closing after opening after closing. 
#
# Syntax:
#     imgR = morphASF(img,SE,seq,n)
#
# Arguments: 
#    img:  Grayscale image
#    SE:   Structuring element. Default: Elementary cross (mmsecross). 
#    seq:  String specifying sequence. 'oc', 'co', 'oco', 'coc'. Default: "OC". 
#    n:    Number of iterations). Default: 1. 
# Ref:

function morphASF(img, SE, seq="OC", n=1)
   
    tempJ = copy(img)

    for i = 1:n
        if (seq == "OC") # close -> open
            tempI = openG(closeG(tempJ,SE),SE)
        elseif (seq == "CO") # open -> close
            tempI = closeG(openG(tempJ,SE),SE)
        elseif (seq == "OCO") # open -> close -> open
            tempI = openG(closeG(openG(tempJ,SE),SE),SE)
        elseif (seq == "COC") # close -> open -> close
            tempI = closeG(openG(closeG(tempJ,SE),SE),SE)
        end
        tempJ = copy(tempI)
    end
    
    return tempJ

end

# Function to perform conditional dilation
# Creates the image Io by dilating the image img by the structuring element SE
# conditionally to Ic. This function may be applied recursively n times.
#
# Syntax:
#     imgR = condDilate(img, imgC, SE, n)
#
# Arguments: 
# Ref:

function condDilate(img, imgC, SE, n=1)
    
    tempI = imIntersect(img, imgC)
    
    for i=1:n
        imgD = dilateG(tempI, SE)
        tempI = imIntersect(imgD, imgC)
    end
    return tempI
    
end

#---------------------------------------------------------------------------------
# AREA BASED MORPHOLOGY
#---------------------------------------------------------------------------------

# Function to perform morphological Area Opening for binary and grayscale images.
# Removes any object with area less than A of a binary image img. The function
# is generalized to grayscale images by applying the binary algorithm successively 
# on "slices" of img taken through each threshold level 0->255
#
# Syntax:
#    imgR = areaOpen(img,A)
#
# Arguments: 
#    img:  Grayscale image
#      A:  Value representing minimum size of area to retain
#
# Ref:
#    Vincent, L., "Grayscale area openings and closings, their efficient implementation and
#    applications", EURASIP Workshop on Mathematical Morphology and its Applications to Signal
#    Processing, pp.22-27 (1993)
# 
#    Vincent, L., "Morphological area openings and closings for greyscale images", NATO Shape
#    in Picture Workshop, pp.197-208 (1992)

function areaOpen(img, rArea)

    dx,dy = size(img)
    
    imgAO = zeros(UInt8,dx,dy)
    
    if isBinary(img)
        # Label each binary region
        imgL, nRegions = imageSET.labelBW(img)
        # Determine the area of each blob
        rS = imageSET.regionStats(imgL, nRegions, "area")
        # Process each blob. If the area is greater than area "A", retain the region.
        for i=1:nRegions
            if rS[i] < rArea
                m = findin(imgL,i)
                img[m] = 0
            end
        end
    
    else # image is a grayscale image
        n = 256;
        tBW = zeros(UInt8,dx,dy)
        for k = 1:n
            # Threshold the image at value k.
            tBW[:,:] = 0
            for i = 1:dx, j = 1:dy
                if (im[i][j] >= k)
                    tBW[i,j] = 1
                end
            end
            # Apply the morphological opening to each binary image.
            fo = areaOpen(tBW,A)
            # Append the area to output image
            imgAO = imgAO .+ fo
        end
    end    
    
    return imgAO

end



end

