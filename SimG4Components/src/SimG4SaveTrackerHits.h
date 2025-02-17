#ifndef SIMG4COMPONENTS_G4SAVETRACKERHITS_H
#define SIMG4COMPONENTS_G4SAVETRACKERHITS_H

// Gaudi
#include "GaudiAlg/GaudiTool.h"

// FCCSW
#include "k4FWCore/DataHandle.h"
#include "SimG4Interface/ISimG4SaveOutputTool.h"
class IGeoSvc;

// datamodel
namespace edm4hep {
class SimTrackerHitCollection;
}

/** @class SimG4SaveTrackerHits SimG4Components/src/SimG4SaveTrackerHits.h SimG4SaveTrackerHits.h
 *
 *  Save tracker hits tool.
 *  All collections passed in the job options will be saved (\b'readoutNames').
 *  Readout name is defined in DD4hep XML file as the attribute 'readout' of 'detector' tag.
 *  If (\b'readoutNames') contain no elements or names that do not correspond to any hit collection,
 *  tool will fail at initialization.
 *  [For more information please see](@ref md_sim_doc_geant4fullsim).
 *
 *  @author Anna Zaborowska
 *  @author Valentin Volkl (extended with Digi Info)
 */

class SimG4SaveTrackerHits : public GaudiTool, virtual public ISimG4SaveOutputTool {
public:
  explicit SimG4SaveTrackerHits(const std::string& aType, const std::string& aName, const IInterface* aParent);
  virtual ~SimG4SaveTrackerHits();
  /**  Initialize.
   *   @return status code
   */
  virtual StatusCode initialize();
  /**  Finalize.
   *   @return status code
   */
  virtual StatusCode finalize();
  /**  Save the data output.
   *   Saves the tracker hits from the collections as specified in the job options in \b'readoutNames'.
   *   @param[in] aEvent Event with data to save.
   *   @return status code
   */
  virtual StatusCode saveOutput(const G4Event& aEvent) final;

private:
  /// Pointer to the geometry service
  ServiceHandle<IGeoSvc> m_geoSvc;
  /// Pointer to Podio and Event Data Services
  PodioLegacyDataSvc* m_podioDataSvc;
  ServiceHandle<IDataProviderSvc> m_eventDataSvc;
  /// Handle for tracker hits
  DataHandle<edm4hep::SimTrackerHitCollection> m_trackHits{"TrackerHits", Gaudi::DataHandle::Writer, this};
  /// Handle for tracker hits including position information
  /// Name of the readouts (hits collections) to save
  Gaudi::Property<std::vector<std::string>> m_readoutNames{
      this, "readoutNames", {}, "Name of the readouts (hits collections) to save"};
};

#endif /* SIMG4COMPONENTS_G4SAVETRACKERHITS_H */
