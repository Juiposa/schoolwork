module imageFILTER

# Module to perform image filtering (grayscale)
#
# ---------------------------------
# Image sharpening filters
# ---------------------------------
# filter_sharpUSM()       - Unsharp masking
# filter_sharpUSMgauss()  - Unsharp masking using Gaussian smoothing
# filter_sharpUMOSLap()   - Order statistic Laplacian sharpening
# filter_sharpUSMLofG()   - Unsharp masking using Laplacian of Gaussian
#
# ---------------------------------
# Basic filters
# ---------------------------------
# filter_CONV()           - image convolution
# filter_GAUSSIAN()       - Gaussian smoothing
# filter_MEDIAN()         - median filtering


# Function to perform image convolution using a kernel

function filter_CONV(img, kernel, norm=true, supp=true)

    dx,dy = size(img)
    kx,ky = size(kernel)
    imgN = copy(img)
    
    e = div(kx-1,2)
    
    for i=e+1:dx-e, j=e+1:dy-e
        # Extract the window area
        block = img[i-e:i+e,j-e:j+e]
        r = block .* kernel

        # Sum the kernel
        sumP = sum(r)
        
        # Calculate the average of the kernel if norm[alization] is chosen
        if norm 
             sumP = div(sumP,(kx * ky))
        else
             sumP = round(Int16,sumP)
        end
        
        # Suppress over/undershooting pixels if supp[ression] is chosen
        if supp
            if sumP > 255
                imgN[i,j] = 255
            elseif sumP < 0
                imgN[i,j] = 0
            else
                imgN[i,j] = sumP
            end
        else
            imgN[i,j] = sumP
        end
    end

    return imgN
end


# Function to perform noise reduction using median filter

function filter_MEDIAN(img,n=5)

    dx,dy = size(img)
    
    imgN = copy(img)
    e = div(n-1,2)
    
    for i=e+1:dx-e, j=e+1:dy-e
        # Extract the window area
        block = img[i-e:i+e,j-e:j+e]
        
        # Calculate median of the block
        wMed = round(UInt8,median(block))

        # Assign the values               
        if wMed > 0
            imgN[i,j] = round(UInt8,wMed)
        else
            imgN[i,j] = img[i,j]
    	end
    end
    
    return imgN
end


# Function to perform unsharp masking
# Ref(s):
#   Schreiber, W.F., "Wirephoto quality improvement by unsharp masking",
#   Pattern Recognition, Vol.2(2), pp.117-120 (1970)
#
function filter_sharpUSM(img, lambda=1.0)

    dx,dy = size(img)
    e = 1

    # Discrete approximation of a Laplacian
    kernel = [0 -1 0; -1 4 -1; 0 -1 0]
    imK = filter_CONV(img, kernel, false, false)
    
    #imK = convert(Array{Int,2}, imK)
    println(typeof(imK))
        
    imgN = copy(img)
    
    for i=e+1:dx-e, j=e+1:dy-e
        newPixel = img[i,j] + imK[i,j] # *lambda
        if newPixel > 255
            imgN[i,j] = 255
        else
            imgN[i,j] = newPixel
        end
    end

    return imgN
end

# Function to perform Gaussian smoothing using a Gaussian filter
# of a specified width and a certain value of sigma. 
# Common values include sigma = 1.0/1.41, width=3/5
#

function filter_GAUSSIAN(img,sigma,width)

    dx,dy = size(img)
    half = div(width,2)
    
    # Create a Gaussian kernel
    kernel = zeros(Float16,width,width)
    for i=1:width, j=1:width
        r = i - half
        s = j - half
        kernel[i,j] =exp(-((r^2.0+s^2.0)/(2.0*sigma^2.0)))
    end
        
    # Normalize the kernel
    kSum = sum(kernel)
    kernel = kernel ./ kSum
    
    imgN = copy(img)
    
    for i=half+1:dx-half, j=half+1:dy-half
        # Extract the window area
        block = img[i-half:i+half,j-half:j+half]
        # Apply the kernel and sum
        r = block .* kernel
        sumP = sum(r)
        
        if sumP > 0
            imgN[i,j] = round(Int16,sumP)
        else
            imgN[i,j] = 0
        end
    end      
    return imgN   
