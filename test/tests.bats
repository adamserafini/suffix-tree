#!/usr/bin/env bats

@test "invoking suffixtree with no arguments prints usage" {
  run ./suffixtree
  [ "$status" -eq 1 ]
  [ "$output" = "usage: suffixtree inputstring" ]
}

@test "invoking suffixtree with too many arguments prints usage" {
  run ./suffixtree too many
  [ "$status" -eq 1 ]
  [ "$output" = "usage: suffixtree inputstring" ]
}

@test "correct suffixtree for x" {
  ./suffixtree x | cmp - test/x.dot
}

@test "correct suffixtree for xa" {
  ./suffixtree xa | cmp - test/xa.dot
}

@test "correct suffixtree for xab" {
  ./suffixtree xab | cmp - test/xab.dot
}

@test "correct suffixtree for xabx" {
  ./suffixtree xabx | cmp - test/xabx.dot
}

@test "correct suffixtree for xabxa" {
  ./suffixtree xabxa | cmp - test/xabxa.dot
}

@test "correct suffixtree for xabxa$" {
  ./suffixtree xabxa$ | cmp - test/xabxa$.dot
}
