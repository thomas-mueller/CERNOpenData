#!/bin/bash
set -e # exit on errors

export SCRAM_ARCH=slc6_amd64_gcc472
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh

cmsrel CMSSW_5_3_32
cd CMSSW_5_3_32/src
eval `scramv1 runtime -sh`

git clone https://github.com/thomas-mueller/CERNOpenData.git

git clone https://github.com/grid-control/grid-control.git -b testing
cd grid-control
git reset --hard 3f93692
cd $CMSSW_BASE/src/

scram b -j 4

