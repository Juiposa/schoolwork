module imageENH

# Module to perform image enhancement (grayscale)
#
# ---------------------------------
# Noise suppression filters
# ---------------------------------
# enh_truncMedian()      - truncated median filter
# filter_MEAN()          - mean (averaging) filter
# enh_hybridMedian()     - hybrid median filter
# enh_alphaTMean()       - alpha trimmed means filter
# filter_wMEDIAN()       - weighted median filter
# Kuwahara()             - Kuwahara edge preserving smoothing filter
# NagaoMatsuyama()       - Nagao Matsuyama edge preserving smoothing filter

# Function to perform noise reduction using truncated median "mode"
#
# Ref(s):
#   Davies, E.R., "On the noise suppression and image enhancement
#   characteristics of the median, truncated median and mode filters",
#   Pattern Recognition Letters, Vol.7, pp.87-97 (1988)
#

function enh_truncMedian(img,n=5)

    dx,dy = size(img)
    #println(dx," x ", dy)

    imgN = copy(img)
    e = div(n-1,2)

    for i=e+1:dx-e, j=e+1:dy-e
        # Extract the window area
        block = img[i-e:i+e,j-e:j+e]
        # println(i, " ",j," ", length(block))

        # Calculate vector statistics
        wMean = round(UInt8,mean(block))
        wMin = minimum(block)
        wMax = maximum(block)
        wMed = round(UInt8,median(block))

        # Calculate the bounds, and select the appropriate elements
        if wMed < wMean
            upper = 2 * wMed - wMin
            NwB = block[block .< upper]
        else
            lower = 2 * wMed - wMax
            NwB = block[block .> lower]
        end

        # Calculate the median of the selected elements
        if length(NwB) == 0
            xmed = 0
        else
        	xmed = median(NwB)
        end

        # Assign the values
        if xmed > 0
            imgN[i,j] = round(UInt8,xmed)
        else
            imgN[i,j] = img[i,j]
    	end
    end

    return imgN
end

# Function to perform a mean smoothing filter on an image
# Function processes the image based on the size of the filter
# being used, default is diameter=5

function filter_MEAN(img,n=5)

    dx,dy = size(img)
    imgN = copy(img)
    e = div(n,2)

    for i=e+1:dx-e, j=e+1:dy-e
        block = img[i-e:i+e,j-e:j+e]
        mn = mean(block)
        imgN[i,j] = round(UInt8,mn)
    end

    return imgN
end

# Function to perform noise reduction using hybrid median
#
# Extracts medians from a 5x5 neighbourhood using two masks:
#
#        1 0 0 0 1          0 0 1 0 0
#        0 1 0 1 0          0 0 1 0 0
#        0 0 1 0 0   and    1 1 1 1 1
#        0 1 0 1 0          0 0 1 0 0
#        1 0 0 0 1          0 0 1 0 0
#
# The hybrid median is then calculated as the median of three values comprising
# the two medians above and the pixel in the original image.
#
# Ref(s):
#

function enh_hybridMedian(img,n=5)

    dx,dy = size(img)
    #println(dx," x ", dy)

    imgN = copy(img)
    v = div(n-1,2)

    # Derive indices for the two patterns representing X and +
    indicesC = [1,5,7,9,13,17,19,21,25]
    indicesP = [3,8,11,12,13,14,15,18,23]

	# Process the image (ignoring the outer two layers of the image boundary
	e = 2
    for i=e+1:dx-e, j=e+1:dy-e
        # Extract the neighbourhood area
        block = img[i-e:i+e,j-e:j+e]

        # Reshape the neighborhood into a vector by flattening the 2D block
        wB = vec(reshape(block,1,25))

        # Extract pixel values using indices
        wBc = wB[indicesC]
        wBp = wB[indicesP]

        # Calculate the median values
        wBcMed = median(wBc)
        wBpMed = median(wBp)

        # Calculate the hybrid median of the original pixel, and the two
        # medians extracted above
        xmed = median([wBcMed,wBpMed,img[i,j]])

        # Assign the values
        if xmed > 0
            imgN[i,j] = round(UInt8,xmed)
        else
            imgN[i,j] = img[i,j]
    	end
    end

    return imgN
