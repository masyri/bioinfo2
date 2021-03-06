#
#  ``` $ Rscript Regressor.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#
library(randomForest)
library(caret)
library(tidyselect)
library(mltools)
library(MLmetrics)
source("data.R")

## load and check arguments
args = commandArgs(trailingOnly=TRUE)
timestamp <- startTimer()
input <- loadArgs(args, "Regressor")

## open files from arguments
cat("\n => load argument files ... \n")
drug_data <- openTable(input@drug_data)            
genes <- openTable(input@gene_expressions)
training_set <- read.table(input@training_set, header = FALSE)
test_set <- read.table(input@test_set, header = FALSE)

drugs <- drug_data[row.names(genes),, drop = FALSE]


## get current Drug Name
cat("\n => prepare data ... \n")
drug_name = names(drugs)[1]

## feature selection
## selektieren von bestimmten Krebsgenen
cancer.genes <- openTable("data/cancer_gene_list.txt")
cancer.genes <- as.character(cancer.genes[,1])
genes <- genes[, colnames(genes) %in% cancer.genes]

## combind data
gesamt <- cbind(drugs, genes)

#erase NA values
gesamt = gesamt[complete.cases(gesamt), ]

## Bind and Split
training <- as.character(training_set[,1])
test <- as.character(test_set[,1])

training_matrix = gesamt[training,]
test_matrix = gesamt[test,]

training_matrix = training_matrix[complete.cases(training_matrix), ]
test_matrix = test_matrix[complete.cases(test_matrix), ]

## 5-Fold Crossvalidation ##
trC <- trainControl(method = 'cv', number = 5, verboseIter = T, savePredictions = "final")

## mtry ### hohe mytry ist gut 
tunegrid <- expand.grid(.mtry=c(2:15))

# split train_matrix again
train_response = training_matrix[, drug_name]
train_exe = training_matrix[, !(colnames(training_matrix)%in% drug_name)]

#seed
set.seed(45)


## Train ##
cat("\n => training ... \n")
fit <- train(x = train_exe, y= train_response, method = 'rf', metric = "RMSE", tuneGrid=tunegrid, trControl = trC)
fit
cat("\n => training finished \n")


## predict ##
pred_test2 <- predict(fit, newdata = test_matrix)
pred_test2

## results ##
## mean squared error ##
# CV Error
finalm <- fit$bestTune$mtry
cv_results <- fit$results
pred <- fit$pred
pred
cv_mse <- mse(preds = pred$pred, actuals = pred$obs)

#Test Error
test_mse <- mse(preds = pred_test2, actuals = test_matrix[,drug_name])

## -- OUTPUT -- ##

folderpath <- createFolderAndPath("output_regressor",drug_name)


## Plots ##

## Plot 3
pred_train2 <- predict(fit, newdata = training_matrix)
plot(pred_train2, training_matrix[,drug_name], xlab = "predicted", ylab = "actuals")
dev.copy(jpeg,filename = concat(folderpath,"plot3.jpg") );
dev.off ();

## Plot 4
plot(pred_test2, test_matrix[,drug_name], xlab = "predicted", ylab = "actuals")
dev.copy(jpeg,filename = concat(folderpath,"plot4.jpg") );
dev.off ();


## Plot 5
b_plot <-  c(cv_mse, test_mse)
barplot(b_plot,horiz = FALSE , ylab = "value", col = c("red","orange"), names.arg =  c("CV Error","Test Error"))
dev.copy(jpeg,filename = concat(folderpath,"plot5.jpg") );
dev.off ();


## Error File
tab <- data.frame(MSE= c(cv_mse, test_mse))
rownames(tab) <- c("CV Error","Test Error")
write.table(tab, file = concat(folderpath,"error_file.txt"), dec = ',', sep = '\t', quote = FALSE)

## Training result file
pred_train3 <- predict(fit, newdata = training_matrix, type = 'raw')
train_result <- data.frame(Predicted_Response = pred_train3)
rownames(train_result) <- rownames(training_matrix)
train_result
write.table(train_result, file = concat(folderpath,"training_set_results.txt"), dec = ',', sep = '\t', quote = FALSE)

## Test result file
pred_test3 <- predict(fit, newdata = test_matrix, type = 'raw')
test_result <- data.frame(Predicted_Response = pred_test3)
rownames(test_result) <- rownames(test_matrix)
test_result
write.table(test_result, file = concat(folderpath,"test_set_results.txt"), dec = ',', sep = '\t', quote = FALSE) 


## out
cat("\n\n => Output-Files saved in ",folderpath,"\n")

## -- PROGRAM END -- ##

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

