include("imageFILTER.jl")
include("imageHIST.jl")

# Module to perform adaptive histogram based image processing
#
# ---------------------------------
# ADAPTiVE HISTOGRAM PROCESSING
# ---------------------------------
# roundFilter()      - Function to generate a circular filter
# histeqADAPT()      - Function to perform adaptive histogram equalization (AHE) 
# histeqADAPTcirc()  - Function to perform adaptive histogram equalization (AHE)
#                      using a circular filter

module imageENHADAPT

using imageFILTER
using imageHIST

# Function to generate a circular filter, where circle elements are denoted
# by 1, and non-circle by 0. The maximum filer size is 21 x 21 (radius 10)
# due to limitations in the current algorithm
#
# Usage: 
#       circFlt = imageENHADAPT.roundFilter(6)

function roundFilter(radius=5)

    if (radius > 10)
        println("Maximum filter radius of 10")
        return 0
    end
    diam = radius * 2 + 1
    filter = zeros(Int8, diam, diam)
    midx = radius + 1
    midy = radius + 1

    # Build the edge of the circular filter with 1's
    for radians=0:0.1:2*pi
        x = round(Int, radius * cos(radians))
        y = round(Int, radius * sin(radians))
        filter[midx+x,midy+y] = 1
    end
    
    # Fill the circular filter with 1's
    for i=2:diam-1
        j = 1
        while (filter[i,j] != 1 && j < diam)
            j = j + 1
        end
        while (filter[i,j] != 0 && j < diam)
            j = j + 1
        end
        while (filter[i,j] != 1 && j < diam)
            filter[i,j] = 1
            j = j + 1
        end
    end
    return filter
end


# Function to perform contrast enhancement using adaptive histogram equalization
# The area modified includes a square of size radius*2+1 (default radius = 21). 
# The filter works by applying histogram equalization to a radius*2+1 x radius*2+1
# area around each pixel in the image, and then assigning the transformed value
# to the pixel in the output image. 
# 
#   Ref(s):
#
# Usage: 
#       imgJ = imageENHADAPT.histeqADAPT(img,25)

function histeqADAPT(img, radius=21)

    dx,dy = size(img)
    imgN = copy(img)

    imgSz = (radius*2+1)^2
    L = 256
    
    for i=radius+1:dx-radius, j=radius+1:dy-radius
        # Extract a block surrounding a pixel
        block = img[i-radius:i+radius, j-radius:j+radius]
        hst = imageHIST.getIMGhist(block,L)
            
        # Calculate the probability density function of the histogram
        # Frequency of a pixel / no. of pixels
        histPDF = hst / imgSz        

        # Derive the cumulative histogram (cumulative distribution probability)
        cdf = cumsum(histPDF)
    
        # Histogram equalization
        fL = round(Int16, cdf*(L-1))
        #println(fL)
        
        imgN[i,j] = fL[img[i,j]+1]        
    end
    
    # Normalize to 8-bit, 0-255
    maxI = maximum(imgN)
    for i=radius+1:dx-radius, j=radius+1:dy-radius
        imgN[i,j] = round(UInt8, (imgN[i,j]/maxI)*255)
    end
        
    return imgN
end


# Function to perform contrast enhancement using adaptive histogram equalization
# The area modified includes a circular filter with a maximum radius of 10
# 
#   Ref(s):
#
# Usage: 
#       imgJ = imageENHADAPT.histeqADAPTcirc(img,5)

function histeqADAPTcirc(img, radius=10)

    dx,dy = size(img)
    imgN = copy(img)

    imgSz = (radius*2+1)^2
    L = 256
    
    circFlt = roundFilter(radius)
    circFltV = vec(reshape(circFlt,1,imgSz))
    f(x) = x == 1
    circFltE = find(f,circFltV)
    
    for i=radius+1:dx-radius, j=radius+1:dy-radius
        # Extract a block surrounding a pixel
        block = img[i-radius:i+radius, j-radius:j+radius]
        blockV = vec(reshape(block,1,imgSz))
        blockC = getindex(blockV,circFltE)
        hst = imageHIST.getIMGhist(blockC,L)
            
        # Calculate the probability density function of the histogram
        # Frequency of a pixel / no. of pixels
        histPDF = hst / imgSz        

        # Derive the cumulative histogram (cumulative distribution probability)
        cdf = cumsum(histPDF)
    
        # Histogram equalization
        fL = round(Int16, cdf*(L-1))
        #println(fL)
        
        imgN[i,j] = fL[img[i,j]+1]        
    end
    
    # Normalize to 8-bit, 0-255
    maxI = maximum(imgN)
    for i=radius+1:dx-radius, j=radius+1:dy-radius
        imgN[i,j] = round(UInt8, (imgN[i,j]/maxI)*255)
    end
        
    return imgN
end

end
