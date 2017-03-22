module colourSPACE

# Module to perform colour space conversion
# 1. RGB => YIQ => RGB
# 2. RGB => HSV => RGB
# 3. RGB => Lab => RGB
# 4. RGB => XYZ => RGB

# ---------------------------------
# YIQ COLOUR SPACE
# ---------------------------------
# The YIQ colour space is used by the NTSC colour system.
#   Y : represents the luma information.
#   I : chrominance information (orange-blue)
#   Q : chrominance information (purple-green)
# FUNCTIONS:
#   rgb2yiq() - Convert RGB to YIQ
#   yiq2rgb() - Convert YIQ to RGB

# Function to convert a colour image from RGB to YIQ colourspace
#
# Syntax:
#    Y, I, Q = rgb2yiq(rgb)
#
# Arguments:
#    rgb:  RGB colour image
#
# Ref:
#    n/a
#
function rgb2yiq(rgb)

    r, g, b = rgb[:,:,1], rgb[:,:,2], rgb[:,:,3]
    r = r / 255.0
    g = g / 255.0
    b = b / 255.0

    y = 0.299 * r + 0.587 * g + 0.114 * b
    i = 0.595716 * r - 0.274453 * g - 0.321263 * b
    q = 0.212456 * r - 0.522591 * g + 0.311135 * b

    return y, i, q
end

# Function to convert a colour image from YIQ to RGB colourspace
#
# Syntax:
#    RGB = rgb2yiq(y, i, q)
#
# Arguments:
#    y:  luma component image
#    i:  chrominance component image
#    q:  chrominance component image
#
# Ref:
#    n/a
#
function yiq2rgb(y, i, q)

    dx,dy = size(y)
    imgRGB = zeros(UInt8, dx, dy, 3)

    r = y + 0.9563 .* i + 0.621 .* q
    g = y - 0.2721 .* i - 0.6474 .* q
    b = y - 1.107 .* i + 1.7046 .* q

    r = r * 255.0
    g = g * 255.0
    b = b * 255.0

    rIndex = numpy.where(r > 255)
    r[rIndex] = 255
    gIndex = numpy.where(g > 255)
    g[gIndex] = 255
    bIndex = numpy.where(b > 255)
    b[bIndex] = 255

    rIndex = numpy.where(r < 0)
    r[rIndex] = 0
    gIndex = numpy.where(g < 0)
    g[gIndex] = 0
    bIndex = numpy.where(b < 0)
    b[bIndex] = 0

    imgRGB[:,:,0] = r
    imgRGB[:,:,1] = g
    imgRGB[:,:,2] = b

    return imgRGB
end

# ---------------------------------
# HSV COLOUR SPACE
# ---------------------------------
# The HSV colour model can be represented by a hex-cone.
#   H : represents the hue information and is a measure of the spectral
#       composition of a colour, and is represented as an angle, which values from 0 to 360.
#   S : represents the saturation, and refers to purity of colours, and varies from 0 to 1.
#   V : represents the darkness of a colour, also ranges from 0 to 1.
# FUNCTIONS:
#   rgb2hsv() - Convert RGB to HSV
#   hsv2rgb() - Convert HSV to RGB

# Function to convert a colour image from RGB to HSV colourspace.
#
# Syntax:
#    H,S,V = rgb2hsv(img)
#
# Arguments:
#    img:  colour image
#
# Ref:
#    n/a
#

function rgb2hsv(rgb)

    dx,dy,dz = size(rgb)
    H = zeros(Float32,dx,dy)
    S = zeros(Float32,dx,dy)
    V = zeros(Float32,dx,dy)

    # Convert 8-bit values to 0->1
    R = rgb[:,:,1] / 255.0
    G = rgb[:,:,2] / 255.0
    B = rgb[:,:,3] / 255.0

    # Highest colour value
    cMax = max(R,G,B)
    # Lowest colour value
    cMin = min(R,G,B)
    # Colour difference
    cDelta = cMax - cMin

    fH = 0.0
    fS = 0.0
    fV = 0.0

    for i=1:dx, j=1:dy
        if (cDelta[i,j] > 0)
            if (cMax[i,j] == R[i,j])
                fH = 60 * mod((G[i,j]-B[i,j])/cDelta[i,j], 6)
            elseif (cMax[i,j] == G[i,j])
                fH = 60 * (((B[i,j]-R[i,j])/cDelta[i,j]) + 2)
            elseif (cMax[i,j] == B[i,j])
                fH = 60 * (((R[i,j]-G[i,j])/cDelta[i,j]) + 4)
            end

            if (cMax[i,j] > 0)
                fS = cDelta[i,j] / cMax[i,j]
            else
                fS = 0
            end

            fV = cMax[i,j]
        else
            fH = 0
            fS = 0
            fV = cMax[i,j]
        end
        S[i,j] = fS
        V[i,j] = fV
        if (fH < 0)
            H[i,j] = fH + 360
        else
            H[i,j] = fH
        end
    end

    return H, S, V

