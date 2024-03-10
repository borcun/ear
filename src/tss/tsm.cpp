#include "tsm.h"

FACE::TSS::TSMessage::TSMessage() {
    m_src = m_dst = 0;
}

FACE::TSS::TSMessage::TSMessage(const uint32_t src, const uint32_t dst)
    : m_src(src), m_dst(dst)
{

}

FACE::TSS::TSMessage::TSMessage(const uint32_t src, const uint32_t dst, const std::string &data)
    : m_src(src), m_dst(dst), m_data(data)
{

}

FACE::TSS::TSMessage::~TSMessage() {

}

void FACE::TSS::TSMessage::setSource(const uint32_t src) {
    m_src = src;
    return;
}

void FACE::TSS::TSMessage::setDestination(const uint32_t dst) {
    m_dst = dst;
    return;
}

void FACE::TSS::TSMessage::setData(const std::string &data) {
    m_data = data;
    return;
}

uint32_t FACE::TSS::TSMessage::getSource() const {
    return m_src;
}

uint32_t FACE::TSS::TSMessage::getDestination() const {
    return m_dst;
}

std::string FACE::TSS::TSMessage::getData() const {
    return m_data;
}
