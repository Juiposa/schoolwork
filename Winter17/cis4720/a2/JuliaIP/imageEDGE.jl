module imageEDGE

include("imageBINARIZE.jl")
using imageBINARIZE

include("imageIO.jl")
using imageIO

# Author: Michael Wirth
# Date:   June 2016

# Module to perform image edge detection
#
# ---------------------------------
# EDGE ENHANCEMENT ALGORITHMS
# ---------------------------------
# sobel()        - Edge enhancement via gradient-based Sobel
# prewitt()      - Edge enhancement via gradient-based Prewitt
# kirsch()       - Edge enhancement via gradient-based Kirsch
# ---------------------------------
# EDGE DETECTION ALGORITHMS
# ---------------------------------
# canny()        - Edge detection via Canny algorithm

# GLOBALS
    type Point
      x::Int
      y::Int
    end

# Function to perform edge enhancement using the gradient-based Sobel operator.
#
# Algorithm:
#
#         X-gradient          Y-gradient
#
#         -1   0   1          -1  -2  -1
#    Gx = -2   0   2     Gy =  0   0   0
#         -1   0   1           1   2   1
#
# 1. Apply both the x- and y- gradient kernels to the image
# 2. Find the gradient magnitude:
#         G = SQRT(Gx^2 + Gy^2) 
# 3. Find the gradient direction information:
#         D = ARCTAN(Gx/Gy)
#
# Syntax:
#    imgR = sobel(img)
#
# Arguments: 
#    img:  Grayscale image
#    dir:  "DEG" degrees or "RAD" radians
#
# Ref:
#    

function sobel(img, dir="DEG")

    dx,dy = size(img)
    imgN = copy(img)

    Gx = zeros(Int,dx,dy)
    Gy = zeros(Int,dx,dy)
    
    # Define the x and y gradient kernels
    GxK = [-1 0 1; -2 0 2; -1 0 1]
    GyK = [-1 -2 -1; 0 0 0; 1 2 1]
#    GxK = [1 0 -1; 2 0 -2; 1 0 -1]
#    GyK = [1 2 1; 0 0 0; -1 -2 -1]

    for i = 2:dx-1, j = 2:dy-1
        # Extract the 3x3 block from the image
        imgBlk = img[i-1:i+1,j-1:j+1]
        # Apply the x and y kernels
        Gx[i,j] = sum(imgBlk .* GxK)
        Gy[i,j] = sum(imgBlk .* GyK)
    end

    # Calculate the magnitude of the pixel using the calculated gradient images
    Gmag = sqrt(Gx.^2 + Gy.^2)
    Gmag = round(Int16,Gmag)
    if dir == "DEG"
        Gdir = atan2(Gy,Gx) * (180 / pi)
    elseif dir == "RAD"
        Gdir = atan2(Gy,Gx)
    end
    
    return Gmag, Gdir

end

# This version of Sobel uses the two reflections of the kernels, yielding
# four kernels in total. This produces a more complete output.

