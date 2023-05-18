#!/bin/bash

export etalist=`ls fitPlots | egrep "_eta__"`
export vtxlist=`ls fitPlots | egrep "_vtx__"`
export ptelist=`ls fitPlots | egrep "_pt_abseta__"`

### switch off overwrite protection ###
unalias mv

### ReNaming of ETA fit canvasses
## typical example: fitPlots/data_Z_PFdBIso0p40_from_PF_and_SIP4p0_eta__SIP_bin0__dB_bin0__dzPV_bin0__eta_bin0__pair_probeMultiplicity_bin0__pt_bin0__PF_pass__vpvPlusExpo.png
## we will keep:             data_Z_PFdBIso0p40_from_PF_and_SIP4p0_eta                                eta_bin0
## typical example: fitPlots/mc_JPsi_Mu7_Track7_PF_from_Tracks_eta__dB_bin0__dzPV_bin0__eta_bin4__pair_drM1_bin0__pair_probeMultiplicity_bin0__pt_bin0__
##                           Mu7_Track7_Jpsi_TK_pass__mcTrue_pass__tag_Mu7_Track7_Jpsi_MU_pass__gaussPlusExpo.png
## we will keep:             mc_JPsi_Mu7_Track7_PF_from_Tracks_eta                      eta_bin4
#
for i in $etalist
do
    echo $i
    export firstPart=`echo $i | awk -F "__" '{ print $1 }' | awk -F "_eta" '{print $1}'`
    # export number=`echo $i | awk -F "__" '{ print NF }'`
    export list=`echo $i | awk -F "__" '{for (j=1;j<=NF;j++) print $j}'`
    for j in $list
    do
	if [[ $j == *"eta_bin"* ]]
	then 
	    export secondPart=$j
	fi
    done
    export thirdPart=`echo $i | awk -F "__" '{ print $NF }'`
    # echo "proposed name :: fitPlots/${firstPart}_${secondPart}_${thirdPart}"
    mv fitPlots/$i fitPlots/${firstPart}_${secondPart}_${thirdPart}
done

### ReNaming of VTX fit canvasses
## typical example: fitPlots/data_Z_PFdBIso0p40_from_PF_and_SIP4p0_vtx__SIP_bin0__abseta_bin0__dB_bin0__dzPV_bin0__pair_probeMultiplicity_bin0__pt_bin0__tag_nVertices_bin0__PF_pass__vpvPlusExpo.png
## typical example: fitPlots/data_JPsi_Mu7_Track7_PF_from_Tracks_vtx__abseta_bin0__dB_bin0__dzPV_bin0__pair_probeMultiplicity_bin0__pt_bin0__tag_nVertices_bin0__
##                           Mu7_Track7_Jpsi_TK_pass__tag_Mu7_Track7_Jpsi_MU_pass__gaussPlusExpo.png
#
for i in $vtxlist
do
    echo $i
    export firstPart=`echo $i | awk -F "__" '{ print $1 }' | awk -F "_vtx" '{print $1}'`
    export list=`echo $i | awk -F "__" '{for (j=1;j<=NF;j++) print $j}'`
    for j in $list
    do
	if [[ $j == *"tag_nVertices_bin"* ]]
	then 
	    export secondPart=$j
	fi
    done
    export secondPart=`echo $secondPart | awk -F "bin" '{print $2}'`
    export thirdPart=`echo $i | awk -F "__" '{ print $NF }'`
    # echo "proposed name :: fitPlots/${firstPart}_vtx_bin${secondPart}_${thirdPart}"
    mv fitPlots/$i fitPlots/${firstPart}_vtx_bin${secondPart}_${thirdPart}
done

### ReNaming of PT_ABSETA fit canvasses
## typical example: fitPlots/data_Z_PFdBIso0p40_from_PF_and_SIP4p0_pt_abseta__SIP_bin0__abseta_bin0__dB_bin0__dzPV_bin0__pair_probeMultiplicity_bin0__pt_bin0__PF_pass__vpvPlusExpo.png
## typical example: fitPlots/data_JPsi_Mu7_Track7_PF_from_Tracks_pt_abseta__abseta_bin0__dB_bin0__dzPV_bin0__pair_drM1_bin0__pair_probeMultiplicity_bin0__pt_bin0__
##                           Mu7_Track7_Jpsi_TK_pass__mcTrue_pass__tag_Mu7_Track7_Jpsi_MU_pass__gaussPlusExpo.png
#
for i in $ptelist
do
    echo $i
    export firstPart=`echo $i | awk -F "__" '{ print $1 }' | awk -F "_pt_abseta" '{print $1}'`
    export list=`echo $i | awk -F "__" '{for (j=1;j<=NF;j++) print $j}'`
    for j in $list
    do
	if [[ $j == *"abseta_bin"* ]]
	then 
	    export secondPart=$j
	fi
	if [[ $j == *"tag_pt_bin"* ]]
	then
            continue 
	elif [[ $j == *"pt_bin"* ]]
	then 
	    export thirdPart=$j
        else 
	    continue
	fi
    done
    export fourthPart=`echo $i | awk -F "__" '{ print $NF }'`
    # echo "proposed name :: fitPlots/${firstPart}_${secondPart}_${thirdPart}_${fourthPart}"
    mv fitPlots/$i fitPlots/${firstPart}_${secondPart}_${thirdPart}_${fourthPart}
done


### switch on overwrite protection ###
source /home/piet/.bash_profile
source /home/piet/.bashrc

