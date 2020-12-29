#include "MediaGym.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("ns3::MediaGym");
NS_OBJECT_ENSURE_REGISTERED(MediaGym);

MediaGym::MediaGym() {
  NS_LOG_FUNCTION(this);

  m_new_rep_index = 0;
  m_old_rep_index = 0;
  m_highestRepIndex = 3;
  m_lastSegmentIndex = 10;
  m_reward = 1;
  m_bufferLast = 0;
  m_lastChunkFinishTime = 0;
  m_lastChunkStartTime = 0;
  m_lastChunkSize = 0;
  m_rebufferTime = 0;
}

MediaGym::~MediaGym() { NS_LOG_FUNCTION(this); }

TypeId MediaGym::GetTypeId(void) {
  static TypeId tid = TypeId("MediaGym")
                          .SetParent<OpenGymEnv>()
                          .SetGroupName("OpenGym")
                          .AddConstructor<MediaGym>();
  return tid;
}

void MediaGym::DoDispose() { NS_LOG_FUNCTION(this); }

Ptr<OpenGymSpace> MediaGym::GetObservationSpace() {
  NS_LOG_FUNCTION(this);

  uint32_t buffernum = 2000000;
  uint32_t lastReq = m_lastSegmentIndex;
  uint32_t lastQual = 8;
  uint32_t lastchunkfinishtime = 2000000;
  uint32_t lastchunkstarttime = 2000000;
  uint32_t rebuffertime = 2000000;
  uint32_t lastchunksize = 0;

  Ptr<OpenGymDiscreteSpace> buffer =
      CreateObject<OpenGymDiscreteSpace>(buffernum);
  Ptr<OpenGymDiscreteSpace> lastRequest =
      CreateObject<OpenGymDiscreteSpace>(lastReq);
  Ptr<OpenGymDiscreteSpace> lastQuality =
      CreateObject<OpenGymDiscreteSpace>(lastQual);
  Ptr<OpenGymDiscreteSpace> lastChunkFinishTime =
      CreateObject<OpenGymDiscreteSpace>(lastchunkfinishtime);
  Ptr<OpenGymDiscreteSpace> lastChunkStartTime =
      CreateObject<OpenGymDiscreteSpace>(lastchunkstarttime);
  Ptr<OpenGymDiscreteSpace> RebufferTime =
      CreateObject<OpenGymDiscreteSpace>(rebuffertime);
  Ptr<OpenGymDiscreteSpace> lastChunkSize =
      CreateObject<OpenGymDiscreteSpace>(lastchunksize);

  Ptr<OpenGymDictSpace> space = CreateObject<OpenGymDictSpace>();
  space->Add("buffer", buffer);
  space->Add("lastRequest", lastRequest);
  space->Add("lastQuality", lastQuality);
  space->Add("lastChunkFinishTime", lastChunkFinishTime);
  space->Add("lastChunkStartTime", lastChunkStartTime);
  space->Add("RebufferTime", RebufferTime);
  space->Add("lastChunkSize", lastChunkSize);

  return space;
}

Ptr<OpenGymSpace> MediaGym::GetActionSpace() {
  NS_LOG_FUNCTION(this);
  uint32_t highestRepIndex = m_highestRepIndex;
  Ptr<OpenGymDiscreteSpace> space =
      CreateObject<OpenGymDiscreteSpace>(highestRepIndex);
  return space;
}

bool MediaGym::GetGameOver() {
  NS_LOG_FUNCTION(this);
  bool isGameOver = false;
  if (m_segmentCounter == m_lastSegmentIndex - 1) {
    NS_LOG_UNCOND("seg counter: " << m_segmentCounter);
    NS_LOG_UNCOND("last seg: " << m_lastSegmentIndex);
    isGameOver = true;
    NS_LOG_UNCOND("GetGameOver: " << isGameOver);
  }
  return isGameOver;
}

Ptr<OpenGymDataContainer> MediaGym::GetObservation() {
  NS_LOG_FUNCTION(this);

  Ptr<OpenGymDiscreteContainer> buffer =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> lastRequest =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> lastQuality =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> lastChunkFinishTime =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> lastChunkStartTime =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> RebufferTime =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> lastChunkSize =
      CreateObject<OpenGymDiscreteContainer>();

  buffer->SetValue(m_bufferNow);
  lastRequest->SetValue(m_segmentCounter);
  lastQuality->SetValue(m_new_rep_index);
  lastChunkFinishTime->SetValue(m_lastChunkFinishTime);
  lastChunkStartTime->SetValue(m_lastChunkStartTime);
  RebufferTime->SetValue(m_rebufferTime);
  lastChunkSize->SetValue(m_lastChunkSize);

  Ptr<OpenGymDictContainer> space = CreateObject<OpenGymDictContainer>();
  space->Add("buffer", buffer);
  space->Add("lastRequest", lastRequest);
  space->Add("lastQuality", lastQuality);
  space->Add("lastChunkFinishTime", lastChunkFinishTime);
  space->Add("lastChunkStartTime", lastChunkStartTime);
  space->Add("RebufferTime", RebufferTime);
  space->Add("lastChunkSize", lastChunkSize);

  return space;
}

float MediaGym::GetReward() {
  NS_LOG_FUNCTION(this);
  return m_reward;
}

std::string MediaGym::GetExtraInfo() {
  std::string info = "extra info";
  return info;
}

bool MediaGym::ExecuteActions(Ptr<OpenGymDataContainer> action) {
  NS_LOG_FUNCTION(this);
  m_old_rep_index = m_new_rep_index;
  Ptr<OpenGymDiscreteContainer> discrete =
      DynamicCast<OpenGymDiscreteContainer>(action);
  m_new_rep_index = discrete->GetValue();
  return true;
}

void MediaGym::ClearObs() { NS_LOG_FUNCTION(this); }

uint32_t MediaGym::GetRepIndex() {
  Notify();
  return m_new_rep_index;
}

void MediaGym::PrintState() {
  NS_LOG_UNCOND("Rep old: " << m_old_rep_index
                            << " --  Rep new : " << m_new_rep_index);
}

void MediaGym::UpdateState(int64_t segmentCounter, int64_t bufferNow,
                           int64_t lastchunkfinishtime,
                           int64_t lastchunkstarttime, int64_t lastchunksize,
                           int64_t rebuffertime) {
  m_lastChunkFinishTime = lastchunkfinishtime;
  m_lastChunkStartTime = lastchunkstarttime;
  m_segmentCounter = segmentCounter;
  m_bufferLast = m_bufferNow;
  m_bufferNow = bufferNow;
  m_lastChunkSize = lastchunksize;
  m_rebufferTime = rebuffertime;
}

}  // namespace ns3