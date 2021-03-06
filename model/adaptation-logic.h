/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2015 Christian Kreuzberger and Daniel Posch, Alpen-Adria-University
 * Klagenfurt
 *
 * This file is part of amus-ndnSIM, based on ndnSIM. See AUTHORS for complete list of
 * authors and contributors.
 *
 * amus-ndnSIM and ndnSIM are free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * amus-ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * amus-ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef DASH_ADAPTATION_LOGIC
#define DASH_ADAPTATION_LOGIC

#define ENSURE_ADAPTATION_LOGIC_REGISTERED(x) \
  dash::player::AdaptationLogicFactory::RegisterAdaptationLogic (x::GetName (), &(x::Create));
#define ENSURE_ADAPTATION_LOGIC_INITIALIZED(x) x x::_staticLogic;

#include "adaptation-logic-factory.h"

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <stdlib.h>

#include "libdash.h"

using namespace ns3::dash::mpd;

namespace ns3 {
namespace dash {
namespace player {

typedef std::map<std::string, IRepresentation *> RepresentationsMap;

class AdaptationLogic
{
public:
  AdaptationLogic (MultimediaPlayer *mPlayer);
  virtual ~AdaptationLogic ();

  static AdaptationLogic *
  Create (MultimediaPlayer *mPlayer)
  {
    return new AdaptationLogic (mPlayer);
  }

  virtual std::string
  GetName () const
  {
    return "dash::player::AdaptationLogic";
  }

  virtual void
  SetAvailableRepresentations (std::map<std::string, IRepresentation *> *availableRepresentations);

  virtual ISegmentURL *GetNextSegment (unsigned int *requested_segment_number,
                                       const ns3::dash::mpd::IRepresentation **usedRepresentation,
                                       bool *hasDownloadedAllSegments);
  unsigned int getTotalSegments ();

  virtual bool hasMinBufferLevel (const ns3::dash::mpd::IRepresentation *rep);

  IRepresentation *GetLowestRepresentation ();

protected:
  MultimediaPlayer *m_multimediaPlayer;
  RepresentationsMap *m_availableRepresentations;

  static AdaptationLogic _staticLogic;

  AdaptationLogic ()
  {
    ENSURE_ADAPTATION_LOGIC_REGISTERED (AdaptationLogic);
  }
};

} // namespace player
} // namespace dash
} // namespace ns3

#endif // DASH_ADAPTATION_LOGIC