end


# Unsharp masking using Gaussian blurring

function filter_sharpUSMgauss(img,sigma,width)

    dx,dy = size(img)
    imgN = copy(img)
    half = div(width,2)

    imgG = filter_GAUSSIAN(img,sigma,width)
    
    # Create the mask by subtracting the Gaussian filtered image from the original
    # essentially leaving the crisp features
    mask = img .- imgG
    
    # Add mask to the original image.
    newImage = img .+ mask
    
    for i=half+1:dx-half, j=half+1:dy-half
        if newImage[i,j] < 0
            imgN[i,j] = 0
        elseif newImage[i,j] > 255
            imgN[i,j] = 255
        else 
            imgN[i,j] = round(Int16,newImage[i,j])
        end
    end    

    return imgN  
end


# Function to perform Order Statistic (OS) Laplacian sharpening
# Ref(s):
# Lee, H.Y., Park, S.Y., "A study of convex/concave edges and
# edge-enhancing operators based on the laplacian", IEEE Transactions on
# Circuits and Systems", Vol.37, No.7, pp.940-946 (1990)

function filter_sharpUMOSLap(img,width)

    dx,dy = size(img)
    # Calculate a median image
    Imed = filter_MEDIAN(img, width);

    # Calculate an average image
    kernel = [1 1 1; 1 1 1; 1 1 1]
    Iav = filter_CONV(img, kernel, true, true)

    # Calculate the Order Statistic Laplacian mask
    Ios = Iav .- Imed;

    # Perform OS Laplacian UM
    # Add the mask to the original image
    newImage = img .+ Ios;
    
    for i=1:dx, j=1:dy
        if newImage[i,j] < 0
            newImage[i,j] = 0
        elseif newImage[i,j] > 255
            newImage[i,j] = 255
        end
    end    

    Ie = round(UInt8, newImage)

    return Ie

end


# Function to perform Laplacian of Gaussian unsharp masking
#  Description 
#    enh_LUM performs unsharp masking using the Laplacian of Gaussian.
#    Given a radius of 3, and a standard deviation of 1.0, the algorithm
#    uses a kernel of the form:
#
#     0.0003    0.0026    0.0086    0.0124    0.0086    0.0026    0.0003
#     0.0026    0.0175    0.0392    0.0431    0.0392    0.0175    0.0026
#     0.0086    0.0392         0   -0.0965         0    0.0392    0.0086
#     0.0124    0.0431   -0.0965   -0.3183   -0.0965    0.0431    0.0124
#     0.0086    0.0392         0   -0.0965         0    0.0392    0.0086
#     0.0026    0.0175    0.0392    0.0431    0.0392    0.0175    0.0026
#     0.0003    0.0026    0.0086    0.0124    0.0086    0.0026    0.0003
#
#  Ref(s):
#    Schreiber, W.F., "Wirephoto quality improvement by unsharp masking",
#    Pattern Recognition, 1970, Vol.2, No.2, pp.117-120. 
#
#    Gonzalez, R.C., Woods, R.E., "Digital Image Processing (2nd ed.)",
#    Prentice Hall, 2002.

function filter_sharpUSMLofG(img, sigma, width)

    dx,dy = size(img)
    # Derive the Laplacian of Gaussian masking kernel (positive discrete Laplacian)
    LoGk = zeros(Float16, width, width)
    R = div(width,2)

    for i = -R:R, j = -R:R
        ki = i + R+1
        kj = j + R+1
        X = ((i^2+j^2) / (2*sigma^2))
        LoGk[ki,kj] = -(1.0/(pi*sigma^4.0)) * (1.0-X) * exp(-X)
    end
    
    # Apply the unsharp masking kernel
    imK = filter_CONV(img, LoGk, false, false)

    # Subtract the mask from the original image
    newImage = img .- imK
    println(img[1:5,1:5])
    println(newImage[1:5,1:5])
    
    for i=1:dx, j=1:dy
        if newImage[i,j] < 0
            newImage[i,j] = 0
        elseif newImage[i,j] > 255
            newImage[i,j] = 255
        end
    end    

    Ie = round(UInt8, newImage)

    return Ie

end

end