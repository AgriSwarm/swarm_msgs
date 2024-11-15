"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import Vector_t

import Time_t

import Pose_t

class DistributedPGOData_t(object):
    __slots__ = ["timestamp", "drone_id", "target_id", "reference_frame_id", "type", "frame_num", "frame_ids", "frame_poses_num", "frame_poses", "frame_dual_num", "frame_duals", "solver_token", "iteration_count"]

    __typenames__ = ["Time_t", "int32_t", "int32_t", "int32_t", "int32_t", "int32_t", "int64_t", "int32_t", "Pose_t", "int32_t", "Vector_t", "int64_t", "int32_t"]

    __dimensions__ = [None, None, None, None, None, None, ["frame_num"], None, ["frame_poses_num"], None, ["frame_dual_num"], None, None]

    def __init__(self):
        self.timestamp = Time_t()
        self.drone_id = 0
        self.target_id = 0
        self.reference_frame_id = 0
        self.type = 0
        self.frame_num = 0
        self.frame_ids = []
        self.frame_poses_num = 0
        self.frame_poses = []
        self.frame_dual_num = 0
        self.frame_duals = []
        self.solver_token = 0
        self.iteration_count = 0

    def encode(self):
        buf = BytesIO()
        buf.write(DistributedPGOData_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.timestamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.timestamp._encode_one(buf)
        buf.write(struct.pack(">iiiii", self.drone_id, self.target_id, self.reference_frame_id, self.type, self.frame_num))
        buf.write(struct.pack('>%dq' % self.frame_num, *self.frame_ids[:self.frame_num]))
        buf.write(struct.pack(">i", self.frame_poses_num))
        for i0 in range(self.frame_poses_num):
            assert self.frame_poses[i0]._get_packed_fingerprint() == Pose_t._get_packed_fingerprint()
            self.frame_poses[i0]._encode_one(buf)
        buf.write(struct.pack(">i", self.frame_dual_num))
        for i0 in range(self.frame_dual_num):
            assert self.frame_duals[i0]._get_packed_fingerprint() == Vector_t._get_packed_fingerprint()
            self.frame_duals[i0]._encode_one(buf)
        buf.write(struct.pack(">qi", self.solver_token, self.iteration_count))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != DistributedPGOData_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return DistributedPGOData_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = DistributedPGOData_t()
        self.timestamp = Time_t._decode_one(buf)
        self.drone_id, self.target_id, self.reference_frame_id, self.type, self.frame_num = struct.unpack(">iiiii", buf.read(20))
        self.frame_ids = struct.unpack('>%dq' % self.frame_num, buf.read(self.frame_num * 8))
        self.frame_poses_num = struct.unpack(">i", buf.read(4))[0]
        self.frame_poses = []
        for i0 in range(self.frame_poses_num):
            self.frame_poses.append(Pose_t._decode_one(buf))
        self.frame_dual_num = struct.unpack(">i", buf.read(4))[0]
        self.frame_duals = []
        for i0 in range(self.frame_dual_num):
            self.frame_duals.append(Vector_t._decode_one(buf))
        self.solver_token, self.iteration_count = struct.unpack(">qi", buf.read(12))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if DistributedPGOData_t in parents: return 0
        newparents = parents + [DistributedPGOData_t]
        tmphash = (0xab518dbdad548fa0+ Time_t._get_hash_recursive(newparents)+ Pose_t._get_hash_recursive(newparents)+ Vector_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if DistributedPGOData_t._packed_fingerprint is None:
            DistributedPGOData_t._packed_fingerprint = struct.pack(">Q", DistributedPGOData_t._get_hash_recursive([]))
        return DistributedPGOData_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

