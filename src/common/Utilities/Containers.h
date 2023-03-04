/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WARHEAD_CONTAINERS_H
#define WARHEAD_CONTAINERS_H

#include "Define.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace Warhead
{
    template<class T>
    constexpr inline T* AddressOrSelf(T* ptr)
    {
        return ptr;
    }

    template<class T>
    [[maybe_unused]] constexpr inline T* AddressOrSelf(T& not_ptr)
    {
        return std::addressof(not_ptr);
    }

    template <class T>
    class CheckedBufferOutputIterator
    {
    public:
        using value_type = void;

        CheckedBufferOutputIterator(T* buf, size_t n) : _buf(buf), _end(buf + n) {}

        T& operator*() const { check(); return *_buf; }
        CheckedBufferOutputIterator& operator++() { check(); ++_buf; return *this; }
        CheckedBufferOutputIterator operator++(int) { CheckedBufferOutputIterator v = *this; operator++(); return v; }

        [[nodiscard]] size_t remaining() const { return (_end - _buf); }

    private:
        T* _buf;
        T* _end;

        void check() const
        {
            if (_buf >= _end)
            {
                throw std::out_of_range("index");
            }
        }
    };
}

namespace Warhead::Containers
{
    /*
     * Returns a pointer to mapped value (or the value itself if map stores pointers)
     */
    template<class M>
    inline auto MapGetValuePtr(M& map, typename M::key_type const& key) -> decltype(AddressOrSelf(map.find(key)->second))
    {
        auto itr = map.find(key);
        return itr != map.end() ? AddressOrSelf(itr->second) : nullptr;
    }
}

#endif //! #ifdef WARHEAD_CONTAINERS_H