function sobel2(img, dir="DEG")

    dx,dy = size(img)
    imgN = copy(img)

    Gx = zeros(Int,dx,dy)
    Gy = zeros(Int,dx,dy)
    Gx1 = zeros(Int,dx,dy)
    Gy1 = zeros(Int,dx,dy)
    Gx2 = zeros(Int,dx,dy)
    Gy2 = zeros(Int,dx,dy)
    
    # Define the x and y gradient kernels
    GxK1 = [-1 0 1; -2 0 2; -1 0 1]
    GyK1 = [-1 -2 -1; 0 0 0; 1 2 1]
    GxK2 = [1 0 -1; 2 0 -2; 1 0 -1]
    GyK2 = [1 2 1; 0 0 0; -1 -2 -1]

    for i = 2:dx-1, j = 2:dy-1
        # Extract the 3x3 block from the image
        imgBlk = img[i-1:i+1,j-1:j+1]
        # Apply the x and y kernels
        Gx1[i,j] = sum(imgBlk .* GxK1)
        Gy1[i,j] = sum(imgBlk .* GyK1)
        Gx2[i,j] = sum(imgBlk .* GxK2)
        Gy2[i,j] = sum(imgBlk .* GyK2)
    end
    
    # Retain the maximum magnitude from (Gx1,Gx2) and (Gy1,Gy2)
    for i = 2:dx-1, j = 2:dy-1
        if Gx1[i,j] > Gx2[i,j]
            Gx[i,j] = Gx1[i,j]
        else
            Gx[i,j] = Gx2[i,j]
        end
        if Gy1[i,j] > Gy2[i,j]
            Gy[i,j] = Gy1[i,j]
        else
            Gy[i,j] = Gy2[i,j]
        end
    end

    # Calculate the magnitude of the pixel using the calculated gradient images
    Gmag = sqrt(Gx.^2 + Gy.^2)
    Gmag = round(Int16,Gmag)
    if dir == "DEG"
        Gdir = atan2(Gy,Gx) * (180 / pi)
    elseif dir == "RAD"
        Gdir = atan2(Gy,Gx)
    end
    
    return Gmag, Gdir

end


# Function to perform edge enhancement using the gradient-based Prewitt operator.
#
# Algorithm:
#
#         X-gradient          Y-gradient
#
#         -1   0   1          -1  -1  -1
#    Gx = -1   0   1     Gy =  0   0   0
#         -1   0   1           1   1   1
#
# 1. Apply both the x- and y- gradient kernels to the image
# 2. Find the gradient magnitude:
#         G = SQRT(Gx^2 + Gy^2) 
# 3. Find the gradient direction information:
#         D = ARCTAN(Gx/Gy)
#
# Syntax:
#    imgR = prewitt(img)
#
# Arguments: 
#    img:  Grayscale image
#
# Ref:
#    

function prewitt(img)

    dx,dy = size(img)
    imgN = copy(img)

    Gx = zeros(Int,dx,dy)
    Gy = zeros(Int,dx,dy)
    
    # Define the x and y gradient kernels
    GxK = [-1 0 1; -1 0 1; -1 0 1]
    GyK = [-1 -1 -1; 0 0 0; 1 1 1]

    for i = 2:dx-1, j = 2:dy-1
        # Extract the 3x3 block from the image
        imgBlk = img[i-1:i+1,j-1:j+1]
        # Apply the x and y kernels
        Gx[i,j] = sum(imgBlk .* GxK)
        Gy[i,j] = sum(imgBlk .* GyK)
    end

    # Calculate the magnitude of the pixel using the calculated gradient images
    Gmag = sqrt(Gx.^2 + Gy.^2)
    Gedge = round(Int16,Gmag)
    
    return Gedge

end

# Function to perform edge enhancement using the gradient-based Kirsch operator.
#
# Algorithm:
#
#         -3  -3   5          -3   5   5           5   5   5           5   5  -3
#    K0 = -3   0   5     K1 = -3   0   5     K2 = -3   0  -3     K3 =  5   0  -3
#         -3  -3   5          -3  -3  -3          -3  -3  -3          -3  -3  -3
#
#          5  -3  -3          -3  -3  -3          -3  -3  -3          -3  -3  -3
#    K4 =  5   0  -3     K5 =  5   0  -3     K6 = -3   0  -3     K7 = -3   0   5
#          5  -3  -3           5   5  -3           5   5   5          -3   5   5
#
# 1. Apply the eight gradient kernels to the image
# 2. Find the gradient magnitude:
#         G = MAX(K0, K1, K2, K3, K4, K5, K6, K7) 
#
# Syntax:
#    imgR = kirsch(img)
#
# Arguments: 
#    img:  Grayscale image
#
# Ref:
#    

