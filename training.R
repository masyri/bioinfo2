

#
# Voreinstellungen
# Wird in die train Funktion eingesetzt bei 'trControl'
#
PreSets <- function() { 
  
  ctrl <- trainControl(method="cv", 
                       summaryFunction=twoClassSummary, 
                       repeats = 3,
                       classProbs=T,
                       savePredictions = T)
  return(ctrl)
}

