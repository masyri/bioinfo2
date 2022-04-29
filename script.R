# 
#
#

inputfile = "X:\\BioInfo_2\\BI_Programmierung\\03_Ramachandran\\plotList.csv"

outputfile = "X:\\BioInfo_2\\BI_Programmierung\\03_Ramachandran\\yay.png"

# -- program start and read in --
library(ggplot2)
# install.packages("ggplot2")
coffee <- read.csv(inputfile, header = TRUE, sep=";")
str(coffee)

# plot the data

plot <- ggplot(coffee)
plot + aes(y = phi, x = psi) + geom_point()
plot + xlim(-180.0,180.0) + ylim(-180.0,180.0)
plot + geom_density_2d_filled(aes(y = phi, x = psi))
 
# , aes(x=phi, y=psi),color="steelblue")
# plot + geom_point(aes(x = phi, y = psi, size = v1), fill="green", shape=21)

ggsave(outputfile) 

