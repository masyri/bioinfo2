



#
# Datensatz für die Argumente nach Programmaufruf
#
setClass(Class="Inputs",
         representation(
           gene_expressions="character",
           drug_data="character",
           training_set="character",
           test_set="character",
           error_file="character"
         )
)





#
# Checkt Argumente 
#
loadArgs <- function(args) {
  
  cat("\n[Classificator] args:",length(args),"\n")

  #
  # Hier kommen die Strings der Dateipfade rein, wenn keine Argumente geladen wurden
  # = Zum Ausführen in RStudio
  #
  input <- new("Inputs",
               gene_expressions = 'data/expression_data.txt',
               drug_data        = 'data/IC50_data.txt',
               training_set     = 'data/training_set.txt',
               test_set         = 'data/test_set.txt',
               error_file       = 'output/error_file.txt'
  )
  
  if (length(args) == 0 ) {
    return(input)
  }
  
  if (length(args) == 4 ) {
    input@gene_expressions = args[1]
    input@drug_data        = args[2]
    input@training_set     = args[3]
    input@test_set         = args[4]
    cat(" 1 :",input@gene_expressions,"\n")
    cat(" 2 :",input@drug_data,"\n")
    cat(" 3 :",input@training_set,"\n")
    cat(" 4 :",input@test_set,"\n")
    return(input)
  }
  
  
  stop("\n | You need four arguments: \n | $ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>\n | example: \n | $ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>\n\n", call.=FALSE)
  
  return(input)
  
}


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



#
# erstellt Ordner und Unterordner und gibt den Pfad zurück
#
createFolderAndPath <-function(foldername,subfolder){
  dir.create(foldername,showWarnings = FALSE)
  folderpath <- paste(foldername,"/",subfolder,"/", sep = "")
  dir.create(folderpath,showWarnings = FALSE)
  return(folderpath)
}

#
# Fügt Dateinamen zusammen
#
concat <-function(foldername,filename){
  path <- paste(foldername,filename, sep = "")
  cat( " :: File created ->",path,"\n")
  return(path)
}




