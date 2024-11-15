"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import Time_t

import Pose_t

class PositionCommand_t(object):
    __slots__ = ["stamp", "drone_id", "pose"]

    __typenames__ = ["Time_t", "int32_t", "Pose_t"]

    __dimensions__ = [None, None, None]

    def __init__(self):
        self.stamp = Time_t()
        self.drone_id = 0
        self.pose = Pose_t()

    def encode(self):
        buf = BytesIO()
        buf.write(PositionCommand_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.stamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.stamp._encode_one(buf)
        buf.write(struct.pack(">i", self.drone_id))
        assert self.pose._get_packed_fingerprint() == Pose_t._get_packed_fingerprint()
        self.pose._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != PositionCommand_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return PositionCommand_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = PositionCommand_t()
        self.stamp = Time_t._decode_one(buf)
        self.drone_id = struct.unpack(">i", buf.read(4))[0]
        self.pose = Pose_t._decode_one(buf)
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if PositionCommand_t in parents: return 0
        newparents = parents + [PositionCommand_t]
        tmphash = (0x5b52c3531cd10e82+ Time_t._get_hash_recursive(newparents)+ Pose_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if PositionCommand_t._packed_fingerprint is None:
            PositionCommand_t._packed_fingerprint = struct.pack(">Q", PositionCommand_t._get_hash_recursive([]))
        return PositionCommand_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

