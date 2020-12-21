/*
 * SubRepresentation.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef SUBREPRESENTATION_H_
#define SUBREPRESENTATION_H_

#include "das-config.h"

#include "ISubRepresentation.h"
#include "Descriptor.h"
#include "RepresentationBase.h"
#include "String.h"

namespace ns3 {
namespace dash {
namespace mpd {
class SubRepresentation : public ISubRepresentation, public RepresentationBase
{
public:
  SubRepresentation ();
  virtual ~SubRepresentation ();

  uint32_t GetLevel () const;
  const std::vector<uint32_t> &GetDependencyLevel () const;
  uint32_t GetBandWidth () const;
  const std::vector<std::string> &GetContentComponent () const;

  void SetLevel (uint32_t level);
  void SetDependencyLevel (const std::string &dependencyLevel);
  void SetBandWidth (uint32_t bandWidth);
  void SetContentComponent (const std::string &contentComponent);

protected:
  uint32_t level;
  std::vector<uint32_t> dependencyLevel;
  uint32_t bandWidth;
  std::vector<std::string> contentComponent;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* SUBREPRESENTATION_H_ */
