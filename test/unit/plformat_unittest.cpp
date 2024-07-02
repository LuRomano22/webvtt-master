#include "payload_testfixture"
class PayloadFormat : public PayloadTest {};

/*
 * Verifies that a cue text span with no tags will parse correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-span (11/27/2012)
 */
TEST_F(PayloadFormat, BasicCueText)
{
  loadVtt( "payload/format/basic-cue-text.vtt", 1 );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )[ 0 ].kind() );
}

/*
 * Verifies that multiple cue components can be put in one line.
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-components
 */
TEST_F(PayloadFormat, MultipleCueTextTag)
{
  loadVtt( "payload/format/multiple-cue-tag.vtt", 1 );
  ASSERT_EQ( 5, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that multiple cue components can be put in one line, one after
 * the other.
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-components
 */
TEST_F(PayloadFormat, MultipleCueTextTagTogether)
{
  loadVtt( "payload/format/multiple-cue-tag-together.vtt", 1 );
  ASSERT_EQ( 4, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that a cue text span with multiple lines will work.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineBasicCueText)
{
  loadVtt( "payload/format/multiline-basic-cue-text.vtt", 1 );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )[ 0 ].kind() );
}

/*
 * Verifies that cue text with single line feed characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineCueText)
{
  loadVtt( "payload/format/multiline-cue-text.vtt", 1 );
  ASSERT_EQ( 5, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that cue text with single carriage return characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineCueTextCR)
{
  loadVtt( "payload/format/multiline-cue-text-cr.vtt", 1 );
  ASSERT_EQ( 5, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that cue text with single CRLF pair characters will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineCueTextCRLF)
{
  loadVtt( "payload/format/multiline-cue-text-crlf.vtt", 1 );
  ASSERT_EQ( 5, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that a file with payload text containing a line feed in between the text
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadFormat, MultilineCueTextExtraNewline)
{
  loadVtt( "payload/format/multiline-cue-text-extra-newline.vtt", 1 );
  ASSERT_EQ( 2, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that a file with payload text containing a carriage return in between the text
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadFormat, MultilineCueTextExtraNewlineCR)
{
  loadVtt( "payload/format/multiline-cue-text-extra-newline-cr.vtt", 1 );
  ASSERT_EQ( 2, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that a file with payload text containing a CRLF pair in between the text
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadFormat, MultilineCueTextExtraNewlineCRLF)
{
  loadVtt( "payload/format/multiline-cue-text-extra-newline-crlf.vtt", 1 );
  ASSERT_EQ( 2, getHeadOfCue( 0 ).childCount() );
}

/**
 * Verifies that multiple cue component are parsed correctly.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally
 *  separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineMultipleCueTextTag)
{
  loadVtt( "payload/format/multiline-multiple-cue-text-tag.vtt", 1 );
  const Node head = getHeadOfCue( 0 );
  ASSERT_LE( 1, head.childCount() );

  const Node underlineTag = head[0];
  EXPECT_EQ( Node::Underline, underlineTag.kind() );

  ASSERT_LE( 2, underlineTag.childCount() );
  EXPECT_EQ( Node::Text, underlineTag[0].kind() );

  const Node italicTag = underlineTag[1];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  ASSERT_LE( 2, italicTag.childCount() );
  EXPECT_EQ( Node::Text, italicTag[0].kind() );
  const Node boldTag = italicTag[1];
  EXPECT_EQ( Node::Bold, boldTag.kind() );
}

/*
 * Verifies that cue text separated by a CR line terminator is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (12/02/2012)
 *  Cue text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineBasicCueTextCR)
{
  loadVtt( "payload/format/multiline-basic-cue-text-cr.vtt", 1 );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )[ 0 ].kind() );
}

/*
 * Verifies that cue text separated by a CRLF line terminator is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (12/02/2012)
 *  Cue text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadFormat, MultilineBasicCueTextCRLF)
{
  loadVtt( "payload/format/multiline-basic-cue-text-crlf.vtt", 1 );
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )[ 0 ].kind() );
}

/* Verifies that cue text with a malformed line terminator is still parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-parser-algorithm (12/02/2012)
 * The WebVTT parser algorithm is as follows:
 * [...] 50. Bad cue: Discard cue.
 */
TEST_F(PayloadFormat, MultilineBasicCueTextExtraLine)
{
  loadVtt( "payload/format/multiline-extra-line-terminator.vtt", 1);
  ASSERT_EQ( Node::Text, getHeadOfCue( 0 )[ 0 ].kind() );
}
