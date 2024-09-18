#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <cassert>
#ifndef __M_BUFF_H__
#define __M_BUFF_H__
// 缓冲区类
namespace log
{

#define BUFFER_DEFAULT_SIZE (1 * 1024 * 1024)
#define BUFFER_INCREMENT_SIZE (1 * 1024 * 1024)
#define BUFFER_THRESHOLD_SIZE (10 * 1024 * 1024)
    class Buffer
    {
    public:
        Buffer()
            : _read_idx(0),
              _write_idx(0),
              _v(BUFFER_DEFAULT_SIZE) {}
        bool empty()
        {
            return _read_idx == _write_idx;
        }

        size_t readAbleSize()
        {
            return _write_idx - _read_idx;
        }

        size_t writeAbleSize()
        {
            return _v.size() - _write_idx;
        }

        void reset()
        {
            _read_idx = _write_idx = 0;
        }

        void swap(Buffer &buf)
        {
            _v.swap(buf._v);
            std::swap(_read_idx, buf._read_idx);
            std::swap(_write_idx, buf._write_idx);
        }

        void push(const char *data, size_t len)
        {
            assert(len <= writeAbleSize());
            ensureEnoughSpace(len);
            std::copy(data, data + len, &_v[_write_idx]);
            _write_idx += len;
        }

        const char *begin()
        {
            return &_v[_read_idx];
        }

        void pop(size_t len)
        {
            _read_idx += len;
            assert(_read_idx <= _write_idx);
        }

    protected:
        void ensureEnoughSpace(size_t len)
        {
            if (len <= writeAbleSize())
                return;
            size_t new_capacity;
            if (_v.size() < BUFFER_THRESHOLD_SIZE)
            {
                new_capacity = _v.size() * 2 + len;
            }
            else
            {
                new_capacity = _v.size() + BUFFER_INCREMENT_SIZE + len;
            }
            _v.resize(new_capacity);
        }

    private:
        size_t _read_idx;
        size_t _write_idx;
        std::vector<char> _v;
    };
}
#endif