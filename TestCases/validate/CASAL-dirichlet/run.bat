rem Basic numbers only model, no catch-at observations
casal -r -q > CASAL-run.log
spm -r -q > SPM-run.log
casal -e -q > CASAL-estimate.log
spm -e -q > SPM-estimate.log
