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

class PolynomialTrajectory(object):
    __slots__ = ["stamp", "trajectory_id", "action", "num_order", "num_segment", "num_coef", "start_yaw", "final_yaw", "coef_x", "coef_y", "coef_z", "time", "mag_coeff", "order", "debug_info"]

    __typenames__ = ["Time_t", "int32_t", "int32_t", "int32_t", "int32_t", "int32_t", "double", "double", "double", "double", "double", "double", "double", "int32_t", "string"]

    __dimensions__ = [None, None, None, None, None, None, None, None, ["num_coef"], ["num_coef"], ["num_coef"], ["num_segment"], None, ["num_segment"], None]

    ACTION_ADD = 1
    ACTION_ABORT = 2
    ACTION_WARN_START = 3
    ACTION_WARN_FINAL = 4
    ACTION_WARN_IMPOSSIBLE = 5

    def __init__(self):
        self.stamp = Time_t()
        self.trajectory_id = 0
        self.action = 0
        self.num_order = 0
        self.num_segment = 0
        self.num_coef = 0
        self.start_yaw = 0.0
        self.final_yaw = 0.0
        self.coef_x = []
        self.coef_y = []
        self.coef_z = []
        self.time = []
        self.mag_coeff = 0.0
        self.order = []
        self.debug_info = ""

    def encode(self):
        buf = BytesIO()
        buf.write(PolynomialTrajectory._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.stamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.stamp._encode_one(buf)
        buf.write(struct.pack(">iiiiidd", self.trajectory_id, self.action, self.num_order, self.num_segment, self.num_coef, self.start_yaw, self.final_yaw))
        buf.write(struct.pack('>%dd' % self.num_coef, *self.coef_x[:self.num_coef]))
        buf.write(struct.pack('>%dd' % self.num_coef, *self.coef_y[:self.num_coef]))
        buf.write(struct.pack('>%dd' % self.num_coef, *self.coef_z[:self.num_coef]))
        buf.write(struct.pack('>%dd' % self.num_segment, *self.time[:self.num_segment]))
        buf.write(struct.pack(">d", self.mag_coeff))
        buf.write(struct.pack('>%di' % self.num_segment, *self.order[:self.num_segment]))
        __debug_info_encoded = self.debug_info.encode('utf-8')
        buf.write(struct.pack('>I', len(__debug_info_encoded)+1))
        buf.write(__debug_info_encoded)
        buf.write(b"\0")

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != PolynomialTrajectory._get_packed_fingerprint():
            raise ValueError("Decode error")
        return PolynomialTrajectory._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = PolynomialTrajectory()
        self.stamp = Time_t._decode_one(buf)
        self.trajectory_id, self.action, self.num_order, self.num_segment, self.num_coef, self.start_yaw, self.final_yaw = struct.unpack(">iiiiidd", buf.read(36))
        self.coef_x = struct.unpack('>%dd' % self.num_coef, buf.read(self.num_coef * 8))
        self.coef_y = struct.unpack('>%dd' % self.num_coef, buf.read(self.num_coef * 8))
        self.coef_z = struct.unpack('>%dd' % self.num_coef, buf.read(self.num_coef * 8))
        self.time = struct.unpack('>%dd' % self.num_segment, buf.read(self.num_segment * 8))
        self.mag_coeff = struct.unpack(">d", buf.read(8))[0]
        self.order = struct.unpack('>%di' % self.num_segment, buf.read(self.num_segment * 4))
        __debug_info_len = struct.unpack('>I', buf.read(4))[0]
        self.debug_info = buf.read(__debug_info_len)[:-1].decode('utf-8', 'replace')
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if PolynomialTrajectory in parents: return 0
        newparents = parents + [PolynomialTrajectory]
        tmphash = (0x64a23b23437f564a+ Time_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if PolynomialTrajectory._packed_fingerprint is None:
            PolynomialTrajectory._packed_fingerprint = struct.pack(">Q", PolynomialTrajectory._get_hash_recursive([]))
        return PolynomialTrajectory._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

