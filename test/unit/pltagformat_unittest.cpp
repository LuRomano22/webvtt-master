#include "payload_testfixture"
class PayloadTagFormat : public PayloadTest {};

/*
 * These tests deal with tricky situations where a cue text tag is improperly formatted but is parsed correctly.
 * These situations end in webvtt nodes whose values are valid and predictable, but were not intended by the original .vtt file.
 */

/*
 * This test is to verify that multiple cue text tags can be nested within eachother.
 * Based on the WebVTT cue components specification as of October 3, 2012.
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-components
 */
TEST_F(PayloadTagFormat, MultipleCueTextTag)
{
  loadVtt( "payload/tag-format/multiple-cue-text-tag.vtt", 1 );
  ASSERT_EQ( Node::Italic, getHeadOfCue( 0 )[ 0 ].kind() );
  ASSERT_EQ( Node::Bold, getHeadOfCue( 0 )[ 0 ][ 1 ].kind() );
}

/*
Verifies that an incorrect class name cannot be used as a cue component.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules step "If token is an end tag" (11/27/2012)
 *  Relevant cue text specification rule(s):
 *    1. End tags that do not close the current open tag are ignored.
 *    2. End tags that are not formatted properly will be ignored.
 *    3. Tags that do not have a valid tag name are ignored.
 *  Implications:
 *    1. Tags that are not closed properly are valid until the end of the current cue text.
*/
TEST_F(PayloadTagFormat, BadTagName)
{
  loadVtt( "payload/tag-format/incorrect-tag-name.vtt", 1 );
  ASSERT_EQ( 3, getHeadOfCue( 0 ).childCount() );
}

/*
 * Verifies that cue text end tags that are out of order will be ignored.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules step "If token is an end tag" (11/27/2012)
 *  Relevant cue text specification rule(s):
 *    1. End tags that do not close the current open tag are ignored.
 *    2. End tags that are not formatted properly will be ignored.
 *  Implications:
 *    1. Tags that are not closed properly are valid until the end of the current cue text.
 */