function kirsch(img)

    dx,dy = size(img)
    imgN = copy(img)

    G0 = zeros(Int,dx,dy)
    G1 = zeros(Int,dx,dy)
    G2 = zeros(Int,dx,dy)
    G3 = zeros(Int,dx,dy)
    G4 = zeros(Int,dx,dy)
    G5 = zeros(Int,dx,dy)
    G6 = zeros(Int,dx,dy)
    G7 = zeros(Int,dx,dy)
    
    # Define the eight Kirsch gradient kernels
    K0 = [-3 -3 5; -3 0 5; -3 -3 5]
    K1 = [-3 5 5; -3 0 5; -3 -3 -3]
    K2 = [5 5 5; -3 0 -3; -3 -3 -3]
    K3 = [5 5 -3; 5 0 -3; -3 -3 -3]
    K4 = [5 -3 -3; 5 0 -3; 5 -3 -3]
    K5 = [-3 -3 -3; 5 0 -3; 5 5 -3]
    K6 = [-3 -3 -3; -3 0 -3; 5 5 5]
    K7 = [-3 -3 -3; -3 0 5; -3 5 5]
    
    for i = 2:dx-1, j = 2:dy-1
        # Extract the 3x3 block from the image
        imgBlk = img[i-1:i+1,j-1:j+1]
        # Apply the Kirsch gradient kernels
        G0[i,j] = sum(imgBlk .* K0)
        G1[i,j] = sum(imgBlk .* K1)
        G2[i,j] = sum(imgBlk .* K2)
        G3[i,j] = sum(imgBlk .* K3)
        G4[i,j] = sum(imgBlk .* K4)
        G5[i,j] = sum(imgBlk .* K5)
        G6[i,j] = sum(imgBlk .* K6)
        G7[i,j] = sum(imgBlk .* K7)
    end
    
    # Calculate the pixel-wise maximum through the eight magnitude images
    Gmax = max(G0,G1,G2,G3,G4,G5,G6,G7)
    Gedge = round(Int16,Gmax)

    return Gedge

end


# Algorithm:
# 1. Convolve the image with a separable gaussian filter.
# 2. Perform Sobel edge enhancement.
# 3. Perform non-maximal suppression.
#    - remove phantom edges and if possible obtain 1-pixel wide contours
# 4. Perform hysteresis.
#    - Remove noisy maxima without breaking contours
#
# Syntax:
#    imgE = canny(img, Tlow, Thigh)
#
# Arguments: 
#    img:  Grayscale image
#  Thigh:  upper threshold for Hysteresis thresholding
#   Tlow:  lower threshold for Hysteresis thresholding
#
# NOTE:
#  Suitable values for the thresholds should be determined experimentally for each 
#  application. 

