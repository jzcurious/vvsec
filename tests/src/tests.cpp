#include <format>
#include <gtest/gtest.h>
#include <txt2tok/scanner.hpp>
#include <txt2tok/stbuilder.hpp>
#include <txt2tok/token.hpp>
#include <vvsec/parser.hpp>

static const char* src_path = "../../assets/tests.udl";

enum Tid : std::size_t {
  indent,
  space,
  type_kw,
  var_kw,
  const_kw,
  struct_kw,
  func_kw,
  ret_kw,
  type_id,
  join,
  inst_id,
  assign,
  str_lit,
  num_lit,
  semicolon,
  plus,
  minus,
  mul,
  divide,
  lpar,
  rpar,
  lbracket,
  rbracket,
  lbrace,
  rbrace,
  langle,
  rangle,
  colon,
  comma,
  line_comment,
  block_comment,
  unknown,
};

// clang-format off
static auto table = t2t::ScanTableBuilder<Tid>{}
  .bind_token(Tid::indent,        R"(^    |\t)",            R"(indent)"             )
  .bind_token(Tid::space,         R"(^ )",                  R"(space)"              )
  .bind_token(Tid::type_kw,       R"(^type)",               R"("type")"             )
  .bind_token(Tid::var_kw,        R"(^var)",                R"("var")"              )
  .bind_token(Tid::const_kw,      R"(^const)",              R"("const")"            )
  .bind_token(Tid::struct_kw,     R"(^struct)",             R"("struct")"           )
  .bind_token(Tid::func_kw,       R"(^func)",               R"("func")"             )
  .bind_token(Tid::ret_kw,        R"(^ret)",                R"("ret")"              )
  .bind_token(Tid::type_id,       R"(^[A-Z][A-Za-z0-9_]*)", R"(type identifier)"    )
  .bind_token(Tid::join,          R"(^\|)",                 R"("|")"                )
  .bind_token(Tid::inst_id,       R"(^[a-z][a-z0-9_]*)",    R"(instance identifier)")
  .bind_token(Tid::assign,        R"(^=)",                  R"("=")"                )
  .bind_token(Tid::str_lit,       R"(^\"([^\"\n]|\.)*\")",  R"(string literal)"     )
  .bind_token(Tid::num_lit,       R"(^[0-9]+(\.[0-9]+)?)",  R"(number literal)"     )
  .bind_token(Tid::semicolon,     R"(^;)",                  R"(";")"                )
  .bind_token(Tid::plus,          R"(^\+)",                 R"("+")"                )
  .bind_token(Tid::minus,         R"(^\-)",                 R"("-")"                )
  .bind_token(Tid::mul,           R"(^\*)",                 R"("*")"                )
  .bind_token(Tid::divide,        R"(^/)",                  R"("/")"                )
  .bind_token(Tid::lpar,          R"(^\()",                 R"("(")"                )
  .bind_token(Tid::rpar,          R"(^\))",                 R".()")."               )
  .bind_token(Tid::lbracket,      R"(^\[)",                 R"("[")"                )
  .bind_token(Tid::rbracket,      R"(^\])",                 R"("]")"                )
  .bind_token(Tid::lbrace,        R"(^\{)",                 R"("{")"                )
  .bind_token(Tid::rbrace,        R"(^\})",                 R"("}")"                )
  .bind_token(Tid::langle,        R"(^<)",                  R"("<")"                )
  .bind_token(Tid::rangle,        R"(^>)",                  R"(">")"                )
  .bind_token(Tid::colon,         R"(^:)",                  R"(":")"                )
  .bind_token(Tid::comma,         R"(^,)",                  R"(",")"                )
  .bind_token(Tid::line_comment,  R"(^//.*$)",              R"(line comment)"       )
  .bind_token(Tid::block_comment, R"(^/\*(.|\s)*\*/)",      R"(block comment)"      )
  .build();
// clang-format on

TEST(Parser, ctor) {
  auto reader = t2t::SourceReader(src_path);
  auto scanner = t2t::Scanner(table);

  using Sym = t2t::MaybeAnchoredToken;

  auto next_sym = [&scanner, &reader]() {
    return scanner.scan(reader);
  };

  auto unexp_sym_handler = []<t2t::TidKind... TidTs>(const Sym& sym, TidTs... tids) {
    std::cout << std::format("Unexpected symbol {}\n", sym.val);
  };

  auto parser = vvsec::Parser<Tid, decltype(next_sym), decltype(unexp_sym_handler)>(
      next_sym, unexp_sym_handler);
}
