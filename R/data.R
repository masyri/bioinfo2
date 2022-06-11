
#
# Auslesen der Tabelle
#
openTable <- function(file) {
  table <- read.table(file,header = TRUE,sep = '\t',fill = TRUE)
  cat(" [Open Table]")
  cat("\n File = ",file)
  cat("\n Size = rows:",nrow(table),"cols:",ncol(table),"\n")
  
  return(table)
}


#
# Gibt eine Partition der Größe percent zurück
#
Splitter <- function(table, percent) { 
  set.seed(123)
  partitionsize <- floor(percent * nrow(table))
  splitted <- sample(seq_len(nrow(table)), size = partitionsize)
  cat("[Splitter] rows: ",nrow(table)," -> ",nrow(table[splitted,])," ( percent:",percent * 100,")\n")
  return(splitted)
}



#
# Gibt Trainingsdatensatz zurück
#
getTrain <- function(table, splitter) { 
  training_set <- table[splitter,]
  cat("[getTraining] rows: ",nrow(table)," -> ",nrow(training_set),"\n")
  return(training_set)
}



#
# Gibt Testdatensatz zurück
#
getTest <- function(table, splitter) { 
  test_set <- table[-splitter,]
  cat("[getTest] rows: ",nrow(table)," -> ",nrow(test_set),"\n")
  return(test_set)
}


