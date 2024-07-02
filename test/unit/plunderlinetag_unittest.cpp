
#include "payload_testfixture"
class PayloadUnderlineTag : public PayloadTest {};

/*
 * Verifies that a underline cue text tag is parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-underline-span (11/27/2012)
 *  Underline tags consist of:
 *    1. A cue span start tag "u" that disallows an annotation.
 *    2. Possible cue internal text representing the underlined text.
 *    3. A cue span end tag.
 */
TEST_F(PayloadUnderlineTag, UnderlineTag)
{
  loadVtt( "payload/u-tag/u-tag.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( 3, head.childCount() );
  ASSERT_EQ( Node::Underline, head[ 1 ].kind() );
}

/*
 * Verifies that a underline tag with an annotation is parsed correctly but does not contain the annotation.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-underline-span (11/27/2012)
 *  Underline tags consist of:
 *    1. A cue span start tag "u" that disallows an annotation.
 *    2. Possible cue internal text representing the underlined text.
 *    3. A cue span end tag.
 */
TEST_F(PayloadUnderlineTag, UnderlineAnnotation)
{
  loadVtt( "payload/u-tag/u-tag-annotation.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( 3, head.childCount() );
  ASSERT_EQ( Node::Underline, head[ 1 ].kind() );
  ASSERT_TRUE( head[ 1 ].annotation().isEmpty() );
}

/*
 * Verifies that a single subclass can be attached to a cue text underline start tag.
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
TEST_F(PayloadUnderlineTag, UnderlineTagSingleSubclass)
{
  loadVtt( "payload/u-tag/u-tag-single-subclass.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( 3, head.childCount() );
  ASSERT_EQ( Node::Underline, head[ 1 ].kind() );

  StringList cssClasses = head[ 1 ].cssClasses();

  ASSERT_EQ( 1, cssClasses.length() );
  expectEquals( "class", cssClasses.stringAt( 0 ) );
}

/*
 * Verifies that multiple subclasses can be attached to a cue text underline start tag.
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
TEST_F(PayloadUnderlineTag, UnderlineTagMultiSubclass)
{
  loadVtt( "payload/u-tag/u-tag-multi-subclass.vtt", 1 );

  const Node head = getHeadOfCue( 0 );

  ASSERT_EQ( 3, head.childCount() );
  ASSERT_EQ( Node::Underline, head[ 1 ].kind() );

  StringList cssClasses = head[ 1 ].cssClasses();

  ASSERT_EQ( 2, cssClasses.length() );
  expectEquals( "class", cssClasses.stringAt( 0 ) );
  expectEquals( "subclass", cssClasses.stringAt( 1 ) );
}