TEST_F(PayloadTagFormat, BadTagNesting)
{
  loadVtt( "payload/tag-format/bad-tag-nesting.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );

  const Node italicNode = head[ 1 ];
  ASSERT_EQ( Node::Italic, italicNode.kind() );
  ASSERT_EQ( Node::Bold, italicNode[ 0 ].kind() );
  ASSERT_EQ( Node::Text, italicNode[ 0 ][ 0 ].kind() );
}

/*
 * Verifies that cue text end tags that are malformed will be ignored.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules step "If token is an end tag" (11/27/2012)
 *  Relevant cue text specification rule(s):
 *    1. End tags that do not close the current open tag are ignored.
 *    2. End tags that are not formatted properly will be ignored.
 *  Implications:
 *    1. Tags that are not closed properly are valid until the end of the current cue text.
 */
TEST_F(PayloadTagFormat, EndTagNoBackSlashNoEndBrace)
{
  loadVtt( "payload/tag-format/end-tag-no-back-slash-no-end-brace.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );

  const Node italicNode = head[ 1 ];
  ASSERT_EQ( Node::Italic, italicNode.kind() );

  ASSERT_EQ( 2, italicNode.childCount() );
  ASSERT_EQ( Node::Text, italicNode[ 0 ].kind() );
  ASSERT_EQ( Node::Italic, italicNode[ 1 ].kind() );
}

/*
 * Verifies that cue text end tags that are malformed will be ignored.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules step "If token is an end tag" (11/27/2012)
 *  Relevant cue text specification rule(s):
 *    1. End tags that do not close the current open tag are ignored.
 *    2. End tags that are not formatted properly will be ignored.
 *  Implications:
 *    1. Tags that are not closed properly are valid until the end of the current cue text.
 */
TEST_F(PayloadTagFormat, EndTagNoEndBrace)
{
  loadVtt( "payload/tag-format/end-tag-no-end-brace.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );

  const Node italicNode = head[ 1 ];
  ASSERT_EQ( Node::Italic, italicNode.kind() );

  ASSERT_EQ( 1, italicNode.childCount() );
  ASSERT_EQ( Node::Text, italicNode[ 0 ].kind() );
}

/*
 * Verifies that cue text end tags that are malformed will be ignored.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules step "If token is an end tag" (11/27/2012)
 *  Relevant cue text specification rule(s):
 *    1. End tags that do not close the current open tag are ignored.
 *    2. End tags that are not formatted properly will be ignored.
 *  Implications:
 *    1. Tags that are not closed properly are valid until the end of the current cue text.
 */
TEST_F(PayloadTagFormat, EndTagNoStartBrace)
{
  loadVtt( "payload/tag-format/end-tag-no-start-brace.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );

  const Node italicNode = head[ 1 ];
  ASSERT_EQ( Node::Italic, italicNode.kind() );

  ASSERT_EQ( 1, italicNode.childCount() );
  ASSERT_EQ( Node::Text, italicNode[ 0 ].kind() );
}

/*
 * Verifies that cue text end tags that are malformed will be ignored.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules step "If token is an end tag" (11/27/2012)
 *  Relevant cue text specification rule(s):
 *    1. End tags that do not close the current open tag are ignored.
 *    2. End tags that are not formatted properly will be ignored.
 *  Implications:
 *    1. Tags that are not closed properly are valid until the end of the current cue text.
 */
TEST_F(PayloadTagFormat, MultiTagNoEndTag)
{
  loadVtt( "payload/tag-format/multi-tag-no-end-tag.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );
  ASSERT_EQ( Node::Text, head[ 0 ].kind() );

  const Node italicNode0 = head[ 1 ];

  ASSERT_EQ( 2, italicNode0.childCount() );
  ASSERT_EQ( Node::Italic, italicNode0.kind() );
  ASSERT_EQ( Node::Text, italicNode0[ 0 ].kind() );

  const Node italicNode1 = italicNode0[ 1 ];

  ASSERT_EQ( Node::Italic, italicNode1.kind() );
  ASSERT_EQ( Node::Text, italicNode1[ 0 ].kind() );
}

/*
 * Verifies that a cue text start tag with an invalid name will be ignored.
 * From http://dev.w3.org/html5/webvtt/#webvtt-tag-state As given by the algorithm defined and any connecting parts. (11/27/2012)
 *  Relevant cue text specification rules:
 *    1. Characters that come after the "<" and before a white space are considered to be apart of the tag name.
 *    2. Tag names that are not valid are ignored.
 *    3. Characters that come after the beginning "<" brace and after a white space character are considered to be apart of the annotation.
 *
 * In this example the parser reads "iare</i" inside of the beginning "<" and ending ">" as the tag name.
 */
TEST_F(PayloadTagFormat, StartTagNoEndBrace)
{
  loadVtt( "payload/tag-format/start-tag-no-end-brace.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );
  ASSERT_EQ( Node::Text, head[ 0 ].kind() );
  ASSERT_EQ( Node::Text, head[ 1 ].kind() );
}

/*
 * Verifies that a cue text start tag with an annotation will be parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-tag-state As given by the algorithm defined and any connecting parts. (11/27/2012)
 *  Relevant cue text specification rules:
 *    1. Characters that come after the "<" and before a white space are considered to be apart of the tag name.
 *    2. Tag names that are not valid are ignored.
 *    3. Characters that come after the beginning "<" brace and after a white space character are considered to be apart of the annotation.
 *
 * In this example the parser reads "are</i" after the whitespace as the annotation.
 */
TEST_F(PayloadTagFormat, StartTagNoEndBraceSpace)
{
  loadVtt( "payload/tag-format/start-tag-no-end-brace-space.vtt", 1 );
  const Node head= getHeadOfCue( 0 );

  ASSERT_EQ( 2, head.childCount() );

  const Node italicNode = head[ 1 ];
  ASSERT_EQ( Node::Italic, italicNode.kind() );

  ASSERT_EQ( 1, italicNode.childCount() );
  ASSERT_EQ( Node::Text, italicNode[ 0 ].kind() );
}
