#! /bin/sh
export GS_OPTIONS="-sPAPERSIZE=a4"
latex master 
dvips -o master.ps master
ps2pdf master.ps
