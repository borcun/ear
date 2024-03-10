#ifndef TRANSPORT_SERVICE_MESSAGE_H
#define TRANSPORT_SERVICE_MESSAGE_H

#include <string>

namespace FACE {
    namespace TSS {
	class TSMessage {
	public:
	    TSMessage();
	    TSMessage(const uint32_t src, const uint32_t dst);
	    TSMessage(const uint32_t src, const uint32_t dst, const std::string &data);
	    virtual ~TSMessage();
	    void setSource(const uint32_t src);
	    void setDestination(const uint32_t dst);
	    void setData(const std::string &data);
	    uint32_t getSource() const;
	    uint32_t getDestination() const;
	    std::string getData() const;
	    
	private:
	    uint32_t m_src;
	    uint32_t m_dst;
	    std::string m_data;
	};
    }
}

#endif
