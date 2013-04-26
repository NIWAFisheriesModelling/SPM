spm -p -q -g 0 > profile.log
rm simulations/*
spm -s 10 -g 0 > simulation.log
spm -m -q -g 0 > MCMC.log
spm -e -q -g 0 > estimate.log
