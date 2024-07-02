#include "regression_testfixture"

// TODO: introduce timeout feature to fail tests that take too long.

// Bug853879 - Infinite loop in function parse_cueparams()
// (https://bugzilla.mozilla.org/show_bug.cgi?id=853879)
//
// File contains syntax errors, but should parse successfully due to not
// aborting on errors.
TEST_F(RegressionTest,Bug853879)
{
  EXPECT_TRUE( parse( "853879-1.vtt" ) );
}

// Bug853589 - Crash [@parse_cueparams]
// (https://bugzilla.mozilla.org/show_bug.cgi?id=853589)
//
// File contains syntax errors (bad end timestamp), but should parse
// successfully due to not aborting on errors.
TEST_F(RegressionTest,Bug853589)
{
  EXPECT_TRUE( parse( "853589-1.vtt" ) );
}

// Bug863931 - Heap Buffer Overflow[@webvtt_start_tag_state]
// (https://bugzilla.mozilla.org/show_bug.cgi?id=863931)
//
// Buffer overflow in webvtt_start_tag_state (cuetext.c)
//
// Initial stack trace:
// ==87623==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x600c025b2dc0 at pc 0x10788de3f bp 0x7fff5fbfb8d0 sp 0x7fff5fbfb8c8
// READ of size 1 at 0x600c025b2dc0 thread T0
//     #0 0x10788de3e in webvtt_start_tag_state cuetext.c:443
//     #1 0x10788e810 in webvtt_cuetext_tokenizer cuetext.c:584
//     #2 0x10788ed0c in webvtt_parse_cuetext cuetext.c:696
//     #3 0x107896b23 in webvtt_proc_cuetext parser.c:1684
//     #4 0x10789e99b in webvtt_parse_chunk parser.c:1736
//     ...
TEST_F(RegressionTest,Bug863931)
{
  EXPECT_TRUE( parse( "863931-1.vtt" ) );
}

