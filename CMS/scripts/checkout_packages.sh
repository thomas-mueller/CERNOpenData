#!/bin/bash
set -e # exit on errors

export SCRAM_ARCH=slc6_amd64_gcc472
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh

cmsrel CMSSW_5_3_32
cd CMSSW_5_3_32/src
eval `scramv1 runtime -sh`

https://github.com/thomas-mueller/CERNOpenData.git

scram b -j 4

