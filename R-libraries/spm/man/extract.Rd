\name{extract}
\alias{extract}
\title{Extract elements from an SPM output file}
\description{
This will read and extract reports from a SPM output file.
}
\usage{
extract(file, path = "", ignore.unknown=FALSE)
}
\arguments{
  \item{file}{the name of the SPM output file to read}
  \item{path}{Optionally, the operating system path to the directory of tghe output file.}
  \item{ignore.unknown}{Ignore unknown reports when reading. (This can be useful to read files that contain undocumented reports or other output)}
 }
\value{
Outputs a list object with elements for each report type: ageing_error, age_size, age_weight, covariance, derived_quantity, derived_layer, estimate_summary, estimate_value, initialisation, layer, layer_derived_view, MCMC, objective_function, observation, partition, partition_biomass, process, random_number_seed, selectivity, simulated_observation, size_weight, spatial_map, preference_function
}
\note{

}
\seealso{
\code{\link{spm-package}}
}
