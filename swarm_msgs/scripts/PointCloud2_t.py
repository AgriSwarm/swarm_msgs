"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import PointField_t

import Time_t

class PointCloud2_t(object):
    __slots__ = ["stamp", "frame_id", "drone_id", "height", "width", "field_num", "fields", "is_bigendian", "is_dense", "point_step", "row_step", "point_num", "data"]

    __typenames__ = ["Time_t", "string", "int32_t", "int32_t", "int32_t", "int32_t", "PointField_t", "boolean", "boolean", "int32_t", "int32_t", "int32_t", "int8_t"]

    __dimensions__ = [None, None, None, None, None, None, ["field_num"], None, None, None, None, None, ["point_num"]]

    def __init__(self):
        self.stamp = Time_t()
        self.frame_id = ""
        self.drone_id = 0
        self.height = 0
        self.width = 0
        self.field_num = 0
        self.fields = []
        self.is_bigendian = False
        self.is_dense = False
        self.point_step = 0
        self.row_step = 0
        self.point_num = 0
        self.data = []

    def encode(self):
        buf = BytesIO()
        buf.write(PointCloud2_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.stamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.stamp._encode_one(buf)
        __frame_id_encoded = self.frame_id.encode('utf-8')
        buf.write(struct.pack('>I', len(__frame_id_encoded)+1))
        buf.write(__frame_id_encoded)
        buf.write(b"\0")
        buf.write(struct.pack(">iiii", self.drone_id, self.height, self.width, self.field_num))
        for i0 in range(self.field_num):
            assert self.fields[i0]._get_packed_fingerprint() == PointField_t._get_packed_fingerprint()
            self.fields[i0]._encode_one(buf)
        buf.write(struct.pack(">bbiii", self.is_bigendian, self.is_dense, self.point_step, self.row_step, self.point_num))
        buf.write(struct.pack('>%db' % self.point_num, *self.data[:self.point_num]))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != PointCloud2_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return PointCloud2_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = PointCloud2_t()
        self.stamp = Time_t._decode_one(buf)
        __frame_id_len = struct.unpack('>I', buf.read(4))[0]
        self.frame_id = buf.read(__frame_id_len)[:-1].decode('utf-8', 'replace')
        self.drone_id, self.height, self.width, self.field_num = struct.unpack(">iiii", buf.read(16))
        self.fields = []
        for i0 in range(self.field_num):
            self.fields.append(PointField_t._decode_one(buf))
        self.is_bigendian = bool(struct.unpack('b', buf.read(1))[0])
        self.is_dense = bool(struct.unpack('b', buf.read(1))[0])
        self.point_step, self.row_step, self.point_num = struct.unpack(">iii", buf.read(12))
        self.data = struct.unpack('>%db' % self.point_num, buf.read(self.point_num))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if PointCloud2_t in parents: return 0
        newparents = parents + [PointCloud2_t]
        tmphash = (0x12d08d3d4f359807+ Time_t._get_hash_recursive(newparents)+ PointField_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if PointCloud2_t._packed_fingerprint is None:
            PointCloud2_t._packed_fingerprint = struct.pack(">Q", PointCloud2_t._get_hash_recursive([]))
        return PointCloud2_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

