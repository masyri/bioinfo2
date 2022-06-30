#
#  ``` $ ./Rscript Regressor.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#
library(randomForest)
library(caret)
library(tidyselect)
library(mltools)
source("data.R")


## load and check arguments

timestamp <- startTimer()

input <- loadArgs(args)



## open files from arguments

drugs <- openTable(input@drug)            
genes <- openTable(input@gene_expressions)
training_set <- openTable(input@training_set)
test_set <- openTable(input@test_set)


## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")
