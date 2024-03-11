#include "tsm.h"
#include <cstring>

FACE::TSS::TSMessage::TSMessage() {

}

FACE::TSS::TSMessage::TSMessage(const uint8_t *data, const uint32_t size) {
    setData(data, size);
}

FACE::TSS::TSMessage::~TSMessage() {

}

void FACE::TSS::TSMessage::setData(const uint8_t *data, const uint32_t size) {
    m_size = size > TS_MAX_DATA_SIZE ? TS_MAX_DATA_SIZE : size;
    memcpy(m_data, data, m_size);
    
    return;
}

const uint8_t *FACE::TSS::TSMessage::getData() const {
    return m_data;
}

uint32_t FACE::TSS::TSMessage::getSize() const {
    return m_size;
}

