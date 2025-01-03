"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import ImageDescriptor_t

import IMUData_t

import Point3f_t

import Time_t

import Pose_t

import SlidingWindow_t

class ImageArrayDescriptor_t(object):
    __slots__ = ["msg_id", "frame_id", "matched_frame", "matched_drone", "image_num", "reference_frame_id", "prevent_adding_db", "landmark_num", "drone_id", "is_lazy_frame", "timestamp", "pose_drone", "is_keyframe", "images", "imu_buf_size", "imu_buf", "Ba", "Bg", "sld_win_status", "cur_td"]

    __typenames__ = ["int64_t", "int64_t", "int64_t", "int32_t", "int32_t", "int32_t", "boolean", "int32_t", "int32_t", "int32_t", "Time_t", "Pose_t", "boolean", "ImageDescriptor_t", "int32_t", "IMUData_t", "Point3f_t", "Point3f_t", "SlidingWindow_t", "float"]

    __dimensions__ = [None, None, None, None, None, None, None, None, None, None, None, None, None, ["image_num"], None, ["imu_buf_size"], None, None, None, None]

    def __init__(self):
        self.msg_id = 0
        self.frame_id = 0
        self.matched_frame = 0
        self.matched_drone = 0
        self.image_num = 0
        self.reference_frame_id = 0
        self.prevent_adding_db = False
        self.landmark_num = 0
        self.drone_id = 0
        self.is_lazy_frame = 0
        self.timestamp = Time_t()
        self.pose_drone = Pose_t()
        self.is_keyframe = False
        self.images = []
        self.imu_buf_size = 0
        self.imu_buf = []
        self.Ba = Point3f_t()
        self.Bg = Point3f_t()
        self.sld_win_status = SlidingWindow_t()
        self.cur_td = 0.0

    def encode(self):
        buf = BytesIO()
        buf.write(ImageArrayDescriptor_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qqqiiibiii", self.msg_id, self.frame_id, self.matched_frame, self.matched_drone, self.image_num, self.reference_frame_id, self.prevent_adding_db, self.landmark_num, self.drone_id, self.is_lazy_frame))
        assert self.timestamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.timestamp._encode_one(buf)
        assert self.pose_drone._get_packed_fingerprint() == Pose_t._get_packed_fingerprint()
        self.pose_drone._encode_one(buf)
        buf.write(struct.pack(">b", self.is_keyframe))
        for i0 in range(self.image_num):
            assert self.images[i0]._get_packed_fingerprint() == ImageDescriptor_t._get_packed_fingerprint()
            self.images[i0]._encode_one(buf)
        buf.write(struct.pack(">i", self.imu_buf_size))
        for i0 in range(self.imu_buf_size):
            assert self.imu_buf[i0]._get_packed_fingerprint() == IMUData_t._get_packed_fingerprint()
            self.imu_buf[i0]._encode_one(buf)
        assert self.Ba._get_packed_fingerprint() == Point3f_t._get_packed_fingerprint()
        self.Ba._encode_one(buf)
        assert self.Bg._get_packed_fingerprint() == Point3f_t._get_packed_fingerprint()
        self.Bg._encode_one(buf)
        assert self.sld_win_status._get_packed_fingerprint() == SlidingWindow_t._get_packed_fingerprint()
        self.sld_win_status._encode_one(buf)
        buf.write(struct.pack(">f", self.cur_td))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != ImageArrayDescriptor_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return ImageArrayDescriptor_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = ImageArrayDescriptor_t()
        self.msg_id, self.frame_id, self.matched_frame, self.matched_drone, self.image_num, self.reference_frame_id = struct.unpack(">qqqiii", buf.read(36))
        self.prevent_adding_db = bool(struct.unpack('b', buf.read(1))[0])
        self.landmark_num, self.drone_id, self.is_lazy_frame = struct.unpack(">iii", buf.read(12))
        self.timestamp = Time_t._decode_one(buf)
        self.pose_drone = Pose_t._decode_one(buf)
        self.is_keyframe = bool(struct.unpack('b', buf.read(1))[0])
        self.images = []
        for i0 in range(self.image_num):
            self.images.append(ImageDescriptor_t._decode_one(buf))
        self.imu_buf_size = struct.unpack(">i", buf.read(4))[0]
        self.imu_buf = []
        for i0 in range(self.imu_buf_size):
            self.imu_buf.append(IMUData_t._decode_one(buf))
        self.Ba = Point3f_t._decode_one(buf)
        self.Bg = Point3f_t._decode_one(buf)
        self.sld_win_status = SlidingWindow_t._decode_one(buf)
        self.cur_td = struct.unpack(">f", buf.read(4))[0]
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if ImageArrayDescriptor_t in parents: return 0
        newparents = parents + [ImageArrayDescriptor_t]
        tmphash = (0xf3adad9f3e1acdc0+ Time_t._get_hash_recursive(newparents)+ Pose_t._get_hash_recursive(newparents)+ ImageDescriptor_t._get_hash_recursive(newparents)+ IMUData_t._get_hash_recursive(newparents)+ Point3f_t._get_hash_recursive(newparents)+ Point3f_t._get_hash_recursive(newparents)+ SlidingWindow_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if ImageArrayDescriptor_t._packed_fingerprint is None:
            ImageArrayDescriptor_t._packed_fingerprint = struct.pack(">Q", ImageArrayDescriptor_t._get_hash_recursive([]))
        return ImageArrayDescriptor_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

