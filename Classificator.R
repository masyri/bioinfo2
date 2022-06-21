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
genes <- openTable(input@gene_expressions)
training_set <- openTable(input@training_set)
test_set <- openTable(input@test_set)

drugs <- drugs[row.names(genes),, drop = FALSE]





## get current Drug Name
drug_name = names(drugs)[1]





## feature selection
## selektieren von bestimmten Krebsgenen 

#text = readtext(input@gene_expressions)
#cancer.genes <- openTable("data/cancer_gene_list.txt")
#cancer <- cancer.genes$TP53
#cancer.genes = as.vector(cancer.genes)

#genes %>% filter(if_any(.cols = all_of(cancer)))
#genes <- subset(genes, select = cancer)




## reduse cell-line 
# bind same cell-lines
##genes$new.col <- c(drugs$Camptothecin, rep(NA, nrow(genes)-length(drugs$Camptothecin)))
#genes <- merge(x= genes,y = drugs, all.x = FALSE , all.y = FALSE)
gesamt <- cbind(drugs, genes)

#erase NA values
gesamt = gesamt[complete.cases(gesamt), ]


## Bind and Split

training_matrix = gesamt[training_set,]
test_matrix = gesamt[test_set,]

split <- Splitter(gesamt,0.8)

training_set <- getTrain(gesamt,split)

test_set <- getTest(gesamt,split)


## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, summaryFunction = twoClassSummary)




## mtry ###
tunegrid <- expand.grid(.mtry=c(1:3))

training_set[,c(drug_name)]

training_set$Camptothecin = factor(training_set$Camptothecin)
levels(training_set$Camptothecin) <- make.names(levels(factor(training_set$Camptothecin)))

# split matix again
train_response = training_matrix[, drug_name]
train_exe = training_matrix[, !(column.name(training_matrix)%in% drug_name)]


## Train ##
fit <- train( method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)
fit





## predict #
pred <- predict(fit, newdata = test_set, type = 'prob')
pred

## confusionmatrix ##
con_m <- confusionMatrix(pred,test_set$Camptothecin)


## output ##

## sensitivity, specificity, Matthew’s correlation coefficient ##

#  Matthew’s correlation coefficient
mcc = mcc(preds = pred, actuals = training_set$Camptothecin)

#  cross validation results
finalm <- fit$bestTune$mtry
cv_results <- fit$results
cv_sens <- cv_results[cv_results$mtry = finalm , "Sens"]
cv_spec <- cv_results[cv_results$mtry = finalm , "Spec"]

#  specificity
test_sens <- as.numeric(con_m$byClass["Sensitivity"])
test_spec <- as.numeric(con_m$byClass["Specificity"])


## files ##
write.table(data, file = input@error_file, dec = ',', sep = '\t')

write.table(data, file = input@training_set, dec = ',', sep = '\t')

write.table(data, file = input@test_set, dec = ',', sep = '\t') 


## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

