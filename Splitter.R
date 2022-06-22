## Split Cell-line-File in Test and Train-Set

source("data.R")

## Arguments

input <- "data/expression_data.txt"
  
percent_training_set <- 0.2

## Splitter

table <- openTable(input)

splitter <- Splitter(table, percent_training_set) 

train  <- rownames(getTrain(table, splitter))

test  <- rownames(getTest(table, splitter))

write.csv(train,file="training_set.txt",row.names= FALSE, col.names = FALSE )

write.csv(test,file="test_set.txt",row.names= FALSE, col.names = FALSE )