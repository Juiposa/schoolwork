include("imageFILTER.jl")

module imageMETRICS

# ---------------------------------
# Functions to calculate image quality metrics
# ---------------------------------
# --NOISE--
# RankNEI()        - Derives Rank's Noise Estimation Index
# noiseAI()        - Noise Amplification Index (NAI)
# --BLUR/SHAPRNESS--
# perblurMetric()  - Perceptual blur metric

using imageFILTER

# Filter to calculate Rank's Noise Estimation Index (NEI)
#
# Ref(s):
# - Rank, K., Landl, M., Unbehauen, R., "Estimation of image noise variance",
#   IEE Proceedings Vision, Image and Signal Processing, 1999, Vol.146, pp.80-84.

function RankNEI(img, wsize=1)

    dx,dy = size(img)
    imgN = copy(img)

    K = 1 # gives a 3x3 window

    # Step 1: Suppression
    # -------------------
    # Vertical filter Y1 (Eq.2)
    coeff = (1.0/sqrt(2.0))
    Y1 = zeros(dx,dy);
    for i=1:dx-1, j=1:dy-1
        Y1[i,j] = coeff * (img[i+1,j] - img[i,j]);
    end

    # Horizontal filter (Eq.3)
    Y2 = zeros(dx,dy);
    for i=1:dx-1, j=1:dy-1
        Y2[i,j] = coeff * (Y1[i,j+1] - Y1[i,j]);
    end
    println("Step 1 complete.")

    # Step 2: Compute the histogram of local standard deviations
    # -------------------
    L = (2*wsize) + 1  # Window size
    Npix = L^ 2        # Number of pixels in the window

    mu = zeros(dx,dy)
    sigma = zeros(dx,dy)

    for i=wsize+1:dx-wsize, j=wsize+1:dy-wsize
        tempMu = 0
        tempSigma = 0
        # Calculate the local mean (Eq.5)
        winL = Y2[i-wsize:i+wsize,j-wsize:j+wsize]
        mu[i,j] = mean(winL)
        # Calculate an estimate of the local noise variance (Eq.4)
        sigma[i,j] = var(winL)
    end

    println("Step 2a complete : (Local Stdev)")

    sigmaSQ = sqrt(sigma)

    Hmax = round(Int,ceil(maximum(sigmaSQ)))
    h = zeros(Hmax)

    # Create a "floating-point" histogram using range-based bins (Eq.7)
    alpha = 1

    h[1] = count(i->(0<=i<=0.5),sigmaSQ)

    for k=2:Hmax
        h[k] = count(i->(k-0.5<=i<k+0.5),sigmaSQ)
    end

    println("Step 2b complete : (Histogram creation)")

    # Step 3: Evaluation of the histogram
    # Calculate the mean square value of the histogram (Eq.8)
    sumK = 0.0

    for k=1:Hmax
        sumK = sumK + k^2.0 * h[k]
    end

    sumh = sum(h)
    nS = sumK / sumh

    # Calculate an initial global estimate for noise variance
    GnS = nS / (alpha^2.0)

    println("Step 3 complete: Histogram equaluation")

    # Step 4: Fade out

    gl = zeros(Hmax)
    beta = 2.15; # Adjustment parameter

    # Use a soft fade-out (cosine) function to reduce the influence of the original image

    lmax = 4
    for l=1:lmax
        for k=1:Hmax          # fade-out process is called iteratively (lmax = 4)
            sl = sqrt(nS)     # Initial sl from Eq.8
            if (k <= sl)      # (Eq.9)
                gl[k] = 1.0
            elseif (k > sl && k <= (beta * sl))
                T = ((beta-k/sl) / (1.0-beta)) * pi
                T1 = 1.0 - cos(T)
                T2 = 0.5 * T1
                gl[k] = T2
            elseif (k > (beta*sl))
                gl[k] = 0.0
            end
        end
        # Calculate an improved value of the mean square
        sumK = 0.0
        sumG = 0.0
        for k=1:Hmax
            sumK = sumK + k^2.0 * gl[k] * h[k]
            sumG = sumG + gl[k] * h[k]
        end
        nS = sumK/sumG
    end

    println("Step 4 complete: Soft fade-out")

    # Final estimate for the noise variance (Eq.11)
    rank = nS / (alpha^2.0)

    return rank
end


# Filter to calculate Noise Amplification Index (NAI)
#
# Ref(s):
# - Rank, K., Landl, M., Unbehauen, R., "Estimation of image noise variance",
#   IEE Proceedings Vision, Image and Signal Processing, 1999, Vol.146, pp.80-84.
# - Sakellaropoilos, P., Costaridou, L., Panayiotakis, G., "A wavelet-
#   based spatially adaptive method for mammographic contrast enhancement",
#   Physics in Medicine and Biology, 2003, Vol.48, pp.787-803.

function noiseAI(imgO, imgE)

    sdn_o = RankNEI(imgO)  # Rank's NEI for the original image
    sdn_e = RankNEI(imgE)  # Rank's NEI for the enhanced image

    println("Rank's NEI Original = ", sdn_o)
    println("Rank's NEI Enhanced = ", sdn_e)

    nai = sdn_o / sdn_e

    println("The noise amplification index = ", nai)

end

# Filter to calculate perceptual blur with a no-reference metric
#
# Ref(s):
# - Crete-Roffet F., Dolmiere T., Ladret P., Nicolas M., "The Blur Effect:
#   Perception and estimation with a new no-reference perceptual blur metric",
#   SPIE Electronic Imaging Symposium Conf Human Vision and Electronic Imaging (2007)
#
#   Note: the output (blur) is in [0,1]; 0 means sharp, 1 means blur

function perblurMetric(img)

    dx,dy = size(img)
    imgN = copy(img)

    # Apply horizontal and vertical strong pass filters using Eq.(1).
    Hv = zeros(9,9)
    Hv[5,:] = 1.0/9.0
    Hh = transpose(Hv)

    # blur the input image in vertical direction
    BLver = imageFILTER.filter_CONV(img,Hv,false)
    # blur the input image in horizontal direction
    BLhor = imageFILTER.filter_CONV(img,Hh,false)

    # Calculate absolute difference images using Eq.(2).

    # variation of the input image (vertical direction)
    DFver = abs(img[1:dx-1,:] - img[2:dx,:])
    # variation of the input image (horizontal direction)
    DFhor = abs(img[:,1:dy-1] - img[:,2:dy])

    # variation of the blurred image (vertical direction)
    DBver = abs(BLver[1:dx-1,:] - BLver[2:dx,:])
    # variation of the blurred image (horizontal direction)
    DBhor = abs(BLhor[:,1:dy-1] - BLhor[:,2:dy])

    # Calculate the variation using Eq.(3)
    # difference between two vertical variations of 2 image (input and blurred)
    Tver = DFver - DBver
    Vver = max(0,Tver)
    # difference between two horizontal variations of 2 image (input and blurred)
    Thor = DFhor - DBhor
    Vhor = max(0,Thor)

    # Calculate the sum of the coefficients DFver, DFhor, Vver, Vhor using Eq.(4).
    SFver = sum(DFver)
    SFhor = sum(DFhor)

    SVver = sum(Vver)
    SVhor = sum(Vhor)

    # Normalize in the range 0 to 1 using Eq.(5).
    blurFver = (SFver-SVver)/SFver
    blurFhor = (SFhor-SVhor)/SFhor

    # Select the more annoying blur from the vertical and horizontal Eq.(6).
    blur = max(blurFver,blurFhor)

    return blur
end




end
