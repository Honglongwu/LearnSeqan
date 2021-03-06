// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2013 NVIDIA Corporation
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of NVIDIA Corporation nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: David Weese <david.weese@fu-berlin.de>
// ==========================================================================

#ifndef SEQAN_EXTRAS_SEQUENCE_ITERATOR_RANGE_H
#define SEQAN_EXTRAS_SEQUENCE_ITERATOR_RANGE_H

namespace seqan {

// ============================================================================
// Forwards
// ============================================================================

template <typename TInput, typename TPipeSpec>
struct Pipe;

// ============================================================================
// Tags, Classes, Enums
// ============================================================================

// ----------------------------------------------------------------------------
// class Range
// ----------------------------------------------------------------------------

template <typename TIterator>
class Range
{
public:

    TIterator _begin;
    TIterator _end;

    // ------------------------------------------------------------------------
    // Range Constructors
    // ------------------------------------------------------------------------

    SEQAN_HOST_DEVICE inline
    Range():
        _begin(),
        _end()
    {}

    template <typename TOtherContainer>
    SEQAN_HOST_DEVICE inline
    Range(TOtherContainer & cont):
        _begin(begin(cont, Standard())),
        _end(end(cont, Standard()))
    {}

    template <typename TOtherContainer>
    SEQAN_HOST_DEVICE inline
    Range(TOtherContainer const & cont):
        _begin(begin(cont, Standard())),
        _end(end(cont, Standard()))
    {}

    SEQAN_HOST_DEVICE inline
    Range(TIterator const & begin, TIterator const & end):
        _begin(begin),
        _end(end)
    {}

    // ------------------------------------------------------------------------
    // Operator =
    // ------------------------------------------------------------------------

    template <typename TOtherContainer>
    SEQAN_HOST_DEVICE inline
    Range &
    operator= (TOtherContainer &other)
    {
        assign(*this, other);
        return *this;
    }

    // ------------------------------------------------------------------------
    // Operator []
    // ------------------------------------------------------------------------

    template <typename TPos>
    SEQAN_HOST_DEVICE inline
    typename Reference<Range>::Type
    operator[] (TPos pos)
    {
        return value(*this, pos);
    }

