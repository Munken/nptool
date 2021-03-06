#ifndef __LaBr3Physics__
#define __LaBr3Physics__
/*****************************************************************************
 * Copyright (C) 2009-2016    this file is part of the NPTool Project        *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Adrien MATTA  contact address: a.matta@surrey.ac.uk      *
 *                                                                           *
 * Creation Date  : November 2009                                            *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class hold theLaBr3 Detector  Physics                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
 
//   STL
#include <vector>
using namespace std ;

class TLaBr3Spectra;
//   ROOT
#include "TObject.h"

//   NPL
#include "TLaBr3Data.h"
#include "TLaBr3Spectra.h"
#include "NPVDetector.h"
#include "NPCalibrationManager.h"

class TLaBr3Physics : public TObject, public NPL::VDetector
{
   public:   //   Constructor and Destructor
      TLaBr3Physics();
      ~TLaBr3Physics();

   public:
      void  Clear();
      void  Clear(const Option_t*) {};
   
   public:   //   Calibrated Data
      vector<UShort_t>   DetectorNumber ;
      vector<Double_t>   Energy;
      vector<Double_t>   Time;

   public:   //   inherrited from VDetector
      //   Read stream at ConfigFile to pick-up parameters of detector (Position,...) using Token
      void ReadConfiguration(string);
      

      //   Add Parameter to the CalibrationManger
      void AddParameterToCalibrationManager();      

      //   Activated associated Branches and link it to the private member DetectorData address
      //   In this method mother Branches (Detector) AND daughter leaf (fDetector_parameter) have to be activated
      void InitializeRootInputRaw() ;
      
      //   Activated associated Branches and link it to the private member DetectorPhysics address
      //   In this method mother Branches (Detector) AND daughter leaf (parameter) have to be activated
      void InitializeRootInputPhysics() ;

      //   Create associated branches and associated private member DetectorPhysics address
      void InitializeRootOutput();
      
      //   This method is called at each event read from the Input Tree. Aime is to build treat Raw dat in order to extract physical parameter. 
      void BuildPhysicalEvent();
      
      //   Same as above, but only the simplest event and/or simple method are used (low multiplicity, faster algorythm but less efficient ...).
      //   This method aimed to be used for analysis performed during experiment, when speed is requiered.
      //   NB: This method can eventually be the same as BuildPhysicalEvent.
      void BuildSimplePhysicalEvent();

      // Same as above but for online analysis
      void BuildOnlinePhysicalEvent()  {BuildPhysicalEvent();};

      // Give and external TLaBr3Data object to TLaBr3Physics. Needed for online analysis for example.
      void SetRawDataPointer(TLaBr3Data* rawDataPointer) {EventData = rawDataPointer;}

      //   Those two method all to clear the Event Physics or Data
      void ClearEventPhysics() {Clear();}      
      void ClearEventData()    {EventData->Clear();}      

    // Method related to the TSpectra classes, aimed at providing a framework for online applications
    // Instantiate the Spectra class and the histogramm throught it
    void InitSpectra();
    // Fill the spectra hold by the spectra class
    void FillSpectra();
    // Used for Online mainly, perform check on the histo and for example change their color if issues are found
    void CheckSpectra();
    // Used for Online only, clear all the spectra hold by the Spectra class
    void ClearSpectra();
    //   Clear The PreTeated object
    void ClearPreTreatedData()   {PreTreatedData->Clear();}

    //   Remove bad channel, calibrate the data and apply threshold
    void PreTreat();
    
   private:   // Data not writted in the tree
      int                NumberOfDetector ;//!
      TLaBr3Data*         EventData ;//!
      TLaBr3Data*         PreTreatedData ;//!
      TLaBr3Physics*      EventPhysics ;//!
      TLaBr3Spectra*	     m_Spectra;//!
      double 		 m_LaBr3_E_Threshold;   
      double 		 m_LaBr3_RAW_Threshold;   
  public: // Spectra Getter
    map< string , TH1*> GetSpectra(); 

      public: // Static constructor to be passed to the Detector Factory
     static NPL::VDetector* Construct();
     ClassDef(TLaBr3Physics,1)  // LaBr3Physics structure
};

#endif
