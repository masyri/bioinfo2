### CIP Pool ###

Sys.setenv(TENSORFLOW_PYTHON="/opt/miniconda3/envs/tf2/bin/python")

### Parameter ###

args = commandArgs(trailingOnly = TRUE)

filepath  <- args[1]

hidden <- 2

### Open Table ... ###

table_raw <- read.table(filepath, header = TRUE, sep= "\t")

count_rows <- nrow(table_raw)

cat(" imput:",count_rows,"rows ")

### Delete duplicate ... ###

table <- table_raw[!duplicated(table_raw, MARGIN = 1),]

count_rows_after <- nrow(table)
cat("\n     ->",count_rows_after,"rows (",count_rows-count_rows_after,"duplicates deleted )")

### start Keras ###

library(tensorflow)
library(keras)
library(tfdatasets)
library(rsample)

# first we split between training and testing sets
split <- initial_split(table, prop = 4/5)
train <- training(split)
test <- testing(split)
# the we split the training set into validation and training
split <- initial_split(train, prop = 4/5)
train <- training(split)
val <- testing(split)
cat("\n train:",nrow(train),"test:",nrow(test),"val:",nrow(val),"\n\n")

# create an input pipeline using tf-datasets
df_to_dataset <- function(table, shuffle = TRUE, batch_size = 32) {
  ds <- table %>%
    tensor_slices_dataset()

  if (shuffle)
    ds <- ds %>% dataset_shuffle(buffer_size = nrow(table))

  ds %>%
    dataset_batch(batch_size = batch_size)
}
batch_size <- 5

train_ds <- df_to_dataset(train, batch_size = batch_size)
val_ds <- df_to_dataset(val, shuffle = FALSE, batch_size = batch_size)
test_ds <- df_to_dataset(test, shuffle = FALSE, batch_size = batch_size)

train_ds %>%
  reticulate::as_iterator() %>%
  reticulate::iter_next() %>%
  str()

  spec <- feature_spec(train_ds, target ~ .)
  spec <- spec %>%
    step_numeric_column(
      all_numeric(), -SecondaryStructure,
      normalizer_fn = scaler_standard()
    ) %>%
    step_categorical_column_with_vocabulary_list(AS_x)