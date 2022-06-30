## Drug Sensitivity Prediction Challenge :smile:

1.0 Starting

1.1 Program requirements

1.2 Program call

2.0 Output :smiley:

2.1 Classificator output

2.2 Regressor output

3.0 Default program call

# 1.0 Starting

## 1.1 Program requirements

> Before starting the program, the following **R-packages**:
>
> should already be installed:

- randomForest
- caret
- tidyselect
- mltools
- ROSE

## 1.2 Program call

> This project contains two programs, one **classificator** and one **regressor**
>
> Start this programs with Rscript and the following arguments :

-   `$ ./Rscript Classificator.R <gene expression> <drug> <training set 80%> <test set 20%>`
-   `$ ./Rscript Regressor.R <gene expression> <drug> <training set 80%> <test set 20%>`

|     | Argument             | Value                             |
|-----|----------------------|-----------------------------------|
| 1   | `<gene expression>`  | 'Your genes'                      |
| 2   | `<drug>`             | "Funny drugs :pill::see_no_evil:" |
| 3   | `<training set 80%>` | "Part of Cell-Lines for train"    |
| 4   | `<test set 20%>`     | "Part of Cell-Lines for test"     |

# 2.0 Output

> ### A complete documentation about the results can be found in the \``/documentation`\` folder.

### 

``` mermaid
flowchart LR
A[Input Data] -- split 80% --> B((Training Set))
A[Input Data] -- split 20% --> C((Test Set))
B -- 5 fold CV --> D{Model}
D -- obtain test error --> C
```

## 2.1 Classificator output

> Files will be saved in folder `output\drugname`

- Plots
- Test-Result-File
- Error-Result-File
- Training-Result-File

## 2.2 Regressor output

> coming soon :eyes:

# 

# 3.0 Default call

> For Testing, call this program without arguments: `$ ./Rscript Classificator.R` or `$ ./Rscript Regressor.R` The files will search in the folder \data

## 

| arg | type                 | default PATH                   |
|:---:|----------------------|--------------------------------|
|  1  | `<gene expression>`  | "/data/expression_data.txt"    |
|  2  | `<drug>`             | "/data/binary_data.txt"        |
|  3  | `<training set 80%>` | "/data/training_set.txt"       |
|  4  | `<test set 20%>`     | "/data/test_set.txt"           |

# 
