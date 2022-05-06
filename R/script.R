### CIP Pool ###

Sys.setenv(TENSORFLOW_PYTHON="/opt/miniconda3/envs/tf2/bin/python")

### Parameter ###

library(nnet)

filepath <- "X:/Bioinfo_2/BI_Programmierung/04_Prediction/Tables/table.csv"

hidden <- 2

### Open Table ... ###

table_raw <- read.table(filepath, header = TRUE, sep= "\t")

count_rows <- nrow(table_raw)

### Delete duplicate ... ###

table <- table_raw[!duplicated(table_raw, MARGIN = 1),]

count_rows_after <- nrow(table)



