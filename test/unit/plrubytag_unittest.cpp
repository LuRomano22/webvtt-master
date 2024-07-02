#include "payload_testfixture"
class PayloadRubyTag : public PayloadTest {};

/**
 * Verifies that the parser correctly parses ruby tags.
 * 1. Check standard - <ruby><rt></rt></ruby>
 * 2. Check optional last rt - <ruby><rt></ruby>
 *
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-ruby-span (11/25/2012):
 * A WebVTT cue ruby span consists of the following components, in the order given:
 * 1. A WebVTT cue span start tag "ruby" that disallows an annotation.
 * 2. One or more occurrences of the following group of components, in the order given:
 *  1. WebVTT cue internal text, representing the ruby base.
 *  2. A WebVTT cue span start tag "rt" that disallows an annotation.
 *  3. A WebVTT cue ruby text span: WebVTT cue internal text, representing the ruby text component
 *     of the ruby annotation.
 *  4. A WebVTT cue span end tag "rt". If this is the last occurrence of this group of components in
 *     the WebVTT cue ruby span, then this last end tag string may be omitted.
 * 3. If the last end tag string was not omitted: Optionally, a WebVTT line terminator.
 * 4. If the last end tag string was not omitted: Zero or more U+0020 SPACE characters or U+0009
 *    CHARACTER TABULATION (tab) characters, each optionally followed by a WebVTT line terminator.
 * 5. A WebVTT cue span end tag "ruby".
 */
TEST_F(PayloadRubyTag, ValidRuby)
{
  loadVtt( "payload/ruby-tag/ruby-cue-component.vtt", 1 );

  const Node head0 = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head0[ 1 ].kind() );
  ASSERT_EQ( Node::RubyText, head0[ 1 ][ 1 ].kind() );
}

TEST_F(PayloadRubyTag, RubyAnnotation)
{
  loadVtt( "payload/ruby-tag/ruby-annotation.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( 0, head[ 1 ].annotation().length() );

}

TEST_F(PayloadRubyTag, RubyTextAnnotation)
{
  loadVtt( "payload/ruby-tag/ruby-text-annotation.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( 0, head[ 1 ].annotation().length() );
}

TEST_F(PayloadRubyTag, NoRubyBaseText)
{
  loadVtt( "payload/ruby-tag/no-base-text.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head[ 1 ].kind() );
  ASSERT_EQ( Node::RubyText, head[ 1 ][ 0 ].kind() );
}

TEST_F(PayloadRubyTag, NoRubyTextTag)
{
  loadVtt( "payload/ruby-tag/no-ruby-text-tag.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head[ 1 ].kind() );
  ASSERT_EQ( Node::Text, head[ 1 ][ 0 ].kind() );
}

TEST_F(PayloadRubyTag, NoRubyText)
{
  loadVtt( "payload/ruby-tag/no-ruby-text.vtt", 1 );

  const Node head0 = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head0[ 1 ].kind() );
  ASSERT_EQ( Node::Text, head0[ 1 ][ 0 ].kind() );
  ASSERT_EQ( Node::RubyText, head0[ 1 ][ 1 ].kind() );
  ASSERT_EQ( head0[ 1 ][ 1 ].childCount(), 0 );
}

TEST_F(PayloadRubyTag, NoRubyTextNoEndRubTextBrace)
{
  loadVtt( "payload/ruby-tag/no-ruby-text-no-end-ruby-text-tag.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head[ 1 ].kind() );
  ASSERT_EQ( Node::Text, head[ 1 ][ 0 ].kind() );
  ASSERT_EQ( Node::RubyText, head[ 1 ][ 1 ].kind() );
  ASSERT_EQ( head[ 1 ][ 1 ].childCount(), 0 );
}

/*
 * Verifies that a single subclass can be attached to a cue text ruby start tag.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag (11/27/2012)
 *  Cue span start tags consist of the following:
 *    1. A "<" character representing the beginning of the start tag.
 *    2. The tag name.
 *    3. Zero or more the following sequence representing a subclasses of the start tag
 *      3.1. A full stop "." character.
 *      3.2. A sequence of non-whitespace characters.
 *    4. If the start tag requires an annotation then a space or tab character followed by a sequence of
 *       non-whitespace characters representing the annotation.
 *    5. A ">" character repsenting the end of the start tag.
 */
TEST_F(PayloadRubyTag, RubyTagSingleSubclass)
{
  loadVtt( "payload/ruby-tag/ruby-tag-single-subclass.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head[ 1 ].kind() );

  StringList cssClasses =  head[ 1 ].cssClasses();

  ASSERT_EQ( 1, cssClasses.length() );
  expectEquals( "class", cssClasses.stringAt( 0 ) );
}

TEST_F(PayloadRubyTag, RubyTagMultiSubclass)
{
  loadVtt( "payload/ruby-tag/ruby-tag-multi-subclass.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::Ruby, head[ 1 ].kind() );

  StringList cssClasses =  head[ 1 ].cssClasses();

  ASSERT_EQ( 2, cssClasses.length() );
  expectEquals( "class", cssClasses.stringAt( 0 ) );
  expectEquals( "subclass", cssClasses.stringAt( 1 ) );
}

/*
 * Verifies that a single subclass can be attached to a cue text ruby text start tag.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-span-start-tag (11/27/2012)
 *  Cue span start tags consist of the following:
 *    1. A "<" character representing the beginning of the start tag.
 *    2. The tag name.
 *    3. Zero or more the following sequence representing a subclasses of the start tag
 *      3.1. A full stop "." character.
 *      3.2. A sequence of non-whitespace characters.
 *    4. If the start tag requires an annotation then a space or tab character followed by a sequence of
 *       non-whitespace characters representing the annotation.
 *    5. A ">" character repsenting the end of the start tag.
 */
TEST_F(PayloadRubyTag, RubyTextTagSingleSubclass)
{
  loadVtt( "payload/ruby-tag/ruby-text-tag-single-subclass.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::RubyText, head[ 1 ][ 1 ].kind() );

  StringList cssClasses = head[ 1 ][ 1 ].cssClasses();

  ASSERT_EQ( 1, cssClasses.length() );
  expectEquals( "class", cssClasses.stringAt( 0 ) );
}

TEST_F(PayloadRubyTag, RubyTextTagMultiSubclass)
{
  loadVtt( "payload/ruby-tag/ruby-text-tag-multi-subclass.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( Node::RubyText, head[ 1 ][ 1 ].kind() );

  StringList cssClasses = head[ 1 ][ 1 ].cssClasses();

  ASSERT_EQ( 2, cssClasses.length() );
  expectEquals( "class", cssClasses.stringAt( 0 ) );
  expectEquals( "subclass", cssClasses.stringAt( 1 ) );
}

TEST_F(PayloadRubyTag, RubyTextNoRuby)
{
  loadVtt( "payload/ruby-tag/rt-no-ruby.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  EXPECT_EQ( 2, head.childCount() );
  EXPECT_EQ( Node::Text, head[ 0 ].kind() );
  EXPECT_EQ( Node::Text, head[ 1 ].kind() );
}
