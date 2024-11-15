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

class Odometry_t(object):
    __slots__ = ["stamp", "frame_id", "pose", "velocity", "angular_velocity"]

    __typenames__ = ["Time_t", "string", "Pose_t", "float", "float"]

    __dimensions__ = [None, None, None, [3], [3]]

    def __init__(self):
        self.stamp = Time_t()
        self.frame_id = ""
        self.pose = Pose_t()
        self.velocity = [ 0.0 for dim0 in range(3) ]
        self.angular_velocity = [ 0.0 for dim0 in range(3) ]

    def encode(self):
        buf = BytesIO()
        buf.write(Odometry_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.stamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.stamp._encode_one(buf)
        __frame_id_encoded = self.frame_id.encode('utf-8')
        buf.write(struct.pack('>I', len(__frame_id_encoded)+1))
        buf.write(__frame_id_encoded)
        buf.write(b"\0")
        assert self.pose._get_packed_fingerprint() == Pose_t._get_packed_fingerprint()
        self.pose._encode_one(buf)
        buf.write(struct.pack('>3f', *self.velocity[:3]))
        buf.write(struct.pack('>3f', *self.angular_velocity[:3]))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != Odometry_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return Odometry_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = Odometry_t()
        self.stamp = Time_t._decode_one(buf)
        __frame_id_len = struct.unpack('>I', buf.read(4))[0]
        self.frame_id = buf.read(__frame_id_len)[:-1].decode('utf-8', 'replace')
        self.pose = Pose_t._decode_one(buf)
        self.velocity = struct.unpack('>3f', buf.read(12))
        self.angular_velocity = struct.unpack('>3f', buf.read(12))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if Odometry_t in parents: return 0
        newparents = parents + [Odometry_t]
        tmphash = (0xa62aacefbb44620a+ Time_t._get_hash_recursive(newparents)+ Pose_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if Odometry_t._packed_fingerprint is None:
            Odometry_t._packed_fingerprint = struct.pack(">Q", Odometry_t._get_hash_recursive([]))
        return Odometry_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

