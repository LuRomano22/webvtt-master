#include "cue_testfixture"
class CueIdArrow : public CueTest { };

/**
 * Test to determine if random arrows other than "-->" do not fail during
 * parsing
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdArrow, MalformedArrows)
{
  loadVtt( "cue-ids/arrows/malformed_arrows.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test if parser fails when it encounters a cue id containing the substring
 * "-->"
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdArrow, Arrow)
{
  loadVtt( "cue-ids/arrows/arrow.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test if parser fails when it encounters a cue id containing the substring
 * "-->" with an extra ">"
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdArrow, ExtraArrowhead)
{
  loadVtt( "cue-ids/arrows/extra_arrowhead.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test if parser fails when it encounters a cue id containing the substring
 * "-->" with an extra "-"
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdArrow, ExtraMinusSign)
{
  loadVtt( "cue-ids/arrows/extra_minus_sign.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

/**
 * Test to determine if a very large WEBVTT Cue Id allows a *very* large
 * character input.  This test floods the cue ID with characters, and should
 * fail with a --> mixed in with the random 2500+ character cue id.
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdArrow, LongStringWithArrow)
{
  loadVtt( "cue-ids/arrows/long_string_with_arrow.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_EXPECTED_TIMESTAMP, 3, 1 );
}

