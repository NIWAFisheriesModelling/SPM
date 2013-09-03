cd CASAL-complex
spm -e > SPM-estimate.log
casal -e -q > CASAL-estimate.log
cd ..
cd SPM-movement-1
spm -r > run.log
cd ..
cd SPM-movement-2
spm -r > run.log
cd ..
cd SPM-movement-3
spm -r > run.log
cd ..
cd SPM-movement-4
spm -r > run.log
cd ..
cd SPM-movement-5
spm -r > run.log
cd ..
cd SPM-movement-6
spm -r > run.log
cd ..
cd SPM-simple
spm -e > Estimate.log
cd ..
cd SPM-simple-profile
spm -p > profile.log
cd ..
cd SPM-two-sex
spm -e > estimate.log
cd ..
