#
#  ``` $ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#

source("data.R")

## load and check arguments

timestamp <- startTimer()

input <- loadArgs(args)



## open files from arguments

drugs <- openTable(input@drug)            
training_set <- openTable(input@training_set)    
test_set <- openTable(input@test_set)         
genes <- openTable(input@gene_expressions)




## Bind and Split

genes <- cbind(genes, drugs)

split <- Splitter(genes,0.8)

training_set <- getTrain(genes,split)

test_set <- getTest(genes,split)

##







## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

