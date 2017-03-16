module imageBINARIZE

# Module to perform image binarization (thresholding)
#
# ---------------------------------
# Adaptive (localized) thresholding
# ---------------------------------
#  niblack()     - Niblack's algorithm OK
#  bernsen()     - Bernsen's algorithm (DRAFT CODE)
#  sauvola()     - Sauvola's algorithm OK
#
# ---------------------------------
# Clustering-based thresholding
# ---------------------------------
#  otsu()        - Otsu's algorithm OK
#  minimumError()- Minimum Error algorithm (Kittler) OK
#
# ---------------------------------
# Attribute-based thresholding
# ---------------------------------
#  moments()     - Moment-preserving (Tsai) OK
#
# ---------------------------------
# Entropy-based thresholding
# ---------------------------------
#  maximumError()- Maximum entropy, Kapur's algorithm OK
#  entropyPun()  - Pun's entropy
#
# ---------------------------------
# Misc. functions
# ---------------------------------
#  im2bw()       - Function to perform global thresholding
#  getIMGhist()  - Function to derive the image histogram
#  entropy()     - Function to calculate entropy


function flog(x)
    if ((x > 0.0) || (x < 0.0))
        fx = log10(x);
    else
        fx = 0.0;
    end
end

# Function to perform global image thresholding
#
# Parameters:
# (in)  img  :  gray-scale image
# (in)  thr  :  threshold value (0->255)
# (out) imgN :  binary image
#
function im2bw(img, thr)

    dx,dy = size(img)
    imgN = copy(img)

    for i = 1:dx, j = 1:dy
        if (im[i][j] < thr)
            imgN[i,j] = 0
        else
            imgN[i,j] = 255
        end
    end
    
	return imgN
end


# Function to display the histogram of an image 
function getIMGhist(img,nBin=256)

    # the histogram of the data
    dx,dy = size(img)
    hst = [1:nBin;]
    hst[1:end] = 0
    
    for i=1:dx, j=1:dy
        hst[img[i,j]+1] = hst[img[i,j]+1] + 1
    end
    return hst
end

# Function to calculate entropy
function entropy(p)

    # Process the non-zero pixels, set the entropy of zero values to zero
    J = zeros(Float32, 256)

    value = zeros(Float32,length(p))
    for i = 1:length(p)
        if (p[i] > 0.0)
            value[i] = -(p[i] .* flog(p[i]))
        end
    end
    return value
end


# Function to perform image thresholding using Otsu's algorithm
#
# Type: clustering threshold algorithm
#
# Parameters:
# (in)  im     :  gray-scale image
# (in)  nbins  :  number of bins in the histogram
# (out) tvalue :  threshold value
#
# Ref(s):
#   Otsu, N., "Threshold selection using grey level histograms", IEEE
#   Transactions on Systems, Man and Cybernetics, Vol.9(1), pp.62-66 (1979)
#
# Notes: Variables coincide with the original paper

function otsu(img, nbins=256)
    
    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    hst = getIMGhist(img)

    # Normalize the histogram 0->1 (Eq.1)
    hstP = hst / imgSize

    # Calculate the total mean level of the original image (Eq.8)
    mu_T = 0.0
    for i = 1:256
        mu_T = mu_T + i * hstP[i]
    end
    
    sigma = zeros(Float32, 256)
    
    for k = 1:256
        # Calculate the zero-order cumulative moments up to the t-th level
        w_k = sum(hstP[1:k])    # (Eq.6)
        
        # Calculate the first-order cumulative moments up to the t-th level
        mu_k = 0.0
        for i = 1:k                 
            mu_k = mu_k + i * hstP[i]    # (Eq.7)
        end
        
        # Calculate  the variance of the class separability   (Eq.18)
        if (w_k != 0.0) && (w_k != 1.0)
            sigma[k] = ((mu_T * w_k - mu_k)^2.0) / (w_k * (1.0-w_k))
        else
            sigma[k] = 0.0
        end
    end
    
    # Choose the threshold for which the variance of class separability is
    # at its maximum. Return the index of this value (Eq.19)
    tvalue = indmax(sigma)
    
    return tvalue
