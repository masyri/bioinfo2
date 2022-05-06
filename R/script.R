# 
# This script creates a Ramachandran-Plot from a given CSV-File and save this
# Plot in a PNG-File
#
#
# -- Command line --
#
# $ Rscript script.R [plot_name] [inputfile]
#
# $ Rscript script.R coffee plotList.csv
#
#

# -- read arguments --

# include in R
#setwd(dirname(getwd()))
#source("extend.R")

# Line read
cat("a string please: ");
a <- readLines("stdin",n=1);
cat("You entered")
str(a);
cat( "\n" )


