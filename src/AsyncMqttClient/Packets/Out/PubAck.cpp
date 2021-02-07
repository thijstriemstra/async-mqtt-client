#include "PubAck.hpp"

using AsyncMqttClientInternals::PubAckOutPacket;

PubAckOutPacket::PubAckOutPacket(PendingAck pendingAck) {
    _data[0] = pendingAck.packetType;
    _data[0] = _data[0] << 4;
    _data[0] = _data[0] | pendingAck.headerFlag;
    _data[1] = 2;
    _packetId = pendingAck.packetId;
    _data[2] = pendingAck.packetId >> 8;
    _data[3] = pendingAck.packetId & 0xFF;
    _released = false;
}

const uint8_t* PubAckOutPacket::data(size_t index) const {
  return &_data[index];
}

size_t PubAckOutPacket::size() const {
  return 4;
}

bool PubAckOutPacket::released() const {
  if (packetType() == AsyncMqttClientInternals::PacketType.PUBREL) {
    return _released;
  }
  return true;
}

uint16_t PubAckOutPacket::packetId() const {
  return _packetId;
}
