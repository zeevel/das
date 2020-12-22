#ifndef MDDIA_GYM_H
#define MEDIA_GYM_H

#include "ns3/core-module.h"
#include "ns3/opengym-module.h"

namespace ns3 {

class MediaGym : public OpenGymEnv {
 public:
  // Constructor Deconstructor and ns3 object interface
  MediaGym();
  virtual ~MediaGym();
  static TypeId GetTypeId(void);
  virtual void DoDispose();

  // OpenGym Interface, need to be overwriten
  virtual Ptr<OpenGymSpace> GetActionSpace();
  virtual Ptr<OpenGymSpace> GetObservationSpace();
  virtual bool GetGameOver();
  virtual Ptr<OpenGymDataContainer> GetObservation();
  virtual float GetReward();
  virtual std::string GetExtraInfo();
  virtual bool ExecuteActions(Ptr<OpenGymDataContainer> action);

  // tool function
  void ClearObs();
  uint32_t GetRepIndex();
  void PrintState();
  void UpdateState(int64_t segmentCounter, int64_t bufferNow,
                   int64_t lastchunkfinishtime, int64_t lastchunkstarttime,
                   int64_t m_lastchunksize, int64_t rebuffertime);

 protected:
  int64_t m_highestRepIndex;
  int64_t m_lastSegmentIndex;
  uint32_t m_old_rep_index;
  uint32_t m_new_rep_index;
  int64_t m_bufferNow;
  int64_t m_bufferLast;
  int64_t m_segmentCounter;
  int64_t m_reward;
  int64_t m_lastChunkFinishTime;
  int64_t m_lastChunkStartTime;
  int64_t m_lastChunkSize;
  int64_t m_rebufferTime;
};

}  // namespace ns3

#endif