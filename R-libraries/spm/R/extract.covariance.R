extract.covariance <- function (lines)
{
    if (missing(lines))
        stop("ERROR: Missing argument lines")
    index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
    index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
    index.hessian <- (1:length(lines))[substring(lines, 1, 7) == "Hessian"][1]
    index.cov <- (1:length(lines))[substring(lines, 1, 10) == "Covariance"][1]
    index.cor <- (1:length(lines))[substring(lines, 1, 11) == "Correlation"][1]

    if (index.start >= index.end) stop("Error")
    res <- list()
    res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) -1)
    res$report.type <- substring(lines[index.start + 1], 14)
    variables <- spm.string.to.vector.of.words(lines[index.start + 2], sep = " ")[-1]
    data <- spm.string.to.vector.of.words(lines[(index.hessian + 1):(index.cov -1)], sep = " ")
    if (length(data)==length(variables)^2) {
      data<-as.numeric(data)
      data <- matrix(data, ncol = length(variables), byrow = TRUE)
      data <- as.data.frame(data)
      colnames(data) <- variables
      rownames(data) <- variables
    } else
      data <- NA
    res$hessian <- data
    data <- spm.string.to.vector.of.words(lines[(index.cov + 1):(index.cor -1)], sep = " ")
        if (length(data)==length(variables)^2) {
          data<-as.numeric(data)
          data <- matrix(data, ncol = length(variables), byrow = TRUE)
          data <- as.data.frame(data)
          colnames(data) <- variables
          rownames(data) <- variables
        } else
        data <- NA
    res$covariance <- data
    data <- spm.string.to.vector.of.words(lines[(index.cor + 1):(index.end -1)], sep = " ")
        if (length(data)==length(variables)^2) {
          data<-as.numeric(data)
          data <- matrix(data, ncol = length(variables), byrow = TRUE)
          data <- as.data.frame(data)
          colnames(data) <- variables
          rownames(data) <- variables
        } else
        data <- NA
    res$correlation <- data
    return(res)
}