end

# Function to convert a colour image from HSV to RGB colourspace.
#
# Syntax:
#    rgb = hsv2rgb(H, S, V)
#
# Arguments:
#    H:  hue image
#    S:  saturation image
#    V:  value image
#
# Ref:
#    n/a
#

function hsv2rgb(H, S, V)

    dx,dy = size(H)
    imgRGB = zeros(Int16,dx,dy,3)

    fX = zeros(Float32,dx,dy)

    # Derive chroma
    fChroma = V .* S
    fHPrime = mod(H/60.0, 6)

    for i=1:dx, j=1:dy
        fX[i,j] = fChroma[i,j] * (1 - abs(mod(fHPrime[i,j],2) - 1))
    end

    fM = V - fChroma
    fR = 0
    fG = 0
    fB = 0

    for i=1:dx, j=1:dy
        if (0 <= fHPrime[i,j] < 1)
            fR = fChroma[i,j]
            fG = fX[i,j]
            fB = 0
        elseif (1 <= fHPrime[i,j] < 2)
            fR = fX[i,j]
            fG = fChroma[i,j]
            fB = 0
        elseif (2 <= fHPrime[i,j] < 3)
            fR = 0
            fG = fChroma[i,j]
            fB = fX[i,j]
        elseif (3 <= fHPrime[i,j] < 4)
            fR = 0
            fG = fX[i,j]
            fB = fChroma[i,j]
        elseif (4 <= fHPrime[i,j] < 5)
            fR = fX[i,j]
            fG = 0
            fB = fChroma[i,j]
        elseif (5 <= fHPrime[i,j] < 6)
            fR = fChroma[i,j]
            fG = 0
            fB = fX[i,j]
        else
            fR = 0
            fG = 0
            fB = 0
        end

        # Convert the pixels from 0->1 to 0->255 and assign to RGB image
        imgRGB[i,j,1] = round(Int16, 255*(fR + fM[i,j]))
        imgRGB[i,j,2] = round(Int16, 255*(fG + fM[i,j]))
        imgRGB[i,j,3] = round(Int16, 255*(fB + fM[i,j]))
    end

    return imgRGB
end


# CIE Colour Spaces
# The CIE space of visible colour is expressed in several common forms: CIE XYZ (1931),
# CIE L*a*b*, and CIE Lu'v' (1976). Each contains the same colours, but they
# distribute these colours differently.


# ---------------------------------
# CIELab COLOUR SPACE
# ---------------------------------
# The CIELab colour model, actually CIE L*a*b* is a colour model+space combo in which
# L is brightness and a and b are chrominance components, with the difference that the
# colour values are far more than the human gamut.
#   L : lightness information - L=0 (black) to L=100 (white)
#   a : chrominance information (red-green) - green (-ve) to red (+ve)
#   b : chrominance information (yellow-blue) - blue (-ve) to yellow (+ve)
# FUNCTIONS:
#   rgb2lab() - Convert RGB to CIELab (uses rgb2xyz())
#   lab2rgb() - Convert CIELab to RGB (uses xyz2rgb())
#
#   Note when a=0 and b=0 it represents a true neutral gray
#   There are no simple conversions between RGB and CIELab

# Function to convert a colour image from RGB to CIELab colourspace.
#
# Syntax:
#    L, a, b = rgb2lab(rgb)
#
# Arguments:
#    rgb:  RGB colour image
#
# Ref:
#    n/a
#
function rgb2lab(rgb)

    dx,dy,dz = size(rgb)
    L = zeros(Float32,dx,dy)
    a = zeros(Float32,dx,dy)
    b = zeros(Float32,dx,dy)

    X,Y,Z = rgb2xyz(rgb)

    # Observer= 2°, Illuminant= D65
    vX = X / 95.047
    vY = Y / 100.000
    vZ = Z / 108.883

    for i=1:dx, j=1:dy
        rX = vX[i,j]
        rY = vY[i,j]
        rZ = vZ[i,j]

        if (rX > 0.008856)
            rX = rX ^ (1.0/3.0)
        else
            rX = (7.787 * rX) + (16.0/116.0)
        end
        if (rY > 0.008856)
            rY = rY ^ (1.0/3.0)
        else
            rY = (7.787 * rY) + (16.0/116.0)
        end
        if (rZ > 0.008856)
            rZ = rZ ^ (1.0/3.0)
        else
            rZ = (7.787 * rZ) + (16.0/116.0)
        end

        L[i,j] = (116 * rY) - 16
        a[i,j] = 500 * (rX - rY)
        b[i,j] = 200 * (rY - rZ)
    end

    return L, a, b

end

