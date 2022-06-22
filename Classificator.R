#
#  ``` $ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#
library(randomForest)
library(caret)
library(tidyselect)
library(mccr)
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

split <- Splitter(genes,0.8)
tr <- getTrain(genes,split)
te <- getTest(genes,split)

tra <- rownames(tr)
tes <- rownames(te)

write.table(tra, file = "training_set.txt", dec = ',', sep = '\t',row.names = FALSE, col.names = FALSE) 
write.table(tes, file = "test_set.txt", dec = ',', sep = '\t',row.names = FALSE, col.names = FALSE) 

trai <- openTable("training_set.txt")
drugs <- drugs[row.names(genes),, drop = FALSE]

## get current Drug Name
drug_name = names(drugs)[1]

## feature selection
## selektieren von bestimmten Krebsgenen 

#correlationMatrix <- cor(genes)
#highlyCorrelated <- findCorrelation(correlationMatrix, cutoff=0.5)

#text = readtext(input@gene_expressions)
#cancer.genes <- openTable("data/cancer_gene_list.txt")
#cancer <- cancer.genes$TP53
#cancer.genes = as.vector(cancer.genes)

#genes %>% filter(if_any(.cols = all_of(cancer)))
#genes <- subset(genes, select = cancer)

# fragen ob wir als input nur 1 drug bekommen oder matrix an drugs
drugs <- subset(drugs, select = c(Camptothecin))
genes <- subset(genes, select = c(TSPAN6, TNMD, DPM1))

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
training_matrix[,drug_name] = factor(training_matrix[,drug_name])
levels(training_matrix[,drug_name]) <- make.names(levels(factor(training_matrix[,drug_name])))

test_matrix[,drug_name] = factor(test_matrix[,drug_name])
levels(test_matrix[,drug_name]) <- make.names(levels(factor(test_matrix[,drug_name])))

# split train_matrix again
train_response = training_matrix[, drug_name]
train_exe = training_matrix[, !(colnames(training_matrix)%in% drug_name)]


## Train ##
fit <- train(x = train_exe, y= train_response, method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)
fit



## confusionmatrix ##
pred_test2 <- predict(fit, newdata = test_matrix)
pred_test2
con_m <- confusionMatrix(pred_test2, test_matrix[,drug_name])
con_m

## Plot

varImpPlot(x = fit$finalModel , sort = TRUE)


## output ##

## sensitivity, specificity, Matthew’s correlation coefficient ##
#  cross validation results
finalm <- fit$bestTune$mtry
cv_results <- fit$results
cv_sens <- cv_results[cv_results$mtry == finalm , "Sens"]
cv_spec <- cv_results[cv_results$mtry == finalm , "Spec"]
cv_mcc <- mccr(act = test_matrix[,drug_name],pred = pred_test2)

#  specificity
test_sens <- as.numeric(con_m$byClass["Sensitivity"])
test_spec <- as.numeric(con_m$byClass["Specificity"])

tp <- as.numeric(con_m$table[1])   # true positives
fn <- as.numeric(con_m$table[2])   # false negatives
fp <- as.numeric(con_m$table[3])   # false positives
tn <- as.numeric(con_m$table[4])   # true negatives

test_mcc <- mcc(TP = tp, FP = fp, TN = tn, FN = fn)

## files ##

tab <- data.frame(sensitivity= c(cv_sens, test_sens), specificity= c(cv_spec, test_spec), mcc = c(cv_mcc,test_mcc))
rownames(tab) <- c("CV Error","Test Error")
write.table(tab, file = "error_file.txt", dec = ',', sep = '\t')

pred_train3 <- predict(fit, newdata = training_matrix, type = 'raw')
train_result <- data.frame(Predicted_Response = pred_train3)
rownames(train_result) <- rownames(training_matrix)
write.table(train_result, file = "training_set_results.txt", dec = ',', sep = '\t')

pred_test3 <- predict(fit, newdata = test_matrix, type = 'raw')
test_result <- data.frame(Predicted_Response = pred_test3)
rownames(test_result) <- rownames(test_matrix)
write.table(test_result, file = "test_set_results.txt", dec = ',', sep = '\t') 


## PROGRAM END

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")