end

# Function to perform image thresholding using the Minimum error algorithm
#
# Type: clustering threshold algorithm
#
# Parameters:
# (in)  im     :  gray-scale image
# (in)  nbins  :  number of bins in the histogram
# (out) tvalue :  threshold value
#
# Ref(s):
#   Kittler, J., Illingworth, J., "Minimum error thresholding", Pattern
#   Recognition, Vol.19(1), pp.41-47 (1986)
#

function minimumError(img, nbins=256)
    
    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    hst = getIMGhist(img)
    indx = [1:256;]

    J = zeros(Float32, 256)
    tbest = 1
    
    # Compute the priori probability
    for t = 1:256

        # (Eq. 5,8,9 for i=1)
        Pt1 = sum(hst[1:t])  # (Eq.5 for i=1)
        sigma1 = 0.0
        if (Pt1 > 0)
            mean1 = sum(hst[1:t] .* indx[1:t]) / Pt1          # (Eq.6 for i=1)
            for k = 1:t                               
                sigma1 = sigma1 + (k - mean1)^2.0 * hst[k]    # (Eq.7 for i=1)
            end
            sigma1 = sqrt(sigma1 / Pt1)
        end

        # (Eq. 5,8,9 for i=2)
        Pt2 = sum(hst[t+1:256])  # (Eq.5 for i=2)
        sigma2 = 0.0
        if (Pt2 > 0)
            mean2 = sum(hst[t+1:256] .* indx[t+1:256]) / Pt2  # (Eq.6 for i=2)
            for k = t+1:256                                   
                sigma2 = sigma2 + (k - mean2)^2.0 * hst[k]    # (Eq.7 for i=2)
            end
            sigma2 = sqrt(sigma2 / Pt2)
        end
        
        # (Eq.15)
        J[t] = 1.0 + 2.0 * (Pt1*flog(sigma1) + Pt2*flog(sigma2)) 
                   - 2.0 * (Pt1*flog(Pt1) + Pt2*flog(Pt2))
    end
    
    # Choose the threshold for which the error is at a minimum. 
    # Return the index of this value (Eq.13)
    tvalue = indmin(J)
   
    return tvalue    
    
end

# Function to perform maximum entropy based thresholding using Kapurs's algorithm
#
# Parameters:
# (in)    im     :  gray-scale image
# (out)   tvalue :  threshold value
#
# Ref(s):
# Kapur, J.N., Sahoo, P.K., Wong, A.K.C., "A new method for grey-level picture
# thresholding using the entropy of the histogram", Graphical Models and Image
# Processing, Vol.29(3), pp.273-285 (1985)
#
function maximumEntropy(img)

    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    hst = getIMGhist(img)

    F = zeros(Float32, 256)

    # Normalize the histogram 0->1
    pD = hst / imgSize

    # Calculate the cumulative distribution function of the normalized histogram
    cdf = cumsum(pD) 
        
	# Calculate the function to be maximized
    for s = 1:256
        Ha = 0.0
        Hb = 0.0
        
        for i = 1:s
            if (pD[i] > 0.0) && (cdf[i] > 0.0)
                Ha = Ha + (-pD[i]/cdf[s] * log(pD[i]/cdf[s]))  # (Eq.16)
            end
        end
                
        for j = s+1:256
            if (pD[j] > 0.0) && (cdf[j] > 0.0)
                Hb = Hb + (-pD[j]/(1.0-cdf[s]) * log(pD[j]/(1.0-cdf[s])))  # (Eq.17)
            end
        end
                
        F[s] = Ha + Hb
        println(s, " ", F[s])
    end
        
    # Choose the maximum value amongst all the entropies
    tvalue = indmax(F)
    
    return tvalue
end

