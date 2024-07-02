#include "payload_testfixture"
class PayloadEscapeCharacter : public PayloadTest {};

/*
 * WebVTT Escape Character Specification being Tested:
 *
 * U+003B SEMICOLON character (;)
 *  First, examine the value of buffer:
 *  If buffer is the string "&amp", then append a U+0026 AMPERSAND character (&) to result.
 *  If buffer is the string "&lt", then append a U+003C LESS-THAN SIGN character (<) to result.
 *  If buffer is the string "&gt", then append a U+003E GREATER-THAN SIGN character (>) to result.
 *  If buffer is the string "&lrm", then append a U+200E LEFT-TO-RIGHT MARK character to result.
 *  If buffer is the string "&rlm", then append a U+200F RIGHT-TO-LEFT MARK character to result.
 *  If buffer is the string "&nbsp", then append a U+00A0 NO-BREAK SPACE character to result.
 *  Otherwise, append buffer followed by a U+003B SEMICOLON character (;) to result.
 *  Then, in any case, set tokenizer state to the WebVTT data state, and jump to the step labeled next.
 *
*/

/*
 * Verifies that greater than escape characters in the cue text payload are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-gt-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter, GT)
{
  loadVtt( "payload/escape/gt-escape-character.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( ">", node.text() );
}

/*
 * Verifies that less than escape characters in the cue text payload are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-lt-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter, LT)
{
  loadVtt( "payload/escape/lt-escape-character.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "<", node.text() );
}

/*
 * Verifies that ampersand escape characters in the cue text payload are parsed correctly.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-amp-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter, Ampersand)
{
  loadVtt( "payload/escape/ampersand-escape-character.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "&", node.text() );
}

/*
 * Verifies that left to right escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-lrm-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter, LRM)
{
  loadVtt( "payload/escape/lrm-escape-character.vtt", 1 );

    const Node node = getHeadOfCue( 0 )[ 0 ];

    /* verify that it is a Node */
    ASSERT_EQ( Node::Text, node.kind() );

    /* create a UTF8 representation of LRM and compare with textnode */
    ASSERT_EQ( LRM, node.text().utf16At( 0 ) );
}

/*
 * Verifies that right to left escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-rlm-escape (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter, RLM)
{
  loadVtt( "payload/escape/rlm-escape-character.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind()) ;

  /* create a UTF8 representation of RLM and compare with textnode */
  ASSERT_EQ( RLM, node.text().utf16At( 0 ) );
}

/*
 * Verifies that multiple escape characters are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 */
TEST_F(PayloadEscapeCharacter, MultipleEscapeCharacter)
{
  loadVtt( "payload/escape/multiple-escape-character.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

    /* verify that it is a Node */
    ASSERT_EQ( Node::Text, node.kind() );

    /* create a UTF8 representation of NBSP and compare with textnode */
    ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
}

/**
 * Verifies that multiple escape characters on multiple lines are parsed.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *
 * Cue text text consists of one or more cue text components optionally
 * separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacter)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character.vtt", 1 );
  const Node head = getHeadOfCue( 0 );
  ASSERT_LT( 0, head.childCount() );

  const Node node = head[0];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_LE( 5, node.text().length() );
  EXPECT_EQ( 5, node.text().length() );
  EXPECT_EQ( NBSP, node.text().utf16At( 0 ) );
  EXPECT_EQ( NBSP, node.text().utf16At( 2 ) );
}

TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacterText)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character-text.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
  expectEquals( "\xC2\xA0\n" "Anyone out there?\n" "\xC2\xA0", node.text() );
}
/*
 * Verifies that multiple escape characters on multiple lines are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacterCR)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character-cr.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
}

/*
 * Verifies that multiple escape characters on multiple lines are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-text (11/27/2012)
 *  Cue text text consists of one or more cue text components optionally separated by a single line terminator which can be:
 *    1. CR (U+000D)
 *    2. LF (U+000A)
 *    3. CRLF pair
 */
TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacterCRLF)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character-crlf.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
}

