module imageHIST

# Module to perform histogram based image processing
#
# ---------------------------------
# HISTOGRAM
# ---------------------------------
# cumhst()        - Function to derive a cumulative histogram
# histeq()                - Function to perform contrast enhancement using 
#                           image histogram equalization
# histhyper()             - Contrast enhancement using histogram hyperbolization
# bihistEQ()              - Bi-histogram equalization


# Function to display the histogram of an image 
#
# Syntax:
#    imgE = getIMGhist(img)
#
# Arguments: 
#    img:  Grayscale image
#   nBin:  number of bins in the histogram (optional, default = 256)
#
# Ref:
#    generic
#
function getIMGhist(img,nBin=256)

    hst = [1:nBin;]
    hst[1:end] = 0    # Create the histogram for the data
    
    if (ndims(img) == 2)
        dx,dy = size(img)
        # Bin each of the intensity values. As the histogram has values
        # 1->256, and the image has values 0->255, and offset of 1 is added.
        for i=1:dx, j=1:dy
            hst[img[i,j]+1] = hst[img[i,j]+1] + 1
        end
    elseif (ndims(img) == 1)
        dx = length(img)
        # Bin each of the intensity values. As the histogram has values
        # 1->256, and the image has values 0->255, and offset of 1 is added.
        for i=1:dx
            hst[img[i]+1] = hst[img[i]+1] + 1
        end        
    end
    
    return hst
end

# Function to derive a cumulative histogram

function cumhst(hist, nBin=256, norm=FALSE)

    d = zeros(Int16,nBin)
    c = 0
    
    # Cumulatively sum the bins from 1 to nBin
    for i = 1:nBin
        c = c + hist[i]
        d[i] = c
    end
    
    # Normalize the cumulative histogram
    if (norm)
        d = d ./ c
    end
                
    return d
end


# Function to perform contrast enhancement using image histogram equalization

function histEQ(img, nBin=256)
    
    dx,dy = size(img)
    imgN = copy(img)
    
    # Calculate the histogram
    imhist = getIMGhist(img,nBin)
    
    # Calculate the probability density function of the histogram
    # Frequency of a pixel / no. of pixels
    histPDF = imhist / (dx * dy)
    
    # Derive the cumulative histogram (cumulative distribution probability)
    cdf = cumsum(histPDF)
    
    # Histogram equalization
    fL = round(Int16, cdf*(nBin-1))
    println(fL)
    
    for i=1:dx, j=1:dy
        imgN[i,j] = fL[img[i,j]+1]
    end

    return imgN
    
end

# Function to perform contrast enhancement using histogram hyperbolization
#   Ref(s):
#   Frei, W., "Image enhancement by histogram hyperbolization", Computer
#   Graphics and Image Processing, Vol.6, pp.286-294 (1977)
#
function histhyper(img, nBin=256)

    dx,dy = size(img)
    imgN = copy(img)
    imSize = dx * dy

    c_value = 0.5
    
    # Get the image histogram
    hst = getIMGhist(img,nBin)
	
    # Normalize the histogram 0.0->1.0
    hstpdf = hst / imSize
    
    # Calculate the cumulative distribution function of the normalized histogram
    cdf = cumsum(hstpdf) 
   
    # Create a vector to store the new histogram
    hY = zeros(Int16,256)
    
    yLog = 1.0 + 1.0 / c_value
    
    # Ref-(Eq.4) 
    for i = 1:256
        hY[i] = c_value * (exp(log(yLog) * cdf[i]) - 1)
    end
    
    # Perform the histogram transformation
    for i = 1:dx, j = 1:dy
        imgN[i,j] = 255 * hY[img[i,j]+1]
    end
      
#    xr = numpy.arange(0,256,1)
#    pylab.plot(xr,hY)
#    pylab.show()

    # Return the modified image, multiplied by 255 to normalize in the range 0->255
    return round(UInt8, imgN)
end

# Function to perform contrast enhancement using mean-preserving bi-histogram equalization
#
# Syntax:
#    imgE = bihistEQ(img)
#
# Arguments: 
#    img:  Grayscale image
#   nBin:  number of bins in the histogram (optional, default = 256)
#
# Ref:
#    Kim, Y.-T. "Contrast enhancement using brightness preserving bi-histogram 
#    equalization", IEEE Transactions on Consumer Electronics, 43, pp.1-8. (1997)
#
function bihistEQ(img, nBin=256)

    dx,dy = size(img)
    imgE = copy(img)
    imSize = dx * dy
    
    gMin = minimum(img)
    gMax = maximum(img)
    
    # Calculate the mean of the image
    Xm = mean(img)
    
    # Calculate the histogram of the image <= Xm (Eq.7)
    p = find(x -> x <= Xm, img)
    Xl = img[p]
    Hl = getIMGhist(Xl)

    # Calculate the probability density function of the subimage <= Xm (Eq.9)
    pL = Hl / (length(Xl))

    # Calculate the cumulative histogram of the image <= Xm (Eq.11)
    cL = cumsum(pL)

    # Calculate the histogram of the image > Xm (Eq.8)
    p = find(x -> x > Xm, img)
    Xu = img[p]
    Hu = getIMGhist(Xu)

    # Calculate the probability density function of the subimage > Xm (Eq.10)
    pU = Hu / (length(Xu))

    # Calculate the cumulative histogram of the image > Xm (Eq.12)
    cU = cumsum(pU)

    # Histogram equalization: make the histogram look uniform.
    fL = round(UInt8, (gMin + (Xm - gMin) * cL))          #(Eq.13)
    fU = round(UInt8, ((Xm+1) + (gMax-(Xm+1)) * cU))      #(Eq.14)

    # Map the image under the new histogram -> Ie. (Eq.16)
    for i=1:dx, j=1:dy
        if (img[i,j] <= Xm)
            imgE[i,j] = fL[img[i,j]+1];
        else
            imgE[i,j] = fU[img[i,j]+1];
        end
    end
    return imgE

end


end