#  Function to perform adaptive image thresholding using Niblack's algorithm
#
#  The threshold value at each pixel im[i][j] is calculated as the sum of 
#  the mean and the standard deviation (times a constant, k) of the  
#  neighbourhood surrounding the pixel (n = size of the neighbourhood).
#  Note: Does not work well in images where the background has light texture
#
#  Type: adaptive localized threshold algorithm
#
#  Parameters:
#  (in)  img :  gray-scale image
#  (in)   k  :  constant value
#  (in)   n  :  size of the neighbourhood (nxn) (default=5)
#  (out) imgN:  binary image
#
#  Example:    t = niblack(img,,5)
#
#  Ref(s):
#  Niblack, W., An Introduction to Digital Image Processing, Prentice Hall
#  pp.115-116 (1986)
#
function niblack(img, k, n=5)
    
    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    v = div((n-1),2)
        
	# Process the image
	for i = v+1:dx-v, j = v+1:dy-v
        # Extract the neighbourhood area
        block = img[i-v:i+v, j-v:j+v]
                   
        # Calculate the mean and standard deviation of the neighbourhood region
        wBmn = mean(block)
        wBstd = std(block)
            
        # Calculate the threshold value
        wBTH = (wBmn + k * wBstd)
            
        # Threshold the pixel
        if (img[i,j] < wBTH)
            imgN[i,j] = 0
        else
            imgN[i,j] = 255
        end
    end
            
    return imgN
end

#  Function to perform adaptive image thresholding using Bernsen's algorithm
#
#  Type: adaptive localized threshold algorithm
#
#  Parameters:
#  (in)  im  :  gray-scale image
#  (in)  TH  :  Integer representing the local contrast threshold
#  (in)  w   :  Integer representing window size
#  (in)  L   :  Integer representing (0) low and (1) high homogeneous areas
#  (out) img :  binary image
# 
#  Example:    t = bernsen(img,90,11,0)
#
#  Ref(s):
#  Bernsen, J., "Dynamic thresholding of grey-level images",
#  Int. Conf. on Pattern Recognition, pp.1251-1255 (1986).
#

function bernsen(img, TH, w, L)

    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    hst = getIMGhist(img)

    maxR = floor(Int16, dx/w)
    maxC = floor(Int16, dy/w)
    
    bL = zeros(Int16, w, w)

	# Process the image
    for i = 1:maxR:w*maxR
        bL[:,:] = 0
        for j = 1:maxC:w*maxC
            # Extract the neighbourhood area
            block = img[i:i+(w-1), j:j+(w-1)]
            # Calculate the min and max of the neighbourhood region
            Zlow = minimum(block)
            Zhigh = maximum(block)
            
            if ((Zhigh - Zlow) < TH && (L == 1))
                bL[:,:] = 255
            elseif ((Zhigh - Zlow) < TH && (L == 0))
                bL[:,:] = 0
            else
                T = round((Zlow + Zhigh)/2.0)
                for x = 1:w, y =1:w
                    if (block[x,y] >= T)
                        bL[x,y] = 255
                    end
                end
            end
            img[i:i+(w-1), j:j+(w-1)] = bL
		end
	end
    return img
end

#  Function to perform adaptive image thresholding using Sauvola's algorithm
#
#  A modified version of Niblack's algorithm in which a threshold is computed
#  with the dynamic range of standard deviation, R. The local mean is used to 
#  multiply terms R and a fixed value k. This has the effect of amplifying the
#  contribution of the SD in an adaptive manner.
#
#  Type: adaptive localized threshold algorithm
#
#  Parameters:
#  (in)  im  :  gray-scale image
#  (in)   R  :  dynamic range of standard deviation (default=128)
#  (in)   k  :  parameter with positive values (default=0.5)
#  (in)   n  :  size of the neighbourhood (nxn) (default=5)
#  (out) img :  binary image
# 
#  Example:    t = sauvola(img,5,128,0.5)
#
#  Ref(s):
#  Sauvola, J., Pietikainen, M., "Adaptive document image binarization", 
#  Pattern Recognition, Vol.33, pp.225-236 (2000)
#
function sauvola(img, n=5, R=128 ,k=0.5)

    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    #hst = getIMGhist(img)
    
    v = div((n-1),2)
        
	# Process the image
    for i=1+v:dx-v, j=1+v:dy-v
    
        # Extract the neighbourhood area
        block = img[i-v:i+v, j-v:j+v]
                  
        # Calculate the mean and standard deviation of the neighbourhood region
        wBmn = mean(block)
        wBstd = std(block)
            
        # Calculate the threshold value (Eq.5)
        wBTH = round(Int16, (wBmn * (1 + k * ((wBstd/R) - 1))))
            
        # Threshold the pixel
        if (img[i,j] < wBTH)
            imgN[i,j] = 0
        else
            imgN[i,j] = 255
        end
    end
            
    return imgN
