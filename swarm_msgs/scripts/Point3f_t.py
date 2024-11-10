"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class Point3f_t(object):
    __slots__ = ["x", "y", "z"]

    __typenames__ = ["float", "float", "float"]

    __dimensions__ = [None, None, None]

    def __init__(self):
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(Point3f_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">fff", self.x, self.y, self.z))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != Point3f_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return Point3f_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = Point3f_t()
        self.x, self.y, self.z = struct.unpack(">fff", buf.read(12))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if Point3f_t in parents: return 0
        tmphash = (0x2a14f112c253ac0c) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if Point3f_t._packed_fingerprint is None:
            Point3f_t._packed_fingerprint = struct.pack(">Q", Point3f_t._get_hash_recursive([]))
        return Point3f_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

