"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class CommandTOL_t(object):
    __slots__ = ["drone_id", "min_pitch", "yaw", "latitude", "longitude", "altitude"]

    __typenames__ = ["int32_t", "float", "float", "float", "float", "float"]

    __dimensions__ = [None, None, None, None, None, None]

    def __init__(self):
        self.drone_id = 0
        self.min_pitch = 0.0
        self.yaw = 0.0
        self.latitude = 0.0
        self.longitude = 0.0
        self.altitude = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(CommandTOL_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">ifffff", self.drone_id, self.min_pitch, self.yaw, self.latitude, self.longitude, self.altitude))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != CommandTOL_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return CommandTOL_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = CommandTOL_t()
        self.drone_id, self.min_pitch, self.yaw, self.latitude, self.longitude, self.altitude = struct.unpack(">ifffff", buf.read(24))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if CommandTOL_t in parents: return 0
        tmphash = (0xb72d1e9f0d2b773) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if CommandTOL_t._packed_fingerprint is None:
            CommandTOL_t._packed_fingerprint = struct.pack(">Q", CommandTOL_t._get_hash_recursive([]))
        return CommandTOL_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

