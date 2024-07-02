#include "cue_testfixture"
class CueIdGeneral : public CueTest { };

/**
 * Test to determine if the most basic one-character cue id passes
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 *
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdGeneral, BasicPass)
{
  loadVtt( "cue-ids/basic_pass.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test to determine if a WEBVTT Cue Id allows a *very* large character input.
 * This test floods the cue ID with characters, but should pass
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 *
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdGeneral, LongString)
{
  loadVtt( "cue-ids/long_string.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
}

/**
 * Test if parser fails if the webvtt file only has a cue id (no timestamp or
 * payload)
 *
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-identifier (11/24/2012)
 *
 * A WebVTT cue identifier is any sequence of one or more characters not
 * containing the substring "-->" (U+002D HYPHEN-MINUS, U+002D HYPHEN-MINUS,
 * U+003E GREATER-THAN SIGN), nor containing any U+000A LINE FEED (LF)
 * characters or U+000D CARRIAGE RETURN (CR) characters.
 *
 * Note: A WebVTT cue identifier can be used to reference a specific cue, for
 * example from script or CSS.
 */
TEST_F(CueIdGeneral, IdOnly)
{
  loadVtt( "cue-ids/id_only.vtt", 0 );
  ASSERT_LE( 1, errorCount() ) << "This file should contain at least 1 error";
  EXPECT_EQ( 1, errorCount() ) << "This file should contain 1 error";

  expectEquals( getError( 0 ), WEBVTT_CUE_INCOMPLETE, 3, 2 );
}
