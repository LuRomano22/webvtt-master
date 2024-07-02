#include "cue_testfixture"
class CueIdLineEndings : public CueTest { };

/**
 * Test if parser fails if there are no line endings (LF OR CRLF) between WEBVTT
 * signature and cue
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
TEST_F(CueIdLineEndings, MissingBetweenSignatureAndId)
{
  loadVtt( "cue-ids/lineendings/missing_between_signature_and_id.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_EXPECTED_EOL, 2, 1 );
}

/**
 * Test if parser fails if there are two line ending characters (LF or CRLF)
 * between cue id and cue timestamp
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
TEST_F(CueIdLineEndings, TwoBetweenIdAndTimestamp)
{
  loadVtt( "cue-ids/lineendings/two_between_id_and_timestamp.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_CUE_INCOMPLETE, 4, 1 );
}

/**
 * Test if parser fails if there are less than two line endings (LF or CRLF)
 * between 2 cues
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
TEST_F(CueIdLineEndings, MissingBetweenPayloadAndId)
{
  loadVtt( "cue-ids/lineendings/missing_between_payload_and_id.vtt", 2 );
  EXPECT_EQ( 0, errorCount() );
}

/**
 * Test to determine if a very large WEBVTT Cue Id allows a *very* large
 * character input.  This test floods the cue ID with characters, and should
 * fail with a LF mixed in with the random 5000+ character cue id.
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
TEST_F(CueIdLineEndings, LongStringLF)
{
  loadVtt( "cue-ids/lineendings/long_string_lf.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_CUE_INCOMPLETE, 4, 1 );
}

/**
 * Test to determine if a very large WEBVTT Cue Id allows a *very* large
 * character input.  This test floods the cue ID with characters, and should
 * fail with a CRLF mixed in with the random 5000+ character cue id.
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
TEST_F(CueIdLineEndings, LongStringCRLF)
{
  loadVtt( "cue-ids/lineendings/long_string_crlf.vtt" );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  expectEquals( getError( 0 ), WEBVTT_CUE_INCOMPLETE, 4, 1 );
}
