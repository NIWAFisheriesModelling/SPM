\name{casal-package}
\alias{casal-package}
\alias{casal}
\docType{package}
\title{
CASAL extract package
}
\description{
A set of R functions are available for reading/processing
CASAL input and output files. For further information about
CASAL, see the webpage http://www.niwa.co.nz/ncfa/tools/casal/
}
\details{
\tabular{ll}{
Package: \tab casal\cr
Version: \tab 2.21\cr
Date: \tab 2008-02-15\cr
License: \tab See the CASAL manual, or use 'casal -l' at the command line to
view the CASAL license.\cr
Packaged: \tab Fri Feb 29 13:08:43 2008; dunn\cr
Built: \tab R 2.6.1; ; 2008-02-29 13:09:10; windows\cr
}

Index:
\preformatted{
casal-package           CASAL extract package
extract.MCYCAY          Extracts MCY/CAY output from a CASAL yields run
                        (casal -Y) when doing stochastic yields
extract.MSY             Extracts MSY output from a CASAL yields run
                        (casal -Y) when doing determinsitic yields
extract.correlation.matrix
                        Extracts thje correlation matrix information
                        from a CASAL standard output file
extract.covariance.matrix
                        Extracts thje covariance matrix information
                        from a CASAL standard output file
extract.csl.command     Extracts the commands and sub-commands from a
                        CASAL 'csl' input parameter file
extract.csl.file        Extracts the commands and sub-commands from a
                        CASAL 'csl' input parameter file
extract.fits            Extracts the observation and associated fit &
                        residual information from a CASAL standard
                        output file
extract.free.parameters
                        Extracts free parameters information from a
                        CASAL standard output file
extract.free.parameters.from.table
                        Extracts the free parameters from a CASAL free
                        parameter flat file
extract.header          Extract the header file information from a
                        CASAL standard output file.
extract.mcmc            Extracts the output samples or quantities from
                        a CASAL MCMC output file into a dataframe
                        object
extract.mpd             Extracts header, objective function, free
                        parameters, fits, and quantities from a CASAL
                        standard output file
extract.mpd.from.file   Extracts the point estimate (MPD) from a from a
                        CASAL standard output file (i.e., the data
                        following the line "In a format suitable for
                        -i")
extract.mulitiple.objective.functions
                        Extracts mulitiple objective functions from a
                        CASAL standard output file
extract.objective.function
                        Extracts the objective function information
                        from a CASAL standard output file
extract.parameter.bounds
                        Extracts parameter bounds for all estimated
                        parameters in an estimation.csl file
extract.parameters.at.bounds
                        Extracts the list free parameters that are at
                        or near a bound from a CASAL standard output
                        file
extract.quantities      Extracts the estimated quantities from a CASAL
                        standard output file
extract.quantities.from.table
                        Extracts the output quantities from a CASAL
                        output file in tabular format.
generate.MVN            extracts the free parameters and the covariance
                        matrix fro generate samples using the
                        multivariate normal distribution
plot.prior              Plots priors using equations and variable names
                        as specified in the CASAL manual
write.csl.file          Writes an R object (created with
                        'extract.csl.file') out to an external file, in
                        a form suitable for use as a 'csl' input
                        parameter file for CASAL (i.e., population.csl,
                        estimation.csl, or output.csl
}
}
\author{
CASAL development team <CASAL@niwa.co.nz>

Maintainer: CASAL development team <CASAL@niwa.co.nz>
}
\keyword{ package }
