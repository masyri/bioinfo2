#
#  ``` $ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#
library(randomForest)
library(caret)
library(tidyselect)
library(mltools)
library(readtext)
source("data.R")

## load and check arguments

timestamp <- startTimer()

input <- loadArgs(args)



## open files from arguments

drugs <- openTable(input@drug)            
training_set <- openTable(input@training_set)    
test_set <- openTable(input@test_set)         
genes <- openTable(input@gene_expressions)

## get current Drug Name
drug_name = names(drugs)[1]

## feature selection
## selektieren von bestimmten Krebsgenen 
text = readtext('data/cancer_gene_list.txt')
cancer.genes <- openTable('data/cancer_gene_list.txt')

cancer.genes = as.vector(cancer.genes)
genestxt <- subset(genes, select = text)

## reduse cell-line 
# bind same cell-lines
gesamt <- merge(x= genes,y = drugs, by = "row.names")
#erase NA values
gesamt = gesamt[complete.cases(gesamt), ]

## Bind and Split

split <- Splitter(gesamt,0.8)

training_set <- getTrain(gesamt,split)

test_set <- getTest(gesamt,split)


## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, summaryFunction = twoClassSummary)

## mtry ###
tunegrid <- expand.grid(.mtry=c(1:3))

training_set$Camptothecin = factor(training_set$Camptothecin)
levels(training_set$Camptothecin) <- make.names(levels(factor(training_set$Camptothecin)))

## Train ##
fit <- train(Camptothecin~., data = training_set, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)
fit


## predict ##
pred <- predict(fit, newdata = test_set, type = 'prob')
pred

## confusionmatrix ##
confusionMatrix(pred,test_set$Camptothecin)


## output ##

## sensitivity, specificity, Matthew’s correlation coefficient ##

mcc = mcc(preds = pred, actuals = training_set$Camptothecin)

## files ##
write.table(data, file = "error_file.txt", dec = ',', sep = '\t')

write.table(data, file = "trainng_file.txt", dec = ',', sep = '\t')

write.table(data, file = "test_file.txt", dec = ',', sep = '\t')

## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

