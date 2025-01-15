#ifndef _VVSEC_PARSER_HPP_
#define _VVSEC_PARSER_HPP_

#include <concepts>
#include <type_traits>

namespace vvsec {

template <class T>
concept TidKind = requires { T::unknown; };

template <class T, class SymT, class TidT>
concept TidMatcherKind = TidKind<TidT> and requires(SymT sym, TidT tid, T x) {
  { x(sym, tid) } -> std::same_as<bool>;
};

template <class T, class SymT>
concept SymProviderKind = requires(T x) {
  { x() } -> std::same_as<SymT>;
};

template <class T, class SymT, class... TidTs>
concept UnexpectedSymHandlerKind = requires(T x, SymT sym, TidTs... tids) {
  { x(sym, tids...) };
};

template <TidKind TidT>
struct MaybeTid final {
  TidT tid;
  bool nothing;

  operator bool() const {
    return not nothing;
  }
};

namespace detail {
template <class HeadT, class... TailTs>
concept same = (std::is_same_v<HeadT, TailTs> and ...);
}

// clang-format off
template <
    class TidT,
    class SymT,
    SymProviderKind<SymT> SymProviderT,
    TidMatcherKind<SymT, TidT> TidMatcherT,
    class UnexpectedSymHandlerT
>
// clang-format on
class Parser {
 private:
  SymT _first_sym;
  SymT _follow_sym;

  SymProviderT _sym_provider;
  TidMatcherT _tid_matcher;
  UnexpectedSymHandlerT _unexpected_sym_handler;

  void _next() {
    _first_sym = _follow_sym;
    _follow_sym = _sym_provider();
  }

 public:
  // clang-format off
  Parser(
      SymProviderT provider, TidMatcherT matcher,
      UnexpectedSymHandlerT unexpected_sym_handler
  )  // clang-format on
      : _first_sym()
      , _follow_sym()
      , _sym_provider(provider)
      , _tid_matcher(matcher)
      , _unexpected_sym_handler(unexpected_sym_handler) {}

  SymT first_sym() const {
    return _first_sym;
  }

  SymT follow_sym() const {
    return _follow_sym;
  }

 protected:
  template <class... TidTs>
    requires detail::same<TidT, TidTs...>
  MaybeTid<TidT> accept(TidTs... tids) {
    auto mtid = MaybeTid<TidT>{TidT::unknown, true};

    ((_tid_matcher(_follow_sym, tids) ? (mtid.tid = tids, mtid.nothing = false) : true)
        and ...);

    return mtid;
  }

  template <class... TidTs>
    requires(detail::same<TidT, TidTs...>
             and UnexpectedSymHandlerKind<UnexpectedSymHandlerT, SymT, TidTs...>)
  MaybeTid<TidT> expect(TidTs... tids) {
    auto mtid = accept(tids...);
    if (not mtid) _unexpected_sym_handler(_follow_sym, tids...);
    return mtid;
  }
};

}  // namespace vvsec

#endif  // _VVSEC_PARSER_HPP_
