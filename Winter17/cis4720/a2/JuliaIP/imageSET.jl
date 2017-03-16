module imageSET

# ---------------------------------
# Image Set Functions (to be used with morphology)
# ---------------------------------
# imUnion()             - Derives the pixelwise maximum of two images
# imIntersect()         - Derives the pixelwise maximum of two images
# imComplement()        - Derive the complement of an image (negative)
# isBinary()            - Function to determine whether an image is binary
# labelBW()

# GLOBALS
    type Point
      x::Int
      y::Int
    end


# Creates an image by taking the pixelwise maximum between
# the images img1 and img2. When img1 and img2 are binary images, the
# result represents the their union.

function imUnion(img1, img2)

    dx1,dy1 = size(img1)
    dx2,dy2 = size(img2)
    
    if dx1 != dx2 || dy1 != dy2
        println("incompatible image sizes")
    end
    
    imgU = max(img1,img2)

    return imgU
end

# Creates an image by taking the pixelwise minimum between
# the images img1 and img2. When img1 and img2 are binary images, the
# result represents the their intersection.

function imIntersect(img1, img2)

    dx1,dy1 = size(img1)
    dx2,dy2 = size(img2)
    
    if dx1 != dx2 || dy1 != dy2
        println("incompatible image sizes")
    end
    
    imgU = min(img1,img2)

    return imgU
end

# Function to derive negative binary image

function imComplement(img)
 
    dx,dy = size(img)
    for i=1:dx, j=1:dy
        if img[i,j] == 0
            img[i,j] = 1
        else 
            img[i,j] = 0
        end
    end
    return img
end

# Function to determine whether or not an image is binary.
#
# Syntax:
# imS = isBinary(img)
# This function returns a value of true if the image img is a binary image.
#
function isBinary(img)

    dx,dy = size(img)
    isZero::Int32 = 0
    isOne::Int32 = 0

    for i=1:dx, j=1:dy
        if img[i,j] == 1
        	isOne = isOne + 1
        elseif img[i,j] == 0
            isZero = isZero + 1
        end
    end
    
    if (isZero + isOne == dx * dy)
        return true
    else
        return false
    end    
end

# Function to compute the connected components of a binary image.
# Algorithm is non-recursive, using a stack
#
function labelBW(img)

    dx,dy = size(img)
    labels = zeros(UInt8,dx,dy)
    visited = zeros(UInt8,dx,dy)
    IDc = 1
    
    stackP = Point[]

    for i=1:dx, j=1:dy
        if img[i,j] == 0
            visited[i,j] = 1
        elseif visited[i,j] == 1
            continue
        else
            # Initialize the stack with this location
            push!(stackP,Point(i,j))
            
            while !isempty(stackP)
                # Pop off the stack
                loc = pop!(stackP)
            
                # If this location has been visited, continue
                if visited[loc.x,loc.y] == 1
                    continue
                end
                
                # Mark the location as true and mark this location with a unique ID
                visited[loc.x,loc.y] = 1
                labels[loc.x,loc.y] = IDc
                
                # Look at the 8 neighbouring locations
                for nx=-1:1, ny=-1:1
                    # Ignore out-of-bounds
                    if loc.x+nx < 1 || loc.x+nx > dx || loc.y+ny < 1 || loc.y+ny > dy
                        continue
                    # Ignore locations already visited
                    elseif visited[loc.x+nx,loc.y+ny] == 1
                        continue
                    # Ignore locations that are zero
                    elseif img[loc.x+nx,loc.y+ny] == 0
                        continue
                    # Add location to the stack
                    else
                        push!(stackP,Point(loc.x+nx,loc.y+ny))
                    end
                end
            end
            IDc = IDc + 1
        end 
    end     
                
    return labels, IDc-1
    
end  

# Function to return statistics about the numR regions in a labeled image 
# area = area of each region in pixels
#
function regionStats(img, numR, stat="area")

    stats = []
    if stat == "area"
        for i=1:numR
            # Find pixel labelled with i
            pX = find(x -> x == i, img)
            # Count the number of pixels
            area = length(pX)
            push!(stats, area)
        end
    end
    return stats
end

function fillIt(img, imgL, numR, rS, rArea)

    for i=1:numR
        println(i,"  ",rS[i])
        if rS[i] < rArea
            m = findin(imgL,i)
            img[m] = 0
        end
    end
    
end



end