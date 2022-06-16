

# Timer
startTimer <- function() {
  start_time <- Sys.time()
  return(start_time)
}

# Timer
endTimer <- function(stamp) {
  end_time <- Sys.time()
  s <- end_time - stamp
  return(s*60)
}

#
# Auslesen der Tabelle
#
openTable <- function(file) {
  t <- startTimer()
  table <- read.table(file,header = TRUE,sep = '\t',fill = TRUE)
  duration <- endTimer(t)
  cat(" [Open Table]")
  cat(" | File = ",file)
  cat(" | rows:",nrow(table),"cols:",ncol(table),"| in ",duration,"seconds\n")
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


