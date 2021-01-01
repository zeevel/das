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

  m_segmentTotalNumber = 100;
  m_bufferNow = 30;
  m_lastSegmentBitrate = 1000000;
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

  double bufferN = 30;
  double lastSegmentB = 1000000;

  Ptr<OpenGymDiscreteSpace> bufferNow =
      CreateObject<OpenGymDiscreteSpace>(bufferN);
  Ptr<OpenGymDiscreteSpace> lastSegmentBitrate =
      CreateObject<OpenGymDiscreteSpace>(lastSegmentB);

  Ptr<OpenGymDictSpace> space = CreateObject<OpenGymDictSpace>();
  space->Add("bufferNow", bufferNow);
  space->Add("lastSegmentBitrate", lastSegmentBitrate);

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
  if (m_segmentTotalNumber == m_lastSegmentIndex - 1) {
    NS_LOG_UNCOND("seg counter: " << m_segmentTotalNumber);
    NS_LOG_UNCOND("last seg: " << m_lastSegmentIndex);
    isGameOver = true;
    NS_LOG_UNCOND("GetGameOver: " << isGameOver);
  }
  return isGameOver;
}

Ptr<OpenGymDataContainer> MediaGym::GetObservation() {
  NS_LOG_FUNCTION(this);
  // std::cout << "[MediaGym::GetObservation()]" << std::endl;

  Ptr<OpenGymDiscreteContainer> bufferNow =
      CreateObject<OpenGymDiscreteContainer>();
  Ptr<OpenGymDiscreteContainer> lastSegmentBitrate =
      CreateObject<OpenGymDiscreteContainer>();

  bufferNow->SetValue(m_bufferNow);
  lastSegmentBitrate->SetValue(m_lastSegmentBitrate);

  Ptr<OpenGymDictContainer> space = CreateObject<OpenGymDictContainer>();
  space->Add("bufferNow", bufferNow);
  space->Add("lastSegmentBitrate", lastSegmentBitrate);

  return space;
}

float MediaGym::GetReward() {
  NS_LOG_FUNCTION(this);
  if (m_bufferNow > m_bufferLast) {
    m_reward = m_reward + 1;
  } else {
    m_reward = 0;
  }
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
  std::cout << "[MediaGym::GetRepIndex()]" << std::endl;
  Notify();
  return m_new_rep_index;
}

void MediaGym::PrintState() {
  NS_LOG_UNCOND("Rep old: " << m_old_rep_index
                            << " --  Rep new : " << m_new_rep_index);
}

void MediaGym::UpdateState(unsigned int segmentTotalNumber, double bufferNow,
                           double lastSegmentBitrate) {
  printf("[MediaGym::UpdateStaet(%d, %lf, %lf)\n", segmentTotalNumber,
         bufferNow, lastSegmentBitrate);
  m_bufferNow = bufferNow;
  m_bufferLast = m_bufferNow;
  m_lastSegmentBitrate = lastSegmentBitrate;
}

}  // namespace ns3