#include <iostream>

#include "TH1D.h"
#include "TLorentzVector.h"

#include "vbf_analysis/Selector/interface/ZPlusJetsValidSelector.h"


using namespace std;

ZPlusJetsValidSelector::ZPlusJetsValidSelector(string infilename, string sampleType, string sampleName, string outdir):
    infilename_( infilename ),
    sampleType_( sampleType ),
    sampleName_( sampleName ),
    outdir_( outdir )
{
    infile_ = TFile::Open(Form("%s",(infilename_+".root").c_str()));
    std::size_t find_slash = infilename_.find_last_of("/");
    infilename_ = infilename_.substr(find_slash+1, infilename_.size() - find_slash -1);
    if ( infile_ ) cout << "Successfully open " + infilename_ + " file."<< endl;
    else exit(0);
}

ZPlusJetsValidSelector::~ZPlusJetsValidSelector()
{
    infile_ -> Close();
}

void ZPlusJetsValidSelector::Initialization()
{
    cout << "[INFO]: Initializing  "<<infilename_<<"  ..." << endl;
    if(SystLabel_ != "") SystLabel_ = "_" + SystLabel_;
    inTree_ = (TTree*)infile_->Get(Form("vbfTagDumper/trees/%s_13TeV_VBFDiJet%s" ,sampleName_.c_str(), SystLabel_.c_str() ));
    inTree_ -> SetBranchAddress("dipho_mass"              ,&dipho_mass               );
    inTree_ -> SetBranchAddress("dipho_leadPt"            ,&dipho_leadPt             );
    inTree_ -> SetBranchAddress("dipho_leadEta"           ,&dipho_leadEta            );
    inTree_ -> SetBranchAddress("dipho_leadPhi"           ,&dipho_leadPhi            );
    inTree_ -> SetBranchAddress("dipho_leadEt"            ,&dipho_leadEt             ); 
    inTree_ -> SetBranchAddress("dipho_lead_ptoM"         ,&dipho_lead_ptoM          );
    inTree_ -> SetBranchAddress("dipho_leadIDMVA"         ,&dipho_leadIDMVA          ); 
    inTree_ -> SetBranchAddress("dipho_subleadPt"         ,&dipho_subleadPt          );
    inTree_ -> SetBranchAddress("dipho_subleadEta"        ,&dipho_subleadEta         );
    inTree_ -> SetBranchAddress("dipho_subleadPhi"        ,&dipho_subleadPhi         );
    inTree_ -> SetBranchAddress("dipho_subleadEt"         ,&dipho_subleadEt          ); 
    inTree_ -> SetBranchAddress("dipho_sublead_ptoM"      ,&dipho_sublead_ptoM       );
    inTree_ -> SetBranchAddress("dipho_subleadIDMVA"      ,&dipho_subleadIDMVA       );   
    inTree_ -> SetBranchAddress("dijet_Mjj"               ,&dijet_Mjj                );
    inTree_ -> SetBranchAddress("dijet_LeadJPt"           ,&dijet_LeadJPt            );
    inTree_ -> SetBranchAddress("dijet_leadEta"           ,&dijet_leadEta            );
    inTree_ -> SetBranchAddress("dijet_SubJPt"            ,&dijet_SubJPt             );
    inTree_ -> SetBranchAddress("dijet_subleadEta"        ,&dijet_subleadEta         );
    inTree_ -> SetBranchAddress("dijet_abs_dEta"          ,&dijet_abs_dEta           );
    inTree_ -> SetBranchAddress("dijet_dphi"              ,&dijet_dphi               );
    inTree_ -> SetBranchAddress("dijet_Zep"               ,&dijet_Zep                );
    inTree_ -> SetBranchAddress("dijet_dipho_dphi_trunc"  ,&dijet_dipho_dphi_trunc   );
    inTree_ -> SetBranchAddress("dijet_minDRJetPho"       ,&dijet_minDRJetPho        );
    inTree_ -> SetBranchAddress("dijet_centrality_gg"     ,&dijet_centrality_gg      );
    inTree_ -> SetBranchAddress("dijet_mva"               ,&dijet_mva                );
    inTree_ -> SetBranchAddress("dipho_mva"               ,&dipho_mva                );
    inTree_ -> SetBranchAddress("dipho_dijet_MVA"         ,&dipho_dijet_MVA          );
    inTree_ -> SetBranchAddress("nvtx"                    ,&nvtx                     );
    inTree_ -> SetBranchAddress("puweight"                ,&puweight                 );
    inTree_ -> SetBranchAddress("weight"                  ,&weight                   );
    if (sampleType_ != "data") {
        inTree_ -> SetBranchAddress("dijet_jet1_match"        ,&dijet_jet1_match         );
        inTree_ -> SetBranchAddress("dijet_jet2_match"        ,&dijet_jet2_match         );
    }
    cout << "[INFO]: Initialization is finished." << endl;
}


