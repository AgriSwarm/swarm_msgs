"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import LandmarkCompact_t

class LandmarkDescriptor_t(object):
    __slots__ = ["landmark", "desc_len", "landmark_descriptor", "desc_len_int8", "landmark_descriptor_int8", "msg_id", "header_id"]

    __typenames__ = ["LandmarkCompact_t", "int32_t", "float", "int32_t", "int8_t", "int64_t", "int64_t"]

    __dimensions__ = [None, None, ["desc_len"], None, ["desc_len_int8"], None, None]

    def __init__(self):
        self.landmark = LandmarkCompact_t()
        self.desc_len = 0
        self.landmark_descriptor = []
        self.desc_len_int8 = 0
        self.landmark_descriptor_int8 = []
        self.msg_id = 0
        self.header_id = 0

    def encode(self):
        buf = BytesIO()
        buf.write(LandmarkDescriptor_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.landmark._get_packed_fingerprint() == LandmarkCompact_t._get_packed_fingerprint()
        self.landmark._encode_one(buf)
        buf.write(struct.pack(">i", self.desc_len))
        buf.write(struct.pack('>%df' % self.desc_len, *self.landmark_descriptor[:self.desc_len]))
        buf.write(struct.pack(">i", self.desc_len_int8))
        buf.write(struct.pack('>%db' % self.desc_len_int8, *self.landmark_descriptor_int8[:self.desc_len_int8]))
        buf.write(struct.pack(">qq", self.msg_id, self.header_id))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != LandmarkDescriptor_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return LandmarkDescriptor_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = LandmarkDescriptor_t()
        self.landmark = LandmarkCompact_t._decode_one(buf)
        self.desc_len = struct.unpack(">i", buf.read(4))[0]
        self.landmark_descriptor = struct.unpack('>%df' % self.desc_len, buf.read(self.desc_len * 4))
        self.desc_len_int8 = struct.unpack(">i", buf.read(4))[0]
        self.landmark_descriptor_int8 = struct.unpack('>%db' % self.desc_len_int8, buf.read(self.desc_len_int8))
        self.msg_id, self.header_id = struct.unpack(">qq", buf.read(16))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if LandmarkDescriptor_t in parents: return 0
        newparents = parents + [LandmarkDescriptor_t]
        tmphash = (0xd21abf75eaa17cda+ LandmarkCompact_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if LandmarkDescriptor_t._packed_fingerprint is None:
            LandmarkDescriptor_t._packed_fingerprint = struct.pack(">Q", LandmarkDescriptor_t._get_hash_recursive([]))
        return LandmarkDescriptor_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", LandmarkDescriptor_t._get_packed_fingerprint())[0]

