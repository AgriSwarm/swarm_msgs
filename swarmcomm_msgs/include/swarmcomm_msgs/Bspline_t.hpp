/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __Bspline_t_hpp__
#define __Bspline_t_hpp__

#include <lcm/lcm_coretypes.h>

#include <vector>


class Bspline_t
{
    public:
        int32_t    start_time_sec;

        int32_t    start_time_nsec;

        int32_t    drone_id;

        int32_t    order;

        int64_t    traj_id;

        int32_t    knots_num;

        std::vector< float > knots;

        int32_t    pos_pts_num;

        std::vector< float > pos_pts_x;

        std::vector< float > pos_pts_y;

        std::vector< float > pos_pts_z;

        int32_t    yaw_pts_num;

        std::vector< float > yaw_pts;

        float      yaw_dt;

        int32_t    msg_id;

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to read while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "Bspline_t"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int Bspline_t::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int Bspline_t::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int Bspline_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t Bspline_t::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* Bspline_t::getTypeName()
{
    return "Bspline_t";
}

int Bspline_t::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->start_time_sec, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->start_time_nsec, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->drone_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->order, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &this->traj_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->knots_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->knots_num > 0) {
        tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->knots[0], this->knots_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->pos_pts_num > 0) {
        tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_x[0], this->pos_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->pos_pts_num > 0) {
        tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_y[0], this->pos_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->pos_pts_num > 0) {
        tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_z[0], this->pos_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->yaw_pts_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->yaw_pts_num > 0) {
        tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->yaw_pts[0], this->yaw_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->yaw_dt, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->msg_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int Bspline_t::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->start_time_sec, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->start_time_nsec, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->drone_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->order, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this->traj_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->knots_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->knots_num) {
        this->knots.resize(this->knots_num);
        tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->knots[0], this->knots_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->pos_pts_num) {
        this->pos_pts_x.resize(this->pos_pts_num);
        tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_x[0], this->pos_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->pos_pts_num) {
        this->pos_pts_y.resize(this->pos_pts_num);
        tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_y[0], this->pos_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->pos_pts_num) {
        this->pos_pts_z.resize(this->pos_pts_num);
        tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->pos_pts_z[0], this->pos_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->yaw_pts_num, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->yaw_pts_num) {
        this->yaw_pts.resize(this->yaw_pts_num);
        tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->yaw_pts[0], this->yaw_pts_num);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->yaw_dt, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->msg_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int Bspline_t::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int64_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __float_encoded_array_size(NULL, this->knots_num);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __float_encoded_array_size(NULL, this->pos_pts_num);
    enc_size += __float_encoded_array_size(NULL, this->pos_pts_num);
    enc_size += __float_encoded_array_size(NULL, this->pos_pts_num);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __float_encoded_array_size(NULL, this->yaw_pts_num);
    enc_size += __float_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    return enc_size;
}

uint64_t Bspline_t::_computeHash(const __lcm_hash_ptr *)
{
    uint64_t hash = 0xf7ae2655d320e128LL;
    return (hash<<1) + ((hash>>63)&1);
}

#endif