end

# Function to perform noise reduction using alpha-trimmed means
#
# alpha is a parameter describing how many elements to trim from the
# sorted vector representing the image neighborhood. For example in a
# 5x5 neighborhood, with alpha=0.2, 5 elements would be trimmed from either end.
#
# For example:
#
#        23 16 23 43 54
#        12 23 34 54 32
#        23 34 49 3  21
#        24 55 65 12 4
#         8  9  7 21 12
#
# Vector:
#
#     (3,4,7,8,9,12,12,12,16,21,21,23,23,23,23,24,32,34,34,43,49,54,54,55,65)
#
# Mean = 26
#
# Trimmed Vector (alpha = 0.2 elements):
#
#     (12,12,12,16,21,21,23,23,23,23,24,32,34,34,43)
#
# Trimmed Mean = 23
#
# The value of alpha is restricted to the interval 0<=alpha<0.5 Ideally in a
# 5x5 neighbourhood, the use of alpha=0.5 will result in the median filter
#
# Ref(s):
#   Bednar, J.B., Watt, T.L., "Alpha-trimmed means and their relationship
#   to median filters", IEEE Transactions on Acoustics, Speech and Signal
#   Processing, Vol.32(1), pp.145-153 (1984)
#

function enh_alphaTMean(img,alpha,n=5)

    dx,dy = size(img)

    imgN = copy(img)
    e = div(n-1,2)

    # Calculate the trim coefficient
    b = round(UInt8, (n*n)*(alpha))

	# Process the image
    for i=e+1:dx-e, j=e+1:dy-e
        # Extract the neighbourhood area
        block = img[i-e:i+e,j-e:j+e]

        # Reshape the neighborhood into a vector by flattening the 2D block
        wB = vec(reshape(block,1,25))

        # Sort the vector into ascending order
        wB = sort(wB)
        len = length(wB)

        # Trim b elements from each end of the vector
        if (b != 0)
            nwB = wB[b+1:len-b]
        end

        # Calculate the mean of the trimmed vector
        tMean = mean(nwB)

        # Assign the values
        if (tMean > 0)
            imgN[i,j] = round(UInt8,tMean)
        end
    end
    return imgN
end

# Function to perform noise reduction using a weighted median filter
#
# It has the spike-noise removal and backgroundung capabilties of the
# median filter, but has greater control in the way they operate. To
# avoid biasing the replacement of top, bottom or one side of a value, a
# natural limitation is applied for general use, eightfold-symmetry:
#
#    A mask of extent 3:
#
#        r   s   r
#        s   t   s
#        r   s   r
#
#     A mask of extent 5
#
#        u   v   w   v   u
#        v   r   s   r   v
#        w   s   y   s   w
#        v   r   s   r   v
#        u   v   w   v   u
#
#     Note that this restriction is NOT necessary for use of the filter.
#
#      e.g.   1   1   1
#             1   3   1
#             1   1   1
#
#      applied to an image region:
#
#             14  51  36
#             18  17  42
#             21  31  36
#
#      leads to a sorted list:
#
#             (14, 17, 17, 17, 18, 21, 31, 36, 36, 42, 51)
#
#      median = 21
#
#  Ref(s):
#    Brownrigg, D.R.K., "The weighted median filter", Communications of the
#    ACM, 1984, Vol.27, No.8, pp.807-818

function filter_wMEDIAN(img, mask=[1 1 1;1 3 1;1 1 1])

    dx,dy = size(img)
    mx,my = size(mask)
    imgN = copy(img)

    e = div(mx, 2)

	# Process the image
    for i=e+1:dx-e, j=e+1:dy-e
        # Extract the neighbourhood area
        block = img[i-e:i+e,j-e:j+e]

        # Create a list to store block elements
        mlist = []
        # Create a list of the weighed intensity values
        for x=1:mx, y=1:my
            for z=1:mask[x,y]
                push!(mlist,block[x,y])
            end
        end

        # Calculate the median of the weighted set of intensity values
        wMed = median(mlist)

	    # Assign the values
        if wMed > 0
            imgN[i,j] = round(UInt8,wMed)
        else
            imgN[i,j] = img[i,j]
    	end
    end

    return imgN

