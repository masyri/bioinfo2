#
# https://cran.r-project.org/web/packages/caret/vignettes/caret.html
#


library(randomForest)
library(tidyverse)
library(caret)
library(mlbench)
source("data.R")
source("training.R")

## Data

genes <- openTable('data/gene_small2.txt')
drugs <- openTable('data/drug_small.txt')

genes <- cbind(genes, drugs)

split <- Splitter(genes,0.8)

training_set <- getTrain(genes,split)

test_set <- getTest(genes,split)

# ii
## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, summaryFunction = twoClassSummary)

## mtry ###
tunegrid <- expand.grid(.mtry=c(1:3))

training_set$Methotrexate = factor(training_set$Methotrexate)
levels(training_set$Methotrexate) <- make.names(levels(factor(training_set$Methotrexate)))

## Train ##
fit <- train(Methotrexate~., data = training_set, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)


# iv
## predict ##
predict(fit, newdata = test_set, type = 'prob')

## confusionmatrix ##
confusionMatrix(data= test_set$pred, reference = test_set$obs)


#v
## Feature Importance-Plot ##
plot(varImp(fit))




## Train

#rdaClasses <- predict(rdaFit, newdata = test_set)
#confusionMatrix(rdaClasses, test_set$RBM5)


#ttt <- train(RBM5~., data=training_set, 
#             metric = "ROC",
#             trControl=PreSets(),
#             method="C5.0", 
#             na.action = na.pass,
#             preProc=c("center", "scale"), 
#             )