function canny(img, Tlow=0, Thigh=0)

    dx,dy = size(img)
    imgG = copy(img)
    
    # Automatic threshold selection using Otsu algorithm
    if (Tlow == 0 && Thigh == 0)
        Thigh = imageBINARIZE.otsu(img)
        Tlow = 0.5 * Thigh
    end
    
    # Apply Gaussian blurring filter
    Gfilter = [2 4 5 4 2; 4 9 12 9 4; 5 12 15 12 5; 4 9 12 9 4; 2 4 5 4 2]
    for i = 3:dx-2, j = 3:dy-2
        imgBlk = img[i-2:i+2,j-2:j+2]
        imgBlur = sum(imgBlk .* Gfilter)/159.0
        imgG[i,j] = round(Int16,imgBlur)
    end
    
    imageIO.imwriteGray("bFlyGaussian.txt", imgG)

    
    # Perform Sobel edge enhancement to obtain edge magnitude and edge orientation
    imgMag, imgDir = sobel2(imgG,"DEG")
    println("Max val = ",maximum(imgMag))
        
    imageIO.imwriteGray("bFlyMag.txt", imgMag)

    # Reduce the angle of the gradient to one of four sectors:
    # 45/225, 0/180, 135/315, 90/270
    for i = 2:dx-1, j = 2:dy-1
        if (imgDir[i,j] < 22.5 && imgDir[i,j] > -22.5) || (imgDir[i,j] > 157.5 && imgDir[i,j] < -157.5)
             imgDir[i,j] = 0
        end
        if (imgDir[i,j] > 22.5 && imgDir[i,j] < 67.5) || (imgDir[i,j] < -112.5 && imgDir[i,j] > -157.5)
             imgDir[i,j] = 45
        end
        if (imgDir[i,j] > 67.5 && imgDir[i,j] < 112.5) || (imgDir[i,j] < -67.5 && imgDir[i,j] > -112.5)
             imgDir[i,j] = 90
        end
        if (imgDir[i,j] > 112.5 && imgDir[i,j] < 157.5) || (imgDir[i,j] < -22.5 && imgDir[i,j] > -67.5)
             imgDir[i,j] = 135
        end
    end
    
    imageIO.imwriteGray("bFlyDir.txt", imgDir)

    maxSup = zeros(Int16,dx,dy)
    
    # NON-MAXIMA SUPPRESSION
    # Due to the multiple response, edge magnitude imgMag[i,j] may contain wide ridges around the local maxima.
    # Non-maxima suppression removes the non-maxima pixels preserving the connectivity of the contours.
    #
    for i = 2:dx-1, j = 2:dy-1
        if (imgDir[i,j] == 0)
            if (imgMag[i,j] > imgMag[i,j-1] && imgMag[i,j] > imgMag[i,j+1])
                if (imgMag[i,j] > 255)
                    maxSup[i,j] = 255
                else
                    maxSup[i,j] = imgMag[i,j]
                end
            else
                maxSup[i,j] = 0
            end
        end
        if (imgDir[i,j] == 45)
            if (imgMag[i,j] > imgMag[i+1,j-1] && imgMag[i,j] > imgMag[i-1,j+1])
                if (imgMag[i,j] > 255)
                    maxSup[i,j] = 255
                else
                    maxSup[i,j] = imgMag[i,j]
                end
            else
                maxSup[i,j] = 0
            end
        end
        if (imgDir[i,j] == 90)
            if (imgMag[i,j] > imgMag[i-1,j] && imgMag[i,j] > imgMag[i+1,j])
                if (imgMag[i,j] > 255)
                    maxSup[i,j] = 255
                else
                    maxSup[i,j] = imgMag[i,j]
                end
            else
                maxSup[i,j] = 0
            end
        end
        if (imgDir[i,j] == 135)
            if (imgMag[i,j] > imgMag[i-1,j-1] && imgMag[i,j] > imgMag[i+1,j+1])
                if (imgMag[i,j] > 255)
                    maxSup[i,j] = 255
                else
                    maxSup[i,j] = imgMag[i,j]
                end
            else
                maxSup[i,j] = 0
            end
        end            
    end    

    imageIO.imwriteGray("bFlyMaxSup.txt", maxSup)
    
    # HYSTERESIS THRESHOLDING 
    # Pprocesses the output from the non-maxima suppression.
    # The algorithm uses two thresholds, Tlow and Thigh
    # - A pixel is called strong if maxSup[i,j] > Thigh
    # - A pixel is called weak if maxSup[i,j] <= Tlow
    # - All other pixels are candidate pixels
    
    final = zeros(Int,dx,dy)
    candidates = Point[]
    
    for i=2:dx-1, j=2:dy-1
        if (maxSup[i,j] >= Thigh) && (final[i,j] == 0)
            push!(candidates,Point(i,j))
            while !isempty(candidates)
                node = pop!(candidates)
                x = node.x
                y = node.y
                if (x < 0 || x >= dx || y < 0 || y >= dy)
                    continue
                end
                if (maxSup[x,y] < Tlow)
                    continue
                end
                if (final[x,y] != 255)
                    final[x,y] = 255
                    push!(candidates,Point(x+1,y-1))              
                    push!(candidates,Point(x+1,y  ))              
                    push!(candidates,Point(x+1,y+1))              
                    push!(candidates,Point(x  ,y+1))              
                    push!(candidates,Point(x  ,y-1))              
                    push!(candidates,Point(x-1,y-1))              
                    push!(candidates,Point(x-1,y  ))              
                    push!(candidates,Point(x-1,y+1))          
                end
            end
        end
    end
    
    return final    
 
end



end