end

#  Function to perform image thresholding using Moment preservation
#
#  Type: adaptive localized threshold algorithm
#
#  Parameters:
#  (in)  im     :  gray-scale image
#  (out) tvalue :  threshold value
# 
#  Example:    t = moments(img)
#
#  Ref(s):
#  Tsai, H., "Moments preserving thresholding: A new approach", 
#  Computer Vision, Graphics and Image Processing, Vol.29(3), pp.377-393 (1985)
#
function moments(img)

    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    hst = getIMGhist(img)

    # Normalize the histogram 0->1
    pD = hst / imgSize
    #for k = 1:256
    #    @printf("cdf %d %.6lf\n", k, pD[k])
    #end
    
    m1 = 0.0
    m2 = 0.0
    m3 = 0.0
    
    # 0th moment
    m0 = 1.0
    
    # Calculate the moments 1-> 3 (Eq.2)
    for i = 1:256
        m1 = m1 + i * pD[i]
        m2 = m2 + (i^2.0 * pD[i])
        m3 = m3 + (i^3.0 * pD[i])
    end
    
    # Eqns from Appendix A1(i)
    cD = m0 * m2 - m1^2.0
    c0 = (m1 * m3 - m2^2.0) * (1.0/cD)
    c1 = (m1 * m2 - m0 * m3) * (1.0/cD)
        
    # Eqns from Appendix A1(ii)
    z0 = 0.5 * (-c1 - sqrt(c1^2.0 - 4*c0))
    z1 = 0.5 * (-c1 + sqrt(c1^2.0 - 4*c0))
    
    # Eqns from Appendix A1(iii)
    pd = z1 - z0
    p0 = (1.0/pd) * (z1 - m1)
    p1 = 1.0 - p0;
    
    # Choose the value of the threshold nearest to p0 with respect to 
    # the cumulative probabilities
    cdf = cumsum(pD) 
    
    for k=1:256
        println(k, " ", cdf[k])
    end

    moments = cdf - p0
    moments = abs(moments)
    
    tvalue = indmin(moments)
    
    return tvalue
end

# Function to perform image thresholding using Pun's Entropy
#
# Parameters:
# (in)  im     :  gray-scale image
# (out) tvalue :  threshold value
#
# Ref(s):
# Pun, T., "A new method for grey-level picture thresholding using the entropy of a 
#   histogram," Signal Processing, 1980, Vol. 2, pp.223-237.
#
function entropyPun(img)

    dx,dy = size(img)
    imgSize = dx * dy
    imgN = copy(img)

    # Get the image histogram
    hst = getIMGhist(img)

    # Normalize the histogram 0->1
    pD = hst / imgSize

	Fe = zeros(Float32, 256)
	x = zeros(Float32, 256)
	
	# Pt is the cumulative probability up to graylevel t
    # Ht is the entropy of the black pixels as thresholded by t
    # HT is the total entropy

    x = entropy(pD)
    Pt = cumsum(pD)
    Ht = cumsum(x)
    HT = Ht[end]
    
    # Calculate the evaluation function to be maximized at all levels

    t = 2;
    for s = 1:255
        to = maximum(pD[1:s])
        from = maximum(pD[s+1:end])
	    if (to > 0.0) && (from > 0.0)
	        x = (Ht[s]/HT) * (flog(Pt[s])/flog(to)) #[Eqn.20]
	        y = 1.0 - (Ht[s]/HT)
	        z = flog(1.0 - Pt[s])/flog(from)
        else 
            x = 0.0
            y = 0.0
            z = 0.0
        end
	    Fe[s] = x + y * z
    end
    
    tvalue = indmax(Fe)

    return tvalue
end

end