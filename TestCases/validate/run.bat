cd CASAL-complex-1
start spm -e -d > SPM-estimate.log
start casal -e -q > CASAL-estimate.log
cd ..
cd CASAL-complex-2
start spm -e -d > SPM-estimate.log
start casal -e -q > CASAL-estimate.log
cd ..
cd CASAL-complex-3
start spm -e -d > SPM-estimate.log
start casal -e -q > CASAL-estimate.log
cd ..
cd SPM-movement-1
start spm -r -d > run.log
cd ..
cd SPM-movement-2
start spm -r -d > run.log
cd ..
cd SPM-movement-3
start spm -r -d > run.log
cd ..
cd SPM-movement-4
start spm -r -d > run.log
cd ..
cd SPM-movement-5
start spm -r -d > run.log
cd ..
cd SPM-movement-6
start spm -r -d > run.log
cd ..
cd SPM-simple
start spm -e -d > Estimate.log
cd ..
cd SPM-simple-profile
start spm -p -d > profile.log
cd ..
cd SPM-two-sex
start spm -e -d > estimate.log
cd ..
exit
