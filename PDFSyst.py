import ROOT
from optparse import OptionParser


def PDFsyst(mass):
    

  _file0 = ROOT.TFile.Open("/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV_final/MC/Original/GluGluToBulkGravitonToHHTo4B_M-"+str(mass)+"_narrow_13TeV-madgraph.root")
  if(mass>900.) :
	_file0 = ROOT.TFile.Open("/eos/uscms/store/user/lpchbb/HeppyNtuples/V25/BulkGravTohhTohbbhbb_narrow_M-"+str(mass)+"_13TeV-madgraph.root")
  tree = _file0.Get("tree")
  CountWeighted = _file0.Get("CountWeighted")
  CountWeightedLHEWeightPdf = _file0.Get("CountWeightedLHEWeightPdf")

  ratio = []
  tree.Draw("1>>histo(1,0.5,1.5)","(Sum$( Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_btagDeepCSVb>0.6324 )>=4)*%s"%(1))
  integral = _file0.Get("histo").GetBinContent(1)
  count = CountWeighted.GetBinContent( 1 )
  ratio.append(integral / count)

  for x in range(101):
    tree.Draw("1>>histo(1,0.5,1.5)","(Sum$( Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_btagDeepCSVb>0.6324 )>=4)*LHE_weights_pdf_wgt[%s]"%(x))
    integral = _file0.Get("histo").GetBinContent(1)
    count = CountWeightedLHEWeightPdf.GetBinContent( CountWeightedLHEWeightPdf.FindBin(x) )
    ratio.append(integral / count / ratio[0])

  histo = ROOT.TH1F("histo","",25,0.9,1.1)
  for r in ratio[:101]:
    histo.Fill(r)

  histo.Draw()
  gaus = ROOT.TF1("gaus","gaus")
  histo.Fit("gaus")

  mean = gaus.GetParameter(1)
  sigma = gaus.GetParameter(2)
  meanErr = gaus.GetParError(1)
  sigmaErr = gaus.GetParError(2)

  print mean,"+/-",meanErr
  print sigma,"+/-",sigmaErr
  syst=sigma+1.	
  print ("PDF lnN %s"%(syst))


if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option('-m','--mass'   ,action='store',type='int',dest='mass'   ,default=300, help='mass')
    (options,args) = parser.parse_args()
    PDFsyst(options.mass)

