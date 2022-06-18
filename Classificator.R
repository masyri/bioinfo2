#
#  ``` $ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#
library(randomForest)
library(caret)
library(mltools)
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

genes2 <- cbind(genes, drugs)

split <- Splitter(genes,0.8)

training_set <- getTrain(genes,split)

test_set <- getTest(genes,split)

## feature selection
cancer.genes <- openTable('data/cancer_gene_list.txt')

as.vector(cancer.genes)
genes <- subset(genes, select = c(cancer.genes))

## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, summaryFunction = twoClassSummary)

## mtry ###
tunegrid <- expand.grid(.mtry=c(1:70))

training_set$CASP10 = factor(training_set$CASP10)
levels(training_set$CASP10) <- make.names(levels(factor(training_set$CASP10)))

## Train ##
fit <- train(CASP10~., data = training_set, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)
fit


## predict ##
pred <- predict(fit, newdata = test_set, type = 'prob')
pred

## confusionmatrix ##
confusionMatrix(pred,test_set$CASP10)


## output ##

## sensitivity, specificity, Matthew’s correlation coefficient ##

mcc = mcc(preds = pred, actuals = training_set$CASP10)

## files ##



## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

