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

class DistributedSync_t(object):
    __slots__ = ["timestamp", "drone_id", "sync_signal", "solver_token"]

    __typenames__ = ["Time_t", "int32_t", "int32_t", "int64_t"]

    __dimensions__ = [None, None, None, None]

    def __init__(self):
        self.timestamp = Time_t()
        self.drone_id = 0
        self.sync_signal = 0
        self.solver_token = 0

    def encode(self):
        buf = BytesIO()
        buf.write(DistributedSync_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.timestamp._get_packed_fingerprint() == Time_t._get_packed_fingerprint()
        self.timestamp._encode_one(buf)
        buf.write(struct.pack(">iiq", self.drone_id, self.sync_signal, self.solver_token))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != DistributedSync_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return DistributedSync_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = DistributedSync_t()
        self.timestamp = Time_t._decode_one(buf)
        self.drone_id, self.sync_signal, self.solver_token = struct.unpack(">iiq", buf.read(16))
        return self
    _decode_one = staticmethod(_decode_one)

    def _get_hash_recursive(parents):
        if DistributedSync_t in parents: return 0
        newparents = parents + [DistributedSync_t]
        tmphash = (0x384b7d86de7f2b94+ Time_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff) + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if DistributedSync_t._packed_fingerprint is None:
            DistributedSync_t._packed_fingerprint = struct.pack(">Q", DistributedSync_t._get_hash_recursive([]))
        return DistributedSync_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

    def get_hash(self):
        """Get the LCM hash of the struct"""
        return struct.unpack(">Q", DistributedSync_t._get_packed_fingerprint())[0]