# Function to convert a colour image from CIELab to RGB colourspace.
#
# Syntax:
#    RGB = lab2rgb(L, a, b)
#
# Arguments:
#    L:  lightness component image
#    a:  chrominance component image
#    b:  chrominance component image
#
# Ref:
#    n/a
#
function lab2rgb(L,a,b)

    dx,dy = size(L)

    X = zeros(Float32,dx,dy)
    Y = zeros(Float32,dx,dy)
    Z = zeros(Float32,dx,dy)

    for i=1:dx, j=1:dy
        vY = (L[i,j] + 16) /116.0
        vX = a[i,j] / 500.0 + vY
        vZ = vY - b[i,j] / 200.0

        if (vY^3.0 > 0.008856)
            vY = vY ^ 3.0
        else
            vY = (vY - 16.0 / 116.0) / 7.787
        end
        if (vX^3.0 > 0.008856)
            vX = vX ^ 3.0
        else
            vX = (vX - 16.0 / 116.0) / 7.787
        end
        if (vZ^3.0 > 0.008856)
            vZ = vZ ^ 3.0
        else
            vZ = (vZ - 16.0 / 116.0) / 7.787
        end

        X[i,j] = vX * 95.047
        Y[i,j] = vY * 100.0
        Z[i,j] = vZ * 108.883
    end

    RGB = xyz2rgb(X,Y,Z)

    return RGB


end

# ---------------------------------
# CIEXYZ COLOUR SPACE
# ---------------------------------
# The CIE colour spaces represent a quantitative link between physical pure colours
# (i.e. wavelengths) and physiological perceived colours in human colour vision.
# The CIE XYZ colour space was derived from a series of experiments done in the
# late 1920s by William David Wright and John Guild.
#   X : a linear combination of cone response curves chosen to be nonnegative
#   Y : luminance
#   Z : quasi-equal to blue stimulation, or the S cone response
# FUNCTIONS:
#   rgb2xyz() - Convert RGB to XYZ
#   xyz2RGB() - Convert XYZ to RGB
#

# Function to convert a colour image from RGB to CIEXYZ colourspace.
#
# Syntax:
#    X, Y, Z = rgb2xyz(rgb)
#
# Arguments:
#    rgb:  RGB colour image
#
# Ref:
#    n/a
#
function rgb2xyz(rgb)

    dx,dy,dz = size(rgb)
    X = zeros(Float32,dx,dy)
    Y = zeros(Float32,dx,dy)
    Z = zeros(Float32,dx,dy)

    # Convert 8-bit values to 0->1
    R = rgb[:,:,1] / 255.0
    G = rgb[:,:,2] / 255.0
    B = rgb[:,:,3] / 255.0

    for i=1:dx, j=1:dy
        vR = R[i,j]
        vG = G[i,j]
        vB = B[i,j]

        if (vR > 0.04045)
            vR = ((vR + 0.055)/1.055) ^ 2.4
        else
            vR = vR / 12.92
        end
        if (vG > 0.04045)
            vG = ((vG + 0.055)/1.055) ^ 2.4
        else
            vG = vG / 12.92
        end
        if (vB > 0.04045)
            vB = ((vB + 0.055)/1.055) ^ 2.4
        else
            vB = vB / 12.92
        end
        vR = vR * 100
        vG = vG * 100
    	vB = vB * 100

    	# Observer. = 2°, Illuminant = D65
        X[i,j] = vR * 0.4124 + vG * 0.3576 + vB * 0.1805;
        Y[i,j] = vR * 0.2126 + vG * 0.7152 + vB * 0.0722;
        Z[i,j] = vR * 0.0193 + vG * 0.1192 + vB * 0.9505;
    end

    return X, Y, Z

end

# Function to convert a colour image from CIEXYZ to RGB colourspace.
#
# Syntax:
#    RGB = rgb2xyz(X, Y, Z)
#
# Arguments:
#    X:  X component image
#    Y:  luminance component image
#    Z:  Z component image
#
# Ref:
#    n/a
#
function xyz2rgb(X, Y, Z)

    dx,dy = size(X)

    RGB = zeros(Int16,dx,dy,3)

    vX = X / 100.0
    vY = Y / 100.0
    vZ = Z / 100.0

    for i=1:dx, j=1:dy
        vR = vX[i,j] *  3.2406 + vY[i,j] * -1.5372 + vZ[i,j] * -0.4986
        vG = vX[i,j] * -0.9689 + vY[i,j] *  1.8758 + vZ[i,j] *  0.0415
        vB = vX[i,j] *  0.0557 + vY[i,j] * -0.2040 + vZ[i,j] *  1.0570

        if (vR > 0.0031308)
            vR = 1.055 * (vR^(1/2.4)) - 0.055
        else
            vR = vR * 12.92
        end
        if (vG > 0.0031308)
            vG = 1.055 * (vG^(1/2.4)) - 0.055
        else
            vG = vG * 12.92
        end
        if (vB > 0.0031308)
            vB = 1.055 * (vB^(1/2.4)) - 0.055
        else
            vB = vB * 12.92
        end
        RGB[i,j,1] = round(Int16,vR * 255)
        RGB[i,j,2] = round(Int16,vG * 255)
    	RGB[i,j,3] = round(Int16,vB * 255)

    end

    return RGB
end

end
