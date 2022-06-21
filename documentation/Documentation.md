### Hier kommt das rein was in die PDF rein soll:



    Documentation
    - description of data processing (including feature selection) + used statistical
    learning method + parameter tuning
    - reporting of results for classification and regression (specify which
    parameters were used to obtain best-performing model)
    - result plots/tables for all 10 drugs indicating the model performance

## Data preprocessing:

#erase NA values

gesamt = gesamt[complete.cases(gesamt), ]

\## Bind and Split

training_matrix = gesamt[training_set,]

test_matrix = gesamt[test_set,]

split \<- Splitter(gesamt,0.8)

training_set \<- getTrain(gesamt,split)

test_set \<- getTest(gesamt,split)

## 5-Fold Crossvalidation with following settings:

### TrainControl Parameter:

-   method = 'cv'

-   number = 5

-   classProbs = TRUE

-   summaryFunction = twoClassSummary)

\## mtry \###

tunegrid \<- expand.grid(.mtry=c(1:3))

training_set[,c(drug_name)]

training_set\$Camptothecin = factor(training_set\$Camptothecin)

levels(training_set\$Camptothecin) \<- make.names(levels(factor(training_set\$Camptothecin)))

\# split matix again

train_response = training_matrix[, drug_name]

train_exe = training_matrix[, !(column.name(training_matrix)%in% drug_name)]

\## Train \##

fit \<- train( method = 'rf', metric = "ROC", tuneGrid=tunegrid, trControl = trC)

fit

\## predict \#

pred \<- predict(fit, newdata = test_set, type = 'prob')

pred

\## confusionmatrix \##

con_m \<- confusionMatrix(pred,test_set\$Camptothecin)

\## output \##

\## sensitivity, specificity, Matthew's correlation coefficient \##

\# Matthew's correlation coefficient

mcc = mcc(preds = pred, actuals = training_set\$Camptothecin)

\# cross validation results

finalm \<- fit\$bestTune\$mtry

cv_results \<- fit\$results

cv_sens \<- cv_results[cv_results\$mtry = finalm , "Sens"]

cv_spec \<- cv_results[cv_results\$mtry = finalm , "Spec"]

\# specificity

test_sens \<- as.numeric(con_m\$byClass["Sensitivity"])

test_spec \<- as.numeric(con_m\$byClass["Specificity"])
