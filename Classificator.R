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

# fragen ob wir als input nur 1 drug bekommen oder matrix an drugs
drugs <- subset(drugs, select = c(Camptothecin))

## combind data
gesamt <- cbind(drugs, genes)

#erase NA values
gesamt = gesamt[complete.cases(gesamt), ]


## Bind and Split

p_split <- 0.2

size_data = ceiling(p_split*nrow(gesamt))

test = sample(rownames(gesamt), size = size_data, replace = TRUE)

training = setdiff(rownames(gesamt),test)

training_matrix = gesamt[training,]
test_matrix = gesamt[test,]


## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, summaryFunction = twoClassSummary)

## mtry ###
tunegrid <- expand.grid(.mtry=c(1:3))

# values from 0, 1 to factor

training_matrix[,c(drug_name)]

training_matrix$Camptothecin = factor(training_matrix$Camptothecin)
levels(training_matrix$Camptothecin) <- make.names(levels(factor(training_matrix$Camptothecin)))

# split matix again
train_response = training_matrix[, drug_name]
train_exe = training_matrix[, !(colnames(training_matrix)%in% drug_name)]


## Train ##
fit <- train(x = train_exe, y= train_response, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)
fit


## predict #
pred_test <- predict(fit, newdata = test_matrix, type = 'prob')
pred_test

pred_train <- predict(fit, newdata = training_matrix, type = 'prob')
pred_train

## confusionmatrix ##
test_matrix$Camptothecin = factor(test_matrix$Camptothecin)
levels(test_matrix$Camptothecin) <- make.names(levels(factor(test_matrix$Camptothecin)))

con_m <- confusionMatrix(table(pred_test, test_matrix[,drug_name]))
test_matrix[,drug_name]
## Plot

varImpPlot(x = fit$finalModel , sort = TRUE)


## output ##

## sensitivity, specificity, Matthew’s correlation coefficient ##

#  Matthew’s correlation coefficient
mcc = mcc(preds = pred_test, actuals = training_set$Camptothecin)

#  cross validation results
finalm <- fit$bestTune$mtry
cv_results <- fit$results
cv_sens <- cv_results[cv_results$mtry == finalm , "Sens"]
cv_spec <- cv_results[cv_results$mtry == finalm , "Spec"]

#  specificity
test_sens <- as.numeric(con_m$byClass["Sensitivity"])
test_spec <- as.numeric(con_m$byClass["Specificity"])


## files ##

tab <- data.frame(sensitivity= c(cv_sens, 1), specificity= c(cv_spec, 1), mcc = c(1,1))
rownames(tab) <- c("CV Error","Test Error")
write.table(tab, file = input@error_file, dec = ',', sep = '\t')

write.table(pred_train, file = input@training_set, dec = ',', sep = '\t')

write.table(pred_test, file = input@test_set, dec = ',', sep = '\t') 


## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