    template <typename TPos>
    SEQAN_HOST_DEVICE inline
    typename GetValue<Range>::Type
    operator[] (TPos pos) const
    {
        return getValue(*this, pos);
    }
};

// ============================================================================
// Metafunctions
// ============================================================================

// ----------------------------------------------------------------------------
// Metafunction IsView
// ----------------------------------------------------------------------------

template <typename TIterator>
struct IsView<Range<TIterator> > : True {};

// ----------------------------------------------------------------------------
// Metafunction Value
// ----------------------------------------------------------------------------

template <typename TIterator>
struct Value<Range<TIterator> >:
    Value<TIterator> {};

template <typename TIterator>
struct Value<Range<TIterator> const>:
    Value<TIterator> {};

// ----------------------------------------------------------------------------
// Metafunction GetValue
// ----------------------------------------------------------------------------

template <typename TIterator>
struct GetValue<Range<TIterator> >:
    GetValue<TIterator> {};

template <typename TIterator>
struct GetValue<Range<TIterator> const>:
    GetValue<TIterator const> {};

// ----------------------------------------------------------------------------
// Metafunction Reference
// ----------------------------------------------------------------------------

template <typename TIterator>
struct Reference<Range<TIterator> >:
    Reference<TIterator> {};

template <typename TIterator>
struct Reference<Range<TIterator> const>:
    Reference<TIterator const> {};

// ----------------------------------------------------------------------------
// Metafunction Iterator
// ----------------------------------------------------------------------------

template <typename TIterator>
struct Iterator<Range<TIterator>, Standard>
{
    typedef TIterator Type;
};

template <typename TIterator>
struct Iterator<Range<TIterator> const, Standard>
{
    typedef TIterator Type;
};

//template <typename TIterator>
//struct Iterator<Range<TIterator> const>: public Iterator<Range<TIterator> > {};

// ----------------------------------------------------------------------------
// Metafunction Difference
// ----------------------------------------------------------------------------

template <typename TIterator>
struct Difference<Range<TIterator> >
{
    typedef typename Difference<TIterator>::Type Type;
};

template <typename TIterator>
struct Size<Range<TIterator> >
{
    typedef typename Difference<TIterator>::Type        TDifference;
    typedef typename MakeUnsigned<TDifference>::Type    Type;
};

// ============================================================================
// Functions
// ============================================================================

// ----------------------------------------------------------------------------
// begin()
// ----------------------------------------------------------------------------

template <typename TIterator>
SEQAN_HOST_DEVICE inline typename Iterator<Range<TIterator>, Standard>::Type
begin(Range<TIterator> & view, Standard)
{
    return view._begin;
}

template <typename TIterator>
SEQAN_HOST_DEVICE inline typename Iterator<Range<TIterator>, Standard>::Type
begin(Range<TIterator> const & view, Standard)
{
    return view._begin;
}

// ----------------------------------------------------------------------------
// end()
// ----------------------------------------------------------------------------

template <typename TIterator>
SEQAN_HOST_DEVICE inline typename Iterator<Range<TIterator>, Standard>::Type
end(Range<TIterator> & view, Standard)
{
    return view._end;
}

template <typename TIterator>
SEQAN_HOST_DEVICE inline typename Iterator<Range<TIterator>, Standard>::Type
end(Range<TIterator> const & view, Standard)
{
    return view._end;
}

// ----------------------------------------------------------------------------
// value()
// ----------------------------------------------------------------------------

template <typename TIterator, typename TPos>
SEQAN_HOST_DEVICE inline typename Reference<Range<TIterator> >::Type
value(Range<TIterator> & view, TPos pos)
{
    return *(view._begin + pos);
}

template <typename TIterator, typename TPos>
SEQAN_HOST_DEVICE inline typename Reference<Range<TIterator> const>::Type
value(Range<TIterator> const & view, TPos pos)
{
    return *(view._begin + pos);
}

// ----------------------------------------------------------------------------
// length()
// ----------------------------------------------------------------------------

template <typename TIterator>
SEQAN_HOST_DEVICE inline typename Difference<Range<TIterator> >::Type
length(Range<TIterator> const & view)
{
    return view._end - view._begin;
}

// ----------------------------------------------------------------------------
// resize()
// ----------------------------------------------------------------------------

// this function doesn't do anything as we are not allowed to change the host (only its elements)
// it is, however, implemented for algorithms that get a sequence to work on
// and need to make sure that it has a certain length

template <typename TIterator, typename TSize, typename TExpand>
SEQAN_HOST_DEVICE inline typename Size< Range<TIterator> >::Type
resize(
    Range<TIterator> & me,
    TSize new_length,
    Tag<TExpand>)
{
    ignoreUnusedVariableWarning(new_length);

    SEQAN_ASSERT_EQ(new_length, (TSize)length(me));
    return length(me);
}

// ----------------------------------------------------------------------------
// assign()
// ----------------------------------------------------------------------------

template <typename TIterator, typename TContainer>
SEQAN_HOST_DEVICE inline void
assign(Range<TIterator> &view, TContainer &cont)
{
    view._begin = begin(cont, Standard());
    view._end = end(cont, Standard());
}

// ----------------------------------------------------------------------------
// operator<<
// ----------------------------------------------------------------------------

template <typename TStream, typename TIterator>
inline TStream &
operator<<(TStream & target,
           Range<TIterator> const & source)
{
    write(target, source);
    return target;
}

// ----------------------------------------------------------------------------
// toRange()
// ----------------------------------------------------------------------------

template <typename TIterator>
SEQAN_HOST_DEVICE inline
Range<TIterator>
toRange(TIterator const &begin, TIterator const &end)
{
    return Range<TIterator>(begin, end);
}

// ----------------------------------------------------------------------------
// pipe interface
// ----------------------------------------------------------------------------

template < typename TIterator,
           typename TInput,
           typename TPipeSpec >
inline void assign(Range<TIterator> &dest, Pipe<TInput, TPipeSpec> &src)
{
    typedef typename Iterator<Range<TIterator>, Standard>::Type TDestIter;
    resize(dest, length(src));
    beginRead(src);
    for (TDestIter _cur = begin(dest, Standard()), _end = end(dest, Standard()); _cur != _end; ++_cur, ++src)
        *_cur = *src;
    endRead(src);
}

template < typename TIterator,
           typename TInput,
           typename TPipeSpec >
inline void operator << (Range<TIterator> &dest, Pipe<TInput, TPipeSpec> &src)
{
    assign(dest, src);
}

}  // namespace seqan

#endif  // #ifndef SEQAN_EXTRAS_SEQUENCE_ITERATOR_RANGE_H
