#
#  ``` $ ./Rscript Regressor.R <gene expression> <drug> <training set 80%> <test set 20%>``` 
#
library(randomForest)
library(caret)
library(tidyselect)
library(mltools)
library(ROSE)
library(MLmetrics)
source("data.R")



## load and check arguments
args = commandArgs(trailingOnly=TRUE)
timestamp <- startTimer()
input <- loadArgs(args)

## open files from arguments
cat("\n => load argument files ... \n")
drug_data <- openTable(input@drug_data)            
genes <- openTable(input@gene_expressions)
training_set <- read.table(input@training_set, header = FALSE)
test_set <- read.table(input@test_set, header = FALSE)

drugs <- drug_data[row.names(genes),, drop = FALSE]

cat("\n => prepare data ...","\n")
## get current Drug Name
cat("\n => prepare data ... \n")
drug_name = names(drugs)[1]

### subset von Medikaments bilden
drugs <- subset(drugs, select = c(Camptothecin))

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
trC <- trainControl(method = 'cv', number = 5, classProbs = TRUE, sampling = "rose", verboseIter = T)

## mtry ###
tunegrid <- expand.grid(.mtry=c(2:10))

# values from 0, 1 to factor X0 X1
#training_matrix[,drug_name] = factor(training_matrix[,drug_name])
#levels(training_matrix[,drug_name]) <- make.names(levels(factor(training_matrix[,drug_name])))

#test_matrix[,drug_name] = factor(test_matrix[,drug_name])
#levels(test_matrix[,drug_name]) <- make.names(levels(factor(test_matrix[,drug_name])))

# split train_matrix again
train_response = training_matrix[, drug_name]
train_exe = training_matrix[, !(colnames(training_matrix)%in% drug_name)]

## Train ##
cat("\n => training ... \n")
fit <- train(x = train_exe, y= train_response, method = 'rf', importance = TRUE, tuneGrid=tunegrid, trControl = trC)
fit
cat("\n => training finished \n")


## confusionmatrix ##
pred_test2 <- predict(fit, newdata = test_matrix)
pred_test2
con_m <- confusionMatrix(pred_test2, test_matrix[,drug_name])
con_m

## results ##
## mean squared error ##
# CV Error
cv_mse <- MSE(y_pred = data, y_true = data2)
cv_mse2 <- mse(preds = data, actuals = data2)

#Test Error
test_mse <- MSE(y_pred = data, y_true = data2)
test_mse2 <- mse(preds = data, actuals = data2)


## -- OUTPUT -- ##

dir.create("output",showWarnings = FALSE)
folderpath <- paste("output/",drug_name,"/", sep = "")
dir.create(folderpath,showWarnings = FALSE)


## Plots ##

## Plot 1
varImpPlot(x = fit$finalModel , sort = TRUE, main = drug_name)
dev.copy(jpeg,filename=paste(folderpath,"plot1.jpg"));
dev.off ();
cat("\nplot 1\n")

## Plot 2
plot(fit, main = drug_name)
dev.copy(jpeg,filename=paste(folderpath,"plot2.jpg"));
dev.off ();
cat("\nplot 2\n")

## Plot 3
plot(fit$finalModel, main = "Barplot")
dev.copy(jpeg,filename=paste(folderpath,"plot3.jpg"));
dev.off ();
cat("\nplot 3\n")

## Plot 4
plot(pred_test2, test_matrix[,drug_name], xlab = "predicted", ylab = "actuals")
dev.copy(jpeg,filename=paste(folderpath,"plot4.jpg"));
dev.off ();
cat("\nplot 4\n")

## Plot 5
b_plot <- c(cv_sens,cv_spec,cv_mcc)
barplot(b_plot,horiz = FALSE , ylim = c(-1,1), ylab = "value", col = c("red","orange","yellow"), names.arg = c("Sensitivity", "Specificity", "Matthew’s correlation coefficient"))
dev.copy(jpeg,filename=paste(folderpath,"plot5.jpg"));
dev.off ();
cat("\nplot 5\n")

## Error File
tab <- data.frame(MSE= c(cv_mse, test_mse))
rownames(tab) <- c("CV Error","Test Error")
write.table(tab, file = paste(folderpath,"error_file.txt"), dec = ',', sep = '\t')

## Training result file
pred_train3 <- predict(fit, newdata = training_matrix, type = 'raw')
train_result <- data.frame(Predicted_Response = pred_train3)
rownames(train_result) <- rownames(training_matrix)
write.table(train_result, file = paste(folderpath,"training_set_results.txt"), dec = ',', sep = '\t')

## Test result file
pred_test3 <- predict(fit, newdata = test_matrix, type = 'raw')
test_result <- data.frame(Predicted_Response = pred_test3)
rownames(test_result) <- rownames(test_matrix)
write.table(test_result, file = paste(folderpath,"test_set_results.txt"), dec = ',', sep = '\t') 

## out
cat("\n\n => Output-Files saved in ",folderpath,"\n")

## -- PROGRAM END -- ##

cat("\n\n => Program finished in ",endTimer(timestamp),"seconds\n")

