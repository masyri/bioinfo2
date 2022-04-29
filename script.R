# 
#
# Command line:
#
# $ Rscript test.R [plot_name] [inputfile]
#
# $ Rscript test.R coffee plotList.csv
#
#

# -- read arguments --

args = commandArgs(trailingOnly = TRUE)

# arg-check
if (length(args)!=2) {
  stop("\n | You need exactly two arguments: \n | $ Rscript test.R [plot_name] [inputfile]\n | example: \n | $ Rscript test.R coffee plotList.csv\n\n", call.=FALSE)
}

name <- args[1]
filename <- args[2]
output <- paste(name,".png", sep = "", collapse = NULL)

# read file
coffee <- read.csv(filename, header = TRUE, sep=";")
tuplecount <- length(count.fields(filename)) - 1

# -- Create Plot --

#install.packages("ggplot2")
library(ggplot2)

# plot the data

plot <- ggplot(coffee)
plot + aes(y = phi, x = psi) + geom_point()
plot + xlim(-180.0,180.0) + ylim(-180.0,180.0)
plot + geom_density_2d_filled(aes(y = phi, x = psi))
 
# , aes(x=phi, y=psi),color="steelblue")
# plot + geom_point(aes(x = phi, y = psi, size = v1), fill="green", shape=21)

ggsave(output) 

# -- Output inputs --

getinputs <- function(){
str <- cat("\n R A M A C H A N D R A N - P L O T \n Your inputs   : ", length(args),"args\n plot name     : ",name,"\n input file    : ",filename,"\n count tuples  : ",tuplecount,"\n\n -> output saved : '",output,"'\n")
}

getinputs()
