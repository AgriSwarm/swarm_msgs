/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __PolynomialTrajectory_t_hpp__
#define __PolynomialTrajectory_t_hpp__

#include <lcm/lcm_coretypes.h>

#include <vector>
#include <string>
#include "Time_t.hpp"


class PolynomialTrajectory_t
{
    public:
        Time_t     stamp;

        int32_t    drone_id;

        int32_t    trajectory_id;

        int32_t    action;

        /// trajectory parameters
        int32_t    num_order;

        int32_t    num_segment;

        int32_t    num_coef;

        /// trajectory coefficients
        double     start_yaw;

        double     final_yaw;

        std::vector< double > coef_x;

        std::vector< double > coef_y;

        std::vector< double > coef_z;

        std::vector< double > time;

        double     mag_coeff;

        std::vector< int32_t > order;

        std::string debug_info;

    public:
        /// action commands
        enum { ACTION_ADD = 1 };
        enum { ACTION_ABORT = 2 };
        enum { ACTION_WARN_START = 3 };
        enum { ACTION_WARN_FINAL = 4 };
        enum { ACTION_WARN_IMPOSSIBLE = 5 };

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
         * Returns "PolynomialTrajectory_t"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int PolynomialTrajectory_t::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int PolynomialTrajectory_t::decode(const void *buf, int offset, int maxlen)
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

int PolynomialTrajectory_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t PolynomialTrajectory_t::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* PolynomialTrajectory_t::getTypeName()
{
    return "PolynomialTrajectory_t";
}

int PolynomialTrajectory_t::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = this->stamp._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->drone_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->trajectory_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->action, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->num_order, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->num_segment, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->num_coef, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->start_yaw, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->final_yaw, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->num_coef > 0) {
        tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->coef_x[0], this->num_coef);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_coef > 0) {
        tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->coef_y[0], this->num_coef);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_coef > 0) {
        tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->coef_z[0], this->num_coef);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_segment > 0) {
        tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->time[0], this->num_segment);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->mag_coeff, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->num_segment > 0) {
        tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->order[0], this->num_segment);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    char* debug_info_cstr = const_cast<char*>(this->debug_info.c_str());
    tlen = __string_encode_array(
        buf, offset + pos, maxlen - pos, &debug_info_cstr, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int PolynomialTrajectory_t::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = this->stamp._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->drone_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->trajectory_id, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->action, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->num_order, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->num_segment, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->num_coef, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->start_yaw, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->final_yaw, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->num_coef) {
        this->coef_x.resize(this->num_coef);
        tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->coef_x[0], this->num_coef);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_coef) {
        this->coef_y.resize(this->num_coef);
        tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->coef_y[0], this->num_coef);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_coef) {
        this->coef_z.resize(this->num_coef);
        tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->coef_z[0], this->num_coef);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_segment) {
        this->time.resize(this->num_segment);
        tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->time[0], this->num_segment);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->mag_coeff, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->num_segment) {
        this->order.resize(this->num_segment);
        tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->order[0], this->num_segment);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    int32_t __debug_info_len__;
    tlen = __int32_t_decode_array(
        buf, offset + pos, maxlen - pos, &__debug_info_len__, 1);
    if(tlen < 0) return tlen; else pos += tlen;
    if(__debug_info_len__ > maxlen - pos) return -1;
    this->debug_info.assign(
        static_cast<const char*>(buf) + offset + pos, __debug_info_len__ - 1);
    pos += __debug_info_len__;

    return pos;
}

int PolynomialTrajectory_t::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += this->stamp._getEncodedSizeNoHash();
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, this->num_coef);
    enc_size += __double_encoded_array_size(NULL, this->num_coef);
    enc_size += __double_encoded_array_size(NULL, this->num_coef);
    enc_size += __double_encoded_array_size(NULL, this->num_segment);
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, this->num_segment);
    enc_size += this->debug_info.size() + 4 + 1;
    return enc_size;
}

uint64_t PolynomialTrajectory_t::_computeHash(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for(fp = p; fp != NULL; fp = fp->parent)
        if(fp->v == PolynomialTrajectory_t::getHash)
            return 0;
    const __lcm_hash_ptr cp = { p, PolynomialTrajectory_t::getHash };

    uint64_t hash = 0xec916416b66625fdLL +
         Time_t::_computeHash(&cp);

    return (hash<<1) + ((hash>>63)&1);
}

#endif