void ZPlusJetsValidSelector::selectLoop( string level, string state )
{
    Initialization();
    if (state != "") state = "_" + state;

    TFile* outfile = TFile::Open(Form("%s/Re_%s.root", outdir_.c_str(), (infilename_ + state +SystLabel_).c_str() ),"recreate");

    //diPhoton variables
    TH1D* h1_Mgg                   = new TH1D("h1_Mgg"                     ,""   ,80  ,70.  ,110.   );    h1_Mgg                     -> Sumw2();      
    TH1D* h1_lead_phoPt            = new TH1D("h1_lead_phoPt"              ,""   ,30  ,20.  ,260.   );    h1_lead_phoPt              -> Sumw2(); 
    TH1D* h1_lead_phoEta           = new TH1D("h1_lead_phoEta"             ,""   ,30  ,-3.  ,3.     );    h1_lead_phoEta             -> Sumw2(); 
    TH1D* h1_lead_phoId_mva        = new TH1D("h1_lead_phoId_mva"          ,""   ,40  ,-1.  ,1.     );    h1_lead_phoId_mva          -> Sumw2(); 
    TH1D* h1_leadPho_PToM          = new TH1D("h1_leadPho_PToM"            ,""   ,25  ,0.   ,4.     );    h1_leadPho_PToM            -> Sumw2(); 
    TH1D* h1_subl_phoPt            = new TH1D("h1_subl_phoPt"              ,""   ,30  ,20.  ,140.   );    h1_subl_phoPt              -> Sumw2(); 
    TH1D* h1_subl_phoEta           = new TH1D("h1_subl_phoEta"             ,""   ,30  ,-3.  ,3.     );    h1_subl_phoEta             -> Sumw2(); 
    TH1D* h1_subl_phoId_mva        = new TH1D("h1_subl_phoId_mva"          ,""   ,40  ,-1.  ,1.     );    h1_subl_phoId_mva          -> Sumw2(); 
    TH1D* h1_sublPho_PToM          = new TH1D("h1_sublPho_PToM"            ,""   ,25  ,0.   ,1.5    );    h1_sublPho_PToM            -> Sumw2(); 
    TH1D* h1_dipho_dEta            = new TH1D("h1_dipho_dEta"              ,""   ,40  ,0.   ,3.     );    h1_dipho_dEta              -> Sumw2(); 
    TH1D* h1_dipho_dphi            = new TH1D("h1_dipho_dphi"              ,""   ,40  ,0.   ,3.2    );    h1_dipho_dphi              -> Sumw2(); 
    //dijet variables
    TH1D* h1_Mjj                   = new TH1D("h1_Mjj"                     ,""   ,30  ,150. ,3500.  );    h1_Mjj                     -> Sumw2(); 
    TH1D* h1_lead_jetPt            = new TH1D("h1_lead_jetPt"              ,""   ,30  ,20.  ,290.   );    h1_lead_jetPt              -> Sumw2(); 
    TH1D* h1_lead_jetEta           = new TH1D("h1_lead_jetEta"             ,""   ,40  ,-5.  ,5.     );    h1_lead_jetEta             -> Sumw2(); 
    TH1D* h1_subl_jetPt            = new TH1D("h1_subl_jetPt"              ,""   ,30  ,10.  ,160.   );    h1_subl_jetPt              -> Sumw2(); 
    TH1D* h1_subl_jetEta           = new TH1D("h1_subl_jetEta"             ,""   ,40  ,-5.  ,5.     );    h1_subl_jetEta             -> Sumw2();
    TH1D* h1_dijet_dEta            = new TH1D("h1_dijet_dEta"              ,""   ,30  ,2.   ,8.     );    h1_dijet_dEta              -> Sumw2(); 
    TH1D* h1_dijet_dPhi            = new TH1D("h1_dijet_dPhi"              ,""   ,30  ,0.   ,3.3    );    h1_dijet_dPhi              -> Sumw2(); 
    TH1D* h1_dijet_Zep             = new TH1D("h1_dijet_Zep"               ,""   ,25  ,0.   ,8.     );    h1_dijet_Zep               -> Sumw2(); 
    TH1D* h1_dijet_dipho_dphi_trunc= new TH1D("h1_dijet_dipho_dphi_trunc"  ,""   ,30  ,0.   ,3.     );    h1_dijet_dipho_dphi_trunc  -> Sumw2(); 
    TH1D* h1_dijet_centrality_gg   = new TH1D("h1_dijet_centrality_gg"     ,""   ,25  ,0.   ,1.     );    h1_dijet_centrality_gg     -> Sumw2(); 
    TH1D* h1_dijet_minDRJetPho     = new TH1D("h1_dijet_minDRJetPho"       ,""   ,40  ,0.   ,0.5    );    h1_dijet_minDRJetPho       -> Sumw2(); 
    //MVA
    TH1D* h1_dipho_mva             = new TH1D("h1_dipho_mva"               ,""   ,40  ,-1.  ,1.     );    h1_dipho_mva               -> Sumw2(); 
    TH1D* h1_dijet_mva             = new TH1D("h1_dijet_mva"               ,""   ,25  ,0.2  ,1.     );    h1_dijet_mva               -> Sumw2(); 
    //TH1D* h1_dijet_mva             = new TH1D("h1_dijet_mva"               ,""   ,25  ,-1.  ,1.     );    h1_dijet_mva               -> Sumw2(); 
    TH1D* h1_dipho_dijet_mva       = new TH1D("h1_dipho_dijet_mva"         ,""   ,40  ,-0.2 ,1.     );    h1_dipho_dijet_mva         -> Sumw2(); 
    //Extra
    TH1D* h1_nvtx                  = new TH1D("h1_nvtx"                    ,""   ,40  ,0.   ,40.    );    h1_nvtx                    -> Sumw2(); 


    cout << "[INFO]: Start dumping "<< infilename_ << endl;
    for ( int entry=0;entry<inTree_->GetEntries();entry++ ) {
        inTree_->GetEntry(entry);
        
        bool loose_cut  = (   dipho_lead_ptoM>(1./4) && dipho_sublead_ptoM>(1./5)
                           && dijet_LeadJPt>30.      && dijet_SubJPt>20.       
                           && dijet_Mjj>100.         &&(dipho_mass>70. && dipho_mass<110.)
                            );
        bool medium_cut = true; 
                          //...
                          
                          
                          
                          
                          
        bool tight_cut  = true;
                          //...
                          
                          
                          
                          
                          

        bool select = true;
        bool jetcut = true;
        if      ( level == "Loose"  )  select = loose_cut;
        else if ( level == "Medium" )  select = medium_cut;
        else if ( level == "Tight"  )  select = tight_cut;
        else {cout <<"Don't find cut level. Loose cut is applied !!!"<<endl; select = loose_cut;}
        if ( sampleType_ != "data" ) {
            bool jet1fake = (dijet_jet1_match == 0. && dijet_jet2_match == 1.); 
            bool jet2fake = (dijet_jet1_match == 1. && dijet_jet2_match == 0.);
            bool bothfakes = (dijet_jet1_match == 0. && dijet_jet2_match == 0.);
            bool bothmatch = (dijet_jet1_match == 1. && dijet_jet2_match == 1.);
            if      ( state == "_jet1fake"  )  jetcut = jet1fake;
            else if ( state == "_jet2fake"  )  jetcut = jet2fake;
            else if ( state == "_bothfakes" )  jetcut = bothfakes; 
            else if ( state == "_bothmatch" )  jetcut = bothmatch;
        }
        
        if ( !(select && jetcut) ) continue;

        double dipho_dEta = fabs( dipho_leadEta - dipho_subleadEta );
        double dipho_dphi = fabs( dipho_leadPhi - dipho_subleadPhi );

        double totalWeight = 1;
        if ( sampleType_ != "data" ) {
            if (isGenWeight_) totalWeight = weight * lumi_;
            else totalWeight = eventWeight_ * puweight;
        }

        h1_Mgg                       ->Fill( dipho_mass               ,totalWeight ); 
        h1_lead_phoPt                ->Fill( dipho_leadPt             ,totalWeight ); 
        h1_lead_phoEta               ->Fill( dipho_leadEta            ,totalWeight ); 
        h1_lead_phoId_mva            ->Fill( dipho_leadIDMVA          ,totalWeight ); 
        h1_leadPho_PToM              ->Fill( dipho_lead_ptoM          ,totalWeight ); 
        h1_subl_phoPt                ->Fill( dipho_subleadPt          ,totalWeight ); 
        h1_subl_phoEta               ->Fill( dipho_subleadEta         ,totalWeight ); 
        h1_subl_phoId_mva            ->Fill( dipho_subleadIDMVA       ,totalWeight ); 
        h1_sublPho_PToM              ->Fill( dipho_sublead_ptoM       ,totalWeight ); 
        h1_dipho_dEta                ->Fill( dipho_dEta               ,totalWeight ); 
        h1_dipho_dphi                ->Fill( dipho_dphi               ,totalWeight ); 
        h1_Mjj                       ->Fill( dijet_Mjj                ,totalWeight ); 
        h1_lead_jetPt                ->Fill( dijet_LeadJPt            ,totalWeight ); 
        h1_lead_jetEta               ->Fill( dijet_leadEta            ,totalWeight ); 
        h1_subl_jetPt                ->Fill( dijet_SubJPt             ,totalWeight ); 
        h1_subl_jetEta               ->Fill( dijet_subleadEta         ,totalWeight ); 
        h1_dijet_dEta                ->Fill( dijet_abs_dEta           ,totalWeight ); 
        h1_dijet_dPhi                ->Fill( dijet_dphi               ,totalWeight ); 
        h1_dijet_Zep                 ->Fill( dijet_Zep                ,totalWeight ); 
        h1_dijet_dipho_dphi_trunc    ->Fill( dijet_dipho_dphi_trunc   ,totalWeight ); 
        h1_dijet_centrality_gg       ->Fill( dijet_centrality_gg      ,totalWeight ); 
        h1_dijet_minDRJetPho         ->Fill( dijet_minDRJetPho        ,totalWeight ); 
        h1_dipho_mva                 ->Fill( dipho_mva                ,totalWeight ); 
        h1_dijet_mva                 ->Fill( dijet_mva                ,totalWeight ); 
        h1_dipho_dijet_mva           ->Fill( dipho_dijet_MVA          ,totalWeight ); 
        h1_nvtx                      ->Fill( nvtx                     ,totalWeight ); 

    }//entry++

    sbevents_ = h1_Mgg->Integral();
    outfilename_ = "Re_" + infilename_ + state + SystLabel_ ;

    cout << "[INFO]: Dumping of "<<infilename_<<".root is finished !!!" << endl;

    outfile  ->  Write();
    outfile  ->  Close();

}

void ZPlusJetsValidSelector::setEventWeight( double wgt, bool isGenWeight )
{
    eventWeight_  = wgt;
    isGenWeight_ =isGenWeight;
}

void ZPlusJetsValidSelector::setLumi( double lumi )
{
    lumi_ = lumi;
}

void ZPlusJetsValidSelector::setSystLabel( string SystLabel )
{
    SystLabel_ = SystLabel;
}

double ZPlusJetsValidSelector::GetSBenents()
{
    return sbevents_;
}

string ZPlusJetsValidSelector::GetOutFileName()
{
    return outfilename_;
}
