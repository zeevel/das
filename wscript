# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

def configure(conf):
    # conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')
    # conf.env.append_value("LINKFLAGS", ["-lcurl"])

    have_curl = conf.check_cfg(package='libcurl', uselib_store='LIBCURL',
                                  args=['--cflags', '--libs'],
                                  mandatory=True)
    conf.env['CURL'] = have_curl
    conf.report_optional_feature("LIBCURL", "libcurl which dash depends on",
                                 conf.env['CURL'],
                                 "library 'curl' not found")

    have_xml = conf.check_cfg(package='libXML', uselib_store='LIBXML',
                                  args=['--cflags', '--libs'],
                                  mandatory=True)
    conf.env['XML'] = have_xml
    conf.report_optional_feature("LIBXML", "libxml which dash depends on",
                                 conf.env['XML'],
                                 "library 'xml' not found")

def build(bld):
    module = bld.create_ns3_module('das', ['internet', 'mobility', 'wifi'])
    module.source = [
        'model/das.cc',
        'helper/das-helper.cc',
        'model/AbstractChunk.cpp',
        'model/AbstractMPDElement.cpp',
        'model/AdaptationSet.cpp',
        'model/BaseUrl.cpp',
        'model/BlockStream.cpp',
        'model/ContentComponent.cpp',
        'model/Descriptor.cpp',
        'model/DownloadStateManager.cpp',
        'model/HTTPTransaction.cpp',
        'model/Metrics.cpp',
        'model/MPD.cpp',
        'model/MultipleSegmentBase.cpp',
        'model/MultiThreading.cpp',
        'model/Path.cpp',
        'model/Period.cpp',
        'model/ProgramInformation.cpp',
        'model/Range.cpp',
        'model/Representation.cpp',
        'model/RepresentationBase.cpp',
        'model/Segment.cpp',
        'model/SegmentBase.cpp',
        'model/SegmentList.cpp',
        'model/SegmentTemplate.cpp',
        'model/SegmentTimeline.cpp',
        'model/SegmentURL.cpp',
        'model/String.cpp',
        'model/SubRepresentation.cpp',
        'model/Subset.cpp',
        'model/SyncedBlockStream.cpp',
        'model/TCPConnection.cpp',
        'model/ThroughputMeasurement.cpp',
        'model/Time.cpp',
        'model/Timeline.cpp',
        'model/URLType.cpp',
        'model/Node.cpp',
        'model/DOMParser.cpp',
        'model/DOMHelper.cpp',
        'model/libdash.cpp',
        'model/DASHManager.cpp',
        'model/multimediabuffer.cpp',
        'model/multimedia-player.cpp',
        'alogic/adaptation-logic-always-lowest.cpp',
        'alogic/adaptation-logic-buffer-based.cpp',
        'alogic/adaptation-logic-dashjs.cpp',
        'alogic/adaptation-logic-manual.cpp',
        'alogic/adaptation-logic-rate-and-buffer-based.cpp',
        'alogic/adaptation-logic-rate-based.cpp',
        'alogic/adaptation-logic-svc-buffer-based-aggressive.cpp',
        'alogic/adaptation-logic-svc-buffer-based-conservative.cpp',
        'alogic/adaptation-logic-svc-buffer-based-normal.cpp',
        'alogic/adaptation-logic-svc-buffer-based.cpp',
        'alogic/adaptation-logic-svc-rate-based.cpp',
        'alogic/adaptation-logic.cpp',
        'alogic/adaptation-no-logic.cpp',
        'alogic/adaptation-logic-rl-based.cpp'
        ]

    module_test = bld.create_ns3_module_test_library('das')
    module_test.source = [
        'test/das-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'das'
    headers.source = [
        'model/das.h',
        'helper/das-helper.h',
        'model/AbstractChunk.h',
        'model/AbstractMPDElement.h',
        'model/adaptation-logic-factory.h',
        'model/adaptation-logic.h',
        'model/AdaptationSet.h',
        'model/BaseUrl.h',
        'model/Block.h',
        'model/BlockStream.h',
        'model/das-config.h',
        'model/ContentComponent.h',
        'model/Descriptor.h',
        'model/DownloadStateManager.h',
        'model/HTTPTransaction.h',
        'model/IAdaptationSet.h',
        'model/IBaseUrl.h',
        'model/IChunk.h',
        'model/IConnection.h',
        'model/IContentComponent.h',
        'model/IDASHManager.h',
        'model/IDASHMetrics.h',
        'model/IDescriptor.h',
        'model/IDownloadableChunk.h',
        'model/IDownloadObserver.h',
        'model/IHTTPTransaction.h',
        'model/IMetrics.h',
        'model/IMPD.h',
        'model/IMPDElement.h',
        'model/IMultipleSegmentBase.h',
        'model/INode.h',
        'model/IPeriod.h',
        'model/IProgramInformation.h',
        'model/IRange.h',
        'model/IRepresentation.h',
        'model/IRepresentationBase.h',
        'model/ISegment.h',
        'model/ISegmentBase.h',
        'model/ISegmentList.h',
        'model/ISegmentTemplate.h',
        'model/ISegmentURL.h',
        'model/ISubRepresentation.h',
        'model/ISegmentTimeline.h',
        'model/ISubset.h',
        'model/ITCPConnection.h',
        'model/IThroughputMeasurement.h',
        'model/ITimeline.h',
        'model/IURLType.h',
        'model/libdash.h',
        'model/Metrics.h',
        'model/MPD.h',
        'model/multimedia-player.h',
        'model/multimediabuffer.h',
        'model/MultipleSegmentBase.h',
        'model/MultiThreading.h',
        'model/Networking.h',
        'model/Path.h',
        'model/Period.h',
        'model/ProgramInformation.h',
        'model/Range.h',
        'model/Representation.h',
        'model/Segment.h',
        'model/SegmentBase.h',
        'model/SegmentList.h',
        'model/SegmentTemplate.h',
        'model/SegmentTimeline.h',
        'model/SegmentURL.h',
        'model/String.h',
        'model/SubRepresentation.h',
        'model/Subset.h',
        'model/SyncedBlockStream.h',
        'model/TCPConnection.h',
        'model/ThroughputMeasurement.h',
        'model/Time.h',
        'model/Timeline.h',
        'model/URLType.h',
        'model/Node.h',
        'model/DOMParser.h',
        'model/DOMHelper.h',
        'model/DASHManager.h',
        'alogic/adaptation-logic-always-lowest.h',
        'alogic/adaptation-logic-buffer-based.h',
        'alogic/adaptation-logic-dashjs.h',
        'alogic/adaptation-logic-manual.h',
        'alogic/adaptation-logic-rate-and-buffer-based.h',
        'alogic/adaptation-logic-rate-based.h',
        'alogic/adaptation-logic-svc-buffer-based.h',
        'alogic/adaptation-logic-svc-rate-based.h',
        'alogic/adaptation-no-logic.h',
        'alogic/adaptation-logic-rl-based.h'
        ]
    
    # if bld.env['ENABLE_CURL']:
    #     print('has ENABLE CURL')
    # module.use.extend(['CURL'])
    # module_test.extend(['CURL'])

    #if bld.env['CURL']:
    #     print("use curl !!!!!!")
    #     module.use.append("LIBCURL")
    module.use.append("LIBCURL")
    module.use.append("LIBXML")

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

