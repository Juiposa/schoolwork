using Gadfly

module imageIO

# ---------------------------------
# Image I/O for ASCII images
# ---------------------------------

# imreadGray   - read a text image file
# imwriteGray  - write a text image file
# getIMGhist   - generate a histogram with a default bin size of 256
# plotIMGhist  - plot the histogram using Gadfly


# Function to read a text image.
function imreadGray(fname)
   
    println(fname)
    imgIn = readdlm(fname,Int16::Type)
    
    return imgIn
end

# Function to write a text image.
function imwriteGray(fname,img)
   
    println(fname)
    writedlm(fname,img)
    
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

# Function to display the histogram of an image 
function minmaxIMG(img)

    min = 0
    max = 0
    # the histogram of the data
    dx,dy = size(img)
    
    for i=1:dx, j=1:dy
        if img[i,j] < min 
            min = img[i,j]
        end
        if img[i,j] > max
            max = img[i,j]
        end
    end
    println(min,max)
end

function plotIMGhist(hst)

    p = plot(x=1:256, y=hst, Geom.line, Guide.XLabel("Intensity Values"), Guide.YLabel("Frequency"),)
    display(p)
    #draw(PNG("myplot.png", 12cm, 6cm), p)
    
end

end