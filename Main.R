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

genes <- openTable('data/gene_expression.txt')
drugs <- openTable('data/drug_response.txt')

genes <- cbind(genes, drugs)

split <- Splitter(genes,0.8)

training_set <- getTrain(genes,split)

test_set <- getTest(genes,split)

# ii
## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, summaryFunction = twoClassSummary)

## mtry ###
tunegrid <- expand.grid(.mtry=c(1:70))

training_set$Methotrexate = factor(training_set$Methotrexate)
levels(training_set$Methotrexate) <- make.names(levels(factor(training_set$Methotrexate)))

## Train ##
fit <- train(Methotrexate~., data = training_set, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)
fit

# iv
## predict ##
pred <- predict(fit, newdata = test_set, type = 'prob')
pred

## confusionmatrix ##
confusionMatrix(as.factor(pred),test_set$Methotrexate)


#v
## Feature Importance-Plot ##
plot(varImp(fit))
