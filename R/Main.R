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



