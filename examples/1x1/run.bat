spm -p -q -g 0 -o profile.dat > profile.log
spm -s 10 -g 0 > simulation.log
spm -m -q -g 0 > MCMC.log
spm -e -q -g 0 -o MPD.dat > estimate.log
