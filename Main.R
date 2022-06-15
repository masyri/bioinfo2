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

split <- Splitter(genes,0.8)

training_set <- getTrain(genes,split)

test_set <- getTest(genes,split)

drugs <- openTable('data/drug_response.txt')

split_drug <- Splitter(drugs,0.8)

training_set_drug <- getTrain(drugs,split_drug)

test_set_drug <- getTest(drugs,split_drug)

# ii
## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5)

## mtry ###
tunegrid <- expand.grid(.mtry=c(1:70))

## Train ##
fit <- train(training_set_drug~., data = training_set, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)


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



