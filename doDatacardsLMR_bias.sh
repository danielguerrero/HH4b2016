mass=$1
cards=""
function=$2
range=$3
background="_${function}_${range}"
dirName="PreselectedWithRegressionDeepCSV/LMRSelection_chi2/fit_bias/LMR_${mass}${background}"
dcardName="datacard_${mass}${background}.txt"
bgLogName="data_bkg.log"
Type="Split"
datacardtype="f_${function}"
data_file="w_background_${function}_${range}.root"
pdfLogName="pdf.log"
sigLogName="signal"${mass}"_sig.log"	
trgLogName="PDFs/trig.log"

sig_norm=`grep 'norm =' ${dirName}/${sigLogName}| awk '{print $3}'`
jec_norm=`grep 'JEC     lnN' ${dirName}/${sigLogName} | awk '{print $3}'`
jer_norm=`grep 'JER     lnN' ${dirName}/${sigLogName} | awk '{print $3}'`
trigger_norm=`grep 'trig'${mass}' ' ${trgLogName} | awk '{print $2}'`
btag_norm=`grep 'btag    lnN' ${dirName}/${sigLogName} | awk '{print $3}'`
pdf_norm=`grep 'PDF lnN' ${dirName}/${pdfLogName} | awk '{print $3}'`
bkg_norm=`grep ' Background number of '${function}_${range}' = ' ${dirName}/${bgLogName} | awk '{print $6}'`

if [ $4 -eq 1 ];
        then
	case "$mass" in
	260) bias=-0.033;; 270) bias=-0.071;;	300) bias=-0.050;;
	esac
	else 
        case "$mass" in
	300) bias=0.038;; 350) bias=0.005;; 400) bias=0.0001;; 450) bias=-0.003;; 500) bias=-0.002;; 550) bias=-0.003;; 600) bias=0.002;;
        esac
fi

echo "bias" ${bias}
echo sig_norm ${sig_norm}
echo JEC ${jec_norm}
echo JER ${jer_norm}
echo trigger ${trigger_norm}
echo bTag ${btag_norm}
echo PDF ${pdf_norm}
echo bkg_norm ${bkg_norm}

#let's build a datacard!
cat > ${dirName}/${dcardName} <<EOF
imax 1 number of channels
jmax * number of backgrounds
kmax * number of systematic uncertainty sources
----------
shapes signal     HbbHbb w_signal_${mass}.root      HbbHbb:signal_fixed
shapes signal_bkg HbbHbb w_signal_${mass}.root      HbbHbb:signal_bkg
shapes background HbbHbb $data_file      HbbHbb:$datacardtype
shapes data_obs   HbbHbb $data_file      HbbHbb:data_obs$background
----------
## Observation
bin                     HbbHbb
observation             -1
----------
bin                   HbbHbb          HbbHbb	HbbHbb
process               signal      background	signal_bkg
process               0           1		2
rate                  ${sig_norm} ${bkg_norm}	${sig_norm}
lumi_13TeV  lnN   1.026       -		-
bTag      lnN     ${btag_norm}    -	-
JER       lnN     ${jer_norm}   - 	-
JEC       lnN     ${jec_norm}   -	-
trigger   lnN     ${trigger_norm}   -   -
PDF       lnN     ${pdf_norm}   -	-
shapeBkg_signal_bkg_HbbHbb__norm param 0.0 ${bias}
EOF
#bkg_norm rateParam HbbHbb 1 ${bkg_norm} 


#now add the systematics to the card
grep 'par_'${function}'_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}

cards+="${dirName}/${dcardName} "
echo $cards