end

# Function to perform noise reduction and smoothing using the Kuwahara filter
# The basic Kuwahara filter does the following:
# 1. For each pixel in the image, the four diagonal neighboring square sized windows
#    (northwest, northeast, southeast and soutwest) that overlap with the pixel at their
#    corners are processed to get their mean and standard deviation.
#
#    +-------+---+-------+
#    |       | A |       |
#    |   A   | / |   B   |
#    |       | B |       |
#    +-------+---+-------+
#    |  A/C  |ALL|  B/D  |
#    +-------+---+-------+
#    |       | C |       |
#    |   C   | / |   D   |
#    |       | D |       |
#    +-------+---+-------+
#
# 2. The output image has the corresponding pixel filled with the mean of the four window
#    that has the smallest standard deviation, i.e. the smoothest window.
#
# Ref(s):
#   Kuwahara, M., Hachimura, K., Eiho, S., Kinoshita, M., "Processing of
#   RI-angiocardiographic images," in Digital Processing of Biomedical Images,
#   New York: Plenum, pp.187-202 (1976).
#

function Kuwahara(img,n=5)

    dx,dy = size(img)
    imgN = copy(img)
    edgex = div(n, 2)
    edgey = div(n, 2)

    mid = round(Int,ceil(n/2.0))
    #tot = (dx - edgex - edgex) * (dy - edgey - edgey)
    println(" Applying Kuwahara filter... ")

	# Process the image
    for i=edgex+1:dx-edgex, j=edgey+1:dy-edgey
        # Select the window to process
        block = img[i-edgex:i+edgex,j-edgey:j+edgey]

        # Subdivide window into 4 regions
        region_1 = block[1:mid,1:mid]
        region_2 = block[mid:n,1:mid]
        region_3 = block[1:mid,mid:n]
        region_4 = block[mid:n,mid:n]

        # Find the region with the smallest variance and take its mean
        regions = [region_1; region_2; region_3; region_4]
        region_vars = [var(region_1),var(region_2),var(region_3),var(region_4)]
        imgN[i,j] = mean(regions[indmin(region_vars)])
    end

    return imgN

end

# Function to perform Nagao-Matsuyama edge-preserving smoothing
#
# Ref(s):
#   Nagao, M., Matsuyama, T., "Edge preserving smoothing",
#   Computer Graphics and Image Processing, 9, pp.394-407 (1979).

function NagaoMatsuyama(img,n=5)

    dx,dy = size(img)
    # Create an empty image to store the value into.
    imgN = zeros(dx,dy)

    # Store the indices for each of the 9 regions
    A = [7 8 9 12 13 14 17 18 19]
    B = [2 3 4 7 8 9 13]
    C = [9 10 13 14 15 19 20]
    D = [13 17 18 19 22 23 24]
    E = [6 7 11 12 13 16 17]
    F = [1 2 6 7 8 12 13]
    G = [4 5 8 9 10 13 14]
    H = [13 14 18 19 20 24 25]
    I = [12 13 16 17 18 21 22]

    regions = Any[]
    push!(regions, A)
    push!(regions, B)
    push!(regions, C)
    push!(regions, D)
    push!(regions, E)
    push!(regions, F)
    push!(regions, G)
    push!(regions, H)
    push!(regions, I)

    blockMeans = zeros(9)
    blockVariance = zeros(9)

    v = div(n,2)

    #Start Processing the image
    for i=3:dx-2, j=3:dy-2
        # Extract the neighbourhood and the pixel from the image
        block = img[i-v:i+v,j-v:j+v]

        # Reshape the neighborhood into a vector by flattening the 2D block
        vBlock = vec(reshape(block,1,25))

        # Calculate the means and variances
        for k=1:9
            blockMeans[k] = mean(getindex(vBlock,regions[k]))
            blockVariance[k] = var(getindex(vBlock,regions[k]))

            # Calculate the smallest variance
            minVar = indmin(blockVariance)

            #Set the pixel to the value of the mean that was associated with the variance
            imgN[i,j] = round(UInt8,blockMeans[minVar])
        end
    end

    return imgN
end


end