/*
 * Verifies that a file with a payload containing a newline in between two escape characters
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacterExtraNewline)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character-extra-newline.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
}

/*
 * Verifies that a file with a payload containing a newline in between two escape characters
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacterExtraNewlineCR)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character-extra-newline-cr.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
}

/*
 * Verifies that a file with a payload containing a newline in between two escape characters
 * will finish the parsing attempt gracefully.
 * From http://dev.w3.org/html5/webvtt/#parsing (12/10/2012):
 *
 * ...
 * 50. Bad cue: Discard cue.
 * 51. Bad cue loop: If position is past the end of input, then jump to the step labeled end.
 */
TEST_F(PayloadEscapeCharacter, MultilineMultipleEscapeCharacterExtraNewlineCRLF)
{
  loadVtt( "payload/escape/multiline-multiple-escape-character-extra-newline-crlf.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );

  /* create a UTF8 representation of NBSP and compare with textnode */
  ASSERT_EQ( NBSP, node.text().utf16At( 0 ) );
}

/*
 * WebVTT Escape Character Specification being Tested:
 *
 * U+003B SEMICOLON character (;)
 *  First, examine the value of buffer:
 *  If buffer is the string "&amp", then append a U+0026 AMPERSAND character (&) to result.
 *  If buffer is the string "&lt", then append a U+003C LESS-THAN SIGN character (<) to result.
 *  If buffer is the string "&gt", then append a U+003E GREATER-THAN SIGN character (>) to result.
 *  If buffer is the string "&lrm", then append a U+200E LEFT-TO-RIGHT MARK character to result.
 *  If buffer is the string "&rlm", then append a U+200F RIGHT-TO-LEFT MARK character to result.
 *  If buffer is the string "&nbsp", then append a U+00A0 NO-BREAK SPACE character to result.
 *  Otherwise, append buffer followed by a U+003B SEMICOLON character (;) to result.
 *  Then, in any case, set tokenizer state to the WebVTT data state, and jump to the step labeled next.
 *
*/

/* Testing Space Character Escape */


/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
  Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&nsp;' instead of '&nbsp;'
 Expected Output: '&nsp;'
*/
TEST_F(PayloadEscapeCharacter, NSP)
{
  loadVtt( "payload/escape/space-character-escape-nsp.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &nsp;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates To:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 The Parser currently allows incorrect escapes to be outputted in the cue text string
 Expected Output: '&nbp'
*/
TEST_F(PayloadEscapeCharacter, NBP)
{
  loadVtt( "payload/escape/space-character-escape-nbp.vtt", 1 );

  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &nbp;", node.text() );

}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
  Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&bsp;' instead of '&nbsp;'
 Expected Output: '&bsp;'
*/
TEST_F(PayloadEscapeCharacter, BSP)
{
  loadVtt( "payload/escape/space-character-escape-bsp.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &bsp;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&bp;' instead of '&nbsp;'
 Expected Output: '&bp;'
*/
TEST_F(PayloadEscapeCharacter, BP)
{
  loadVtt( "payload/escape/space-character-escape-bp.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &bp;", node.text() );

}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&b;' instead of '&nbsp;'
 Expected Output: '&b;'
*/
TEST_F(PayloadEscapeCharacter, B)
{
  loadVtt( "payload/escape/space-character-escape-b.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &b;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&s;' instead of '&nbsp;'
 Expected Output: '&s;'
*/
TEST_F(PayloadEscapeCharacter, S)
{
  loadVtt( "payload/escape/space-character-escape-s.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &s;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&ns;' instead of '&nbsp;'
 Expected Output: '&ns;'
*/
TEST_F(PayloadEscapeCharacter, NS)
{
  loadVtt( "payload/escape/space-character-escape-ns.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &ns;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&np;' instead of '&nbsp;'
 Expected Output: '&np;'
*/
TEST_F(PayloadEscapeCharacter, NP)
{
  loadVtt( "payload/escape/space-character-escape-np.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &np;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&sp;' instead of '&nbsp;'
 Expected Output: '&sp;'
*/
TEST_F(PayloadEscapeCharacter, SP)
{
  loadVtt( "payload/escape/space-character-escape-sp.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &sp;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&p;' instead of '&nbsp;'
 Expected Output: '&p;'
*/
TEST_F(PayloadEscapeCharacter, P)
{
  loadVtt( "payload/escape/space-character-escape-p.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &p;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&bs;' instead of '&nbsp;'
 Expected Output: '&bs;'
*/
TEST_F(PayloadEscapeCharacter, BS)
{
  loadVtt( "payload/escape/space-character-escape-bs.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &bs;", node.text() );
}

/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&nbs;' instead of '&nbsp;'
 Expected Output: '&nbs;'
*/
TEST_F(PayloadEscapeCharacter, NBS)
{
  loadVtt( "payload/escape/space-character-escape-nbs.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &nbs;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&nb;' instead of '&nbsp;'
 Expected Output: '&nb;'
*/
TEST_F(PayloadEscapeCharacter, NB)
{
  loadVtt( "payload/escape/space-character-escape-nb.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &nb;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Space Character Escape : '&n;' instead of '&nbsp;'
 Expected Output: '&n;'
*/
TEST_F(PayloadEscapeCharacter, N)
{
  loadVtt( "payload/escape/space-character-escape-n.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Space Character escape: &n;", node.text() );
}

/* Testing Left-To-Right Character Escape */

/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&lr;' instead of '&lrm;'
 Expected Output: '&lr;'
*/
TEST_F(PayloadEscapeCharacter, LeftToRight)
{
  loadVtt( "payload/escape/left-to-right-character-escape-lr.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &lr;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&l;' instead of '&lrm;'
 Expected Output: '&l;'
*/
TEST_F(PayloadEscapeCharacter, L)
{
  loadVtt( "payload/escape/left-to-right-character-escape-l.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &l;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&lm;' instead of '&lrm;'
 Expected Output: '&lm;'
*/
TEST_F(PayloadEscapeCharacter, LM)
{
  loadVtt( "payload/escape/left-to-right-character-escape-lm.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &lm;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&rm;' instead of '&lrm;'
 Expected Output: '&rm;'
*/
TEST_F(PayloadEscapeCharacter, RM)
{
  loadVtt( "payload/escape/left-to-right-character-escape-rm.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &rm;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&m;' instead of '&lrm;'
 Expected Output: '&m;'
*/
TEST_F(PayloadEscapeCharacter, M)
{
  loadVtt( "payload/escape/left-to-right-character-escape-m.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &m;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&r;' instead of '&lrm;'
 Expected Output: '&r;'
*/
TEST_F(PayloadEscapeCharacter, R)
{
  loadVtt( "payload/escape/left-to-right-character-escape-r.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &r;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&lm;' instead of '&lrm;'
 Expected Output: '&lm;'
*/
TEST_F(PayloadEscapeCharacter, LM_LeftToRight)
{
  loadVtt( "payload/escape/left-to-right-character-escape-lm.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &lm;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Left to Right Character Escape : '&rl;' instead of '&lrm;'
 Expected Output: '&rl;'
*/
TEST_F(PayloadEscapeCharacter, RL)
{
  loadVtt( "payload/escape/left-to-right-character-escape-rl.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Left to Right Character escape: &rl;", node.text() );
}

/* Test Ampersand Character Escape */

/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Expected Output: '&'
*/
TEST_F(PayloadEscapeCharacter, AmpersandCharacter)
{
  loadVtt( "payload/escape/ampersand-character-escape.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Ampersand Special Character: &", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Ampersand Escape : '&a;' instead of '&amp;'
 Expected Output: '&a;'
*/
TEST_F(PayloadEscapeCharacter, A)
{
  loadVtt( "payload/escape/ampersand-character-escape-a.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Ampersand escape: &a;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Ampersand Escape : '&am;' instead of '&amp;'
 Expected Output: '&am;'
*/
TEST_F(PayloadEscapeCharacter, AM)
{
  loadVtt( "payload/escape/ampersand-character-escape-am.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Ampersand escape: &am;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Ampersand Escape : '&mp;' instead of '&amp;'
 Expected Output: '&mp;'
*/
TEST_F(PayloadEscapeCharacter, MP)
{
  loadVtt( "payload/escape/ampersand-character-escape-mp.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Ampersand escape: &mp;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Ampersand Escape : '&p;' instead of '&amp;'
 Expected Output: '&p;'
*/
TEST_F(PayloadEscapeCharacter, P_Ampersand)
{
  loadVtt( "payload/escape/ampersand-character-escape-p.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Ampersand escape: &p;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Ampersand Escape : '&ap;' instead of '&amp;'
 Expected Output: '&ap;'
*/
TEST_F(PayloadEscapeCharacter, AP)
{
  loadVtt( "payload/escape/ampersand-character-escape-ap.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Ampersand escape: &ap;", node.text() );
}

/* Test Less Than Character Escape */

/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Less Than Escape : '&l;' instead of '&lt;'
 Expected Output: '&l;'
*/
TEST_F(PayloadEscapeCharacter, LessThan)
{
  loadVtt( "payload/escape/less-than-character-escape-l.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Less Than escape: &l;", node.text() );
}
/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Less Than Escape : '&t;' instead of '&lt;'
 Expected Output: '&t;'
*/
TEST_F(PayloadEscapeCharacter, T)
{
  loadVtt( "payload/escape/less-than-character-escape-t.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Less Than escape: &t;", node.text() );
}

/* Test Greater Than Escape Character */

/*
 WebVTT Specification Version:
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 Description:
 Incorrect Greater Than Escape : '&g;' instead of '&gt;'
 Expected Output: '&g;'
*/
TEST_F(PayloadEscapeCharacter, GreaterThan)
{
  loadVtt( "payload/escape/greater-than-character-escape-g.vtt", 1 );
  const Node node = getHeadOfCue( 0 )[ 0 ];

  /* verify that it is a Node */
  ASSERT_EQ( Node::Text, node.kind() );
  expectEquals( "Test Greater Than escape: &g;", node.text() );
}

/*
 WebVTT - Living Standard Last Updated 2 October 2012

 Relates to:
 Cue Text Escape Characters and Cue Text Tags:
 http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules

 cue text to be parsed: <i>Test Ampersand escape within i tag: &amp; </i>
 correct Ampersand Character Escape : within a cue i tag
*/
TEST_F(PayloadEscapeCharacter, AmpersandWithinTag)
{
  loadVtt( "payload/escape/i-tag-with-ampersand.vtt", 1 );

  const Node node = getHeadOfCue(0);

  /* Check to see if the Italic node has been correctly formed */
  ASSERT_EQ( Node::Italic, node[ 0 ].kind() );

  /* verify the text within the i tag */
  const Node textNode = getHeadOfCue( 0 )[ 0 ][ 0 ];
  expectEquals( "Test Ampersand escape within i tag: & ", textNode.text() );
}

/**
 * Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text to be Parsed: <b><i>Test Ampersand escape within i tag: &amp;
 *                        </i></b>
 * correct Ampersand Character Escape : cue b tag within a cue i tag
 */
TEST_F(PayloadEscapeCharacter, AmpersandWithinMultipleTags)
{
  loadVtt( "payload/escape/i-within-b-tag-with-ampersand.vtt", 1 );
  const Node head = getHeadOfCue(0);
  ASSERT_LT( 0, head.childCount() );

  /* verify bold tag */
  const Node boldTag = head[0];
  EXPECT_EQ( Node::Bold, boldTag.kind() );
  ASSERT_LT( 0, boldTag.childCount() );

  /* verify italic tag within bold tag */
  const Node italicTag = boldTag[ 0 ];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  ASSERT_LT( 0, italicTag.childCount() );
  /* verify the text within the italic tag */
  const Node textNode = italicTag[0];
  expectEquals( "Test Ampersand escape within i tag: & ", textNode.text() );
}

/**
 * Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text to be Parsed: <b><i> some filler text </i></b> &amp;
 * correct Ampersand Character Escape outside cue b tag within a cue i tag
 */
TEST_F(PayloadEscapeCharacter, AmpersandOutsideTwoTags)
{
  loadVtt( "payload/escape/"
           "i-within-b-tag-with-ampersand-outside.vtt", 1 );
  const Node head = getHeadOfCue(0);
  ASSERT_LT( 0, head.childCount() );

  /* verify bold tag */
  const Node boldTag = head[0];
  EXPECT_EQ( Node::Bold, boldTag.kind() );
  ASSERT_LT( 0, boldTag.childCount() );

  /* verify italic tag within bold tag */
  const Node italicTag = boldTag[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  ASSERT_LT( 1, head.childCount() );
  /* verify the escape character text within the i tag */
  const Node textNode = head[ 1 ];
  expectEquals( " &", textNode.text() );
}

/**
 * Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text to be Parsed: <i.class> Some Filler Text </i>
 *                        &amp;
 * correct Ampersand Character Escape on new line after two encapsulated tags
 * with class
 */
TEST_F(PayloadEscapeCharacter, AmpersandOnNewLineAfterTwoTagsWithClass)
{
  loadVtt( "payload/escape/"
           "ampersand-outside-tag-on-newline-with-class.vtt", 1 );
  const Node head = getHeadOfCue(0);
  ASSERT_LT( 0, head.childCount() );

  /* verify italic tag */
  const Node italicTag = head[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  /* verify class inside italic tag*/
  StringList cssClass = italicTag.cssClasses();
  expectEquals( "class", cssClass.stringAt(0) );

  ASSERT_LT( 1, head.childCount() );
  /* verify the escape character text within i tag */
  const Node textNode = head[ 1 ];
  expectEquals( "\n& ", textNode.text() );
}

/**
 * Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text to be Parsed: <i.class> ampersand escape: &amp; </i>
 * correct Ampersand Character Escape inside tag with a class
 */
TEST_F(PayloadEscapeCharacter, AmpersandInsideOneTagWithClass)
{
  loadVtt( "payload/escape/ampersand-inside-tag-with-class.vtt", 1 );
  const Node head = getHeadOfCue( 0 );
  ASSERT_LT( 0, head.childCount() );

  /* verify italic tag */
  const Node italicTag = head[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  /* verify class inside italic tag*/
  StringList cssClass = italicTag.cssClasses();
  expectEquals( "class", cssClass.stringAt(0) );

  ASSERT_LT( 0, italicTag.childCount() );

  /* verify escape character text within i tag */
  const Node textNode = italicTag[ 0 ];
  expectEquals( " ampersand escape: & ", textNode.text() );
}

/**
 * WebVTT Specification Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text to be Parsed:
 * <b><i> some filler text </i></b>
 * &amp;
 * correct Ampersand Character Escape outside two encapsulates tags
 */
TEST_F(PayloadEscapeCharacter, AmpersandOutsideEncapsulatedTags)
{
  loadVtt( "payload/escape/ampersand-outside-encapsulated-tags.vtt", 1 );
  const Node head = getHeadOfCue( 0 );
  ASSERT_LT( 0, head.childCount() );

  /* verify bold tag */
  const Node boldTag = head[0];
  EXPECT_EQ( Node::Bold, boldTag.kind() );
  ASSERT_LT( 0, boldTag.childCount() );

  /* verify italic tag within bold tag */
  const Node italicTag = boldTag[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );
  ASSERT_LT( 1, head.childCount() );

  /* verify character escape outside i tag */
  const Node textNode = head[ 1 ];
  expectEquals( " \n&", textNode.text() );
}

/**
 * WebVTT Specification Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text to be Parsed: <i.class.subclass> ampersand escape: &amp; </i>
 * correct Ampersand Character Escape on line after a tag with a class
 * and subclass
 */
TEST_F(PayloadEscapeCharacter, AmpersandOnLineWithClassAndSubClass)
{
  loadVtt( "payload/escape/"
           "ampersand-inside-tag-with-subclass.vtt", 1 );
  const Node head = getHeadOfCue( 0 );
  ASSERT_LT( 0, head.childCount() );

  /* verify italic tag */
  const Node italicTag = head[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  /* verify class inside italic tag*/
  StringList cssClass = italicTag.cssClasses();
  expectEquals( "class", cssClass.stringAt(0) );

  /* verify subclass within the i tag */
  expectEquals( "subclass", cssClass.stringAt(1) );

  ASSERT_LT( 0, italicTag.childCount() );

  /* verify escape character text within i tag*/
  const Node textNode = italicTag[ 0 ];
  expectEquals( " ampersand escape: & ", textNode.text() );
}

/**
 * WebVTT Specification Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text To be Parsed:
 * <i.class.subclass> Some Filler Text </i>
 * &amp;
 * correct Ampersand Character Escape on new line after a tag with a class
 * and subclass
 */
TEST_F(PayloadEscapeCharacter, AmpersandOnNewlineWithClassAndSubclass)
{
  loadVtt( "payload/escape/"
           "ampersand-outside-tag-on-newline-with-subclass.vtt", 1 );
  const Node head = getHeadOfCue( 0 );
  ASSERT_LT( 0, head.childCount() );

  /* verify italic tag */
  const Node italicTag = head[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  /* verify class inside italic tag */
  StringList cssClass = italicTag.cssClasses();
  expectEquals( "class", cssClass.stringAt(0) );

  /* verify subclass within the i tag */
  expectEquals( "subclass", cssClass.stringAt(1) );

  ASSERT_LT( 1, head.childCount() );
  /* verify character escape outside i tag */
  const Node textNode = head[ 1 ];
  expectEquals( "\n& ", textNode.text() );
}

/**
 * WebVTT Specification Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text To be Parsed: <i.class.subclass> Some Filler Text </i> &amp;
 * correct Ampersand Character Escape on line outside tag with a class
 * and subclass
 */
TEST_F(PayloadEscapeCharacter, AmpersandOutsideTagWithSubclass)
{
  loadVtt( "payload/escape/"
           "ampersand-outside-tag-with-subclass.vtt", 1 );

  const Node head = getHeadOfCue(0);
  ASSERT_LE( 2, head.childCount() );

  /* verify italic tag */
  const Node italicTag = head[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  /* verify class inside italic tag*/
  StringList cssClass = italicTag.cssClasses();
  expectEquals( "class", cssClass.stringAt(0) );

  /* verify subclass within the i tag */
  expectEquals( "subclass", cssClass.stringAt(1) );

  ASSERT_LE( 1, italicTag.childCount() );
  /* verify text node within italic tag */
  expectEquals( " Some Filler Text ", italicTag[0].text() );

  /* verify escape sequence in last text node */
  expectEquals( " & ", head[1].text() );
}

/**
 * WebVTT Specification Version:
 * WebVTT - Living Standard Last Updated 2 October 2012
 *
 * Relates To:
 * Cue Text Escape Characters and Cue Text Tags:
 * http://dev.w3.org/html5/webvtt/#webvtt-cue-text-parsing-rules
 *
 * Description:
 * Cue Text To be Parsed: <i.class> Some Filler Text </i> &amp;
 * correct Ampersand Character Escape on line outside tag with a class
 * and subclass
 */
TEST_F(PayloadEscapeCharacter, AmpersandOutsideTagWithClass)
{
  loadVtt( "payload/escape/"
           "ampersand-outside-tag-with-class.vtt", 1 );
  const Node head = getHeadOfCue(0);
  ASSERT_LE( 2, head.childCount() );

  /* verify italic tag */
  const Node italicTag = head[0];
  EXPECT_EQ( Node::Italic, italicTag.kind() );

  /* verify class inside italic tag*/
  StringList cssClass = italicTag.cssClasses();
  expectEquals( "class", cssClass.stringAt(0) );

  ASSERT_LE( 1, italicTag.childCount() );
  /* verify text node within italic node */
  expectEquals( " Some Filler Text ", italicTag[0].text() );

  /* verify character escape sequence in last text node */
  expectEquals( " & ", head[1].text() );

}

