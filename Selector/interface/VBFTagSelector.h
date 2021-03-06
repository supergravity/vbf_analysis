#ifndef __VBFTAGSELECTOR__
#define __VBFTAGSELECTOR__

#include <string>

#include "TFile.h"
#include "TTree.h"

class VBFTagSelector{

    public:
        VBFTagSelector(std::string indir, std::string infilename, std::string sampleName, std::string outdir);
        ~VBFTagSelector();
        void SetSignalRegion(double min, double max);
        void selectLoop(bool isSideBand = true);
        void SetSystLabel(std::string SystLabel = "");

    private:

        TFile* infile_;
        TTree* inTree_;
        std::string indir_;
        std::string infilename_;
        std::string sampleName_;
        std::string SystLabel_;
        std::string outdir_;
        double min_;
        double max_;

        void Initialization();
        Float_t dipho_mass              ; 
        Float_t dipho_leadPt            ; 
        Float_t dipho_leadEta           ; 
        Float_t dipho_leadPhi           ; 
        Float_t dipho_leadEt            ; 
        Float_t dipho_lead_ptoM         ; 
        Float_t dipho_leadIDMVA         ; 
        Float_t dipho_subleadPt         ; 
        Float_t dipho_subleadEta        ; 
        Float_t dipho_subleadPhi        ; 
        Float_t dipho_subleadEt         ; 
        Float_t dipho_sublead_ptoM      ;
        Float_t dipho_subleadIDMVA      ;
        Float_t dijet_Mjj               ; 
        Float_t dijet_LeadJPt           ; 
        Float_t dijet_leadEta           ; 
        Float_t dijet_SubJPt            ; 
        Float_t dijet_subleadEta        ; 
        Float_t dijet_abs_dEta          ; 
        Float_t dijet_dphi              ; 
        Float_t dijet_Zep               ; 
        Float_t dijet_dipho_dphi_trunc  ; 
        Float_t dijet_minDRJetPho       ;
        Float_t dijet_centrality_gg     ;
        Float_t dijet_mva               ; 
        Float_t dipho_mva               ; 
        Float_t dipho_dijet_MVA         ; 
        Int_t nvtx                      ; 
        Float_t puweight                ; 
        Float_t weight                  ;
        Float_t jet1_pt                 ; 
        Float_t jet1_eta                ; 
        Float_t jet1_Phi                ; 
        Float_t jet1_mass               ; 
        Float_t jet2_pt                 ; 
        Float_t jet2_eta                ; 
        Float_t jet2_Phi                ; 
        Float_t jet2_mass               ; 
        Float_t jet3_pt                 ; 
        Float_t jet3_eta                ; 
        Float_t jet3_Phi                ; 
        Float_t jet3_mass               ; 

        //outTree
        Float_t dijet_LeadJPt_           ;
        Float_t dijet_SubJPt_            ;
        Float_t dijet_abs_dEta_          ;
        Float_t dijet_Mjj_               ;
        Float_t dijet_centrality_gg_     ;
        Float_t dijet_dipho_dphi_trunc_  ;
        Float_t dijet_dphi_              ;
        Float_t dijet_minDRJetPho_       ;
        Float_t dipho_lead_ptoM_         ;
        Float_t dipho_sublead_ptoM_      ;
        Float_t dipho_mva_               ;
        Float_t dipho_dijet_MVA_         ;


};

#endif
