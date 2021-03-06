/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2015 Christian Kreuzberger and Daniel Posch,
 *Alpen-Adria-University Klagenfurt
 *
 * This file is part of amus-ndnSIM, based on ndnSIM. See AUTHORS for complete
 *list of authors and contributors.
 *
 * amus-ndnSIM and ndnSIM are free software: you can redistribute it and/or
 *modify it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or (at your
 *option) any later version.
 *
 * amus-ndnSIM is distributed in the hope that it will be useful, but WITHOUT
 *ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *details.
 *
 * You should have received a copy of the GNU General Public License along with
 * amus-ndnSIM, e.g., in COPYING.md file.  If not, see
 *<http://www.gnu.org/licenses/>.
 **/

#ifndef DASH_MULTIMEDIA_PLAYER
#define DASH_MULTIMEDIA_PLAYER

#include <map>
#include <memory>
#include <string>
#include <typeinfo>

#include "adaptation-logic.h"
#include "multimediabuffer.h"

using namespace ns3::dash::mpd;

namespace ns3 {
namespace dash {
namespace player {

class MultimediaPlayer {
  friend class AdaptationLogic;

 public:
  // zMultimediaPlayer();
  MultimediaPlayer(std::string AdaptationLogicStr,
                   unsigned int maxBufferedSeconds);
  ~MultimediaPlayer();

  bool AddToBuffer(unsigned int segmentNr,
                   const dash::mpd::IRepresentation *usedRepresentation,
                   float experiencedDownloadBitrate, bool isLayeredContent);

  // Check if there is enough Space in Buffer
  bool EnoughSpaceInBuffer(unsigned int segmentNr,
                           const dash::mpd::IRepresentation *usedRepresentation,
                           bool isLayeredContent);

  double GetBufferLevel(std::string repId = std::string("NULL"));
  double GetBufferPercentage(std::string repId = std::string("NULL"));

  unsigned int getHighestBufferedSegmentNr(std::string repId);
  unsigned int nextSegmentNrToConsume();

  MultimediaBuffer::BufferRepresentationEntry ConsumeFromBuffer();

  void SetAvailableRepresentations(
      std::map<std::string, IRepresentation *> *availableRepresentations);

  AdaptationLogic *GetAdaptationLogic();

  void SetLastDownloadBitRate(double bitrate);

  double GetLastDownloadBitRate();

  void traverseBuff();

 protected:
  MultimediaBuffer *m_buffer;
  double m_lastBitrate;
  AdaptationLogic *m_adaptLogic;
  std::map<std::string, IRepresentation *> *m_availableRepresentations;
};
}  // namespace player
}  // namespace dash
}  // namespace ns3
#endif  // DASH_MULTIMEDIA_PLAYER
