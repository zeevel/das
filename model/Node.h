/*
 * Node.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef NODE_H_
#define NODE_H_

#include "das-config.h"

#include "INode.h"
#include "String.h"
#include "AdaptationSet.h"
#include "BaseUrl.h"
#include "ContentComponent.h"
#include "Descriptor.h"
#include "Metrics.h"
#include "MPD.h"
#include "MultipleSegmentBase.h"
#include "Period.h"
#include "ProgramInformation.h"
#include "Range.h"
#include "Representation.h"
#include "RepresentationBase.h"
#include "SegmentBase.h"
#include "SegmentList.h"
#include "SegmentTemplate.h"
#include "SegmentTimeline.h"
#include "SegmentURL.h"
#include "SubRepresentation.h"
#include "Subset.h"
#include "URLType.h"
#include "IHTTPTransaction.h"

namespace ns3 {
namespace dash {
namespace xml {
class Node : public INode
{
public:
  Node ();
  Node (const Node &other);
  virtual ~Node ();

  const std::vector<INode *> &GetNodes () const;
  const std::vector<Node *> &GetSubNodes () const;
  std::vector<std::string> GetAttributeKeys () const;
  const std::string &GetName () const;
  std::string GetText () const;
  const std::map<std::string, std::string> &GetAttributes () const;
  int GetType () const;
  void SetType (int type);
  const std::string &GetAttributeValue (std::string key) const;
  void AddSubNode (Node *node);
  void SetName (const std::string &name);
  bool HasAttribute (const std::string &name) const;
  void AddAttribute (const std::string &key, const std::string &value);
  bool HasText () const;
  void SetText (const std::string &text);
  void Print (std::ostream &stream) const;
  dash::mpd::MPD *ToMPD () const;
  void SetMPDPath (std::string path);

private:
  void SetCommonValuesForRep (dash::mpd::RepresentationBase &object) const;
  void SetCommonValuesForSeg (dash::mpd::SegmentBase &object) const;
  void SetCommonValuesForMSeg (dash::mpd::MultipleSegmentBase &object) const;
  dash::mpd::AdaptationSet *ToAdaptationSet () const;
  dash::mpd::BaseUrl *ToBaseUrl () const;
  dash::mpd::ContentComponent *ToContentComponent () const;
  dash::mpd::Descriptor *ToDescriptor () const;
  dash::mpd::Metrics *ToMetrics () const;
  dash::mpd::Period *ToPeriod () const;
  dash::mpd::ProgramInformation *ToProgramInformation () const;
  dash::mpd::Range *ToRange () const;
  dash::mpd::Representation *ToRepresentation () const;
  dash::mpd::SegmentBase *ToSegmentBase () const;
  dash::mpd::SegmentList *ToSegmentList () const;
  dash::mpd::SegmentTemplate *ToSegmentTemplate () const;
  dash::mpd::Timeline *ToTimeline () const;
  dash::mpd::SegmentTimeline *ToSegmentTimeline () const;
  dash::mpd::SegmentURL *ToSegmentURL () const;
  dash::mpd::SubRepresentation *ToSubRepresentation () const;
  dash::mpd::Subset *ToSubset () const;
  dash::mpd::URLType *ToURLType (dash::metrics::HTTPTransactionType transActType) const;

  std::vector<Node *> subNodes;
  std::map<std::string, std::string> attributes;
  std::string name;
  std::string text;
  int type;
  std::string mpdPath;
};
} // namespace xml
} // namespace dash
} // namespace ns3
#endif /* NODE_H_ */
