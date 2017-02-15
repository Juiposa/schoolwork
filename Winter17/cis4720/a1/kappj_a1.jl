include("include.jl")

println("Opening files.");

img1 = imageIO.imreadGray("images\\noisy1.txt")
img2 = imageIO.imreadGray("images\\noisy2.txt")
img3 = imageIO.imreadGray("images\\noise_1.txt")
img4 = imageIO.imreadGray("images\\noise_2.txt")
img5 = imageIO.imreadGray("images\\photogravure.txt")
img6 = imageIO.imreadGray("images\\eg3_gaussianNoise.txt")

println("Editing images\n")

println("Truncated median.")
imgT1 = imageENH.enh_truncMedian(img1,5)
imgT2 = imageENH.enh_truncMedian(img2,5)
imgT3 = imageENH.enh_truncMedian(img3,5)
imgT4 = imageENH.enh_truncMedian(img4,5)
imgT5 = imageENH.enh_truncMedian(img5,5)
imgT6 = imageENH.enh_truncMedian(img6,5)

println("Mean.")
imgM1 = imageENH.filter_MEAN(img1,5)
imgM2 = imageENH.filter_MEAN(img2,5)
imgM3 = imageENH.filter_MEAN(img3,5)
imgM4 = imageENH.filter_MEAN(img4,5)
imgM5 = imageENH.filter_MEAN(img5,5)
imgM6 = imageENH.filter_MEAN(img6,5)

println("Nagao-Matsuyama.")
imgNM1 = imageENH.NagaoMatsuyama(img1,5)
imgNM2 = imageENH.NagaoMatsuyama(img2,5)
imgNM3 = imageENH.NagaoMatsuyama(img3,5)
imgNM4 = imageENH.NagaoMatsuyama(img4,5)
imgNM5 = imageENH.NagaoMatsuyama(img5,5)
imgNM6 = imageENH.NagaoMatsuyama(img6,5)



println("Outputting images")
imageIO.imwriteGray("results\\noisy1T.out", imgT1)
imageIO.imwriteGray("results\\noisy2T.out", imgT2)
imageIO.imwriteGray("results\\noise_1T.out", imgT3)
imageIO.imwriteGray("results\\noise_2T.out", imgT4)
imageIO.imwriteGray("results\\photogravureT.out", imgT5)
imageIO.imwriteGray("results\\eg3_gaussianNoiseT.out", imgT6)

imageIO.imwriteGray("results\\noisy1M.out", imgM1)
imageIO.imwriteGray("results\\noisy2M.out", imgM2)
imageIO.imwriteGray("results\\noise_1M.out", imgM3)
imageIO.imwriteGray("results\\noise_2M.out", imgM4)
imageIO.imwriteGray("results\\photogravureM.out", imgM5)
imageIO.imwriteGray("results\\eg3_gaussianNoiseM.out", imgM6)

imageIO.imwriteGray("results\\noisy1NM.out", imgNM1)
imageIO.imwriteGray("results\\noisy2NM.out", imgNM2)
imageIO.imwriteGray("results\\noise_1NM.out", imgNM3)
imageIO.imwriteGray("results\\noise_2NM.out", imgNM4)
imageIO.imwriteGray("results\\photogravureNM.out", imgNM5)
imageIO.imwriteGray("results\\eg3_gaussianNoiseNM.out", imgNM6)


println("Generating metrics.")

outfile = open("metrics.txt", "w")

write(outfile, "Base Images\n")
write(outfile, "noisy1:               $(imageMETRICS.RankNEI(img1)) \n")
write(outfile, "noisy2:               $(imageMETRICS.RankNEI(img2)) \n")
write(outfile, "noise_1:              $(imageMETRICS.RankNEI(img3)) \n")
write(outfile, "noise_2:              $(imageMETRICS.RankNEI(img4)) \n")
write(outfile, "photogravure:         $(imageMETRICS.RankNEI(img5)) \n")
write(outfile, "eg3_gaussianNoise:    $(imageMETRICS.RankNEI(img6)) \n\n")

write(outfile, "Truncated median.\n")
write(outfile, "noisy1:               $(imageMETRICS.RankNEI(imgT1)) \n")
write(outfile, "noisy2:               $(imageMETRICS.RankNEI(imgT2)) \n")
write(outfile, "noise_1:              $(imageMETRICS.RankNEI(imgT3)) \n")
write(outfile, "noise_2:              $(imageMETRICS.RankNEI(imgT4)) \n")
write(outfile, "photogravure:         $(imageMETRICS.RankNEI(imgT5)) \n")
write(outfile, "eg3_gaussianNoise:    $(imageMETRICS.RankNEI(imgT6)) \n\n")

write(outfile, "Mean.\n")
write(outfile, "noisy1:               $(imageMETRICS.RankNEI(imgM1)) \n")
write(outfile, "noisy2:               $(imageMETRICS.RankNEI(imgM2)) \n")
write(outfile, "noise_1:              $(imageMETRICS.RankNEI(imgM3)) \n")
write(outfile, "noise_2:              $(imageMETRICS.RankNEI(imgM4)) \n")
write(outfile, "photogravure:         $(imageMETRICS.RankNEI(imgM5)) \n")
write(outfile, "eg3_gaussianNoise:    $(imageMETRICS.RankNEI(imgM6)) \n\n")

write(outfile, "Nagao-Matsuyama\n")
write(outfile, "noisy1:               $(imageMETRICS.RankNEI(imgNM1)) \n")
write(outfile, "noisy2:               $(imageMETRICS.RankNEI(imgNM2)) \n")
write(outfile, "noise_1:              $(imageMETRICS.RankNEI(imgNM3)) \n")
write(outfile, "noise_2:              $(imageMETRICS.RankNEI(imgNM4)) \n")
write(outfile, "photogravure:         $(imageMETRICS.RankNEI(imgNM5)) \n")
write(outfile, "eg3_gaussianNoise:    $(imageMETRICS.RankNEI(imgNM6)) \n\n")


close(outfile)
