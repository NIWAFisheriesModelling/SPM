# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $


"extract" <-
function(file,path=""){
  if(missing(path)) path<-""
  filename<-spm.make.filename(path=path,file=file)
  line <- scan(filename, what = "", sep = "\n")
  # if a header exists, read it then delete
  res<-list()
  if(substring(line[1],1,3)=="SPM") {
    header<-list()
    header$call<-line[2]
    header$date<-line[3]
    header$version<-line[4]
    header$user.name<-line[5]
    header$machine.name<-line[6]
    res$header<-header
  }
  # which lines are labels of reports?
  index<-(1:length(line))[substring(line,1,1)=="["]
  # get the report label
  report.label<-substring(line[index],2,nchar(line[index])-1)
  # get the report type
  report.type<-substring(line[index+1],13)
  # error check
  if(length(report.label)!=length(report.type)) stop("Error")
  # add the last line of the file to index to assist in tracking reports
  index<-c(index,length(line))
  # create a counter to assist in labelling
  counter<-list("initialisation_phase"=0,"partition"=0,"process"=0,"derived_quantity"=0,"estimate_value"=0,"estimate_summary"=0,"objective_function"=0,"observation"=0,"layer"=0,"selectivity"=0,"random_number_seed"=0,"weight_at_size"=0)

  # iterate through report types and extract values
  for(i in 1:length(report.type)) {
    if(report.type[i]=="initialisation_phase") {
      if(!("initialisation_phase" %in% names(res))) {
        res$"initialisation_phase"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"initialisation_phase"<-counter$"initialisation_phase"+1
      # extract report
      temp<-extract.initialisationphase(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"initialisation_phase"[[counter$"initialisation_phase"]]<-temp
      names(res$"initialisation_phase")[counter$"initialisation_phase"]<-report.label[i]
    }
    if(report.type[i]=="partition") {
      if(!("partition" %in% names(res))) {
        res$"partition"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"partition"<-counter$"partition"+1
      # extract report
      temp<-extract.partition(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"partition"[[counter$"partition"]]<-temp
      names(res$"partition")[counter$"partition"]<-report.label[i]
    }
    if(report.type[i]=="process") {
      if(!("process" %in% names(res))) {
        res$"process"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"process"<-counter$"process"+1
      # extract report
      temp<-extract.process(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"process"[[counter$"process"]]<-temp
      names(res$"process")[counter$"process"]<-report.label[i]
    }
    if(report.type[i]=="derived_quantity") {
      if(!("derived_quantity" %in% names(res))) {
        res$"derived_quantity"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"derived_quantity"<-counter$"derived_quantity"+1
      # extract report
      temp<-extract.derivedquantity(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"derived_quantity"[[counter$"derived_quantity"]]<-temp
      names(res$"derived_quantity")[counter$"derived_quantity"]<-report.label[i]
    }
    if(report.type[i]=="estimate_summary") {
      if(!("estimate_summary" %in% names(res))) {
        res$"estimate_summary"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"estimate_summary"<-counter$"estimate_summary"+1
      # extract report
      temp<-extract.estimatesummary(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"estimate_summary"[[counter$"estimate_summary"]]<-temp
      names(res$"estimate_summary")[counter$"estimate_summary"]<-report.label[i]
    }
    if(report.type[i]=="objective_function") {
      if(!("objective_function" %in% names(res))) {
        res$"objective_function"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"objective_function"<-counter$"objective_function"+1
      # extract report
      temp<-extract.objectivefunction(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"objective_function"[[counter$"objective_function"]]<-temp
      names(res$"objective_function")[counter$"objective_function"]<-report.label[i]
    }
    if(report.type[i]=="observation") {
      if(!("observation" %in% names(res))) {
        res$"observation"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"observation"<-counter$"observation"+1
      # extract report
      temp<-extract.observation(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"observation"[[counter$"observation"]]<-temp
      names(res$"observation")[counter$"observation"]<-report.label[i]
    }
    if(report.type[i]=="layer") {
      if(!("layer" %in% names(res))) {
        res$"layer"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"layer"<-counter$"layer"+1
      # extract report
      temp<-extract.layer(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"layer"[[counter$"layer"]]<-temp
      names(res$"layer")[counter$"layer"]<-report.label[i]
    }
    if(report.type[i]=="selectivity") {
      if(!("selectivity" %in% names(res))) {
        res$"selectivity"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"selectivity"<-counter$"selectivity"+1
      # extract report
      temp<-extract.selectivity(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"selectivity"[[counter$"selectivity"]]<-temp
      names(res$"selectivity")[counter$"selectivity"]<-report.label[i]
    }
    if(report.type[i]=="random_number_seed") {
      if(!("random_number_seed" %in% names(res))) {
        res$"random_number_seed"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"random_number_seed"<-counter$"random_number_seed"+1
      # extract report
      temp<-extract.randomnumberseed(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"random_number_seed"[[counter$"random_number_seed"]]<-temp
      names(res$"random_number_seed")[counter$"random_number_seed"]<-report.label[i]
    }
    if(report.type[i]=="weight_at_size") {
      if(!("weight_at_size" %in% names(res))) {
        res$"weight_at_size"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"weight_at_size"<-counter$"weight_at_size"+1
      # extract report
      temp<-extract.weightatsize(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"weight_at_size"[[counter$"weight_at_size"]]<-temp
      names(res$"weight_at_size")[counter$"weight_at_size"]<-report.label[i]
    }
  }
  return(res)
}

file<-"run.log"
path<-"c:\\X\\no_tag"

a<-extract(file,path)
