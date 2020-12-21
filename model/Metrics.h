/*
 * Metrics.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef METRICS_H_
#define METRICS_H_

#include "das-config.h"

#include <string>
#include <vector>

#include "IMetrics.h"
#include "Descriptor.h"
#include "Range.h"
#include "AbstractMPDElement.h"

namespace ns3 {
namespace dash {
namespace mpd {
class Metrics : public IMetrics, public AbstractMPDElement
{
public:
  Metrics ();
  virtual ~Metrics ();

  const std::vector<IDescriptor *> &GetReportings () const;
  const std::vector<IRange *> &GetRanges () const;
  const std::string &GetMetrics () const;

  void AddReporting (Descriptor *reporting);
  void AddRange (Range *range);
  void SetMetrics (const std::string &metrics);

private:
  std::vector<Descriptor *> reportings;
  std::vector<Range *> ranges;
  std::string metrics;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* METRICS_H_ */
