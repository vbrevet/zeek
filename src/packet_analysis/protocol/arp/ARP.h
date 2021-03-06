// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include <packet_analysis/Analyzer.h>
#include <packet_analysis/Component.h>

#include <sys/socket.h>
#include <net/if_arp.h>

#ifndef arp_pkthdr
#define arp_pkthdr arphdr
#endif

namespace zeek::packet_analysis::ARP {

class ARPAnalyzer : public Analyzer {
public:
	ARPAnalyzer();
	~ARPAnalyzer() override = default;

	bool AnalyzePacket(size_t len, const uint8_t* data, Packet* packet) override;

	static zeek::packet_analysis::AnalyzerPtr Instantiate()
		{
		return std::make_shared<ARPAnalyzer>();
		}

private:
	zeek::AddrValPtr ToAddrVal(const void* addr);
	zeek::StringValPtr ToEthAddrStr(const u_char* addr);

	void BadARPEvent(const struct arp_pkthdr* hdr, const char* fmt, ...)
			__attribute__((format(printf, 3, 4)));
	void RequestReplyEvent(EventHandlerPtr e, const u_char* src, const u_char* dst,
			const char* spa, const char* sha, const char* tpa, const char* tha);
};

}
