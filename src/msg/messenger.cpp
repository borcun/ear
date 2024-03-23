#include "messenger.h"

EAR::Messenger::Messenger(const std::string &node) : m_node(node) { }

EAR::Messenger::~Messenger() { }

const std::string &EAR::Messenger::getNode() const {
    return m_node;
}
