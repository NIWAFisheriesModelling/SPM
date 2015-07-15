cd CASAL-complex-1
spm -e -d > SPM-estimate.log
casal -e -q > CASAL-estimate.log
cd..
cd CASAL-dirichlet
spm -e -d > SPM-estimate.log
casal -e -q > CASAL-estimate.log
cd..
cd CASAL-complex-2
spm -r -d > SPM-run.log
casal -r -q > CASAL-run.log
spm -e -d > SPM-estimate.log
casal -e -q > CASAL-estimate.log
cd ..
cd CASAL-complex-3
spm -e -d > SPM-estimate.log
casal -e -q > CASAL-estimate.log
cd ..
cd SPM-movement-1
spm -r -d > run.log
cd ..
cd SPM-movement-2
spm -r -d > run.log
cd ..
cd SPM-movement-3
spm -r -d > run.log
cd ..
cd SPM-movement-4
spm -r -d > run.log
cd ..
cd SPM-movement-5
spm -r -d > run.log
cd ..
cd SPM-movement-6
spm -r -d > run.log
cd ..
cd SPM-simple
spm -e -d > Estimate.log
cd ..
cd SPM-simple-profile
spm -p -d > profile.log
cd ..
cd SPM-two-sex
spm -e -d > estimate.log
cd ..
exit
